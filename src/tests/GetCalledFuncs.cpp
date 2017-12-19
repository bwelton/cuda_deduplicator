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
#include <mutex>

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
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <deque>

using namespace Dyninst;
using namespace ParseAPI;
using namespace PatchAPI;
using namespace SymtabAPI;


std::vector<std::string> funcNames;
std::map<uint64_t, std::string> namePoints; 
std::map<std::string, uint64_t> stackCounts;
std::set<std::string> _interestingStacks;

BPatch_addressSpace * addrs;
BPatch bpatch;

std::vector<BPatch_function *> findFuncByName(BPatch_image * appImage, const char * funcName)
{
  /* fundFunctions returns a list of all functions with the name 'funcName' in the binary */
  BPatch_Vector<BPatch_function * >funcs;
  if (NULL == appImage->findFunction(funcName, funcs) || !funcs.size() || NULL == funcs[0])
  {
      std::cerr << "Failed to find " << funcName <<" function in the instrumentation library" << std::endl;
      return std::vector<BPatch_function *>();
  }
  std::cerr << "Found " << funcName << " this many times " << funcs.size() << std::endl;
  if (funcs.size() > 1) {
    for(int i = 0; i < funcs.size(); i++ )
    {
        std::cerr << "    " << funcs[i]->getName() << std::endl;
    }
  }
  return funcs;
}

int main() {
	std::vector<char *> synchMemoryCopies = {"cuMemcpyDtoH_v2","cuMemcpyHtoD_v2", "cuMemcpyHtoA_v2","cuMemcpyPeer", "cuMemAlloc_v2","cuMemFree_v2"};
	std::vector<char *> asyncMemoryCopies = {"cuMemcpyHtoDAsync_v2","cuMemcpyDtoHAsync_v2","cuMemcpyHtoAAsync_v2"};
	std::vector<char *> knownSynch = {"cuMemAlloc_v2","cuMemFree_v2"};
	BPatch_binaryEdit * app = bpatch.openBinary("/usr/lib/x86_64-linux-gnu/libcuda.so", true);
	BPatch_image * appImage = app->getImage();
	std::vector<std::set<std::string>> _calledSyncFunctions;
	for (auto i : synchMemoryCopies) {
		std::set<std::string> exploredFunctions;

		std::vector<BPatch_function *> funcs = findFuncByName(appImage, i);
		std::deque<BPatch_function *> unexplored;
		unexplored.insert(unexplored.end(), funcs.begin(), funcs.end());
		while(!unexplored.empty()) {
			BPatch_function * thisFunc = unexplored.front();
			unexplored.pop_front();
			if (exploredFunctions.find(thisFunc->getName()) != exploredFunctions.end())
				continue;

			// We have a new function to explore...
			exploredFunctions.insert(thisFunc->getName());

			std::vector<BPatch_point *> calledFunctions;
			thisFunc->getCallPoints(calledFunctions);
			for (auto z : calledFunctions) {
				BPatch_function * cFunc = z->getCalledFunction();
				if (cFunc == NULL)
					continue;
				std::cout << thisFunc->getName() << " is calling " << cFunc->getName() << std::endl;
				if (exploredFunctions.find(cFunc->getName()) != exploredFunctions.end())
					continue;				
				unexplored.push_back(cFunc);
			}
		}
		_calledSyncFunctions.push_back(exploredFunctions);
	}	
	std::set<std::string> intersection = _calledSyncFunctions[0];
	for (auto z : _calledSyncFunctions){
		std::set<std::string> tmp = intersection;
		intersection.clear();
		std::set_intersection(tmp.begin(), tmp.end(), z.begin(), z.end(),  std::inserter(intersection,intersection.begin()));

	}
	// _calledSyncFunctions.clear();
	// for (auto i : synchMemoryCopies) {
	// 	std::set<std::string> exploredFunctions;

	// 	std::vector<BPatch_function *> funcs = findFuncByName(appImage, i);
	// 	std::deque<BPatch_function *> unexplored;
	// 	unexplored.insert(unexplored.end(), funcs.begin(), funcs.end());
	// 	while(!unexplored.empty()) {
	// 		BPatch_function * thisFunc = unexplored.front();
	// 		unexplored.pop_front();
	// 		if (exploredFunctions.find(thisFunc->getName()) != exploredFunctions.end())
	// 			continue;

	// 		// We have a new function to explore...
	// 		exploredFunctions.insert(thisFunc->getName());

	// 		std::vector<BPatch_point *> calledFunctions;
	// 		thisFunc->getCallPoints(calledFunctions);
	// 		for (auto z : calledFunctions) {
	// 			BPatch_function * cFunc = z->getCalledFunction();
	// 			if (cFunc == NULL)
	// 				continue;
	// 			std::cout << thisFunc->getName() << " is calling " << cFunc->getName() << std::endl;
	// 			if (exploredFunctions.find(cFunc->getName()) != exploredFunctions.end())
	// 				continue;				
	// 			unexplored.push_back(cFunc);
	// 		}
	// 	}
	// 	_calledSyncFunctions.push_back(exploredFunctions);
	// }	
	// for (auto z : _calledSyncFunctions){
	// 	std::set<std::string> tmp = intersection;
	// 	intersection.clear();
	// 	std::set_intersection(tmp.begin(), tmp.end(), z.begin(), z.end(),  std::inserter(intersection,intersection.begin()));

	// }
	_calledSyncFunctions.clear();
	for (auto i : asyncMemoryCopies) {
		std::set<std::string> exploredFunctions;

		std::vector<BPatch_function *> funcs = findFuncByName(appImage, i);
		std::deque<BPatch_function *> unexplored;
		unexplored.insert(unexplored.end(), funcs.begin(), funcs.end());
		while(!unexplored.empty()) {
			BPatch_function * thisFunc = unexplored.front();
			unexplored.pop_front();
			if (exploredFunctions.find(thisFunc->getName()) != exploredFunctions.end())
				continue;

			// We have a new function to explore...
			exploredFunctions.insert(thisFunc->getName());

			std::vector<BPatch_point *> calledFunctions;
			thisFunc->getCallPoints(calledFunctions);
			for (auto z : calledFunctions) {
				BPatch_function * cFunc = z->getCalledFunction();
				if (cFunc == NULL)
					continue;
				std::cout << thisFunc->getName() << " is calling " << cFunc->getName() << std::endl;
				if (exploredFunctions.find(cFunc->getName()) != exploredFunctions.end())
					continue;				
				unexplored.push_back(cFunc);
			}
		}
		_calledSyncFunctions.push_back(exploredFunctions);
	}	
	for (auto z : _calledSyncFunctions){
		std::set<std::string> tmp = intersection;
		intersection.clear();
		std::set_intersection(tmp.begin(), tmp.end(), z.begin(), z.end(),  std::inserter(intersection,intersection.begin()));

	}	
	std::cout << "Intersection of callsets" << std::endl;
	for (auto z : intersection)
		std::cout << z << std::endl;
}