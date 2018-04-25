#pragma once
#include <vector>
#include <memory>
#include "CheckAccesses.h"
#include "OutputWriter.h"

class LoadStoreDriver {
public:
	LoadStoreDriver(CheckAccessesPtr access);
	void RecordAccess(uint64_t id, uint64_t addr);
	void PushStack(uint64_t stack);
	void PopStack(uint64_t stack);
	bool ShouldSignalSync(bool inSync);
	void SyncCalled();
	void SignalSync();
private:
	std::vector<uint64_t> _storedStack;
	std::vector<uint64_t> _stackAtSync;
	OutputWriterPtr _writer;
	CheckAccessesPtr _access;
	bool _syncTriggered;
	bool _found;
	bool _firstWrite;
	bool _firstSync;
	uint64_t _syncStackDepth;
};

typedef std::shared_ptr<LoadStoreDriver> LoadStoreDriverPtr;