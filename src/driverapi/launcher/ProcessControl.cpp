#include "ProcessControl.h"

ProcessController::ProcessController(boost::program_options::variables_map vm) :
	_vm(vm), _launched(false), _insertedInstrimentation(false) {
}

BPatch_addressSpace * ProcessController::LaunchProcess() {
	BPatch_addressSpace * handle = NULL;
	std::vector<std::string> progName = _vm["prog"].as<std::vector<std::string> >();

	// Setup arguments
	char ** argv = (char**)malloc(progName.size() * sizeof(char *));
	for (int i = 0; i < progName.size(); i++) 
		argv[i] = strdup(progName[i].c_str());

	// Create the bpatch process
	handle = bpatch.processCreate(argv[0],(const char **)argv);
	assert(handle != NULL);

	// Free temporary argv
	for (int i = 0; i < progName.size(); i++)
		free(argv[i]);
	free(argv);

	_addrSpace = handle;
	_launched = true;
	_appProc = dynamic_cast<BPatch_process*>(_addrSpace);
	return handle;
}

BPatch * ProcessController::GetBPatch() {
	return &bpatch;
}

void ProcessController::Run() {
	_appProc->continueExecution();
	bpatch.waitForStatusChange();
}

bool ProcessController::IsTerminated() {
	return _appProc->isTerminated();
}

bool ProcessController::ContinueExecution() {
	return _appProc->continueExecution();
}

bool ProcessController::IsStopped() {
	return _appProc->isStopped();
}

void ProcessController::ReadDefinition(std::string WrapperDef) {
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
	    	std::cerr << "[PROCCTR] Token size is not 4 in wrapper def.... skipping this function" << std::endl;
	    	std::cerr << "[PROCCTR] Line skipped: " << line << std::endl;
	    } else {
	    	std::cerr << "[PROCCTR] Insserting Instrimentation Into: " << line << std::endl;
	    	std::transform(tokens[0].begin(), tokens[0].end(), tokens[0].begin(), ::tolower);
	    	_wrapFunctions.push_back(std::make_tuple(tokens[0],tokens[1],tokens[2],tokens[3], tokens[4]));
	    }
	}
}

std::vector<BPatch_function *> findFuncByName(BPatch_image * appImage, const char * funcName) {
  /* fundFunctions returns a list of all functions with the name 'funcName' in the binary */
  BPatch_Vector<BPatch_function * >funcs;
  if (NULL == appImage->findFunction(funcName, funcs) || !funcs.size() || NULL == funcs[0])
  {
      std::cerr << "Failed to find " << funcName <<" function in the instrumentation library" << std::endl;
      return std::vector<BPatch_function *>();
  }
  std::cerr << "Found " << funcName << " this many times " << funcs.size() << std::endl;
  if (funcs.size() > 1) {
    for(int i = 0; i < funcs.size(); i++ )
    {
        std::cerr << "    " << funcs[i]->getName() << std::endl;
    }
  }
  return funcs;
}

void ProcessController::InstrimentApplication() {
	BPatch_image * img = _addrSpace->getImage();
	std::map<std::string, std::vector<Symbol *> > instLibSymbols;
	uint64_t wrapCount = 0;
	uint64_t totalFunctions = 0;
	for (auto i : _wrapFunctions) {
		totalFunctions += 1;
		if (std::get<0>(i).find("wrap") == std::string::npos)
			continue;
		std::vector<BPatch_function *> orig = findFuncByName(img,std::get<1>(i).c_str());
		if (orig.size() == 0) {
			std::cerr << "[PROCCTR] Could not find function with name - " << std::get<1>(i) << std::endl;
			continue;
		}
		std::vector<BPatch_function *> wrapfunc = findFuncByName(img,std::get<2>(i).c_str());
		if (wrapfunc.size() == 0){
			std::cerr << "[PROCCTR] Could not find wrapper function - " << std::get<2>(i) << std::endl;
			continue;
		}
		
		// Find Hook Symbol	
		if (instLibSymbols.find(std::get<3>(i)) == instLibSymbols.end()) {
			std::vector<Symbol *> tmp;
			Dyninst::SymtabAPI::Module *symtab =  Dyninst::SymtabAPI::convert(wrapfunc[0]->getModule());
			symtab->getAllSymbols(tmp);	
			instLibSymbols[std::get<3>(i)] = tmp;
		}

		std::cerr << "[PROCCTR] Replacing " << orig[0]->getName() << " with " << wrapfunc[0]->getName() << " and new hook " << std::get<4>(i) << std::endl;
		for (Symbol * sym : instLibSymbols[std::get<3>(i)]) {
			if (sym->getPrettyName() == std::get<4>(i)) {
				if (_addrSpace->wrapFunction(orig[0], wrapfunc[0], sym) == true){
					std::cerr << "[PROCCTR] Function " << orig[0] << " wrapped successful" << std::endl;
					wrapCount += 1;
				}
				else 
					std::cerr << "[PROCCTR] Function " << orig[0] << " WRAPPING FAILED" << std::endl;	
				break;
			}
		}
	}
	_insertedInstrimentation =  true;
}

bool ProcessController::LoadWrapperLibrary(std::string libname) {
	if(!_addrSpace->loadLibrary(libname.c_str())) {
		return false;
	}
	return true;
}	

std::set<std::string> ProcessController::WrapperLibraries() {
	std::set<std::string> ret;
	for (auto i : _wrapFunctions) {
		if (std::get<0>(i).find("wrap") != std::string::npos) {
			ret.insert(std::get<3>(i));
		}
	}
	return ret;
}

bool ProcessController::InsertInstrimentation(std::string WrapperDef) {
	// Force libcuda to be loaded
	assert(LoadWrapperLibrary(std::string("libcuda.so")) != false);
    ReadDefinition(WrapperDef);
	std::set<std::string> libsToLoad = WrapperLibraries();
	for (auto i : libsToLoad)
		LoadWrapperLibrary(i);
	InstrimentApplication();
}