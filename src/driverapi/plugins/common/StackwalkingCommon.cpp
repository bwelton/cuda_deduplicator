#include <map>
#include <vector>
#include <iostream> 
#include <fstream>    
#include <string>		
#include <cassert> 
#include <unistd.h>
#include <sys/syscall.h>
#include <sstream>
#include <cstring>
#include <memory>
#include <execinfo.h>
#include <unordered_map>
#include <unistd.h>
#include <dlfcn.h>

#include "StackPoint.h"
#include "framestepper.h"
#include "walker.h"
#include "procstate.h"
#include "swk_errors.h"
#include "steppergroup.h"
#include "frame.h"
#include "sw_c.h"
#include "Symtab.h"
#include "BPatch.h"
#include "BPatch_process.h"

using namespace Dyninst;
using namespace Dyninst::Stackwalker;
using namespace SymtabAPI;

thread_local Walker *  local_walker = NULL;
// struct StackWalkerFastMap{
// 	uint64_t _total_count;
// 	std::map<uint64_t, StackWalkerFastMap *> _map;
// 	StackWalkerFastMap() : _total_count(0) {};
// 	void Init() {
// 		// RAStackReaderWriter rs(fopen("AC_BinStacks.bin", "rb"));
// 		// std::vector<std::vector<uint64_t>>  stacks = rs.ReadStacks();
// 		// for (auto i : stacks) {
// 		// 	Insert(i, 0);
// 		// }
// 		// _total_count = 0;
// 		//StackKeyReader r(fopen("AC_AutoCorrectStacks.txt", "rb"));
// 		//std::map<uint64_t, std::vector<StackPoint> > stacks = r.ReadStacks();

// 	};
// 	~StackWalkerFastMap() {
// 		//DIOGENES_SHUTDOWN_MODE = true;
// 		//if (_total_count != 0)
// 		//	std::cout << "NUMBER OF OPTI HITS = " << std::dec << _total_count << std::endl;
// 	};
// 	void Insert(std::vector<uint64_t> & input, int pos) {
// 		if(input.size() <= pos)
// 			return;
// 		uint64_t val = input[pos];
// 		if (_map.find(val) == _map.end()) {
// 			_map[val] = new StackWalkerFastMap();
// 		}
// 		_map[val]->Insert(input, pos+1);
// 	};

// 	bool Lookup(std::vector<uint64_t> & input, int pos) {
// 		if(input.size() <= pos)
// 			return true;
// 		uint64_t val = input[pos];
// 		if(_map.find(val) == _map.end())
// 			return false;
// 		return _map[val]->Lookup(input,pos+1);
// 	};

// 	bool IterativeLookup(uint64_t * input, int size, int pos) {
// 		std::map<uint64_t, StackWalkerFastMap *> * curMap = &_map;
// 		int insize = size;
// 		while (pos < insize) {
// 			auto it = curMap->find(input[pos]);
// 			if (it == curMap->end()) 
// 				return false;
// 			curMap = &(it->second->_map);
// 			pos++;
// 		}
// 		_total_count++;
// 		return true;
// 	};
// };



//thread_local StackWalkerFastMap fm;
extern "C" {
	void INIT_FP_STACKWALKER() {
		if (local_walker != NULL)
			return;
		local_walker = Walker::newWalker();
	}


	bool GET_FP_STACKWALK_NONSW(std::vector<StackPoint> & ret) {
		void * local_stack[100];
		int tmpretm = backtrace(local_stack, 100);
		for (int i = 0; i < tmpretm; i++) {
			StackPoint sp;
			sp.libname = std::string("ABSOLUTE_ADDR_REQ_MUTATOR");
			sp.libOffset = ((uint64_t*)local_stack)[i];
			sp.raFramePos = sp.libOffset;
			ret.push_back(sp);
		}
		return true;
	}


	bool GET_FP_STACKWALK(std::vector<StackPoint> & ret) {

		// void * local_stack[100];
		// int tmpretm = backtrace(local_stack, 100);
		INIT_FP_STACKWALKER();

		std::vector<Frame> stackwalk;
		if(local_walker->walkStack(stackwalk) == false) {
			return false;
		}
		std::string lib;
		void * stab;
		for (auto frame : stackwalk) {
			StackPoint sp;
			uint64_t offset;
			//std::cerr << "RA/FP/SP: " << std::hex << frame.getRA() << ","  << frame.getFP() << "," << frame.getSP() << std::endl;
			frame.getLibOffset(lib, offset, stab);
			sp.libname = lib;
			sp.libOffset = offset;
			sp.raFramePos = (uint64_t)frame.getRA();
			ret.push_back(sp);
		}
		return true;
	}
}