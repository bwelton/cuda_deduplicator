#pragma ONCE
#include "PluginCommon.h"
#include <algorithm>
#include <set>
#include <iostream>
#include "xxhash32.h"
#include "cuda.h"

class Parameters;

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
	MemoryTransfer(Parameters * params);
	bool IsSupportedTransfer();
	uint32_t GetHash(void * ptr, size_t size);
	uint32_t GetHashAtLocation( void * dstPtr, size_t tSize, CUmemorytype location);
	uint32_t GetSourceDataArray( void * dstPtr, size_t tSize, size_t offset);
	void PrecallHandleStandard();
	void PrecallHandleArray();
	void PostcallHandleArray();
	void PostcallHandleStandard();
	void PreTransfer();
	void PostTransfer();
};

#include "Parameters.h"