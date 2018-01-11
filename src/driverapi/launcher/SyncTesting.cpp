#include "SyncTesting.h"

SyncTesting::SyncTesting(boost::program_options::variables_map vm) :
	_vm(vm) {

}

void SyncTesting::Run() {
	TimeApplications base(_vm);
	double time = base.Run();
	RunWithCUPTI();
	GatherSynchronizationDelay();
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

void SyncTesting::RunWithCUPTI() {
	std::vector<std::string> cupti_plugin = {"libCUPTIEventHandler"};
	CreatePluginFile(cupti_plugin);
	TimeApplications base(_vm);
	std::string def(WRAPPER_DEF);
	double time = base.RunWithInstrimentation(def);
}

void SyncTesting::GatherSynchronizationDelay() {
	std::vector<std::string> cupti_plugin;
	CreatePluginFile(cupti_plugin);
	TimeApplications base(_vm);
	std::string def("");
	std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string> > extras;
	extras.push_back(std::make_tuple(std::string("wrap"), std::string(INTERNAL_SYNC), std::string("INTER_InternalSynchronization"), std::string(DRIVER_LIBRARY), std::string("ORIGINAL_InternalSynchronization")));
	double time = base.RunWithInstrimentation(def, extras);
}