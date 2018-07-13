#include "SyncTesting.h"

SyncTesting::SyncTesting(boost::program_options::variables_map vm) :
	_vm(vm) {
	if (vm.count("prog") > 0){
		std::vector<std::string> progName = _vm["prog"].as<std::vector<std::string> >();
		_programName = std::string(basename((char *)progName[0].c_str()));
	}	
}

void SyncTesting::ReprocessModel() {
	// Add a bogus execution time for now so that other things do not break
	_model.AddExecutionTime(0.0);

	// Get the stacks and line info.
	_model.ReadStackFiles();
	//_model.ExtractLineInfo();

	// Get the timing list
	std::vector<StackPoint> timingList;
	_model.GetTimingList(timingList);

	// Read the syncronization times.
	_model.CaptureSyncTime();
}

void SyncTesting::Run() {
	double time;
	// {
	// 	TimeApplications base(_vm);
	// 	std::cerr << "Running " << _programName << " without instrimentation to obtain total execution time" << std::endl;
	// 	std::cerr << "Saving application output to file : " << _programName << ".base.out" << std::endl;
	// 	//base.RedirectOutToFile(_programName + std::string(".base.out"));
	// 	time = base.Run();
	// 	//base.ReturnToTerminal();
	// 	_model.AddExecutionTime(time);
	// 	std::cerr << "Application executed with runtime of - " << time << "s" << std::endl;
	// }
	
	
	// //RunWithCUPTI();

	// // Find out what user called functions actually contain a synchronization.
	// // This also captures secret entries into libcuda with synchronizations and relates them back
	// // to user level calls. 
	// {
	// 	// Remove all previous stack files from this directory.
	// 	system("exec rm -rf ./stackOut.*");
	// 	TimeApplications base(_vm);
	// 	std::cerr << "Running " << _programName << " with stacktrace information enabled" << std::endl;
	// 	std::cerr << "Saving application output to file : " << _programName << ".stacktrace.out" << std::endl;
	// 	//base.RedirectOutToFile(_programName + std::string(".stacktrace.out"));
	// 	time = base.RunWithStackTracing();
	// 	//base.ReturnToTerminal();
	// 	_model.AddExecutionTime(time);
	// 	std::cerr << "Application executed with runtime of - " << time << "s" << std::endl;		
	// }
	// //return;
	//  _model.ReadStackFiles();
	// //_model.ExtractLineInfo();
	// //InstrumentProgram();
	// std::vector<StackPoint> timingList;
	// _model.GetTimingList(timingList);
	// std::cout << "Timing list of size - " << timingList.size() << std::endl;

	// // Get timing for these functions
	// {
	// 	TimeApplications base(_vm);
	// 	std::cerr << "Running " << _programName << " with timing information enabled" << std::endl;
	// 	std::cerr << "Saving application output to file : " << _programName << ".time.out" << std::endl;
	// 	base.RedirectOutToFile(_programName + std::string(".time.out"));		
	// 	double mytime = base.InternalRunWithTiming(timingList);
	// 	base.ReturnToTerminal();
	// 	_model.AddExecutionTime(mytime);	
	// 	std::cerr << "Application executed with runtime of - " << mytime << "s" << std::endl;	
	// }


	// // Check that our timing run matches the synchronizations identified.
	// // If so, this program is very likely deterministic given the same inputs in relation to cuda calls.
	// _model.CaptureSyncTime();
	// //return;

	// Load Store Instrimentation.
	// What needs to be captured:
	// 		Function Entry for each function that Synchronizes* 
	//      Function Exit for each function that Synchronizes*
	//          Capture only target functions which we dont know.
	//      Synchronization Call
	//      Memory Allocations and Transfers
	//      Load Stores elsewhere
	// 
	{	
		std::vector<std::string> pluginNames = {"libSynchTool"};
		CreatePluginFile(pluginNames);
		std::string def(WRAPPER_DEF);
		//std::string def("");
		TimeApplications base(_vm);
		std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string> > extras;
		std::map<uint64_t, StackRecord> stackSyncs; //= _model.GetTimingStackRecords();
		//std::map<uint64_t, StackRecord> stackSyncs = _model.GetTimingStackRecords();
		//extras.push_back(std::make_tuple(std::string("wrap"), std::string(INTERNAL_SYNC), std::string("INTER_InternalSynchronization"), std::string(DRIVER_LIBRARY), std::string("ORIGINAL_InternalSynchronization")));
		double time = base.RunWithLSInstrimentation(def, extras, timingList, stackSyncs);
		//std::cerr << "[Base] We are setting up syncs checking with " << stackSyncs.size() << std::endl;
		//_model.AddFirstUses(base._firstUses);
	}
	//_model.FixLSStackFiles();
	// We are done running. Perform Analysis.
	//_model.FinalProcessing();

	// //GatherSynchronizationCalls();
	// std::cerr << "Launcher has identified the following synchronoization calls" << std::endl;
	// for(auto i : _syncCalls) {
	// 	std::cerr << "\t" << i << std::endl;
	// }
	// GatherSynchronizationDelay();
	// InstrumentProgram();
	// RunWithLoadStoreAnalysis();
}

