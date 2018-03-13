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
#define MAXIMUM_STACK 512

// Stash Space for writing data to file
thread_local char * stashSpace = NULL;
thread_local size_t charSize = 0;

// Reentrant protection 
thread_local bool in_inst = false;

// Storing the current stack
thread_local std::vector<std::pair<uint64_t, uint64_t> > calls;
thread_local std::vector<uint64_t> entries; 
thread_local pid_t my_thread_id = -1;

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

		if (my_thread_id == -1)
			my_thread_id = (pid_t) syscall(__NR_gettid);

		std::stringstream ss;
		ss << "stackOut." << my_thread_id << ".bin";
		outputFile.reset(new OutputFile(ss.str()));
		assert(outputFile.get() != NULL);
		stashSpace = (char *) malloc(MAXIMUM_STACK * sizeof(uint64_t) * 2 + sizeof(size_t));
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
		if (entries.size() > 0)
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
		in_inst = true;
		SETUP_INTERCEPTOR();

		// Compare the entries at call points to function entries. 
		if (entries.size() !=  calls.size()) {
			if (calls.size() < entries.size()) {
				std::vector<std::pair<uint64_t, uint64_t> > tmp = calls; 
				calls.clear();
				// insert missing calls into the call vector
				size_t callPos = 0;
				for(int i = 0; i < entries.size(); i++) {
					if(entries[i] == tmp[callPos].first) {
						calls.push_back(tmp[callPos]);
						callPos += 1;
					} else {
						calls.push_back(std::make_pair(entries[i],0));
					}
				}
				assert(callPos == tmp.size());
			} else {
				assert(entries.size() < calls.size());
			}
		}

		int pos = 0;
		assert(calls.size() < MAXIMUM_STACK);
		size_t callCount = calls.size();
		std::memcpy(stashSpace, (void*) &(callCount), sizeof(size_t));
		pos += sizeof(size_t);
		for (auto i : calls) {
			std::memcpy(&(stashSpace[pos]), (void*) &(i.first), sizeof(uint64_t));
			pos += sizeof(uint64_t);
			std::memcpy(&(stashSpace[pos]), (void*) &(i.second), sizeof(uint64_t));
			pos += sizeof(uint64_t);
		}
		fwrite(stashSpace, 1, pos, outputFile->outFile);
		in_inst = false;
	}
}