#include "ProcessControl.h"
static BPatch bpatch;
static ProcessController * curController;
ProcessController::ProcessController(boost::program_options::variables_map vm) :
	_vm(vm), _launched(false), _insertedInstrimentation(false), _terminated(false) {
}

BPatch_addressSpace * ProcessController::LaunchProcess() {
	BPatch_addressSpace * handle = NULL;
	std::vector<std::string> progName = _vm["prog"].as<std::vector<std::string> >();

	// Setup arguments
	char ** argv = (char**)malloc(progName.size() * sizeof(char *)+1);
	for (int i = 0; i < progName.size(); i++) 
		argv[i] = strdup(progName[i].c_str());

	argv[progName.size()] = NULL;
	for (int i = 0; i < progName.size(); i++)
		std::cerr << "[PROCCTR] Launch Arguments - " << argv[i] << std::endl;
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

BPatch_addressSpace * ProcessController::LaunchProcessInstrimenter(std::string WrapperDef) {
	BPatch_addressSpace * handle = NULL;
	std::vector<std::string> progName = _vm["prog"].as<std::vector<std::string> >();

	// Insert Instrimentation Library into binary before launching.

	bpatch.setInstrStackFrames(true);
	BPatch_binaryEdit *app = bpatch.openBinary(progName[0].c_str(), true);
	ReadDefinition(WrapperDef);
	std::set<std::string> libs = WrapperLibraries();
	for (auto i : libs) {
		assert(app->loadLibrary(i.c_str()) != NULL);
	}
	progName[0] = progName[0] + std::string("_withlibs");
	if(!app->writeFile(progName[0].c_str())) {
		std::cerr << "[PROCCTR] Could not write output binary" << std::endl;
		exit(-1);
	}

	// Setup arguments
	char ** argv = (char**)malloc(progName.size() * sizeof(char *)+1);
	for (int i = 0; i < progName.size(); i++) 
		argv[i] = strdup(progName[i].c_str());

	argv[progName.size()] = NULL;
	for (int i = 0; i < progName.size(); i++)
		std::cerr << "[PROCCTR] Launch Arguments - " << argv[i] << std::endl;
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
	//_appProc->continueExecution();
	
	bpatch.waitForStatusChange();
}

bool ProcessController::IsTerminated() {
	if (_terminated == true)
		return _terminated;
	else 
		_terminated = _appProc->isTerminated();
	return _terminated;
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
	bool print = true;

	for (auto i : _loadedLibraries) {
		BPatch_object * obj = i.second;
		std::vector<Symbol *> tmp;
		Dyninst::SymtabAPI::Symtab * symt = Dyninst::SymtabAPI::convert(obj);
		symt->getAllSymbols(tmp);
		instLibSymbols[i.first] = tmp;
	}
	// {
	// 	std::vector<BPatch_variableExpr *> vars;
	// 	img->getVariables(vars);
	// 	for (auto n : vars){
	// 		std::cerr << "Global Variable: " << n->getName() << std::endl;
	// 		std::string curTmp = std::string(n->getName());
	// 		uint64_t ptr;
	// 		if (curTmp.find(std::string("ORIGINAL_SOMETHING")) != std::string::npos) {
	// 			n->readValue((void*)&ptr, sizeof(uint64_t));
	// 			std::cerr << "VALUE: " << std::hex << ptr << std::dec << std::endl;
	// 		}
	// 	}
	// }
	for (auto i : _wrapFunctions) {
		totalFunctions += 1;
		if (std::get<0>(i).find("wrap") == std::string::npos)
			continue;
		BPatch_Vector<BPatch_function *> orig = findFuncByName(img,std::get<1>(i).c_str());
		//std::vector<BPatch_function *> * orig2 =  mod->findFunction(std::get<1>(i).c_str(), funcs, true, false, false, false);//findFuncByName(img,std::get<1>(i).c_str());
		//std::vector<BPatch_function *> orig = *orig2;		
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
			assert(1 == 0);
			std::vector<Symbol *> tmp;
			Dyninst::SymtabAPI::Module *symtab =  Dyninst::SymtabAPI::convert(wrapfunc[0]->getModule());
			//symtab->getAllUndefinedSymbols(tmp);	
			//symtab->getAllSymbolsByType(tmp, Dyninst::Symbol::ST_UNKNOWN);	
			instLibSymbols[std::get<3>(i)] = tmp;
		}

		std::cerr << "[PROCCTR] Replacing " << orig[0]->getName() << " with " << wrapfunc[0]->getName() << " and new hook " << std::get<4>(i) << std::endl;
		Symbol * storedSymbol = NULL;
		//bool firstPass = true;
		for (Symbol * sym : instLibSymbols[std::get<3>(i)]) {
			// if (print == true)
			// 	std::cerr << sym->getMangledName() << std::endl;
			if (sym->getPrettyName() == std::string(std::get<4>(i))) {
				// if(firstPass){
				// 	firstPass = false;
				// 	continue;
				// }
				uint64_t ptr;
				Symbol *newsym = new Symbol("add_sym_newsymbol",
			      	Symbol::ST_FUNCTION,
			      	Symbol::SL_GLOBAL,
			      	Symbol::SV_DEFAULT,
			      	sym->getOffset(),
			      	sym->getModule(),
				  	sym->getRegion());
				std::cerr << "Symbol is a function " << newsym->isFunction() << std::endl;
				//newsym->readValue((void*)&ptr, sizeof(uint64_t));
				std::cerr << "VALUE: " << newsym->getOffset() << "," << newsym->getPtrOffset() << "," << newsym->isVariable() << "," << newsym->getIndex() << std::endl;
				if (_addrSpace->wrapFunction(orig[0], wrapfunc[0], newsym) == true){
					std::cerr << "[PROCCTR] Function " << orig[0]->getName() << " wrapped successful" << std::endl;
					wrapCount += 1;
					storedSymbol = newsym;
					//newsym->readValue((void*)&ptr, sizeof(uint64_t));
					std::cerr << "VALUE: " << newsym->getOffset() << "," << newsym->getPtrOffset() << "," << newsym->isVariable() << "," << newsym->getIndex() << std::endl;
				}
				else 
					std::cerr << "[PROCCTR] Function " << orig[0]->getName() << " WRAPPING FAILED" << std::endl;	
				//break;
			}
		}
		if (storedSymbol != NULL) {
			
			// std::vector<BPatch_variableExpr *> vars;
			// img->getVariables(vars);
			// for (auto n : vars){
			// 	std::cerr << "Global Variable: " << n->getName() << std::endl;
			// 	std::string curTmp = std::string(n->getName());
			// 	uint64_t ptr;
			// 	if (curTmp.find(std::string("ORIGINAL_SOMETHING")) != std::string::npos) {
			// 		n->readValue((void*)&ptr, sizeof(uint64_t));
			// 		std::cerr << "VALUE: " << std::hex << ptr << std::dec << std::endl;
			// 		//ptr = 0;
			// 		//n->writeValue((void *)&ptr, int(sizeof(uint64_t)), false);
			// 	}
			// }
			// BPatch_object * obj = _loadedLibraries[std::get<3>(i)];
			// std::vector<BPatch_function *> fm;
			// _addrSpace->findFunction(std::get<4>(i).c_str(), fm, true, false, true, false);

			// std::vector<Symbol *> tmp;
			// Dyninst::SymtabAPI::Symtab * symt = Dyninst::SymtabAPI::convert(obj);
			// symt->findSymbol(tmp, std::get<4>(i).c_str(), Symbol::ST_UNKNOWN, mangledName, false, false, true);
			// for (auto n : tmp)
			// 	std::cerr << "[POST] Symbol: " << n->getMangledName() << " is a function: " << n->isFunction() << std::endl;

			// for (auto i : _loadedLibraries) {
			// 	BPatch_object * obj = i.second;
			// 	std::vector<Symbol *> tmp;
			// 	Dyninst::SymtabAPI::Symtab * symt = Dyninst::SymtabAPI::convert(obj);
			// 	symt->getAllUndefinedSymbols(tmp);
			// 	instLibSymbols[i.first] = tmp;
			// }			
			// std::cerr << "Symbol is a function " << storedSymbol->isFunction() << std::endl;
		}
		print = false;
	}
	_insertedInstrimentation =  true;
}

