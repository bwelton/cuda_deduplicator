#include <iostream>
#include <fstream> 
#include <memory>   
#include <string>
#include <stdio.h> 
#include <map>
#include <sstream> 
#include <vector>
#include <atomic> 
#include <cstring>
#include <list>
#include <deque>
#include <cuda_runtime_api.h>
#include <cuda.h>

#include "MemRecDataFile.h"

extern "C" {
	volatile int64_t DIOGENES_CTX_ID = -1;
}

struct MemAddress {
	uint64_t addr;
	int64_t loc;
	uint64_t size;
};

class MemKeeper {
public:
	MemKeeper() {
		allocCount = 10000;
		for (int i = 0; i < 10000; i++)
			_allocedAddresses.push_back(new MemAddress());
	};

	~MemKeeper() {
		for(auto i : _allocedAddresses)
			delete i;
		for(auto i : _addressMap)
			delete i.second;
		_addressMap.clear();
		_allocedAddresses.clear();
	}

	MemAddress * ReturnEmpty() {
		MemAddress * ret = NULL;
		if (_allocedAddresses.size() > 0) {
			ret = _allocedAddresses.front();
			_allocedAddresses.pop_front();
		} else {
			allocCount++;
			if (allocCount % 10000 == 0)
				std::cerr << "[MemAddress::ReturnEmpty] Alloced - " << allocCount <<  " MemAddress structs" << std::endl;
			ret = new MemAddress();
		}
		return ret;
	}

	MemAddress * Get(uint64_t addr) {
		if (_addressMap.find(addr) == _addressMap.end())
			return NULL;
		return _addressMap[addr];
	};

	MemAddress * GetLowerBound(uint64_t addr)  {
		auto lb = _addressMap.lower_bound(addr);
		if (lb == _addressMap.end())
			return NULL;
		return lb->second;
	}
	void AddOneSeen(int64_t id, std::map<int64_t, int64_t> & seenMap) {
		auto it = seenMap.find(id);
		if (it == seenMap.end()) {
			seenMap[id] = 1;
		} else {
			(it->second)++;
		}
	};


	void SubNumSeen(int64_t id, std::map<int64_t, int64_t> & seenMap, int64_t count) {
		auto it = seenMap.find(id);
		if (it != seenMap.end()) {
			it->second -= count;
			if (it->second <= 0)
				seenMap.delete(it);
		}
	};
	MemAddress * Set(uint64_t addr, uint64_t size, int64_t loc) {
		MemAddress * n;
		if (_addressMap.find(addr) != _addressMap.end()) {
			n = _addressMap[addr];
		} else {
			n = ReturnEmpty();
		}
		n->addr = addr;
		n->loc = loc;
		n->size = size;
		_addressMap[addr] = n;
		AddOneSeen(loc, _allocSeen);
		return n;
	};

	std::map<uint64_t, MemAddress*> * GetAddressMapPtr() {
		return &_addressMap;
	}
	void Delete(int64_t loc, uint64_t addr) {
		if (_addressMap.find(addr) != _addressMap.end()) {
			_allocedAddresses.push_back(_addressMap[addr]);
			_addressMap.erase(addr);
		}
		AddOneSeen(loc, _freeSeen);
	};

	uint64_t allocCount;
	std::map<int64_t, int64_t> _allocSeen;
	std::map<int64_t, int64_t> _freeSeen;
	std::map<uint64_t, MemAddress*> _addressMap;
	std::deque<MemAddress *> _allocedAddresses;
};


class OutputWriter{
public:
	OutputWriter(std::shared_ptr<MemKeeper> cmem, std::shared_ptr<MemKeeper> gmem) : _cpuLocalMem(cmem), _gpuLocalMem(gmem) {};
	void RecordGPUMallocPair(MemAddress * addr, int64_t freeLoc) {
		if (_GPUMallocRecords.find(addr->loc) == _GPUMallocRecords.end())
			_GPUMallocRecords[addr->loc] = std::map<int64_t,CUMallocTracker*>();
		if (_GPUMallocRecords[addr->loc].find(freeLoc) != _GPUMallocRecords[addr->loc].end())
			_GPUMallocRecords[addr->loc][freeLoc]->count++;
		else {
			CUMallocTracker * tmp = new CUMallocTracker();
			tmp->allocSite = addr->loc;
			tmp->freeSite = freeLoc;
			tmp->count = 1;
			_GPUMallocRecords[addr->loc][freeLoc] = tmp;
		}
	};

