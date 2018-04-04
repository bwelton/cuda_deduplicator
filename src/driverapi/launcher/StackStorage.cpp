#include "StackStorage.h"



StackRecord::StackRecord() {}

StackRecord::StackRecord(uint64_t id, std::vector<StackPoint> & points) : _id(id), _points(points) {

}

StackPoint StackRecord::GetFirstCudaCall() {
	for (int i = _points.size() - 1; i >= 0; i = i - 1){
		if(_points[i].libname.find("libcuda.so") != std::string::npos){
			_points[i].empty = false;
#ifdef DEBUG_STACKRECORD
			std::cout << "[StackRecord] First entry into libcuda for Stack Record " << _id << " is " << _points[i].funcName << std::endl;
#endif
			return _points[i];
		}
	}	
	StackPoint empty;
	empty.empty = true;
	return empty;
}

void StackRecord::AddStackRecord(uint64_t pos) {
	if (_ranges.size() == 0){
		_ranges.push_back(SyncRangeRecord(pos));
		return;
	}
	if (_ranges.back().ExtendRange(pos) == false) {
		_ranges.push_back(SyncRangeRecord(pos));
	}
}

// void StackRecord::AddTimingData(uint64_t start, uint64_t len, double time) {
// 	_timingData.push_back(TimingData(start, len, time));
// }

std::vector<std::string> StackRecord::GetLibNames() {
	std::vector<std::string> ret;
	for (auto i : _points) {
		ret.push_back(i.libname);
	}
	return ret;
}

void StackRecord::GetStackSymbols(SymbolMap & m) {
	for (int i = 0; i < _points.size(); i++) {
		if (m.find(_points[i].libname) == m.end())
			continue;
		std::pair<std::string, LineInfo> tmp;
		m[_points[i].libname]->GetInfoAtLocation(_points[i].libOffset, tmp);
		//std::cerr << _points[i].libname << " " << _points[i].libOffset << std::endl;
		_points[i].funcOffset = m[_points[i].libname]->GetFunctionOffset(_points[i].libOffset);
		_points[i].funcName = m[_points[i].libname]->GetFuncName(_points[i].libOffset);
		_points[i].empty = false;
	}
#ifdef DEBUG_STACKRECORD
	std::cout << "[StackRecord] Decoded Stack for ID - " << _id << std::endl;
	for (auto i : _points)
		std::cout << "[StackRecord]\t" << i.funcName << "@" << i.funcOffset << " in " << i.libname << std::endl;
#endif 
}


CudaCallMap::CudaCallMap() : _pos(1) {
	_nameToGeneralID[std::string("unknown")] = 0;
	_stackToGeneral[0] = 0;
}

void CudaCallMap::InsertStackID(std::string s, uint64_t id) {
	if (_nameToGeneralID.find(s) == _nameToGeneralID.end()){
		_nameToGeneralID[s] = _pos;
		_stackToGeneral[id] = _pos;
		_pos++;
	} else {
		_stackToGeneral[id] = _nameToGeneralID[s];
	}
}

std::string CudaCallMap::GeneralToName(uint64_t id) {
	for (auto i : _nameToGeneralID)
		if (i.second == id)
			return i.first;
	return std::string("");
}

uint64_t CudaCallMap::StackIDToGeneral(uint64_t id) {
	if (_stackToGeneral.find(id) == _stackToGeneral.end())
		assert(1 == 0);
	return _stackToGeneral[id];
}

uint64_t CudaCallMap::NameToGeneral(std::string s) {
	if (_nameToGeneralID.find(s) == _nameToGeneralID.end())
		assert(1 == 0);
	return _nameToGeneralID[s];
}

