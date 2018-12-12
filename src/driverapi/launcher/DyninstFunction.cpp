#include "DyninstFunction.h"
DyninstFunction::DyninstFunction(std::shared_ptr<DyninstProcess> proc, BPatch_function * func, std::shared_ptr<InstrimentationTracker> tracker, std::shared_ptr<BinaryLocationIDMap> bmap) : 
		_proc(proc), _track(tracker), _func(func),  _bmap(bmap) {
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