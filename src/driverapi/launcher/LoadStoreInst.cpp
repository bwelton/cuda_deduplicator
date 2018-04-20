#include "LoadStoreInst.h"
#include "Instruction.h"

LoadStoreInst::LoadStoreInst(BPatch_addressSpace * addrSpace, BPatch_image * img) :
	_addrSpace(addrSpace), _img(img), _started(false), _funcId(0) {
	_runOneTime = false;	
}

// Synchronization Points:
// 1. Wrap all function calls in the program outside of libcuda
//    - Wrapper Framwork: locationID.


// bool LoadStoreInst::ShouldWrap(BPatch_function * func, )

void LoadStoreInst::InsertEntryExitSnippets(BPatch_function * func, std::vector<BPatch_point*> * points) {
	std::string libname = func->getModule()->getObject()->pathName();
	std::cout << "[LoadStoreInst][EntryExit] Inserting entry exit instrimentation into - " << func->getName() << " with ids: ";
	for (auto i : *points) {
		if (i->getCalledFunction() == NULL)
			continue;
		std::vector<std::pair<Dyninst::InstructionAPI::Instruction::Ptr, Dyninst::Address> > instructionVector;
		i->getBlock()->getInstructions(instructionVector);
		Dyninst::InstructionAPI::Instruction::Ptr pointInstruction = NULL;
		for (auto z : instructionVector)
			if(z.second == (uint64_t)i->getAddress())
			{
				pointInstruction = z.first;
				break;
			}
		std::string instString;
		if (pointInstruction != NULL)
			instString = pointInstruction->format();
		else 
			continue;
		if (instString.find("call") == std::string::npos)
			continue;
		std::vector<BPatch_point*> singlePoint;
		singlePoint.push_back(i);
		uint64_t id;
		uint64_t libOffsetAddr = 0;
		if (_dynOps.GetFileOffset(_addrSpace, i, libOffsetAddr))
			id = _binLoc.StorePosition(libname, libOffsetAddr);
		else
			id = _binLoc.StorePosition(libname, (uint64_t) i->getAddress());
		std::cout << "[LoadStoreInst][EntryExit] \tInstruction at point " << id << " , " << std::hex << (uint64_t) i->getAddress() << std::dec << std::endl;
		std::vector<BPatch_snippet*> recordArgs;
		recordArgs.push_back(new BPatch_constExpr(id));
		BPatch_funcCallExpr entryExpr(*_entryFunction, recordArgs);
		BPatch_funcCallExpr exitExpr(*_exitingFunction, recordArgs);
		//std::cout << id << ",";
		if (_addrSpace->insertSnippet(entryExpr,singlePoint, BPatch_callBefore) == NULL) {
			std::cout << "[LoadStoreInst][EntryExit] \t\t ERROR! Could not insert entry tracking into " << func->getName() << std::endl;
		}
		if (_addrSpace->insertSnippet(exitExpr,singlePoint,BPatch_callAfter) == NULL) {
			std::cout << "[LoadStoreInst][EntryExit] \t\t ERROR! Could not insert exit tracking into " << func->getName() << std::endl;
		}		
	}
}

void LoadStoreInst::WrapEntryAndExit(std::map<uint64_t, StackRecord> & syncStacks) {
	// Get all the functions in the binary
	std::vector<BPatch_object *> objects;
	_img->getObjects(objects);
	for (auto i : syncStacks) {
		std::vector<StackPoint> points = i.second.GetStackpoints();
		for (auto z : points) {
			std::cout << "[LoadStoreInst][EntryExit] Attempting to find - " << z.funcName << std::endl;
			BPatch_function * func;
			if(_dynOps.FindFuncByStackPoint(_addrSpace, func, z) <= 0){
				std::cout << "[LoadStoreInst][EntryExit] Could not find function - " << z.funcName << std::endl;
				continue;
			}
			std::vector<BPatch_point*> * funcCalls = func->findPoint(BPatch_locSubroutine);
			if (_instTracker.ShouldInstriment(func, funcCalls, CALL_TRACING)) {
				std::cout << "[LoadStoreInst][EntryExit] Inserting exit/entry info into - " << z.funcName << std::endl;
				InsertEntryExitSnippets(func, funcCalls);
			}			
		}
	}		
}	

