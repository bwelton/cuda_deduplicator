#pragma once
#include "Parameters.h"
#include "MemoryTransfer.h"
#include "PluginCommon.h"
#include "LogInfo.h"
#include <iostream>
#include <fstream>    
#include <string>
#include <map>
#include <sstream>
#include <boost/thread/recursive_mutex.hpp>
#include <unistd.h>
#include <sys/syscall.h>

extern "C" {
	void init(std::vector<std::string> & cmd_list);
	PluginReturn Precall(std::shared_ptr<Parameters> params);
	PluginReturn Postcall(std::shared_ptr<Parameters> params);
}

class SynchTool {
public:
	SynchTool(std::vector<std::string> & cmd_list);
	~SynchTool();
	PluginReturn Precall(std::shared_ptr<Parameters> params);
	PluginReturn Postcall(std::shared_ptr<Parameters> params);
	void SetThreadLocals();
private:
	std::shared_ptr<LogInfo> _sync_log;
	// std::map<int,std::string> _cmdToName;
	// size_t callcount;
	// std::map<CallID, bool> _transferCalls;
	boost::recursive_mutex _sync_mtx;
	// std::shared_ptr<LogInfo> _timeline_log;
	std::map<uint32_t, uint64_t> _pastTransfers;
	// uint64_t _count; 
	// bool _enabled;
};

#define PLUG_BUILD_FACTORY(param) \
	if (Worker.get() == NULL) { \
		Worker.reset(new SynchTool(param)); \
	} 

#define PLUG_FACTORY_PTR Worker.get()
