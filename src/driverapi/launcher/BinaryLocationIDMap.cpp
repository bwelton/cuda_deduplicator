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


std::vector<std::string> GetTokensFromLine(std::string line, std::string seperator) {
	std::vector<std::string> ret;
	boost::char_separator<char> seperators(seperator.c_str());
	boost::tokenizer<boost::char_separator<char>> tokens(line, seperators);
    for (const auto& t : tokens) {
    	ret.push_back(std::string(t));
    }
    return ret;
}

void BinaryLocationIDMap::ReadMap(std::string indir) {
	boost::filesystem::path libBin(indir);
	boost::filesystem::path libKey(indir);
	
	libBin /= "BM_library.bin";
	libKey /= "BM_library.key";
	std::ifstream bin(libBin.string(), std::ios::binary);
	std::ifstream key(libKey.string(), std::ios::binary);

	for (std::string line; std::getline(key, line); ){
		std::vector<std::string> items = GetTokensFromLine(line, std::string("$"));
		assert(items.size() == 2);
		_libnameToLibID[items[1]] = std::stoull(items[0]);
		_libIdtoLibname[std::stoull(items[0])] = items[1];
	}

	key.close();
	while (!bin.eof()) {
		uint16_t libId = 0;
		uint64_t iden = 0;
		uint64_t offset = 0;
		bin.read((char *)&libId, sizeof(uint16_t));
		if (bin.eof())
			break;
		bin.read((char *)&offset, sizeof(uint64_t));
		bin.read((char *)&iden, sizeof(uint64_t));
		_idToLibOffset[iden] = std::make_pair(uint64_t(libId), offset);
	} 
	bin.close();
}

void BinaryLocationIDMap::WriteMap(std::string outdir) {
	// libraryNameId,Libname = BM_library.key (txt)
	// libraryNameId(uint16_t),offset(uint64_t),libid(uint64_t) = BM_library.bin
	boost::filesystem::path libBin(outdir);
	boost::filesystem::path libKey(outdir);
	
	libBin /= "BM_library.bin";
	libKey /= "BM_library.key";
	std::ofstream bin(libBin.string(), std::ios::binary);
	std::ofstream key(libKey.string(), std::ios::binary);

	for (auto i : _libIdtoLibname) {
		assert(i.first < std::numeric_limits<uint16_t>::max());
		key << i.first << "$" << i.second << std::endl;
	}
	key.close();

	for (auto i : _idToLibOffset) {
		uint64_t iden = i.first;
		uint16_t libId = uint16_t(i.second.first);
		uint64_t offset =  i.second.second;
		bin.write((char *)&libId, sizeof(uint16_t));
		bin.write((char *)&offset, sizeof(uint64_t));
		bin.write((char *)&iden, sizeof(uint64_t));
	}
	bin.close();

}