	void RecordCPUMallocPair(MemAddress * addr, int64_t freeLoc) {
		if (_CPUTransRecords.find(addr->loc) == _CPUTransRecords.end())
			_CPUTransRecords[addr->loc] = std::map<int64_t,GLIBMallocTracker*>();
		if (_CPUTransRecords[addr->loc].find(freeLoc) != _CPUTransRecords[addr->loc].end())
			_CPUTransRecords[addr->loc][freeLoc]->count++;
		else {
			GLIBMallocTracker * tmp = new GLIBMallocTracker();
			tmp->allocSite = addr->loc;
			tmp->freeSite = freeLoc;
			tmp->count = 1;
			_CPUTransRecords[addr->loc][freeLoc] = tmp;
		}
	};

	void RecordCopyRecord(MemAddress * addr, int64_t copyLoc) {
		if (_CopyRecords.find(addr->loc) == _CopyRecords.end())
			_CopyRecords[addr->loc] = std::map<int64_t,CUMemTransferTracker*>();
		if (_CopyRecords[addr->loc].find(copyLoc) != _CopyRecords[addr->loc].end())
			_CopyRecords[addr->loc][copyLoc]->count++;
		else {
			CUMemTransferTracker * tmp = new CUMemTransferTracker();
			tmp->allocSite = addr->loc;
			tmp->copyID = copyLoc;
			tmp->count = 1;
			_CopyRecords[addr->loc][copyLoc] = tmp;
		}		
	};
	template <typename T> 
	std::set<int64_t> CheckForUnwrittenEntries(std::shared_ptr<MemKeeper> mem, std::map<int64_t, std::map<int64_t,T>> & m) {
		std::set<int64_t> ret;
		std::map<uint64_t, MemAddress*> * a = mem->GetAddressMapPtr();
		for(auto i : *a) {
			if (m.find(i.second.loc) == m.end()) {
				ret.insert(i.second.loc);
			}
		}
		return ret;
	};

	// template<typename T>
	// void WriteUnknownMallocs(std::set<int64_t>)


	// void WriteUnknownCPUMallocs(std::shared_ptr<MemKeeper> cpuMem) {
	// 	std::set<int64_t> tmp = CheckForUnwrittenEntries<GLIBMallocTracker*>(cpuMem, _CPUTransRecords);

	template<typename T> 
	void WriteMemData(MemRecDataFile & wfile, std::map<int64_t, std::map<int64_t,T*>> & mmap, std::shared_ptr<MemKeeper> mkeep) {
		std::vector<T*> outVec;
		for (auto i : _GPUMallocRecords){
			for (auto x : i.second) {
				outVec.push_back(x.second);
				mkeep->SubNumSeen(i.first,mkeep->_allocSee,x.second->count);
				mkeep->SubNumSeen(i.second,mkeep->_freeSee,x.second->count);
			}
		}
		for (auto i : mkeep->_allocSee) {
			T * tmp = new T();
			tmp->allocSite = i.first;
			tmp->count = i.second;
			tmp->freeSite = -1;
			outVec.push_back(tmp);
		}
		for (auto i : mkeep->_freeSee) {
			T * tmp = new T();
			tmp->freeSite = i.first;
			tmp->count = i.second;
			tmp->allocSite = -1;
			outVec.push_back(tmp);
		}
		wfile.Write<T *>(outVec);
	};

