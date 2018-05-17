#pragma once
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>
#include <cassert>
#include <fstream>
#include "BinaryRewriter.h"
#include "StacktraceInst.h"
#include "Constants.h"
#include "StackPoint.h"
#include "SymbolLookup.h"
#include "StackStorage.h"
#include "CallIDGenerator.h"

class StageTwo {
public:
	StageTwo(boost::program_options::variables_map vm);
	bool Run();
	void ExtractLineInfo(std::map<uint64_t, StackRecord> & rec);
	std::map<uint64_t, std::vector<StackPoint> >  ReadStackKey();
private:
	boost::program_options::variables_map _vm;	
	BinaryRewriter _rw;
	std::map<uint64_t, StackRecord> _stackRecords;
	boost::filesystem::path _stageOnePath;
	boost::filesystem::path _stageTwoPath;
};

StageTwo::StageTwo(boost::program_options::variables_map vm) :
	_vm(vm) {
	std::vector<std::string> progName = _vm["prog"].as<std::vector<std::string> >();
	_stageOnePath = boost::filesystem::current_path();
	_stageTwoPath = boost::filesystem::current_path();
	_stageOnePath /= "stageOne";
	_stageTwoPath /= "stageTwo";
	boost::filesystem::path dependsFile = _stageOnePath;
	dependsFile /= "NI_dependencies.txt";
	_rw = BinaryRewriter(progName[0], true, std::string("stageTwo"),true, dependsFile.string());
}

std::map<uint64_t, std::vector<StackPoint> >  StageTwo::ReadStackKey() {
	boost::filesystem::path keyFile = _stageOnePath;
	_stageOnePath /= "NI_synchronizations.key";
	StackKeyReader reader(keyFile.string());
	return reader.ReadStacks();
}

void StageTwo::ExtractLineInfo(std::map<uint64_t, StackRecord> & rec) {
	SymbolMap symbolInfo;
	
	// Open all symtabs for functions found on the stack. 
	for (auto i : rec) {
		std::vector<std::string> lnames = i.second.GetLibNames();
		for (auto z : lnames){
			if (symbolInfo.find(z) == symbolInfo.end())
				symbolInfo[z] = std::shared_ptr<SymbolLookup>(new SymbolLookup(z));
		}	
	}

	for (auto & i : rec)
		i.second.GetStackSymbols(symbolInfo);
}

void StageTwo::Run() {
	std::map<uint64_t, std::vector<StackPoint> > ret = ReadStackKey();
	for (auto & i : ret)
		_stackRecords[i.first] = StackRecord(i.first, i.second);
	ExtractLineInfo(_stackRecords);
	boost::filesystem::path idMap = _stageTwoPath; 
	idMap /= "TF_timerIdMap.txt";
	CallIDGenerator cmap(idMap.string(), true);
	for (auto & i : _stackRecords) {
		std::cerr << "Adding " << i.second.GetFirstCudaCall().funcName << " with hash id " << i.first << std::endl;
		cmap.InsertStackID(i.second.GetFirstCudaCall().funcName, i.first);
	}

}

class TimerInstrimentation {
public:
	TimerInstrimentation(BPatch_addressSpace * addrSpace, BPatchBinaryPtr binary);
	void InsertTimers(std::vector<StackPoint> points);
	void GetModules(std::map<std::string, BPatch_object *> & objs);
private:
	DynOpsClass _ops;
	BPatch_addressSpace * _addrSpace;
	BPatchBinaryPtr _bpBinary;
};

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
		instFunc = _ops.FindFunctionByOffset(_addrSpace, curObj, curObj->fileOffsetToAddr(i.funcOffset) );
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