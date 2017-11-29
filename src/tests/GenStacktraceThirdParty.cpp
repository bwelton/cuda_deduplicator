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
using namespace Dyninst;
using namespace ParseAPI;
using namespace PatchAPI;
using namespace SymtabAPI;


std::vector<std::string> funcNames;
BPatch_addressSpace * addrs;
BPatch bpatch;
bool loaded;

BPatch_addressSpace * LaunchProcess(const char * name, const char * argv[]) {
	BPatch_addressSpace * handle = NULL;
	handle = bpatch.processCreate(name, argv);
	assert(handle != NULL);
	return handle;
}

void InsertBreakpoints(BPatch_module * mod){
	if (loaded == true)
		return;
	BPatch_breakPointExpr bp;
	//BPatch_Vector<BPatch_function *> * allFuncs = mod->getProcedures(true);
	BPatch_Vector<BPatch_point *> points;
	for(auto i : funcNames) {
		BPatch_Vector<BPatch_function *> funcs;
		BPatch_Vector<BPatch_function *> * tmp = mod->findFunction(i.c_str(), funcs, true, false, false, false);
		if (tmp == NULL)
			continue;
		BPatch_Vector<BPatch_point *> * entry_points;
		entry_points = (*tmp)[0]->findPoint(BPatch_entry);
		points.insert(points.end(), entry_points->begin(), entry_points->end());
		std::cerr << "Inserting instrimentation into " << i << std::endl;
	}
	if(!addrs->insertSnippet(bp, points)) {
		fprintf(stderr, "%s\n", "InsertFailed");
		exit(-1);
	}
}

// bool InsertBreakpointsBeforeLaunch() {
// 	bool ret = false;

// }

void LibLoadedCallBack(BPatch_thread * thread, BPatch_module * mod, bool loaded) {
	char * name = (char *) malloc(500 * sizeof(char));
	name = mod->getName(name, 500);
	std::string tmp = std::string(name);
	std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
	if (tmp.find(std::string("libcuda.so")) != std::string::npos) {
		// We have found libcuda, trigger instrimentation
		InsertBreakpoints(mod);
	}
	loaded = true;
}

std::vector<std::string> GetFunctionNames(const char * file) {
	std::vector<std::string> ret;
	std::ifstream t;
	std::string line;
	t.open(file,std::ifstream::in);
	while (std::getline(t, line)) {
		ret.push_back(line);
	}
	return ret;
}

int main(const int argc, const char * argv[]){
	loaded = false;
	funcNames = GetFunctionNames(argv[1]);
	addrs = LaunchProcess(argv[2], &(argv[2]));
	bpatch.registerDynLibraryCallback((BPatchDynLibraryCallback)&LibLoadedCallBack);
	BPatch_process* appProc = dynamic_cast<BPatch_process*>(addrs);
	// BPatch_binaryEdit* appBin = dynamic_cast<BPatch_binaryEdit*>(addrs);
	BPatch_image *image = addrs->getImage();
	BPatch_Vector<BPatch_module*> mods;
	image->getModules(mods);
	for (auto mod : mods){
		char * name = (char *) malloc(500 * sizeof(char));
		name = mod->getName(name, 500);
		std::string tmp = std::string(name);
		std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
		if (tmp.find(std::string("libcuda.so")) != std::string::npos) {
			// We have found libcuda, trigger instrimentation
			InsertBreakpoints(mod);
			loaded = true;
			break;
		}
	}
	if (!appProc->continueExecution()) {
	    fprintf(stderr, "continueExecution failed\n");
	}
	while (!appProc->isTerminated()) {
		bpatch.waitForStatusChange();
		std::cerr << "Status Changed...." << std::endl;
		appProc->continueExecution();
	}
	std::cerr << "loaded: " << loaded << std::endl;
}
