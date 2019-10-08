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
#include <memory>
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
using namespace Dyninst;
using namespace ParseAPI;
using namespace PatchAPI;
using namespace SymtabAPI;
#include <vector>
#include <unordered_map>
#include <memory>
#include <unordered_set>
class BPatchBinary {
public:
	BPatchBinary(std::string binName, bool output = false, std::string outName = std::string(""));
	BPatch_image * GetImage();
	BPatch_addressSpace * GetAddressSpace();
	~BPatchBinary();
	std::vector<uint64_t> FindSyncCandidates();
private:
	BPatch_addressSpace * _as;
	BPatch_binaryEdit * _be;
	std::string _binName;
	bool _output;
	std::string _outName;
	BPatch bpatch;
};

struct FuncCFG{ 
	FuncCFG(BPatch_function * in) : func(in) {};
	std::unordered_set<std::shared_ptr<FuncCFG>> parents;
	std::unordered_set<std::shared_ptr<FuncCFG>> children;

	void InsertChild(std::shared_ptr<FuncCFG> child) {
		children.insert(child);
	}
	void InsertParent(std::shared_ptr<FuncCFG> par) {
		parents.insert(par);
	}
	BPatch_function * func; 
};

