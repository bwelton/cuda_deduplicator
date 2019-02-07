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
		.wrapperName = std::string("strcpy_wrapper"),
		.argMap = {std::make_pair(0,0)},
	};
	DFW_MAP[tmp.wrap] = tmp;
}

DyninstFunctionWraps::DyninstFunctionWraps(std::shared_ptr<DyninstProcess> proc) : _proc(proc) {}


bool DyninstFunctionWraps::InsertLoadStoreInstrimentation(BPatch_function * func) {
	OneTimeFillMap();
	if (DFW_MAP.find(func->getName()) == DFW_MAP.end())
		return false;
	std::string tmpName = func->getName();
	BPatch_object * obj = func->getModule()->getObject();
	if (obj->pathName().find(DFW_MAP[tmpName].library) == std::string::npos)
		return false;

	std::cerr << "[DyninstFunctionWraps::InsertLoadStoreInstrimentation] Inserting custom function wrap for function " 
		      << func->getName() << " In library " <<  DFW_MAP[tmpName].library << std::endl;

	return true;
}
