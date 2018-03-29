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
using namespace Dyninst;
using namespace Dyninst::Stackwalker;
using namespace SymtabAPI;


// Stash Space for writing data to file
thread_local char * stashSpace = NULL;
thread_local size_t charSize = 0;
thread_local Walker *  local_walker;
// Reentrant protection 
thread_local bool in_inst = false;
thread_local uint64_t skippedStacks;

// Storing the current stack
thread_local std::vector<std::pair<uint64_t, uint64_t> > calls;
thread_local std::vector<uint64_t> entries; 
thread_local pid_t my_thread_id = -1;
// Make this really large, in case we need lots of space for the stack.
thread_local char stackStore[512000];

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
thread_local std::shared_ptr<StackKeyWriter> keyFile;


extern "C" {

	void SETUP_INTERCEPTOR() {
		if (outputFile.get() != NULL)
			return;

		skippedStacks = 0;
		local_walker = Walker::newWalker();
		if (my_thread_id == -1)
			my_thread_id = (pid_t) syscall(__NR_gettid);

		std::stringstream ss;
		ss << "stackOut." << my_thread_id << ".bin";
		outputFile.reset(new OutputFile(ss.str()));
		assert(outputFile.get() != NULL);
		ss.str(std::string());
		ss << "stackOut." << my_thread_id << ".key";
		keyFile.reset(new StackKeyWriter(fopen(ss.str().c_str(),"w")));
		assert(keyFile.get() != NULL);
	}



	__attribute__ ((noinline)) void RecordStack() {
		SETUP_INTERCEPTOR();
		std::vector<Frame> stackwalk;
		std::vector<StackPoint> points;
		uint64_t pos = 0;
		StackPoint sp;
		std::string lib;
		void * stab;
		if(local_walker->walkStack(stackwalk) == false) {
			std::cout << "Could not walk stack, returning nothing" << std::endl;
			skippedStacks += 1; 
			fwrite(&pos, 1, sizeof(uint64_t), outputFile->outFile);
			return;
		}
		for (auto frame : stackwalk) {
			StackPoint sp;
			uint64_t offset;
			frame.getLibOffset(lib, offset, stab);
			sp.libname = lib;
			sp.libOffset = offset;
			points.push_back(sp);
		}
		pos = keyFile->InsertStack(points);
		fwrite(&pos, 1, sizeof(uint64_t), outputFile->outFile);
		// uint64_t offset = stackwalk.size();
		// std::memcpy(stackStore, &offset, sizeof(uint64_t));
		// pos += sizeof(uint64_t);
		// for (auto frame : stackwalk) {
		// 	frame.getLibOffset(lib, offset, stab);
		// 	sp.libname = lib;
		// 	sp.libOffset = offset;
		// 	if (pos < 512000) {
		// 		int ret = sp.Serialize(&(stackStore[pos]), 512000 - pos);
		// 		if (ret == -1)
		// 			assert(ret != -1);
		// 		pos += ret;
		// 	}
		// }
		// fwrite(&pos, 1, sizeof(int), outputFile->outFile);
		// fwrite(stackStore, 1, pos, outputFile->outFile);
	}


	__attribute__ ((noinline)) int SynchronizationWrapper(void * a, void * b, void * c) {
		return 0;
	} 


	__attribute__ ((noinline)) int STACK_SyncWrapper(void * a, void * b, void * c) {
		RecordStack();
		return SynchronizationWrapper(a,b,c);
	}




	// void STACKTRACE_RECORD_MAIN_ENTRY(uint64_t id) {
	// 	if(in_inst)
	// 		return;
	// 	in_inst = true;
	// 	SETUP_INTERCEPTOR();
	// 	entries.push_back(id);
	// 	in_inst = false;
	// }
	// void STACKTRACE_RECORD_MAIN_EXIT(uint64_t id) {
	// 	if (in_inst)
	// 		return;
	// 	in_inst = true;
	// 	SETUP_INTERCEPTOR();
	// 	if (entries.back() != id) {
	// 		std::cerr << "ERROR! Record Exit does not equal the entrance at the start of the stack!" << std::endl;
	// 		std::cerr << id << std::endl;
	// 	}
	// 	else
	// 		entries.pop_back();
	// 	in_inst = false;
	// }

	// void STACKTRACE_RECORD_ENTRY(uint64_t id, uint64_t callAddr) {
	// 	if (in_inst)
	// 		return;
	// 	in_inst = true;
	// 	SETUP_INTERCEPTOR();
	// 	calls.push_back(std::make_pair(id, callAddr));
	// 	in_inst = false;
	// }

	// void STACKTRACE_RECORD_EXIT(uint64_t id, uint64_t callAddr) {
	// 	if (in_inst)
	// 		return;
	// 	in_inst = true;
	// 	SETUP_INTERCEPTOR();
	// 	// Error out if for some reason the vector is empty.
	// 	if (calls.size() == 0)
	// 		assert(calls.size() > 0);

	// 	// If there is a non matching id at the back, error out.
	// 	if(calls.back().first != id) {
	// 		std::cerr << "ERROR! Exit does not equal the entrance at the start of the stack!" << std::endl;
	// 		std::cerr << id << "," << callAddr << " not maching " << calls.back().first << "," << calls.back().second << std::endl;
	// 	}
	// 	else 
	// 		calls.pop_back();
	// 	in_inst = false;
	// }

	void SYNC_RECORD_SYNC_CALL() {
		// Original Call 
		// Entry FP (deduced from RSP): 0x7fffffffb880 (+8)
		// Entry RSP: 0x7fffffffb888
		// Entry RBP: 0x731c88 (makes no sense, likely some value stored here).
		//
		// Instrimentation Call:
		// Entry RBP: 0x7fffffffb798 -> old RBP
		// Entry RSP: 0x7fffffffb580 -> Some saved value, dont use. 
		// 
		// Regenerating RSP and RBP:
		// Original RBP: *CurRBP
		// Original RSP: CurRBP-0xF0
		// Original RA: if(abs(OrigRBP - OrigRSP) > 5128), default to RSP, 
		// 				else default to RBP - 8.
		// 
		// RSP at entry: 0x7fffffffb888
		//  0x7fffffffb580 + 0xa8 + 0x218
		//  0x7fffffffb798
		//  Distance from RBP 0xF0
		//  
		//  0x00007ffff628041f
		//  SP: lastSP - 0xF0
		//  FP: SP
		//  RA: *SP
		// uint64_t lastSP;

		// asm volatile("mov %%RBP, %0" : "=r" (lastSP));
		// std::cerr << "RBP Value: " << std::hex << lastSP << std::dec << std::endl;
		// std::cerr << "Previous RBP Value: " << std::hex << ((uint64_t*)lastSP)[0] << std::dec << std::endl;
		// std::cerr << "Previous RSP Value: " << std::hex << lastSP + 0xF0 << std::dec << std::endl;
		// uint64_t originalRA = 0x0;
		// uint64_t originalRBP = ((uint64_t*)lastSP)[0];
		// uint64_t originalRSP = lastSP + 0xF0;
		// if (originalRSP - originalRBP > 5128) {
		// 	originalRA = ((uint64_t*)originalRSP)[0];
		// 	originalRBP = (originalRSP-0x8);
		// } else {
		// 	originalRA = ((uint64_t*)originalRBP-0x8)[0];
		// }
		// std::cerr << "Previous RA Value: " <<  std::hex << originalRA << std::dec << std::endl;
		// std::cerr << "Previous RBP Value: " << std::hex << originalRBP << std::dec << std::endl;
		// if (originalRA == 0 || originalRBP == 0 || originalRSP == 0){
		// 	std::cerr << "could not generate stack, skipping" << std::endl;
		// 	return;
		// }
		
		SETUP_INTERCEPTOR();

		// asm volatile("mov %0, %%RBP" : "=r" (originalRBP));

		// int bt_size = backtrace(backtraceStore, 1024);

		// // asm volatile("mov %0, %%RBP" : "=r" (lastSP));
		// // assert(bt_size > 0);
		// for (int i = 0; i < bt_size; i++)
		// 	std::cerr << std::hex << backtraceStore[i] << std::dec << std::endl;



		// if( ((uint64_t*)lastSP)[0] > 5128)
		// 	if (((uint64_t*)lastSP)[0] > lastSP - 0xF0)
		// 		if (((uint64_t*)lastSP)[0] - (lastSP - 0xF0) > 5128)
		// 			originalRA = ((uint64_t*)(lastSP - 0xF0))[0];
		// 		else
		// 			originalRA = ((uint64_t*)lastSP - 0x8)[0];
		// 	else
		// 		originalRA = ((uint64_t*)lastSP - 0x8)[0];
		// else 
		// 	assert(1 == 0);

		//if (((uint64_t*)lastSP)[0]  lastSP - 0xF0 )	


		// volatile uint64_t * addrOff = ((uint64_t*)lastSP);
		// volatile uint64_t possiblePreviousFrame = addrOff[0];
		// volatile uint64_t retAddr = ((uint64_t*)lastSP + 0xF0)[0];
		// lastSP = lastSP + 0xF0;
		
		// std::cerr << "Possible Previous Frame: " << std::hex << possiblePreviousFrame << std::dec << std::endl;
		// std::cerr << "Last SP: " << std::hex << lastSP << std::dec << std::endl;
		// std::cerr << "Stack/FP: " << std::hex << lastSP << std::dec << "," <<  std::hex << lastSP - 0x8 << std::dec << std::endl;
		// std::cerr << "Return Address: " << std::hex << retAddr << std::dec << std::endl;
		// in_inst = true;
		// SETUP_INTERCEPTOR();
		// std::cerr << "Sync Called" << std::endl;

		int pos = 0;

		// assert(local_walker != NULL);
		std::vector<Frame> stackwalk;
		// addrOff[0] = lastSP - 0x8;

		// addrOff[0] = possiblePreviousFrame;
		// 0x00007ffff5483eba
		// Frame myFrame;
		// Frame * fr = Dyninst::Stackwalker::Frame::newFrame(originalRA, originalRSP, originalRBP, local_walker);
		// std::cerr << std::hex << fr->getRA() << std::dec << " " << std::hex << fr->getSP() << std::dec << " " << std::hex << fr->getFP() << std::dec << " " << std::endl;
		// myFrame = *fr;
		// std::cerr << std::hex << myFrame.getRA() << std::dec << " " << std::hex << myFrame.getSP() << std::dec << " " << std::hex << myFrame.getFP() << std::dec << " " << std::endl;
		
		// //local_walker->getInitialFrame(myFrame);
		// for(int i = 0; i < 5; i++) {
		// 	Frame out;
		// 	if (local_walker->walkSingleFrame(myFrame, out) == false)
		// 		break;
		// 	std::string tmp;
		// 	out.getName(tmp);
		// 	std::cerr << tmp << " " << std::hex << out.getRA() << std::dec << " " << std::hex << out.getSP() << std::dec << " " << std::hex << out.getFP() << std::dec << " " << std::endl;
		// 	myFrame = out;
		// }
		// std::cerr << "Done walking the stack" << std::endl;
		// // //0x7ffff6280388

// RA: 0x00007ffff5483eba
		local_walker->walkStack(stackwalk);
		std::cerr << "We got " << stackwalk.size() << " frames" << std::endl;
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
		// assert(entries.size() < MAXIMUM_STACK);
		// size_t callCount = entries.size();
		// std::memcpy(stashSpace, (void*) &(callCount), sizeof(size_t));
		// pos += sizeof(size_t);
		// for (auto i : entries) {
		// 	std::memcpy(&(stashSpace[pos]), (void*) &(i), sizeof(uint64_t));
		// 	pos += sizeof(uint64_t);
		// 	// std::memcpy(&(stashSpace[pos]), (void*) &(i.second), sizeof(uint64_t));
		// 	// pos += sizeof(uint64_t);
		// }
		// fwrite(stashSpace, 1, pos, outputFile->outFile);
		// in_inst = false;
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