#include "TimeApplications.h"

TimeApplications::TimeApplications(boost::program_options::variables_map vm) :
	_vm(vm) {

}

double TimeApplications::Run() {
	ProcessController proc(_vm);
	proc.LaunchProcess();
	auto start = std::chrono::high_resolution_clock::now();
	while (!proc.IsTerminated())
		proc.ContinueExecution();
	auto stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = stop-start;
	std::cerr << "[TIMEAPP] Application runtime without instrimentation - " << diff.count() << std::endl;
	return diff.count();	
}

