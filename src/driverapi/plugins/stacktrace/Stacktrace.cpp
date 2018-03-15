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


// Stash Space for writing data to file
thread_local char * stashSpace = NULL;
thread_local size_t charSize = 0;
thread_local Walker *  local_walker;
// Reentrant protection 
thread_local bool in_inst = false;

// Storing the current stack
thread_local std::vector<std::pair<uint64_t, uint64_t> > calls;
thread_local std::vector<uint64_t> entries; 
thread_local pid_t my_thread_id = -1;

thread_local void * backtraceStore[1024];

void * return_frame_ptr(int i) {
	switch (i) {
		case 0:
			return __builtin_frame_address(0);
		case 1:
			return __builtin_frame_address(1);
		case 2:
			return __builtin_frame_address(2);
		case 3:
			return __builtin_frame_address(3);
		case 4:
			return __builtin_frame_address(4);
		case 5:
			return __builtin_frame_address(5);
		case 6:
			return __builtin_frame_address(6);
		case 7:
			return __builtin_frame_address(7);
		case 8:
			return __builtin_frame_address(8);
		case 9:
			return __builtin_frame_address(9);
		case 10:
			return __builtin_frame_address(10);
		case 11:
			return __builtin_frame_address(11);
		case 12:
			return __builtin_frame_address(12);
		default:
			return NULL;
	}
}



struct OutputFile {
	FILE * outFile;
	OutputFile(std::string filename) {
		outFile = fopen(filename.c_str(),"w");
	}

	~OutputFile() {
		fflush(outFile);
		fclose(outFile);
	}
};

thread_local std::shared_ptr<OutputFile> outputFile;

