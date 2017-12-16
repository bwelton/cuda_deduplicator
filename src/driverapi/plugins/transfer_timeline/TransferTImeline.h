#pragma ONCE
#include "Parameters.h"
#include "PluginCommon.h"
#include "xxhash32.h"
#include "LogInfo.h"

extern "C" {
	void init(std::vector<std::string> & cmd_list);
	PluginReturn Precall(std::shared_ptr<Parameters> params);
	PluginReturn Postcall(std::shared_ptr<Parameters> params);
}

class TransferTimeline {
public:
	TransferTimeline(std::vector<std::string> & cmd_list);
	~TransferTimeline();
	PluginReturn Precall(std::shared_ptr<Parameters> params);
	PluginReturn Postcall(std::shared_ptr<Parameters> params);
private:
	std::map<int,std::string> _cmdToName;
	size_t callcount;
	std::map<CallID, bool> _transferCalls;
	boost::recursive_mutex _timeline_mtx;
	std::shared_ptr<LogInfo> _timeline_log;
	std::map<uint32_t, uint64_t> _pastTransfers;
	uint64_t _count; 
	bool _enabled;
};
//#define TRANSFER_CALLS {ID_cuMemcpy,

//ID_cuMemcpyAtoH,
//ID_cuMemcpyAtoA,
//ID_cuMemcpyAtoD_v2,
//ID_cuMemcpyAtoHAsync_v2,
//ID_cuMemcpyAtoH_v2,
//ID_cuMemcpyAtoA_v2,
//ID_cuMemcpyAtoD,
//ID_cuMemcpyAtoHAsync,
//
//ID_cuMemcpyDtoA,
//ID_cuMemcpyDtoA_v2,
//ID_cuMemcpyHtoA_v2,
//ID_cuMemcpyHtoA,
//ID_cuMemcpyHtoAAsync,
//ID_cuMemcpyHtoAAsync_v2,
//
//ID_cuMemcpyHtoD,
//ID_cuMemcpyDtoH,
//ID_cuMemcpyDtoD,
//ID_cuMemcpyDtoH_v2,
//ID_cuMemcpyDtoD_v2,
//ID_cuMemcpyAsync,
//ID_cuMemcpyHtoDAsync,
//ID_cuMemcpyDtoHAsync,
//ID_cuMemcpyDtoDAsync,
//ID_cuMemcpyHtoD_v2,
//ID_cuMemcpyHtoDAsync_v2,
//ID_cuMemcpyDtoHAsync_v2,
//ID_cuMemcpyDtoDAsync_v2,



std::function<int(void *,CUpointer_attribute,CUdeviceptr)> Bound_cuPointerGetAttribute;

//
//UNSUPPORTED:
//ID_cuMemcpyPeer,
//ID_cuMemcpyPeerAsync,
//ID_cuMemcpy2D_v2,
//ID_cuMemcpy2DUnaligned_v2,
//ID_cuMemcpy3D_v2,
//ID_cuMemcpy2DAsync,
//ID_cuMemcpy3DAsync,
//ID_cuMemcpy3DPeerAsync,
//ID_cuMemcpy2DAsync_v2,
//ID_cuMemcpy3DAsync_v2,
//ID_cuMemcpy2D,
//ID_cuMemcpy2DUnaligned,
//ID_cuMemcpy3D,
//ID_cuMemcpy3DPeer};

void MemoryTransfer::Get1DTransferPrecall(std::shared_ptr<Parameters> params) {
	CUmemorytype srcType;
	Bound_cuPointerGetAttribute((void*)&srcType, CU_POINTER_ATTRIBUTE_MEMORY_TYPE, *((void**)params.get()->GetParameter(1)));
	if(srcType == CU_MEMORYTYPE_HOST) {
		// src is a host pointer, perform now;
	}
	// Otherwise wait for post
	return;
}
void MemoryTransfer::Get1DTransferPostcall(std::shared_ptr<Parameters> params) {
	CUmemorytype srcType;
	Bound_cuPointerGetAttribute((void*)&srcType, CU_POINTER_ATTRIBUTE_MEMORY_TYPE, *((void**)params.get()->GetParameter(0)));
	if(srcType == CU_MEMORYTYPE_HOST) {
		// src is a host pointer, perform now;
	}
	// Otherwise wait we are done
	return;
}

void MemoryTransfer::GetArrayTransferPrecall(std::shared_ptr<Parameters> params) {


//ID_cuMemcpyDtoA,
//ID_cuMemcpyDtoA_v2,
//ID_cuMemcpyHtoA_v2,
//ID_cuMemcpyHtoA,
//ID_cuMemcpyHtoAAsync,
//ID_cuMemcpyHtoAAsync_v2,
		CUmemorytype srcType;
	if (_arrayToSingle.find(params.get()->GetID()) != _arrayToSingle.end()){

		Bound_cuPointerGetAttribute((void*)&srcType, CU_POINTER_ATTRIBUTE_MEMORY_TYPE, *((void**)params.get()->GetParameter(0)));
		if (srcType == CU_MEMORYTYPE_HOST){
			// Perform work now
		}		
	} else {
		Bound_cuPointerGetAttribute((void*)&srcType, CU_POINTER_ATTRIBUTE_MEMORY_TYPE, *((void**)params.get()->GetParameter(2)));
		if (srcType == CU_MEMORYTYPE_HOST){
			// Perform work now
		}		
	}
}
class MemoryTransfer {
	void * dst;
	void * host;
	uint32_t hash;

};


PluginReturn TransferTimeline::Precall(std::shared_ptr<Parameters> params) {
	if(_transferCalls.find(params.get()->GetID()) == _transferCalls.end()){
		return NO_ACTION;
	}

}
