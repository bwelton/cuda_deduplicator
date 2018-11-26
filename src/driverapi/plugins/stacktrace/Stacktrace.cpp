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
#include "StackPoint.h"
#include "StackwalkingCommon.h"

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

thread_local uint64_t skippedStacks;
thread_local pid_t my_thread_id = -1;
thread_local std::shared_ptr<OutputFile> outputFile;
thread_local std::shared_ptr<StackKeyWriter> keyFile;


extern "C" {

	void SETUP_INTERCEPTOR() {
		if (outputFile.get() != NULL)
			return;

		skippedStacks = 0;
		if (my_thread_id == -1)
			my_thread_id = (pid_t) syscall(__NR_gettid);

		std::stringstream ss;
		ss << "DIOGENES_SyncCalls.bin";
		outputFile.reset(new OutputFile(ss.str()));
		assert(outputFile.get() != NULL);
		ss.str(std::string());
		ss << "DIOGENES_SyncCalls.key";
		keyFile.reset(new StackKeyWriter(fopen(ss.str().c_str(),"w")));
		assert(keyFile.get() != NULL);
	}



	__attribute__ ((noinline)) void RecordStack() {
//		fprintf(stderr,"We are recording a stack position....\n");
		SETUP_INTERCEPTOR();
		uint64_t pos = 0;
		std::vector<StackPoint> points;
		bool ret = GET_FP_STACKWALK(points);
		if(ret == false) {
			std::cout << "Could not walk stack, returning nothing" << std::endl;
			skippedStacks += 1; 
			std::cout << "Skipped Stacks: " << skippedStacks << std::endl;
			fwrite(&pos, 1, sizeof(uint64_t), outputFile->outFile);
		} else {
			pos = keyFile->InsertStack(points);
			fwrite(&pos, 1, sizeof(uint64_t), outputFile->outFile);			
		}

		
		// uint64_t pos = 0;
		// StackPoint sp;
		// std::string lib;
		// void * stab;
		// if(local_walker->walkStack(stackwalk) == false) {
		// 	std::cout << "Could not walk stack, returning nothing" << std::endl;
		// 	skippedStacks += 1; 
		// 	std::cout << "Skipped Stacks: " << skippedStacks << std::endl;
		// 	fwrite(&pos, 1, sizeof(uint64_t), outputFile->outFile);
		// 	return;
		// }
		// for (auto frame : stackwalk) {
		// 	StackPoint sp;
		// 	uint64_t offset;
		// 	frame.getLibOffset(lib, offset, stab);
		// 	sp.libname = lib;
		// 	sp.libOffset = offset;
		// 	points.push_back(sp);
		// }
		// pos = keyFile->InsertStack(points);
		// fwrite(&pos, 1, sizeof(uint64_t), outputFile->outFile);
	}


	__attribute__ ((noinline)) int SynchronizationWrapper(void * a, void * b, void * c);


	__attribute__ ((noinline)) int STACK_SyncWrapper(void * a, void * b, void * c) {
		RecordStack();
		return SynchronizationWrapper(a,b,c);
	}

	void SYNC_RECORD_SYNC_CALL() {
		std::vector<StackPoint> points;
		bool ret = GET_FP_STACKWALK(points);
		// for (auto i : points) {
		// 	std::cerr << i.libname <<  "," << i.libOffset << std::endl;
		// }
	}

}