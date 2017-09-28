#pragma once
#include <map>
#include <string>
#include <iostream>
#include <sstream> 
#include <map>
#include <cuda.h>
#include <cupti.h>
#include <boost/thread/recursive_mutex.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "InstrumentBase.h"
#include "TransferBase.h"


class CUPTIEventHandler : public InstrumentBase {
private: 
	boost::recursive_mutex _mtx;
	std::shared_ptr<LogInfo> _log;
public: 
	const char * getMemcpyKindString(CUpti_ActivityMemcpyKind kind);
	void bufferRequested(uint8_t **buffer, size_t *size, size_t *maxNumRecords);
	void ProcessEvent(CUpti_Activity * record);
	void bufferCompleted(CUcontext ctx, uint32_t streamId, uint8_t *buffer, size_t size, size_t validSize);
	int PerformAction(TransferPtr t);
	int PostTransfer(TransferPtr t);
	~CUPTIEventHandler();
	CUPTIEventHandler(bool enabled = false, FILE * file = NULL);
};