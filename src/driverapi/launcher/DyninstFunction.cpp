#include "DyninstFunction.h"
DyninstFunction::DyninstFunction(std::shared_ptr<DyninstProcess> proc, BPatch_function * func, std::shared_ptr<InstrimentationTracker> tracker, std::shared_ptr<BinaryLocationIDMap> bmap) : 
		_proc(proc), _track(tracker), _func(func),  _bmap(bmap), _exitEntryDone(false), _lsDone(false) {
	_obj = _func->getModule()->getObject();
	std::shared_ptr<DynOpsClass> ops = proc->ReturnDynOps();
	ops->GetBasicBlocks(func, _bblocks);
	std::vector<std::pair<Dyninst::InstructionAPI::Instruction, Dyninst::Address> > instructionVector;
	for (auto i : _bblocks) {
		instructionVector.clear();
		i->getInstructions(instructionVector);
		for (auto n : instructionVector) {
			_instmap[(uint64_t) n.second]  = std::make_pair(n.first, i);
		}
	}
	_entrySize = GetSmallestEntryBlockSize();

}

std::string DyninstFunction::PrintInst(InstStats & stats) {
	bool stackTraced = false;
	bool lsInstrimented = false;
	std::stringstream ss;
	if (_insertedInst.size() == 0){
		ss <<"FUNCTION: " << _func->getName()  << " IN MODULE " << _obj->pathName() << " NO INST" << std::endl;
		return ss.str();
	}

	//ss << "FUNCTION: " << _func->getName()  << " IN MODULE " << _obj->pathName() << std::endl;
	for (auto i : _instmap) {
		ss << "0x" << std::hex << i.first << ": " << i.second.first.format(0);
		if (_insertedInst.find(i.first) !=  _insertedInst.end()) {
			if (std::get<0>(_insertedInst[i.first]) == 1) {
				stats.callTracedInsts++;
				std::string tmp = i.second.first.format(0);
				stats.ct_instNames.insert(tmp.substr(0, tmp.find(' ')));
				ss << " CALLTRACED ";
				stackTraced = true;
			} else if (std::get<0>(_insertedInst[i.first]) == -1){
				ss << " FAILED CALLTRACE ";
			}
			if (std::get<1>(_insertedInst[i.first]) == 1) {
				stats.lsInsts++;
				std::string tmp = i.second.first.format(0);
				stats.ls_instNames.insert(tmp.substr(0, tmp.find(' ')));
				ss << " LS APPLIED ";
				lsInstrimented = true;
			} else if (std::get<1>(_insertedInst[i.first]) == -1){
				ss << " FAILED LS ";
			}			
		}
		ss << "\n";
	}
	std::string ret = ss.str();
	ss.str(std::string());
	ss <<  "FUNCTION: " << _func->getName()  << " IN MODULE " << _obj->pathName() << (stackTraced ? " FUNC_STACKTRACED " : " ") << (lsInstrimented ? " FUNC_LSINSTRIMENTED " : " " ) << std::endl;
	return ss.str() + ret;
}

void DyninstFunction::EntryExitWrapping() {
	// Find the function calls being made
	if(_exitEntryDone == true)
		return;
	std::string libname = _obj->pathName();
	// Skip entry/exit instrimentation on libcuda
	if (libname.find("libcuda.so") != std::string::npos) {
		_exitEntryDone = true;
		return;
	}
	std::shared_ptr<DynOpsClass> ops = _proc->ReturnDynOps();
	std::vector<BPatch_function *> entryFuncs = ops->FindFuncsByName(_proc->GetAddressSpace(), std::string("RECORD_FUNCTION_ENTRY"), NULL);
	std::vector<BPatch_function *> exitFuncs = ops->FindFuncsByName(_proc->GetAddressSpace(), std::string("RECORD_FUNCTION_EXIT"), NULL);
	assert(entryFuncs.size() == 1);
	assert(exitFuncs.size() == 1);
	std::vector<BPatch_point*> * funcCalls = _func->findPoint(BPatch_locSubroutine);
	for (auto i : *funcCalls)  {
		std::vector<BPatch_point*> singlePoint;
		singlePoint.push_back(i);
		uint64_t id;
		int writeValue = 0;
		uint64_t libOffsetAddr = 0;
		if (!ops->GetFileOffset(_proc->GetAddressSpace(), i, libOffsetAddr, true))
			libOffsetAddr = (uint64_t) i->getAddress();

		if (_bmap->AlreadyExists(libname, libOffsetAddr)) {
			writeValue = -1;
		} else {
			writeValue = 1;
			id = _bmap->StorePosition(libname, libOffsetAddr);
			std::vector<BPatch_snippet*> recordArgs;
			recordArgs.push_back(new BPatch_constExpr(id));
			BPatch_funcCallExpr entryExpr(*entryFuncs[0], recordArgs);
			BPatch_funcCallExpr exitExpr(*exitFuncs[0], recordArgs);

			if (_proc->GetAddressSpace()->insertSnippet(entryExpr,singlePoint, BPatch_callBefore) == NULL) {
				std::cerr << "[LoadStoreInst][EntryExit] \t\t ERROR! Could not insert entry tracking into " << _func->getName() << std::endl;
			}
			if (_proc->GetAddressSpace()->insertSnippet(exitExpr,singlePoint,BPatch_callAfter) == NULL) {
				std::cerr << "[LoadStoreInst][EntryExit] \t\t ERROR! Could not insert exit tracking into " << _func->getName() << std::endl;
			}
		}

		if(_insertedInst.find((uint64_t)i->getAddress()) == _insertedInst.end()){
			_insertedInst[(uint64_t)i->getAddress()] = std::make_tuple(writeValue,0);
		} else {
			assert(std::get<0>(_insertedInst[(uint64_t)i->getAddress()]) == 0);
			std::get<0>(_insertedInst[(uint64_t)i->getAddress()]) = writeValue;
		}
	}
	_exitEntryDone = true;
}

