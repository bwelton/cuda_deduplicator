#include "MemoryTransfer.h"

bool CallIsTransfer(CallID call) {
	if (TransferCallIDs == NULL)
		return false;
	if (TransferCallIDs->find(call) != TransferCallIDs->end())
		return true;
	return false;	
}

bool MemoryTransfer::IsSupportedTransfer() {
	if (_supported == 0)
		return false;
	else if (_supported == 1)
		return true;

	CallID callIdent = _params->GetID();
	if (StandardCopies->find(callIdent) != StandardCopies->end() ||
		ArrayCopies->find(callIdent) != ArrayCopies->end()){
		_supported = 1;
		if (ArrayCopies->find(callIdent) != ArrayCopies->end())
			_arrayTransfer = true;
		return true;
	}

	_supported = 0;
	if (UnsupportedCopies->find(callIdent) != UnsupportedCopies->end()){
		return false;
	}

	std::cerr << "WARNING: We have an unknown transfer call with ID: " << _params->GetID() << std::endl;
	return false;
}

MemoryTransfer::MemoryTransfer(Parameters *params) :
	_params(params), _arrayTransfer(false), _supported(-1), _transfer(false), _origData(0), _transferedData(0) {
	if (CallIsTransfer(params->GetID()))
		_transfer = true;
	else
		_transfer = false;
	if (_transfer == true)
		IsSupportedTransfer();
}

uint32_t MemoryTransfer::GetHash(void * ptr, size_t size){
	return XXHash32::hash(ptr, size, 0);
}

uint32_t MemoryTransfer::GetSourceDataHash( void * dstPtr, size_t tSize) {
	void * data;
	bool mallocd = false;
	// Get a hash check of the data already at the destination
	if (_dstType == CU_MEMORYTYPE_HOST){
		// Destination data already on the CPU, just use that ptr
		data = dstPtr;
	} else if(_dstType == CU_MEMORYTYPE_DEVICE) {
		// Destination is the GPU, grab existing data.
		data = malloc(tSize);
		if(Bound_cuMemcpyDtoH_v2(data,(CUdeviceptr)dstPtr, tSize) != 0){
			std::cerr << "Could not copy data off GPU for destination hash checking, exiting now" << std::endl;
			exit(-1);
		}
		mallocd = true;
	} else if (_dstType == CU_MEMORYTYPE_ARRAY) {
	 	std::cerr << "Wrong processing routine has been used for this transfer with ID: " << _params->GetID() <<  " and name " << _params->GetName() << std::endl;
	 	exit(-1);
	} else {
		std::cerr << "Unknown ptr type for destination has been used for this transfer with ID: " << _params->GetID() <<  " and name " << _params->GetName() << std::endl;
		exit(-1);
	}
	uint32_t hashv = GetHash(data, tSize);
	if (mallocd == true)
		free(data);
	return hashv;
}

uint32_t MemoryTransfer::GetTransferredData( void * dstPtr, void * srcPtr, size_t tSize) {
	void * data;
	bool mallocd = false;
	// Get a hash check of the data already at the destination
	if (_dstType == CU_MEMORYTYPE_HOST){
		// Destination data already on the CPU, just use that ptr
		data = dstPtr;
	} else if(_dstType == CU_MEMORYTYPE_DEVICE) {
		// Destination is the GPU, grab existing data.
		if (_srcType == CU_MEMORYTYPE_HOST) {
			data = srcPtr;
		} else {
			data = malloc(tSize);
			if(Bound_cuMemcpyDtoH_v2(data,(CUdeviceptr)dstPtr, tSize) != 0){
				std::cerr << "Could not copy data off GPU for destination hash checking, exiting now" << std::endl;
				exit(-1);
			}
			mallocd = true;
		}
	} else if (_dstType == CU_MEMORYTYPE_ARRAY) {
	 	std::cerr << "Wrong processing routine has been used for this transfer with ID: " << _params->GetID() <<  " and name " << _params->GetName() << std::endl;
	 	exit(-1);
	} else {
		std::cerr << "Unknown ptr type for destination has been used for this transfer with ID: " << _params->GetID() <<  " and name " << _params->GetName() << std::endl;
		exit(-1);
	}
	uint32_t hashv = GetHash(data, tSize);
	if (mallocd == true)
		free(data);
	return hashv;
}

uint32_t MemoryTransfer::GetSourceDataArray( void * dstPtr, size_t tSize, size_t offset) {
	void * data = malloc(tSize);
	if (_dstType == CU_MEMORYTYPE_ARRAY) {
		if(Bound_cuMemcpyAtoH_v2(data, (CUarray)dstPtr, offset, tSize) != 0) {
			std::cerr << "Could not copy array data for destination hash checking, exiting now" << std::endl;
			exit(-1);			
		}
	} else {
	 	std::cerr << "Wrong processing routine has been used for this transfer with ID: " << _params->GetID() <<  " and name " << _params->GetName() << std::endl;
	 	exit(-1);		
	}
	uint32_t hashv = GetHash(data, tSize);
	free(data);
	return hashv;
}


void MemoryTransfer::PrecallHandleStandard() {
	if (_origData != 0)
		return;
	Bound_cuPointerGetAttribute((void*)&_srcType, CU_POINTER_ATTRIBUTE_MEMORY_TYPE, *((void**)_params->GetParameter(1)));
	Bound_cuPointerGetAttribute((void*)&_dstType, CU_POINTER_ATTRIBUTE_MEMORY_TYPE, *((void**)_params->GetParameter(0)));
	_transferSize = ((size_t*)_params->GetParameter(2))[0];

	_origData = GetSourceDataHash(*((void**)_params->GetParameter(0)), _transferSize);
}

