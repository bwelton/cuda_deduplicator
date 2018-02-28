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