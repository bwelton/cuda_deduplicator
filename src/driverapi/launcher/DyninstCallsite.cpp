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

uint64_t DyninstCallsite::GetPointFileAddress() {
	uint64_t libOffsetAddr = 0;
	if (!_proc->ReturnDynOps()->GetFileOffset(_proc->GetAddressSpace(), &_point, libOffsetAddr, true))
		libOffsetAddr = GetPointAddress();
	return libOffsetAddr;
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

uint64_t DyninstCallsite::ReplaceFunctionCallWithID(int64_t id) {
	if (_replaced)
		return;

	//_replaced = true;

	BPatch_addressSpace * aspace = _proc->GetAddressSpace();

	BPatch_image * img = aspace->getImage();
	BPatch_variableExpr * var = img->findVariable("DIOGENES_CTX_ID");

	assert(var != NULL);

	BPatch_arithExpr setVal(BPatch_assign, *var, BPatch_constExpr(id));
	std::vector<BPatch_point*> singlePoint;
	singlePoint.push_back(_point);
	assert(_proc->GetAddressSpace()->insertSnippet(setVal,singlePoint,BPatch_callBefore) != NULL);
	ReplaceFunctionCall();
	return GetPointAddress();
}