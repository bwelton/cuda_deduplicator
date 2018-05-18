#pragma once
#include <unistd.h>
#include <boost/filesystem.hpp>
#include "DyninstIncludes.h"
#include "DynOpsClass.h"
class BPatchBinary {
public:
	BPatchBinary(std::string binName, bool output = false, std::string outName = std::string(""));
	BPatchBinary(std::vector<std::string> appAndArgs);
	BPatch_image * GetImage();
	BPatch_addressSpace * GetAddressSpace();
	~BPatchBinary();
	bool LoadLibrary(std::string libName);
	bool RunUntilCompletion();
private:
	DynOpsClass _ops;
	std::vector<BPatch_addressSpace*> _multiAs;
	BPatch_addressSpace * _as;
	BPatch_binaryEdit * _be;
	std::string _binName;
	bool _output;
	std::string _outName;
	BPatch bpatch;
	BPatch_process * _pe;
	bool _procEdit;
};

// class BinaryRewriter{
// public:
// 	BinaryRewriter(std::string appName, bool readDepends = false);


	

// };