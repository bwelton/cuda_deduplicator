#pragma once
#define BOOST_TEST_DYN_LINK
#include <cuda_runtime_api.h>
#include <cuda.h>
#include <boost/test/unit_test.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <sys/wait.h>
#include <stdio.h>
#include <memory>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <fstream>
#include <streambuf>
#include <utility>
#include <tuple>
#include <iostream>
typedef boost::function<void(void)> ActionCall;

void RedirectOutputToFile() {
	remove("test_output.txt");
	freopen("test_output.txt","w",stdout);
	dup2(fileno(stdout), fileno(stderr));
}

// Create random data
void * GenRandom(size_t bcount) {
	void * d = (void *) malloc(bcount);
	for (int x = 0; x < bcount; x++){
		((char *)d)[x] = (char)(rand() % 256);
	}
	return d;
}

#define CheckGPUResult(ans) { gpuAssertion((ans), __FILE__, __LINE__); }
inline void gpuAssertion(cudaError_t ecode, const char *file, int line)
{
   if (ecode != cudaSuccess) 
   {
      fprintf(stderr,"GPUassert: %s %s %d\n", cudaGetErrorString(ecode), file, line);
      exit(ecode);
   }
}

struct CudaCtx
{
	cudaStream_t _stream;
	CudaCtx() {
		CheckGPUResult(cudaStreamCreate(&_stream));
	}
	~CudaCtx() {
		cudaStreamDestroy(_stream);
	}
	cudaStream_t GetStream() {
		return _stream;
	}

	void SynchronizeStream() {
		CheckGPUResult(cudaStreamSynchronize(_stream));
	}
};

template <typename T> 
struct DeviceMemory 
{
	T * store;
	size_t _size;
	T * _cpuStore;
	DeviceMemory(size_t size) {
		CheckGPUResult(cudaMalloc((void **)&store, size * sizeof(T)));
		_size = size;
		_cpuStore = (T*) GenRandom(size * sizeof(T));
	}
	~DeviceMemory() {
		cudaFree(store);
		free(_cpuStore);
	}

	void ReadAsync(std::shared_ptr<CudaCtx> ctx) {
		CheckGPUResult(cudaMemcpyAsync(_cpuStore, store, _size * sizeof(T), cudaMemcpyDeviceToHost, ctx.get()->GetStream()));
	}

	void WriteAsync(std::shared_ptr<CudaCtx> ctx) {
		CheckGPUResult(cudaMemcpyAsync(store, _cpuStore, _size * sizeof(T), cudaMemcpyHostToDevice, ctx.get()->GetStream()));		
	}

	void ReadSync() {
		CheckGPUResult(cudaMemcpy(_cpuStore, store, _size * sizeof(T), cudaMemcpyDeviceToHost));	
	}

	void WriteSync() {
		CheckGPUResult(cudaMemcpy(store, _cpuStore, _size * sizeof(T), cudaMemcpyHostToDevice));			
	}

	bool CompareDevToCPU() {
		T * local_cache = (T*) malloc(_size * sizeof(T));
		memcpy(local_cache, _cpuStore, _size * sizeof(T));
		ReadSync();
		int ret = memcmp(local_cache, _cpuStore, _size * sizeof(T));
		free(local_cache);
		if (ret != 0)
			return false;
		return true;
	}

};

struct TestingFixture {
		TestingFixture() {
			remove("dedup_out.txt");
		}
		int LaunchAndWait(ActionCall a) {
			pid_t child_pid = fork();
			if (child_pid == 0){
				// Child process, perform action then exit
				a();
				exit(0);
			} else {
				pid_t tpid = 0;
				int status = 1;
				while (tpid != child_pid) {
					tpid = wait(&status);
					if(tpid != child_pid) {
						BOOST_FAIL("Could not wait on child process, fork may not be functional on this machine");
					}
				}
				BOOST_CHECK(status == 0);
				return status;
			}
			return -1;
		}

		~TestingFixture() {
			remove("dedup_out.txt");
		}
};

