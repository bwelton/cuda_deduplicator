#pragma once
#include <string>
#include <map> 
#include <utility>
#include <algorithm>
#include <boost/tokenizer.hpp>
#include <boost/filesystem.hpp>
#include <fstream>
#include "StackPoint.h"

class BinaryLocationIDMap {
public:
	BinaryLocationIDMap();
	uint64_t StorePosition(std::string & libname, uint64_t offsetAddr);
	uint64_t GetOffsetForID(uint64_t id);
	std::string * GetLibnameForID(uint64_t id);
	StackPoint BuildStackPoint(uint64_t id);
	void WriteMap(std::string outdir);
	void ReadMap(std::string indir);
private:
	uint64_t _curPos, _libids;
	std::map<uint64_t,std::pair<uint64_t, uint64_t>> _idToLibOffset;
	std::map<std::string, uint64_t> _libnameToLibID;
	std::map<uint64_t,std::string> _libIdtoLibname;
};
