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
#include "BPatch_basicBlock.h"
#include "BPatch_binaryEdit.h"
#include "BPatch_image.h"
#include "BPatch_function.h"
#include "BPatch_Vector.h"
#include "BPatch_point.h"
#include "BPatch_addressSpace.h"
#include "BPatch_statement.h"
using namespace Dyninst;
using namespace ParseAPI;
using namespace PatchAPI;
using namespace SymtabAPI;

#define StringVector std::vector<std::string>
enum InstType {
	LOAD_STORE_INST = 0,
	CALL_TRACING
};


class InstrimentationTracker {
public:
	InstrimentationTracker();
	void AddAlreadyInstrimented(std::vector<std::string> & wrappedFunctions);
	bool ShouldInstriment(BPatch_function * func, std::vector<BPatch_point *> * points, InstType t);
private:

	uint64_t HashPoint(BPatch_function * func, BPatch_point * point);
	bool ShouldInstrimentFunciton(BPatch_function * func, InstType t);
	bool ShouldInstrimentModule(BPatch_function * func, InstType t);
	std::vector<std::string> _prevWrappedFunctions;
	std::map<InstType, std::set<uint64_t> > _alreadyInstrimented;
};
