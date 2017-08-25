#pragma ONCE
#include <boost/preprocessor/array/enum.hpp>
#include "deduplicator.h"

#ifdef ENABLE_STACKTRACING
#include "strace.h"
#endif 


struct CudaTimers {
	cudaEvent_t start, stop;
	CudaTimers() {
		cudaEventCreate(&start);
		cudaEventCreate(&stop);
	}
	void StartTimer(cudaStream_t s) {
		cudaEventRecord(start, s);
	}
	void EndTimer(cudaStream_t s) {
		cudaEventRecord(stop, s);
	}
	float GetTime() {
		float ret = 0.0;
		cudaEventSynchronize(stop);
		cudaEventElapsedTime(&ret, start, stop);
		return ret;
	}
}; 

extern thread_local std::shared_ptr<CudaTimers> CudaTime;
#define BUILD_TIMER_CLASS \
	if (CudaTime.get() == NULL) { \
		fprintf(stderr, "%s\n", "Setting up our global data structure"); \
		CudaTime.reset(new CudaTimers()); \
	} 

#define TIMER_PTR CudaTime.get()

#define TIMING_WRAPPER 