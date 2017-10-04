#include "CUPTIEventHandler.h"

// /opt/nvidia/cudatoolkit7.5/7.5.18-1.0502.10743.2.1/extras/CUPTI/include/cupti_runtime_cbid.h
// This is super unsafe and may need to be refactored. 
std::shared_ptr<InstrumentBase> s_instance;

// This is a special case for CUPTI.... Since callbacks can come
// at *any time including during distruction of objects at exit* we cannot
// use a shared_ptr since it will race here. 
static LogInfo * _cupti_output;
static std::shared_ptr<LogInfo> _packetInfo;


thread_local int my_thread_id = -1; 
thread_local int my_process_id = -1;
static uint64_t startTimestamp;

extern "C" {
	const char * getMemcpyKindStringC(CUpti_ActivityMemcpyKind kind)
	{
	  switch (kind) {
	  case CUPTI_ACTIVITY_MEMCPY_KIND_HTOD:
	    return "HostToDevice";
	  case CUPTI_ACTIVITY_MEMCPY_KIND_DTOH:
	    return "DeviceToHost";
	  case CUPTI_ACTIVITY_MEMCPY_KIND_HTOA:
	    return "HtoA";
	  case CUPTI_ACTIVITY_MEMCPY_KIND_ATOH:
	    return "AtoH";
	  case CUPTI_ACTIVITY_MEMCPY_KIND_ATOA:
	    return "AtoA";
	  case CUPTI_ACTIVITY_MEMCPY_KIND_ATOD:
	    return "AtoD";
	  case CUPTI_ACTIVITY_MEMCPY_KIND_DTOA:
	    return "DtoA";
	  case CUPTI_ACTIVITY_MEMCPY_KIND_DTOD:
	    return "DeviceToDevice";
	  case CUPTI_ACTIVITY_MEMCPY_KIND_HTOH:
	    return "HostToHost";
	  default:
	    break;
	  }

	  return "<unknown>";
	}

	const char * translateRuntimeCallback (CUpti_CallbackId id) {
		switch(id) {
			case CUPTI_RUNTIME_TRACE_CBID_cudaFree_v3020:
				return "cudaFree";
			case CUPTI_RUNTIME_TRACE_CBID_cudaMalloc_v3020:
				return "cudaMalloc";
		    case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy_v3020:
		        return "cudaMemcpy";
		    case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy2D_v3020:
		        return "cudaMemcpy2D";
		    case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyToArray_v3020:
		        return "cudaMemcpyToArray";
		    case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy2DToArray_v3020:
		        return "cudaMemcpy2DToArray";
		    case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyFromArray_v3020:
		        return "cudaMemcpyFromArray";
		    case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy2DFromArray_v3020:
		        return "cudaMemcpy2DFromArray";
		    case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyArrayToArray_v3020:
		        return "cudaMemcpyArrayToArray";
		    case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy2DArrayToArray_v3020:
		        return "cudaMemcpy2DArrayToArray";
		    case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyToSymbol_v3020:
		        return "cudaMemcpyToSymbol";
		    case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyFromSymbol_v3020:
		        return "cudaMemcpyFromSymbol";
		    case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyAsync_v3020:
		        return "cudaMemcpyAsync";
		    case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyToArrayAsync_v3020:
		        return "cudaMemcpyToArrayAsync";
		    case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyFromArrayAsync_v3020:
		        return "cudaMemcpyFromArrayAsync";
		    case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy2DAsync_v3020:
		        return "cudaMemcpy2DAsync";
		    case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy2DToArrayAsync_v3020:
		        return "cudaMemcpy2DToArrayAsync";
		    case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy2DFromArrayAsync_v3020:
		        return "cudaMemcpy2DFromArrayAsync";
		    case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyToSymbolAsync_v3020:
		        return "cudaMemcpyToSymbolAsync";
		    case CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyFromSymbolAsync_v3020:
		        return "cudaMemcpyFromSymbolAsync";
			default:
				break;
		}
		return "<unknown>";
	}

	const char * translateDriverCallback (CUpti_CallbackId id) {
		switch (id) {
		    case CUPTI_DRIVER_TRACE_CBID_cuMemcpyHtoD_v2:
		    	return "cuMemcpyHtoD_v2";
		    case CUPTI_DRIVER_TRACE_CBID_cuMemcpyHtoDAsync_v2:
		    	return "cuMemcpyHtoDAsync_v2";
		    case CUPTI_DRIVER_TRACE_CBID_cuMemcpyDtoH_v2:
		    	return "cuMemcpyDtoH_v2";
		    case CUPTI_DRIVER_TRACE_CBID_cuMemcpyDtoHAsync_v2:
		    	return "cuMemcpyDtoHAsync_v2";
		    case CUPTI_DRIVER_TRACE_CBID_cuMemcpyDtoD_v2:
		    	return "cuMemcpyDtoD_v2";
		    case CUPTI_DRIVER_TRACE_CBID_cuMemcpyDtoDAsync_v2:
		    	return "cuMemcpyDtoDAsync_v2";
		    case CUPTI_DRIVER_TRACE_CBID_cuMemcpyAtoH_v2:
		    	return "cuMemcpyAtoH_v2";
		    case CUPTI_DRIVER_TRACE_CBID_cuMemcpyAtoHAsync_v2:
		    	return "cuMemcpyAtoHAsync_v2";
		    case CUPTI_DRIVER_TRACE_CBID_cuMemcpyAtoD_v2:
		    	return "cuMemcpyAtoD_v2";
		    case CUPTI_DRIVER_TRACE_CBID_cuMemcpyDtoA_v2:
		    	return "cuMemcpyDtoA_v2";
		    case CUPTI_DRIVER_TRACE_CBID_cuMemcpyAtoA_v2:
		    	return "cuMemcpyAtoA_v2";
		    case CUPTI_DRIVER_TRACE_CBID_cuMemcpy2D_v2:
		    	return "cuMemcpy2D_v2";
		    case CUPTI_DRIVER_TRACE_CBID_cuMemcpy2DUnaligned_v2:
		    	return "cuMemcpy2DUnaligned_v2";
		    case CUPTI_DRIVER_TRACE_CBID_cuMemcpy2DAsync_v2:
		    	return "cuMemcpy2DAsync_v2";
		    case CUPTI_DRIVER_TRACE_CBID_cuMemcpy3D_v2:
		    	return "cuMemcpy3D_v2";
		    case CUPTI_DRIVER_TRACE_CBID_cuMemcpy3DAsync_v2:
		    	return "cuMemcpy3DAsync_v2";
		    case CUPTI_DRIVER_TRACE_CBID_cuMemcpyHtoA_v2:
		    	return "cuMemcpyHtoA_v2";
		    case CUPTI_DRIVER_TRACE_CBID_cuMemcpyHtoAAsync_v2:
		    	return "cuMemcpyHtoAAsync_v2";
		    case CUPTI_DRIVER_TRACE_CBID_cuMemcpy:
		    	return "cuMemcpy";
		    case CUPTI_DRIVER_TRACE_CBID_cuMemcpyAsync:
		    	return "cuMemcpyAsync";
		    default:
		    	break;
		}
		return "<unknown>";
	}

	void bufRequest(uint8_t **buffer, size_t *size, size_t *maxNumRecords) {
		uint8_t * buf = (uint8_t *) malloc(4096*32);
		if (buf == NULL) {
			fprintf(stderr, "%s\n", "CUPTIAPI OUT OF MEMORY, EXITING NOW");
			exit(-1);	
		}
		*size =  4096 * 32;
		*buffer = buf;
		*maxNumRecords = 0;
	}

	void ProcessEventC(CUpti_Activity * record) {
		if (record->kind == CUPTI_ACTIVITY_KIND_MEMCPY) {
			CUpti_ActivityMemcpy * cpy = (CUpti_ActivityMemcpy *) record;
			std::stringstream ss;
			ss << "CPY," << getMemcpyKindStringC((CUpti_ActivityMemcpyKind) cpy->copyKind) << "," << cpy->bytes << "," << cpy->start - startTimestamp << "," << cpy->end - startTimestamp << "," << cpy->correlationId << "," << cpy->runtimeCorrelationId << "," << cpy->contextId << "," << cpy->deviceId << "," << cpy->streamId << std::endl;
			std::string out = ss.str();	
			_cupti_output->Write(out);
	    } else if (record->kind == CUPTI_ACTIVITY_KIND_RUNTIME) {
	    	CUpti_ActivityAPI *api = (CUpti_ActivityAPI *) record;
	    	std::stringstream ss;
	    	ss << "RR" << "," << translateRuntimeCallback(api->cbid) << "," << api->processId << "," << api->threadId << "," << api->correlationId << "," << api->start - startTimestamp << "," << api->end - startTimestamp << std::endl;
	 		std::string out = ss.str();	
			_cupti_output->Write(out);
	    } else if (record->kind == CUPTI_ACTIVITY_KIND_DRIVER) {
	    	CUpti_ActivityAPI *api = (CUpti_ActivityAPI *) record;
	    	std::stringstream ss;
	    	ss << "DR" << "," << translateDriverCallback(api->cbid) << "," << api->processId << "," << api->threadId << "," << api->correlationId << "," << api->start - startTimestamp << "," << api->end - startTimestamp << std::endl;
	 		std::string out = ss.str();	
			_cupti_output->Write(out);	    	
		}
		// Doesn't exist in cuda 7.5......
	  //   } else if (record->kind == CUPTI_ACTIVITY_KIND_SYNCHRONIZATION) {
	  //   	CUpti_ActivitySynchronization *api = (CUpti_ActivitySynchronization *) record;
	  //   	std::stringstream ss;
	  //   	ss << "SYNC" << "," << api->contextId << "," << api->correlationId << "," << api->start - startTimestamp << "," << api->end - startTimestamp << "," << api->streamId << std::endl;    		
	 	// 	std::string out = ss.str();	
			// _cupti_output.get()->Write(out);	
	  //   }

	}
	void bufCompleted(CUcontext ctx, uint32_t streamId, uint8_t *buffer, size_t size, size_t validSize) {
	  	CUptiResult status;
	  	CUpti_Activity *record = NULL;
		if (validSize > 0) {
	  		do {
				status = cuptiActivityGetNextRecord(buffer, validSize, &record);
				if (status == CUPTI_SUCCESS) {
			 		ProcessEventC(record);
				} else if (status == CUPTI_ERROR_MAX_LIMIT_REACHED) {
				 	break;
				} else {
					const char * errorStr;
					cuptiGetResultString(status, &errorStr); 
					std::cerr << "Error in CUPTI " << status << " " << errorStr << std::endl;
					break;
				} 
			} while (1);
	  	}
	  	_cupti_output->Flush();
	  	free(buffer);
	}
}

