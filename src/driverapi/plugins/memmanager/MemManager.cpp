#include <iostream>
#include <fstream> 
#include <memory>   
#include <string>
#include <stdio.h> 
#include <map>
#include <sstream> 
#include <vector>
// CUDA include
#include <cuda_runtime_api.h>
#include <cuda.h>
#include <atomic> 

std::atomic<bool> DIOGENES_Atomic_Malloc(false);

//#define MEMMANAGE_DEBUG 1
class MemStats {
public:
	MemStats(std::string name);
	~MemStats();
	void AllocatedMemory(uint64_t size);
	void FreedMemory(uint64_t size);
	void UsedCache(size_t size);
	void TransferAddrKnown(bool known);
private:
	std::map<uint64_t, uint64_t> _sizes;
	uint64_t _current;
	uint64_t _max;
	uint64_t _allocatedCount;
	uint64_t _freedCount;
	uint64_t _knownTransferAddrs;
	uint64_t _unknownTransferAddrs;
	std::string _type;
	uint64_t _cacheHits;
};


class MemManage {
public:
	MemManage();
	cudaError_t GPUAllocate(void ** mem, uint64_t size);
	cudaError_t GPUFree(void * mem);
	void * CPUAllocate(uint64_t size);
	void CheckDestTransMem(void * mem);
	void CPUFree(void * mem);
private:
	std::map<uint64_t, uint64_t> _gpuMem;
	std::map<uint64_t, std::vector<void *> > _gpuMemSize;
	std::map<uint64_t, uint64_t> _cpuMem;
	std::shared_ptr<MemStats> _cpuStats;
	std::shared_ptr<MemStats> _gpuStats;
	//
};

MemStats::MemStats(std::string name) :  _current(0), _max(0), _allocatedCount(0), _freedCount(0), 
										_type(name), _cacheHits(0), _knownTransferAddrs(0),
										_unknownTransferAddrs(0) {}

MemStats::~MemStats() {
	std::stringstream ss;
	ss << "==============================================================" << std::endl;
	ss << "Allocator Type: " << _type << std::endl;
	ss << "Alloc Count: " << _allocatedCount << " Free Count: " << _freedCount << std::endl;
	ss << "Max Allocated: " << _max << std::endl;
	ss << "Known Transfer Addr: " << _knownTransferAddrs << " Unknown Trans Addr: " << _unknownTransferAddrs << std::endl;
	ss << "Cache Hits: " << _cacheHits << std::endl;
	ss << "Sizes Allocated... " << std::endl;

	for (auto i : _sizes) {
		ss << i.first << " " << i.second << std::endl;
	}
	std::cerr << ss.str();
}

void MemStats::UsedCache(size_t size) {
#ifdef MEMMANAGE_DEBUG
	std::cout << "[MemStats::UsedCache] Cached memory range used for alloc of size - " << size << std::endl;
#endif
	_cacheHits++;
}


void MemStats::TransferAddrKnown(bool known) {
	if (known)
		_knownTransferAddrs++;
	else
		_unknownTransferAddrs++;

}
void MemStats::AllocatedMemory(uint64_t size) {
#ifdef MEMMANAGE_DEBUG
	std::cout << "[MemStats::AllocatedMemory] Allocating Memory of size - " << size << std::endl;
#endif
	if (_sizes.find(size) == _sizes.end())
		_sizes[size] = 1;
	else
		_sizes[size] += 1;
	_current += size;
	if (_current > _max)
		_max = _current;
	_allocatedCount++;
}

void MemStats::FreedMemory(uint64_t size) {
#ifdef MEMMANAGE_DEBUG
	std::cout << "[MemStats::FreedMemory] Freeing Memory of size - " << size << std::endl;
#endif
	_freedCount += 1;
	if (_current > size) 
		_current -= size;
	else
		std::cerr << "[MemStats::FreedMemory] We have a free from a memory location we don't know" << std::endl;
}


MemManage::MemManage() :  _cpuStats(new MemStats(std::string("CPU"))), _gpuStats(new MemStats(std::string("GPU"))) {

}

bool FindFreeMemory(std::map<uint64_t, std::vector<void *> >  & memRegions, void ** mem, uint64_t size) {
	if(memRegions.find(size) != memRegions.end())
		if (memRegions[size].size() > 0){
			*mem = (memRegions[size].back());
			memRegions[size].pop_back();
			return true;
		}

	return false;
}

cudaError_t MemManage::GPUAllocate (void** mem, uint64_t size) {
	#ifdef MEMMANAGE_DEBUG
		std::cout << "[MemManage::GPUAllocate] Entering GPU allocator to get size of " << size << std::endl;
	#endif
	if (FindFreeMemory(_gpuMemSize, mem, size)) {
		#ifdef MEMMANAGE_DEBUG
			std::cout << "[MemManage::GPUAllocate] Using a cached address " << std::endl;
		#endif
		_gpuStats->UsedCache(size);
		return cudaSuccess;
	}
	#ifdef MEMMANAGE_DEBUG
		std::cout << "[MemManage::GPUAllocate] Allocating a new GPU memory address " << std::endl;
	#endif	
	// Allocate if we must...
	cudaError_t tmp = cudaMalloc(mem, size);
	if (tmp == cudaSuccess){
		_gpuStats->AllocatedMemory(size);
		if (_gpuMemSize.find(size) == _gpuMemSize.end())
			_gpuMemSize[size] = std::vector<void *>();
		_gpuMem[*((uint64_t*)mem)] = size;
	}
	return tmp;
}

