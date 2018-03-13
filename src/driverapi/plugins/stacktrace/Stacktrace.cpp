#include <map>
#include <vector>
#include <iostream> 
#include <fstream>    
#include <string>		
#include <cassert> 

#define MAXIMUM_STACK 512

// Stash Space for writing data to file
thread_local char * stashSpace = NULL;
thread_local size_t charSize = 0;

// Reentrant protection 
thread_local bool in_inst = false;

// Storing the current stack
thread_local std::vector<std::pair<uint64_t id, uint64_t callAddr> > calls;
thread_local pid_t my_thread_id = -1;
thread_local FILE * outputFile = NULL;
extern "C" {
	void SETUP_INTERCEPTOR() {
		if (outputFile != NULL)
			return;

		if (my_thread_id == -1)
			my_thread_id = (pid_t) syscall(__NR_gettid);

		std::stringstream ss;
		ss << "stackOut." << my_thread_id << ".bin";
		outputFile = fopen(ss.str().c_str(), "w");
		assert(outputFile != NULL);
		stashSpace = (char *) malloc(MAXIMUM_STACK * sizeof(uint64_t) * 2 + sizeof(size_t));
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
		calls.pop_back();
		in_inst = false;
	}

	void SYNC_RECORD_SYNC_CALL() {
		in_inst = true;
		int pos = 0;
		assert(calls.size() < MAXIMUM_STACK);
		std::memcpy(stashSpace, (void*) &(calls.size()), sizeof(size_t));
		pos += sizeof(size_t);
		for (auto i : calls) {
			std::memcpy(&(stashSpace[pos]), (void*) &(i.first), sizeof(uint64_t));
			pos += sizeof(uint64_t);
			std::memcpy(&(stashSpace[pos]), (void*) &(i.second), sizeof(uint64_t));
			pos += sizeof(uint64_t);
		}
		write(outputFile, stashSpace, pos);
		in_inst = false;
	}

	void CAPTURE_EXIT(){
		in_inst = true;
		fflush(outputFile);
		fclose(outputFile);
	}
}