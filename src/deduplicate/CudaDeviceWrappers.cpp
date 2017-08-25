#include "CudaWrapper.h"
#include "WrapperMacros.h"
#undef BOOST_PP_ARRAY_ENUM
#undef BOOST_PREPROCESSOR_ARRAY_ENUM_HPP
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/array/elem.hpp>
#include <boost/preprocessor/array/enum.hpp>
thread_local std::shared_ptr<CudaTimers> CudaTime;
extern boost::recursive_mutex _log_mtx;

// Device Driver API
extern "C" {
DataStruct HostToDeviceDedup(void * dst, void * src, size_t bytecount, bool blocking = false, CUstream cudaStream = 0) {
	DataStruct transfer;
	transfer.storePTR = src;
	transfer.destPtr = dst;
	transfer.size = bytecount;
	transfer.stream = (cudaStream_t)cudaStream;
	transfer.blocking = blocking;
	transfer = STORAGE_PTR->DeduplicateData(transfer);
	return transfer;
}

void DeviceToHostDedup(void * dst, void * src, size_t bytecount, bool blocking = false, CUstream cudaStream = 0) {
	// UNSUPPORTED
	assert("UNSUPPORTED FEATURE: Device To Host Deduplication" == 0);
}

void HostToDeviceDetect(float time, void * dst, void * src, size_t bytecount) {
	
#ifdef ENABLE_STACKTRACING
	STORAGE_PTR->TrackTransfer(0, bytecount, (char *)src, time, GenStackTrace());
#else 
	STORAGE_PTR->TrackTransfer(0, bytecount, (char *)src, time);
#endif
}

void DeviceToHostDetect(float time, void * dst, void * src, size_t bytecount) {
	// Destination is the host and that is the only place we can do the check
#ifdef ENABLE_STACKTRACING
	STORAGE_PTR->TrackTransfer(0, bytecount, (char*)dst, time, GenStackTrace());
#else
	STORAGE_PTR->TrackTransfer(0, bytecount, (char*)dst, time);
#endif

}


// Tracking Calls
UNSUPPORTED_CALL(cuMemcpy_detect, 3, int)
	STORAGE_PTR->LogOutput("cuMemcpy - Unified Addressing Not Supported for detect");
	return ret_value;
}

UNSUPPORTED_CALL(cuMemcpyAsync_detect, 4, int)
	STORAGE_PTR->LogOutput("cuMemcpyAsync - Unified Addressing Not Supported for detect");
	return ret_value;
}

UNSUPPORTED_CALL(cuMemcpyA2A_detect, 5, int)
	STORAGE_PTR->LogOutput("cuMemcpyArrayToArray - Host to Host Copy Skipped");
	return ret_value;
}

WRAP_SUPPORTED_CALL_TIME(cuMemcpyA2D_detect, 4, int) 
	TIMER_MACRO(cuMemcpyA2D_detect, 4, (cudaStream_t) 0, int);

	// c, the third parameter of this function, is the offset into src (b) to copy from.
	HostToDeviceDetect(TIMER_PTR->GetTime(), (void *)a, (void *)(((char *)b)+((size_t)c)) , (size_t)d);
	return ret_value;
}

WRAP_SUPPORTED_CALL_TIME(cuMemcpyA2H_detect, 4, int) 
	TIMER_MACRO(cuMemcpyA2H_detect, 4, (cudaStream_t) 0, int);

	DeviceToHostDetect(TIMER_PTR->GetTime(), (void *)a,(void *)(((char *)b)+((size_t)c)), (size_t)d);
	return ret_value;
}

WRAP_SUPPORTED_CALL_TIME(cuMemcpyA2HAsync_detect, 5, int)
	TIMER_MACRO(cuMemcpyA2HAsync_detect, 5, (cudaStream_t) e, int);

	DeviceToHostDetect(TIMER_PTR->GetTime(), (void *)a,(void *)(((char *)b)+((size_t)c)), (size_t)d);
	return ret_value;	
}

WRAP_SUPPORTED_CALL_TIME(cuMemcpyD2A_detect, 4, int)
	TIMER_MACRO(cuMemcpyD2A_detect, 4, (cudaStream_t) 0, int);
	DeviceToHostDetect(TIMER_PTR->GetTime(), (void *)(((char *)a)+((size_t)b)), (void*)a, (size_t)d);
	return ret_value;

}

UNSUPPORTED_CALL(cuMemcpyD2D_detect, 3, int)
	//int ret_value = CALL_UNDERLYING(cuMemcpyD2D_detect, VARARRAY(3));
	return ret_value;
}

UNSUPPORTED_CALL(cuMemcpyD2DAsync_detect, 4, int)
	//int ret_value = CALL_UNDERLYING(cuMemcpyD2DAsync_detect, VARARRAY(4));
	return ret_value;
}

