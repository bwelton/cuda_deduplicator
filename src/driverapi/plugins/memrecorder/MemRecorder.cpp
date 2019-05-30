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
		return n;
	};

	void Delete(uint64_t addr) {
		if (_addressMap.find(addr) != _addressMap.end()) {
			_allocedAddresses.push_back(_addressMap[addr]);
			_addressMap.erase(addr);
		}
	};

	uint64_t allocCount;
	std::map<uint64_t, MemAddress*> _addressMap;
	std::deque<MemAddress *> _allocedAddresses;
};


class OutputWriter{
public:
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
		_outWriter.reset(new OutputWriter());
		_cpuLocalMem.reset(new MemKeeper());
		_gpuLocalMem.reset(new MemKeeper());
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
		_cpuLocalMem->Delete(addr);
	};

	void GPUMallocData(uint64_t addr, size_t size, int64_t loc)  {
		_gpuLocalMem->Set(addr,size, loc);
	};
	void GPUFreeData(uint64_t addr, int64_t loc) {
		MemAddress * gpuAddr = _gpuLocalMem->Get(addr);
		if (gpuAddr != NULL) {
			_outWriter->RecordGPUMallocPair(gpuAddr, loc);
		}		
		_gpuLocalMem->Delete(addr);	
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



extern "C" {
	void * DIOGENES_REC_MALLOCWrapper(size_t size)  {
		int64_t cache = DIOGENES_CTX_ID;
		if(DIOGENES_GetGlobalLock() && DIOGENES_TEAR_DOWN == false) {
			PLUG_BUILD_FACTORY();
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
			PLUG_FACTORY_PTR->CPUFreeData((uint64_t)mem);
			DIOGENES_ReleaseGlobalLock();
		}
		free(mem);
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



