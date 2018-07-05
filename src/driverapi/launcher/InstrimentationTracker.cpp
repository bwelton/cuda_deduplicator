#include "InstrimentationTracker.h"
#define INST_TRACKER_RECORD 1
InstrimentationTracker::InstrimentationTracker() : _logFile("IT_log.txt", std::ofstream::out | std::ofstream::app) {
	#ifdef INST_TRACKER_RECORD
	_recordInst.open("InstrimentationRecorder.txt", std::ofstream::out);
	#endif

	// Open File Exlusion lists
	// Grab Defaults 
	_loadStoreFuncSkips =  OpenAndParseExclusionFile(std::string(LOCAL_INSTALL_PATH) + std::string("/lib/LoadStoreFunctions.skip"));
	_loadStoreModSkips =  OpenAndParseExclusionFile(std::string(LOCAL_INSTALL_PATH) + std::string("/lib/LoadStoreModules.skip"));
	_callTracingFuncSkips =  OpenAndParseExclusionFile(std::string(LOCAL_INSTALL_PATH) + std::string("/lib/CallTracingFunctions.skip"));
	_callTracingModSkips =  OpenAndParseExclusionFile(std::string(LOCAL_INSTALL_PATH) + std::string("/lib/CallTracingModules.skip"));

	// Grab those that are local for this application.
	StringVector LSFunc = OpenAndParseExclusionFile(std::string("LoadStoreFunctions.skip"));
	StringVector LSMod = OpenAndParseExclusionFile(std::string("LoadStoreModules.skip"));
	StringVector CTFunc = OpenAndParseExclusionFile(std::string("CallTracingFunctions.skip"));
	StringVector CTMod = OpenAndParseExclusionFile(std::string("CallTracingModules.skip"));

	// Concate defaults with application specific skips.
	_loadStoreFuncSkips.insert(_loadStoreFuncSkips.end(), LSFunc.begin(), LSFunc.end());
	_loadStoreModSkips.insert(_loadStoreModSkips.end(), LSMod.begin(), LSMod.end());
	_callTracingFuncSkips.insert(_callTracingFuncSkips.end(),CTFunc.begin(), CTFunc.end());
	_callTracingModSkips.insert(_callTracingModSkips.end(), CTMod.begin(), CTMod.end());

	for (auto & i : _callTracingModSkips) {
		std::transform(i.begin(), i.end(), i.begin(), ::tolower);
	}
	for (auto & i : _loadStoreModSkips) {
		std::transform(i.begin(), i.end(), i.begin(), ::tolower);
	}
}

StringVector InstrimentationTracker::OpenAndParseExclusionFile(std::string filename) {
	StringVector ret;
	std::ifstream t(filename.c_str(), std::ios::binary);
	if (!t.good()){
		std::cerr << "[InstrimentationTracker::OpenAndParseExclusionFile] Could not open excludes file: " << filename << std::endl;
		return std::vector<std::string>();
	}

	std::string line;
	while (std::getline(t, line)) {
		if (line.at(0) == '#' || line.at(0) == '\n' || line.size() < 2)
			continue;
		if (line.find('\n') != std::string::npos)
			line.erase(line.find('n'), 1);
		ret.push_back(line);
	}
	return ret;
}


void InstrimentationTracker::RecordInstrimentation(InstType t, BPatch_function * func, std::vector<BPatch_point *> * points) {
#ifdef INST_TRACKER_RECORD
	for(auto i : *points)
		RecordInstrimentation(t, func, i);
#endif
	_recordInst.flush();
}

void InstrimentationTracker::RecordInstrimentation(InstType t, BPatch_function * func, BPatch_point * point) {
#ifdef INST_TRACKER_RECORD
	_recordInst << int(t) << "$" <<  func->getModule()->getObject()->pathName() << "$" << (uint64_t)point->getAddress() << std::endl;
#endif
}

