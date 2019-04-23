#include "FixCudaFree.h"
FixCudaFree::FixCudaFree(std::shared_ptr<DyninstProcess> proc) : _proc(proc) {}

void FixCudaFree::InsertAnalysis(StackRecMap & recs) {
	_bmap.reset(new BinaryLocationIDMap())
	BPatch_object * libcuda = _proc->LoadLibrary(std::string("libcuda.so.1"));
	std::shared_ptr<InstrimentationTracker> tracker(new InstrimentationTracker());
	std::vector<BPatch_function *> all_functions;
	BPatch_image * img = _proc->GetAddressSpace()->getImage();
	img->getProcedures(all_functions);
	for (auto i : all_functions) {
		_dyninstFunctions[(uint64_t)i->getBaseAddr()] = std::shared_ptr<DyninstFunction>(new DyninstFunction(_proc, i, tracker, _bmap));
	}

	std::string binary_name = std::string("cuibm");
	std::string tmpLibname = std::string("");
	std::string tmpFuncName = std::string("");
	for (auto i : _dyninstFunctions) {
		if (i.second->IsExcludedFunction(LOAD_STORE_INST))
			continue;
		i.second->GetFuncInfo(tmpLibname, tmpFuncName);
		if (tmpLibname.find(binary_name) != std::string::npos) {
			std::vector<DyninstCallsite> callsites;
			i.second->GetCallsites(callsites);
			for (auto x : callsites)
				if (x.GetCalledFunction()->find("cudaFree") != std::string::npos)
					std::cerr << "Found function call to cudaFree in " << tmpFuncName << std::endl;
		}
	}

}