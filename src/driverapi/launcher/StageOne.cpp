#include "StageOne.h"
StageOne::StageOne(boost::program_options::variables_map vm) : _vm(vm) {
	std::vector<std::string> progName = _vm["prog"].as<std::vector<std::string> >();
	_rw = ProcessRewriter(progName);
}

bool StageOne::Run() {
	assert(_rw.OpenLibrary(std::string("libcuda.so.1")) == true);
	assert(_rw.OpenLibrary(std::string(LOCAL_INSTALL_PATH) + std::string("/lib/plugins/libStacktrace.so")) == true);	
	StacktraceInst inst(_rw.GetAppBinary()->GetAddressSpace(), _rw.GetAppBinary()->GetImage());
	inst.InsertStackInst();
	// Run application until completion
	_rw.GetAppBinary()->RunUntilCompletion();
	
}