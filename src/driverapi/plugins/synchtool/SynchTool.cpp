#include "SynchTool.h"
int exited = 0;
std::shared_ptr<SynchTool> Worker;
LoadStoreDriverPtr _LoadStoreDriver;
CheckAccessesPtr _dataAccessManager;
FILE * _temporaryFiles;
extern "C" {


	void INIT_SYNC_COMMON() {
		if (_dataAccessManager.get() != NULL)
			return;
		_dataAccessManager.reset(new CheckAccesses());
		_LoadStoreDriver.reset(new LoadStoreDriver(_dataAccessManager));
		//_temporaryFiles = fopen("TemporaryOutput.txt","w");
	}

	void  __attribute__ ((noinline)) RECORD_FUNCTION_ENTRY(uint64_t id) {
		INIT_SYNC_COMMON();
		//assert(1 == 0);
		// fprintf(_temporaryFiles,"[SynchTool] Captured function entry - %llu\n", id);
		// fflush(_temporaryFiles);
		//std::cerr << "[SynchTool] Captured function entry - " << id << std::endl;
		//_LoadStoreDriver->PushStack(id);

	}
	void  __attribute__ ((noinline)) RECORD_FUNCTION_EXIT(uint64_t id) {
		INIT_SYNC_COMMON();
		//assert(1==0);
		// fprintf(_temporaryFiles,"[SynchTool] Captured function exit - %llu\n", id);
		// fflush(_temporaryFiles);
		//std::cerr << "[SynchTool] Captured function exit - " << id << std::endl;
		//_LoadStoreDriver->PopStack(id);
	}

	void SYNC_CAPTURE_SYNC_CALL() {
		INIT_SYNC_COMMON();
		std::cerr << "[SynchTool] Captured Synchronization call" << std::endl;
		_LoadStoreDriver->SyncCalled();
	}
	void SYNC_RECORD_MEM_ACCESS(uint64_t addr, uint64_t id) {
		INIT_SYNC_COMMON();
		//assert(1==0);
//		fprintf(_temporaryFiles,"[SynchTool] Captured memory access - %llu, %llu\n", addr, id);
//		fflush(_temporaryFiles);
		//std::cerr << "[SynchTool] Captured memory access at " << id << " with mem location " << std::hex << addr << std::dec << std::endl;
		_LoadStoreDriver->RecordAccess(id, addr);
	}
}

SynchTool::SynchTool(std::vector<std::string> & cmd_list) {
	INIT_SYNC_COMMON();
	_cmd_list = cmd_list;
	exited = 0;
	_sync_log.reset(new LogInfo(fopen("synch_log.out", "w")));
}

SynchTool::~SynchTool() {
	exited = 1;
}


void SynchTool::UnifiedAllocation(std::shared_ptr<Parameters> params) {
	// // PT_cuMemAllocManaged CUdeviceptr ** ,size_t* ,unsigned int*
	// std::tuple<PT_cuMemAllocManaged> pvalues = GetParams<PT_cuMemAllocManaged>(params);
	// MemoryRange tmp;
	// tmp.begin = (uint64_t)(std::get<0>(pvalues)[0]);
	// tmp.size = (uint64_t)(std::get<1>(pvalues)[0]);
	// tmp.end = tmp.begin + tmp.size;
	// tmp.transferID = params.get()->GetInstID();
	// tmp.unifiedMemory = 1;
	// _ranges[tmp.begin] = tmp;
}

void SynchTool::GetLiveTransfer(std::shared_ptr<Parameters> params) {
	MemoryTransfer * mem = params.get()->GetMemtrans();
	uint64_t baseAddr = mem->GetCPUAddress();
	int stream = mem->GetStream();
	if (baseAddr == 0){
		// This is a DtoD call that we dont really care or handle. 
		return;
	}
	
	MemoryRange tmp;
	tmp.begin =  baseAddr;
	tmp.size =  mem->GetSize();
	tmp.end = baseAddr + tmp.size;
	tmp.transferID = params.get()->GetInstID();
	tmp.unifiedMemory = 0;
	tmp.stream = stream;
	_dataAccessManager->AddMemoryTransfer(tmp);

#ifdef SYNCH_DEBUG
	std::stringstream ss;
	ss << "[SynchTool] Adding Memory Transfer - " << params.get()->GetName() << " with the following info\n" 
	   << "\tCPU Starting Address = 0x" << std::hex << tmp.begin << std::dec 
	   << "\n\tTransfer Size = " << tmp.size 
	   << "\n\tStream = " << tmp.stream;
	_sync_log.get()->Write(ss.str());
#endif
}

PluginReturn SynchTool::Precall(std::shared_ptr<Parameters> params) {
	Parameters * p = params.get();
	// If the call is not a synchronization
	if (ID_InternalSynchronization != p->GetID()){
		MemoryTransfer * mem = p->GetMemtrans();
		if (mem->IsTransfer() == true){
			// Disable hash checking for performance.  
			mem->SetHashGeneration(false);
			mem->PreTransfer();
			GetLiveTransfer(params);
		} else if (p->GetID() == ID_cuMemAllocManaged){
			// This is a unified memory address allocation, for now
			// we assume that these are always live
		}
	}

	return NO_ACTION;
}

PluginReturn SynchTool::Postcall(std::shared_ptr<Parameters> params) {

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