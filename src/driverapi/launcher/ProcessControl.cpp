#include "ProcessControl.h"
static BPatch bpatch;
static ProcessController * curController;
ProcessController::ProcessController(boost::program_options::variables_map vm, LogInfo * log) :
	_vm(vm), _launched(false), _insertedInstrimentation(false), _terminated(false), _log(log) {
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
		_log->Write(std::string("[PROCCTR] Launch Arguments - ") + std::string(argv[i]));

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

std::map<uint64_t, std::vector<StackPoint> > ProcessController::GetThreadStacks() {
	std::map<uint64_t, std::vector<StackPoint> > ret;
	BPatch_Vector<BPatch_thread *> threads;
	_appProc->getThreads(threads);
	for(auto i : threads){
		BPatch_Vector<BPatch_frame> frames;
		i->getCallStack(frames);
		uint64_t threadTid = i->getTid();
		for (auto frame : frames) {
			StackPoint sp;
			BPatch_function * func = frame.findFunction();
			BPatch_point * point = frame.getPoint();
			if (func == NULL && point == NULL) {
				sp.empty = true;
			} else if (func == NULL && point != NULL) {
				sp.framePtr = (uint64_t)point->getAddress();
	   		    sp.empty = false;
			} else {
				sp.fname = func->getName();
				// Get the symbol for the source line.
				BPatch_module * funcMod = func->getModule();
				if (funcMod != NULL){
					sp.libOffset = (uint64_t) frame.getPC() - (uint64_t) funcMod->getBaseAddr();
				}
				sp.framePtr = (uint64_t)frame.getPC();
				assert(func->getModule() != NULL);
				const char * libname = func->getModule()->libraryName();
				if (libname != NULL)
					sp.libname = std::string(libname);
				sp.empty = false;
			}
			ret[threadTid].push_back(sp);
		}
	}
	return ret;
}

BPatch_addressSpace * ProcessController::LaunchProcessInstrimenter(std::string WrapperDef) {
	assert(1 == 0);
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
		_log->Write(std::string("[PROCCTR] Could not write output binary"));

		exit(-1);
	}

	// Setup arguments
	char ** argv = (char**)malloc(progName.size() * sizeof(char *)+1);
	for (int i = 0; i < progName.size(); i++) 
		argv[i] = strdup(progName[i].c_str());

	argv[progName.size()] = NULL;
	for (int i = 0; i < progName.size(); i++)
		_log->Write(std::string("[PROCCTR] Launch Arguments - ") + std::string(argv[i]));
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

bool InRegionCheck(std::vector<BPatch_object::Region> & regions, void * addr) {
	for (auto i : regions) {
		if ((uint64_t)addr > (uint64_t)i.base && (uint64_t)addr < ((uint64_t)i.base + i.size))
			return true;
	}
	return false;
}

void ProcessController::InsertLoadStores() {
	// BPatch_effectiveAddressExpr,BPatch_originalAddressExpr, 
	// assert(LoadWrapperLibrary(std::string(LOCAL_INSTALL_PATH) + std::string("/lib/plugins/libSynchTool.so")) != false);
	//_appProc->stopExecution();
	std::vector<BPatch_snippet*> recordArgs;
	std::vector<BPatch_function *> all_functions;
	std::vector<BPatch_function *> callFunc;
	std::vector<BPatch_point*> points; 

	BPatch_image * img = _addrSpace->getImage();
	BPatch_snippet * loadAddr = new BPatch_effectiveAddressExpr();
	BPatch_snippet * instAddr = new BPatch_originalAddressExpr();

	recordArgs.push_back(loadAddr);
	recordArgs.push_back(instAddr);

	img->findFunction("SYNC_RECORD_MEM_ACCESS", callFunc);
	assert(callFunc.size() > 0);

	BPatch_funcCallExpr recordAddrCall(*(callFunc[0]), recordArgs);
	
	img->getProcedures(all_functions);

	std::set<BPatch_opCode> axs;
	axs.insert(BPatch_opLoad);
	axs.insert(BPatch_opStore);

	// Get all the objects.
	std::vector<BPatch_object *> imgObjects;
	std::vector<BPatch_object::Region> skipRegions;
	img->getObjects(imgObjects);
	for (auto x : imgObjects) {
		std::string libname = x->name();
		std::string pathname = x->pathName();
		std::transform(libname.begin(), libname.end(), libname.begin(), ::tolower);
		std::transform(pathname.begin(), pathname.end(), pathname.begin(), ::tolower);

		if (libname.find("cuda_deduplicator") != std::string::npos ||
			libname.find("libcuda.so") != std::string::npos ||
			libname.find("dyninst") != std::string::npos ||
			libname.find("libdriverapiwrapper.so") != std::string::npos ||
			pathname.find("cuda_deduplicator") != std::string::npos ||
			pathname.find("libcuda.so") != std::string::npos ||
			pathname.find("dyninst") != std::string::npos ||
			pathname.find("libdriverapiwrapper.so") != std::string::npos) {
				std::vector<BPatch_object::Region> tmpRegion;
				x->regions(tmpRegion);
				skipRegions.insert(skipRegions.end(), tmpRegion.begin(), tmpRegion.end());
			}
	}

	for (auto x : all_functions) {
		if (InRegionCheck(skipRegions, x->getBaseAddr())){
			std::cerr << "Function passed for Instrimentation: " << x->getName() << std::endl;
			continue;
		}
		std::vector<BPatch_point*> * tmp = x->findPoint(axs);
		points.insert(points.end(), tmp->begin(), tmp->end());
		std::cerr << "Inserting Load/Store Instrimentation into : " << x->getName() << std::endl;
		if (points.size() >= 1)
			assert(_addrSpace->insertSnippet(recordAddrCall,points));
		points.clear();
	}

	// for (auto x : local_mods) {
	// 	std::string libname;
	// 	if(x->libraryName() == NULL) 
	// 		libname = std::string("");
	// 	else
	// 		libname = std::string(x->libraryName());
	// 	bool noInst = false;
	// 	for (auto y : _loadedLibraries) {
			// if (y.first.find(libname) != std::string::npos ||
			// 	libname.find("cuda_deduplicator") != std::string::npos ||
			// 	libname.find("libcuda.so") != std::string::npos ||
			// 	libname.find("dyninst") != std::string::npos ||
			// 	libname.find("libDriverAPIWrapper.so") != std::string::npos){
	// 			noInst = true;
	// 			break;
	// 		} 
	// 	}
	// 	if (noInst)
	// 		continue;
	// 	std::cerr << "Inserting Load/Store Instrimentation into Module : " << libname << std::endl;

	// 	std::vector<BPatch_function *> inst_funcs;


	// 	x->getProcedures(inst_funcs);

	// 	// Gather the set of points to instrument 
	// 	for (auto y : inst_funcs) {
	// 		std::cerr << "Inserting Load/Store Instrimentation into : " << y->getName() << std::endl;
	// 		std::vector<BPatch_point*> * tmp = y->findPoint(axs);
	// 		points.insert(points.end(), tmp->begin(), tmp->end());
	// 	}
	// }
	// if (points.size() >= 1)
	// 	assert(_addrSpace->insertSnippet(recordAddrCall,points));
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
	    	_log->Write(std::string("Token size is not 5 in wrapper def.... skipping this function"));
	    	_log->Write(std::string("Line skipped: ") + line);
	    } else {
	    	_log->Write(std::string("Inserting Instrimentation Into: ") + line);
	    	std::transform(tokens[0].begin(), tokens[0].end(), tokens[0].begin(), ::tolower);
	    	_wrapFunctions.push_back(std::make_tuple(tokens[0],tokens[1],tokens[2],tokens[3], tokens[4]));
	    }
	}
}

