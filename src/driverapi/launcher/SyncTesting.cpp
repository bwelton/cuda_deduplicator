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
	CreatePluginFile(cupti_plugin);
	CreateFunctionTimers(funcsToTime);
	TimeApplications base(_vm);
	std::string def("");
	std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string> > extras;
	extras.push_back(std::make_tuple(std::string("wrap"), std::string(INTERNAL_SYNC), std::string("INTER_InternalSynchronization"), std::string(DRIVER_LIBRARY), std::string("ORIGINAL_InternalSynchronization")));
	double time = base.RunWithInstrimentation(def, extras);
}