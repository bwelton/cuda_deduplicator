#pragma once
#include <string.h>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <utility> 
#include <stdarg.h>
#include <iomanip>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

struct CUMallocTracker {

	uint8_t type;
	int64_t allocSite;
	int64_t freeSite;
	int64_t count;	
	CUMallocTracker () {
		type = 43;
	};
	inline size_t GetSize() {
		return sizeof(uint8_t)+sizeof(int64_t)+sizeof(int64_t)+sizeof(int64_t);
	};
	static CUMallocTracker * Deserialize(char * in) {
		if (in[0] != 43)
			return NULL;
		CUMallocTracker * ret = new CUMallocTracker();
		int64_t * ptr = (int64_t*)&(in[1]);
		ret->allocSite = ptr[0];
		ret->freeSite = ptr[1];
		ret->count = ptr[2];
		return ret;
	};
	inline void Serialize(char * out) {
		out[0] = type;
		int64_t * ptr = (int64_t*)&(out[1]);
		ptr[0] = allocSite;
		ptr[1] = freeSite;
		ptr[2] = count;
	};

};

struct GLIBMallocTracker {

	uint8_t type;
	int64_t allocSite;
	int64_t freeSite;
	int64_t count;	
	CUMallocTracker () {
		type = 48;
	};
	inline size_t GetSize() {
		return sizeof(uint8_t)+sizeof(int64_t)+sizeof(int64_t)+sizeof(int64_t);
	};
	static CUMallocTracker * Deserialize(char * in) {
		if (in[0] != 48)
			return NULL;
		CUMallocTracker * ret = new CUMallocTracker();
		int64_t * ptr = (int64_t*)&(in[1]);
		ret->allocSite = ptr[0];
		ret->freeSite = ptr[1];
		ret->count = ptr[2];
		return ret;
	};
	inline void Serialize(char * out) {
		out[0] = type;
		int64_t * ptr = (int64_t*)&(out[1]);
		ptr[0] = allocSite;
		ptr[1] = freeSite;
		ptr[2] = count;
	};

};

struct CUMemTransferTracker {
	uint8_t type;
	int64_t allocSite;
	int64_t copyID;
	int64_t count;	
	CUMemTransferTracker () {
		type = 79;
	};
	inline size_t GetSize() {
		return sizeof(uint8_t)+sizeof(int64_t)+sizeof(int64_t)+sizeof(int64_t);
	};
	inline void Serialize(char * out) {
		out[0] = type;
		int64_t * ptr = (int64_t*)&(out[1]);
		ptr[0] = allocSite;
		ptr[2] = copyID;
		ptr[3] = count;
	};
	static CUMemTransferTracker * Deserialize(char * in) {
		if (in[0] != 79)
			return NULL;
		CUMemTransferTracker * ret = new CUMemTransferTracker();
		int64_t * ptr = (int64_t*)&(in[1]);
		ret->allocSite = ptr[0];
		ret->copyID = ptr[2];
		ret->count = ptr[3];
		return ret;
	};

};

// CudaMalloc <allocedSite,freedSite, count>
// CudaMemCPU <allocedSite,freedSite, copyID, count> 
struct MemRecDataFile {
	FILE * _fid;
	MemRecDataFile(FILE * file) {
		_fid = file;
	}

	~MemRecDataFile() {
		fclose(_fid);
	}
	template<typename T> 
	void Write(std::vector<T> & data) {
		if (data.size() == 0)
			return;
		char * outMem = (char*) malloc((data.size())*data[0].GetSize());
		for (int i = 0; i < data.size(); i++){ 
			data[i].Serialize(&(outMem[i * data[i].GetSize()]));
		}
		fwrite(outMem, sizeof(char), (data.size())*data[0].GetSize(), _fid);
		free(outMem);
	};

	void Read(std::vector<CUMemTransferTracker*> & MemTrans, std::vector<CUMallocTracker*> & MallocTrac, std::vector<GLIBMallocTracker*> & GLIBMalloc) {
		fseek(_fid, 0, SEEK_END);
		size_t size = ftell(_fid);
		fseek(_fid, 0, SEEK_SET);
		char * data = (char *) malloc(size * sizeof(char));
		fread(data, sizeof(char), size, _fid);
		uint64_t pos = 0;
		while (pos < size) {
			CUMallocTracker * tmp1 = CUMallocTracker::Deserialize(&(data[pos]));
			CUMemTransferTracker * tmp2 = CUMemTransferTracker::Deserialize(&(data[pos]));
			GLIBMallocTracker * tmp3 = GLIBMallocTracker::Deserialize(&(data[pos]));
			if (tmp1 != NULL) {
				pos += tmp1->GetSize();
				MallocTrac.push_back(tmp1);
			} else if (tmp2 != NULL) {
				pos += tmp2->GetSize();
				MemTrans.push_back(tmp2);
			} else if (tmp3 != NULL) {
				pos += tmp3->GetSize();
				GLIBMalloc.push_back(tmp3); 
			} else {
				std::cerr << "[MemRecDataFile::Read] Unexpected end of file! exiting!" << std::endl;
				exit(-1); 
			}
		}
	};
};