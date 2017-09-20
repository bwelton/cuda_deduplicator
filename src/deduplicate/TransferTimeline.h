#pragma once
#include <memory>
#include <iostream>
#include <set>
#include "LogInfo.h"
#include <sstream> 
#include <boost/thread/recursive_mutex.hpp>

class TransferTimeline{
public:
	TransferTimeline();
	~TransferTimeline();
	void Write(std::string a);
	void AddTransfer(std::string type, uint32_t id, size_t size);
	void WriteLogEntry(std::string & type, uint32_t id, size_t size, uint64_t count, uint64_t origTransfer);
private:
	boost::recursive_mutex _timeline_mtx;
	std::shared_ptr<LogInfo> _timeline_log;
	std::map<uint32_t, uint64_t> _pastTransfers;
	uint64_t _count; 
};
