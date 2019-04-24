#include <iostream>
#include <fstream>    
#include <string>
#include <map>
// CUDA include
#include <cuda.h>
extern "C" {
cudaError_t  DIOGENES_cudaFreeWrapper(void * mem) {
	std::cerr << "I am freeing an address of .... " << std::hex << (uint64_t) mem << std::endl;
	return cudaFree(mem);
}

cudaError_t DIOGENES_cudaMallocWrapper(void ** mem, size_t size) {
	cudaError_t tmp = cudaMalloc(mem, size);
	if (tmp == cudaSuccess)
		std::cerr << "I alloced an address at " << std::hex << *((uint64_t**)mem)  <<  " of size " << size << std::endl;
	return tmp;
}

cudaError_t DIOGENES_cudaMemcpyAsyncWrapper(void * dst, const void * src, size_t size, cudaMemcpyKind kind, cudaStream_t stream) {
	std::cerr << "Initiating a transfer between  " << std::hex << dst <<  " and " << std::hex << src << " of size " << size << std::endl;
	return cudaMemcpyAsync(dst, src, size, kind, stream);
}
}

