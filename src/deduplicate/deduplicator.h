#ifndef DEDUPLICATOR
#define DEDUPLICATOR 1
#include "cuda_runtime_api.h"
#include "crt/host_runtime.h"
#include "cuda.h"
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <functional>
#include <array>
#include <iostream>
#include <cassert>
#include <deque>
#include <sys/time.h>
#include <cstdlib>
#include <sstream>
#include <tuple>
#include <utility> 
#include <stdarg.h>
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <mutex>
#include <cstdarg>
#include <stdarg.h>
#include <condition_variable>
#include <boost/thread/recursive_mutex.hpp>
#include "LogInfo.h"
#include "xxhash32.h"

//#define DEBUG_OUTPUT 1
#define ALLOCATION_SIZE 5242880
#define ALLOCATION_COUNT 20
#define TIMEOUT 10 //Timeout data after 10 successful transfers have taken place.
#define MAX_DATA_SIZE_BYTES 10485760 // Maximum size of data that can be temporarily stored

struct DataStruct {
	bool duplicate;
	void * storePTR;
	void * destPtr;
	uint32_t hash;
	size_t size;
	cudaStream_t stream;
	cudaError_t status;
	bool blocking;
};

struct DeviceMemory {
	uint32_t id;
	cudaIpcMemHandle_t handle;
};

struct DevMemPtr {
	uint32_t id;
	void * ptr;
};

enum OutLocation {
	STDOUT = 0, 
	STDERR = 1,
	TOFILE = 2
};
typedef void (*cudaD2DCall)(void *, void *, size_t, cudaStream_t);
class Deduplicate{
public:
	Deduplicate();
	~Deduplicate();
	void GenerateAllocation();
	void AllocateLocalIPC();
	void TrackTransfer(int id, int64_t size);
	void TrackTransfer(int id, int64_t size, char * data);
	uint32_t HashData(char * data, size_t size);
	cudaError_t PerformCachedTransfer(DataStruct ret);
	DataStruct DeduplicateData(DataStruct ret);
	DeviceMemory GrabLast();
	void LogOutput(char * fmt,...);
	DataStruct AddNew(DataStruct ret);
	void TrackTransfer(int id, int64_t size, char * data, float transfer_time);
private:

	size_t _collisionCount;
	int64_t _collisionSize;
        int64_t _totalSize;
	size_t _totalCount;
	size_t _caughtDuplicates;
	std::map<uint32_t, void *> _storedCopies;
	void * _devPtr;
	int _transferCount;
	std::vector<DeviceMemory> _freeStorage;
	std::deque<std::pair<uint32_t,DeviceMemory> > _usedStorage;
	std::map<uint32_t, DeviceMemory> _cachedTransfer;

	uint64_t _transferErrors;
	std::map<int, int64_t> _previousTransfers; 
	std::map<int, void *> _storedTransfers;
	uint64_t _missedHashes;
	int64_t _missedSize;
	std::map<uint32_t, int64_t> _previousHash;
	cudaIpcMemHandle_t _devHandle;
	cudaD2DCall func_call;
	double _totTransferTime, _totDuplicateTime;
	std::shared_ptr<LogInfo> _log;
};

extern std::shared_ptr<Deduplicate> Dedup;
#define BUILD_STORAGE_CLASS \
	if (Dedup.get() == NULL) { \
		fprintf(stderr, "%s\n", "Setting up our global data structure"); \
		Dedup.reset(new Deduplicate()); \
	} 

#define STORAGE_PTR Dedup.get()
#endif
