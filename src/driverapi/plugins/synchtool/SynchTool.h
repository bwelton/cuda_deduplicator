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
#include <errno.h>
#include <sys/mman.h>
#include <signal.h>
#include <sstream>

#define SYNCH_DEBUG 1

extern "C" {
	void init(std::vector<std::string> & cmd_list);
	PluginReturn Precall(std::shared_ptr<Parameters> params);
	PluginReturn Postcall(std::shared_ptr<Parameters> params);
}

struct MemoryRange {
	uint64_t begin;
	uint64_t end; 
	uint64_t size; 
	uint64_t transferID;
	uint64_t unifiedMemory;
	int stream;
};

class SynchTool {
public:
	SynchTool(std::vector<std::string> & cmd_list);
	~SynchTool();
	PluginReturn Precall(std::shared_ptr<Parameters> params);
	PluginReturn Postcall(std::shared_ptr<Parameters> params);
	void UnifiedAllocation(std::shared_ptr<Parameters> params);
	void GetLiveTransfer(std::shared_ptr<Parameters> params);
	void MemoryFree(std::shared_ptr<Parameters> params);
	void SignalToParent(uint64_t stream);
	void ClearExisting(uint64_t stream);
	uint64_t * SeralizeMemRanges(size_t & size);
	void UnprotectMemory();
	void MemProtectAddrs();
	void SetThreadLocals();
	void RecordSynchronization(uint64_t id);
private:
	std::shared_ptr<LogInfo> _sync_log;
	std::map<uint64_t, MemoryRange> _ranges;
	std::map<uint64_t, size_t> _protectedMem;
	// std::map<int,std::string> _cmdToName;
	// size_t callcount;
	// std::map<CallID, bool> _transferCalls;
	boost::recursive_mutex _sync_mtx;
	// std::shared_ptr<LogInfo> _timeline_log;
	std::map<uint32_t, uint64_t> _pastTransfers;
	std::set<CallID> _callsContainingSynch;
	std::vector<std::string> _cmd_list;
	// uint64_t _count; 
	// bool _enabled;
};

#define PLUG_BUILD_FACTORY(param) \
	if (Worker.get() == NULL) { \
		Worker.reset(new SynchTool(param)); \
	} 

#define PLUG_FACTORY_PTR Worker.get()
