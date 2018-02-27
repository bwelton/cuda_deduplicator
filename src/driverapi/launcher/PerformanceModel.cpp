#include "PerformanceModel.h"

PerformanceModel::PerformanceModel() : _fastestExecTime(std::numeric_limits<double>::max()) {

}

void PerformanceModel::AddExecutionTime(double secs) {
	if (secs < _fastestExecTime) {
		std::cerr << "[PerfModel] Updating lowest execution time - " << _fastestExecTime << "=>" << secs << std::endl;
		_fastestExecTime = secs;
	}
}