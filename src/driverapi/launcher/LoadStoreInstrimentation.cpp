#include "LoadStoreInstrimentation.h"

LoadStoreInstrimentation::LoadStoreInstrimentation(std::shared_ptr<DyninstProcess> proc) : _proc(proc) { 
	_bmap.reset(new BinaryLocationIDMap());

}


void LoadStoreInstrimentation::InsertAnalysis(StackRecMap & recs) {
	// Create the dyninst functions from all the functions in the process.
	std::vector<BPatch_function *> all_functions;
	BPatch_image * img = _proc->GetAddressSpace()->getImage();
	img->getProcedures(all_functions);
	std::shared_ptr<InstrimentationTracker> tracker(new InstrimentationTracker());

	for (auto i : all_functions) {
		_dyninstFunctions.push_back(std::shared_ptr<DyninstFunction>(new DyninstFunction(_proc, i, tracker, _bmap)));		
	}

	// Setup apicapture
	APICaptureInstrimentation procTime(_proc);
	procTime.InsertInstrimentation();
}

void LoadStoreInstrimentation::PostProcessing(StackRecMap & recs) {}
