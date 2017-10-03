#include "CUPTIEventHandler.h"

// /opt/nvidia/cudatoolkit7.5/7.5.18-1.0502.10743.2.1/extras/CUPTI/include/cupti_runtime_cbid.h
// This is super unsafe and may need to be refactored. 
std::shared_ptr<InstrumentBase> s_instance;
std::shared_ptr<LogInfo> _cupti_output;
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
			ss << getMemcpyKindStringC((CUpti_ActivityMemcpyKind) cpy->copyKind) << "," << cpy->bytes << "," << cpy->start - startTimestamp << "," << cpy->end - startTimestamp << "," << cpy->correlationId << "," << cpy->runtimeCorrelationId << "," << cpy->contextId << "," << cpy->deviceId << "," << cpy->streamId << std::endl;
			std::string out = ss.str();	
			_cupti_output.get()->Write(out);
	    } else if (record->kind == CUPTI_ACTIVITY_KIND_RUNTIME) {
	    	CUpti_ActivityAPI *api = (CUpti_ActivityAPI *) record;
	    	std::stringstream ss;
	    	ss << "RR" << "," << api->cbid << "," << api->processId << "," << api->threadId << "," << api->correlationId << "," << api->start - startTimestamp << "," << api->end - startTimestamp << std::endl;
	 		std::string out = ss.str();	
			_cupti_output.get()->Write(out);
	    } else if (record->kind == CUPTI_ACTIVITY_KIND_DRIVER) {
	    	CUpti_ActivityAPI *api = (CUpti_ActivityAPI *) record;
	    	std::stringstream ss;
	    	ss << "DR" << "," << api->cbid << "," << api->processId << "," << api->threadId << "," << api->correlationId << "," << api->start - startTimestamp << "," << api->end - startTimestamp << std::endl;
	 		std::string out = ss.str();	
			_cupti_output.get()->Write(out);	    	
	    }

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
	  	free(buffer);
	}
}

int CUPTIEventHandler::PerformAction(TransferPtr t) {
	return 0;
}

int CUPTIEventHandler::PostTransfer(TransferPtr t) { 
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
	_cupti_output.reset(new LogInfo(file));
	// Initailize CUPTI to capture memory transfers
	if (cuptiActivityEnable(CUPTI_ACTIVITY_KIND_MEMCPY) != CUPTI_SUCCESS) {
		std::cerr << "Could not enable activity capturing for memcpy's with CUPTI" << std::endl;
		_enabled = false;
		return;
	}
	cuptiActivityEnable(CUPTI_ACTIVITY_KIND_DRIVER);
	cuptiActivityEnable(CUPTI_ACTIVITY_KIND_RUNTIME);
	cuptiGetTimestamp(&startTimestamp);
	if (cuptiActivityRegisterCallbacks(bufRequest, bufCompleted) != CUPTI_SUCCESS) {
		std::cerr << "Could not bind CUPTI functions, disabling CUPTI" << std::endl;
		_enabled = false;
		return;		
	}
}