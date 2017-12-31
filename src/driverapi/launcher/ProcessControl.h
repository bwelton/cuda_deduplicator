#pragma once
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
#include "dynC.h"
#include "set"
#include <boost/program_options.hpp>

using namespace Dyninst;
using namespace ParseAPI;
using namespace PatchAPI;
using namespace SymtabAPI;

class ProcessController {
public:
	ProcessControler(boost::program_options::variables_map vm);
	BPatch_addressSpace * LaunchProcess();
	BPatch * GetBPatch();
	
private:
	BPatch bpatch;
	boost::program_options::variables_map _vm;
	BPatch_addressSpace * _addrSpace;
	bool _launched;
};