#include "OutputWriter.h"

OutputWriter::OutputWriter() : _curPos(1) {
	_accessFile.reset(new OutputFile(std::string("LS_trace.bin")));
	_stackKeyFile.reset(new StackKeyWriter(fopen("LS_stackkey.bin", "w")));
}

void OutputWriter::RecordAccess(uint64_t id, std::vector<StackPoint> & currentStack) {
	// uint64_t hash = HashStack(currentStack);
	// if (_prevStacks.find(hash) == _prevStacks.end()) {
	// 	_stackKeyFile->Write(_curPos, currentStack);
	// 	_prevStacks[hash] = _curPos;
	// }
	uint64_t idKey = _stackKeyFile->InsertStack(currentStack);
	_accessFile->Write(id, idKey);
}

uint64_t OutputWriter::HashStack(std::vector<uint64_t> & currentStack) {
	std::stringstream ss;
	for (auto i : currentStack)
		ss << i << ",";
	return std::hash<std::string>()(ss.str());	
}