int CUPTIEventHandler::PerformAction(TransferPtr t) {
	return 0;
}

int CUPTIEventHandler::PostTransfer(TransferPtr t) { 
	if (_enabled == false)
		return 0;

	if (my_thread_id == -1) 
		my_thread_id = (int) syscall( __NR_gettid );
	if (my_process_id == -1)
		my_process_id = (int) getpid();
	std::stringstream ss;	
	ss << t.get()->GetID() << "," << t.get()->GetSize() << "," << my_process_id << "," << my_thread_id << std::endl;
	std::string out = ss.str();	
	_packetInfo.get()->Write(out);	
	return 0;
}


CUPTIEventHandler::~CUPTIEventHandler() {
	cudaDeviceSynchronize();
	cuptiActivityFlushAll(0);
}


CUPTIEventHandler::CUPTIEventHandler(bool enabled, FILE * file) {
	_enabled = enabled;
	if (enabled == false)
		return;
	_packetInfo.reset(new LogInfo(fopen("timing_packet_corr.txt", "w")));
	_cupti_output = new LogInfo(file);
	// Initailize CUPTI to capture memory transfers
	if (cuptiActivityEnable(CUPTI_ACTIVITY_KIND_MEMCPY) != CUPTI_SUCCESS) {
		std::cerr << "Could not enable activity capturing for memcpy's with CUPTI" << std::endl;
		_enabled = false;
		return;
	}
	cuptiActivityEnable(CUPTI_ACTIVITY_KIND_DRIVER);
	cuptiActivityEnable(CUPTI_ACTIVITY_KIND_RUNTIME);
	// Doesn't exist in cuda 7.5...... 
	//cuptiActivityEnable(CUPTI_ACTIVITY_KIND_SYNCHRONIZATION);
	cuptiGetTimestamp(&startTimestamp);
	if (cuptiActivityRegisterCallbacks(bufRequest, bufCompleted) != CUPTI_SUCCESS) {
		std::cerr << "Could not bind CUPTI functions, disabling CUPTI" << std::endl;
		_enabled = false;
		return;		
	}
}