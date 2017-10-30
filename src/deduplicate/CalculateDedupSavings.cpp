#include "CalculateDedupSavings.h"
#define DEBUG 1
CalculateDedupSavings::CalculateDedupSavings(char * timeline_file, char * correlation_file, char * timing_file) :
	_timeline_file(strdup(timeline_file)), _correlation_file(strdup(correlation_file)), _timing_file(strdup(timing_file))
{

}

void CalculateDedupSavings::ReadTimeline(std::vector<TimelineRec> & records) {
	std::ifstream t(_timeline_file);
	if (!t.good()) {
		std::cerr << "Could not open timeline file" << std::endl;
	}
	std::string line;
	uint64_t id, dupid;
	size_t size;
	assert(sizeof(uint64_t) != sizeof(size_t));
	while (std::getline(t, line)) {
		if (line.size() > 2) {
			std::replace( line.begin(), line.end(), ',', ' ');
			sscanf(line.c_str(),"%llu %*u %llu %*s %llu\n", &id, &size, &dupid);			
			records.push_back(std::make_tuple(id, size, dupid));
		}
	}
	std::cerr << "We have read " << records.size() << " records from Timeline file" << std::endl;
}
void CalculateDedupSavings::ReadCorrelation(std::vector<CorrelationRec> & records) {
	std::ifstream t(_correlation_file);
	if (!t.good()) {
		std::cerr << "Could not open correlation file" << std::endl;
	}
	std::string line;
	uint64_t id, stream, procid, threadid;
	while (std::getline(t, line)) {
		if (line.size() > 2) {
			sscanf(line.c_str(), "%llu,%*llu,%llu,%llu,%llu", &id, &stream, &procid, &threadid);			
			records.push_back(std::make_tuple(id, stream, procid, threadid));
		}
	}	
	std::cerr << "We have read " << records.size() << " records from Correlation file" << std::endl;
}

bool CalculateDedupSavings::IsTransfer(CUPTIRecord & a) {
	if (std::get<2>(a) != 0) {
		return true;
	}
	return false;
}

std::pair<uint64_t, uint64_t> CalculateDedupSavings::CalculateProcessSavings(CUDAProcess & proc) {
	uint64_t min = 0;
	uint64_t max = 0;
	uint64_t ctrans = 0;
	uint64_t gtrans = 0;

	CUPTIRecord rec;
	int type;
	for (auto i : proc.transferRecords) {
		while (proc.GetNextCUPTITransferOrSynchronization(rec, type, _typeKeys)){
		// Check if transfers match, continue otherwise
			if (type == 1) {
				// if the sizes don't match, continue to next transfer....
				if (std::get<7>(rec) != std::get<1>(i)) {
					std::cerr << "Skipping a record" << std::endl;
					continue;
				}
				if (std::get<2>(i) > 0) {
					ctrans += std::get<4>(rec);
					gtrans += std::get<3>(rec);
				}
			} else if (type == 2) {
				min += ctrans;
				max += ctrans + gtrans;
				ctrans = 0;
				gtrans = 0;
				continue;
			} else if (type == 3) {
				// If the sizes match, we have a record match
				if (std::get<7>(rec) == std::get<1>(i)) {
					if (std::get<2>(i) > 0) {
						ctrans += std::get<4>(rec);
						gtrans += std::get<3>(rec);
					}
				}
				min += ctrans;
				max += ctrans + gtrans;
				ctrans = 0;
				gtrans = 0;
				if (std::get<7>(rec) != std::get<1>(i)){
					std::cerr << "Skipping a record" << std::endl;
					continue;
				}
			}
			break;
		}
	}
	return std::make_pair(min,max);
}

