#include "CheckAccesses.h"
CheckAccesses::CheckAccesses() : _doNotCheck(false) {};

void CheckAccesses::AddMemoryTransfer(MemoryRange & range) {
	_doNotCheck = true;
	_current.push_back(range);
	_doNotCheck = false;
}

void CheckAccesses::SyncCalled() {
	_prev = _current;
}

bool CheckAccesses::IsAddressProtected(uint64_t addr) {
	if (_doNotCheck)
		return false;
	for (auto i : _prev)
		if(i.IsInRange(addr))
			return true;
	return false;
}
