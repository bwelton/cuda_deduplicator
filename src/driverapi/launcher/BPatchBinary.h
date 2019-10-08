#pragma once
#include "DyninstIncludes.h"
#include <vector>
#include <unordered_map>
#include <memory>
#include <unordered_set>
class BPatchBinary {
public:
	BPatchBinary(std::string binName, bool output = false, std::string outName = std::string(""));
	BPatch_image * GetImage();
	BPatch_addressSpace * GetAddressSpace();
	~BPatchBinary();
	std::vector<uint64_t> FindSyncCandidates();
private:
	BPatch_addressSpace * _as;
	BPatch_binaryEdit * _be;
	std::string _binName;
	bool _output;
	std::string _outName;
	BPatch bpatch;
};

struct FuncCFG{ 
	FuncCFG(BPatch_Function * in) : func(in) {};
	std::unordered_set<std::shared_ptr<FuncCFG>> parents;
	std::unordered_set<std::shared_ptr<FuncCFG>> children;

	void InsertChild(std::shared_ptr<FuncCFG> child) {
		children.insert(child);
	}
	void InsertParent(std::shared_ptr<FuncCFG> par) {
		parents.insert(par);
	}
	BPatch_Function * func; 
};

