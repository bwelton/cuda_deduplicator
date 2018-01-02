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

class TimeApplications {
public:
	TimeApplications(boost::program_options::variables_map vm);
	double Run();
private:
	boost::program_options::variables_map _vm;
};