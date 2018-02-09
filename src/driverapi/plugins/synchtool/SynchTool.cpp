#include "SynchTool.h"
#include "HelperFunctions.h"
#include <stdlib.h>

std::shared_ptr<SynchTool> Worker;
thread_local std::shared_ptr<Parameters> prevCall;
int exited = 0;
thread_local pid_t my_thread_id = -1; 
thread_local int my_process_id = -1;

extern "C" {
	__attribute__ ((noinline)) void SYNCH_SIGNAL_DYNINST(void * memoryRanges, size_t bsize) {
		// Do nothing here, this just delivers a pointer to dyninst to do its magic
	}

	__attribute__ ((noinline)) void SYNCH_FIRST_FAULT() {

	}

	static void sync_mem_handler(int sig, siginfo_t *si, void *unused)
	{
		//PLUG_BUILD_FACTORY(std::vector<std::string>())
		PLUG_FACTORY_PTR->UnprotectMemory();
		SYNCH_FIRST_FAULT();
	}

	void SYNC_RECORD_MEM_ACCESS(uint64_t addr, uint64_t progCounter) {
		std::cerr << "Address: " << std::hex << addr << std::dec << " read at location: " << std::hex 
		          << progCounter << std::dec << std::endl;
	}
}

SynchTool::SynchTool(std::vector<std::string> & cmd_list) {
	_cmd_list = cmd_list;
	exited = 0;
	_sync_log.reset(new LogInfo(fopen("synch_log.out", "w")));
}

SynchTool::~SynchTool() {
	exited = 1;
	FILE * fdes = fopen("synchronous_calls.txt","w");
	for (auto i : _callsContainingSynch)
		fprintf(fdes, "%s\n", _cmd_list[(int)i].c_str());
	fclose(fdes);
	_sync_log.get()->Flush();
	_sync_log.reset();
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

	if (_ranges.find(tmp.begin) != _ranges.end()){
		std::cerr << "[SynchTool] Transfer with same CPU starting address, Potential Duplicate Transfer?" << std::endl;
	} else {
		_ranges[tmp.begin] = tmp;
	}
#ifdef SYNCH_DEBUG
	std::stringstream ss;
	ss << "[SynchTool] Adding Memory Transfer - " << params.get()->GetName() << " with the following info\n" 
	   << "\tCPU Starting Address = 0x" << std::hex << tmp.begin << std::dec 
	   << "\n\tTransfer Size = " << tmp.size 
	   << "\n\tStream = " << tmp.stream;
	_sync_log.get()->Write(ss.str());
#endif
}

void SynchTool::MemoryFree(std::shared_ptr<Parameters> params) {
	// std::tuple<PT_cuMemFree> pvalues = GetParams<PT_cuMemFree>(params);
	// uint64_t addr = (uint64_t)(std::get<0>(pvalues)[0]);
	// if (_ranges.find(addr) != _ranges.end())
	// 	_ranges.erase(addr);
}

void SynchTool::SetThreadLocals() {
	if (my_thread_id == -1) 
		my_thread_id = (pid_t) syscall(__NR_gettid);
	if (my_process_id == -1)
		my_process_id = (int) getpid();	
}

void SynchTool::MemProtectAddrs() {
 //    struct sigaction sa;
 //    sa.sa_flags = SA_SIGINFO;
 //    sigemptyset(&sa.sa_mask);
 //    sa.sa_sigaction = sync_mem_handler;
 //    if(sigaction(SIGSEGV, &sa, NULL) == -1) 
 //    	std::cerr << "[SYNCH TOOL] - Could not set signal handler" << std::endl;

	// for (auto i : _ranges) {
	// 	uint64_t addr = i.first;
	// 	uint64_t size = i.second.size;
	// 	uint64_t pageAligned = (size_t)addr + (size_t)addr % 4096;
	// 	size = size + ((size_t)addr % 4096);
	// 	_protectedMem[pageAligned] = size;
	// 	if (mprotect((void*)pageAligned, size, PROT_NONE) == -1) 
	// 		std::cerr << "[SYNCH TOOL] Could not set signal handler on location: " << std::hex << pageAligned << std::dec << std::endl;
	// }
}

