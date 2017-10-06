#include "CUPTIEventHandler.h"
#include "CUPTIDriverCIBTranslate.h"
#include "CUPTIRuntimeCIBTranslate.h"

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
		if(RuntimeCIBMap.find(id) != RuntimeCIBMap.end())
			return RuntimeCIBMap[id];
		return "<unknown>";
	}

	const char * translateDriverCallback (CUpti_CallbackId id) {
		if (DriverCIBMap.find(id) != DriverCIBMap.end())
			return DriverCIBMap[id];
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