#pragma once
#include <vector>
#include "CheckAccesses.h"
#include "OutputWriter.h"


class LoadStoreDriver {
public:
	LoadStoreDriver(CheckAccessesPtr access);
	void RecordAccess(uint64_t id, uint64_t addr);
	void PushStack(uint64_t stack);
	void PopStack(uint64_t stack);
	void SyncCalled();
public:
	std::vector<uint64_t> _storedStack;
	OutputWriterPtr _writer;
	CheckAccessesPtr _access;
	bool _syncTriggered;
	bool _found;
};