void InstrimentationTracker::AddAlreadyInstrimented(std::vector<std::string> & wrappedFunctions) {
	//_prevWrappedFunctions = wrappedFunctions;
}
bool InstrimentationTracker::ShouldInstriment(BPatch_function * func, std::vector<BPatch_point *> * points, InstType t) {
	if (!ShouldInstrimentFunciton(func, t) || !ShouldInstrimentModule(func, t)){
		_logFile << "[InstrimentationTracker] We are rejecting function " << func->getName() <<  " because module/function is labeled as uninstrimentable" << std::endl;
		if (!ShouldInstrimentModule(func, t))
			_logFile << "[InstrimentationTracker]\tRejected because module is set to skip" << std::endl;
		if (!ShouldInstrimentFunciton(func, t))
			_logFile << "[InstrimentationTracker]\tRejected because function is set to skip" << std::endl;
		return false;
	}
	
	if (_alreadyInstrimented.find(t) == _alreadyInstrimented.end())
		_alreadyInstrimented[t] = std::set<uint64_t>();
	std::string pathName = func->getModule()->getObject()->pathName();
	std::set<uint64_t> removeList;

	for (int i = 0; i < points->size(); i++) {
		if ((*points)[i]->getCalledFunction() != NULL) {
			if (ShouldInstrimentPoint((*points)[i]->getCalledFunction(), t) == false){
				removeList.insert(i);
			} else {
				//std::cerr << "Instrumenting function call - " << (*points)[i]->getCalledFunction()->getName() << "@" << std::hex << (uint64_t)(*points)[i]->getAddress() << std::dec <<std::endl;
			}
		}
		uint64_t hashValue = HashPoint(func, (*points)[i]);
		if (_alreadyInstrimented[t].find(hashValue) != _alreadyInstrimented[t].end())
			removeList.insert(i);
		else 
			_alreadyInstrimented[t].insert(hashValue);
	}
	std::vector<BPatch_point *> tmpPoints = *points;
	points->clear();
	for (int i = 0; i < tmpPoints.size(); i++) {
		if (removeList.find(i) == removeList.end())
			points->push_back(tmpPoints[i]);
	}
	if (points->size() == 0) 
		return false;
	return true;
}

uint64_t InstrimentationTracker::HashPoint(BPatch_function * func, BPatch_point * point) {
	std::stringstream ss;
	ss << func->getModule()->getObject()->pathName() << "," << (uint64_t)point->getAddress();
	return std::hash<std::string>()(ss.str());
}

bool InstrimentationTracker::ShouldInstrimentPoint(BPatch_function * func, InstType t) {
	static StringVector callTracingInstSkips  = {"__stack_chk_fail", "_Unwind_Resume"};
	static StringVector loadStoreInstSkips = {"EMPTY_VECTOR_DONT"};
    StringVector * toSkip;
    if (t == LOAD_STORE_INST)
    	toSkip = &loadStoreInstSkips;
    else
    	toSkip = &callTracingInstSkips;	
    std::string funcName = func->getName();
    for (auto i : *toSkip) {
    	if (funcName.find(i) != std::string::npos)
    		return false;
    }
    return true;
}

