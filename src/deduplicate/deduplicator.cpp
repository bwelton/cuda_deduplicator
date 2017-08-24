#include "deduplicator.h"
std::shared_ptr<Deduplicate> Dedup;
boost::recursive_mutex _mtx; 
boost::recursive_mutex _log_mtx;
// Thread Local Storage for device memory ptrs.
// The reason for this is to support future work where
//   multiple devices may be in use (where each thread will 
//   have a different ptr translations to device memory)
thread_local std::map<uint32_t, DevMemPtr> _dev_mem;

extern "C" {
	extern void d2d_copy_launcher_me(void * out, void * in, size_t size, cudaStream_t stream);
}
#define gpuErrchk(ans) gpuAssert((ans), __FILE__, __LINE__)
inline cudaError_t gpuAssert(cudaError_t code, const char *file, int line, bool abort=true)
{
   if (code != cudaSuccess) 
   {
      fprintf(stderr,"GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
      if (abort) exit(code);
   } 
   return code;
}

void Deduplicate::GenerateAllocation() {
	if(cudaMalloc(&_devPtr, ALLOCATION_SIZE * ALLOCATION_COUNT) != CUDA_SUCCESS) {
		fprintf(stderr, "%s\n", "COULD NOT ALLOCATE CUDA STORAGE");
		LogOutput("%s\n", "COULD NOT ALLOCATE CUDA STORAGE");
		exit(-1);
	}
	#ifdef DEBUG_OUTPUT
	LogOutput("%s: %llu\n","Successfully allocated CUDA Memory", ALLOCATION_SIZE * ALLOCATION_COUNT);
	#endif


	for (int i = 0; i < ALLOCATION_COUNT; i++) {
		DeviceMemory tmp;
		DevMemPtr tmp2;
		tmp.id = i;
		tmp2.id = i;
		_freeStorage.push_back(tmp);
		tmp2.ptr = ((char *)_devPtr)+ (ALLOCATION_SIZE * i);
		_dev_mem[i] = tmp2;
	}		
}

Deduplicate::Deduplicate() {
	boost::recursive_mutex::scoped_lock lock(_mtx);
	_log.reset(new LogInfo(stderr));
	GenerateAllocation();
	_collisionCount = 0;
	_collisionSize = 0;
	_totalCount = 0;
	_totalSize = 0;
	_missedHashes = 0;
	_missedSize = 0;
	_transferErrors = 0;
	_caughtDuplicates = 0;
}

void Deduplicate::AllocateLocalIPC(){

	if (_dev_mem.size() == 0) {
		void * tmp;
		boost::recursive_mutex::scoped_lock lock(_mtx);
		//PrintContext();
		if (_dev_mem.size() != 0) 
			return;
		cudaPointerAttributes attrs;
		fprintf(stderr, "Device PTR: %p\n", _devPtr);
		while(1) {
			gpuErrchk(cudaPointerGetAttributes(&attrs,_devPtr));
			if (attrs.devicePointer == NULL){
				fprintf(stderr, "%s\n", "Cant access Device Ptr");
				sleep(1);
			} else {
				break;
			}
		}

		for (int i = 0; i < ALLOCATION_COUNT; i++) {
			DevMemPtr tmp2;	
			tmp2.id = i;
			tmp2.ptr = ((char *)_devPtr) + (ALLOCATION_SIZE * i);
			_dev_mem[i] = tmp2;
		}
	}
}

Deduplicate::~Deduplicate() {
  fprintf(stderr, "Collisions: %llu, Size: %lld\n", _collisionCount, _collisionSize); 
  fprintf(stderr, "Total Transfer Time: %f, Time Spent Transferring Duplicates: %f\n", _totTransferTime, _totDuplicateTime);
  fprintf(stderr, "Total Transfer: %llu, Total Size: %lld\n", _totalCount, _totalSize); 
  fprintf(stderr, "Missed Collisions: %llu, Total Size: %lld\n",_missedHashes, _missedSize );
  fprintf(stderr, "Transfer Errors: %llu, Caught duplicates: %llu\n",_transferErrors,_caughtDuplicates );
}

uint32_t Deduplicate::HashData(char * data, size_t size) {
	uint32_t result = 0;
//#ifdef USE_PRIVATE 
	result = XXHash32::hash(data, size, 0);
//#endif
	return result;
}

cudaError_t Deduplicate::PerformCachedTransfer(DataStruct ret){
	//boost::recursive_mutex::scoped_lock lock(_mtx);
	//func_call((void *)ret.destPtr, (void *)ret.storePTR, ret.size, ret.stream);
	//d2d_copy_launcher_me((void *)ret.destPtr, (void *)ret.storePTR, ret.size, ret.stream);
	return cudaMemcpyAsync((void *)ret.destPtr, (const void *)ret.storePTR, ret.size, cudaMemcpyDeviceToDevice, ret.stream);
}


DataStruct Deduplicate::DeduplicateData(DataStruct ret) {
	if (ret.size > 5242880 || ret.size < 16) {
		//fprintf(stderr, "Size is too large\n");
		ret.duplicate = false;
		return ret;
	}

//#ifdef USE_PRIVATE 
	ret.hash = HashData((char*)ret.storePTR,ret.size);
#ifdef DEBUG_OUTPUT
	LogOutput("\nTransfer Hash: %u Size: %llu \n", ret.hash, ret.size);
#endif
//#endif
	AllocateLocalIPC();
	{
		boost::recursive_mutex::scoped_lock lock(_mtx);
		if (_cachedTransfer.find(ret.hash) != _cachedTransfer.end()) {
			ret.duplicate = true;
			DeviceMemory tmp = _cachedTransfer[ret.hash];
			ret.storePTR = _dev_mem[tmp.id].ptr;
			ret.status = gpuErrchk(PerformCachedTransfer(ret));
			if (ret.status != CUDA_SUCCESS) {
				ret.duplicate = false;
				fprintf(stderr, "duplicate transfer failed\n");
			} else {
				_caughtDuplicates++;
			}
		} else {
			ret.duplicate = false;
		}
	}
	return ret;
}

DeviceMemory Deduplicate::GrabLast(){
	{
		boost::recursive_mutex::scoped_lock lock(_mtx);
		std::pair<uint32_t,DeviceMemory> tmp = _usedStorage.front();
		_usedStorage.pop_front();
		_cachedTransfer.erase(tmp.first);
		return tmp.second;
	}

}

DataStruct Deduplicate::AddNew(DataStruct ret) {
	// return ret;
	if (ret.size > 5242880) 
		return ret;
	void * storePtr;
	{
		DeviceMemory tmp;
		boost::recursive_mutex::scoped_lock lock(_mtx);
		if (_cachedTransfer.find(ret.hash) != _cachedTransfer.end()) 
			return ret;
		if (_freeStorage.size() > 0) {
			tmp = _freeStorage.back();
			_freeStorage.pop_back();
		} else {
			tmp = GrabLast();
		}
		ret.destPtr = _dev_mem[tmp.id].ptr;
		if(gpuErrchk(PerformCachedTransfer(ret)) != CUDA_SUCCESS) {
			fprintf(stderr, "COULD NOT PERFORM DUPLICATE TRANSFER\n");
			_transferErrors++;
			_freeStorage.push_back(tmp);
			return ret;
		}
		_cachedTransfer[ret.hash] = tmp;
		_usedStorage.push_back(std::make_pair(ret.hash,tmp));
	}
	return ret;
}

void Deduplicate::LogOutput(char * fmt,...) {
    va_list args;

    va_start(args, fmt);
    _log.get()->Write(fmt, args);
    va_end(args);
}

void Deduplicate::TrackTransfer(int id, int64_t size, char * data) {

}

void Deduplicate::TrackTransfer(int id, int64_t size, char * data, float transfer_time) {
	// Track transfer but do not actually perform deduplication....
	// Independent of the deduplicator
	if (size == 0)
		return;

	uint32_t hash = HashData(data, size);

	boost::recursive_mutex::scoped_lock lock(_mtx);

	if (_previousHash.find(hash) != _previousHash.end()) {
		_collisionCount++;
		_collisionSize += size;
		_totDuplicateTime += transfer_time;
	} else {
		_previousHash[hash] = size;
	}
	_totalSize += size;
	_totalCount += 1;
	_totTransferTime += transfer_time;
}

void Deduplicate::TrackTransfer(int id, int64_t size) {
}