WRAP_SUPPORTED_CALL_TIME(cuMemcpyD2H_detect, 3, int)
	TIMER_MACRO(cuMemcpyD2H_detect, 3, (cudaStream_t) 0, int);
	DeviceToHostDetect(TIMER_PTR->GetTime(), (void *) a, (void *)b, (size_t) c);
	return ret_value;
}


WRAP_SUPPORTED_CALL_TIME(cuMemcpyD2HAsync_detect, 4, int) 
	TIMER_MACRO(cuMemcpyD2HAsync_detect, 4, (cudaStream_t) d, int);
	DeviceToHostDetect(TIMER_PTR->GetTime(), (void *) a, (void *)b, (size_t) c);
	return ret_value;
}

UNSUPPORTED_CALL(cuMemcpyH2A_detect, 4, int) 
	//int ret_value = CALL_UNDERLYING(cuMemcpyH2A_detect, VARARRAY(4));
	return ret_value;
}

UNSUPPORTED_CALL(cuMemcpyH2AAsync_detect, 5, int) 
	//int ret_value = CALL_UNDERLYING(cuMemcpyH2AAsync_detect, VARARRAY(5));
	return ret_value;
}

WRAP_SUPPORTED_CALL_TIME(cuMemcpyH2D_detect, 3, int) 
	TIMER_MACRO(cuMemcpyH2D_detect, 3, (cudaStream_t) 0, int);
	HostToDeviceDetect(TIMER_PTR->GetTime(), (void *)a, (void*)b, (size_t) c);
	return ret_value;	
}

WRAP_SUPPORTED_CALL_TIME(cuMemcpyH2DAsync_detect, 4, int)
	TIMER_MACRO(cuMemcpyH2DAsync_detect, 4, (cudaStream_t) d, int);
	HostToDeviceDetect(TIMER_PTR->GetTime(), (void *)a, (void*)b, (size_t) c);
	return ret_value;	
}

// Deduplication Wrapper Functions.
// Currently only support Host -> Device Deduplication

WRAP_SUPPORTED_CALL_TIME(cuMemcpyHtoDAsync_dedup, 4, int) 
	int error = (int)CUDA_SUCCESS;
	DataStruct ret = HostToDeviceDedup(a, b, (size_t)c, false, (CUstream) d);
	if (ret.duplicate == false) {
		STORAGE_PTR->LogOutput("No existing duplicate found, perform transfer H2DAsync");
		int v = CALL_UNDERLYING_ARGS(cuMemcpyHtoDAsync_dedup, 4);
		if (v != error){
			STORAGE_PTR->LogOutput("Could not perform underlying transfer - cuMemcpyH2DAsync");
			return v;
		}
		ret.storePTR = (void *) a;
		STORAGE_PTR->AddNew(ret);
	} else {
		STORAGE_PTR->LogOutput("Duplicate found- H2D Async");
	}
	return error;
}

WRAP_SUPPORTED_CALL_TIME(cuMemcpyHtoD_dedup, 3, int) 
	int error = (int)CUDA_SUCCESS;
	DataStruct ret = HostToDeviceDedup(a, b, (size_t)c, true, 0);	
	if (ret.duplicate == false) {
		#ifdef DEBUG_OUTPUT
		STORAGE_PTR->LogOutput("No existing duplicate found, perform transfer H2D");
		#endif
		int v = CALL_UNDERLYING_ARGS(cuMemcpyHtoD_dedup, 3);
		if (v != error){
			STORAGE_PTR->LogOutput("Could not perform underlying transfer - cuMemcpyH2D");
			return v;
		}
		ret.storePTR = (void *) a;
		STORAGE_PTR->AddNew(ret);
	} else {
		// #ifdef DEBUG_OUTPUT
		// STORAGE_PTR->LogOutput("Duplicate found- H2D");
		// #endif
		// error = cudaDeviceSynchronize();		
	}
	return error;
}


WRAP_SUPPORTED_CALL_TIME(cuMemcpyAtoD_dedup, 4, int) 
	int error = (int)CUDA_SUCCESS;
	DataStruct ret = HostToDeviceDedup(a, (void *)(((char*)b)+(size_t)c), (size_t)d, true, 0);	
	if (ret.duplicate == false) {
		#ifdef DEBUG_OUTPUT
		STORAGE_PTR->LogOutput("No existing duplicate found, perform transfer A2D");
		#endif
		int v = CALL_UNDERLYING_ARGS(cuMemcpyAtoD_dedup, 4);
		if (v != error){
			STORAGE_PTR->LogOutput("Could not perform underlying transfer - cuMemcpyA2D");
			return v;
		}
		ret.storePTR = (void *) a;
		STORAGE_PTR->AddNew(ret);
	} else {
		#ifdef DEBUG_OUTPUT
		STORAGE_PTR->LogOutput("Duplicate found- A2D");
		#endif
		error = cudaDeviceSynchronize();		
	}
	return error;
}

}
