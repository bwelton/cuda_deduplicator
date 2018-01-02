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

using namespace Dyninst;
using namespace ParseAPI;
using namespace PatchAPI;
using namespace SymtabAPI;

class ProcessController {
public:
	ProcessController(boost::program_options::variables_map vm);
	BPatch_addressSpace * LaunchProcess();
	BPatch * GetBPatch();
	void Run();
	bool LoadWrapperLibrary(std::string libname);
	bool InsertInstrimentation(std::string WrapperDef);
	void ReadDefinition(std::string WrapperDef);
	void InstrimentApplication();
	std::set<std::string> WrapperLibraries();

	bool IsTerminated();
	bool ContinueExecution();
	bool IsStopped();
	void LibraryLoadCallback(BPatch_thread * thread, BPatch_object * obj, bool l);
private:
	double _instrimentationOverhead;
	BPatch bpatch;
	boost::program_options::variables_map _vm;
	BPatch_addressSpace * _addrSpace;
	bool _launched;
	bool _insertedInstrimentation;
	bool _terminated;
	std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string> > _wrapFunctions;
	BPatch_process * _appProc;
};