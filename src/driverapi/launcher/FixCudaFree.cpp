#include "FixCudaFree.h"
FixCudaFree::FixCudaFree(std::shared_ptr<DyninstProcess> proc) : _proc(proc) {}

void FixCudaFree::InsertAnalysis(StackRecMap & recs) {
	_bmap.reset(new BinaryLocationIDMap());
	BPatch_object * libcuda = _proc->LoadLibrary(std::string("libcuda.so.1"));
	BPatch_object * wrapper = _proc->LoadLibrary(std::string(LOCAL_INSTALL_PATH) + std::string("/lib/plugins/libDiogenesMemManager.so"));
	std::shared_ptr<InstrimentationTracker> tracker(new InstrimentationTracker());
	std::vector<BPatch_function *> all_functions;
	BPatch_image * img = _proc->GetAddressSpace()->getImage();
	img->getProcedures(all_functions);
	for (auto i : all_functions) {
		_dyninstFunctions[(uint64_t)i->getBaseAddr()] = std::shared_ptr<DyninstFunction>(new DyninstFunction(_proc, i, tracker, _bmap));
	}

	std::string binary_name = std::string("main");
	std::string tmpLibname = std::string("");
	std::string tmpFuncName = std::string("");
	for (auto i : _dyninstFunctions) {
		if (i.second->IsExcludedFunction(LOAD_STORE_INST))
			continue;
		i.second->GetFuncInfo(tmpLibname, tmpFuncName);
		if (tmpFuncName.find("DIOGENES_") != std::string::npos || tmpLibname.find("/lib/plugins/") != std::string::npos)
			continue;
		if (tmpLibname.find("/usr/lib64/libc-2.17.so") != std::string::npos)
			continue;

		//if (tmpLibname.find(binary_name) != std::string::npos) {
			std::vector<DyninstCallsite> callsites;
			i.second->GetCallsites(callsites);
			for (auto x : callsites) {
				if (*(x.GetCalledFunction()) == std::string("cudaFree"))
					std::cerr << "Found function call to cudaFree in " << tmpFuncName << " within library " << tmpLibname << " (calling " << *(x.GetCalledFunction()) << ")"  << std::endl;
				if (*(x.GetCalledFunction()) == std::string("cudaMalloc"))
					std::cerr << "Found function call to cudaMalloc in " << tmpFuncName << " within library " << tmpLibname << " (calling " << *(x.GetCalledFunction()) << ")" << std::endl;
				if (*(x.GetCalledFunction()) == std::string("__GI___libc_malloc"))
					std::cerr << "Found function call to malloc in " << tmpFuncName << " within library " << tmpLibname << " (calling " << *(x.GetCalledFunction()) << ")" << std::endl;
				if (*(x.GetCalledFunction()) == std::string("cudaMemcpyAsync"))
					std::cerr << "Found function call to cudaMemcpyAsync in " << tmpFuncName << " within library " << tmpLibname << " (calling " << *(x.GetCalledFunction()) << ")"  << std::endl;
			}
		//}
	}

}