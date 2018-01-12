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
			fprintf(out, "%llu,%f\n",i.first, i.second);
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
		_timers.push_back(std::make_pair(params.get()->GetInstID(), diff.count()));
		return PERFORMED_ACTION;
	}
	return NO_ACTION;
}

PluginReturn TimeCall::Postcall(std::shared_ptr<Parameters> params) {
	return NO_ACTION;
}

extern "C"{

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