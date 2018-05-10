#pragma once
#include "DyninstIncludes.h"
#include "DependsFile.h"
#include "BPatchBinary.h"
#include <memory>
#include <iostream>
#include <array>
//#include <boost/filesystem.hpp>
//using namespace boost::filesystem;

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


BinaryRewriter::BinaryRewriter(std::string appName, bool openWriteable,  std::string outDir, bool readDepends)  :
	_appName(appName), _write(openWriteable), _outDir(outDir), _readDepends(readDepends) {
	Init();
}


void BinaryRewriter::Init() {
	std::vector<std::string> depedencies;
	if (_readDepends){
		DependsFile readDepends("NI_dependencies.txt", false);
		depedencies = ReadLibraries();
		std::cout << "[BinaryRewriter] Dependency file contains the following entries : " << std::endl;
		for (auto i : depedencies) {
			std::cout << "[BinaryRewriter]\t" << i << std::endl;
		}
	}
	if (_write) {
		boost::filesystem::path p(_appName);
		boost::filesystem::path outName(_outDir);
		outName /= p.filename();
		// Open the application
		_OpenBinaries.push_back(std::shared_ptr<BPatchBinary>(new BPatchBinary(_appName,true,outname.string())));
	} else {
		_OpenBinaries.push_back(std::shared_ptr<BPatchBinary>(new BPatchBinary(_appName,false)));
	}
	
}