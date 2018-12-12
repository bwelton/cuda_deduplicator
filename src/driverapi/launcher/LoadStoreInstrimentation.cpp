#include "LoadStoreInstrimentation.h"

LoadStoreInstrimentation::LoadStoreInstrimentation(std::shared_ptr<DyninstProcess> proc) : _proc(proc) {  }


void LoadStoreInstrimentation::InsertAnalysis(StackRecMap & recs) {

	APICaptureInstrimentation procTime(_proc);
	procTime.InsertInstrimentation();
}

void LoadStoreInstrimentation::PostProcessing(StackRecMap & recs) {}