void SyncTesting::ReadDefinition(std::string WrapperDef) {
	std::ifstream f;
	std::string line;
	f.open(WrapperDef.c_str(),std::ifstream::in);
	while (std::getline(f, line)) {
	    std::stringstream ss(line);
	    std::vector<std::string> tokens;
	    std::string item;
	    while (std::getline(ss, item, ',')) {
	        tokens.push_back(item);
	    }
	    if (tokens.size() != 5) {
	    	std::cerr << std::string("Token size is not 5 in wrapper def.... skipping this function\n");
	    	std::cerr << std::string("Line skipped: ")  << line << std::endl;
	    } else {
	    	std::transform(tokens[0].begin(), tokens[0].end(), tokens[0].begin(), ::tolower);
	    	_wrapperDefFunctions.push_back(std::make_tuple(tokens[0],tokens[1],tokens[2],tokens[3], tokens[4]));
	    }
	}
}

void SyncTesting::CreatePluginFile(std::vector<std::string> plugins) {
	std::vector<std::string> PluginList = PLUGIN_LIST;
	std::ofstream pfile;
	pfile.open("pluginlist.txt");
	for (auto i : plugins) {
		for (auto z : PluginList) {
			if (z.find(i) != std::string::npos){
				pfile << z << std::endl;
				break;
			}
		}
	}
	pfile.close();
}

void SyncTesting::ReadSynchronizationCalls() {
  std::ifstream ifs ("synchronous_calls.txt", std::ifstream::in);
  std::string line;
  while (std::getline(ifs, line)) {
  	_syncCalls.insert(line);
  }
  ifs.close();
}

void SyncTesting::GatherSynchronizationCalls() {
	std::vector<std::string> pluginNames = {"libSynchTool"};
	CreatePluginFile(pluginNames);
	std::string def(WRAPPER_DEF);
	TimeApplications base(_vm);
	std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string> > extras;
	extras.push_back(std::make_tuple(std::string("wrap"), std::string(INTERNAL_SYNC), std::string("INTER_InternalSynchronization"), std::string(DRIVER_LIBRARY), std::string("ORIGINAL_InternalSynchronization")));
	double time = base.RunWithInstrimentation(def, extras);
	ReadSynchronizationCalls();
}

void SyncTesting::RunWithLoadStoreAnalysis() {
	std::vector<std::string> pluginNames = {"libSynchTool"};
	std::vector<std::string> pluginLoads;
	std::vector<std::string> PluginList = PLUGIN_LIST;
	for (auto i : PluginList) {
		if (i.find("libSynchTool") != std::string::npos){
			pluginLoads.push_back(i);
			break;
		}
	}	
	CreatePluginFile(pluginNames);
	std::string def("");
	TimeApplications base(_vm);
	std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string> > extras;
	extras.push_back(std::make_tuple(std::string("wrap"), std::string(INTERNAL_SYNC), std::string("INTER_InternalSynchronization"), std::string(DRIVER_LIBRARY), std::string("ORIGINAL_InternalSynchronization")));
	double time = base.RunWithLoadStore(def, extras, pluginLoads);
	//ReadSynchronizationCalls();
}

// void SyncTesting::HandleSynchronizationBreakpoint(ProcessController & p) {

// }

