#include "LoadStoreInst.h"

LoadStoreInst::LoadStoreInst(BPatch_addressSpace * addrSpace, BPatch_image * img) :
	_addrSpace(addrSpace), _img(img), _started(false), _funcId(0) {
	

}

void LoadStoreInst::SetWrappedFunctions(std::vector<std::string> & wrappedFunctions ) {
	_wrappedFunctions = wrappedFunctions;
}


bool LoadStoreInst::InstrimentAllModules(bool finalize, std::vector<uint64_t> & skips, uint64_t & instUntil, std::vector<std::string> & syncFunctions) {
	Setup();

	std::stringstream ss;
	// Parameters for Record Memory Function
	std::vector<BPatch_snippet*> recordArgs;
	BPatch_snippet * loadAddr = new BPatch_effectiveAddressExpr();
	BPatch_snippet * instAddr = new BPatch_originalAddressExpr();
	recordArgs.push_back(loadAddr);
	recordArgs.push_back(instAddr);
	BPatch_funcCallExpr recordAddrCall(*_recordMemAccess, recordArgs);

	BeginInsertionSet();

	IdentifyRegions();

	// Get all the functions in the binary
	std::vector<BPatch_function *> all_functions;
	_img->getProcedures(all_functions);

	std::set<uint64_t> alreadyInstrimented;
	std::set<uint64_t> alreadyScheduled;
	std::queue<BPatch_function *> funcsToInstriment;

	// Find all functions that are in user generated code, this is our base to start instrimentation.
	for (auto x : all_functions) {
		// First get the region for this function, should only be 1.
		BPatch_object::Region funcRegion = FindRegion(x);
		if (IsNeverInstriment(x, funcRegion) || IsSkipUnlessCalled(x, funcRegion)) {
			continue;
		}
		alreadyScheduled.insert((uint64_t)x->getBaseAddr());

		funcsToInstriment.push(x);
	}

	std::cerr << "We will be starting instrimentation with " << funcsToInstriment.size() << " functions" << std::endl;

	std::vector<BPatch_point *> points; 

	std::set<BPatch_opCode> axs;
	axs.insert(BPatch_opLoad);
	axs.insert(BPatch_opStore);

	while (funcsToInstriment.empty() == false) {
		if (_funcId == instUntil && instUntil != 0)
			break;
		BPatch_function * x = funcsToInstriment.front();
		funcsToInstriment.pop();


		if (IsSkipExact(x))
			alreadyInstrimented.insert((uint64_t)x->getBaseAddr());

		if (alreadyInstrimented.find((uint64_t)x->getBaseAddr()) != alreadyInstrimented.end())
			continue;
		
		alreadyInstrimented.insert((uint64_t)x->getBaseAddr());
		BPatch_object::Region funcRegion = FindRegion(x);
		if (IsNeverInstriment(x, funcRegion)) {
			continue;
		}

		if (std::find(skips.begin(), skips.end(), _funcId) != skips.end()){
			_funcId+= 1;
			continue;
		}

		std::cerr << "Inserting instrimentation into function - " << x->getName() << std::endl;
		// Insert function tracing
		//{
			std::vector<BPatch_point*> * funcEntry = x->findPoint(BPatch_locEntry);
			std::vector<BPatch_snippet*> testArgs;
			testArgs.push_back(new BPatch_constExpr(_funcId));
			BPatch_funcCallExpr recordFuncEntry(*_tracerFunction, testArgs);
			std::cerr << x->getName() << "," << _funcId << std::endl;
			if (_addrSpace->insertSnippet(recordFuncEntry,*funcEntry) == NULL) 
				std::cerr << "could not insert func entry snippet" << std::endl;
		//}
		{
			// std::vector<BPatch_point*> * FuncExit = x->findPoint(BPatch_locExit);
			// std::vector<BPatch_snippet*> testArgs;
			// testArgs.push_back(new BPatch_constExpr(_funcId));
			// BPatch_funcCallExpr recordFuncExit(*_endFuncCall, testArgs);
			// //std::cerr << x->getName() << "," << _funcId << std::endl;
			// if (_addrSpace->insertSnippet(recordFuncExit,*FuncExit) == NULL) 
			// 	std::cerr << "could not insert func exit snippet" << std::endl;
		}
		_idToFunction[_funcId] = std::string(x->getName());
		_funcId += 1;		


		// Insert load store instrimentation
		std::vector<BPatch_point*> * tmp = x->findPoint(axs);
		if (tmp != NULL){
			points.insert(points.end(), tmp->begin(), tmp->end());
			std::cerr << "Inserting Load/Store Instrimentation into : " << x->getName() << std::endl;
			if (points.size() >= 1)
				if (_addrSpace->insertSnippet(recordAddrCall, points) == NULL) 
					std::cerr << "could not insert snippet" << std::endl;
			points.clear();
		} else {
			std::cerr << "Could not find any load/stores for function : " << x->getName() << std::endl;
		}

		// Instriment all functions that we call.
		std::vector<BPatch_point*> * funcCalls = x->findPoint(BPatch_locSubroutine);
		if (funcCalls != NULL) {
			for (auto y : *funcCalls) {
				BPatch_function * calledFunction = y->getCalledFunction();
				if (calledFunction != NULL){
					if (alreadyInstrimented.find((uint64_t)calledFunction->getBaseAddr()) == alreadyInstrimented.end() && 
						alreadyScheduled.find((uint64_t)calledFunction->getBaseAddr()) == alreadyScheduled.end())
						funcsToInstriment.push(calledFunction);
				}
			}
		} else {
			std::cerr << "Could not find any function calls in : " << x->getName() << std::endl;
		}		
	}

	// Add Wappers to Sync Functions if they exist:

	for (auto i : syncFunctions){
		if(std::find(_wrappedFunctions.begin(), _wrappedFunctions.end(),i ) != _wrappedFunctions.end())
			continue;
		std::cerr << "We need to wrap function - " << i << std::endl;
	}
	instUntil = _funcId;
	if (finalize)
		Finalize();

	return true;
}

