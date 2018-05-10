#include "BPatchBinary.h"

BPatchBinary::BPatchBinary(std::string binName, bool output, std::string outName)  :
	_binName(binName), _output(output), _outName(outName) {
	_as = bpatch.openBinary(_binName.c_str(), true);
	assert(_as != NULL);
	_be = dynamic_cast<BPatch_binaryEdit*>(_as);
}

BPatchBinary::~BPatchBinary() {
	if(_output){
		std::cout << "[BPatchBinary] Saving binary to file - " << _outName << std::endl;
		if(!_be->writeFile(_outName.c_str()))
			std::cout << "[BPatchBinary] Could not generate output binary - " << _outName << std::endl;
	}
}

BPatch_image * BPatchBinary::GetImage() {
	return _be->getImage();
}


bool BPatchBinary::LoadLibrary(std::string libName) {
	std::vector<std::string> tmp = _ops.GetLibraryNames(GetAddressSpace());
	for (auto i : tmp) 
		if (libName.find(i) != std::string::npos || i.find(libName) != std::string::npos || i == libName)
			return true;
	if(GetAddressSpace()->loadLibrary(libName.c_str()))
		return true;
	return false;
}
BPatch_addressSpace * BPatchBinary::GetAddressSpace() {
	return _as;
}