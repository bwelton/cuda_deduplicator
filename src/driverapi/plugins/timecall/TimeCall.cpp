#include "TimeCall.h"
std::shared_ptr<TimeCall> Worker;
thread_local int exited;
TimeCall::TimeCall(std::vector<std::string> & cmd_list) {
	exited = 0;
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
	exited = 1;
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

thread_local std::shared_ptr<TFReaderWriter> _outFile;
thread_local std::shared_ptr<StackKeyWriter> keyFile;
thread_local TF_Record _tfRecord;
thread_local std::vector<std::pair<uint64_t, std::chrono::high_resolution_clock::time_point> > TimingPairs; 
thread_local std::vector<uint64_t> TimingCount; 
thread_local int alreadyStarted = 0;
//std::shared_ptr<LogInfo> _timingLog;

extern "C"{

void INIT_TIMERS() {
	if (_outFile.get() == NULL) {
		_tfRecord.type = TF_SYNCRECORD;
		alreadyStarted = 0;
		std::cerr << "Starting timing log" << std::endl;
		_outFile.reset(new TFReaderWriter());
		_outFile->Open("TF_trace.bin", TF_WRITE);
	}
	if (keyFile.get() == NULL) {
		std::cerr << "Starting keyfile" << std::endl;
		keyFile.reset(new StackKeyWriter(fopen("TF_timekey.bin","w")));
	}
}

void TIMER_SIMPLE_COUNT_ADD_ONE() {
	INIT_TIMERS();
	if (TimingCount.size() > 0)
		TimingCount[TimingCount.size() - 1] += 1;
	else {
		// Write out an unknown timing entry
		

		_outFile->Write(_tfRecord);

		//_outFile->Write(0,0,0,0.0);
		//_outFile->Write(0, 0.0, 1);
		std::cout << "Timing error, trying to add one to an unknown synchronization!" << std::endl;
	}
}

void TIMER_SIMPLE_TIME_START(uint64_t id) {
	INIT_TIMERS();
	TimingCount.push_back(0);
	TimingPairs.push_back(std::make_pair(id,std::chrono::high_resolution_clock::now()));
}

void TIMER_SIMPLE_TIME_STOP(uint64_t id) {
	INIT_TIMERS();
	std::chrono::high_resolution_clock::time_point endTimer = std::chrono::high_resolution_clock::now();

	int found = -1;
	for (int i = TimingPairs.size(); i >= 0; i = i - 1) {
		if (TimingPairs[i].first == id){
			found = i;
			break;
		}
	}
	if (found == -1) {
		std::cerr << "Could not find starting time for call " << id << std::endl;
		assert(found != -1);
	}
	std::chrono::duration<double> diff = endTimer-TimingPairs[found].second;


	if (TimingCount[TimingCount.size() - 1] > 0) {
		std::vector<StackPoint> points;
		bool ret = GET_FP_STACKWALK(points);
		_tfRecord.s.dynId = id;
		_tfRecord.s.count = TimingCount[TimingCount.size() - 1];
		_tfRecord.s.time = diff.count();
		if (ret == false) {
			std::cout << "unknown timing stack, discarding time" << std::endl;
			_tfRecord.s.stackId  = 0;
		} else {
			uint64_t pos = keyFile->InsertStack(points);
			_tfRecord.s.stackId = pos;
		}	
		_outFile->Write(_tfRecord);
	}
	TimingPairs.erase(TimingPairs.begin() + found);
}

void init(std::vector<std::string> & cmd_list) {
	PLUG_BUILD_FACTORY(cmd_list)
}

PluginReturn Precall(std::shared_ptr<Parameters> params){
	if (exited == 1)
		return NO_ACTION;
	return PLUG_FACTORY_PTR->Precall(params);
}

PluginReturn Postcall(std::shared_ptr<Parameters> params) {
	if (exited == 1)
		return NO_ACTION;
	return PLUG_FACTORY_PTR->Postcall(params);
}

}