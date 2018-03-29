#pragma once
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
#include <cassert>
#include <sys/types.h>
#include <unistd.h>
#include <mutex>
#include <queue>
#include <boost/program_options.hpp>

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
#include "LogInfo.h"
#include "Constants.h"

//#define SP_DEBUG 1

struct StackPoint {
	std::string fname;
	std::string libname;
	std::string funcName;
	uint64_t libOffset;
	uint64_t funcOffset;
	uint64_t framePtr;
	bool inMain;
	bool empty;
	StackPoint() : empty(true), libOffset(0), framePtr(0), funcOffset(0), fname(std::string("")), libname(std::string("")) {
		inMain = false;
	};
	uint64_t GetKey() {
		return framePtr;
	};

	int Serialize(char * data, int size) {
		int pos = 0;
		if (size < sizeof(uint64_t) + libname.size() + sizeof(uint64_t))
			return -1;

#ifdef SP_DEBUG
		std::cerr << "Encoding: " << libname << "," << libOffset << std::endl;
#endif
		uint64_t stringSize = libname.size();
		std::memcpy(&(data[0]), &stringSize, sizeof(uint64_t));
		pos += sizeof(uint64_t);
		std::memcpy(&(data[pos]),libname.c_str(), libname.size());
		pos += libname.size();
		std::memcpy(&(data[pos]), &libOffset, sizeof(uint64_t));
		return pos + sizeof(uint64_t);
	}

	int Deserialize(char * data, int len) {
		char tmp[1024];
		uint64_t size = 0;
		int pos = 0;
		std::memcpy(&size, data, sizeof(uint64_t));
		pos += sizeof(uint64_t);
		if (len < size + sizeof(uint64_t) + sizeof(uint64_t))
			assert(len < size + sizeof(uint64_t) + sizeof(uint64_t));
		if (size >= 1024)
			assert(size < 1024);
		std::memcpy(tmp, &(data[pos]), size);

		tmp[size] = '\000';
		libname = std::string(tmp);
		pos += size;
		std::memcpy(&libOffset, &(data[pos]), sizeof(uint64_t));
#ifdef SP_DEBUG
		std::cerr << "Decoding: " << libname << "," << libOffset << std::endl;
#endif
		empty = false;
		framePtr = libOffset;
		pos += sizeof(uint64_t);
		return pos;
	}

};

struct StackHasher{
	std::stringstream ss;
	uint64_t HashStack(std::vector<StackPoint> & points) {
		if (points.size() == 0)
			return 0;
		ss.str(std::string());
		for (auto i : points)
			ss << i.libname << "," << i.libOffset << "|";
		return std::hash<std::string>()(ss.str());
	}
};


// Key file for the stacks outputted
struct StackKeyWriter {
	char buffer[512000];
	uint64_t curPos;
	std::map<uint64_t, uint64_t> prevStacks;
	StackHasher h;
	FILE * out;
	StackKeyWriter(FILE * fp) {
		out = fp;
		curPos = 1;
	}
	~StackKeyWriter() {
		fclose(out);
	}
	uint64_t InsertStack(std::vector<StackPoint> & points){
		uint64_t hash = h.HashStack(points);
		if (hash == 0)
			return 0;
		if (prevStacks.find(hash) != prevStacks.end()) {
			hash = prevStacks[hash];
			return hash;
		} else {
			prevStacks[hash] = curPos;
			hash = curPos;
			curPos++;
		}
		int pos = 0;
		std::stringstream outStr;
		outStr << hash << "$";
		for (auto i : points)
			outStr << i.libname << "@" << i.libOffset << "$";

		std::string t = outStr.str();
		t.pop_back();
		t = t + std::string("\n");
		do {
			pos += fwrite(t.c_str(), 1, t.size() - pos, out);
		} while(pos != t.size());
		std::cerr << "Wrote stack with hash id: " << hash << std::endl;
	}
};

struct StackKeyReader {
	FILE * in;
	StackKeyReader(FILE * fp) {
		in = fp;
	}
	~StackKeyReader() {
		fclose(in);
	}
	std::map<uint64_t, std::vector<StackPoint> > ReadStacks() {
		std::map<uint64_t, std::vector<StackPoint> > ret;
		fseek(in, 0, SEEK_END);
  		uint64_t size = ftell(in);
  		fseek(in, 0, SEEK_SET);
  		std::shared_ptr<char> tmp(new char[size+1]);
  		uint64_t readPos = 0;
  		do {
  			readPos += fread(tmp.get(), 1, size - readPos, in);
  		} while (readPos != size);
  		tmp.get()[size] = '\000';
  		char * token = strtok(tmp.get(), "\n");
  		while (token != NULL) {
  			std::string tmpToken = std::string(token);
  			std::cerr << tmpToken << std::endl;
  			uint64_t hash = std::stoull(tmpToken.substr(0, tmpToken.find("$")));
  			uint64_t start = tmpToken.find("$") + 1;
  			ret[hash] = std::vector<StackPoint>();
  			while(start < tmpToken.size()){
  				StackPoint sp;
  				std::string r;
  				if (tmpToken.find("$", start) != std::string::npos){
  					r = tmpToken.substr(start, tmpToken.find("$", start) - 2);
  					start = tmpToken.find("$", start) + 1;
	  			}	else{
  					r = tmpToken.substr(start);
  					start = tmpToken.size();
  				}
  				std::cerr << r << std::endl;
  				sp.libname = r.substr(0, r.find("@"));	
  				sp.libOffset = std::stoull(r.substr(r.find("@")));
  				std::cerr <<  hash << "," << sp.libname << "," << sp.libOffset << std::endl;
  				ret[hash].push_back(sp);
  			}
  			token = strtok(NULL,"\n");
  		}


		// while(fread(&size,1, sizeof(int), in) > 0) {
		// 	if (feof(in))
		// 		break;
		// 	std::vector<StackPoint> points; 
		// 	uint64_t hashId, recCount, pos;
		// 	pos = 0;
		// 	int read = 0;
		// 	do {
		// 		read += fread(&(buffer[read]), 1, size - read, in);
		// 	} while (read < size);
		// 	assert(read == size);
		// 	std::memcpy(&hashId, &(buffer[pos]), sizeof(uint64_t));
		// 	pos += sizeof(uint64_t);
		// 	std::memcpy(&recCount, &(buffer[pos]), sizeof(uint64_t));
		// 	pos += sizeof(uint64_t);
		// 	for (int i = 0; i < recCount; i++) {
		// 		StackPoint sp;
		// 		pos += sp.Deserialize(&(buffer[pos]), size - pos);
		// 		points.push_back(sp);
		// 	}
		// 	ret[hashId] = points;
		// 	std::cerr << "Read stack with hash id: " << hashId << std::endl;
		// }
		return ret;
	}
};


namespace std {
	template<> struct less<StackPoint> {
		bool operator() (const StackPoint& lhs, const StackPoint& rhs) {
			return lhs.framePtr < rhs.framePtr;
		};
	};
};