bool LoadStoreInst::IsSkipUnlessCalled(BPatch_function * func, BPatch_object::Region reg) {
	StringVector neverLibs = GetSkipPaths();
	for (auto x : neverLibs)
		if (_regionToLibname[reg].first.find(x) != std::string::npos || _regionToLibname[reg].second.find(x) != std::string::npos)
			return true;	
	return false;
}

bool LoadStoreInst::IsNeverInstriment(BPatch_function * func, BPatch_object::Region reg) {
	StringVector neverLibs = GetNeverInstrimentLibs();
	StringVector neverFuncs = GetSkipFunctions();

	for (auto x : neverLibs)
		if (_regionToLibname[reg].first.find(x) != std::string::npos || _regionToLibname[reg].second.find(x) != std::string::npos)
			return true;
	std::string funcName = func->getName();

	for (auto x : neverFuncs)
		if (funcName.find(x) != std::string::npos)
			return true;

	return false;
}

bool LoadStoreInst::IsSkipExact(BPatch_function * func) {
	std::string funcName = func->getName();
	StringVector n = SkipExact();
	for (auto i : n) {
		if (funcName == i)
			return true;
	}
	return false;
}

BPatch_object::Region LoadStoreInst::FindRegion(BPatch_function * func) {
	uint64_t funcBase = (uint64_t)func->getBaseAddr();
	for (auto i : _regionToLibname) {
		if (i.first.base <= funcBase && (i.first.base + i.first.size) >= funcBase)
			return i.first;
	}
	BPatch_object::Region tmp;
	assert(1 == 0);
	return tmp;
}


void LoadStoreInst::IdentifyRegions() {
	// Identify all regions in the module.
	std::vector<BPatch_object *> imgObjects;
	_img->getObjects(imgObjects);
	for (auto x : imgObjects) {
		std::string libname = x->name();
		std::string pathname = x->pathName();		
		std::vector<BPatch_object::Region> tmpRegion;
		x->regions(tmpRegion);		
		for (auto y : tmpRegion) 
			_regionToLibname[y] = std::make_pair(pathname,libname);
	}
}

