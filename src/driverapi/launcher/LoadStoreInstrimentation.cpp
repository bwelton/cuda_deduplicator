#include "LoadStoreInstrimentation.h"

LoadStoreInstrimentation::LoadStoreInstrimentation(std::shared_ptr<DyninstProcess> proc) : _proc(proc) { 
	_bmap.reset(new BinaryLocationIDMap());

}


void LoadStoreInstrimentation::InsertAnalysis(StackRecMap & recs) {
	std::shared_ptr<DynOpsClass> ops = _proc->ReturnDynOps();
	BPatch_object * libcuda = _proc->LoadLibrary(std::string("libcuda.so.1"));
	// Load all the libraries that appear in the stacktraces into the process address space. 
	for (auto i : recs) {
		for (auto z : i.second.GetStackpoints()) {
		 	if (z.libname.find(".so") != std::string::npos)
		 		_proc->LoadLibrary(z.libname);
		}
	}

	// Create the dyninst functions from all the functions in the process.
	std::vector<BPatch_function *> all_functions;
	BPatch_image * img = _proc->GetAddressSpace()->getImage();
	img->getProcedures(all_functions);
	std::shared_ptr<InstrimentationTracker> tracker(new InstrimentationTracker());

	for (auto i : all_functions) {
		_dyninstFunctions.push_back(std::shared_ptr<DyninstFunction>(new DyninstFunction(_proc, i, tracker, _bmap)));	
		_funcPositions[i] = _dyninstFunctions.size() - 1;
	}

	// Setup apicapture
	APICaptureInstrimentation procTime(_proc);
	procTime.InsertInstrimentation();

	// Insert Entry/Exit info
	InsertEntryExit(recs);

	// Insert Sync Capture
	BPatch_function * enterSync;
	std::vector<BPatch_function*> cudaSyncFunctions = ops->GetFunctionsByOffeset(_proc->GetAddressSpace(), libcuda, ops->GetSyncFunctionLocation());
	assert(cudaSyncFunctions.size() == 1);
	assert(ops->FindFuncByName(_proc->GetAddressSpace(), enterSync, std::string("SYNC_CAPTURE_SYNC_CALL")) == 1);
	std::vector<BPatch_point*> * entryPoints = cudaSyncFunctions[0]->findPoint(BPatch_locEntry);
	std::string tmp = cudaSyncFunctions[0]->getModule()->getObject()->pathName();
	_bmap.StorePosition(tmp,ops->GetSyncFunctionLocation());
	std::vector<BPatch_snippet*> recordArgs;
	BPatch_funcCallExpr entryExpr(*enterSync, recordArgs);
	assert(_proc->GetAddressSpace()->insertSnippet(entryExpr,*entryPoints) != NULL);
}

void LoadStoreInstrimentation::InsertEntryExit(StackRecMap & recs) {
	std::shared_ptr<DynOpsClass> ops = _proc->ReturnDynOps();
	for (auto i : recs) {
		std::vector<StackPoint> points = i.second.GetStackpoints();
		for (auto z : points) {
			BPatch_function * func;
			if (ops->FindFuncByStackPoint(_proc->GetAddressSpace(), func, z) <= 0) {
				std::cerr << "[LoadStoreInstrimentation::InsertEntryExit] Could not find function - " << z.funcName << std::endl;
				continue;
			}
			assert(_funcPositions.find(func) != _funcPositions.end());
			_dyninstFunctions[_funcPositions[func]]->EntryExitWrapping();
		}
	}
}

void LoadStoreInstrimentation::PostProcessing(StackRecMap & recs) {}