	// };
	~OutputWriter() {
		MemRecDataFile wfile(fopen("DIOGENES_MemRecords.bin","wb"));
		WriteMemData<CUMallocTracker>(wfile, _GPUMallocRecords, _gpuLocalMem);
		WriteMemData<GLIBMallocTracker>(wfile, _CPUTransRecords, _cpuLocalMem);	
		// GPUMallocVec gvec;
		// for (auto i : _GPUMallocRecords)
		// 	for (auto x : i.second)
		// 		gvec.push_back(x.second);
		// wfile.Write<CUMallocTracker*>(gvec);

		// CPUMallocVec cvec;
		// for (auto i : _CPUTransRecords)
		// 	for (auto x : i.second)
		// 		cvec.push_back(x.second);
		// wfile.Write<GLIBMallocTracker*>(cvec);

		MemTransVec mvec;
		for (auto i : _CopyRecords)
			for (auto x : i.second)
				mvec.push_back(x.second);

		wfile.Write<CUMemTransferTracker*>(mvec);
	};
	std::shared_ptr<MemKeeper> _cpuLocalMem;
	std::shared_ptr<MemKeeper> _gpuLocalMem;
	std::map<int64_t, std::map<int64_t,CUMemTransferTracker*>> _CopyRecords;
	std::map<int64_t, std::map<int64_t,GLIBMallocTracker*>> _CPUTransRecords;
	std::map<int64_t, std::map<int64_t,CUMallocTracker*>> _GPUMallocRecords;
};

volatile bool DIOGENES_TEAR_DOWN = false;
class MemTracker {
public:
	MemTracker() {
		_NullAddr = new MemAddress();
		_NullAddr->loc = -1;
		_NullAddr->size = 0;
		_cpuLocalMem.reset(new MemKeeper());
		_gpuLocalMem.reset(new MemKeeper());
		_outWriter.reset(new OutputWriter(_cpuLocalMem, _gpuLocalMem));
	};

	~MemTracker() {
		DIOGENES_TEAR_DOWN = true;
	}
	void CPUMallocData(uint64_t addr, size_t size, int64_t loc) {
		_cpuLocalMem->Set(addr,size, loc);
	};

	void CPUFreeData(uint64_t addr, int64_t loc) {
		MemAddress * cpuAddr = _cpuLocalMem->Get(addr);
		if (cpuAddr != NULL) {
			_outWriter->RecordCPUMallocPair(cpuAddr, loc);
		}
		_cpuLocalMem->Delete(loc,addr);
	};

	void GPUMallocData(uint64_t addr, size_t size, int64_t loc)  {
		_gpuLocalMem->Set(addr,size, loc);
	};
	void GPUFreeData(uint64_t addr, int64_t loc) {
		MemAddress * gpuAddr = _gpuLocalMem->Get(addr);
		if (gpuAddr != NULL) {
			_outWriter->RecordGPUMallocPair(gpuAddr, loc);
		}		
		_gpuLocalMem->Delete(loc,addr);	
	};
 	
	void RecordMemTransfer(uint64_t addr, int64_t loc) {
		MemAddress * cpuAddr = _cpuLocalMem->GetLowerBound(addr);
		if (cpuAddr == NULL) {
			cpuAddr = _NullAddr;
		}
		_outWriter->RecordCopyRecord(cpuAddr, loc);
	}

	MemAddress * _NullAddr;
	std::shared_ptr<OutputWriter> _outWriter;
	std::shared_ptr<MemKeeper> _cpuLocalMem;
	std::shared_ptr<MemKeeper> _gpuLocalMem;
};


// Lock Atomic
std::atomic<bool> DIOGENES_MEM_Atomic_Malloc(false);

inline bool DIOGENES_GetGlobalLock() {
	bool setVal = false;
	return DIOGENES_MEM_Atomic_Malloc.compare_exchange_weak(setVal, true);
}

inline bool DIOGENES_ReleaseGlobalLock() {
	DIOGENES_MEM_Atomic_Malloc.exchange(false);
	return true;
}

std::shared_ptr<MemTracker> DIOGENES_MEMORY_RECORDER;



