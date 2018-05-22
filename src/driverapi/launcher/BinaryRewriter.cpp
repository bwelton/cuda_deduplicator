#include "BinaryRewriter.h"
BinaryRewriter::BinaryRewriter(std::string appName, bool openWriteable,  std::string outDir, bool readDepends, std::string dpFilename)  :
	_appName(appName), _write(openWriteable), _outDir(outDir), _readDepends(readDepends), _dpFilename(dpFilename) {
	Init();
}

BinaryRewriter::BinaryRewriter() {}
void BinaryManagerBase::OpenLibrary(std::string libname) {
	assert(_OpenBinaries.size() > 0);
	if(!_OpenBinaries[0]->LoadLibrary(libname))
		std::cout << "[BinaryRewriter] OpenLibrary Could not load library - " << libname << std::endl;
}

void BinaryRewriter::Init() {
	std::vector<std::string> depedencies;
	if (_readDepends){
		DependsFile readDepends(_dpFilename.c_str(), false);
		depedencies = readDepends.ReadLibraries();
		std::cout << "[BinaryRewriter] Dependency file contains the following entries : " << std::endl;
		for (auto i : depedencies) {
			std::cout << "[BinaryRewriter]\t" << i << std::endl;
		}
	}
	if (_write) {
		boost::filesystem::path outName(boost::filesystem::current_path());
		boost::filesystem::path p(_appName);
		//boost::filesystem::path outName(p.parent_path());
		outName /= _outDir;
		outName /= p.filename();
		std::cout << "[BinaryRewriter] Output filename is - " << outName.string() << std::endl;
		// Open the application
		BinaryManagerBase::_OpenBinaries.push_back(BPatchBinaryPtr(new BPatchBinary(_appName,true,outName.string())));
	} else {
		BinaryManagerBase::_OpenBinaries.push_back(BPatchBinaryPtr(new BPatchBinary(_appName,false)));
	}
	for (auto i : depedencies) {
		if (i.find("libcuda.so") != std::string::npos)
			continue;
		//BinaryManagerBase::_OpenBinaries.push_back(BPatchBinaryPtr(new BPatchBinary(i,false)));
		//if(!BinaryManagerBase::_OpenBinaries[0]->LoadLibrary(i))
		// 	std::cout << "[BinaryRewriter] Could not load library - " << i << std::endl;
	}


}

void BinaryRewriter::OpenAllDependencies() {
	std::vector<std::string> curList;
	for (auto i : BinaryManagerBase::_OpenBinaries) {
		std::vector<std::string> tmp_list = GetDependencies(i);
		curList.insert(curList.end(), tmp_list.begin(), tmp_list.end());
	}
	while (curList.size() > 0) {
		std::string tmp = curList.back();
		std::cout << "[BinaryRewriter] Loading dependencies for - " << tmp << std::endl;
		curList.pop_back();
		if (tmp.find("ld-linux-x86-64") != std::string::npos || 
			tmp.find("linux-vdso.so") != std::string::npos || 
			tmp.find("librt.so") != std::string::npos ||
			tmp.find("libpthread.so") != std::string::npos || 
			tmp.find("libdl.so") != std::string::npos)
			continue; 
		if (FindAppBinary(tmp).get())
			continue;
		BPatchBinaryPtr l = LoadObject(tmp);
		std::vector<std::string> tmp_list = GetDependencies(l);
		curList.insert(curList.end(), tmp_list.begin(), tmp_list.end());
	}

}

std::vector<std::string> BinaryRewriter::GetDependencies(BPatchBinaryPtr file) {
	std::vector<std::string> ret;
	std::vector<BPatch_object *> objs;
	file->GetAddressSpace()->getImage()->getObjects(objs);
	for (auto i : objs) {
		Symtab *symtab =  Dyninst::SymtabAPI::convert(i);
		std::vector<std::string> tmp = symtab->getDependencies();
		for (auto n : tmp)
			ret.push_back(_gen.FindLibraryInPath(n));
	}
	return ret;
}

BPatchBinaryPtr BinaryRewriter::FindAppBinary(std::string libname) {
	boost::filesystem::path tmpP(libname);
	std::string libFileName = tmpP.filename().string();

	for (auto i : BinaryManagerBase::_OpenBinaries) {
		boost::filesystem::path tmp(i->GetName());
		if (tmp.pathname().string().find(libFileName) != std::string::npos)
			return i;
	}
	return BPatchBinaryPtr();
}
BPatchBinaryPtr BinaryRewriter::LoadObject(std::string obj) {
	if (FindAppBinary(obj).get() != NULL)
		return FindAppBinary(obj);
	std::cout << "[BinaryRewriter] Loading library - " << obj << std::endl;
	boost::filesystem::path outName(boost::filesystem::current_path());
	boost::filesystem::path p(obj);
	//boost::filesystem::path outName(p.parent_path());
	outName /= _outDir;
	outName /= p.filename();
	BinaryManagerBase::_OpenBinaries.push_back(BPatchBinaryPtr(new BPatchBinary(obj,true,outName.string())));
	return BinaryManagerBase::_OpenBinaries[BinaryManagerBase::_OpenBinaries.size() - 1];
}


std::vector<BPatch_object *> BinaryRewriter::GetAllObjects() {
	std::vector<BPatch_object *> ret;
	for (auto i : BinaryManagerBase::_OpenBinaries) {
		std::vector<BPatch_object *> tmp;
		i->GetImage()->getObjects(tmp);
		ret.insert(ret.end(), tmp.begin(), tmp.end());
	}	
	return ret;
}


std::vector<BPatchBinaryPtr> BinaryRewriter::GetAllBinaryObjects() {
	return BinaryManagerBase::_OpenBinaries;
}

BPatchBinaryPtr BinaryManagerBase::GetAppBinary() {
	return _OpenBinaries[0];
}
ProcessRewriter::ProcessRewriter() {}

ProcessRewriter::ProcessRewriter(std::vector<std::string> appAndParams) {
	std::cout << "[ProcessRewriter] Attempting to start application - " << appAndParams[0] << std::endl;
	BinaryManagerBase::_OpenBinaries.push_back(BPatchBinaryPtr(new BPatchBinary(appAndParams)));
}