cudaError_t MemManage::GPUFree(void * mem){
	if (_gpuMem.find((uint64_t)mem) != _gpuMem.end()) {
		_gpuMemSize[_gpuMem[(uint64_t)mem]].push_back(mem);
		return cudaSuccess;
	} 
	// Free the memory, we have no idea what this is.
	
	return cudaFree(mem);
}

void * MemManage::CPUAllocate(uint64_t size) {
	void * tmp = malloc(size);
	_cpuMem[(uint64_t) tmp] = size;
	_cpuStats->AllocatedMemory(size);
	return tmp;
}

void MemManage::CPUFree(void * mem) {
	if (_cpuMem.find((uint64_t) mem) != _cpuMem.end()) {
		_cpuStats->FreedMemory(_cpuMem[(uint64_t)mem]);
		_cpuMem.erase((uint64_t)mem);
	} else {
		std::cerr << "[MemManage::CPUFree] We have no idea what this memory address is... " << std::hex << mem << std::endl;
	}
	free(mem);
}

uint64_t Diogenes_FindMemKey(std::map<uint64_t,uint64_t> & m, uint64_t addr) {
	std::map<uint64_t, uint64_t>::iterator lb = m.lower_bound(addr);
	if (lb == m.end())
		return 0;
	if (lb->first + lb->second >= addr)
		return lb->first;
	return 0;
}

void MemManage::CheckDestTransMem(void * mem) {
	uint64_t key = Diogenes_FindMemKey(_cpuMem, (uint64_t) mem);
	if (key == 0)
		_cpuStats->TransferAddrKnown(false);
	else 
		_cpuStats->TransferAddrKnown(true);
		//std::cerr << "[MemManage::CheckDestTransMem] We do not know about this CPU address in memory transfer - " << std::hex << (uint64_t) mem << std::endl;
}

std::shared_ptr<MemManage> DIOGENES_MEMORY_MANAGER;

#define PLUG_BUILD_FACTORY(param) \
	if (DIOGENES_MEMORY_MANAGER.get() == NULL) { \
		bool original = DIOGENES_Atomic_Malloc.exchange(true); \
		DIOGENES_MEMORY_MANAGER.reset(new MemManage(param)); \
		DIOGENES_Atomic_Malloc.exchange(original); \
	} 

#define PLUG_FACTORY_PTR DIOGENES_MEMORY_MANAGER.get()


extern "C" {
cudaError_t  DIOGENES_cudaFreeWrapper(void * mem) {
	PLUG_BUILD_FACTORY()
	return PLUG_FACTORY_PTR->GPUFree(mem);
	// //fprintf(stderr,"I am freeing an address of %p \n", mem);
	// return cudaFree(mem);
}

cudaError_t DIOGENES_cudaMallocWrapper(void ** mem, size_t size) {
	PLUG_BUILD_FACTORY()

	return PLUG_FACTORY_PTR->GPUAllocate(mem, uint64_t(size));

	// cudaError_t tmp = cudaMalloc(mem, size);
	// if (tmp == cudaSuccess)
	// 	std::cerr << "I alloced an address at " << std::hex << *((uint64_t**)mem)  <<  " of size " << size << std::endl;
	// return tmp;
}

cudaError_t DIOGENES_cudaMemcpyAsyncWrapper(void * dst, const void * src, size_t size, cudaMemcpyKind kind, cudaStream_t stream) {
	PLUG_BUILD_FACTORY()
	if (kind == cudaMemcpyDeviceToHost)
		PLUG_FACTORY_PTR->CheckDestTransMem(dst);
	//std::cerr << "Initiating a transfer between  " << std::hex << dst <<  " and " << std::hex << src << " of size " << size << std::endl;
	return cudaMemcpyAsync(dst, src, size, kind, stream);
}

void * DIOGENES_MALLOCWrapper(size_t size) {
	void * tmp = NULL;
	bool setVal = false;
	if(DIOGENES_Atomic_Malloc.compare_exchange_weak(setVal, true)) {
		PLUG_BUILD_FACTORY()	
		tmp = PLUG_FACTORY_PTR->CPUAllocate(uint64_t(size));
		DIOGENES_Atomic_Malloc.exchange(false);
	} else {
		tmp = malloc(size);
	} 
	//std::cerr << "Malloced data at  " << std::hex << tmp << " of size " << size << std::endl;
	return tmp;
}

void DIOGENES_FREEWrapper(void * mem) {
	bool setVal = false;
	if(DIOGENES_Atomic_Malloc.compare_exchange_weak(setVal, true)) {
		PLUG_BUILD_FACTORY()
		PLUG_FACTORY_PTR->CPUFree(mem);
		DIOGENES_Atomic_Malloc.exchange(false);
	} else {
		free(mem);
	}
}
}

