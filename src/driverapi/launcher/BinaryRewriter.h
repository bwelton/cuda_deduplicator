#pragma once
#include "DyninstIncludes.h"
#include "DependsFile.h"
#include "BPatchBinary.h"
#include <memory>
#include <iostream>
#include <array>
#include <boost/filesystem.hpp>
using namespace boost::filesystem;

class BinaryRewriter{
public:
	BinaryRewriter(std::string appName, bool openWriteable, std::string outDir = std::string(""), bool readDepends = false);
	void OpenLibrary(std::string libname);

private:
	void Init();
	std::string _appName;
	std::string _outDir;
	bool _write;
	bool _readDepends;
	std::vector<std::shared_ptr<BPatchBinary> > _OpenBinaries;
};


