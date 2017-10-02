#include "CUPTIEventHandler.h"

extern "C" {
	void bufRequest(uint8_t **buffer, size_t *size, size_t *maxNumRecords) {
		CUPTIEventHandler::GetInstance()->bufferRequested(buffer, size, maxNumRecords);
	}

	void bufCompleted(CUcontext ctx, uint32_t streamId, uint8_t *buffer, size_t size, size_t validSize) {
		CUPTIEventHandler::GetInstance()->bufferCompleted(ctx, streamId, buffer, size, validSize);
	}

}

CUPTIEventHandler * CUPTIEventHandler::GetInstance()  {
	if (s_instance == NULL)
		assert(s_instance != NULL);
	return s_instance;
}

const char * CUPTIEventHandler::getMemcpyKindString(CUpti_ActivityMemcpyKind kind)
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

void CUPTIEventHandler::bufferRequested(uint8_t **buffer, size_t *size, size_t *maxNumRecords) {
	uint8_t * buf = (uint8_t *) malloc(4096*32);
	if (buf == NULL) {
		fprintf(stderr, "%s\n", "CUPTIAPI OUT OF MEMORY, EXITING NOW");
		exit(-1);
	}
	*size =  4096 * 32;
	*buffer = buf;
	*maxNumRecords = 0;
}

void CUPTIEventHandler::ProcessEvent(CUpti_Activity * record) {
	if (record->kind == CUPTI_ACTIVITY_KIND_MEMCPY) {
		CUpti_ActivityMemcpy * cpy = (CUpti_ActivityMemcpy *) record;
		std::stringstream ss;
		ss << getMemcpyKindString((CUpti_ActivityMemcpyKind) cpy->copyKind) << "," << cpy->start << "," << cpy->end << "," << cpy->correlationId << "," << cpy->runtimeCorrelationId << std::endl;
		std::string out = ss.str();	
		_log.get()->Write(out);
  }
}

void CUPTIEventHandler::bufferCompleted(CUcontext ctx, uint32_t streamId, uint8_t *buffer, size_t size, size_t validSize) {
  	CUptiResult status;
  	CUpti_Activity *record = NULL;
	if (validSize > 0) {
  		do {
			status = cuptiActivityGetNextRecord(buffer, validSize, &record);
			if (status == CUPTI_SUCCESS) {
		 		ProcessEvent(record);
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

int CUPTIEventHandler::PerformAction(TransferPtr t) {
	if (_enabled == false)
		return 0;
	// if (cuptiActivityPushExternalCorrelationId(CUPTI_EXTERNAL_CORRELATION_KIND_CUSTOM0, t.get()->GetID()) != CUPTI_SUCCESS) {
	// 	std::cerr << "Could not push correlationId" << std::endl;
	// 	return -1;
	// }
	return 0;
}

int CUPTIEventHandler::PostTransfer(TransferPtr t) { 
	if (_enabled == false)
		return 0;
	// uint64_t externalId = 0;
	// if (cuptiActivityPopExternalCorrelationId(CUPTI_EXTERNAL_CORRELATION_KIND_CUSTOM0,&externalId) != CUPTI_SUCCESS) {
	// 	std::cerr << "Could not pop correlationId" << std::endl;
	// 	return -1;
	// }
	return 0;
}


CUPTIEventHandler::~CUPTIEventHandler() {
	//cuptiFinalize();
}

CUPTIEventHandler::CUPTIEventHandler(bool enabled, FILE * file) {
	_enabled = enabled;
	if (enabled == false)
		return;
	s_instance = this;
	_log.reset(new LogInfo(file));
	// Initailize CUPTI to capture memory transfers
	if (cuptiActivityEnable(CUPTI_ACTIVITY_KIND_MEMCPY) != CUPTI_SUCCESS) {
		std::cerr << "Could not enable activity capturing for memcpy's with CUPTI" << std::endl;
		_enabled = false;
		return;
	}

	if (cuptiActivityRegisterCallbacks(bufRequest, bufCompleted) != CUPTI_SUCCESS) {
		std::cerr << "Could not bind CUPTI functions, disabling CUPTI" << std::endl;
		_enabled = false;
		return;		
	}
}