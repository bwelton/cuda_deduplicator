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
	std::cout << "[DynOpsClass] Found function " << name << " " << tmp.size() << " times" << std::endl;
	return tmp.size();
}

BPatch_function * DynOpsClass::FindFunctionByOffset(BPatch_addressSpace * aspace, BPatch_object * obj, uint64_t offset) {
	std::vector<BPatch_module *> mods;
	obj->modules(mods);
	for (auto i : mods) {
		std::vector<BPatch_function*> procs;
		i->getProcedures(procs, true);
		for (auto z : procs) {
			if((uint64_t)z->getBaseAddr() == offset)
				return z;
		}
	}
	return NULL;
}

std::vector<std::string> DynOpsClass::GetLibraryNames(BPatch_addressSpace * aspace) {
	std::vector<std::string> ret;
	BPatch_image * img = aspace->getImage();
	std::vector<BPatch_object *> objects;
	img->getObjects(objects);
	for (auto i : objects){  
		ret.push_back(i->pathName());
	}		
	return ret;
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

// Hack to get around point->getInsnAtPoint() not wokring
Dyninst::InstructionAPI::Instruction::Ptr DynOpsClass::FindInstructionAtPoint(BPatch_point * point) {
	std::vector<std::pair<Dyninst::InstructionAPI::Instruction::Ptr, Dyninst::Address> > instructionVector;
	point->getBlock()->getInstructions(instructionVector);
	bool found = false;
	for (auto z : instructionVector) {
		if(z.second == (uint64_t)point->getAddress()) {
			found = true;
			return z.first;
		} else if (found == true) {
			 
		}
	}
	return NULL;
}


bool DynOpsClass::GetFileOffset(BPatch_addressSpace * aspace, BPatch_point * point, uint64_t & addr, bool addInstSize) {
	if (point->getFunction() == NULL)
		return false;
	auto inst = FindInstructionAtPoint(point);
	size_t size = 0;
	if (inst != NULL && addInstSize){
		size = inst->size();
	}
	if (point->getFunction()->getModule()->isSharedLib())
		addr = (uint64_t)point->getAddress() - (uint64_t)point->getFunction()->getModule()->getBaseAddr() + size;
	else
		addr = (uint64_t)point->getAddress() + size;
	return true;
}