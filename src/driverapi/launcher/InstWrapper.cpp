#include "InstWrapper.h"

InstWrapper::InstWrapper(BinaryRewriter * rw, std::string def, InstrimentationLoggerPtr log) : _rw(rw), _def(def), _logger(log) { ReadDefinition(_def);}

void InstWrapper::Run(std::string libcudaTouse) {
	InsertWrappers(libcudaTouse);
}

std::vector<std::string> InstWrapper::GetWrappedFuncNames() {
	std::vector<std::string> ret;
	for (auto i : _wrapFunctions)
		ret.push_back(std::get<1>(i));
	return ret;
	
}

void InstWrapper::InsertWrappers(std::string libcudaTouse) {
	BPatchBinaryPtr libCuda = _rw->LoadObject(libcudaTouse);
	for (auto i : _wrapFunctions){
		std::string instType, funcNameToWrap, wrapperFunction, wrapperLib, symbolToReplace;
		instType = std::get<0>(i);
		funcNameToWrap = std::get<1>(i);
		wrapperFunction = std::get<2>(i);
		wrapperLib = std::get<3>(i);
		symbolToReplace = std::get<4>(i);
		//BPatchBinaryPtr libDriverAPIWrapper = _rw->LoadObject(wrapperLib);

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
				//std::cout << "[InstWrapper] Symbol Captured: " << symbolToReplace << "off:" << sym->getOffset() << ",PtrOffset: " << sym->getPtrOffset() << ", LocalTOC:" << sym->getLocalTOC() << ", size:" << sym->getSize() << std::endl;
				if (libCuda->GetAddressSpace()->wrapFunction(orig,  newWrap, sym) == true){
					_logger->Log(orig->getModule()->getObject()->pathName(), orig->getName(), WRAPPED_FUNCTION);
					std::cout << "[InstWrapper] Succesfully wrapped function - " << funcNameToWrap << std::endl;
				} else {
					std::cout << "[InstWrapper] FAILED to wrap funciton - " << funcNameToWrap << std::endl;
				}
				break;
			}
		}
		// tmp.clear();
		// symt->getAllSymbols(tmp);
		// for(auto sym : tmp) 
		// 	if (sym->getPrettyName() == symbolToReplace) 
		// 		std::cout << "[InstWrapper] POST Symbol Captured: " << symbolToReplace << "off:" << sym->getOffset() << ",PtrOffset: " << sym->getPtrOffset() << ", LocalTOC:" << sym->getLocalTOC() << ", size:" << sym->getSize() << std::endl;
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
	    	std::cout << "[InstWrapper] Inserting function wrapping line for function - " << tokens[1] << std::endl;
	    	_wrapFunctions.push_back(std::make_tuple(tokens[0],tokens[1],tokens[2],tokens[3], tokens[4]));
	    }
	}
}
