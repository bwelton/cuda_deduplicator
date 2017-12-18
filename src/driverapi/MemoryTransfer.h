#pragma ONCE
#include "Parameters.h"
#include "PluginCommon.h"
#include <set>
#include <iostream>
#include "xxhash32.h"
#include "cuda.h"

class MemoryTransfer {
private:
	int _supported;
	Parameters * _params;
	bool _transfer;
	bool _arrayTransfer;
	uint32_t _transferedData;
	uint32_t _origData;
	size_t _transferSize;
	CUmemorytype _srcType;
	CUmemorytype _dstType;
public:
	MemoryTransfer(CallID call, Parameters * params);
	bool IsSupportedTransfer();
	uint32_t GetHash(void * ptr, size_t size);
	uint32_t GetSourceDataHash( void * dstPtr, size_t tSize);
	uint32_t GetTransferredData( void * dstPtr, void * srcPtr, size_t tSize);
	uint32_t GetSourceDataArray( void * dstPtr, size_t tSize, size_t offset);
	void PrecallHandleStandard();
	void PrecallHandleArray();
	void PostcallHandleArray();
	void PostcallHandleStandard();
	void PreTransfer();
	void PostTransfer();
}