void LoadStoreInst::Setup() {
	// Finds all functions we need to hook into in the binary.
	std::vector<BPatch_function *> callFunc;
	std::vector<BPatch_function *> tracerCall;
	std::vector<BPatch_function *> endFuncCall;
	_img->findFunction("SYNC_RECORD_MEM_ACCESS", callFunc);
	_img->findFunction("SYNC_RECORD_FUNCTION_ENTRY", tracerCall);	
	_img->findFunction("SYNC_RECORD_FUNCTION_EXIT", endFuncCall);	
	
	assert(callFunc.size() > 0);
	assert(tracerCall.size() > 0);
	assert(endFuncCall.size() > 0);
	_endFuncCall = endFuncCall[0];
	_recordMemAccess = callFunc[0];
	_tracerFunction = tracerCall[0];
}


bool LoadStoreInst::InstrimentNewModule(BPatch_object * obj, bool finalize) {
	// Adds instrimentation to a module loaded at a later point in time.
	return false;
}

void LoadStoreInst::Finalize() {
	// Finalizes the insertion set of dyninst
	if (_started)
		_addrSpace->finalizeInsertionSet(false);
	_started = false;
}


void LoadStoreInst::BeginInsertionSet() {
	// Begin the insertion set;
	if(!_started)
		_addrSpace->beginInsertionSet();
	_started = true;
}


StringVector & LoadStoreInst::GetSkipPaths() {
	// Returns a vector of library paths to skip for instrimentation.
	static StringVector ret = {"cuda_deduplicator", "cudadedup", "dyninst", "boost", "/usr/", "/lib/", "libcuda.so","libCUPTIEventHandler.so","libEcho.so","libSynchTool.so","libTimeCall.so","libTransferTimeline.so","libStubLib.so"};
	return ret;

}

StringVector & LoadStoreInst::SkipExact() {
	static StringVector ret = {"__random","backtrace_and_maps","__GI__IO_unsave_markers","_IO_setb","__GI___mempcpy","__munmap","__GI___twalk","__GI__IO_adjust_column"};
	return ret;
}

StringVector & LoadStoreInst::GetSkipFunctions() {
	// Returns a list of functions to never instriment. 
	// These functions include application init (_init), dlopen/dlsym, etc. 
	static StringVector ret = {"_fini","atexit",
	"__libc_csu_init", "__libc_csu_fini","malloc","printf","fwrite","strlen","abort","assert","strnlen","new_heap","fflush",
	"__static_initialization_and_destruction_0","_start", "__GI___backtrace","__GI___libc_secure_getenv","__GI_exit","cudart","_IO_puts","__new_fopen","fopen","_Unwind_Resume","__run_exit_handlers","free","open",
	"_init", "cudart::cuosInitializeCriticalSection","cudart::", "cudaLaunch",
	"cudart::cuosInitializeCriticalSectionShared","cudart::cuosMalloc",
	"cudart::cuosInitializeCriticalSectionWithSharedFlag","cudaLaunch","dim3::dim3",
	"__printf","__GI_fprintf","_IO_vfprintf_internal","buffered_vfprintf","printf_positional","__printf_fp","__printf_fphex","__fxprintf","__GI___printf_fp_l","vfwprintf","__GI___asprintf","buffered_vfprintf","printf_positional","_IO_vasprintf","__snprintf","vsnprintf",
    "__GI___libc_malloc","_int_malloc","__malloc_assert","malloc_consolidate","sysmalloc","malloc_printerr"};
    return ret;
}

StringVector & LoadStoreInst::GetNeverInstrimentLibs() {
	// Get the names of libraries to NEVER instriment. These include our libraries
	// and things such as libpthread. 
	static StringVector ret = {"libdl-2.23.so","libpthread-2.23.so", "cudadedup", "libcuda.so","libCUPTIEventHandler.so","libEcho.so","libSynchTool.so","libTimeCall.so","libTransferTimeline.so","libStubLib.so"};
	return ret;
}