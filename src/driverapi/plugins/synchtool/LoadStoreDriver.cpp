#include "LoadStoreDriver.h"

LoadStoreDriver::LoadStoreDriver(CheckAccessesPtr access) :  _syncTriggered(false), _found(false), _access(access) {
	_writer.reset(new OutputWriter());
}

void LoadStoreDriver::RecordAccess(uint64_t id, uint64_t addr) {
	if (_syncTriggered && !_found) {
		if(_access->IsAddressProtected(addr)) {
			_writer->RecordAccess(id,_storedStack);
			_found = true;
		}
	}
}

void LoadStoreDriver::PushStack(uint64_t stack) {
	_storedStack.push_back(stack);
}

void LoadStoreDriver::PopStack(uint64_t stack) {
	if (_storedStack.back() == stack) 
		_storedStack.pop_back();
	else {
		for (int i = _storedStack.size() - 1; i >= 0; i = i - 1) {
			if (_storedStack[i] == stack){
				_storedStack.erase(_storedStack.begin() + i);
				break;
			}
		}
	}
}
void LoadStoreDriver::SyncCalled() {
	_access->SyncCalled();
	_found = false;
	_syncTriggered = true;
}