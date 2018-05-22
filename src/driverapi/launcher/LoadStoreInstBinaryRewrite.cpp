#include "LoadStoreInstBinaryRewrite.h"
#include "Instruction.h"

LoadStoreInstBinaryRewrite::LoadStoreInstBinaryRewrite(BinaryRewriter * rw) :
	_addrSpace(NULL), _img(NULL), _started(false), _funcId(0), _rw(rw) {
	_runOneTime = false;	
}

void LoadStoreInstBinaryRewrite::InsertEntryExitSnippets(BPatch_function * func, std::vector<BPatch_point*> * points) {
	std::string libname = func->getModule()->getObject()->pathName();
	_logFile << "[LoadStoreInstBinaryRewrite][EntryExit] Inserting entry exit instrimentation into - " << func->getName() << " with ids: ";
	for (auto i : *points) {
		// if (i->getCalledFunction() == NULL)
		// 	continue;
		// std::vector<std::pair<Dyninst::InstructionAPI::Instruction::Ptr, Dyninst::Address> > instructionVector;
		// i->getBlock()->getInstructions(instructionVector);
		// Dyninst::InstructionAPI::Instruction::Ptr pointInstruction = NULL;
		// for (auto z : instructionVector)
		// 	if(z.second == (uint64_t)i->getAddress())
		// 	{
		// 		pointInstruction = z.first;
		// 		break;
		// 	}
		// std::string instString;
		// if (pointInstruction != NULL)
		// 	instString = pointInstruction->format();
		// else 
		// 	continue;
		// if (instString.find("call") == std::string::npos)
		// 	continue;
		std::vector<BPatch_point*> singlePoint;
		singlePoint.push_back(i);
		uint64_t id;
		uint64_t libOffsetAddr = 0;
		if (_dynOps.GetFileOffset(func->getAddSpace(), i, libOffsetAddr, true))
			id = _binLoc.StorePosition(libname, libOffsetAddr);
		else
			id = _binLoc.StorePosition(libname, (uint64_t) i->getAddress());
		_logFile << "[LoadStoreInstBinaryRewrite][EntryExit] \tInstruction at point " << id << " , " << std::hex << (uint64_t) i->getAddress() << std::dec 
				 << " libname: " << libname << " libOffsetPosition: " << libOffsetAddr << std::endl;
		std::vector<BPatch_snippet*> recordArgs;
		recordArgs.push_back(new BPatch_constExpr(id));
		_entryFunction = NULL;
		_exitingFunction = NULL;
		assert(_dynOps.FindFuncByName(func->getAddSpace(), _entryFunction, std::string("RECORD_FUNCTION_ENTRY")) == 1);
		assert(_dynOps.FindFuncByName(func->getAddSpace(), _exitingFunction, std::string("RECORD_FUNCTION_EXIT")) == 1);		

		BPatch_funcCallExpr entryExpr(*_entryFunction, recordArgs);
		BPatch_funcCallExpr exitExpr(*_exitingFunction, recordArgs);
		//_logFile << id << ",";
		if (func->getAddSpace()->insertSnippet(entryExpr,singlePoint, BPatch_callBefore) == NULL) {
			_logFile << "[LoadStoreInstBinaryRewrite][EntryExit] \t\t ERROR! Could not insert entry tracking into " << func->getName() << std::endl;
		}
		if (func->getAddSpace()->insertSnippet(exitExpr,singlePoint,BPatch_callAfter) == NULL) {
			_logFile << "[LoadStoreInstBinaryRewrite][EntryExit] \t\t ERROR! Could not insert exit tracking into " << func->getName() << std::endl;
		}		
	}
}

