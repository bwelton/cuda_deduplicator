#pragma once
#include <string.h>
#include <algorithm>
#include <functional>
#include <array>
#include <iostream>
#include <cassert>
#include <deque>
#include <sys/time.h>
#include <cstdlib>
#include <sstream>
#include <tuple>
#include <utility> 
#include <stdarg.h>
#include <map>
#include <set> 
#include <iomanip>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <mutex>
#include <fstream>
#include <boost/program_options.hpp>
#include "ProcessControl.h"
#include "SymbolLookup.h"
#include "StackPoint.h"
struct CallPoint {
	std::string libCudaCallname;
	std::vector<uint64_t> callStacks;
	double time;
	// Number of times this specific call synchronizes
	uint64_t syncCount;
	CallPoint(std::string name, uint64_t count, double t) {
		time = t;
		syncCount = count;
		libCudaCallname = name;
	}
};

class PerformanceModel {
public:
	PerformanceModel();
	void AddExecutionTime(double secs);
	void AddStack(std::vector<StackPoint> stack);
	void ExtractLineInfo();
	void ProcessStacks();
	void CaptureSyncTime();
	void GetTimingList(std::vector<StackPoint> & timingList);
private:
	double _fastestExecTime;
	uint64_t _totalSyncs;
	std::vector<uint64_t> _stackOrder;
	std::vector<CallPoint> _callPoints;
	std::map<uint64_t, uint64_t> _stackCount;
	std::map<uint64_t, std::vector<StackPoint> > _stackPoints;

	std::map<uint64_t, std::vector<std::pair<std::string, LineInfo> > > _lineInfo;
	std::map<uint64_t, std::tuple<std::string, std::string, std::string> > _callPair;

};