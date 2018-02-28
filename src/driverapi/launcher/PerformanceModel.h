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
class PerformanceModel {
public:
	PerformanceModel();
	void AddExecutionTime(double secs);
	void AddStack(std::vector<StackPoint> stack);
	void ExtractLineInfo();
private:
	double _fastestExecTime;
	std::vector<uint64_t> _stackOrder;
	std::map<uint64_t, uint64_t> _stackCount;
	std::map<uint64_t, std::vector<StackPoint> > _stackPoints;
	std::map<uint64_t, std::vector<std::pair<std::string, LineInfo> > > _lineInfo;
};