void LoadStoreInstBinaryRewrite::WrapEntryAndExit(std::map<uint64_t, StackRecord> & syncStacks) {
	// Get all the functions in the binary
	// std::vector<BPatch_object *> objects;
	// _img->getObjects(objects);
	for (auto i : syncStacks) {
		std::vector<StackPoint> points = i.second.GetStackpoints();
		for (auto z : points) {
			BPatchBinaryPtr obj = _rw->FindAppBinary(z.libname);
			assert(obj.get() != NULL);
			_logFile << "[LoadStoreInstBinaryRewrite][EntryExit] Attempting to find - " << z.funcName << std::endl;
			BPatch_function * func;
			if(_dynOps.FindFuncByStackPoint(obj->GetAddressSpace(), func, z) <= 0){
				_logFile << "[LoadStoreInstBinaryRewrite][EntryExit] Could not find function - " << z.funcName << std::endl;
				continue;
			}
			std::vector<BPatch_point*> * funcCalls = func->findPoint(BPatch_locSubroutine);
			if (_instTracker.ShouldInstriment(func, funcCalls, CALL_TRACING)) {
				_logFile << "[LoadStoreInstBinaryRewrite][EntryExit] Inserting exit/entry info into - " << z.funcName << "," << func->getModule()->getObject()->pathName() << std::endl;
				InsertEntryExitSnippets(func, funcCalls);
			} else {
				_logFile << "[LoadStoreInstBinaryRewrite][EntryExit] Rejected function - " << z.funcName << std::endl;
			}		
		}
	}		
}	

void LoadStoreInstBinaryRewrite::InsertSyncNotifierSnippet(BPatch_function * func, uint64_t offset) {
	assert(func != NULL);
	std::vector<BPatch_point*> * entryPoints = func->findPoint(BPatch_locEntry);
	std::string tmp = func->getModule()->getObject()->pathName();
	uint64_t id = _binLoc.StorePosition(tmp,offset);
	std::vector<BPatch_snippet*> recordArgs;
	_enterSync = NULL;
	assert(_dynOps.FindFuncByName(func->getAddSpace(), _enterSync, std::string("SYNC_CAPTURE_SYNC_CALL")) == 1);	
	BPatch_funcCallExpr entryExpr(*_enterSync, recordArgs);
	if (func->getAddSpace()->insertSnippet(entryExpr,*entryPoints) == NULL) {
		std::cerr << "[LoadStoreInstBinaryRewrite][SyncNotifier] FATAL ERROR! Insertion of notifier into libcuda.so - failed! Callname: " << func->getName() << std::endl;
	}
}

void LoadStoreInstBinaryRewrite::InsertSyncCallNotifier() {
	InsertSyncNotifierSnippet(_libcudaSync, INTERNAL_SYNC_LS);
}

void LoadStoreInstBinaryRewrite::InsertLoadStoreSnippets(BPatch_function * func, std::vector<BPatch_point*> * points) {
	std::string libname = func->getModule()->getObject()->pathName();
	_logFile << "[LoadStoreInstBinaryRewrite][LoadStoreSnippet] Inserting load store instrimentation into - " << func->getName() << "," << func->getModule()->getObject()->pathName() << "\n";
	for (auto i : *points) {
		uint64_t libOffsetAddr = 0;
		uint64_t id = 0;
		std::vector<BPatch_point*> singlePoint;
		singlePoint.push_back(i);
		if (_dynOps.GetFileOffset(func->getAddSpace(), i, libOffsetAddr))
			id = _binLoc.StorePosition(libname, libOffsetAddr);
		else
			id = _binLoc.StorePosition(libname, (uint64_t) i->getAddress());
		std::vector<BPatch_snippet*> recordArgs;
		BPatch_snippet * loadAddr = new BPatch_effectiveAddressExpr();
		recordArgs.push_back(loadAddr);
		recordArgs.push_back(new BPatch_constExpr(id));
		_recordMemAccess = NULL;
		assert(_dynOps.FindFuncByName(func->getAddSpace(), _recordMemAccess, std::string("SYNC_RECORD_MEM_ACCESS")) == 1);
		BPatch_funcCallExpr recordAddrCall(*_recordMemAccess, recordArgs);
		if (func->getAddSpace()->insertSnippet(recordAddrCall,singlePoint) == NULL) {
			std::cerr << "[LoadStoreInstBinaryRewrite][LoadStoreSnippet]\t\tCould not insert load store instrimentation into " << id << " in function " << func->getName() << std::endl;
		}
	}
}


