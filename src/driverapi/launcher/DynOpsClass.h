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
#include "BPatch_basicBlock.h"
#include "dynC.h"
#include "set"
#include "LogInfo.h"
#include "Constants.h"
#include "StackPoint.h"
#include "StackStorage.h"
#include "BinaryRewriter.h"
#include "BPatchBinary.h"

using namespace Dyninst;
using namespace ParseAPI;
using namespace PatchAPI;
using namespace SymtabAPI;

// Perform common operations on dyninst objects
class DynOpsClass {
public:
	DynOpsClass();
	int FindFuncByStackPoint(BPatch_addressSpace * aspace, BPatch_function * & ret, StackPoint & point);
	int FindFuncByName(BPatch_addressSpace * aspace, BPatch_function * & ret, std::string name);
	int FindFuncByLibnameOffset(BPatch_addressSpace * aspace, BPatch_function * & ret, std::string libname, uint64_t offset, bool exact = true);
	BPatch_object * FindObjectByName(BPatch_addressSpace * aspace, std::string & name, bool exact = true);
	bool GetFileOffset(BPatch_addressSpace * aspace, BPatch_point * point, uint64_t & addr, bool addInstSize = false);
	Dyninst::InstructionAPI::Instruction::Ptr FindInstructionAtPoint(BPatch_point * point);
	std::vector<std::string> GetLibraryNames(BPatch_addressSpace * aspace);
	BPatch_function * FindFunctionByOffset(BPatch_addressSpace * aspace, BPatch_object * obj, uint64_t offset);
	int FindFunctionInLibrary(BinaryRewriter * _rw, BPatch_function *& ret,  std::string fname, std::string libname);
};
