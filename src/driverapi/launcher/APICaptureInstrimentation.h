#pragma once
#include "DyninstProcess.h"
#include "Constants.h"
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <string>
#include <vector>
#include <map>
#include <cassert>
#include <iostream>
#include <memory>
#include <algorithm>
#include <sys/types.h>
#include <unistd.h>

#include "DynOpsClass.h"
#include "Common.h"

// Dyninst includes
#include "CodeObject.h"
#include "CFG.h"
#include "PatchObject.h"
#include "PatchMgr.h"
#include "Point.h"
#include "BPatch_object.h"
#include "BPatch_snippet.h"
#include "BPatch.h"
#include "BPatch_binaryEdit.h"
#include "BPatch_image.h"
#include "BPatch_function.h"
#include "BPatch_Vector.h"
#include "BPatch_point.h"
#include "BPatch_addressSpace.h"
#include "BPatch_statement.h"
#include "BPatch_basicBlock.h"
#include "dynC.h"
#include "set"
#include "LogInfo.h"
#include "Constants.h"
#include "StackPoint.h"
#include "StackStorage.h"

using namespace Dyninst;
using namespace ParseAPI;
using namespace PatchAPI;
using namespace SymtabAPI;

class APICaptureInstrimentation {
public:
	APICaptureInstrimentation(std::shared_ptr<DyninstProcess> proc);
	bool InsertInstrimentation();
private:
	std::shared_ptr<DyninstProcess> _proc;
};

APICaptureInstrimentation::APICaptureInstrimentation(std::shared_ptr<DyninstProcess> proc) : _proc(proc) { 

}

bool APICaptureInstrimentation::InsertInstrimentation() {
	std::shared_ptr<DynOpsClass> ops = _proc->ReturnDynOps();
	BPatch_object * libCuda = _proc->LoadLibrary(std::string("libcuda.so.1"));
	BPatch_object * driverAPIWrapper = _proc->LoadLibrary(std::string(LOCAL_INSTALL_PATH) + std::string("/lib/libDriverAPIWrapper.so"));
	std::vector<BPatch_function *> binderFunction = ops->FindFuncsByName(_proc->GetAddressSpace(), std::string("DefineBinders"), driverAPIWrapper);

	// We expect only a single call with this name, fail if there is more than one.
	assert(binderFunction.size() == 1);

	std::vector<BPatch_snippet*> recordArgs;
	BPatch_funcCallExpr entryExpr(*(binderFunction[0]), recordArgs);
	std::cerr << "[APICaptureInstrimentation::InsertInstrimentation] Fireing off one time call to setup API Capture Instrimentation\n";
	dynamic_cast<BPatch_process*>(_proc->GetAddressSpace())->oneTimeCode(entryExpr);
}


