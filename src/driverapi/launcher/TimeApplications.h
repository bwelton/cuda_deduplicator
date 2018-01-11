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
#include <boost/program_options.hpp>
#include <numeric>
#include <chrono>
#include "ProcessControl.h"
#include "LogInfo.h"
class TimeApplications {
public:
	TimeApplications(boost::program_options::variables_map vm);
	double Run();
	double InternalRun();
	double RunWithInstrimentation(std::string wrapperDef);
private:
	boost::program_options::variables_map _vm;
};