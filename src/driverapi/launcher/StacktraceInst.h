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
#include <queue>
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
#include "StackPoint.h"
using namespace Dyninst;
using namespace ParseAPI;
using namespace PatchAPI;
using namespace SymtabAPI;

#define INTERNAL_SYNC_ST 0x2864C0
typedef std::pair<uint64_t, BPatch_function *> FuncIDPair;
class StacktraceInst {
public:
	StacktraceInst(BPatch_addressSpace * addrSpace, BPatch_image * img);
	void Setup();
	bool IsFunctionExcluded(BPatch_function * func);
	void InsertStackInst();
	uint64_t GetFuncId(BPatch_function * func);
	void InsertEntryExitCall(BPatch_function * instFunc, BPatch_function * calledFunc, BPatch_point * callPoint);
	std::vector<std::pair<BPatch_function *, BPatch_point *> > GetFunctionCalls(BPatch_function * func);
	void InsertInstFuncEntryExit(BPatch_function * instFunc);
private:
	BPatch_function * _entryFunc;
	BPatch_function * _exitFunc;
	BPatch_function * _recordSync;
	BPatch_function * _atEntryFunc;
	BPatch_function * _atExitFunc;

	BPatch_addressSpace * _addrSpace;
	BPatch_image * _img;

	// Stores the current id
	uint64_t _curID;
	// Offset to <bpatch_function, id> map
	std::map<uint64_t, FuncIDPair > _idMap; 
};