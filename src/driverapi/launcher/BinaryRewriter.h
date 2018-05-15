#pragma once
#include "DyninstIncludes.h"
#include "DependsFile.h"
#include "BPatchBinary.h"
#include <memory>
#include <iostream>
#include <array>
#include <boost/filesystem.hpp>

typedef std::shared_ptr<BPatchBinary> BPatchBinaryPtr;
class BinaryManagerBase {
public: 
	BinaryManagerBase() {};
	void OpenLibrary(std::string libname);
	BPatchBinaryPtr GetAppBinary();
protected:
	std::vector<BPatchBinaryPtr > _OpenBinaries;
};



class BinaryRewriter : public BinaryManagerBase { 
public:
	BinaryRewriter(std::string appName, bool openWriteable, std::string outDir = std::string(""), bool readDepends = false);
	// void OpenLibrary(std::string libname);
	// BPatchBinaryPtr GetAppBinary();
private:
	void Init();
	std::string _appName;
	std::string _outDir;
	bool _write;
	bool _readDepends;
	// std::string _appName;
	// std::string _outDir;
	// bool _write;
	// bool _readDepends;
	// std::vector<BPatchBinaryPtr > _OpenBinaries;
};


// class ProcessRewriter : public BinaryManagerBase {
// public:
// 	ProcessRewriter(std::vector<std::string> appAndParams, )

// };