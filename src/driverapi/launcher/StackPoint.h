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

#define SP_DEBUG 1

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
		uint64_t size = 0;
		int pos = 0;
		std::memcpy(&size, data, sizeof(uint64_t));
		pos += sizeof(uint64_t);
		if (len < size + sizeof(uint64_t) + sizeof(uint64_t))
			assert(len < size + sizeof(uint64_t) + sizeof(uint64_t));
		libname = std::string((const char *) &(data[pos]), size);
		pos += size;
		std::memcpy(&libOffset, &(data[pos]), sizeof(uint64_t));
#ifdef SP_DEBUG
		std::cerr << "Decoding: " << libname << "," << libOffset << std::endl;
#endif
		empty = false;
		framePtr = libOffset;
		return pos;
	}

};

namespace std {
	template<> struct less<StackPoint> {
		bool operator() (const StackPoint& lhs, const StackPoint& rhs) {
			return lhs.framePtr < rhs.framePtr;
		};
	};
};
