#include <iostream>
#include <fstream>    
#include <string>
#include <stdio.h> 
#include <map>
// CUDA include
#include <cuda_runtime_api.h>
#include <cuda.h>
extern "C" {
cudaError_t  DIOGENES_cudaFreeWrapper(void * mem) {
	fprintf(stderr,"I am freeing an address of %p \n", mem);
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

void * DIOGENES_MALLOCWrapper(size_t size){
	void * tmp = malloc(size);
	std::cerr << "Malloced data at  " << std::hex << tmp << " of size " << size << std::endl;
	return tmp;
}
}

