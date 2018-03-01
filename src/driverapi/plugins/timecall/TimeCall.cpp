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
		// uint64_t * firstArg = ((uint64_t*)params.get()->GetParameter(0));
		// uint64_t * secondArg = ((uint64_t*)params.get()->GetParameter(1));
		// uint64_t * thirdArg = ((uint64_t*)params.get()->GetParameter(2));
		// std::cerr << "Call To Sync: " << firstArg[0] << "," << secondArg[0] << "," << thirdArg[0] << std::endl;
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

thread_local std::vector<std::pair<std::string, std::chrono::high_resolution_clock::time_point> > TimingPairs; 
thread_local std::vector<uint64_t> TimingCount; 
thread_local int alreadyStarted = 0;
std::shared_ptr<LogInfo> _timingLog;

extern "C"{

void TIMER_SIMPLE_COUNT_ADD_ONE() {
	if (TimingCount.size() > 0)
		TimingCount[TimingCount.size() - 1] += 1;
	else {
		std::cerr << "Timing error, trying to add one to an unknown synchronization!" << std::endl;
	}
}

void TIMER_SIMPLE_TIME_START(const char * callName) {
	if (_timingLog.get() == NULL) {
		alreadyStarted = 0;
		std::cerr << "Starting timing log" << std::endl;
		_timingLog.reset(new LogInfo(fopen("callDelay.out", "w")));
	}
	TimingCount.push_back(0);
	TimingPairs.push_back(std::make_pair(std::string(callName),std::chrono::high_resolution_clock::now()));
}

void TIMER_SIMPLE_TIME_STOP(const char * callName) {
	std::chrono::high_resolution_clock::time_point endTimer = std::chrono::high_resolution_clock::now();
	std::string tmp = std::string(callName);
	int found = -1;
	for (int i = TimingPairs.size(); i >= 0; i = i - 1) {
		if (TimingPairs[i].first == tmp){
			found = i;
			break;
		}
	}
	if (found == -1) {
		std::cerr << "Could not find starting time for call " << tmp << std::endl;
		assert(found != -1);
	}
	std::chrono::duration<double> diff = endTimer-TimingPairs[found].second;
	std::stringstream ss;
	if (TimingCount[TimingCount.size() - 1] > 0){
		ss << callName << "," << diff.count() << "," << TimingCount[TimingCount.size() - 1];
		_timingLog->Write(ss.str());
	}
	TimingCount.pop_back();
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