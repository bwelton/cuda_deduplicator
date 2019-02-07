#include "DyninstFunctionWraps.h"

std::map<std::string, DFW_wrapper> DFW_MAP;
volatile bool DFW_MAP_SET = false;
void OneTimeFillMap() {
	if (DFW_MAP_SET)
		return;
	DFW_MAP_SET = true;
	DFW_wrapper tmp;
	DFW_MAP.clear();

	tmp = {
		.wrap =  std::string("strcpy"),
		.library = std::string("libc-2.17.so"),
		.wrapperName = std::string("diogenes_strcpy_wrapper"),
		.argMap = {std::make_pair(0,0),std::make_pair(1,1)},
	};
	DFW_MAP[tmp.wrap] = tmp;
}

DyninstFunctionWraps::DyninstFunctionWraps(std::shared_ptr<DyninstProcess> proc) : _proc(proc) {}


bool DyninstFunctionWraps::InsertLoadStoreInstrimentation(BPatch_function * func, std::shared_ptr<BinaryLocationIDMap> bmap) {
	OneTimeFillMap();
	if (DFW_MAP.find(func->getName()) == DFW_MAP.end())
		return false;
	std::string tmpName = func->getName();
	BPatch_object * obj = func->getModule()->getObject();
	if (obj->pathName().find(DFW_MAP[tmpName].library) == std::string::npos)
		return false;

	std::cerr << "[DyninstFunctionWraps::InsertLoadStoreInstrimentation] Inserting custom function wrap for function " 
		      << func->getName() << " In library " <<  DFW_MAP[tmpName].library << std::endl;


	std::vector<BPatch_function *> recordMemAccess = ops->FindFuncsByName(_proc->GetAddressSpace(), DFW_MAP[tmpName].wrapperName, NULL);
	std::vector<BPatch_point*> * loadsAndStores = func->findPoint(axs);
	std::vector<BPatch_point*> * locationEntry = func->findPoint(BPatch_locEntry);
	assert(recordMemAccess.size() == 1);
	assert(loadsAndStores->size() > 0);
	assert(locationEntry->size() > 0);

	std::string libname = _obj->pathName();
	uint64_t addr = (uint64_t)(*loadsAndStores)[0]->getAddress();

	uint64_t libOffsetAddr = 0;
	if (!ops->GetFileOffset(_proc->GetAddressSpace(), (*loadsAndStores)[0], libOffsetAddr, true))
		libOffsetAddr = (uint64_t) i->getAddress();

	assert(bmap->AlreadyExists(libname, libOffsetAddr) == false);
	uint64_t id = _bmap->StorePosition(libname, libOffsetAddr);

	std::vector<BPatch_snippet*> recordArgs;
	for (auto i : DFW_MAP[tmpName].argMap){
		assert(i.first <= recordArgs.size());
		while (i.first < recordArgs.size())
			recordArgs.push_back(BPatch_constExpr(uint64_t(0)));
		recordArgs.push_back(BPatch_paramExpr(i.second));
	}
	recordArgs.push_back(id);
	BPatch_funcCallExpr recordAddrCall(*(recordMemAccess[0]), recordArgs);
	assert(_proc->GetAddressSpace()->insertSnippet(recordAddrCall,*loadsAndStores) != NULL);
	return true;
}
