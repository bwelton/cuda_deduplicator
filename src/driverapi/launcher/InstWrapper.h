#pragma once
#include "DyninstIncludes.h"
#include <vector>
#include <string>
#include <tuple>
#include "BinaryRewriter.h"
#include "BPatchBinary.h"
#include "DynOpsClass.h"

class InstWrapper{
public:
	InstWrapper(BinaryRewriter * rw, std::string def);
	void Run(std::string libcudaTouse);
	void ReadDefinition(std::string WrapperDef);
	void InsertWrappers(std::string libcudaTouse);
	std::vector<std::string> GetWrappedFuncNames();
	
private:
	std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string> > _wrapFunctions;
	BinaryRewriter * _rw;
	std::string _def;
	DynOpsClass _ops;
};
