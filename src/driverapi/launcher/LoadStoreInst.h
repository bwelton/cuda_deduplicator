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

#define StringVector std::vector<std::string>
#define INTERNAL_SYNC_LS 0x2864C0


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

enum InstType {
	LOAD_STORE_INST = 0,
	CALL_TRACING
};


class BinaryLocationIDMap {
public:
	BinaryLocationIDMap();
	uint64_t StorePosition(std::string & libname, uint64_t offsetAddr);
	uint64_t GetOffsetForID(uint64_t id);
	std::string * GetLibnameForID(uint64_t id);
private:
	uint64_t _curPos, _libids;
	std::map<uint64_t,std::pair<uint64_t, uint64_t>> _idToLibOffset;
	std::map<std::string, uint64_t> _libnameToLibID;
	std::map<uint64_t,std::string> _libIdtoLibname;
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


class LoadStoreInst {
public: 
	LoadStoreInst(BPatch_addressSpace * addrSpace, BPatch_image * img);
	bool InstrimentAllModules(bool finalize, std::vector<uint64_t> & skips, uint64_t & instUntil, std::vector<std::string> & syncFunctions, std::vector<StackPoint> & points);
	bool InstrimentNewModule(BPatch_object * obj, bool finalize);
	void Finalize();
	void BeginInsertionSet();
	bool RunOneTimeCode();
	void SetWrappedFunctions(std::vector<std::string> & wrappedFunctions);
	std::map<uint64_t, StackPoint> _firstUses;
	void WrapEntryAndExit();
	void InsertSyncNotifierSnippet(BPatch_function * func, uint64_t offset);
	void InsertSyncCallNotifier(std::vector<StackPoint> & points);
private:
	bool IsSkipUnlessCalled(BPatch_function * func, BPatch_object::Region reg);
	bool IsNeverInstriment(BPatch_function * func, BPatch_object::Region reg);
	bool IsSkipExact(BPatch_function * func);
	BPatch_object::Region FindRegion(BPatch_function * func);
	void IdentifyRegions();
	void Setup();
	StringVector & GetSkipPaths();
	StringVector & GetSkipFunctions();
	StringVector & GetNeverInstrimentLibs();
	StringVector & SkipExact();
	void InsertEntryExitSnippets(BPatch_function * func, std::vector<BPatch_point*> * points);
	BPatch_image * _img;
	BPatch_addressSpace * _addrSpace;
	bool _started;
	bool _runOneTime;
	std::vector<std::string> _wrappedFunctions;
	uint64_t _funcId;
	std::map<uint64_t, std::string> _idToFunction;

	BPatch_function * _recordMemAccess;
	BPatch_function * _tracerFunction;
	BPatch_function * _endFuncCall;
	BPatch_function * _enterSync;
	BPatch_function * _exitSync;
	BPatch_function * _syncLibNotify;

	BPatch_function * _entryFunction;
	BPatch_function * _exitingFunction;

	BinaryLocationIDMap _binLoc;
	InstrimentationTracker _instTracker;
	std::map<BPatch_object::Region, std::pair<std::string,std::string> > _regionToLibname;
};