extern "C" {
	void SETUP_INTERCEPTOR() {
		if (outputFile.get() != NULL)
			return;


		local_walker = Walker::newWalker();
		if (my_thread_id == -1)
			my_thread_id = (pid_t) syscall(__NR_gettid);

		std::stringstream ss;
		ss << "stackOut." << my_thread_id << ".bin";
		outputFile.reset(new OutputFile(ss.str()));
		assert(outputFile.get() != NULL);
		stashSpace = (char *) malloc(MAXIMUM_STACK * sizeof(uint64_t) + sizeof(size_t));
	}

	void STACKTRACE_RECORD_MAIN_ENTRY(uint64_t id) {
		if(in_inst)
			return;
		in_inst = true;
		SETUP_INTERCEPTOR();
		entries.push_back(id);
		in_inst = false;
	}
	void STACKTRACE_RECORD_MAIN_EXIT(uint64_t id) {
		if (in_inst)
			return;
		in_inst = true;
		SETUP_INTERCEPTOR();
		if (entries.back() != id) {
			std::cerr << "ERROR! Record Exit does not equal the entrance at the start of the stack!" << std::endl;
			std::cerr << id << std::endl;
		}
		else
			entries.pop_back();
		in_inst = false;
	}

	void STACKTRACE_RECORD_ENTRY(uint64_t id, uint64_t callAddr) {
		if (in_inst)
			return;
		in_inst = true;
		SETUP_INTERCEPTOR();
		calls.push_back(std::make_pair(id, callAddr));
		in_inst = false;
	}

	void STACKTRACE_RECORD_EXIT(uint64_t id, uint64_t callAddr) {
		if (in_inst)
			return;
		in_inst = true;
		SETUP_INTERCEPTOR();
		// Error out if for some reason the vector is empty.
		if (calls.size() == 0)
			assert(calls.size() > 0);

		// If there is a non matching id at the back, error out.
		if(calls.back().first != id) {
			std::cerr << "ERROR! Exit does not equal the entrance at the start of the stack!" << std::endl;
			std::cerr << id << "," << callAddr << " not maching " << calls.back().first << "," << calls.back().second << std::endl;
		}
		else 
			calls.pop_back();
		in_inst = false;
	}

	void SYNC_RECORD_SYNC_CALL() {
		// RSP at entry: 0x7fffffffb888
		//  0x7fffffffb580 + 0xa8 + 0x218
		//  0x7fffffffb798
		//  Distance from RBP 0xF0
		//  
		//  0x00007ffff628041f
		//  SP: lastSP - 0xF0
		//  FP: SP
		//  RA: *SP
		uint64_t lastSP;

		asm volatile("mov %%RBP, %0" : "=r" (lastSP));
		std::cerr << "Last SP: " << lastSP << std::endl;
		lastSP = lastSP - 0xF0;
		std::cerr << "Stack/FP: " << std::hex << lastSP << std::dec << std::endl;
		std::cerr << "Return Address: " std::hex << ((uint64_t*)lastSP)[0] << std::dec << std::endl;
		in_inst = true;
		SETUP_INTERCEPTOR();
		std::cerr << "Sync Called" << std::endl;

		int pos = 0;

		// assert(local_walker != NULL);
		// std::vector<Frame> stackwalk;
		// int bt_size = backtrace(backtraceStore, 1024);
		// assert(bt_size > 0);
		// for (int i = 0; i < bt_size; i++)
		// 	std::cerr << std::hex << backtraceStore[i] << std::dec << std::endl;

		Frame myFrame;
		local_walker->getInitialFrame(myFrame);
		for(int i = 0; i < 10; i++) {
			Frame out;
			std::cerr << std::hex << myFrame.getRA() << std::dec << " " << std::hex << myFrame.getSP() << std::dec << " " << std::hex << myFrame.getFP() << std::dec << " " << std::endl;
			local_walker->walkSingleFrame(myFrame, out);
			myFrame = out;
		}
		//0x7ffff6280388


		// //local_walker->walkStack(stackwalk);
		// std::cerr << "We got " << stackwalk.size() << " frames" << std::endl;
		// Initialize cursor to current frame for local unwinding.
		// unw_getcontext(&context);
		// unw_init_local(&cursor, &context);
		// while (unw_step(&cursor)) {
		// 	unw_word_t offset, pc;
		// 	unw_get_reg(&cursor, UNW_X86_EBP, &pc);
		// 	void * pts
		//    if (pc == 0) {
		//       break;
		//    }
		//    fprintf(stderr, "0x%lx\n", pc);
		// }


		// for (int i = 0; i < 12; i++) {
		// 	std::cerr << std::hex << return_frame_ptr(i) << std::dec << std::endl;
		// 	if (return_frame_ptr(i) == NULL)
		// 		break;
		// }
		assert(entries.size() < MAXIMUM_STACK);
		size_t callCount = entries.size();
		std::memcpy(stashSpace, (void*) &(callCount), sizeof(size_t));
		pos += sizeof(size_t);
		for (auto i : entries) {
			std::memcpy(&(stashSpace[pos]), (void*) &(i), sizeof(uint64_t));
			pos += sizeof(uint64_t);
			// std::memcpy(&(stashSpace[pos]), (void*) &(i.second), sizeof(uint64_t));
			// pos += sizeof(uint64_t);
		}
		fwrite(stashSpace, 1, pos, outputFile->outFile);
		in_inst = false;
	}

	// std::stringstream ret; 	
	// std::vector<Frame> stackwalk;
	// std::string s;
	// void * sym; 
	// Walker * walker = Walker::newWalker();
	// walker->walkStack(stackwalk);
	// Dyninst::Offset offset;
	// for (int i = 0; i < stackwalk.size(); i++) {
	// 	stackwalk[i].getName(s);
	// 	ret << s << " - ";
	// 	if(stackwalk[i].getLibOffset(s, offset, sym) == false){
	// 	 	continue;
	// 	}
	// 	Symtab * curSym = static_cast<Symtab *>(sym);
	// 	if (sym == NULL) {
	// 		ret << "\n";
	// 		continue;
	// 	}
	// 	std::vector<Statement *> lines;
	// 	if((curSym)->getSourceLines(lines,offset) == false) {
	// 		ret << "\n";
	// 		continue;
	// 	}
	// 	for (int q = 0; q < lines.size(); q++) {
	// 		ret << lines[q]->getFile() << ":" << std::to_string(lines[q]->getLine()) << " ";
	// 	}
	// 	ret << "\n";
	// }
	// ret << "\n";
	// return ret.str();
}