void ProcessController::InsertWrapperDef(std::string type, std::string origName, std::string wrapperFunc, std::string lib, std::string origSymbol) {
	_wrapFunctions.push_back(std::make_tuple(type, origName, wrapperFunc, lib, origSymbol));
}

std::vector<BPatch_function *> findFuncByName(BPatch_image * appImage, const char * funcName, LogInfo * _log) {
  std::stringstream ss;
  /* fundFunctions returns a list of all functions with the name 'funcName' in the binary */
  BPatch_Vector<BPatch_function * >funcs;
  if (NULL == appImage->findFunction(funcName, funcs) || !funcs.size() || NULL == funcs[0])
  {
      std::cerr << "Failed to find " << funcName <<" function in the instrumentation library" << std::endl;
      return std::vector<BPatch_function *>();
  }
  ss << "Found " << funcName << " this many times " << funcs.size();
  _log->Write(ss.str());
  ss.clear();
  if (funcs.size() > 1) {
    for(int i = 0; i < funcs.size(); i++ )
    {
       ss << "    " << funcs[i]->getName();
       _log->Write(ss.str());
       ss.clear();
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
		instLibSymbols[i.first].insert(instLibSymbols[i.first].end(),tmp.begin(),tmp.end());
	}
	std::stringstream ss;
	for (auto i : _wrapFunctions) {
		totalFunctions += 1;
		if (std::get<0>(i).find("wrap") == std::string::npos)
			continue;
		BPatch_Vector<BPatch_function *> orig;
		if (std::get<1>(i).find("0x") ==  std::string::npos)
			orig = findFuncByName(img,std::get<1>(i).c_str(), _log);
		else {
			// This is an offset.....
			// We must:
			// 1. Convert the offset to an uint.
			uint64_t offset = uint64_t(std::stoull(std::get<1>(i),0,16));
			Dyninst::Address offsetAddress = 0;
			bool foundCuda = false;
			for (auto obj : _loadedLibraries){
				if (obj.first.find(std::string("libcuda.so")) == std::string::npos)
					continue;
				// Potentially more stable method 
				std::vector<BPatch_module *> soModules;
				obj.second->modules(soModules);
				assert(soModules.size() == 1);
				offsetAddress = soModules[0]->getLoadAddr() + offset;


				// // We have found the cuda lib....
				// // Find the function by offset within that library
				// offsetAddress = obj.second->fileOffsetToAddr(offset);
				std::stringstream ss;
				ss << "Found offset for function " << offset << " at location " << offsetAddress;
				_log->Write(ss.str());
				assert(offsetAddress != 0);
				//break;
			}	
			_addrSpace->findFunctionsByAddr(offsetAddress, orig);
			std::stringstream ss;
			ss << "Found function " << std::get<1>(i) << " at location " << offsetAddress << " " << orig.size() << " number of times";
			_log->Write(ss.str());
			assert(orig.size() != 0);
		}
		//std::vector<BPatch_function *> * orig2 =  mod->findFunction(std::get<1>(i).c_str(), funcs, true, false, false, false);//findFuncByName(img,std::get<1>(i).c_str());
		//std::vector<BPatch_function *> orig = *orig2;		
		if (orig.size() == 0) {
			std::cerr << "[PROCCTR] Could not find function with name - " << std::get<1>(i) << std::endl;
			continue;
		}
		std::vector<BPatch_function *> wrapfunc = findFuncByName(img,std::get<2>(i).c_str(), _log);
		if (wrapfunc.size() == 0){
			std::cerr << "[PROCCTR] Could not find wrapper function - " << std::get<2>(i) << std::endl;
			continue;
		}
		
		// Find Hook Symbol	
		if (instLibSymbols.find(std::get<3>(i)) == instLibSymbols.end()) {
			assert(1 == 0);
			std::vector<Symbol *> tmp;
			Dyninst::SymtabAPI::Module *symtab =  Dyninst::SymtabAPI::convert(wrapfunc[0]->getModule());	
			instLibSymbols[std::get<3>(i)] = tmp;
		}

		ss << "Replacing " << orig[0]->getName() << " with " << wrapfunc[0]->getName() << " and new hook " << std::get<4>(i);
		_log->Write(ss.str());
		ss.clear();

		for (Symbol * sym : instLibSymbols[std::get<3>(i)]) {
			if (sym->getPrettyName() == std::string(std::get<4>(i))) {
				uint64_t ptr;
				BPatch_object * obj = _loadedLibraries[std::get<3>(i)];
				Dyninst::SymtabAPI::Symtab * symt = Dyninst::SymtabAPI::convert(obj);

				if (_addrSpace->wrapFunction(orig[0], wrapfunc[0], sym) == true){
					ss << "Function " << orig[0]->getName() << " wrapped successful";
					_log->Write(ss.str());
					ss.clear();
					wrapCount += 1;
				} else {
					std::cerr << "[PROCCTR] Function " << orig[0]->getName() << " WRAPPING FAILED" << std::endl;	
					ss << "Function " << orig[0]->getName() << " WRAPPING FAILED" << std::endl;	
					_log->Write(ss.str());
					ss.clear();
				}
				break;
			}
		}
	}
	_insertedInstrimentation =  true;
}

void ProcessController::InsertBreakpoints(std::vector<std::string> functionNames) {
	BPatch_image * img = _addrSpace->getImage();
	BPatch_breakPointExpr bp;
	BPatch_Vector<BPatch_point *> points;
	for (auto i : functionNames) {
		std::vector<BPatch_function *> wrapfunc; //= findFuncByName(img,i.c_str(), _log);
		std::cerr << "Searching for breakpoint function " << i << std::endl; 
		for (auto z : _loadedLibraries) {
			z.second->findFunction(i, wrapfunc, false);
			std::cerr << "Searching object: " << z.second->name() << std::endl;
			if (wrapfunc.size() > 0) 
				break;
		}
		assert(wrapfunc.size() != 0);
		BPatch_Vector<BPatch_point *> * entry_points;
		entry_points = wrapfunc[0]->findPoint(BPatch_entry);
		std::stringstream ss;
		ss << "Inserting breakpoint at function: " << i;
		_log->Write(ss.str());
		points.insert(points.end(), entry_points->begin(), entry_points->end());
	}	
	if(!_addrSpace->insertSnippet(bp, points)) {
		fprintf(stderr, "%s\n", "InsertFailed");
		exit(-1);
	}
}

bool ProcessController::LoadWrapperLibrary(std::string libname) {
	_log->Write(std::string("Loading library ") + libname + std::string(" into address space"));
	BPatch_object * tmp;
	tmp = _appProc->loadLibrary(libname.c_str());
	if(tmp == NULL) {
		std::cerr << "[PROCCTR] Failed to load library - " << libname << " into address space!" << std::endl;
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

bool ProcessController::InsertInstrimentation(std::string WrapperDef) {
	// Force libcuda to be loaded
	assert(LoadWrapperLibrary(std::string("libcuda.so.1")) != false);
	assert(LoadWrapperLibrary(std::string(LOCAL_INSTALL_PATH) + std::string("/lib/libStubLib.so")) != false);
	if (WrapperDef != std::string(""))
    	ReadDefinition(WrapperDef);

	std::set<std::string> libsToLoad = WrapperLibraries();
	for (auto i : libsToLoad)
		LoadWrapperLibrary(i);
	InstrimentApplication();
}