#include "StackStorage.h"

StackRecord::StackRecord() {}

StackRecord::StackRecord(uint64_t id, std::vector<StackPoint> & points) : _id(id), _points(points) {

}

StackPoint StackRecord::GetFirstCudaCall() {
	for (int i = _points.size() - 1; i >= 0; i = i - 1){
		if(_points[i].libname.find("libcuda.so") != std::string::npos){
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

void StackRecord::GetStackSymbols(SymbolMap & m) {
	for (int i = 0; i < _points.size(); i++) {
		if (m.find(_points[i].libname) == m.end())
			continue;
		std::pair<std::string, LineInfo> tmp;
		m[_points[i].libname]->GetInfoAtLocation(_points[i].libOffset, tmp);
		_points[i].funcOffset = m[_points[i].libname]->GetFunctionOffset(_points[i].libOffset);
		_points[i].funcName = m[_points[i].libname]->GetFuncName(_points[i].libOffset);
		_points[i].empty = false;
	}
#ifdef DEBUG_STACKRECORD
	std::cout << "[StackRecord] Decoded Stack for ID - " << _id << std::endl;
	for (auto i : _points)
		std::cout << "[StackRecord]\t" << i.funcName << "@" << i.libOffset << " in " << i.libname << std::endl;
#endif 
}