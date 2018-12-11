#include "LoadStoreInstrimentation.h"

LoadStoreInstrimentation::LoadStoreInstrimentation(std::shared_ptr<DyninstProcess> proc) : _proc(proc) {  }


void LoadStoreInstrimentation::InsertAnalysis(StackRecMap & recs) {}

void LoadStoreInstrimentation::PostProcessing(StackRecMap & recs) {}
