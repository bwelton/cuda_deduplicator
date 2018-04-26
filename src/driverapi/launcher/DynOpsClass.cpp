#include "DynOpsClass.h"
DynOpsClass::DynOpsClass() {}

int DynOpsClass::FindFuncByStackPoint(BPatch_addressSpace * aspace, BPatch_function * & ret, StackPoint & point) {
	if (aspace == NULL) 
		return -1;
	int tmp = 0;
	if (point.funcOffset > 0)
		tmp = FindFuncByLibnameOffset(aspace, ret, point.libname, point.funcOffset);
	if (tmp <= 0)
		tmp = FindFuncByName(aspace, ret, point.funcName);

	return tmp; 
}

int DynOpsClass::FindFuncByName(BPatch_addressSpace * aspace, BPatch_function * & ret, std::string name) {
	if (aspace == NULL) 
		return -1;
	BPatch_image * img = aspace->getImage();
	std::vector<BPatch_function *> tmp;
	img->findFunction(name.c_str(), tmp);
	if (tmp.size() > 0) 
		ret = tmp[0];
	return tmp.size();
}

BPatch_object * DynOpsClass::FindObjectByName(BPatch_addressSpace * aspace, std::string & name, bool exact) {
	if (aspace == NULL) 
		return NULL;
	BPatch_image * img = aspace->getImage();
	std::vector<BPatch_object *> objects;
	img->getObjects(objects);
	for (auto i : objects){ 
		if (exact) {
			if (i->pathName() == name)
				return i;
		} else {
			if (i->pathName().find(name) != std::string::npos)
				return i;
		}
	}
	return NULL;
}

int DynOpsClass::FindFuncByLibnameOffset(BPatch_addressSpace * aspace, BPatch_function * & ret, std::string libname, uint64_t offset, bool exact) {
	if (aspace == NULL) 
		return -1;
	BPatch_image * img = aspace->getImage();
	BPatch_object * obj = FindObjectByName(aspace, libname, exact);
	
	if (obj == NULL)
		return -1;

	BPatch_function * func = img->findFunction(obj->fileOffsetToAddr(offset));
	if (func == NULL)
		return 0;
	ret = func;
	return 1;
}

bool DynOpsClass::GetFileOffset(BPatch_addressSpace * aspace, BPatch_point * point, uint64_t & addr) {
	char tmp[32];
	if (point->getFunction() == NULL)
		return false;
	InstructionAPI::Instruction::Ptr tmp22 = point->getInsnAtPoint();
	int size = point->getDisplacedInstructions(32, &tmp);
	if (point->getFunction()->getModule()->isSharedLib())
		addr = (uint64_t)point->getAddress() - (uint64_t)point->getFunction()->getModule()->getBaseAddr() + size;
	else
		addr = (uint64_t)point->getAddress();
	return true;
}