void MemoryTransfer::PrecallHandleArray() {
	// SingleAddr, ArrayPtr, 
	if (_origData != 0)
		return;
	static std::vector<CallID> toSinglePtr = {ID_cuMemcpyAtoH, ID_cuMemcpyAtoD_v2, ID_cuMemcpyAtoHAsync_v2, ID_cuMemcpyAtoH_v2, ID_cuMemcpyAtoD, ID_cuMemcpyAtoHAsync};
	static std::vector<CallID> toArray = {ID_cuMemcpyDtoA, ID_cuMemcpyDtoA_v2, ID_cuMemcpyHtoA_v2, ID_cuMemcpyHtoA, ID_cuMemcpyHtoAAsync, ID_cuMemcpyHtoAAsync_v2};
	if (std::find(toSinglePtr.begin(), toSinglePtr.end(), _params->GetID()) != toSinglePtr.end()) {
		// Array to normal pointer transfer
		Bound_cuPointerGetAttribute((void*)&_srcType, CU_POINTER_ATTRIBUTE_MEMORY_TYPE, *((void**)_params->GetParameter(1)));
		Bound_cuPointerGetAttribute((void*)&_dstType, CU_POINTER_ATTRIBUTE_MEMORY_TYPE, *((void**)_params->GetParameter(0)));
		_transferSize = ((size_t*)_params->GetParameter(3))[0];
		_origData = GetSourceDataHash(*((void**)_params->GetParameter(0)), _transferSize);
	} else if (std::find(toArray.begin(), toArray.end(), _params->GetID()) != toArray.end()) {
		// Pointer to Array
		Bound_cuPointerGetAttribute((void*)&_srcType, CU_POINTER_ATTRIBUTE_MEMORY_TYPE, *((void**)_params->GetParameter(2)));
		Bound_cuPointerGetAttribute((void*)&_dstType, CU_POINTER_ATTRIBUTE_MEMORY_TYPE, *((void**)_params->GetParameter(0)));
		_transferSize = ((size_t*)_params->GetParameter(3))[0];
		_origData = GetSourceDataArray(*((void**)_params->GetParameter(0)),_transferSize, ((size_t*)_params->GetParameter(1))[0]);
	} else if (_params->GetID() == ID_cuMemcpyAtoA_v2) {
		// Special case where arrays are both at source and destination...
		Bound_cuPointerGetAttribute((void*)&_srcType, CU_POINTER_ATTRIBUTE_MEMORY_TYPE, *((void**)_params->GetParameter(2)));
		Bound_cuPointerGetAttribute((void*)&_dstType, CU_POINTER_ATTRIBUTE_MEMORY_TYPE, *((void**)_params->GetParameter(0)));
		_transferSize = ((size_t*)_params->GetParameter(4))[0];
		_origData = GetSourceDataArray(*((void**)_params->GetParameter(0)),_transferSize, ((size_t*)_params->GetParameter(1))[0]);
	} else {
		std::cerr << "We are not an array that we know about/is supported, exiting now...." << std::endl;
		exit(-1);
	}
}

void MemoryTransfer::PostcallHandleArray() {
	if (_transferedData != 0)
		return;
	static std::vector<CallID> toSinglePtr = {ID_cuMemcpyAtoH, ID_cuMemcpyAtoD_v2, ID_cuMemcpyAtoHAsync_v2, ID_cuMemcpyAtoH_v2, ID_cuMemcpyAtoD, ID_cuMemcpyAtoHAsync};
	static std::vector<CallID> toArray = {ID_cuMemcpyDtoA, ID_cuMemcpyDtoA_v2, ID_cuMemcpyHtoA_v2, ID_cuMemcpyHtoA, ID_cuMemcpyHtoAAsync, ID_cuMemcpyHtoAAsync_v2};
	if (std::find(toSinglePtr.begin(), toSinglePtr.end(), _params->GetID()) != toSinglePtr.end()) {
		// Array to normal pointer transfer
		_transferedData = GetSourceDataHash(*((void**)_params->GetParameter(0)), _transferSize);
	} else if (std::find(toArray.begin(), toArray.end(), _params->GetID()) != toArray.end()) {
		// Pointer to Array
		_transferedData = GetSourceDataArray(*((void**)_params->GetParameter(0)),_transferSize, ((size_t*)_params->GetParameter(1))[0]);
	} else if (_params->GetID() == ID_cuMemcpyAtoA_v2) {
		// Special case where arrays are both at source and destination...
		_transferedData = GetSourceDataArray(*((void**)_params->GetParameter(0)),_transferSize, ((size_t*)_params->GetParameter(1))[0]);
	} else {
		std::cerr << "We are not an array that we know about/is supported, exiting now...." << std::endl;
		exit(-1);
	}	
}

void MemoryTransfer::PostcallHandleStandard() {
	if (_transferedData != 0)
		return;
	_transferedData = GetTransferredData(*((void**)_params->GetParameter(0)), *((void**)_params->GetParameter(1)), _transferSize);
}
// Perform the pretransfer operations to get hash of dest/source.
void MemoryTransfer::PreTransfer() {
	if (_supported == false)
		return;
	if (_arrayTransfer == true)
		PrecallHandleArray();
	else (_arrayTransfer == false)
		PrecallHandleStandard();
}

void MemoryTransfer::PostTransfer() {
	if (_supported == false)
		return;
	if (_arrayTransfer == true)
		PostcallHandleArray();
	else (_arrayTransfer == false)
		PostcallHandleStandard();
}
