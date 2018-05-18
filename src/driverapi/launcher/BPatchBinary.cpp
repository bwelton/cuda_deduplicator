#include "BPatchBinary.h"

BPatchBinary::BPatchBinary(std::string binName, bool output, std::string outName)  :
	_binName(binName), _output(output), _outName(outName), _procEdit(false) {
	bpatch.setInstrStackFrames(true);
	bpatch.setLivenessAnalysis(false);
	_be = bpatch.openBinary(_binName.c_str(), true);
	_be->getAS(_multiAs);
	std::cout << "[BPatchBinary] Loaded " << _multiAs.size() << " address spaces" << std::endl;
	// assert(_as != NULL);
	//_as = dynamic_cast<BPatch_binaryEdit*>(_as);
	bpatch.setInstrStackFrames(true);
	bpatch.setLivenessAnalysis(false);
}

BPatchBinary::BPatchBinary(std::vector<std::string> appAndArgs)  :
	_binName(appAndArgs[0]), _output(false), _outName(std::string("")), _procEdit(true) {
	bpatch.setInstrStackFrames(true);
	bpatch.setLivenessAnalysis(false);

	char ** argv = (char**)malloc(appAndArgs.size() * sizeof(char *)+sizeof(char *));
	for (int i = 0; i < appAndArgs.size(); i++) 
		argv[i] = strdup(appAndArgs[i].c_str());

	argv[appAndArgs.size()] = NULL;
	for (int i = 0; i < appAndArgs.size(); i++)
		std::cout << "[BPatchBinary] Launch arguments for program - " << argv[i] << std::endl;

	_as = bpatch.processCreate(argv[0],(const char **)argv);

	for (int i = 0; i < appAndArgs.size(); i++)
		free(argv[i]);
	free(argv);
	assert(_as != NULL);
	_pe = dynamic_cast<BPatch_process*>(_as);
	bpatch.setInstrStackFrames(true);
	bpatch.setLivenessAnalysis(false);
}


BPatchBinary::~BPatchBinary() {
	if(_output){
		boost::filesystem::path curDir(boost::filesystem::current_path());
		boost::filesystem::path p(_outName);
		chdir(p.parent_path().string().c_str());
		std::cout << "[BPatchBinary] Saving binary to file - " << _outName << std::endl;
		if(!_be->writeFile(_outName.c_str()))
			std::cout << "[BPatchBinary] Could not generate output binary - " << _outName << std::endl;
		chdir(curDir.parent_path().string().c_str());
	}
}

BPatch_image * BPatchBinary::GetImage() {
	if (!_procEdit)
		return _be->getImage();
	return _pe->getImage();
}

bool BPatchBinary::RunUntilCompletion() {
	if (!_procEdit)
		return false;
	std::cout << "[BPatchBinary] Running program until compleation" << std::endl;
	if (!_pe->continueExecution()) {
	    fprintf(stderr, "continueExecution failed\n");
	}
	bpatch.waitForStatusChange();
	// while (!_pe->isTerminated()) {
	// 	bpatch.waitForStatusChange();
	// 	_pe->continueExecution();
	// }
	return true;
}

bool BPatchBinary::LoadLibrary(std::string libName) {
	std::vector<std::string> tmp = _ops.GetLibraryNames(GetAddressSpace());
	for (auto i : tmp) 
		if (libName.find(i) != std::string::npos || i.find(libName) != std::string::npos || i == libName){
			std::cout << "[BPatchBinary] Library already loaded - " << libName.c_str() << std::endl;
			return true;
		}
	if(GetAddressSpace()->loadLibrary(libName.c_str())){
		std::cout << "[BPatchBinary] Successfully loaded library - " << libName.c_str() << std::endl;
		return true;
	}
	std::cout << "[BPatchBinary] Failed to load library - " << libName.c_str() << std::endl;
	return false;
}
BPatch_addressSpace * BPatchBinary::GetAddressSpace() {
	if (_procEdit)
		return _as;
	else if {
		return _multiAs[0];
	}
}