void SynchTool::UnprotectMemory() {
	// for (auto i : _protectedMem) {
	// 	mprotect((void*)i.first, i.second, PROT_READ | PROT_WRITE | PROT_EXEC);
	// }
	// _protectedMem.clear();
}

uint64_t * SynchTool::SeralizeMemRanges(size_t & size) {
	uint64_t * mem = (uint64_t*)malloc(_ranges.size() * 6 * sizeof(uint64_t));
	size_t pos = 0;
	for (auto i : _ranges) {
		mem[pos] = i.second.begin;
		mem[pos + 1] = i.second.end;
		mem[pos + 2] = i.second.size;
		mem[pos + 3] = i.second.transferID;
		mem[pos + 4] = i.second.unifiedMemory;
		mem[pos + 5] = i.second.stream;
		pos += 6;
	}
	size = _ranges.size() * 6 * sizeof(uint64_t);
	return mem;
}

void SynchTool::ClearExisting(uint64_t stream) {
	std::vector<uint64_t> memAddrs;
	for (auto & i : _ranges) {
		if (stream == 0){
			if (i.second.unifiedMemory == 0) {
				memAddrs.push_back(i.first);
			}
		} else {
			if (i.second.unifiedMemory == 0 && i.second.stream == int(stream)) {
				memAddrs.push_back(i.first);
			}
		}
	}
	for (auto i : memAddrs) {
		_ranges.erase(i);
	}
}

void SynchTool::SignalToParent(uint64_t stream) {
	size_t size;
	uint64_t * mem = SeralizeMemRanges(size);
	SYNCH_SIGNAL_DYNINST(mem, size);
	free(mem);
	//MemProtectAddrs();
	ClearExisting(stream);
}


PluginReturn SynchTool::Precall(std::shared_ptr<Parameters> params) {
	Parameters * p = params.get();
	// If the call is not a synchronization
	if (ID_InternalSynchronization != p->GetID()){
		// Stash its value in TLS
		prevCall = params;
		// If this is a memory transfer, we must store its information.
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
	} else {
		// This is a synchronization, Signal to Dyninst to begin load store instrimentation. 
		uint64_t stream = 0;
		if (prevCall.get() != NULL) {
			if (prevCall.get()->GetID() == ID_cuStreamSynchronize) {
				std::tuple<PT_cuStreamSynchronize> pvalues = GetParams<PT_cuStreamSynchronize>(prevCall);
				stream = uint64_t(std::get<0>(pvalues)[0]);
			} else {
				MemoryTransfer * mem = prevCall.get()->GetMemtrans();
				if (mem->IsTransfer() == true)
					stream = uint64_t(mem->GetStream());
			}
			// Record calls which performed synchronizations.
			_callsContainingSynch.insert(prevCall.get()->GetID());
		}
		#ifdef SYNCH_DEBUG
		std::stringstream ss;
		ss << "[SynchTool] Captured Synchronization";
		_sync_log.get()->Write(ss.str());
		#endif
		SignalToParent(stream);
		//prevCall.reset();
	}

	return NO_ACTION;
}

PluginReturn SynchTool::Postcall(std::shared_ptr<Parameters> params) {
	if (params.get()->GetID() != ID_cuStreamSynchronize)
		prevCall.reset();
	// SetThreadLocals();
	// Parameters * p = params.get();
	// CallID ident = p->GetID();
	// if (ident != ID_InternalSynchronization){
	// 	GetLiveTransfer(params);
	// 	if (ident == ID_cuMemHostAlloc) 
	// 		UnifiedAllocation(params);
	// 	else if (ident == ID_cuMemFree) 
	// 		MemoryFree(params);
	// } else {
	// 	// Synchronization is complete, signal to 
	// 	SignalToParent();	
	// }
	// return NO_ACTION;
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