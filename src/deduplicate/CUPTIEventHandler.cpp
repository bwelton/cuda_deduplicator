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
	 	// rintf("MEMCPY %s [ %llu - %llu ] device %u, context %u, stream %u, correlation %u/r%u\n",
		// 	getMemcpyKindString((CUpti_ActivityMemcpyKind) memcpy->copyKind),
		// 	(unsigned long long) (memcpy->start - startTimestamp),
		// 	(unsigned long long) (memcpy->end - startTimestamp),
		// 	memcpy->deviceId, memcpy->contextId, memcpy->streamId,
		// 	memcpy->correlationId, memcpy->runtimeCorrelationId);
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