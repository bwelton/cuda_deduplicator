#include "CalculateDedupSavings.h"
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
			sscanf(line.c_str(),"%llu,%*u,%llu,%*s,%llu", &id, &size, &dupid);			
			records.push_back(std::make_tuple(id, size, dupid));
		}
	}
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
}

void CalculateDedupSavings::ReadTiming(std::vector<TimingRec> & records, double & finalTime) {
	_typeKeys.clear();
	std::map<std::string, uint32_t> keyToId;
	std::string RR = std::string("RR,"); // 1
	std::string DR = std::string("DR,"); // 2
	std::string CPY = std::string("CPY,"); // 3
	std::string TET = std::string("TET,"); // 3
	uint32_t curKey = 0;

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
		if (line.find(RR) != std::string::npos || line.find(DR) != std::string::npos) {
			sscanf(line.c_str(), "%*s,%s,%llu,%llu,%llu,%llu,%llu", cname,  &corrid, &start_time, &end_time, &procid, &threadid);
			if(line.find(RR) != std::string::npos)
				type_key = 1;
			else
				type_key = 2;
		}
		else if (line.find(CPY) != std::string::npos) {
			sscanf(line.c_str(), "%*s,%s,%llu,%llu,%llu,%llu,%d,%d,%d,%llu", cname,  &corrid, &start_time, &end_time, 
				&size, &runcorr, &ctx, &dev, &stream);
			type_key = 3;
		}
		else if (line.find(TET) != std::string::npos) {
			sscanf(line.c_str(), "%*s,%lf", &finalTime);
			return
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
		records.push_back((std::make_tuple(corrid,type_key,cname_key,start_time,end_time,procid,threadid,size_t(size),runcorr,ctx,dev,stream)));
	}
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