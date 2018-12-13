#include "DyninstFunction.h"
DyninstFunction::DyninstFunction(std::shared_ptr<DyninstProcess> proc, BPatch_function * func, std::shared_ptr<InstrimentationTracker> tracker, std::shared_ptr<BinaryLocationIDMap> bmap) : 
		_proc(proc), _track(tracker), _func(func),  _bmap(bmap), _exitEntryDone(false) {
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

std::string DyninstFunction::PrintInst() {
	if (_insertedInst.size() == 0)
		return std::string("");

	std::stringstream ss;
	ss << "FUNCTION: " << _func->getName()  << " IN MODULE " << _obj->pathName() << std::endl;
	for (auto i : _instmap) {
		ss << "0x" << std::hex << i.first << ": " << i.second.first.format(0);
		if (_insertedInst.find(i.first) !=  _insertedInst.end()) {
			if (std::get<0>(_insertedInst[i.first]) == 1) {
				ss << " CALLTRACED ";
			} else if (std::get<0>(_insertedInst[i.first]) == -1){
				ss << " FAILED CALLTRACE ";
			}
			if (std::get<1>(_insertedInst[i.first]) == 1) {
				ss << " LS APPLIED ";
			} else if (std::get<1>(_insertedInst[i.first]) == -1){
				ss << " FAILED LS ";
			}			
		}
		ss << "\n";
	}
	return ss.str();
}

void DyninstFunction::EntryExitWrapping() {
	// Find the function calls being made
	if(_exitEntryDone == true)
		return;
	std::string libname = _obj->pathName();
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