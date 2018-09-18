#include "BinaryLocationIDMap.h"
BinaryLocationIDMap::BinaryLocationIDMap() : _curPos(1), _libids(1) {

}
uint64_t BinaryLocationIDMap::StorePosition(std::string & libname, uint64_t offsetAddr) {
	if (_libnameToLibID.find(libname) == _libnameToLibID.end()) {
		_libnameToLibID[libname] = _libids;
		_libIdtoLibname[_libids] = libname;
		_libids++;
	}
	_idToLibOffset[_curPos] = std::make_pair(_libnameToLibID[libname], offsetAddr);
	_curPos++;
	return _curPos - 1;
}

uint64_t BinaryLocationIDMap::GetOffsetForID(uint64_t id) {
	if (_idToLibOffset.find(id) != _idToLibOffset.end())
		return _idToLibOffset[id].second;
	return 0;
}

bool BinaryLocationIDMap::SetAbsoluteID(uint64_t id, std::string & libname, uint64_t offsetAddr) {
	if (_libnameToLibID.find(libname) == _libnameToLibID.end()) {
		_libnameToLibID[libname] = _libids;
		_libIdtoLibname[_libids] = libname;
		_libids++;
	}
	if (_idToLibOffset.find(id) != _idToLibOffset.end())
		assert("WE SHOULD NEVER BE HERE" != 0);
	_idToLibOffset[id] = std::make_pair(_libnameToLibID[libname], offsetAddr);		
	return true;
}

std::string * BinaryLocationIDMap::GetLibnameForID(uint64_t id) {
	if (_idToLibOffset.find(id) != _idToLibOffset.end())
		if (_libIdtoLibname.find(_idToLibOffset[id].first) != _libIdtoLibname.end())
			return &(_libIdtoLibname[_idToLibOffset[id].first]);
	return (std::string *)NULL;
}

StackPoint BinaryLocationIDMap::BuildStackPoint(uint64_t id) {
	StackPoint ret;
	ret.libOffset = GetOffsetForID(id);
	ret.libname = *GetLibnameForID(id);
	return ret;
}

void BinaryLocationIDMap::DumpLocationMap(std::string outFile) {
	std::ofstream dumpIDMap;
	dumpIDMap.open(outFile.c_str(), std::ofstream::out);

	std::for_each(_libnameToLibID.begin(), _libnameToLibID.end(), [&dumpIDMap](std::map<uint64_t,std::string>::iterator & i) {dumpIDMap << i->first <<"," << i->second << std::endl;});
	dumpIDMap << "EndOfHeader" << std::endl;
	std::for_each(_idToLibOffset.begin(), _idToLibOffset.end(), [&dumpIDMap](std::map<uint64_t,std::pair<uint64_t, uint64_t>>::iterator & i) {dumpIDMap << i->first <<"," << i->second.first << "," << i->second.second << std::endl;});
	dumpIDMap.close();
}