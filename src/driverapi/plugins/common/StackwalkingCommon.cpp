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
#define UNW_LOCAL_ONLY  
#include <libunwind.h>
#define MAXIMUM_STACK 512
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

thread_local Walker *  local_walker = NULL;

extern "C" {
	void INIT_FP_STACKWALKER() {
		if (local_walker != NULL)
			return;
		local_walker = Walker::newWalker();
	}

	bool GET_FP_STACKWALK(std::vector<StackPoint> & ret) {
		INIT_FP_STACKWALKER();
		
		std::vector<Frame> stackwalk;
		if(local_walker->walkStack(stackwalk) == false) {
			return false;
		}
		for (auto frame : stackwalk) {
			StackPoint sp;
			uint64_t offset;
			frame.getLibOffset(lib, offset, stab);
			sp.libname = lib;
			sp.libOffset = offset;
			ret.push_back(sp);
		}
		return true;
	}
}