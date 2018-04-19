#include "CheckAccesses.h"
CheckAccesses::CheckAccesses() {};

void CheckAccesses::AddMemoryTransfer(MemoryRange & range) {
	_current.push_back(range);
}

void CheckAccesses::SyncCalled() {
	_prev = _current;
}

bool CheckAccesses::IsAddressProtected(uint64_t addr) {
	for (auto i : _prev)
		if(i.IsInRange(addr))
			return true;
	return false;
}
