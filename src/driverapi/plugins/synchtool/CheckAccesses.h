#pragma once
#include <vector>
#include <memory>
#include "MemoryRange.h"
#include <boost/icl/interval_set.hpp>
#include <boost/icl/interval.hpp>
using namespace boost::icl;

class CheckAccesses {
public:
	CheckAccesses();
	void AddMemoryTransfer(MemoryRange & range);
	void SyncCalled();
	bool IsAddressProtected(uint64_t addr);
	bool IsAddressRangeProtected(uint64_t addr, uint64_t count);
	void AddUnifiedMemRange(MemoryRange & range);
	void RemoveUnifiedMemoryRange(MemoryRange & range);
private:
	std::vector<MemoryRange> _prev;
	std::vector<MemoryRange> _current;	
	std::vector<MemoryRange> _unifiedMemory;	
	bool _doNotCheck;
	interval_set<uint64_t> _memoryRanges;
	interval_set<uint64_t> _memoryRangesPrev;
	bool _reset;
};

typedef std::shared_ptr<CheckAccesses> CheckAccessesPtr;