void LoadStoreInst::InsertSyncNotifierSnippet(BPatch_function * func, uint64_t offset) {
	assert(func != NULL);
	std::vector<BPatch_point*> * entryPoints = func->findPoint(BPatch_locEntry);
	std::string tmp = func->getModule()->getObject()->pathName();
	uint64_t id = _binLoc.StorePosition(tmp,offset);
	std::vector<BPatch_snippet*> recordArgs;
	BPatch_funcCallExpr entryExpr(*_enterSync, recordArgs);
	if (_addrSpace->insertSnippet(entryExpr,*entryPoints) == NULL) {
		std::cerr << "[LoadStoreInst][SyncNotifier] FATAL ERROR! Insertion of notifier into libcuda.so - failed! Callname: " << func->getName() << std::endl;
	}
}

void LoadStoreInst::InsertSyncCallNotifier() {
	InsertSyncNotifierSnippet(_libcudaSync, INTERNAL_SYNC_LS);
}

void LoadStoreInst::InsertLoadStoreSnippets(BPatch_function * func, std::vector<BPatch_point*> * points) {
	std::string libname = func->getModule()->getObject()->pathName();
	std::cerr << "[LoadStoreInst][LoadStoreSnippet] Inserting load store instrimentation into - " << func->getName() << " with ids: ";
	for (auto i : *points) {
		uint64_t libOffsetAddr = 0;
		uint64_t id = 0;
		std::vector<BPatch_point*> singlePoint;
		singlePoint.push_back(i);
		if (_dynOps.GetFileOffset(_addrSpace, i, libOffsetAddr))
			id = _binLoc.StorePosition(libname, libOffsetAddr);
		else
			id = _binLoc.StorePosition(libname, (uint64_t) i->getAddress());
		std::vector<BPatch_snippet*> recordArgs;
		BPatch_snippet * loadAddr = new BPatch_effectiveAddressExpr();
		recordArgs.push_back(loadAddr);
		recordArgs.push_back(new BPatch_constExpr(id));
		BPatch_funcCallExpr recordAddrCall(*_recordMemAccess, recordArgs);
		std::cerr << id << ",";
		if (_addrSpace->insertSnippet(recordAddrCall,singlePoint) == NULL) {
			std::cerr << "[LoadStoreInst][LoadStoreSnippet]\t\tCould not insert load store instrimentation into " << id << std::endl;
		}
	}
	std::cerr << std::endl;
}


void LoadStoreInst::InsertLoadStoreInstrimentation() {
	std::vector<BPatch_function *> all_functions;
	_img->getProcedures(all_functions);
	std::set<BPatch_opCode> axs;
	axs.insert(BPatch_opLoad);
	axs.insert(BPatch_opStore);
	for (auto i : all_functions) {
		std::vector<BPatch_point*> * loadsAndStores = i->findPoint(axs);
		if (_instTracker.ShouldInstriment(i, loadsAndStores, LOAD_STORE_INST)) {
			InsertLoadStoreSnippets(i, loadsAndStores);
		}
	}
}


void LoadStoreInst::SetWrappedFunctions(std::vector<std::string> & wrappedFunctions ) {
	_wrappedFunctions = wrappedFunctions;
	_instTracker.AddAlreadyInstrimented(wrappedFunctions);
}

