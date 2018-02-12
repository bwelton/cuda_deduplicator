#include "SyncTesting.h"

SyncTesting::SyncTesting(boost::program_options::variables_map vm) :
	_vm(vm) {

}

void SyncTesting::Run() {
	TimeApplications base(_vm);
	double time = base.Run();
	RunWithCUPTI();
	GatherSynchronizationCalls();
	std::cerr << "Launcher has identified the following synchronoization calls" << std::endl;
	for(auto i : _syncCalls) {
		std::cerr << "\t" << i << std::endl;
	}
	GatherSynchronizationDelay();
	InstrumentProgram();
	RunWithLoadStoreAnalysis();
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
	CreatePluginFile(pluginNames);
	std::string def("");
	TimeApplications base(_vm);
	std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string> > extras;
	extras.push_back(std::make_tuple(std::string("wrap"), std::string(INTERNAL_SYNC), std::string("INTER_InternalSynchronization"), std::string(DRIVER_LIBRARY), std::string("ORIGINAL_InternalSynchronization")));
	double time = base.RunWithLoadStore(def, extras);
	//ReadSynchronizationCalls();
}

// void SyncTesting::HandleSynchronizationBreakpoint(ProcessController & p) {

// }

void SyncTesting::HandleBreakpoint(ProcessController * p) {
	std::map<uint64_t, std::vector<StackPoint> > stacks = p->GetThreadStacks();
	for (auto i : stacks) {
		bool containsLibcuda = false;
		for (auto z : i.second) 
			if(z.libname.find("libcuda.so") != std::string::npos) {
				containsLibcuda = true;
				break;
			}
		if (containsLibcuda == true) {
			std::stringstream ss;
			for (auto z : i.second) {
				if(_stackKeys.find(z) == _stackKeys.end())
					_stackKeys.insert(z);
				ss << std::hex << z.framePtr << std::dec << std::endl;
			}
			if (_storedStacks.find(ss.str()) == _storedStacks.end())
				_storedStacks[ss.str()] = 1;
			else
				_storedStacks[ss.str()] += 1;
		}
	}
}

void SyncTesting::InstrumentProgram() {
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
	double time = base.RunWithBreakpoints(def, extras, breakpointNames,pluginLoads, std::bind(&SyncTesting::HandleBreakpoint, this, std::placeholders::_1));
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
	double time = base.RunWithInstrimentation(def, extras);
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