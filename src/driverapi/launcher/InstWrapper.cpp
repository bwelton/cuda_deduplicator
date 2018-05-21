#include "InstWrapper.h"

InstWrapper::InstWrapper(BinaryRewriter * rw, std::string def) : _rw(rw), _def(def) { }

void InstWrapper::Run() {
	ReadDefinition(_def);
	InsertWrappers();
}

void InstWrapper::InsertWrappers(std::stirng libcudaTouse) {
	BPatchBinaryPtr libCuda = _rw->LoadObject(libcudaTouse);
	for (auto i : _wrapFunctions){
		std::string instType, funcNameToWrap, wrapperFunction, wrapperLib, symbolToReplace;
		instType = std::get<0>(i);
		funcNameToWrap = std::get<1>(i);
		wrapperFunction = std::get<2>(i);
		wrapperLib = std::get<3>(i);
		symbolToReplace = std::get<4>(i);

		if (instType.find("wrap") == std::string::npos)
			continue;

		if (funcNameToWrap.find("0x") != std::string::npos) 
			continue;

		BPatch_object * wrapperLibrary = libCuda->GetObject(wrapperLib);
		BPatch_function * orig = NULL;
		BPatch_function * newWrap = NULL;

		_ops.FindFuncByName(libCuda->GetAddressSpace(), orig, funcNameToWrap);
		_ops.FindFuncByName(libCuda->GetAddressSpace(), newWrap, wrapperFunction);
		assert(orig != NULL);
		assert(newWrap != NULL);
		Dyninst::SymtabAPI::Symtab * symt = Dyninst::SymtabAPI::convert(wrapperLibrary);
		std::vector<Dyninst::SymtabAPI::Symbol *> tmp;
		symt->getAllSymbols(tmp);
		for(auto sym : tmp) {
			if (sym->getPrettyName() == symbolToReplace) {
				if (libCuda->GetAddressSpace()->wrapFunction(orig,  newWrap, sym) == true){
					std::cout << "[InstWrapper] Succesfully wrapped function - " << funcNameToWrap << std::endl;
				} else {
					std::cout << "[InstWrapper] FAILED to wrap funciton - " << funcNameToWrap << std::endl;
				}
				break;
			}
		}
	}
}

void InstWrapper::ReadDefinition(std::string WrapperDef) {
	std::ifstream f;
	std::string line;
	f.open(WrapperDef.c_str(),std::ifstream::in);
	while (std::getline(f, line)) {
	    std::stringstream ss(line);
	    std::vector<std::string> tokens;
	    std::string item;
	    while (std::getline(ss, item, ',')) {
	        tokens.push_back(item);
	    }
	    if (tokens.size() != 5) {
	    	std::cout << "[InstWrapper] Could not read line of wrapper def" << std::endl;
	    } else {
	    	std::transform(tokens[0].begin(), tokens[0].end(), tokens[0].begin(), ::tolower);
	    	std::cout << "[InstWrapper] Inserting function wrapping line for function - " << tokens[0] << std::endl;
	    	_wrapFunctions.push_back(std::make_tuple(tokens[0],tokens[1],tokens[2],tokens[3], tokens[4]));
	    }
	}
}
