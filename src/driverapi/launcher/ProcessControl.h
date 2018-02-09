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

// Dyninst includes
#include "CodeObject.h"
#include "CFG.h"
#include "PatchObject.h"
#include "PatchMgr.h"
#include "Point.h"
#include "BPatch_object.h"
#include "BPatch_snippet.h"
#include "BPatch.h"
#include "BPatch_binaryEdit.h"
#include "BPatch_image.h"
#include "BPatch_function.h"
#include "BPatch_Vector.h"
#include "BPatch_point.h"
#include "BPatch_addressSpace.h"
#include "BPatch_statement.h"
#include "dynC.h"
#include "set"
#include "LogInfo.h"
#include "Constants.h"

using namespace Dyninst;
using namespace ParseAPI;
using namespace PatchAPI;
using namespace SymtabAPI;

struct StackPoint {
	std::string fname;
	std::string libname;
	uint64_t libOffset;
	uint64_t framePtr;
	bool empty;
	StackPoint() : empty(true), libOffset(0), framePtr(0), fname(std::string("")), libname(std::string("")) {

	};
	uint64_t GetKey() {
		return framePtr;
	};
};

namespace std {
	template<> struct less<StackPoint> {
		bool operator() (const StackPoint& lhs, const StackPoint& rhs) {
			return lhs.GetKey() < rhs.GetKey();
		}
	}
}


class ProcessController {
public:
	ProcessController(boost::program_options::variables_map vm, LogInfo * log );
	BPatch_addressSpace * LaunchProcess();
	BPatch_addressSpace * LaunchProcessInstrimenter(std::string WrapperDef);
	BPatch * GetBPatch();
	void Run();
	bool LoadWrapperLibrary(std::string libname);
	bool InsertInstrimentation(std::string WrapperDef);
	void ReadDefinition(std::string WrapperDef);
	void InstrimentApplication();
	std::set<std::string> WrapperLibraries();
	void InsertWrapperDef(std::string type, std::string origName, std::string wrapperFunc, std::string lib, std::string origSymbol);
	bool IsTerminated();
	bool ContinueExecution();
	bool IsStopped();
	void InsertBreakpoints(std::vector<std::string> functionNames);
	std::map<uint64_t, std::vector<StackPoint> > GetThreadStacks();
	
	//void LibraryLoadCallback(BPatch_thread * thread, BPatch_object * obj, bool l);
private:
	LogInfo * _log;
	double _instrimentationOverhead;
	boost::program_options::variables_map _vm;
	BPatch_addressSpace * _addrSpace;
	bool _launched;
	bool _insertedInstrimentation;
	bool _terminated;
	std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string> > _wrapFunctions;
	BPatch_process * _appProc;
	std::map<std::string, BPatch_object *> _loadedLibraries;
};