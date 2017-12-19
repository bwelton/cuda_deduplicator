#include "SynchTool.h"
std::shared_ptr<SynchTool> Worker;
int exited = 0;
thread_local pid_t my_thread_id = -1; 
thread_local int my_process_id = -1;


SynchTool::SynchTool(std::vector<std::string> & cmd_list) {
	exited = 0;
	_sync_log.reset(new LogInfo(fopen("synch_log.out", "w")));
}

SynchTool::~SynchTool() {
	exited = 1;
	_sync_log.get()->Flush();
	_sync_log.reset();
}


void SynchTool::SetThreadLocals() {
	if (my_thread_id == -1) 
		my_thread_id = (pid_t) syscall(__NR_gettid);
	if (my_process_id == -1)
		my_process_id = (int) getpid();	
}


PluginReturn SynchTool::Precall(std::shared_ptr<Parameters> params) {
	// MemoryTransfer * mem = params.get()->GetMemtrans();
	// if (mem->IsTransfer() == false)
	// 	return NO_ACTION;
	// mem->PreTransfer();
	// //std::cerr << "[TRANSFER-TIMELINE] - Captured transfer: " << params.get()->GetName() << std::endl;
	return NO_ACTION;
}

PluginReturn SynchTool::Postcall(std::shared_ptr<Parameters> params) {
	SetThreadLocals();
	// MemoryTransfer * mem = params.get()->GetMemtrans();	
	// if (mem->IsTransfer() == false)
	// 	return NO_ACTION;
	// mem->PostTransfer();
	// WriteLog(params);
	return NO_ACTION;
}

extern "C"{

void init(std::vector<std::string> & cmd_list) {
	PLUG_BUILD_FACTORY(cmd_list)
}

PluginReturn Precall(std::shared_ptr<Parameters> params){
	if (exited == 1)
		return NO_ACTION;
	return PLUG_FACTORY_PTR->Precall(params);
}

PluginReturn Postcall(std::shared_ptr<Parameters> params) {
	if (exited == 1)
		return NO_ACTION;
	return PLUG_FACTORY_PTR->Postcall(params);
}

}