void LoadStoreInstBinaryRewrite::InsertLoadStoreInstrimentation() {
	for (auto m : _rw->GetAllBinaryObjects()) {
		std::vector<BPatch_function *> all_functions;
		m->GetImage()->getProcedures(all_functions);
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
}

void LoadStoreInstBinaryRewrite::WriteBinLocation(std::string outDir){
	_binLoc.WriteMap(outDir);
}

void LoadStoreInstBinaryRewrite::FixLSStackFiles() {
	// Converts:
	// LS_trace.bin -> {LS_trace.bin, LS_tracekey.txt}
	// LS_stackkey.bin -> LS_stackkey.txt
	std::cerr << "Runing onetime code on exit of LS" << std::endl;
	ReadLoadStoreFiles tmp(&_binLoc);
	tmp.OutputTraceKey(std::string("LS_trace.bin"), std::string("LS_tracekey.txt"));
	tmp.CreateStackKey(std::string("LS_stackkey.bin"), std::string("LS_stackkey.txt"));
}

LoadStoreInstBinaryRewrite::~LoadStoreInstBinaryRewrite() {
	// if(_runOneTime)
	// 	FixLSStackFiles();
}

void LoadStoreInstBinaryRewrite::SetWrappedFunctions(std::vector<std::string> & wrappedFunctions ) {
	_wrappedFunctions = wrappedFunctions;
	_instTracker.AddAlreadyInstrimented(wrappedFunctions);
}

bool LoadStoreInstBinaryRewrite::InstrimentAllModules(bool finalize, std::vector<uint64_t> & skips, uint64_t & instUntil, std::vector<std::string> & syncFunctions, 
										 std::vector<StackPoint> & points, std::map<uint64_t, StackRecord> & syncStacks) {
	Setup();
	//BeginInsertionSet();
	WrapEntryAndExit(syncStacks);
	InsertSyncCallNotifier();
	//InsertSyncCallNotifier(points);
	InsertLoadStoreInstrimentation();
	_runOneTime =true;
	if (finalize)
		Finalize();

	return true;
}


void LoadStoreInstBinaryRewrite::Setup() {
	_rw->OpenAllDependencies();
	for (auto i : _rw->GetAllBinaryObjects()) {
		if (i->GetName().find("libSynchTool") != std::string::npos)
			continue;
		i->LoadLibrary(std::string(LOCAL_INSTALL_PATH) + std::string("/lib/plugins/libSynchTool.so"));
	}

	// assert(_dynOps.FindFuncByName(_addrSpace, _entryFunction, std::string("RECORD_FUNCTION_ENTRY")) == 1);
	// assert(_dynOps.FindFuncByName(_addrSpace, _exitingFunction, std::string("RECORD_FUNCTION_EXIT")) == 1);
	// assert(_dynOps.FindFuncByName(_addrSpace, _enterSync, std::string("SYNC_CAPTURE_SYNC_CALL")) == 1);
	// assert(_dynOps.FindFuncByName(_addrSpace, _recordMemAccess, std::string("SYNC_RECORD_MEM_ACCESS")) == 1);
	BPatchBinaryPtr libcuda = _rw->LoadObject("libcuda.so");
	libcuda->LoadLibrary(std::string(LOCAL_INSTALL_PATH) + std::string("/lib/plugins/libSynchTool.so"));
	assert(_dynOps.FindFuncByLibnameOffset(libcuda->GetAddressSpace(), _libcudaSync, std::string("libcuda.so"), INTERNAL_SYNC_LS, false) == 1);
}


bool LoadStoreInstBinaryRewrite::InstrimentNewModule(BPatch_object * obj, bool finalize) {
	// Adds instrimentation to a module loaded at a later point in time.
	return false;
}

void LoadStoreInstBinaryRewrite::Finalize() {
	// Finalizes the insertion set of dyninst
	_started = false;
}


void LoadStoreInstBinaryRewrite::BeginInsertionSet() {
	// Begin the insertion set;
	_started = true;
}



void LoadStoreInstBinaryRewrite::InsertLoadStoresInit(std::vector<uint64_t> & skips, uint64_t & instUntil, std::vector<StackPoint> & points, std::map<uint64_t, StackRecord> & syncStacks, std::vector<std::string> wrappedFunctionNames) {
	// Check this....
	//LoadWrapperLibrary(std::string(LOCAL_INSTALL_PATH) + std::string("/lib/plugins/libStubLib.so"));
	for (auto i : syncStacks) {
		for (auto z : i.second.GetStackpoints()) {
		 	if (z.libname.find(".so") != std::string::npos)
		 		_rw->LoadObject(z.libname);
		}
	}
	std::vector<std::string> synchFunctions;

	for (auto i : points) {
		synchFunctions.push_back(i.funcName);
		//synchFunctions.push_back(i.fname);
	}

	SetWrappedFunctions(wrappedFunctionNames);
	InstrimentAllModules(true, skips, instUntil, synchFunctions, points,syncStacks);
}