#include "StacktraceInst.h"

StacktraceInst::StacktraceInst(BPatch_addressSpace * addrSpace, BPatch_image * img) :
	_addrSpace(addrSpace), _img(img), _curID(0) {
	

}


void StacktraceInst::InsertStackInst() {
	Setup();
	// Get a list of all functions in the binary
	std::vector<BPatch_function *> all_functions;
	_img->getProcedures(all_functions);

	// Begin the insertion set
	_addrSpace->beginInsertionSet();

	// The strategy here is to insert an entry call at all functions calls in the function to denote entrance
	// into the underlying function and the position of that entrance (i.e. the specific call it entered from).
	// We will also record the exit from this function. 
	for (auto i : all_functions) {
		if (IsFunctionExcluded(i))
			continue;
		uint64_t myID =  GetFuncId(i);	
		// Get points
		std::vector<std::pair<BPatch_function * , BPatch_point *> > calls = GetFunctionCalls(i);
		InsertInstFuncEntryExit(i);
		// for (auto n : calls) {
		// 	InsertEntryExitCall(i, n.first, n.second);
		// }
	}

	// Insert call to capture synchronization specifically
	BPatch_function * cudaSync = NULL;
	Dyninst::Address offsetAddress = 0;
	std::vector<BPatch_object *> imgObjs;
	_img->getObjects(imgObjs);
	for (auto i : imgObjs){
		if (i->name().find("libcuda.so") == std::string::npos)
			continue;
		// Found libcuda
		offsetAddress = i->fileOffsetToAddr(INTERNAL_SYNC_ST);
		cudaSync = _img->findFunction(offsetAddress);
		break;
	}
	assert(cudaSync != NULL);
	{
		std::vector<BPatch_point*> * funcEntry = cudaSync->findPoint(BPatch_locEntry);
		std::vector<BPatch_snippet*> testArgs;
		BPatch_funcCallExpr recordFuncEntry(*_recordSync, testArgs);
		std::cerr << "Adding Sync Notifyer" << std::endl;
		if (_addrSpace->insertSnippet(recordFuncEntry,*funcEntry) == NULL) 
			std::cerr << "could not insert func entry snippet" << std::endl;
	}

	_addrSpace->finalizeInsertionSet(false);	
}
 

void StacktraceInst::InsertInstFuncEntryExit(BPatch_function * instFunc){
	if (IsFunctionExcluded(instFunc))
		return;
	assert(instFunc != NULL);

	uint64_t id = GetFuncId(instFunc);
	if (_alreadyInstrimented.find(id) != _alreadyInstrimented.end())
		return;
	_alreadyInstrimented.insert(id);
	std::vector<BPatch_snippet*> testArgs;

	testArgs.push_back(new BPatch_constExpr(id));	
	BPatch_funcCallExpr recordFuncEntry(*_atEntryFunc, testArgs);
	BPatch_funcCallExpr recordFuncExit(*_atExitFunc, testArgs);	

	std::vector<BPatch_point*> * entryLocations = instFunc->findPoint(BPatch_locEntry);
	std::vector<BPatch_point*> * exitLocations = instFunc->findPoint(BPatch_locExit);

	if (_addrSpace->insertSnippet(recordFuncEntry,*entryLocations) == NULL)
		std::cerr << "Could not insert entry snippet - " << instFunc->getName() << std::endl;

	if (_addrSpace->insertSnippet(recordFuncExit,*exitLocations) == NULL)
		std::cerr << "Could not insert entry snippet - " << instFunc->getName() << std::endl;

}
void StacktraceInst::InsertEntryExitCall(BPatch_function * instFunc, BPatch_function * calledFunc, BPatch_point * callPoint) {
	if (IsFunctionExcluded(calledFunc))
		return;
	
	uint64_t id = GetFuncId(calledFunc);

	// Before the point, insert an entry call.
	// After the point, insert an exit call.
	
	std::vector<BPatch_snippet*> testArgs;
	testArgs.push_back(new BPatch_constExpr(id));
	testArgs.push_back(new BPatch_constExpr(((uint64_t)callPoint->getAddress()) - (uint64_t)instFunc->getModule()->getBaseAddr()));
	BPatch_funcCallExpr recordFuncEntry(*_entryFunc, testArgs);
	//std::cerr << x->getName() << "," << _funcId << std::endl;
	if (_addrSpace->insertSnippet(recordFuncEntry,*callPoint,BPatch_callBefore) == NULL)
		std::cerr << "Could not insert entry snippet - " << calledFunc->getName() << std::endl;

	BPatch_funcCallExpr recordFuncExit(*_exitFunc, testArgs);	
	if (_addrSpace->insertSnippet(recordFuncExit,*callPoint,BPatch_callAfter) == NULL)
		std::cerr << "Could not insert exit snippet - " << calledFunc->getName() << std::endl;
}