void SyncTesting::HandleBreakpoint(ProcessController * p) {
	std::map<uint64_t, std::vector<StackPoint> > stacks = p->GetThreadStacks();
	// for (auto i : stacks) {
	// 	bool containsLibcuda = false;
	// 	for (auto z : i.second) 
	// 		if(z.libname.find("libSynchTool.so") != std::string::npos) {
	// 			containsLibcuda = true;
	// 			break;
	// 		}
	// 	if (containsLibcuda == true) {
	// 		_model.AddStack(i.second);
	// 		std::stringstream ss;
	// 		for (auto z : i.second) {
	// 			if(_stackKeys.find(z) == _stackKeys.end())
	// 				_stackKeys.insert(z);
	// 		}
	// 		if (_storedStacks.find(ss.str()) == _storedStacks.end())
	// 			_storedStacks[ss.str()] = 1;
	// 		else
	// 			_storedStacks[ss.str()] += 1;
	// 	}
	// }
}

void SyncTesting::InstrumentProgram() {
	// This is going to be off by one for the first synchronization call.....

	std::vector<std::string> pluginNames = {"libSynchTool"};
	std::vector<std::string> pluginLoads;
	std::vector<std::string> PluginList = PLUGIN_LIST;
	std::vector<std::string> breakpointNames = {"SYNCH_SIGNAL_DYNINST"};
	for (auto i : PluginList) {
		if (i.find("libSynchTool") != std::string::npos){
			pluginLoads.push_back(i);
			break;
		}
	}
	CreatePluginFile(pluginNames);
	std::string def("");
	TimeApplications base(_vm);
	std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string> > extras;
	extras.push_back(std::make_tuple(std::string("wrap"), std::string(INTERNAL_SYNC), std::string("INTER_InternalSynchronization"), std::string(DRIVER_LIBRARY), std::string("ORIGINAL_InternalSynchronization")));
	base.RedirectOutToFile(_programName + std::string(".breakpoint.out"));
	double time = base.RunWithBreakpoints(def, extras, breakpointNames,pluginLoads, std::bind(&SyncTesting::HandleBreakpoint, this, std::placeholders::_1));
	base.ReturnToTerminal();
	//ReadSynchronizationCalls();
}

void SyncTesting::CreateFunctionTimers(std::vector<std::string> functions) {
	std::ofstream pfile;
	pfile.open("FuncsToTime.txt");
	for (auto i : functions) {
		pfile << i << std::endl;
	}
	pfile.close();	
}

void SyncTesting::RunWithCUPTI() {
	std::vector<std::string> cupti_plugin = {"libCUPTIEventHandler"};
	CreatePluginFile(cupti_plugin);
	TimeApplications base(_vm);
	std::string def(WRAPPER_DEF);
	std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string> > extras;
	base.RedirectOutToFile(_programName + std::string(".cupti.out"));
	double time = base.RunWithInstrimentation(def, extras);
	base.ReturnToTerminal();
}

void SyncTesting::GatherSynchronizationDelay() {
	std::vector<std::string> cupti_plugin = {"libTimeCall"};
    std::vector<std::string> funcsToTime = {"InternalSynchronization"};
	std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string> > extras;
	ReadDefinition(std::string(WRAPPER_DEF));
	std::set<std::string> check;
	for (auto i : _wrapperDefFunctions) {
		std::string tmp = std::get<1>(i);
		std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
		for (auto z : _syncCalls) {
			std::string tmp2 = z;
			std::transform(tmp2.begin(), tmp2.end(), tmp2.begin(), ::tolower);
			tmp2 = tmp2 + std::string("_v2");
			if (tmp == tmp2) {
				extras.push_back(i);
				funcsToTime.push_back(std::get<1>(i));
				check.insert(z);
				break;
			}	
			tmp2 = z;
			std::transform(tmp2.begin(), tmp2.end(), tmp2.begin(), ::tolower);	
			if (tmp == tmp2) {
				extras.push_back(i);
				funcsToTime.push_back(std::get<1>(i));
				check.insert(z);
				break;
			}
		}
	}
	if (check.size() != _syncCalls.size())
		std::cerr << "POTENTIAL ERROR - Sync calls do not match timing calls!" << std::endl;
	CreatePluginFile(cupti_plugin);
	CreateFunctionTimers(funcsToTime);
	TimeApplications base(_vm);
	std::string def("");
	extras.push_back(std::make_tuple(std::string("wrap"), std::string(INTERNAL_SYNC), std::string("INTER_InternalSynchronization"), std::string(DRIVER_LIBRARY), std::string("ORIGINAL_InternalSynchronization")));
	double time = base.RunWithInstrimentation(def, extras);
}