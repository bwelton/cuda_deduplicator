#include "LaunchIdentifySync.h"
LaunchIdentifySync::LaunchIdentifySync(std::shared_ptr<DyninstProcess> proc) : _proc(proc) { 

}

void LaunchIdentifySync::InsertAnalysis(std::vector<uint64_t> functionsToTrace, std::string funcName) { 
	std::shared_ptr<DynOpsClass> ops = _proc->ReturnDynOps();
	std::vector<BPatch_function *> main = ops->FindFuncsByName(_proc->GetAddressSpace(), std::string("main"), NULL);
	BPatch_object * libCuda = _proc->LoadLibrary(std::string("libcuda.so.1"));
	BPatch_object * driverAPIWrapper = _proc->LoadLibrary(std::string(LOCAL_INSTALL_PATH) + std::string("/lib/plugins/libFindSyncHelper.so"));
	
	std::vector<BPatch_function *> cEntry = ops->FindFuncsByName(_proc->GetAddressSpace(), std::string("CALL_ENTRY"), driverAPIWrapper);
	std::vector<BPatch_function *> cExit = ops->FindFuncsByName(_proc->GetAddressSpace(), std::string("CALL_EXIT"), driverAPIWrapper);
	std::vector<BPatch_function *> signalStart = ops->FindFuncsByName(_proc->GetAddressSpace(), std::string("SignalStartInstra"), driverAPIWrapper);

	assert(cEntry.size() == 1 && cExit.size() == 1 && signalStart.size() == 1 && main.size() > 0);

	std::unordered_map<uint64_t, BPatch_function *> funcMap;
	std::vector<BPatch_function *> funcs;
	_proc->GetAddressSpace()->getImage()->getProcedures(funcs);
	uint64_t curId = 5;

	std::unordered_map<uint64_t, uint64_t> idToOffset;
	for (auto i : funcs) {
		if (i->getModule()->getObject() == libCuda)
			funcMap[((uint64_t)i->getBaseAddr()) - ((uint64_t)i->getModule()->getBaseAddr())] = i;
	}
	_proc->BeginInsertionSet();
	for (auto i : functionsToTrace) {
		if (funcMap.find(i) == funcMap.end()){
			std::cerr << "Could not find function at offset = " << std::hex << i << std::endl;
		} else {
			std::vector<BPatch_snippet*> recordArgs;
			recordArgs.push_back(new BPatch_constExpr(curId));
			BPatch_funcCallExpr entryExpr(*cEntry[0], recordArgs);
			BPatch_funcCallExpr exitExpr(*cExit[0], recordArgs);
			auto f = funcMap[i];
			std::vector<BPatch_point*> * entry = f->findPoint(BPatch_locEntry);
			std::vector<BPatch_point*> * exit = f->findPoint(BPatch_locExit);
			_proc->GetAddressSpace()->insertSnippet(entryExpr,*entry);
			_proc->GetAddressSpace()->insertSnippet(exitExpr,*exit);
			idToOffset[i] = curId;
			curId++;
			funcMap.erase(i);
		}
	}
	BPatch_function * mainFunc = main[0];
	if (main.size() > 1) {
		for (auto i : main)
			if (i->getModule()->getObject()->pathName().find(".so") == std::string::npos)
				mainFunc = i;
	}

	std::vector<BPatch_point*> * funcCalls = mainFunc->findPoint(BPatch_locSubroutine);
	for (auto i : *funcCalls) {
		if (i->getCalledFunction()->getName().find(funcName) != std::string::npos) {
			std::vector<BPatch_point*> singlePoint;
			singlePoint.push_back(i);
			std::vector<BPatch_snippet*> recordArgs;
			BPatch_funcCallExpr entryExpr(*signalStart[0], recordArgs);
			_proc->GetAddressSpace()->insertSnippet(entryExpr,singlePoint, BPatch_callBefore);
		}
	}
}