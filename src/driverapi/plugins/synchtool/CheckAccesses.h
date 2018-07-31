#pragma once
#include <vector>
#include <memory>
#include "MemoryRange.h"

class CheckAccesses {
public:
	CheckAccesses();
	void AddMemoryTransfer(MemoryRange & range);
	void SyncCalled();
	bool IsAddressProtected(uint64_t addr);
	void AddUnifiedMemRange(MemoryRange & range);
	void RemoveUnifiedMemoryRange(MemoryRange & range);
private:
	std::vector<MemoryRange> _prev;
	std::vector<MemoryRange> _current;	
	std::vector<MemoryRange> _unifiedMemory;	
	bool _doNotCheck;
};

typedef std::shared_ptr<CheckAccesses> CheckAccessesPtr;