void CalculateDedupSavings::NormalizeProcessIDs(std::vector<CombinedRecord> & correlation,
												std::vector<CUDAProcess> & procs) {
	// If we only have one process, we know that CPU/GPU process ID's will match with procs.
	if (procs.size() == 1) {
		procs[0].procid = std::get<4>(correlation[0]);
		procs[0].threadid = std::get<5>(correlation[0]);
		procs[0].transferRecords = correlation;
		return;
	}

	// If we have more than one process.... Right now we must infer what CUPTI reported process
	// matches the CPU reported process. 
	// Why? CUPTI ThreadID's don't match anything "known".
	
	// First split the CPU up into procs...
	std::vector<CPUProcess> cpuProcs;
	for (auto i : correlation) {
		bool found = false;
		for (auto z : cpuProcs) {
			if (z == i){
				z.transferRecords.push_back(i);
				found = true;
			}
		}
		if (found == false){
			CPUProcess newProc;
			newProc.procid = std::get<4>(i);
			newProc.threadid = std::get<5>(i);
			newProc.transferRecords.push_back(i);
			cpuProcs.push_back(newProc);
		}
	}
	
	for (auto i : cpuProcs) {
		std::vector<int> counts;
		bool found = false;
		for (auto z : procs) {
			if (z == i) {
				found = true;
				z.transferRecords = i.transferRecords;
				z.procid = i.procid;
				z.threadid = i.threadid;
				z.matched = true;
				break;
			} else {
				counts.push_back(z.MatchEntries(i));
			}
		}
		if (found != false) {
			int lowestPos = 100000000;
			int lowestProc = -1;
			for(int z = 0; z < counts.size(); z++) {
				if (counts[z] < lowestPos && procs[z].matched == false) {
					lowestProc = z;
					lowestPos = z;
				}
			}
			if (lowestProc == -1) {
				std::cerr << "WE COULD NOT MATCH A CPU PROCESS TO A GPU PROCESS, EXITING NOW" << std::endl;
				exit(-1);
			}
			procs[lowestProc].transferRecords = i.transferRecords;
			procs[lowestProc].procid = i.procid;
			procs[lowestProc].threadid = i.threadid;
			procs[lowestProc].matched = true;
		}
	}
}	
//         Min      Max
std::pair<uint64_t, uint64_t> CalculateDedupSavings::GenerateEstimate(std::vector<TimingRec> & timing, 
																	  std::vector<CombinedRecord> & correlation) {
	// Sort the timing records to get them in order 
	std::sort(timing.begin(), timing.end(), 
		[](const TimingRec & a, const TimingRec & b) -> bool {
			return std::get<0>(a) < std::get<0>(b);
		});


	uint64_t corrid, start_time, end_time, procid, threadid, size, stream;
	uint32_t type_key, cname_key;
	int runcorr, ctx, dev;
	std::vector<CUDAProcess> procs;
	CUPTIRecord rec = std::make_tuple(0,0,0,0,0,0,0,0,0,0,0,0);
	int64_t currentRecord = -1;

	for (auto i : timing) {
		std::tie(corrid, type_key, cname_key, start_time, end_time, procid, threadid, size, runcorr, ctx, dev, stream) = i;
		if (currentRecord != corrid && currentRecord != -1){
			bool found = false;
			for (auto z : procs) {
				if (std::get<5>(rec) == z.procid && std::get<6>(rec) == z.threadid){
					found = true;
					z.records.push_back(rec);
				}
			}
			if (found == false){
				CUDAProcess tmp;
				tmp.procid = std::get<5>(rec);
				tmp.threadid = std::get<6>(rec);
				tmp.records.push_back(rec);
				procs.push_back(tmp);
			}
			currentRecord = corrid;
			rec = std::make_tuple(0,0,0,0,0,0,0,0,0,0,0,0);
		} else {
			currentRecord = corrid;
		}
		if (type_key == 1 || type_key == 2){
			std::get<0>(rec) = corrid;
			std::get<1>(rec) = cname_key;
			std::get<4>(rec) = std::get<4>(rec) + (end_time - start_time);
			std::get<5>(rec) = procid;
			std::get<6>(rec) = threadid;
		} else if (type_key == 3){
			std::get<0>(rec) = corrid;
			std::get<2>(rec) = cname_key;
			std::get<3>(rec) = std::get<3>(rec) + (end_time - start_time);
			std::get<7>(rec) = size;
			std::get<8>(rec) = runcorr;
			std::get<9>(rec) = ctx;
			std::get<10>(rec) = dev;
			std::get<11>(rec) = stream;
		}
	}
	NormalizeProcessIDs(correlation, procs);


	// This will need to change when we have a multi-process model that is more reliable....
	std::vector<std::pair<uint64_t, uint64_t> > timeSavedPerProc;
	for (auto i : procs) {
		timeSavedPerProc.push_back(CalculateProcessSavings(i));
	}
	uint64_t min = std::numeric_limits<uint64_t>::max();
	uint64_t max = 0;
	for (auto i : timeSavedPerProc){
		if (i.first < min) {
			min = i.first;
		} 
		if (i.second > max) 
		{
			max = i.second;
		}
	}
	return std::make_pair(min,max);
}
int CalculateDedupSavings::NameToId(std::string name){
	for(auto i : _typeKeys) {
		if (i.second == name) {
			return i.first;
		}
	}
	return -1;
}
void CalculateDedupSavings::ReadTiming(std::vector<TimingRec> & records, double & finalTime) {
	_typeKeys.clear();
	std::map<std::string, uint32_t> keyToId;
	std::string RR = std::string("RR "); // 1
	std::string DR = std::string("DR "); // 2
	std::string CPY = std::string("CPY "); // 3
	std::string TET = std::string("TET "); // 4
	uint32_t curKey = 1;

	std::ifstream t(_timing_file);
	if (!t.good()) {
		std::cerr << "Could not open timing file" << std::endl;
	}
	std::string line;
	uint64_t corrid, start_time, end_time, procid, threadid, size, stream;
	uint32_t type_key, cname_key;
	int runcorr, ctx, dev;
	char cname[4096];
	std::string cnameStr;
	while (std::getline(t, line)) {
		corrid = 0; start_time = 0; end_time = 0; procid = 0; threadid = 0; size = 0; stream = 0;
		type_key = 0; cname_key = 0; runcorr = 0; ctx = 0; dev = 0;
		std::replace( line.begin(), line.end(), ',', ' ');
#ifdef DEBUG
		std::cerr << line << std::endl;
#endif
		if (line.find(RR) != std::string::npos || line.find(DR) != std::string::npos) {
			sscanf(line.c_str(), "%*s %s %llu %llu %llu %llu %llu", cname,  &corrid, &start_time, &end_time, &procid, &threadid);
			if(line.find(RR) != std::string::npos)
				type_key = 1;
			else
				type_key = 2;
		}
		else if (line.find(CPY) != std::string::npos) {
			sscanf(line.c_str(), "%*s %s %llu %llu %llu %llu %d %d %d %llu", cname,  &corrid, &start_time, &end_time, 
				&size, &runcorr, &ctx, &dev, &stream);
			type_key = 3;
		}
		else if (line.find(TET) != std::string::npos) {
			sscanf(line.c_str(), "%*s %lf", &finalTime);
			break;
		} else {
			assert("WE SHOULDN'T BE HERE" == 0);
		}

		cnameStr = std::string(cname);
		if (keyToId.find(cnameStr) != keyToId.end()) {
			cname_key = keyToId[cnameStr];
		} else {
			keyToId[cnameStr] = curKey;
			_typeKeys[curKey] = cnameStr;
			cname_key = curKey;
			curKey++;
		}
#ifdef DEBUG
		std::cerr << corrid << "," << type_key <<"," << cname_key <<"," << start_time <<"," << end_time <<"," << procid <<"," << threadid <<"," << size_t(size) <<"," << runcorr <<"," << ctx <<"," << dev <<"," << stream << std::endl;
#endif
		records.push_back((std::make_tuple(corrid,type_key,cname_key,start_time,end_time,procid,threadid,size_t(size),runcorr,ctx,dev,stream)));
	}
	std::cerr << "We have read " << records.size() << " records from ReadTiming file" << std::endl;
}

void CalculateDedupSavings::CombineTimelineCorrelation(std::vector<TimelineRec> & timeline, 
													   std::vector<CorrelationRec> & correlation,
													   std::vector<CombinedRecord> & output) {
	// Sort the ids for both.
	std::sort(timeline.begin(), timeline.end(), 
		[](const TimelineRec & a, const TimelineRec & b) -> bool {
			return std::get<0>(a) < std::get<0>(b);
		});
	std::sort(correlation.begin(), correlation.end(), 
		[](const CorrelationRec & a, const CorrelationRec & b) -> bool {
			return std::get<0>(a) < std::get<0>(b);
		});
	assert(timeline.size() == correlation.size());
	size_t location = 0;
	bool failed = false;
	for (auto i : timeline){
		if (std::get<0>(i) != std::get<0>(correlation[location])){
			failed = true;
		}
		output.push_back(std::make_tuple(std::get<0>(i), std::get<1>(i), std::get<2>(i), 
				std::get<1>(correlation[location]), std::get<2>(correlation[location]), std::get<3>(correlation[location])));
		location++;
	}
	assert(failed == false);
}