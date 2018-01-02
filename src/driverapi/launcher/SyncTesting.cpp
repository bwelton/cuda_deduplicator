#include "SyncTesting.h"

SyncTesting::SyncTesting(boost::program_options::variables_map vm) :
	_vm(vm) {

}

void SyncTesting::Run() {
	TimeApplications base(_vm);
	double time = base.Run();
	double CUPTITiming = RunWithCUPTI();

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
}

void SyncTesting::RunWithCUPTI() {
	std::vector<std::string> cupti_plugin = {"libCUPTIEventHandler"};
	CreatePluginFile(cupti_plugin);
	TimeApplications base(_vm);
	std::string def(WRAPPER_DEF);
	double time = base.RunWithInstrimentation(def);

}