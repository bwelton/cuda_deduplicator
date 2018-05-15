#include "BinaryRewriter.h"
BinaryRewriter::BinaryRewriter(std::string appName, bool openWriteable,  std::string outDir, bool readDepends)  :
	_appName(appName), _write(openWriteable), _outDir(outDir), _readDepends(readDepends) {
	Init();
}

void BinaryManagerBase::OpenLibrary(std::string libname) {
	assert(_OpenBinaries.size() > 0);
	if(!_OpenBinaries[0]->LoadLibrary(libname))
		std::cout << "[BinaryRewriter] OpenLibrary Could not load library - " << libname << std::endl;
}

void BinaryRewriter::Init() {
	std::vector<std::string> depedencies;
	if (_readDepends){
		DependsFile readDepends("NI_dependencies.txt", false);
		depedencies = readDepends.ReadLibraries();
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
		BinaryManagerBase::_OpenBinaries.push_back(BPatchBinaryPtr(new BPatchBinary(_appName,true,outName.string())));
	} else {
		BinaryManagerBase::_OpenBinaries.push_back(BPatchBinaryPtr(new BPatchBinary(_appName,false)));
	}
	for (auto i : depedencies)
		if(!BinaryManagerBase::_OpenBinaries[0]->LoadLibrary(i))
			std::cout << "[BinaryRewriter] Could not load library - " << i << std::endl;
}

BPatchBinaryPtr BinaryManagerBase::GetAppBinary() {
	return _OpenBinaries[0];
}