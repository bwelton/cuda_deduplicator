#include "InstrimentationTracker.h"
InstrimentationTracker::InstrimentationTracker() {
}

void InstrimentationTracker::AddAlreadyInstrimented(std::vector<std::string> & wrappedFunctions) {
	//_prevWrappedFunctions = wrappedFunctions;
}
bool InstrimentationTracker::ShouldInstriment(BPatch_function * func, std::vector<BPatch_point *> * points, InstType t) {
	if (!ShouldInstrimentFunciton(func, t) || !ShouldInstrimentModule(func, t))
		return false;
	
	if (_alreadyInstrimented.find(t) == _alreadyInstrimented.end())
		_alreadyInstrimented[t] = std::set<uint64_t>();
	std::string pathName = func->getModule()->getObject()->pathName();
	std::set<uint64_t> removeList;

	for (int i = 0; i < points->size(); i++) {
		if ((*points)[i]->getCalledFunction() != NULL) {
			if (ShouldInstrimentPoint((*points)[i]->getCalledFunction(), t) == false){
				std::cerr << "Found a funciton we shouldn't instriment!" << std::endl;
				removeList.insert(i);
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
	static StringVector callTracingInstSkips  = {"___stack_chk_fail", "_Unwind_Resume"};
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
	static StringVector callTracingSkips  = {"main","dyninst","Dyninst","___stack_chk_fail","targ130a20","targ130a30", "targ2c21f0","targ2c2550","__run_exit_handlers","exit","libc","__GI_"," __malloc","abort","__random","__stack_chk_fail","deregister_tm_clones","register_tm_clones","backtrace_and_maps","__GI__IO_unsave_markers","_IO_setb","__GI___mempcpy","__munmap","__GI___twalk","__GI__IO_adjust_column"};
	static StringVector loadStoreSkips =  {"_fini","atexit","main", "dyninst", "boost","pthread", "clock","timer","__aio_",
	"__libc_csu_init", "__libc_csu_fini","malloc","printf","fwrite","strlen","abort","assert","strnlen","new_heap","fflush",
	"__static_initialization_and_destruction_0","_start", "__GI___backtrace","__GI___libc_secure_getenv","__GI_exit","cudart","_IO_puts","__new_fopen","fopen","_Unwind_Resume","__run_exit_handlers","free","open",
	"_init", "cudart::cuosInitializeCriticalSection","cudart::", "cudaLaunch","__timer","pthread","elf","dwarf",
	"cudart::cuosInitializeCriticalSectionShared","cudart::cuosMalloc", "basic_ostringstream","basic_istringstream",
	"cudart::cuosInitializeCriticalSectionWithSharedFlag","cudaLaunch","dim3::dim3","std::num_get","std::time_get",
	"__printf","__GI_fprintf","_IO_vfprintf_internal","buffered_vfprintf","printf_positional","__printf_fp","__printf_fphex","__fxprintf","__GI___printf_fp_l","vfwprintf","__GI___asprintf","buffered_vfprintf","printf_positional","_IO_vasprintf","__snprintf","vsnprintf",
    "__GI___libc_malloc","_int_malloc","__malloc_assert","malloc_consolidate","sysmalloc","malloc_printerr"};

    StringVector * toSkip;
    if (t == LOAD_STORE_INST)
    	toSkip = &loadStoreSkips;
    else
    	toSkip = &callTracingSkips;
    std::string funcName = func->getName();
    for (auto i : *toSkip) {
    	if (funcName.find(i) != std::string::npos)
    		return false;
    }
    for (auto i : _prevWrappedFunctions) {
    	if (funcName.find(i) != std::string::npos)
    		return false;
    }
    return true;
}

bool InstrimentationTracker::ShouldInstrimentModule(BPatch_function * func, InstType t) {
	static StringVector loadStoreModSkips = {"libc","pthread","elf","dwarf","boost","libcuda","boost","Dyninst", "dyninst", "cudadedup","libcudnn.so","libaccinj64.so","libcublas.so","libcudart.so","libcufft.so","libcufftw.so","libcuinj64.so","libcurand.so","libcusolver.so","libcusparse.so","libnppc.so","libnppial.so","libnppicc.so","libnppicom.so","libnppidei.so","libnppif.so","libnppig.so","libnppim.so","libnppist.so","libnppisu.so","libnppitc.so","libnpps.so","libnvblas.so","libnvgraph.so","libnvrtc-builtins.so","libnvrtc.so","libdl-2.23.so","libpthread-2.23.so", "cudadedup", "libcuda.so","libcuptieventhandler.so","libecho.so","libsynchtool.so","libtimecall.so","libtransfertimeline.so","libstublib.so", "dyninst", "dyninst"};
	static StringVector callTracingModSkips = {"libc","ld-linux-x86-64","libgcc_s.so","libstdc++.so", "libdl.so", "libpthread.so", "cudadedup", "libdl-2.23.so","dyninst","dyninst","boost", "libc.so", "linux-vdso.so", "libpthread-2.23.so","libcuptieventhandler.so","libecho.so","libsynchtool.so","libtimecall.so","libtransfertimeline.so","libstublib.so", "dyninst","Dyninst"};
    StringVector * toSkip;
    if (t == LOAD_STORE_INST)
    	toSkip = &loadStoreModSkips;
    else
    	toSkip = &callTracingModSkips;
    std::string modname = func->getModule()->getObject()->pathName();
    std::transform(modname.begin(), modname.end(), modname.begin(), ::tolower);
    for (auto i : *toSkip) {
    	if (modname.find(i) != std::string::npos)
    		return false;
    	//if (modname.find("libcuda.so") == std::string::npos)
    	//	return false;
    }
    return true;
}
