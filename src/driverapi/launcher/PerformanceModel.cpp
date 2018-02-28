#include "PerformanceModel.h"

PerformanceModel::PerformanceModel() : _fastestExecTime(std::numeric_limits<double>::max()) {

}

void PerformanceModel::AddExecutionTime(double secs) {
	if (secs < _fastestExecTime) {
		std::cerr << "[PerfModel] Updating lowest execution time - " << _fastestExecTime << "=>" << secs << std::endl;
		_fastestExecTime = secs;
	}
}

void PerformanceModel::AddStack(std::vector<StackPoint> stack) {
	std::stringstream ss;
	for (auto z : stack) {
		ss << z.framePtr << std::endl;
	}
	uint64_t hash = std::hash<std::string>()(ss.str());
	_stackOrder.push_back(hash);
	if (_stackCount.find(hash) == _stackCount.end())
		_stackCount[hash] = 0;
	_stackCount[hash] += 1;
	if (_stackPoints.find(hash) == _stackPoints.end())
		_stackPoints[hash] = stack;	
}

void PerformanceModel::ExtractLineInfo() {
	std::map<std::string, std::shared_ptr<SymbolLookup> > symbolInfo;
	
	// Open all symtabs for functions found on the stack. 
	for (auto i : _stackPoints) {
		for (auto z : i.second){
			if (symbolInfo.find(z.libname) == symbolInfo.end())
				symbolInfo[z.libname] = std::shared_ptr<SymbolLookup>(new SymbolLookup(z.libname));
		}	
	}

	// Decode line info for every stack
	for (auto i : _stackPoints) {
		_lineInfo[i.first] = std::vector<std::pair<std::string, LineInfo> >();
		for(auto z : i.second) {
			// Convert to line info and add  to _lineInfo
		}
	}
}