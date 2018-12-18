#include "OutputWriter.h"

OutputWriter::OutputWriter(bool timeType) : _curPos(1), _timeType(timeType) {
	if (timeType == false) {
		_accessFile.reset(new OutputFile(std::string("LS_trace.bin")));
		_stackKeyFile.reset(new OutputFile(std::string("LS_stackkey.bin")));
	} else {
		_firstUse.reset(new OutputFile(std::string("FI_stackkey.bin")));
		_timingValues.reset(new OutputFile(std::string("FI_trace.bin")));
	}
}

void OutputWriter::RecordAccess(uint64_t id, std::vector<uint64_t> & currentStack, double timeID) {
	uint64_t hash = HashStack(currentStack);
	if (_prevStacks.find(hash) == _prevStacks.end()) {
		if (_timeType == false)
			_stackKeyFile->Write(_curPos, currentStack);
		else 
			_firstUse->Write(_curPos, currentStack);
		_prevStacks[hash] = _curPos;
		_curPos++;
	}
	if (_timeType == false) {
		_accessFile->Write(id, _prevStacks[hash]);
	} else {
		_timingValues->Write(id, _prevStacks[hash], timeID);
	}
}

uint64_t OutputWriter::HashStack(std::vector<uint64_t> & currentStack) {
	std::stringstream ss;
	for (auto i : currentStack)
		ss << i << ",";
	return std::hash<std::string>()(ss.str());	
}