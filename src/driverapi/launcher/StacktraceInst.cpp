#include "StacktraceInst.h"

StacktraceInst::StacktraceInst(BPatch_addressSpace * addrSpace, BPatch_image * img) :
	_addrSpace(addrSpace), _img(img), _curID(0) {
	

}


void StacktraceInst::InsertStackInst() {
	Setup();
	// Begin the insertion set
	_addrSpace->beginInsertionSet();

	assert(_addrSpace->wrapFunction(_cudaSync, _wrapperFunc, _wrapSym) != false);

	_addrSpace->finalizeInsertionSet(false);	
}
 

void StacktraceInst::InsertInstFuncEntryExit(BPatch_function * instFunc){
	// if (IsFunctionExcluded(instFunc))
	// 	return;
	// assert(instFunc != NULL);

	// uint64_t id = GetFuncId(instFunc);
	// if (_alreadyInstrimented.find(id) != _alreadyInstrimented.end())
	// 	return;
	// _alreadyInstrimented.insert(id);
	// std::vector<BPatch_snippet*> testArgs;

	// testArgs.push_back(new BPatch_constExpr(id));	
	// BPatch_funcCallExpr recordFuncEntry(*_atEntryFunc, testArgs);
	// BPatch_funcCallExpr recordFuncExit(*_atExitFunc, testArgs);	

	// std::vector<BPatch_point*> * entryLocations = instFunc->findPoint(BPatch_locEntry);
	// std::vector<BPatch_point*> * exitLocations = instFunc->findPoint(BPatch_locExit);

	// if (_addrSpace->insertSnippet(recordFuncEntry,*entryLocations) == NULL)
	// 	std::cerr << "Could not insert entry snippet - " << instFunc->getName() << std::endl;

	// if (_addrSpace->insertSnippet(recordFuncExit,*exitLocations) == NULL)
	// 	std::cerr << "Could not insert entry snippet - " << instFunc->getName() << std::endl;

}
void StacktraceInst::InsertEntryExitCall(BPatch_function * instFunc, BPatch_function * calledFunc, BPatch_point * callPoint) {
	// if (IsFunctionExcluded(calledFunc))
	// 	return;
	
	// uint64_t id = GetFuncId(calledFunc);

	// // Before the point, insert an entry call.
	// // After the point, insert an exit call.
	
	// std::vector<BPatch_snippet*> testArgs;
	// testArgs.push_back(new BPatch_constExpr(id));
	// testArgs.push_back(new BPatch_constExpr(((uint64_t)callPoint->getAddress()) - (uint64_t)instFunc->getModule()->getBaseAddr()));
	// BPatch_funcCallExpr recordFuncEntry(*_entryFunc, testArgs);
	// //std::cerr << x->getName() << "," << _funcId << std::endl;
	// if (_addrSpace->insertSnippet(recordFuncEntry,*callPoint,BPatch_callBefore) == NULL)
	// 	std::cerr << "Could not insert entry snippet - " << calledFunc->getName() << std::endl;

	// BPatch_funcCallExpr recordFuncExit(*_exitFunc, testArgs);	
	// if (_addrSpace->insertSnippet(recordFuncExit,*callPoint,BPatch_callAfter) == NULL)
	// 	std::cerr << "Could not insert exit snippet - " << calledFunc->getName() << std::endl;
}

std::vector<std::pair<BPatch_function *, BPatch_point *> > StacktraceInst::GetFunctionCalls(BPatch_function * func) {
	// std::vector<BPatch_point*> * callPoints = func->findPoint(BPatch_locSubroutine);
	// std::vector<std::pair<BPatch_function *, BPatch_point *> > ret;
	// for (auto i : *callPoints) {
	// 	if (i->getCalledFunction() == NULL)
	// 		continue;
	// 	ret.push_back(std::make_pair(i->getCalledFunction(), i));
	// }
	// return ret;
}

uint64_t StacktraceInst::GetFuncId(BPatch_function * func) {
	// uint64_t baseAddr = (uint64_t)func->getBaseAddr();
	// if (_idMap.find(baseAddr) != _idMap.end()) {
	// 	return _idMap[baseAddr].first;
	// }
	// // doesn't exist, add it.
	// _idMap[baseAddr] = std::make_pair(_curID, func);
	// _curID += 1;
	// return _curID - 1;
}

void StacktraceInst::Setup() {
	std::vector<BPatch_function *> wrapperFunc;
	_img->findFunction("STACK_SyncWrapper", wrapperFunc);
	assert(wrapperFunc.size() > 0);
	_wrapperFunc = wrapperFunc[0];

	BPatch_function * cudaSync = NULL;
	std::vector<BPatch_object *> imgObjs;
	_img->getObjects(imgObjs);
	for (auto i : imgObjs){
		if (i->name().find("libcuda.so") == std::string::npos)
			continue;
		// Found libcuda
		uint64_t offsetAddress = i->fileOffsetToAddr(INTERNAL_SYNC_ST);
		cudaSync = _img->findFunction(offsetAddress);
		break;
	}
	assert(cudaSync != NULL);
	_cudaSync = cudaSync;

	// Find the symbol to wrap
	BPatch_object * obj = _wrapperFunc->getModule()->getObject();
	Dyninst::SymtabAPI::Symtab * symt = Dyninst::SymtabAPI::convert(obj);
	std::vector<Dyninst::SymtabAPI::Symbol *> tmp;
	symt->getAllSymbols(tmp);
	_wrapSym = NULL;
	for (auto i : tmp) {
		if (i->getPrettyName().find("SynchronizationWrapper") != std::string::npos) {
			if (i->getModule()->fileName.find("STraceWrapSync") == std::string::npos)
				continue;
			_wrapSym = i;
			std::cerr << "Found synchtonization Wrapper" << std::endl;
			break;
		}
	}
	assert(_wrapSym != NULL);

	// _img->findFunction("STACK_SyncWrapper", wrapperFunc);
}


bool StacktraceInst::IsFunctionExcluded(BPatch_function * func) {
	// static std::vector<std::string> skippedNames = {"cuda_deduplicator", "dyninst", "boost" , "libCUPTIEventHandler", "libdl-2.23.so","libpthread-2.23.so","libc.so.6","libm.so.6", "exit", "/usr", "/lib","/lib64",
	// 												"__random","__stack_chk_fail","deregister_tm_clones","register_tm_clones","backtrace_and_maps","__GI__IO_unsave_markers","_IO_setb","__GI___mempcpy","__munmap","__GI___fortify_fail","helper_thread","timer_helper_thread","__GI___twalk","__GI__IO_adjust_column","__GI___libc_fatal","_Unwind_Resume","__longjmp_chk"
	// 												"libdl-2.23.so","libpthread-2.23.so", "cudadedup","libCUPTIEventHandler.so","libEcho.so","libSynchTool.so","libTimeCall.so","libTransferTimeline.so","libStubLib.so", "libStacktrace.so"};
	// std::string funcName = func->getName();
	// std::string objectName = func->getModule()->getObject()->pathName();
	// for (auto i : skippedNames){
	// 	if (funcName.find(i) != std::string::npos)
	// 		return true;
	// 	if (objectName.find(i) != std::string::npos)
	// 		return true;
	// }
	// // If this is the sync call, skip it.
	// if ((uint64_t)func->getBaseAddr() == INTERNAL_SYNC_ST)
	// 	return true;
	// return false;
}