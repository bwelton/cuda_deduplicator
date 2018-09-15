#include "SynchTool.h"
volatile int exited = 0;
volatile int inSpecialCase = 0;
std::shared_ptr<SynchTool> Worker;
thread_local LoadStoreDriverPtr _LoadStoreDriver;
thread_local CheckAccessesPtr _dataAccessManager;
FILE * _temporaryFiles;
bool enteredMe = false;
volatile int justChecking = 8;
extern "C" {


static gotcha_wrappee_handle_t memcpyWrapper_handle;
static void * memcpyWrapper(void * dest, void * src, size_t count);
struct gotcha_binding_t funcBinders[] = { {"memcpy",memcpyWrapper,&memcpyWrapper_handle}};


	void INIT_SYNC_COMMON() {
		if(exited == 1)
			return;
		if (_dataAccessManager.get() != NULL)
			return;
		// gotcha_set_priority("cuda/specialcases", 1);
		// int result = gotcha_wrap(gotfuncs, 1, "cuda/specialcases");
		// assert(result == GOTCHA_SUCCESS);
		_dataAccessManager.reset(new CheckAccesses());
		_LoadStoreDriver.reset(new LoadStoreDriver(_dataAccessManager));
		//_temporaryFiles = fopen("TemporaryOutput.txt","w");
	}
	void * memcpyWrapper(void * dest, void * src, size_t count) {
		INIT_SYNC_COMMON();
		inSpecialCase = 1;
	}

	void RECORD_FUNCTION_ENTRY(uint64_t id) {
		if(exited == 1)
			return;
		// if (justChecking == 8)
		// 	justChecking = 1;
		// else 
		// 	justChecking = 1002321;
		INIT_SYNC_COMMON();
		// //assert(1 == 0);
		// // fprintf(_temporaryFiles,"[SynchTool] Captured function entry - %llu\n", id);
		// // fflush(_temporaryFiles);
		// //std::cerr << "[SynchTool] Captured function entry - " << id << std::endl;
		_LoadStoreDriver->PushStack(id);
	}
	void RECORD_FUNCTION_EXIT(uint64_t id) {
		if(exited == 1)
			return;
		// if (justChecking == 8)
		// 	justChecking = 1;
		// else 
		// 	justChecking = 1002321;
		INIT_SYNC_COMMON();
		// //assert(1==0);
		// // fprintf(_temporaryFiles,"[SynchTool] Captured function exit - %llu\n", id);
		// // fflush(_temporaryFiles);
		// //std::cerr << "[SynchTool] Captured function exit - " << id << std::endl;
		_LoadStoreDriver->PopStack(id);
	}

	void SYNC_CAPTURE_SYNC_CALL() {
		if(exited == 1)
			return;
		// if (justChecking == 8)
		// 	justChecking = 1;
		// else 
		// 	justChecking = 1002321;
	    INIT_SYNC_COMMON();
		 //std::cerr << "[SynchTool] Captured Synchronization call" << std::endl;
		_LoadStoreDriver->SyncCalled();
	}
	void SYNC_RECORD_MEM_ACCESS(uint64_t addr, uint64_t id) {
		if(exited == 1 || inSpecialCase == 1)
			return;
		//std::cerr << "Inside of address " << std::hex << addr<< std::endl;
		// if (justChecking == 8)
		// 	justChecking = 1;
		// else 
		// 	justChecking = 1002321;
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
	_LoadStoreDriver.reset();
	_dataAccessManager.reset();
}


void SynchTool::UnifiedAllocation(std::shared_ptr<Parameters> params) {
	// // PT_cuMemAllocManaged CUdeviceptr ** ,size_t* ,unsigned int*
	std::tuple<PT_cuMemAllocManaged> pvalues = GetParams<PT_cuMemAllocManaged>(params);
	MemoryRange tmp;
	tmp.begin = *((uint64_t *)(std::get<0>(pvalues)[0]));
	tmp.size = (uint64_t)(std::get<1>(pvalues)[0]);
	tmp.end = tmp.begin + tmp.size;
	tmp.transferID = params.get()->GetInstID();
	tmp.unifiedMemory = 1;
	tmp.stream = 0;
	std::stringstream ss;
	ss << "[SynchTool] Adding Unified Memory Location - " << params.get()->GetName() << " with the following info\n" 
	   << "\tCPU Starting Address = 0x" << std::hex << tmp.begin << std::dec 
	   << "\n\tAllocation Size = " << tmp.size 
	   << "\n\tStream = " << tmp.stream;
	std::cerr << ss.str() << std::endl; 
	_dataAccessManager->AddUnifiedMemRange(tmp);

	//_ranges[tmp.begin] = tmp;
}

void SynchTool::FreeMemoryAllocation(std::shared_ptr<Parameters> params) {
	std::tuple<PT_cuMemFree> pvalues = GetParams<PT_cuMemFree>(params);
	MemoryRange tmp;
	tmp.begin = (uint64_t)(std::get<0>(pvalues)[0]);
	tmp.end = 0;
	tmp.transferID = params.get()->GetInstID();
	tmp.unifiedMemory = 1;
	tmp.stream = 0;
	_dataAccessManager->RemoveUnifiedMemoryRange(tmp);
	std::stringstream ss;
	ss << "[SynchTool] cudaMemoryFree at call - " << params.get()->GetName() << " with the following info\n" 
	   << "\tCPU Starting Address = 0x" << std::hex << tmp.begin << std::dec;
	std::cerr << ss.str() << std::endl; 
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

//#ifdef SYNCH_DEBUG
	std::stringstream ss;
	ss << "[SynchTool] Adding Memory Transfer - " << params.get()->GetName() << " with the following info\n" 
	   << "\tCPU Starting Address = 0x" << std::hex << tmp.begin << std::dec 
	   << "\n\tTransfer Size = " << tmp.size 
	   << "\n\tStream = " << tmp.stream;
	std::cerr << ss.str() << std::endl;
	//_sync_log.get()->Write(ss.str());
//#endif
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
			// // Cuda Malloc Mana
			// std::cerr << "[SynchTool::Precall] I am an idiot for not filling this in...." << std::endl;
			// UnifiedAllocation(params);
			// This is a unified memory address allocation, for now
			// we assume that these are always live
		} else if (p->GetID() == ID_cuMemFree){
			FreeMemoryAllocation(params);
		}		
	}

	return NO_ACTION;
}

PluginReturn SynchTool::Postcall(std::shared_ptr<Parameters> params) {
	Parameters * p = params.get();
	// If the call is not a synchronization
	if (ID_InternalSynchronization != p->GetID()){
		if (p->GetID() == ID_cuMemAllocManaged){
			UnifiedAllocation(params);	
		}
	}
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