#define PLUG_BUILD_FACTORY() \
	if (DIOGENES_MEMORY_RECORDER.get() == NULL) { \
		DIOGENES_MEMORY_RECORDER.reset(new MemTracker()); \
	} 

#define PLUG_FACTORY_PTR DIOGENES_MEMORY_RECORDER.get()

int debugPrintCount = 0;

extern "C" {
	void * DIOGENES_REC_MALLOCWrapper(size_t size)  {
		int64_t cache = DIOGENES_CTX_ID;
		if(DIOGENES_GetGlobalLock() && DIOGENES_TEAR_DOWN == false) {
			PLUG_BUILD_FACTORY();
			// if (debugPrintCount % 10000 == 0)
			// 	std::cerr << "[CACHE] Malloc Cache address is - " << cache << std::endl;
			// debugPrintCount++;
			void * ret = malloc(size);
			PLUG_FACTORY_PTR->CPUMallocData((uint64_t)ret, size, cache);
			DIOGENES_ReleaseGlobalLock();
			return ret;
		} else {
			return malloc(size);
		}
	}
	void DIOGENES_REC_FREEWrapper(void * mem) {
		int64_t cache = DIOGENES_CTX_ID;
		if (DIOGENES_GetGlobalLock() && DIOGENES_TEAR_DOWN == false) {
			PLUG_BUILD_FACTORY();
			// if (debugPrintCount % 10000 == 0)
			// 	std::cerr << "[CACHE] Free Cache address is - " << cache << std::endl;
			// debugPrintCount++;
			PLUG_FACTORY_PTR->CPUFreeData((uint64_t)mem, cache);
			DIOGENES_ReleaseGlobalLock();
		}
		free(mem);
	}

	cudaError_t DIOGENES_REC_CudaMalloc(void ** data, size_t size) {
		int64_t cache = DIOGENES_CTX_ID;
		cudaError_t ret = cudaErrorUnknown;
		if (DIOGENES_GetGlobalLock() && DIOGENES_TEAR_DOWN == false) {
			PLUG_BUILD_FACTORY();
			ret = cudaMalloc(data, size);
			PLUG_FACTORY_PTR->GPUMallocData((uint64_t)(*data), size, cache);
			DIOGENES_ReleaseGlobalLock();
		} else {
			ret = cudaMalloc(data, size);
		}
		//assert(1==0);
		return ret;
	}

	cudaError_t DIOGENES_REC_CudaFree(void * data) {
		int64_t cache = DIOGENES_CTX_ID;
		if (DIOGENES_GetGlobalLock() && DIOGENES_TEAR_DOWN == false) {
			PLUG_BUILD_FACTORY();
			PLUG_FACTORY_PTR->GPUFreeData((uint64_t)(data), cache);
			DIOGENES_ReleaseGlobalLock();
		}
		return cudaFree(data);
	}
	cudaError_t DIOGENES_REC_CudaMemcpy(void * dst, const void * src, size_t size, cudaMemcpyKind kind, cudaStream_t stream) {
		int64_t cache = DIOGENES_CTX_ID;
		if (kind == cudaMemcpyDeviceToHost) {
			if (DIOGENES_GetGlobalLock() && DIOGENES_TEAR_DOWN == false) {
				PLUG_BUILD_FACTORY();
				PLUG_FACTORY_PTR->RecordMemTransfer((uint64_t)dst, cache);
				DIOGENES_ReleaseGlobalLock();
			}
		}
		//assert(1==0);
		return cudaMemcpyAsync(dst,src,size,kind,stream);
	}
	// void * DIOGENES_REC_MALLOCWrapper(size_t size)  {
	// 	int64_t cache = DIOGENES_CTX_ID;
	// 	if(DIOGENES_GetGlobalLock()) {
	// 		if ()
	// 	}

	// }

}



// class MemCollector {
// public:
// 	MemCollector::MemCollector() {}

// 	void MemCollector::CaptureMalloc(void * mem, size_t size, uint64_t loc) {
// 		if (mem )
// 	};
// };



