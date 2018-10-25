#include "DynOpsClass.h"
DynOpsClass::DynOpsClass() {
	init = false;
}

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


void DynOpsClass::SetupPowerMap(BPatch_addressSpace * addr) {
	if (init)
		return;

	std::vector<BPatch_function *> all_functions;
	BPatch_image * _img = addr->getImage();
	_img->getProcedures(all_functions);
	for (auto i : all_functions) {
		if (_powerFuncmap.find((uint64_t)i->getBaseAddr()) != _powerFuncmap.end())
			assert("WE SHOULDN'T BE HERE" != 0);
		_powerFuncmap[(uint64_t)i->getBaseAddr()] = i;
	}
	init = true;
}

BPatch_function * DynOpsClass::GetPOWERFunction(BPatch_function * function) {
	SetupPowerMap(function->getAddSpace());
	uint64_t address = (uint64_t)function->getBaseAddr();
	if (_powerFuncmap.find(address + 0x8) != _powerFuncmap.end())
		return _powerFuncmap[address + 0x8];
	return function;

}
// BPatch_function * DynOpsClass::GetPOWERFunction(BPatch_function * function) { 
// 	// Returns the real function when using power.



// }

int DynOpsClass::FindFuncByName(BPatch_addressSpace * aspace, BPatch_function * & ret, std::string name) {
	if (aspace == NULL) 
		return -1;
	SetupPowerMap(aspace);
	BPatch_image * img = aspace->getImage();
	std::vector<BPatch_function *> tmp;
	img->findFunction(name.c_str(), tmp);
	if (tmp.size() > 0) 
		ret = GetPOWERFunction(tmp[0]);
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

std::vector<BPatch_function *> DynOpsClass::FindFunctionsByLibnameOffset(BPatch_addressSpace * aspace, std::string libname, uint64_t offset, bool exact) {
	std::vector<BPatch_function *> ret;
	if (aspace == NULL) 
		return ret;

	std::cerr << "Trying to find - " << libname << " at offset " << std::hex << offset << std::endl;
	BPatch_image * img = aspace->getImage();
	BPatch_object * obj = FindObjectByName(aspace, libname, exact);
	
	if (obj == NULL)
		return ret;
	std::vector<BPatch_point *> points;
	obj->findPoints(offset, points);
	//img->findFunction(obj->fileOffsetToAddr(offset), ret);
	for (auto i : points)
		ret.push_back(i->getFunction());
	std::cerr << "Found - " << ret.size() << " functions" << std::endl;
	return ret;
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

std::vector<BPatch_object *> DynOpsClass::GetObjects(BPatch_addressSpace * aspace) {
	BPatch_image * _img = aspace->getImage();
	std::vector<BPatch_object *> objects;
	img->getObjects(objects);
	return objects;
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