#include <stdio.h>
#include "BPatch.h"
#include "BPatch_addressSpace.h"
#include "BPatch_process.h"
#include "BPatch_binaryEdit.h"
#include "BPatch_point.h"
#include "BPatch_function.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <functional>
#include <array>
#include <iostream>
#include <cassert>
#include <deque>
#include <sys/time.h>
#include <cstdlib>
#include <sstream>
#include <tuple>
#include <utility> 
#include <stdarg.h>
#include <map>
#include <set> 
#include <iomanip>
#include <string>
#include <sys/types.h>
#include <unistd.h>

// Dyninst includes
#include "CodeObject.h"
#include "CFG.h"
#include "PatchObject.h"
#include "PatchMgr.h"
#include "Point.h"
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

//using namespace std;
using namespace Dyninst;
using namespace ParseAPI;
using namespace PatchAPI;
using namespace SymtabAPI;

// Pulls all function symbols from binary, places them into textfile. 

int main(const int argc, const char * argv[]){
	BPatch patch;
	BPatch_binaryEdit * app = patch.openBinary(argv[1], true);
	BPatch_image * img = app->getImage();
	app->loadLibrary("/nobackup/spack_repo/opt/spack/linux-ubuntu16.04-x86_64/gcc-6.4.0/cudadedup-develop-mbsbiqg2zylptsgokmkjiehitydyfwtq/lib/plugins/libSynchTool.so");
	std::vector<BPatch_function *> tracerCall;
	std::vector<BPatch_function *> giStrlen;
	img->findFunction("SYNC_RECORD_FUNCTION_ENTRY", tracerCall);
	img->findFunction("__GI_strlen",giStrlen);
	std::vector<BPatch_point*> * funcEntry = giStrlen[0]->findPoint(BPatch_locEntry);
	std::vector<BPatch_snippet*> testArgs;
	testArgs.push_back(new BPatch_constExpr(0));
	BPatch_funcCallExpr recordFuncEntry(*(tracerCall[0]), testArgs);
	assert(img->getAddressSpace()->insertSnippet(recordFuncEntry,*funcEntry)!= NULL);
	if(!app->writeFile(argv[2])) {
		fprintf(stderr, "Could not write output file %s\n", argv[2]);
		return -1;
	}

	// std::ofstream pfile;
	// pfile.open(argv[2]);	
	// BPatch_image * img = app->getImage();
	// std::vector<BPatch_function *> funcs;
	// img->getProcedures(funcs, false);
	// for (auto i : funcs) {
	// 	if (i->getName().at(0) == 'c' && i->getName().at(1) == 'u') {
	// 		if (i->getName().find(std::string("__")) == std::string::npos) {
	// 			pfile << "" << std::hex << i->getBaseAddr() << std::dec << " " << i->getName() 
	// 			      << " 0x" << std::hex << i->getFootprint() << std::dec << std::endl;		
	// 		}
	// 	}
	// }
	pfile.close();
}