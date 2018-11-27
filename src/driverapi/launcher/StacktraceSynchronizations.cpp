#include "StacktraceSynchronizations.h"
#define USE_BPATCHINSERT 1
StacktraceSynchronizations::StacktraceSynchronizations(std::shared_ptr<DyninstProcess> proc) : _proc(proc) {
}


void StacktraceSynchronizations::Setup() {
	/***
	 * Setup finds the key functions we need for finding synchronizations:
	 *
	 * 1. Nvidia's internal synchronization function. This function is located at a specific, driver version
	 *    dependent offset into libcuda.so. Right now, we have a directory of md5sum,offset infromation where
	 *    we look up the md5sum of the systems libcuda to identify the location of this function. How these
	 *    locations are determined is via manual testing currently. 
	 * 2. The wrapper that performs the backtrace (using dyninst), inserted at the beginning of the synchronization function above
	 **/

	// Insert libraries needed into process	
	BPatch_object * libcuda = _proc->LoadLibrary(std::string("libcuda.so.1"));
	BPatch_object * libstrace = _proc->LoadLibrary(std::string(LOCAL_INSTALL_PATH) + std::string("/lib/plugins/libStacktrace.so"));
	std::shared_ptr<DynOpsClass> ops = _proc->ReturnDynOps();
	std::vector<BPatch_function *> stackTracer;

	#ifdef USE_BPATCHINSERT
	stackTracer = ops->FindFuncsByName(_proc->GetAddressSpace(), std::string("RecordStack"), libstrace);
	#else
	stackTracer = ops->FindFuncsByName(_proc->GetAddressSpace(), std::string("STACK_SyncWrapper"), libstrace);
	#endif

	std::cerr << "[StacktraceSynchronizations::Setup] Starting Setup.... " << std::endl;

	std::vector<BPatch_function *> wrapperFunc;
	#ifdef USE_BPATCHINSERT
	wrapperFunc = ops->FindFuncsByName(_proc->GetAddressSpace(), std::string("RecordStack"), NULL); 
	#else
	wrapperFunc = ops->FindFuncsByName(_proc->GetAddressSpace(), std::string("STACK_SyncWrapper"), NULL); 
	#endif
	assert(wrapperFunc.size() > 0);
	_wrapperFunc = wrapperFunc[0];

	BPatch_function * cudaSync = NULL;

	std::vector<BPatch_function*> cudaSyncFunctions = ops->GetFunctionsByOffeset(_proc->GetAddressSpace(), libcuda, ops->GetSyncFunctionLocation());

	assert(cudaSyncFunctions.size() == 1);

	_cudaSync = cudaSyncFunctions[0];

	wrapperFunc = ops->FindFuncsByName(_proc->GetAddressSpace(), std::string("SynchronizationWrapper"), NULL); 
	assert(wrapperFunc.size() == 1);
	_wrapSym = wrapperFunc[0];
}


void StacktraceSynchronizations::InsertStacktracing() {
	/** 
	 * Inserts stack tracing to identify the locations of synchronizations in libcuda. 
	 *
	 * Currently either wraps the syncrhonization function (if function wrapping enabled, this is currently broken in dyninst) 
	 * or viainsertion of a function call to instrimentation into the beginning of the synchronization function (current method).
	 *
	 */

	Setup();
	
	_proc->BeginInsertionSet();
#ifdef USE_BPATCHINSERT
	// Testing
	//assert(cuCtxSync.size() > 0);
	std::vector<BPatch_point*> * entryLocations = _cudaSync->findPoint(BPatch_locEntry);
	std::vector<BPatch_snippet*> testArgs;
	BPatch_funcCallExpr recordFuncEntry(*_wrapperFunc, testArgs);
	assert(_proc->GetAddressSpace()->insertSnippet(recordFuncEntry,*entryLocations) != false);
#else
	assert(_proc->GetAddressSpace()->wrapFunction(_cudaSync, _wrapperFunc, _wrapSym) != false);
#endif
// 	// _addrSpace->finalizeInsertionSet(false);
// 	BPatch_process * tmpProc = dynamic_cast<BPatch_process*>(_addrSpace);		
}


void StacktraceSynchronizations::ReadResults(StackRecMap & recs) {
	ReadStackKeys reader(std::string("DIOGENES_SyncCalls.key"), std::string("DIOGENES_SyncCalls.bin"));
	reader.GetStackRecords(recs, std::bind(&ReadStackKeys::ProcessStacktraceSynch, &reader, std::placeholders::_1));
}