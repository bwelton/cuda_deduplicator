#include "LoadStoreDriver.h"

LoadStoreDriver::LoadStoreDriver(CheckAccessesPtr access) : _firstSync(true), _syncTriggered(false), _firstWrite(true), _found(false), _access(access) {
}

void LoadStoreDriver::RecordAccess(uint64_t id, uint64_t addr) {
	if (_syncTriggered && !_found) {
		if(_access->IsAddressProtected(addr)) {
			if (_firstWrite)
				_writer.reset(new OutputWriter());
			_firstWrite = false;
			_writer->RecordAccess(id,_storedStack);
			_found = true;
		}
	}
}

void LoadStoreDriver::PushStack(uint64_t stack) {
	_storedStack.push_back(stack);
}

bool LoadStoreDriver::ShouldSignalSync(bool inSync) {
	// This kludge is needed to catch cases where the low-level synchronize is called by 
	// a libcuda function more than once
	
	// No synchronization occured, return immediately.
	if (!inSync && _firstSync)
		return false;

	// Dont stop on the first sync, record the stack depth and continue.
	if(_firstSync) {
		_syncStackDepth = _storedStack.size();
		_firstSync = false;
		return false;
	} 

	// We have synchronized prior, check if we are a few stack positions away from
	// the low level synchronization.
	if (!inSync && _syncStackDepth >= _storedStack.size() + 3) {
		_firstSync = true;
		return true;
	}

	return false;
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
	if (ShouldSignalSync(false))
		SignalSync();
}

void LoadStoreDriver::SyncCalled() {
	ShouldSignalSync(true);
}

void LoadStoreDriver::SignalSync() {
	_access->SyncCalled();
	_found = false;
	_syncTriggered = true;
}