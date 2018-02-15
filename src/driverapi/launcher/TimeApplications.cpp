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
	return InternalRun();
}

double TimeApplications::RunWithInstrimentation(std::string wrapperDef, std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string> > extras) {
	LogInfo log(std::string("CUPTIRun.txt"), std::string("[CUPTI]"), true);
	ProcessController proc(_vm, &log);
	proc.LaunchProcess();
	for (auto i : extras)
		proc.InsertWrapperDef(std::get<0>(i), std::get<1>(i), std::get<2>(i), std::get<3>(i), std::get<4>(i));
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

double TimeApplications::RunWithBreakpoints(std::string wrapperDef, 
											std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string> > extras,
											std::vector<std::string> breakFunctions,
											std::vector<std::string> libLoads,
											std::function<void(ProcessController *)> cb) {
	LogInfo log(std::string("BreakpointRun.txt"), std::string("[BPRun]"), true);
	ProcessController proc(_vm, &log);
	proc.LaunchProcess();
	for (auto i : extras)
		proc.InsertWrapperDef(std::get<0>(i), std::get<1>(i), std::get<2>(i), std::get<3>(i), std::get<4>(i));
	proc.InsertInstrimentation(wrapperDef);
	for (auto i : libLoads) 
		proc.LoadWrapperLibrary(i);

	proc.InsertBreakpoints(breakFunctions);
	proc.ContinueExecution();
	auto start = std::chrono::high_resolution_clock::now();
	while (!proc.IsTerminated()){
		proc.Run();
		if (proc.IsStopped()){
			std::cerr << "[TIMEAPP] Breakpoint has been hit" << std::endl;
			cb(&proc);
			proc.ContinueExecution();
		}
	}
	auto stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = stop-start;
	std::cerr << "[TIMEAPP] Application runtime with instrimentation - " << diff.count() << std::endl;
	return diff.count();	
}


void TimeApplications::IdentifyDyninstBugs(std::string wrapperDef, std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string> > extras, std::vector<std::string> libLoads) {
	std::vector<std::string> testerFunctions = {"_IO_puts","_IO_new_fclose","__GI_fseek"};
	LogInfo outLog(std::string("NonworkingCalls.txt"), std::string("[NonWorking]"), true);
	for (auto n : testerFunctions) {
		remove("run_done.txt");
		LogInfo log(std::string("LoadStoreRun.txt"), std::string("[LSRUN]"), true);
		ProcessController proc(_vm, &log);
		proc.LaunchProcess();
		// proc.InsertLoadStores();
		for (auto i : libLoads) 
			proc.LoadWrapperLibrary(i);
		proc.InsertLoadStoreSingle(std::string(n));
		// for (auto i : extras)
		// 	proc.InsertWrapperDef(std::get<0>(i), std::get<1>(i), std::get<2>(i), std::get<3>(i), std::get<4>(i));
		// proc.InsertInstrimentation(wrapperDef);
		
		std::vector<std::string> bpoints;
		bpoints.push_back(std::string("SYNCH_SIGNAL_DYNINST"));
		bpoints.push_back(std::string("SYNC_RECORD_MEM_ACCESS"));
		bpoints.push_back(std::string("SYNC_RECORD_FUNCTION_ENTRY"));

		//proc.InsertBreakpoints(bpoints);
		proc.ContinueExecution();
		bool inserted = true;
		auto start = std::chrono::high_resolution_clock::now();
		while (!proc.IsTerminated()){
			proc.Run();

			if (proc.IsStopped()) {
				// std::cerr << "Hit breakpoint" << std::endl;
				// std::map<uint64_t, std::vector<StackPoint> > stackmap = proc.GetThreadStacks();
				// for (auto i : stackmap) {
				// 	std::cerr << "Stack length: " << i.second.size() << std::endl;
				// }
				proc.ContinueExecution();
			}

		}
		auto stop = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = stop-start;
		std::cerr << "[TIMEAPP] Application runtime with instrimentation - " << diff.count() << std::endl;
		bool badCall = false;
	    if (FILE *file = fopen("run_done.txt", "r")) {
	        fclose(file);
	    } else {
	        badCall = true;
	    }   
	    if (badCall == true){
	    	std::stringstream ss;
	    	ss << n << std::endl;
	    	outLog.Write(ss.str());
	    	outLog.Flush();
	    	std::cerr << n << " has failed" << std::endl;
	    }
	}

}

double TimeApplications::RunWithLoadStore(std::string wrapperDef, std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string> > extras, std::vector<std::string> libLoads) {
	IdentifyDyninstBugs(wrapperDef, extras, libLoads);
	LogInfo log(std::string("LoadStoreRun.txt"), std::string("[LSRUN]"), true);
	

	ProcessController proc(_vm, &log);

	proc.LaunchProcess();
	// proc.InsertLoadStores();
	for (auto i : libLoads) 
		proc.LoadWrapperLibrary(i);
	proc.InsertLoadStores();
	// for (auto i : extras)
	// 	proc.InsertWrapperDef(std::get<0>(i), std::get<1>(i), std::get<2>(i), std::get<3>(i), std::get<4>(i));
	// proc.InsertInstrimentation(wrapperDef);
	
	std::vector<std::string> bpoints;
	bpoints.push_back(std::string("SYNCH_SIGNAL_DYNINST"));
	bpoints.push_back(std::string("SYNC_RECORD_MEM_ACCESS"));
	bpoints.push_back(std::string("SYNC_RECORD_FUNCTION_ENTRY"));

	//proc.InsertBreakpoints(bpoints);
	proc.ContinueExecution();
	bool inserted = true;
	auto start = std::chrono::high_resolution_clock::now();
	while (!proc.IsTerminated()){
		proc.Run();

		if (proc.IsStopped()) {
			// std::cerr << "Hit breakpoint" << std::endl;
			// std::map<uint64_t, std::vector<StackPoint> > stackmap = proc.GetThreadStacks();
			// for (auto i : stackmap) {
			// 	std::cerr << "Stack length: " << i.second.size() << std::endl;
			// }
			proc.ContinueExecution();
		}

	}
	auto stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = stop-start;
	std::cerr << "[TIMEAPP] Application runtime with instrimentation - " << diff.count() << std::endl;
	return diff.count();	
}

