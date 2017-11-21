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

using namespace std;
using namespace Dyninst;
using namespace ParseAPI;
using namespace PatchAPI;
using namespace SymtabAPI;

std::pair<uint64_t, uint64_t> ReadLine(std::string line) {
	uint64_t id, ptr;
	std::string token_1 = line.substr(0, line.find(std::string(",")));
	std::string token_2 = line.substr(line.find(std::string(","))+1, line.size());
	std::stringstream ss; 
	ss << token_1;
	ss >> std::dec >> id;
	ss.clear();
	ss << token_2;
	ss >> std::hex >> ptr;
	ss.clear();
	std::cout << "Got: " << id << "," << std::hex << ptr << std::dec << std::endl;
	return std::make_pair(id,ptr);
}

int main(int argc, char * argv[]){
	BPatch bpatch;
	int pid = atoi(argv[1]);
	BPatch_addressSpace * handle = NULL;
	handle = bpatch.processAttach(NULL, pid);

	if (handle == NULL) {
		std::cerr << "could not attach to process, exiting now" << std::endl;
		exit(-1);
	}

	// Read the function pointers
	std::vector<std::pair<uint64_t, uint64_t> > IdsAndPtrs;
	std::ifstream t;
	t.open("function_pts.txt",std::ifstream::in);
	std::string line;
	while (std::getline(t, line)) {	
		IdsAndPtrs.push_back(ReadLine(line));
	}
	std::cout << "We have " << IdsAndPtrs.size() << " functions to find " << std::endl;
	std::vector<BPatch_module *> * modules;
	BPatch_image * image = handle->getImage();
	modules = image->getModules();
	char * nameTmp = (char*)malloc(300*sizeof(char));
	for(auto i : *modules) {
		
		nameTmp = i->getFullName(nameTmp, 299);
		std::string libName = std::string(nameTmp);
		if (libName.find(std::string("libcuda")) != std::string::npos) {
			std::cout << "We have found libcuda" << std::endl;
			std::cout << "Function Hunting Begins.... " << std::endl;
			for (auto q : IdsAndPtrs) {
				BPatch_Vector<BPatch_function *> * functors;
				BPatch_Vector<BPatch_function *> f1;
				functors= i->findFunctionByAddress((void*)q.second, f1);
				if (functors.size() == 0) 
					std::cout << "COULD NOT FIND FUNCTION " << q.second << "," << q.first << std::endl;
				else
					std::cout << "FOUND FUNCTION " << q.second << "," << q.first << std::endl;
			}
			exit(0);
		}
		std::cout << "Module loaded: " << nameTmp << std::endl;
	}
}
