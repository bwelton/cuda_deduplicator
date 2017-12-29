#include "SynchTool.h"
#include "HelperFunctions.h"
#include <stdlib.h>

std::shared_ptr<SynchTool> Worker;
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


}

SynchTool::SynchTool(std::vector<std::string> & cmd_list) {
	exited = 0;
	_sync_log.reset(new LogInfo(fopen("synch_log.out", "w")));
}

SynchTool::~SynchTool() {
	exited = 1;
	_sync_log.get()->Flush();
	_sync_log.reset();
}


void SynchTool::UnifiedAllocation(std::shared_ptr<Parameters> params) {
	// PT_cuMemAllocManaged CUdeviceptr ** ,size_t* ,unsigned int*
	std::tuple<PT_cuMemAllocManaged> pvalues = GetParams<PT_cuMemAllocManaged>(params);
	MemoryRange tmp;
	tmp.begin = (uint64_t)(std::get<0>(pvalues)[0]);
	tmp.size = (uint64_t)(std::get<1>(pvalues)[0]);
	tmp.end = tmp.begin + tmp.size;
	tmp.transferID = params.get()->GetInstID();
	tmp.unifiedMemory = 1;
	_ranges[tmp.begin] = tmp;
}

void SynchTool::GetLiveTransfer(std::shared_ptr<Parameters> params) {
	MemoryTransfer * mem = params.get()->GetMemtrans();
	uint64_t baseAddr = mem->GetCPUAddress();
	if (baseAddr == 0)
		return;

	MemoryRange tmp;
	tmp.begin =  baseAddr;
	tmp.size =  mem->GetSize();
	tmp.end = baseAddr + tmp.size;
	tmp.transferID = params.get()->GetInstID();
	tmp.unifiedMemory = 0;
	_ranges[tmp.begin] = tmp;	
}

void SynchTool::MemoryFree(std::shared_ptr<Parameters> params) {
	std::tuple<PT_cuMemFree> pvalues = GetParams<PT_cuMemFree>(params);
	uint64_t addr = (uint64_t)(std::get<0>(pvalues)[0]);
	if (_ranges.find(addr) != _ranges.end())
		_ranges.erase(addr);
}

void SynchTool::SetThreadLocals() {
	if (my_thread_id == -1) 
		my_thread_id = (pid_t) syscall(__NR_gettid);
	if (my_process_id == -1)
		my_process_id = (int) getpid();	
}

void SynchTool::MemProtectAddrs() {
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = sync_mem_handler;
    if(sigaction(SIGSEGV, &sa, NULL) == -1) 
    	std::cerr << "[SYNCH TOOL] - Could not set signal handler" << std::endl;

	for (auto i : _ranges) {
		uint64_t addr = i.first;
		uint64_t size = i.second.size;
		uint64_t pageAligned = (size_t)addr + (size_t)addr % 4096;
		size = size + ((size_t)addr % 4096);
		_protectedMem[pageAligned] = size;
		if (mprotect((void*)pageAligned, size, PROT_NONE) == -1) 
			std::cerr << "[SYNCH TOOL] Could not set signal handler on location: " << std::hex << pageAligned << std::dec << std::endl;
	}
}

void SynchTool::UnprotectMemory() {
	for (auto i : _protectedMem) {
		mprotect((void*)i.first, i.second, PROT_READ | PROT_WRITE | PROT_EXEC);
	}
	_protectedMem.clear();
}

uint64_t * SynchTool::SeralizeMemRanges(size_t & size) {
	uint64_t * mem;
	posix_memalign((void **)&mem, 4096, _ranges.size() * 5 * sizeof(uint64_t));
	size_t pos = 0;
	for (auto i : _ranges) {
		mem[pos] = i.second.begin;
		mem[pos + 1] = i.second.end;
		mem[pos + 2] = i.second.size;
		mem[pos + 3] = i.second.transferID;
		mem[pos + 4] = i.second.unifiedMemory;
		pos += 5;
	}
	size = _ranges.size() * 5 * sizeof(uint64_t);
	return mem;
}

void SynchTool::ClearExisting() {
	std::vector<uint64_t> memAddrs;
	for (auto & i : _ranges) {
		if (i.second.unifiedMemory == 0) 
			memAddrs.push_back(i.first);
	}
	for (auto i : memAddrs) {
		_ranges.erase(i);
	}
}

void SynchTool::SignalToParent() {
	size_t size;
	uint64_t * mem = SeralizeMemRanges(size);
	SYNCH_SIGNAL_DYNINST(mem, size);
	free(mem);

	MemProtectAddrs();

	ClearExisting();
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
	Parameters * p = params.get();
	CallID ident = p->GetID();
	if (ident != ID_InternalSynchronization){
		GetLiveTransfer(params);
		if (ident == ID_cuMemHostAlloc) 
			UnifiedAllocation(params);
		else if (ident == ID_cuMemFree) 
			MemoryFree(params);
	} else {
		// Synchronization is complete, signal to 
		
	}



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