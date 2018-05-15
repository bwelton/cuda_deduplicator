#pragma once
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
private:
	DynOpsClass _ops;
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