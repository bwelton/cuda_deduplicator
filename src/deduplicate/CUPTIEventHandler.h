#pragma once
#include <map>
#include <string>
#include <iostream>
#include <sstream> 
#include <map>
#include <cuda.h>
#include <cupti.h>
// #include <cupti_runtime_cbid.h>
// #include <cupti_driver_cbid.h>
#include <boost/thread/recursive_mutex.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "InstrumentBase.h"
#include "TransferBase.h"
#include "LogInfo.h"
#include <linux/unistd.h>
#include <sys/syscall.h>

class CUPTIEventHandler : public InstrumentBase {
private: 
	boost::recursive_mutex _mtx;
	std::shared_ptr<LogInfo> _log;
	bool _enabled;
public: 
	int PerformAction(TransferPtr t);
	int PostTransfer(TransferPtr t);
	~CUPTIEventHandler();
	CUPTIEventHandler(bool enabled = false, FILE * file = NULL);
};