bool ProcessController::LoadWrapperLibrary(std::string libname) {
	std::cerr << "[PROCCTR] Loading library " << libname << " into address space\n";
	BPatch_object * tmp;
	tmp = _appProc->loadLibrary(libname.c_str());
	if(tmp == NULL) {
		return false;
	}
	_loadedLibraries[libname] = tmp;
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

extern "C" void DYNINST_LibraryLoadCallback(BPatch_thread * thread, BPatch_object * obj, bool l) {
	std::cerr << "[PROCCTR] In Load library callback" << std::endl;
	curController->LibraryLoadCallback(thread, obj, l);
}

void ProcessController::LibraryLoadCallback(BPatch_thread * thread, BPatch_object * obj, bool l) {
	BPatch_process* appProc = dynamic_cast<BPatch_process*>(_addrSpace);
	if (_insertedInstrimentation == true)
		return;
	BPatch_image *image = _addrSpace->getImage();
	BPatch_Vector<BPatch_module*> mods;
	image->getModules(mods);
	for (auto mod : mods) {
		char * name = (char *) malloc(500 * sizeof(char));
		name = mod->getName(name, 500);
		std::string tmp = std::string(name);
		std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
		if (tmp.find(std::string("libcuda.so")) != std::string::npos) {	
			std::cerr << "[PROCCTR] Inserting Instrimentation into libcuda.so" << std::endl;
			_insertedInstrimentation = true;
			std::set<std::string> libsToLoad = WrapperLibraries();
			for (auto i : libsToLoad)
				LoadWrapperLibrary(i);
			InstrimentApplication();
		}
	}
}

// bool ProcessController::InsertInstrimentation(std::string WrapperDef) {
// 	curController = this;
//     ReadDefinition(WrapperDef);
// 	//std::set<std::string> libsToLoad = WrapperLibraries();
// 	// Run application until libcuda is loaded. 
// 	bpatch.registerDynLibraryCallback((BPatchDynLibraryCallback)&DYNINST_LibraryLoadCallback);
// 	return true;
// 	//assert(LoadWrapperLibrary(std::string("libcuda.so.1")) != false);
// 	// for (auto i : libsToLoad)
// 	// 	LoadWrapperLibrary(i);
// 	// InstrimentApplication();
// }


bool ProcessController::InsertInstrimentation(std::string WrapperDef) {
	// Force libcuda to be loaded
	assert(LoadWrapperLibrary(std::string("libcuda.so.1")) != false);
	assert(LoadWrapperLibrary(std::string("/nobackup/spack_repo/opt/spack/linux-ubuntu16.04-x86_64/gcc-6.4.0/cudadedup-develop-mbsbiqg2zylptsgokmkjiehitydyfwtq/lib/libStubLib.so")) != false);
    ReadDefinition(WrapperDef);
	std::set<std::string> libsToLoad = WrapperLibraries();
	for (auto i : libsToLoad)
		LoadWrapperLibrary(i);
	InstrimentApplication();
}