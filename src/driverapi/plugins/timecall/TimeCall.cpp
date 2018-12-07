#include "TimeCall.h"
std::shared_ptr<TimeCall> Worker;
thread_local int TIMECALL_exited;
TimeCall::TimeCall(std::vector<std::string> & cmd_list) {
	TIMECALL_exited = 0;
	std::ifstream infile("FuncsToTime.txt");
	std::string line;
	while (std::getline(infile, line)) {
		for (int i = 0; i < cmd_list.size(); i++) {
			if (cmd_list[i] == line){
				_callsToMonitor.insert((CallID)i);
				std::cerr << "[TimeCall] Timing - " << cmd_list[i] << std::endl;
				break;
			}
		}
	}
}

TimeCall::~TimeCall() {
	TIMECALL_exited = 1;
	if(_timers.size() > 0) {
		FILE * out = fopen("call_timers.txt","w");
		for(auto i : _timers)
			fprintf(out, "%s,%llu,%f\n",std::get<0>(i), std::get<1>(i), std::get<2>(i));
		fclose(out);
		_timers.clear();
	}
}

PluginReturn TimeCall::Precall(std::shared_ptr<Parameters> params) {
	if (_callsToMonitor.find(params.get()->GetID()) != _callsToMonitor.end()) {
		auto start = std::chrono::high_resolution_clock::now();
		params.get()->Call();
		auto stop = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = stop-start;
		_timers.push_back(std::make_tuple(params.get()->GetName(), params.get()->GetInstID(), diff.count()));
		return PERFORMED_ACTION;
	}
	return NO_ACTION;
}

PluginReturn TimeCall::Postcall(std::shared_ptr<Parameters> params) {
	return NO_ACTION;
}

thread_local std::shared_ptr<TFReaderWriter> TIMECALL_outFile;
thread_local std::shared_ptr<StackKeyWriter> TIMECALL_keyFile;
thread_local TF_Record TIMECALL_tfRecord;
thread_local std::vector<std::pair<uint64_t, std::chrono::high_resolution_clock::time_point> > TIMECALL_TimingPairs; 
thread_local std::vector<uint64_t> TIMECALL_TimingCount; 
thread_local int alreadyStarted = 0;
//std::shared_ptr<LogInfo> _timingLog;

extern "C"{

void INIT_TIMERS() {
	if (TIMECALL_outFile.get() == NULL) {
		TIMECALL_tfRecord.type = TF_SYNCRECORD;
		alreadyStarted = 0;
		std::cerr << "Starting timing log" << std::endl;
		TIMECALL_outFile.reset(new TFReaderWriter());
		TIMECALL_outFile->Open("TF_trace.bin", TF_WRITE);
	}
	if (TIMECALL_keyFile.get() == NULL) {
		std::cerr << "Starting TIMECALL_keyfile" << std::endl;
		TIMECALL_keyFile.reset(new StackKeyWriter(fopen("TF_timekey.bin","w")));
	}
}

void TIMER_SIMPLE_COUNT_ADD_ONE() {
	INIT_TIMERS();
	if (TIMECALL_TimingCount.size() > 0)
		TIMECALL_TimingCount[TIMECALL_TimingCount.size() - 1] += 1;
	else {
		// Write out an unknown timing entry
		

		TIMECALL_outFile->Write(TIMECALL_tfRecord);

		//TIMECALL_outFile->Write(0,0,0,0.0);
		//TIMECALL_outFile->Write(0, 0.0, 1);
		std::cout << "Timing error, trying to add one to an unknown synchronization!" << std::endl;
	}
}

void TIMER_SIMPLE_TIME_START(uint64_t id) {
	INIT_TIMERS();
	TIMECALL_TimingCount.push_back(0);
	TIMECALL_TimingPairs.push_back(std::make_pair(id,std::chrono::high_resolution_clock::now()));
}

void TIMER_SIMPLE_TIME_STOP(uint64_t id) {
	INIT_TIMERS();
	std::chrono::high_resolution_clock::time_point endTimer = std::chrono::high_resolution_clock::now();

	int found = -1;
	for (int i = TIMECALL_TimingPairs.size(); i >= 0; i = i - 1) {
		if (TIMECALL_TimingPairs[i].first == id){
			found = i;
			break;
		}
	}
	if (found == -1) {
		std::cerr << "Could not find starting time for call " << id << std::endl;
		assert(found != -1);
	}
	std::chrono::duration<double> diff = endTimer-TIMECALL_TimingPairs[found].second;


	if (TIMECALL_TimingCount[TIMECALL_TimingCount.size() - 1] > 0) {
		std::vector<StackPoint> points;
		bool ret = GET_FP_STACKWALK(points);
		TIMECALL_tfRecord.s.dynId = id;
		TIMECALL_tfRecord.s.count = TIMECALL_TimingCount[TIMECALL_TimingCount.size() - 1];
		TIMECALL_tfRecord.s.time = diff.count();
		if (ret == false) {
			std::cout << "unknown timing stack, discarding time" << std::endl;
			TIMECALL_tfRecord.s.stackId  = 0;
		} else {
			uint64_t pos = TIMECALL_keyFile->InsertStack(points);
			TIMECALL_tfRecord.s.stackId = pos;
		}	
		TIMECALL_outFile->Write(TIMECALL_tfRecord);
	}
	TIMECALL_TimingPairs.erase(TIMECALL_TimingPairs.begin() + found);
}

void init(std::vector<std::string> & cmd_list) {
	PLUG_BUILD_FACTORY(cmd_list)
}

PluginReturn Precall(std::shared_ptr<Parameters> params){
	if (TIMECALL_exited == 1)
		return NO_ACTION;
	return PLUG_FACTORY_PTR->Precall(params);
}

PluginReturn Postcall(std::shared_ptr<Parameters> params) {
	if (TIMECALL_exited == 1)
		return NO_ACTION;
	return PLUG_FACTORY_PTR->Postcall(params);
}

}