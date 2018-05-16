#include "StageOne.h"
StageOne::StageOne(boost::program_options::variables_map vm) : _vm(vm) {
	std::vector<std::string> progName = _vm["prog"].as<std::vector<std::string> >();
	_rw = BinaryRewriter(progName[0], true, std::string("stageOne"),false);
}

bool StageOne::Run() {
	_rw.OpenLibrary(std::string("libcuda.so.1"));
	_rw.OpenLibrary(std::string(LOCAL_INSTALL_PATH) + std::string("/lib/plugins/libStacktrace.so"));	
	StacktraceInst inst(_rw.GetAppBinary()->GetAddressSpace(), _rw.GetAppBinary()->GetImage());
	inst.InsertStackInst();
	inst.InsertDLOpenCapture();
	// Run application until completion
	_rw.GetAppBinary()->RunUntilCompletion();	
}