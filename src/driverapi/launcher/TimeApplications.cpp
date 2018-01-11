#include "TimeApplications.h"

TimeApplications::TimeApplications(boost::program_options::variables_map vm) :
	_vm(vm) {

}

double TimeApplications::InternalRun() {
	LogInfo log(std::string(""), std::string(""), false);
	ProcessController proc(_vm, &log);
	proc.LaunchProcess();
	assert(proc.ContinueExecution() == true);
	auto start = std::chrono::high_resolution_clock::now();
	while (!proc.IsTerminated()){
		proc.Run();
		assert(proc.ContinueExecution() == true);
	}
	auto stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = stop-start;
	std::cerr << "[TIMEAPP] Application runtime without instrimentation - " << diff.count() << std::endl;
	return diff.count();	
}

double TimeApplications::Run() {
	// Run this twice to get rid of dyninst overhead....
	double ignore = InternalRun();
	return InternalRun();
}

double TimeApplications::RunWithInstrimentation(std::string wrapperDef) {
	LogInfo log(std::string("CUPTIRun.txt"), std::string("[CUPTI]"), true);
	ProcessController proc(_vm, &log);
	proc.LaunchProcess();
	proc.InsertInstrimentation(wrapperDef);
	proc.ContinueExecution();
	auto start = std::chrono::high_resolution_clock::now();
	while (!proc.IsTerminated()){
		proc.Run();
	}
	auto stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = stop-start;
	std::cerr << "[TIMEAPP] Application runtime with instrimentation - " << diff.count() << std::endl;
	return diff.count();	
}