std::vector<std::pair<BPatch_function *, BPatch_point *> > StacktraceInst::GetFunctionCalls(BPatch_function * func) {
	std::vector<BPatch_point*> * callPoints = func->findPoint(BPatch_locSubroutine);
	std::vector<std::pair<BPatch_function *, BPatch_point *> > ret;
	for (auto i : *callPoints) {
		if (i->getCalledFunction() == NULL)
			continue;
		ret.push_back(std::make_pair(i->getCalledFunction(), i));
	}
	return ret;
}

uint64_t StacktraceInst::GetFuncId(BPatch_function * func) {
	uint64_t baseAddr = (uint64_t)func->getBaseAddr();
	if (_idMap.find(baseAddr) != _idMap.end()) {
		return _idMap[baseAddr].first;
	}
	// doesn't exist, add it.
	_idMap[baseAddr] = std::make_pair(_curID, func);
	_curID += 1;
	return _curID - 1;
}

void StacktraceInst::Setup() {
	std::vector<BPatch_function *> entryFunc;
	std::vector<BPatch_function *> exitFunc;
	std::vector<BPatch_function *> recordSync;
	std::vector<BPatch_function *> atFunctionEntry;
	std::vector<BPatch_function *> atFunctionExit;

	_img->findFunction("STACKTRACE_RECORD_ENTRY", entryFunc);
	_img->findFunction("STACKTRACE_RECORD_EXIT", exitFunc);	
	_img->findFunction("STACKTRACE_RECORD_MAIN_ENTRY", atFunctionEntry);
	_img->findFunction("STACKTRACE_RECORD_MAIN_EXIT", atFunctionExit);	
	_img->findFunction("SYNC_RECORD_SYNC_CALL", recordSync);	

	assert(entryFunc.size() > 0);
	assert(exitFunc.size() > 0);
	assert(recordSync.size() > 0);
	assert(atFunctionExit.size() > 0);
	assert(atFunctionEntry.size() > 0);

	_entryFunc = entryFunc[0];
	_exitFunc = exitFunc[0];
	_recordSync = recordSync[0];
	_atEntryFunc = atFunctionEntry[0];
	_atExitFunc = atFunctionExit[0];

}


bool StacktraceInst::IsFunctionExcluded(BPatch_function * func) {
	static std::vector<std::string> skippedNames = {"cuda_deduplicator", "dyninst", "boost" , "libCUPTIEventHandler", "cudadedup", "libdl-2.23.so","libpthread-2.23.so","libc.so.6","libm.so.6", "exit",
													"__random","__stack_chk_fail","deregister_tm_clones","register_tm_clones","backtrace_and_maps","__GI__IO_unsave_markers","_IO_setb","__GI___mempcpy","__munmap","__GI___twalk","__GI__IO_adjust_column",
													"libdl-2.23.so","libpthread-2.23.so", "cudadedup", "libcuda.so","libCUPTIEventHandler.so","libEcho.so","libSynchTool.so","libTimeCall.so","libTransferTimeline.so","libStubLib.so"};
	std::string funcName = func->getName();
	std::string objectName = func->getModule()->getObject()->pathName();
	for (auto i : skippedNames){
		if (funcName.find(i) != std::string::npos)
			return true;
		if (objectName.find(i) != std::string::npos)
			return true;
	}
	// If this is the sync call, skip it.
	if ((uint64_t)func->getBaseAddr() == INTERNAL_SYNC_ST)
		return true;
	return false;
}