bool InstrimentationTracker::ShouldInstrimentFunciton(BPatch_function * func, InstType t) {
//	static StringVector callTracingSkips  = {"dyninst","Dyninst","main","___stack_chk_fail","__run_exit_handlers","exit","libc","__GI_"," __malloc","abort","__random","__stack_chk_fail","deregister_tm_clones","register_tm_clones","backtrace_and_maps","__GI__IO_unsave_markers","_IO_setb","__GI___mempcpy","__munmap","__GI___twalk","__GI__IO_adjust_column"};
	// static StringVector loadStoreSkips =  {"_fini","atexit","main", "dyninst", "boost","pthread", "clock","timer","__aio_",
	// "__libc_csu_init", "__libc_csu_fini","malloc","printf","fwrite","strlen","abort","assert","strnlen","new_heap","fflush",
	// "__static_initialization_and_destruction_0","_start", "__GI___backtrace","__GI___libc_secure_getenv","__GI_exit","cudart","_IO_puts","__new_fopen","fopen","_Unwind_Resume","__run_exit_handlers","free","open",
	// "_init", "cudart::cuosInitializeCriticalSection","cudart::", "cudaLaunch","__timer","pthread","elf","dwarf",
	// "cudart::cuosInitializeCriticalSectionShared","cudart::cuosMalloc", "basic_ostringstream","basic_istringstream",
	// "cudart::cuosInitializeCriticalSectionWithSharedFlag","cudaLaunch","dim3::dim3","std::num_get","std::time_get",
	// "__printf","__GI_fprintf","_IO_vfprintf_internal","buffered_vfprintf","printf_positional","__printf_fp","__printf_fphex","__fxprintf","__GI___printf_fp_l","vfwprintf","__GI___asprintf","buffered_vfprintf","printf_positional","_IO_vasprintf","__snprintf","vsnprintf",
    // "__GI___libc_malloc","_int_malloc","__malloc_assert","malloc_consolidate","sysmalloc","malloc_printerr", "cudaHostGetDevicePointer", "cudaHostGetFlags"};

    StringVector * toSkip;
    if (t == LOAD_STORE_INST)
    	toSkip = &_loadStoreFuncSkips;
    else
    	toSkip = &_callTracingFuncSkips;
    std::string funcName = func->getName();
    for (auto i : *toSkip) {
    	if (funcName.find(i) != std::string::npos)
    		return false;
    }
    if (t == LOAD_STORE_INST)
	    for (auto i : _prevWrappedFunctions) {
	    	if (funcName.find(i) != std::string::npos)
	    		return false;
	    }
	// if (t == LOAD_STORE_INST){
	// 	if (func->getMangledName().find("_ZN6SAMRAI4algs25HyperbolicLevelIntegrator37coarsenDataForRichardsonExtrapolationERKSt10shared_ptrINS_4hier14PatchHierarchyEEiRKS2_INS3_10PatchLevelEEdb") == std::string::npos)
	// 		return false;
	// }
    return true;
}

bool InstrimentationTracker::ShouldInstrimentModule(BPatch_function * func, InstType t) {
	//static StringVector loadStoreModSkips = {"libicui18n","libnvtoolsext","libgfortran","libnvidia-fatbinaryloader","libxlsmp","nvidia-384","libc","libmpi","liblzma","libxerces","libunwind.so","gettext","libxml2","openmpi","libgcc_s","libstdc++","pthread","elf","dwarf","boost","libcuda","boost","Dyninst", "dyninst", "cudadedup","libcudnn.so","libaccinj64.so","libcublas.so","libcudart.so","libcufft.so","libcufftw.so","libcuinj64.so","libcurand.so","libcusolver.so","libcusparse.so","libnppc.so","libnppial.so","libnppicc.so","libnppicom.so","libnppidei.so","libnppif.so","libnppig.so","libnppim.so","libnppist.so","libnppisu.so","libnppitc.so","libnpps.so","libnvblas.so","libnvgraph.so","libnvrtc-builtins.so","libnvrtc.so","libdl-2.23.so","libpthread-2.23.so", "cudadedup", "libcuda.so","libcuptieventhandler.so","libecho.so","libsynchtool.so","libtimecall.so","libtransfertimeline.so","libstublib.so", "dyninst", "dyninst", "libdriverapiwrapper", "libgotcha", "cudadedup"};
	//static StringVector callTracingModSkips = {"libc.so","ld-linux-x86-64","libgcc_s.so","libstdc++.so", "libdl.so", "libpthread.so", "cudadedup", "libdl-2.23.so","dyninst","dyninst","boost", "libc.so", "linux-vdso.so", "libpthread-2.23.so","libcuptieventhandler.so","libecho.so","libsynchtool.so","libtimecall.so","libtransfertimeline.so","libstublib.so", "dyninst","Dyninst", "libdriverapiwrapper", "libgotcha", "cudadedup"};
    StringVector * toSkip;
    if (t == LOAD_STORE_INST)
    	toSkip = &_loadStoreModSkips;
    else
    	toSkip = &_callTracingModSkips;
    std::string modname = func->getModule()->getObject()->pathName();
    std::transform(modname.begin(), modname.end(), modname.begin(), ::tolower);
    for (auto i : *toSkip) {
    	if (modname.find(i) != std::string::npos)
    		return false;
    	//if (modname.find("libcuda.so") == std::string::npos)
    	//	return false;
    }
    // if (t == LOAD_STORE_INST){
    // 	if (modname.find("stencil") != std::string::npos)
    // 		return true;
    // 	return false;
    // }
    return true;
}