bool LoadStoreInst::InstrimentAllModules(bool finalize, std::vector<uint64_t> & skips, uint64_t & instUntil, std::vector<std::string> & syncFunctions, std::vector<StackPoint> & points, std::map<uint64_t, StackRecord> & syncStacks) {
	Setup();
	BeginInsertionSet();
	WrapEntryAndExit(syncStacks);
	InsertSyncCallNotifier();
	//InsertSyncCallNotifier(points);
	//InsertLoadStoreInstrimentation();
	// _runOneTime = true;
	// std::stringstream ss;
	// // Parameters for Record Memory Function
	// std::vector<BPatch_snippet*> recordArgs;
	// BPatch_snippet * loadAddr = new BPatch_effectiveAddressExpr();
	// BPatch_snippet * instAddr = new BPatch_originalAddressExpr();
	// recordArgs.push_back(loadAddr);
	// recordArgs.push_back(instAddr);
	// BPatch_funcCallExpr recordAddrCall(*_recordMemAccess, recordArgs);



	// IdentifyRegions();

	// // Get all the functions in the binary
	// std::vector<BPatch_function *> all_functions;
	// _img->getProcedures(all_functions);

	// std::set<uint64_t> alreadyInstrimented;
	// std::set<uint64_t> alreadyScheduled;
	// std::queue<BPatch_function *> funcsToInstriment;

	// // Find all functions that are in user generated code, this is our base to start instrimentation.
	// for (auto x : all_functions) {
	// 	// First get the region for this function, should only be 1.
	// 	BPatch_object::Region funcRegion = FindRegion(x);
	// 	if (IsNeverInstriment(x, funcRegion) || IsSkipUnlessCalled(x, funcRegion)) {
	// 		continue;
	// 	}
	// 	alreadyScheduled.insert((uint64_t)x->getBaseAddr());

	// 	funcsToInstriment.push(x);
	// }

	// std::cerr << "We will be starting instrimentation with " << funcsToInstriment.size() << " functions" << std::endl;

	// std::vector<BPatch_point *> points; 

	// std::set<BPatch_opCode> axs;
	// axs.insert(BPatch_opLoad);
	// axs.insert(BPatch_opStore);

	// while (funcsToInstriment.empty() == false) {
	// 	if (_funcId == instUntil && instUntil != 0)
	// 		break;
	// 	BPatch_function * x = funcsToInstriment.front();
	// 	funcsToInstriment.pop();


	// 	if (IsSkipExact(x))
	// 		alreadyInstrimented.insert((uint64_t)x->getBaseAddr());

	// 	if (alreadyInstrimented.find((uint64_t)x->getBaseAddr()) != alreadyInstrimented.end())
	// 		continue;
		
	// 	alreadyInstrimented.insert((uint64_t)x->getBaseAddr());
	// 	BPatch_object::Region funcRegion = FindRegion(x);
	// 	if (IsNeverInstriment(x, funcRegion)) {
	// 		continue;
	// 	}

	// 	if (std::find(skips.begin(), skips.end(), _funcId) != skips.end()){
	// 		_funcId+= 1;
	// 		continue;
	// 	}

	// 	std::cerr << "Inserting instrimentation into function - " << x->getName() << std::endl;
	// 	// Insert function tracing
	// 	{
	// 		std::vector<BPatch_point*> * funcEntry = x->findPoint(BPatch_locEntry);
	// 		std::vector<BPatch_snippet*> testArgs;
	// 		testArgs.push_back(new BPatch_constExpr(_funcId));
	// 		BPatch_funcCallExpr recordFuncEntry(*_tracerFunction, testArgs);
	// 		std::cerr << x->getName() << "," << _funcId << std::endl;
	// 		if (_addrSpace->insertSnippet(recordFuncEntry,*funcEntry) == NULL) 
	// 			std::cerr << "could not insert func entry snippet" << std::endl;
	// 	}
	// 	{
	// 		std::vector<BPatch_point*> * FuncExit = x->findPoint(BPatch_locExit);
	// 		std::vector<BPatch_snippet*> testArgs;
	// 		testArgs.push_back(new BPatch_constExpr(_funcId));
	// 		BPatch_funcCallExpr recordFuncExit(*_endFuncCall, testArgs);
	// 		//std::cerr << x->getName() << "," << _funcId << std::endl;
	// 		if (_addrSpace->insertSnippet(recordFuncExit,*FuncExit) == NULL) 
	// 			std::cerr << "could not insert func exit snippet" << std::endl;
	// 	}
	// 	_idToFunction[_funcId] = std::string(x->getName());
	// 	_funcId += 1;		


	// 	// Insert load store instrimentation
	// 	std::vector<BPatch_point*> * tmp = x->findPoint(axs);
	// 	if (tmp != NULL){
	// 		points.insert(points.end(), tmp->begin(), tmp->end());
	// 		std::cerr << "Inserting Load/Store Instrimentation into : " << x->getName() << std::endl;
	// 		if (points.size() >= 1)
	// 			if (_addrSpace->insertSnippet(recordAddrCall, points) == NULL) 
	// 				std::cerr << "could not insert snippet" << std::endl;
	// 		points.clear();
	// 	} else {
	// 		std::cerr << "Could not find any load/stores for function : " << x->getName() << std::endl;
	// 	}

	// 	// Instriment all functions that we call.
	// 	std::vector<BPatch_point*> * funcCalls = x->findPoint(BPatch_locSubroutine);
	// 	if (funcCalls != NULL) {
	// 		for (auto y : *funcCalls) {
	// 			BPatch_function * calledFunction = y->getCalledFunction();
	// 			if (calledFunction != NULL){
	// 				if (alreadyInstrimented.find((uint64_t)calledFunction->getBaseAddr()) == alreadyInstrimented.end() && 
	// 					alreadyScheduled.find((uint64_t)calledFunction->getBaseAddr()) == alreadyScheduled.end())
	// 					funcsToInstriment.push(calledFunction);
	// 			}
	// 		}
	// 	} else {
	// 		std::cerr << "Could not find any function calls in : " << x->getName() << std::endl;
	// 	}		
	// }

	// std::set<uint64_t> funcsWrapped;
	// // Add Wappers to Sync Functions if they exist:
	// for (auto i : syncFunctions){
	// 	// Function is part of the public CUDA API. Do not rewrap.
	// 	if(std::find(_wrappedFunctions.begin(), _wrappedFunctions.end(),i ) != _wrappedFunctions.end())
	// 		continue;
		
	// 	// We need to perform the wrapping of this function here. 
	// 	// This wrapping is entry/exit function notification only since we do not know
	// 	// parameter counts/types for this function. 

	// 	// Find the function if we can...
	// 	std::vector<BPatch_function *> funcList;
	// 	_img->findFunction(i.c_str(), funcList);
	// 	if (funcList.size() == 0){
	// 		std::cerr << "Could not find the function " << i << " in the image" << std::endl;
	// 		continue;
	// 	}
	// 	assert(funcList.size() == 1);
	// 	std::cerr << "Inserting enter/exit instrimentation into sync call " << i << std::endl;

	// 	BPatch_function * x = funcList[0];
	// 	// We already wrapped this function
	// 	if (funcsWrapped.find((uint64_t)x->getBaseAddr()) != funcsWrapped.end()) {
	// 		std::cerr << "Already inserted instrimentation for func " << i << std::endl;
	// 		continue;
	// 	}
	// 	funcsWrapped.insert((uint64_t)x->getBaseAddr());
	// 	{
	// 		std::vector<BPatch_point*> * funcEntry = x->findPoint(BPatch_locEntry);
	// 		std::vector<BPatch_snippet*> testArgs;
	// 		testArgs.push_back(new BPatch_constExpr(_funcId));
	// 		BPatch_funcCallExpr recordFuncEntry(*_enterSync, testArgs);
	// 		std::cerr << x->getName() << "," << _funcId << std::endl;
	// 		if (_addrSpace->insertSnippet(recordFuncEntry,*funcEntry) == NULL) 
	// 			std::cerr << "could not insert func entry snippet" << std::endl;
	// 	}
	// 	{
	// 		std::vector<BPatch_point*> * FuncExit = x->findPoint(BPatch_locExit);
	// 		std::vector<BPatch_snippet*> testArgs;
	// 		testArgs.push_back(new BPatch_constExpr(_funcId));
	// 		BPatch_funcCallExpr recordFuncExit(*_exitSync, testArgs);
	// 		//std::cerr << x->getName() << "," << _funcId << std::endl;
	// 		if (_addrSpace->insertSnippet(recordFuncExit,*FuncExit) == NULL) 
	// 			std::cerr << "could not insert func exit snippet" << std::endl;
	// 	}		
	// 	std::cerr << "Instrimentation inserted into " << i << std::endl;
	// 	_funcId += 1;
	// }

	// // Final step is to mark the synchronization function
	// uint64_t sync_offset = INTERNAL_SYNC_LS;
	// BPatch_function * cudaSync = NULL;
	// Dyninst::Address offsetAddress = 0;
	// std::vector<BPatch_object *> imgObjs;
	// _img->getObjects(imgObjs);
	// for (auto i : imgObjs){
	// 	if (i->name().find("libcuda.so") == std::string::npos)
	// 		continue;
	// 	// Found libcuda
	// 	offsetAddress = i->fileOffsetToAddr(sync_offset);
	// 	cudaSync = _img->findFunction(offsetAddress);
	// 	break;
	// }
	// assert(cudaSync != NULL);
	// {
	// 	std::vector<BPatch_point*> * funcEntry = cudaSync->findPoint(BPatch_locEntry);
	// 	std::vector<BPatch_snippet*> testArgs;
	// 	BPatch_funcCallExpr recordFuncEntry(*_syncLibNotify, testArgs);
	// 	std::cerr << "Adding Sync Notifyer" << std::endl;
	// 	if (_addrSpace->insertSnippet(recordFuncEntry,*funcEntry) == NULL) 
	// 		std::cerr << "could not insert func entry snippet" << std::endl;
	// }

	// // Find exit call and insert a breakpoint at that location,
	// {
	// 	BPatch_breakPointExpr bp;
	// 	std::vector<BPatch_function *> funcList;
	// 	_img->findFunction("exit", funcList);
	// 	assert(funcList.size() > 0);
	// 	assert(funcList.size() == 1);
	// 	BPatch_Vector<BPatch_point *> * entry_points;
	// 	entry_points = funcList[0]->findPoint(BPatch_entry);
	// 	_addrSpace->insertSnippet(bp, *entry_points);
	// }


	// instUntil = _funcId;
	if (finalize)
		Finalize();

	return true;
}


