#include "TimerInstrimentation.h"
TimerInstrimentation::TimerInstrimentation(BPatch_addressSpace * addrSpace, BPatchBinaryPtr binary) :
 _addrSpace(addrSpace), _bpBinary(binary) {

} 

void TimerInstrimentation::GetModules(std::map<std::string, BPatch_object *> & objs){
	std::vector<BPatch_object *> objects;
	BPatch_image * img = _addrSpace->getImage();
	img->getObjects(objects);
	for (auto i : objects) {
		objs[i->pathName()] = i;
	}
}

void TimerInstrimentation::InsertTimers(std::vector<StackPoint> points) {
	// Load the timing plugin

	std::vector<BPatch_function *> startFunc;
	std::vector<BPatch_function *> stopFunc;
	BPatch_image * img = _addrSpace->getImage();
	img->findFunction("TIMER_SIMPLE_TIME_START", startFunc);
	img->findFunction("TIMER_SIMPLE_TIME_STOP", stopFunc);
	assert(startFunc.size() > 0);
	assert(stopFunc.size() > 0);
	std::map<std::string, BPatch_object *> objs;
	GetModules(objs);
	_addrSpace->beginInsertionSet();
	// Insert timer to add one every time a syncrhonization is called
	{
		BPatch_object * libcudaObj = NULL;
		for (auto z : objs) {
			if (z.first.find("libcuda.so") != std::string::npos){
				libcudaObj = z.second;
				break;
			}
		}
		assert(libcudaObj != NULL);
		BPatch_function * syncFunction = NULL;
		syncFunction = img->findFunction(libcudaObj->fileOffsetToAddr(INTERNAL_SYNC_C));
		if (syncFunction == NULL) {
			syncFunction = _ops.FindFunctionByOffset(_addrSpace, libcudaObj, libcudaObj->fileOffsetToAddr(INTERNAL_SYNC_C));
		}
		assert(syncFunction != NULL);
		std::vector<BPatch_function *> addFunction;
		img->findFunction("TIMER_SIMPLE_COUNT_ADD_ONE", addFunction);
		assert(addFunction.size() > 0);
		std::vector<BPatch_point*> * funcEntry = syncFunction->findPoint(BPatch_locEntry);
		std::vector<BPatch_snippet*> testArgs;
		BPatch_funcCallExpr recordFuncEntry(*(addFunction[0]), testArgs);
		assert(_addrSpace->insertSnippet(recordFuncEntry,*funcEntry) != NULL);
	}
	std::cout << "[TimerInstrimentation] Inserting timers into " << points.size() << " functions " << std::endl;
	// Insert Entry/Exit calls for synchronous functions
	for (auto i : points) {
		BPatch_object * curObj = NULL;
		for (auto z : objs) {
			if (i.libname == z.first){
				curObj = z.second;
				break;
			}
		}
		if (curObj == NULL) {
			std::cout << "[TimerInstrimentation] Could not find - " << i.libname << " resorting to manual insertion" << std::endl;
			_bpBinary->LoadLibrary(i.libname);
			objs[i.libname] = _ops.FindObjectByName(_addrSpace, i.libname);
			assert(objs[i.libname] != NULL);
			curObj = objs[i.libname];
		}

		BPatch_function * instFunc = NULL;
		assert(curObj != NULL);
		if (i.funcName.find("targ") == std::string::npos)
			assert(_ops.FindFuncByName(_addrSpace, instFunc, i.funcName));
		else {
			std::string tmp_funcName = i.funcName;
			tmp_funcName.erase(0,4);
			std::cout << "[TimerInstrimentation] Looking for targ function at location: " << tmp_funcName << std::endl;
			tmp_funcName = std::string("0x") + tmp_funcName;
			instFunc = _ops.FindFunctionByOffset(_addrSpace, curObj, curObj->fileOffsetToAddr(std::stoull(tmp_funcName, NULL, 16)));
		}
		assert(instFunc != NULL);
		// if (i.inMain)
		// 	instFunc = img->findFunction(i.funcOffset);
		// else{
		// 	assert(curObj->fileOffsetToAddr(i.funcOffset) != -1);
		// 	instFunc = img->findFunction(curObj->fileOffsetToAddr(i.funcOffset));
		// }
		std::cout << "[TimerInstrimentation] Inserting timing Instrimentation into - " << instFunc->getName() << std::endl;
		std::cout << "[TimerInstrimentation] Function Name: " << i.funcName << ","<< i.funcName << "," << i.timerID << std::endl;
		assert(instFunc != NULL);
		assert(instFunc->getName() == i.funcName);
		std::vector<BPatch_point*> * funcEntry = instFunc->findPoint(BPatch_locEntry);
		std::vector<BPatch_point*> * funcExit = instFunc->findPoint(BPatch_locExit);
		assert(funcEntry->size() > 0);
		assert(funcExit->size() > 0);
		std::vector<BPatch_snippet*> testArgs;
		testArgs.push_back(new BPatch_constExpr(i.timerID));
		BPatch_funcCallExpr recordFuncEntry(*(startFunc[0]), testArgs);
		BPatch_funcCallExpr recordFuncExit(*(stopFunc[0]), testArgs);
		assert(_addrSpace->insertSnippet(recordFuncEntry,*funcEntry) != NULL);
		assert(_addrSpace->insertSnippet(recordFuncExit,*funcExit) != NULL); 
	}
	assert(_addrSpace->finalizeInsertionSet(false) == true);
}