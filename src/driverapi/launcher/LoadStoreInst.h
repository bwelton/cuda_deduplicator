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

using namespace Dyninst;
using namespace ParseAPI;
using namespace PatchAPI;
using namespace SymtabAPI;

#define StringVector std::vector<std::string>

namespace std
{
    template<> struct less<BPatch_object::Region>
    {
       bool operator() (const BPatch_object::Region& lhs, const BPatch_object::Region& rhs) const
       {
           return (uint64_t)lhs.base < (uint64_t)rhs.base;
       }
    };
}

class LoadStoreInst {
public: 
	LoadStoreInst(BPatch_addressSpace * addrSpace, BPatch_image * img);
	bool InstrimentAllModules(bool finalize) ;
	bool InstrimentNewModule(BPatch_object * obj, bool finalize);
	void Finalize();
	void BeginInsertionSet();
private:
	bool IsSkipUnlessCalled(BPatch_function * func, BPatch_object::Region reg);
	bool IsNeverInstriment(BPatch_function * func, BPatch_object::Region reg);
	BPatch_object::Region FindRegion(BPatch_function * func);
	void IdentifyRegions();
	void Setup();
	StringVector & GetSkipPaths();
	StringVector & GetSkipFunctions();
	StringVector & GetNeverInstrimentLibs();

	BPatch_image * _img;
	BPatch_addressSpace * _addrSpace;
	bool _started;

	uint64_t _funcId;
	std::map<uint64_t, std::string> _idToFunction;

	BPatch_function * _recordMemAccess;
	BPatch_function * _tracerFunction;

	std::map<BPatch_object::Region, std::pair<std::string,std::string> > _regionToLibname;
};