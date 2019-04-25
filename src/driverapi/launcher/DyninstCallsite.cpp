#include "DyninstCallsite.h"
DyninstCallsite::DyninstCallsite(std::shared_ptr<DyninstProcess> proc, BPatch_function * func, BPatch_point & point) : _proc(proc), _func(func), _point(point), _calledFunc(std::string("UNKNOWN")), _replaced(false) {
	BPatch_function * tmp = point.getCalledFunction();
	if (tmp == NULL)
		return;

	_calledFunc = tmp->getName();
}

uint64_t DyninstCallsite::GetPointAddress() {
	return (uint64_t)_point.getAddress();
}

std::string * DyninstCallsite::GetCalledFunction() {
	return &_calledFunc;
}
void DyninstCallsite::ReplaceFunctionCall(BPatch_function * _newCall) {
	if (_replaced)
		return;

	_replaced = true;

	BPatch_addressSpace * aspace = _proc->GetAddressSpace();

	aspace->replaceFunctionCall(_point, *_newCall);
}