void LoadStoreInst::Setup() {

	assert(_dynOps.FindFuncByName(_addrSpace, _entryFunction, std::string("RECORD_FUNCTION_ENTRY")) == 1);
	assert(_dynOps.FindFuncByName(_addrSpace, _exitingFunction, std::string("RECORD_FUNCTION_EXIT")) == 1);
	assert(_dynOps.FindFuncByName(_addrSpace, _enterSync, std::string("SYNC_CAPTURE_SYNC_CALL")) == 1);
	assert(_dynOps.FindFuncByName(_addrSpace, _recordMemAccess, std::string("SYNC_RECORD_MEM_ACCESS")) == 1);
	assert(_dynOps.FindFuncByLibnameOffset(_addrSpace, _libcudaSync, std::string("libcuda.so"), INTERNAL_SYNC_LS, false) == 1);
}


bool LoadStoreInst::InstrimentNewModule(BPatch_object * obj, bool finalize) {
	// Adds instrimentation to a module loaded at a later point in time.
	return false;
}

void LoadStoreInst::Finalize() {
	// Finalizes the insertion set of dyninst
	if (_started)
		_addrSpace->finalizeInsertionSet(false);
	_started = false;
}


void LoadStoreInst::BeginInsertionSet() {
	// Begin the insertion set;
	if(!_started)
		_addrSpace->beginInsertionSet();
	_started = true;
}
