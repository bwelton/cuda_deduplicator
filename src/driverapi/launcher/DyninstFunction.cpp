#include "DyninstFunction.h"
DyninstFunction::DyninstFunction(std::shared_ptr<DyninstProcess> proc, BPatch_function * func, std::shared_ptr<InstrimentationTracker> tracker) : _proc(proc), _track(tracker), _func(func) {
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
}