void DyninstFunction::InsertLoadStoreAnalysis() {
	if (IsExcludedFunction(LOAD_STORE_INST) || _lsDone){
		_lsDone = true;
		return;
	}
	_lsDone = true;
	std::shared_ptr<DynOpsClass> ops = _proc->ReturnDynOps();
	std::vector<BPatch_function *> recordMemAccess = ops->FindFuncsByName(_proc->GetAddressSpace(), std::string("SYNC_RECORD_MEM_ACCESS"), NULL);
	assert(recordMemAccess.size() == 1);
	std::string libname = _obj->pathName();
	std::set<BPatch_opCode> axs;
	axs.insert(BPatch_opLoad);
	axs.insert(BPatch_opStore);
	std::vector<BPatch_point*> * loadsAndStores = _func->findPoint(axs);
	std::set<uint64_t> exclude;
	GenExclusionSet(exclude);
	for (auto i : *loadsAndStores) {
		int writeValue = 0;
		uint64_t addr = (uint64_t)i->getAddress();
		if (exclude.find(addr) != exclude.end()) {
			writeValue = -1;
		} else {
			uint64_t libOffsetAddr = 0;
			if (!ops->GetFileOffset(_proc->GetAddressSpace(), i, libOffsetAddr, true))
				libOffsetAddr = (uint64_t) i->getAddress();
			if(_bmap->AlreadyExists(libname, libOffsetAddr)){
				writeValue = -1;
			} else {
				std::vector<BPatch_point*> singlePoint;
				singlePoint.push_back(i);
				writeValue = 1;
				uint64_t id = _bmap->StorePosition(libname, libOffsetAddr);
				std::vector<BPatch_snippet*> recordArgs;
				BPatch_snippet * loadAddr = new BPatch_effectiveAddressExpr();
				recordArgs.push_back(loadAddr);
				recordArgs.push_back(new BPatch_constExpr(id));
				BPatch_funcCallExpr recordAddrCall(*(recordMemAccess[0]), recordArgs);
				assert(_proc->GetAddressSpace()->insertSnippet(recordAddrCall,singlePoint) != NULL);
			}
		}
		if(_insertedInst.find((uint64_t)i->getAddress()) == _insertedInst.end()){
			_insertedInst[(uint64_t)i->getAddress()] = std::make_tuple(0,writeValue);
		} else {
			assert(std::get<1>(_insertedInst[(uint64_t)i->getAddress()]) == 0);
			std::get<1>(_insertedInst[(uint64_t)i->getAddress()]) = writeValue;
		}
	}
}
uint64_t DyninstFunction::HandleEmulated(BPatch_basicBlock * block) {
	// Returns the address of the reserveration use instruction.
	std::vector<std::pair<Dyninst::InstructionAPI::Instruction, Dyninst::Address> > instructionVector;
	block->getInstructions(instructionVector);
	for (auto i : instructionVector) {
		std::string tmp = i.first.format(0);
		// Use of reservation instructions
		if (tmp.find("stbcx") != std::string::npos ||
			tmp.find("sthcx") != std::string::npos ||
			tmp.find("stwcx") != std::string::npos ||
			tmp.find("stdcx") != std::string::npos || 
			tmp.find("stqcx") != std::string::npos ) {
			return i.second + 4;
		}		
	}
	assert("SHOULD NOT BE HERE" == 0);
	return 0;
}
void DyninstFunction::GenExclusionSet(std::set<uint64_t> & excludedAddress) {
	// This is a set of instructions that should never be profiled.
	// Right now in this set is all instructions with the following properties:
	// 1. Ranges of emulated instructions. 
	// 2. stfq instructions
	
	for (auto i : _instmap) {
		std::string tmp = i.second.first.format(0);
		// Reservation Instructions
		// Find emulated start/end
		if (tmp.find("lwarx") != std::string::npos || 
			tmp.find("lbarx") != std::string::npos ||
			tmp.find("lharx") != std::string::npos ||
			tmp.find("ldarx") != std::string::npos ||
			tmp.find("lqarx") != std::string::npos ){
			uint64_t endingAddress = HandleEmulated(i.second.second);
			excludedAddress.insert(i.first);
			assert(endingAddress > i.first);
			for (uint64_t t = i.first; t < endingAddress + 4; t = t + 4) 
				excludedAddress.insert(t);				
		} else {
			if (tmp.find("stfq ") != std::string::npos)
				excludedAddress.insert(i.first);
			else if (tmp.find("[r1 +") != std::string::npos || tmp.find("[r1 -") != std::string::npos)
				excludedAddress.insert(i.first);
		}
	}

}

uint64_t DyninstFunction::GetSmallestEntryBlockSize() {
	BPatch_flowGraph * fg = _func->getCFG();
	std::vector<BPatch_basicBlock *> entry;
	uint64_t smallest = 100000000;
	assert(fg->getEntryBasicBlock(entry) == true);
	for (auto i : entry) {
		uint64_t cur = (uint64_t) i->getStartAddress();
		uint64_t size = _instmap[cur].first.size();
		while (1) {
			uint64_t next = cur + _instmap[cur].first.size();
			if (_instmap.find(next) == _instmap.end())
				break;
			cur = next;
			size += _instmap[cur].first.size();
		}
		if (size < smallest)
			smallest = size;
	}
	return smallest;
}

bool DyninstFunction::IsExcludedFunction(InstType T) {
	if (_track->ShouldInstrimentFunciton(_func, T) && _track->ShouldInstrimentModule(_func, T))
		return false;
	return true;

}