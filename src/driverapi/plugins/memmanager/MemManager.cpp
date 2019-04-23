#include <iostream>
#include <fstream>    
#include <string>
#include <map>
// CUDA include
#include <cuda.h>

CUresult cudaMemFreeWrapper(CUdeviceptr mem) {
	std::cerr << "I am freeing an address of .... " << std::hex << (uint64_t) mem << std::endl;
	return cuMemFree(mem);
}

