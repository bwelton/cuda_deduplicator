#pragma once
#include <iostream>
#include <functional>
#include <memory>
#include <map>
#include <vector>
#include "Parameters.h"
#include "DriverWrapperBase.h"
enum PluginReturn {
	NO_ACTION = 0,
	NOTIFY_ON_CHANGE,	// Notify when the parameter has changed
	DO_NOT_PERFORM,		// Instruct driver to not perform the action
	PERFORMED_ACTION,	// This plugin performed the action, do not perform again
	MODIFIED_PARAMS,	// This plugin modified the parameters
	FAILED			// This plugin has failed
};

enum CallID {
	ID_CUGETERRORSTRING = 0,
	ID_CUGETERRORNAME,
	ID_CUINIT,
	ID_CUDRIVERGETVERSION,
	ID_CUDEVICEGET,
	ID_CUDEVICEGETCOUNT,
	ID_CUDEVICEGETNAME,
	ID_CUDEVICETOTALMEM,
	ID_CUDEVICEGETATTRIBUTE,
	ID_CUDEVICEGETPROPERTIES,
	ID_CUDEVICECOMPUTECAPABILITY,
	ID_CUDEVICEPRIMARYCTXRETAIN,
	ID_CUDEVICEPRIMARYCTXRELEASE,
	ID_CUDEVICEPRIMARYCTXSETFLAGS,
	ID_CUDEVICEPRIMARYCTXGETSTATE,
	ID_CUDEVICEPRIMARYCTXRESET,
	ID_CUCTXCREATE,
	ID_CUCTXDESTROY,
	ID_CUCTXPUSHCURRENT,
	ID_CUCTXPOPCURRENT,
	ID_CUCTXSETCURRENT,
	ID_CUCTXGETCURRENT,
	ID_CUCTXGETDEVICE,
	ID_CUCTXGETFLAGS,
	ID_CUCTXSYNCHRONIZE,
	ID_CUCTXSETLIMIT,
	ID_CUCTXGETLIMIT,
	ID_CUCTXGETCACHECONFIG,
	ID_CUCTXSETCACHECONFIG,
	ID_CUCTXGETSHAREDMEMCONFIG,
	ID_CUCTXSETSHAREDMEMCONFIG,
	ID_CUCTXGETAPIVERSION,
	ID_CUCTXGETSTREAMPRIORITYRANGE,
	ID_CUCTXATTACH,
	ID_CUCTXDETACH,
	ID_CUMODULELOAD,
	ID_CUMODULELOADDATA,
	ID_CUMODULELOADDATAEX,
	ID_CUMODULELOADFATBINARY,
	ID_CUMODULEUNLOAD,
	ID_CUMODULEGETFUNCTION,
	ID_CUMODULEGETGLOBAL,
	ID_CUMODULEGETTEXREF,
	ID_CUMODULEGETSURFREF,
	ID_CULINKCREATE,
	ID_CULINKADDDATA,
	ID_CULINKADDFILE,
	ID_CULINKCOMPLETE,
	ID_CULINKDESTROY,
	ID_CUMEMGETINFO,
	ID_CUMEMALLOC,
	ID_CUMEMALLOCPITCH,
	ID_CUMEMFREE,
	ID_CUMEMGETADDRESSRANGE,
	ID_CUMEMALLOCHOST,
	ID_CUMEMFREEHOST,
	ID_CUMEMHOSTALLOC,
	ID_CUMEMHOSTGETDEVICEPOINTER,
	ID_CUMEMHOSTGETFLAGS,
	ID_CUMEMALLOCMANAGED,
	ID_CUDEVICEGETBYPCIBUSID,
	ID_CUDEVICEGETPCIBUSID,
	ID_CUIPCGETEVENTHANDLE,
	ID_CUIPCOPENEVENTHANDLE,
	ID_CUIPCGETMEMHANDLE,
	ID_CUIPCOPENMEMHANDLE,
	ID_CUIPCCLOSEMEMHANDLE,
	ID_CUMEMHOSTREGISTER,
	ID_CUMEMHOSTUNREGISTER,
	ID_CUMEMCPY,
	ID_CUMEMCPYPEER,
	ID_CUMEMCPYHTOD,
	ID_CUMEMCPYDTOH,
	ID_CUMEMCPYDTOD,
	ID_CUMEMCPYDTOA,
	ID_CUMEMCPYATOD,
	ID_CUMEMCPYHTOA,
	ID_CUMEMCPYATOH,
	ID_CUMEMCPYATOA,
	ID_CUMEMCPY2D,
	ID_CUMEMCPY2DUNALIGNED,
	ID_CUMEMCPY3D,
	ID_CUMEMCPY3DPEER,
	ID_CUMEMCPYASYNC,
	ID_CUMEMCPYPEERASYNC,
	ID_CUMEMCPYHTODASYNC,
	ID_CUMEMCPYDTOHASYNC,
	ID_CUMEMCPYDTODASYNC,
	ID_CUMEMCPYHTOAASYNC,
	ID_CUMEMCPYATOHASYNC,
	ID_CUMEMCPY2DASYNC,
	ID_CUMEMCPY3DASYNC,
	ID_CUMEMCPY3DPEERASYNC,
	ID_CUMEMSETD8,
	ID_CUMEMSETD16,
	ID_CUMEMSETD32,
	ID_CUMEMSETD2D8,
	ID_CUMEMSETD2D16,
	ID_CUMEMSETD2D32,
	ID_CUMEMSETD8ASYNC,
	ID_CUMEMSETD16ASYNC,
	ID_CUMEMSETD32ASYNC,
	ID_CUMEMSETD2D8ASYNC,
	ID_CUMEMSETD2D16ASYNC,
	ID_CUMEMSETD2D32ASYNC,
	ID_CUARRAYCREATE,
	ID_CUARRAYGETDESCRIPTOR,
	ID_CUARRAYDESTROY,
	ID_CUARRAY3DCREATE,
	ID_CUARRAY3DGETDESCRIPTOR,
	ID_CUMIPMAPPEDARRAYCREATE,
	ID_CUMIPMAPPEDARRAYGETLEVEL,
	ID_CUMIPMAPPEDARRAYDESTROY,
	ID_CUPOINTERGETATTRIBUTE,
	ID_CUMEMPREFETCHASYNC,
	ID_CUMEMADVISE,
	ID_CUMEMRANGEGETATTRIBUTE,
	ID_CUMEMRANGEGETATTRIBUTES,
	ID_CUPOINTERSETATTRIBUTE,
	ID_CUPOINTERGETATTRIBUTES,
	ID_CUSTREAMCREATE,
	ID_CUSTREAMCREATEWITHPRIORITY,
	ID_CUSTREAMGETPRIORITY,
	ID_CUSTREAMGETFLAGS,
	ID_CUSTREAMWAITEVENT,
	ID_CUSTREAMADDCALLBACK,
	ID_CUSTREAMATTACHMEMASYNC,
	ID_CUSTREAMQUERY,
	ID_CUSTREAMSYNCHRONIZE,
	ID_CUSTREAMDESTROY,
	ID_CUEVENTCREATE,
	ID_CUEVENTRECORD,
	ID_CUEVENTQUERY,
	ID_CUEVENTSYNCHRONIZE,
	ID_CUEVENTDESTROY,
	ID_CUEVENTELAPSEDTIME,
	ID_CUSTREAMWAITVALUE32,
	ID_CUSTREAMWRITEVALUE32,
	ID_CUSTREAMBATCHMEMOP,
	ID_CUFUNCGETATTRIBUTE,
	ID_CUFUNCSETCACHECONFIG,
	ID_CUFUNCSETSHAREDMEMCONFIG,
	ID_CULAUNCHKERNEL,
	ID_CUFUNCSETBLOCKSHAPE,
	ID_CUFUNCSETSHAREDSIZE,
	ID_CUPARAMSETSIZE,
	ID_CUPARAMSETI,
	ID_CUPARAMSETF,
	ID_CUPARAMSETV,
	ID_CULAUNCH,
	ID_CULAUNCHGRID,
	ID_CULAUNCHGRIDASYNC,
	ID_CUPARAMSETTEXREF,
	ID_CUOCCUPANCYMAXACTIVEBLOCKSPERMULTIPROCESSOR,
	ID_CUOCCUPANCYMAXACTIVEBLOCKSPERMULTIPROCESSORWITHFLAGS,
	ID_CUOCCUPANCYMAXPOTENTIALBLOCKSIZE,
	ID_CUOCCUPANCYMAXPOTENTIALBLOCKSIZEWITHFLAGS,
	ID_CUTEXREFSETARRAY,
	ID_CUTEXREFSETMIPMAPPEDARRAY,
	ID_CUTEXREFSETADDRESS,
	ID_CUTEXREFSETADDRESS2D,
	ID_CUTEXREFSETFORMAT,
	ID_CUTEXREFSETADDRESSMODE,
	ID_CUTEXREFSETFILTERMODE,
	ID_CUTEXREFSETMIPMAPFILTERMODE,
	ID_CUTEXREFSETMIPMAPLEVELBIAS,
	ID_CUTEXREFSETMIPMAPLEVELCLAMP,
	ID_CUTEXREFSETMAXANISOTROPY,
	ID_CUTEXREFSETBORDERCOLOR,
	ID_CUTEXREFSETFLAGS,
	ID_CUTEXREFGETADDRESS,
	ID_CUTEXREFGETARRAY,
	ID_CUTEXREFGETMIPMAPPEDARRAY,
	ID_CUTEXREFGETADDRESSMODE,
	ID_CUTEXREFGETFILTERMODE,
	ID_CUTEXREFGETFORMAT,
	ID_CUTEXREFGETMIPMAPFILTERMODE,
	ID_CUTEXREFGETMIPMAPLEVELBIAS,
	ID_CUTEXREFGETMIPMAPLEVELCLAMP,
	ID_CUTEXREFGETMAXANISOTROPY,
	ID_CUTEXREFGETBORDERCOLOR,
	ID_CUTEXREFGETFLAGS,
	ID_CUTEXREFCREATE,
	ID_CUTEXREFDESTROY,
	ID_CUSURFREFSETARRAY,
	ID_CUSURFREFGETARRAY,
	ID_CUTEXOBJECTCREATE,
	ID_CUTEXOBJECTDESTROY,
	ID_CUTEXOBJECTGETRESOURCEDESC,
	ID_CUTEXOBJECTGETTEXTUREDESC,
	ID_CUTEXOBJECTGETRESOURCEVIEWDESC,
	ID_CUSURFOBJECTCREATE,
	ID_CUSURFOBJECTDESTROY,
	ID_CUSURFOBJECTGETRESOURCEDESC,
	ID_CUDEVICECANACCESSPEER,
	ID_CUDEVICEGETP2PATTRIBUTE,
	ID_CUCTXENABLEPEERACCESS,
	ID_CUCTXDISABLEPEERACCESS,
	ID_CUGRAPHICSUNREGISTERRESOURCE,
	ID_CUGRAPHICSSUBRESOURCEGETMAPPEDARRAY,
	ID_CUGRAPHICSRESOURCEGETMAPPEDMIPMAPPEDARRAY,
	ID_CUGRAPHICSRESOURCEGETMAPPEDPOINTER,
	ID_CUGRAPHICSRESOURCESETMAPFLAGS,
	ID_CUGRAPHICSMAPRESOURCES,
	ID_CUGRAPHICSUNMAPRESOURCES,
	ID_CUGETEXPORTTABLE,
	ID_CUTEXREFSETADDRESS2D_V2,
	ID_CUMEMCPYHTOD_V2,
	ID_CUMEMCPYDTOH_V2,
	ID_CUMEMCPYDTOD_V2,
	ID_CUMEMCPYDTOA_V2,
	ID_CUMEMCPYATOD_V2,
	ID_CUMEMCPYHTOA_V2,
	ID_CUMEMCPYATOH_V2,
	ID_CUMEMCPYATOA_V2,
	ID_CUMEMCPYHTOAASYNC_V2,
	ID_CUMEMCPYATOHASYNC_V2,
	ID_CUMEMCPY2D_V2,
	ID_CUMEMCPY2DUNALIGNED_V2,
	ID_CUMEMCPY3D_V2,
	ID_CUMEMCPYHTODASYNC_V2,
	ID_CUMEMCPYDTOHASYNC_V2,
	ID_CUMEMCPYDTODASYNC_V2,
	ID_CUMEMCPY2DASYNC_V2,
	ID_CUMEMCPY3DASYNC_V2,
	ID_CUMEMSETD8_V2,
	ID_CUMEMSETD16_V2,
	ID_CUMEMSETD32_V2,
	ID_CUMEMSETD2D8_V2,
	ID_CUMEMSETD2D16_V2,
	ID_CUMEMSETD2D32_V2
};

#ifndef DEFINED_TEMPLATES
#define EXTERN_FLAG extern
#else
#define EXTERN_FLAG 
#endif
EXTERN_FLAG std::function<int(CUresult,const char * *)> Bound_cuGetErrorString;
EXTERN_FLAG std::function<int(CUresult,const char * *)> Bound_cuGetErrorName;
EXTERN_FLAG std::function<int(unsigned int)> Bound_cuInit;
EXTERN_FLAG std::function<int(int *)> Bound_cuDriverGetVersion;
EXTERN_FLAG std::function<int(CUdevice *,int)> Bound_cuDeviceGet;
EXTERN_FLAG std::function<int(int *)> Bound_cuDeviceGetCount;
EXTERN_FLAG std::function<int(char *,int,CUdevice)> Bound_cuDeviceGetName;
EXTERN_FLAG std::function<int(size_t *,CUdevice)> Bound_cuDeviceTotalMem;
EXTERN_FLAG std::function<int(int *,CUdevice_attribute,CUdevice)> Bound_cuDeviceGetAttribute;
EXTERN_FLAG std::function<int(CUdevprop *,CUdevice)> Bound_cuDeviceGetProperties;
EXTERN_FLAG std::function<int(int *,int *,CUdevice)> Bound_cuDeviceComputeCapability;
EXTERN_FLAG std::function<int(CUcontext *,CUdevice)> Bound_cuDevicePrimaryCtxRetain;
EXTERN_FLAG std::function<int(CUdevice)> Bound_cuDevicePrimaryCtxRelease;
EXTERN_FLAG std::function<int(CUdevice,unsigned int)> Bound_cuDevicePrimaryCtxSetFlags;
EXTERN_FLAG std::function<int(CUdevice,unsigned int *,int *)> Bound_cuDevicePrimaryCtxGetState;
EXTERN_FLAG std::function<int(CUdevice)> Bound_cuDevicePrimaryCtxReset;
EXTERN_FLAG std::function<int(CUcontext *,unsigned int,CUdevice)> Bound_cuCtxCreate;
EXTERN_FLAG std::function<int(CUcontext)> Bound_cuCtxDestroy;
EXTERN_FLAG std::function<int(CUcontext)> Bound_cuCtxPushCurrent;
EXTERN_FLAG std::function<int(CUcontext *)> Bound_cuCtxPopCurrent;
EXTERN_FLAG std::function<int(CUcontext)> Bound_cuCtxSetCurrent;
EXTERN_FLAG std::function<int(CUcontext *)> Bound_cuCtxGetCurrent;
EXTERN_FLAG std::function<int(CUdevice *)> Bound_cuCtxGetDevice;
EXTERN_FLAG std::function<int(unsigned int *)> Bound_cuCtxGetFlags;
EXTERN_FLAG std::function<int(void)> Bound_cuCtxSynchronize;
EXTERN_FLAG std::function<int(CUlimit,size_t)> Bound_cuCtxSetLimit;
EXTERN_FLAG std::function<int(size_t *,CUlimit)> Bound_cuCtxGetLimit;
EXTERN_FLAG std::function<int(CUfunc_cache *)> Bound_cuCtxGetCacheConfig;
EXTERN_FLAG std::function<int(CUfunc_cache)> Bound_cuCtxSetCacheConfig;
EXTERN_FLAG std::function<int(CUsharedconfig *)> Bound_cuCtxGetSharedMemConfig;
EXTERN_FLAG std::function<int(CUsharedconfig)> Bound_cuCtxSetSharedMemConfig;
EXTERN_FLAG std::function<int(CUcontext,unsigned int *)> Bound_cuCtxGetApiVersion;
EXTERN_FLAG std::function<int(int *,int *)> Bound_cuCtxGetStreamPriorityRange;
EXTERN_FLAG std::function<int(CUcontext *,unsigned int)> Bound_cuCtxAttach;
EXTERN_FLAG std::function<int(CUcontext)> Bound_cuCtxDetach;
EXTERN_FLAG std::function<int(CUmodule *,const char *)> Bound_cuModuleLoad;
EXTERN_FLAG std::function<int(CUmodule *,const void *)> Bound_cuModuleLoadData;
EXTERN_FLAG std::function<int(CUmodule *,const void *,unsigned int,CUjit_option *,void * *)> Bound_cuModuleLoadDataEx;
EXTERN_FLAG std::function<int(CUmodule *,const void *)> Bound_cuModuleLoadFatBinary;
EXTERN_FLAG std::function<int(CUmodule)> Bound_cuModuleUnload;
EXTERN_FLAG std::function<int(CUfunction *,CUmodule,const char *)> Bound_cuModuleGetFunction;
EXTERN_FLAG std::function<int(CUdeviceptr *,size_t *,CUmodule,const char *)> Bound_cuModuleGetGlobal;
EXTERN_FLAG std::function<int(CUtexref *,CUmodule,const char *)> Bound_cuModuleGetTexRef;
EXTERN_FLAG std::function<int(CUsurfref *,CUmodule,const char *)> Bound_cuModuleGetSurfRef;
EXTERN_FLAG std::function<int(unsigned int,CUjit_option *,void * *,CUlinkState *)> Bound_cuLinkCreate;
EXTERN_FLAG std::function<int(CUlinkState,CUjitInputType,void *,size_t,const char *,unsigned int,CUjit_option *,void * *)> Bound_cuLinkAddData;
EXTERN_FLAG std::function<int(CUlinkState,CUjitInputType,const char *,unsigned int,CUjit_option *,void * *)> Bound_cuLinkAddFile;
EXTERN_FLAG std::function<int(CUlinkState,void * *,size_t *)> Bound_cuLinkComplete;
EXTERN_FLAG std::function<int(CUlinkState)> Bound_cuLinkDestroy;
EXTERN_FLAG std::function<int(size_t *,size_t *)> Bound_cuMemGetInfo;
EXTERN_FLAG std::function<int(CUdeviceptr *,size_t)> Bound_cuMemAlloc;
EXTERN_FLAG std::function<int(CUdeviceptr *,size_t *,size_t,size_t,unsigned int)> Bound_cuMemAllocPitch;
EXTERN_FLAG std::function<int(CUdeviceptr)> Bound_cuMemFree;
EXTERN_FLAG std::function<int(CUdeviceptr *,size_t *,CUdeviceptr)> Bound_cuMemGetAddressRange;
EXTERN_FLAG std::function<int(void * *,size_t)> Bound_cuMemAllocHost;
EXTERN_FLAG std::function<int(void *)> Bound_cuMemFreeHost;
EXTERN_FLAG std::function<int(void * *,size_t,unsigned int)> Bound_cuMemHostAlloc;
EXTERN_FLAG std::function<int(CUdeviceptr *,void *,unsigned int)> Bound_cuMemHostGetDevicePointer;
EXTERN_FLAG std::function<int(unsigned int *,void *)> Bound_cuMemHostGetFlags;
EXTERN_FLAG std::function<int(CUdeviceptr *,size_t,unsigned int)> Bound_cuMemAllocManaged;
EXTERN_FLAG std::function<int(CUdevice *,const char *)> Bound_cuDeviceGetByPCIBusId;
EXTERN_FLAG std::function<int(char *,int,CUdevice)> Bound_cuDeviceGetPCIBusId;
EXTERN_FLAG std::function<int(CUipcEventHandle *,CUevent)> Bound_cuIpcGetEventHandle;
EXTERN_FLAG std::function<int(CUevent *,CUipcEventHandle)> Bound_cuIpcOpenEventHandle;
EXTERN_FLAG std::function<int(CUipcMemHandle *,CUdeviceptr)> Bound_cuIpcGetMemHandle;
EXTERN_FLAG std::function<int(CUdeviceptr *,CUipcMemHandle,unsigned int)> Bound_cuIpcOpenMemHandle;
EXTERN_FLAG std::function<int(CUdeviceptr)> Bound_cuIpcCloseMemHandle;
EXTERN_FLAG std::function<int(void *,size_t,unsigned int)> Bound_cuMemHostRegister;
EXTERN_FLAG std::function<int(void *)> Bound_cuMemHostUnregister;
EXTERN_FLAG std::function<int(CUdeviceptr,CUdeviceptr,size_t)> Bound_cuMemcpy;
EXTERN_FLAG std::function<int(CUdeviceptr,CUcontext,CUdeviceptr,CUcontext,size_t)> Bound_cuMemcpyPeer;
EXTERN_FLAG std::function<int(CUdeviceptr,const void *,size_t)> Bound_cuMemcpyHtoD;
EXTERN_FLAG std::function<int(void *,CUdeviceptr,size_t)> Bound_cuMemcpyDtoH;
EXTERN_FLAG std::function<int(CUdeviceptr,CUdeviceptr,size_t)> Bound_cuMemcpyDtoD;
EXTERN_FLAG std::function<int(CUarray,size_t,CUdeviceptr,size_t)> Bound_cuMemcpyDtoA;
EXTERN_FLAG std::function<int(CUdeviceptr,CUarray,size_t,size_t)> Bound_cuMemcpyAtoD;
EXTERN_FLAG std::function<int(CUarray,size_t,const void *,size_t)> Bound_cuMemcpyHtoA;
EXTERN_FLAG std::function<int(void *,CUarray,size_t,size_t)> Bound_cuMemcpyAtoH;
EXTERN_FLAG std::function<int(CUarray,size_t,CUarray,size_t,size_t)> Bound_cuMemcpyAtoA;
EXTERN_FLAG std::function<int(const CUDA_MEMCPY2D *)> Bound_cuMemcpy2D;
EXTERN_FLAG std::function<int(const CUDA_MEMCPY2D *)> Bound_cuMemcpy2DUnaligned;
EXTERN_FLAG std::function<int(const CUDA_MEMCPY3D *)> Bound_cuMemcpy3D;
EXTERN_FLAG std::function<int(const CUDA_MEMCPY3D_PEER *)> Bound_cuMemcpy3DPeer;
EXTERN_FLAG std::function<int(CUdeviceptr,CUdeviceptr,size_t,CUstream)> Bound_cuMemcpyAsync;
EXTERN_FLAG std::function<int(CUdeviceptr,CUcontext,CUdeviceptr,CUcontext,size_t,CUstream)> Bound_cuMemcpyPeerAsync;
EXTERN_FLAG std::function<int(CUdeviceptr,const void *,size_t,CUstream)> Bound_cuMemcpyHtoDAsync;
EXTERN_FLAG std::function<int(void *,CUdeviceptr,size_t,CUstream)> Bound_cuMemcpyDtoHAsync;
EXTERN_FLAG std::function<int(CUdeviceptr,CUdeviceptr,size_t,CUstream)> Bound_cuMemcpyDtoDAsync;
EXTERN_FLAG std::function<int(CUarray,size_t,const void *,size_t,CUstream)> Bound_cuMemcpyHtoAAsync;
EXTERN_FLAG std::function<int(void *,CUarray,size_t,size_t,CUstream)> Bound_cuMemcpyAtoHAsync;
EXTERN_FLAG std::function<int(const CUDA_MEMCPY2D *,CUstream)> Bound_cuMemcpy2DAsync;
EXTERN_FLAG std::function<int(const CUDA_MEMCPY3D *,CUstream)> Bound_cuMemcpy3DAsync;
EXTERN_FLAG std::function<int(const CUDA_MEMCPY3D_PEER *,CUstream)> Bound_cuMemcpy3DPeerAsync;
EXTERN_FLAG std::function<int(CUdeviceptr,unsigned char,size_t)> Bound_cuMemsetD8;
EXTERN_FLAG std::function<int(CUdeviceptr,unsigned short,size_t)> Bound_cuMemsetD16;
EXTERN_FLAG std::function<int(CUdeviceptr,unsigned int,size_t)> Bound_cuMemsetD32;
EXTERN_FLAG std::function<int(CUdeviceptr,size_t,unsigned char,size_t,size_t)> Bound_cuMemsetD2D8;
EXTERN_FLAG std::function<int(CUdeviceptr,size_t,unsigned short,size_t,size_t)> Bound_cuMemsetD2D16;
EXTERN_FLAG std::function<int(CUdeviceptr,size_t,unsigned int,size_t,size_t)> Bound_cuMemsetD2D32;
EXTERN_FLAG std::function<int(CUdeviceptr,unsigned char,size_t,CUstream)> Bound_cuMemsetD8Async;
EXTERN_FLAG std::function<int(CUdeviceptr,unsigned short,size_t,CUstream)> Bound_cuMemsetD16Async;
EXTERN_FLAG std::function<int(CUdeviceptr,unsigned int,size_t,CUstream)> Bound_cuMemsetD32Async;
EXTERN_FLAG std::function<int(CUdeviceptr,size_t,unsigned char,size_t,size_t,CUstream)> Bound_cuMemsetD2D8Async;
EXTERN_FLAG std::function<int(CUdeviceptr,size_t,unsigned short,size_t,size_t,CUstream)> Bound_cuMemsetD2D16Async;
EXTERN_FLAG std::function<int(CUdeviceptr,size_t,unsigned int,size_t,size_t,CUstream)> Bound_cuMemsetD2D32Async;
EXTERN_FLAG std::function<int(CUarray *,const CUDA_ARRAY_DESCRIPTOR *)> Bound_cuArrayCreate;
EXTERN_FLAG std::function<int(CUDA_ARRAY_DESCRIPTOR *,CUarray)> Bound_cuArrayGetDescriptor;
EXTERN_FLAG std::function<int(CUarray)> Bound_cuArrayDestroy;
EXTERN_FLAG std::function<int(CUarray *,const CUDA_ARRAY3D_DESCRIPTOR *)> Bound_cuArray3DCreate;
EXTERN_FLAG std::function<int(CUDA_ARRAY3D_DESCRIPTOR *,CUarray)> Bound_cuArray3DGetDescriptor;
EXTERN_FLAG std::function<int(CUmipmappedArray *,const CUDA_ARRAY3D_DESCRIPTOR *,unsigned int)> Bound_cuMipmappedArrayCreate;
EXTERN_FLAG std::function<int(CUarray *,CUmipmappedArray,unsigned int)> Bound_cuMipmappedArrayGetLevel;
EXTERN_FLAG std::function<int(CUmipmappedArray)> Bound_cuMipmappedArrayDestroy;
EXTERN_FLAG std::function<int(void *,CUpointer_attribute,CUdeviceptr)> Bound_cuPointerGetAttribute;
EXTERN_FLAG std::function<int(CUdeviceptr,size_t,CUdevice,CUstream)> Bound_cuMemPrefetchAsync;
EXTERN_FLAG std::function<int(CUdeviceptr,size_t,CUmem_advise,CUdevice)> Bound_cuMemAdvise;
EXTERN_FLAG std::function<int(void *,size_t,CUmem_range_attribute,CUdeviceptr,size_t)> Bound_cuMemRangeGetAttribute;
EXTERN_FLAG std::function<int(void * *,size_t *,CUmem_range_attribute *,size_t,CUdeviceptr,size_t)> Bound_cuMemRangeGetAttributes;
EXTERN_FLAG std::function<int(const void *,CUpointer_attribute,CUdeviceptr)> Bound_cuPointerSetAttribute;
EXTERN_FLAG std::function<int(unsigned int,CUpointer_attribute *,void * *,CUdeviceptr)> Bound_cuPointerGetAttributes;
EXTERN_FLAG std::function<int(CUstream *,unsigned int)> Bound_cuStreamCreate;
EXTERN_FLAG std::function<int(CUstream *,unsigned int,int)> Bound_cuStreamCreateWithPriority;
EXTERN_FLAG std::function<int(CUstream,int *)> Bound_cuStreamGetPriority;
EXTERN_FLAG std::function<int(CUstream,unsigned int *)> Bound_cuStreamGetFlags;
EXTERN_FLAG std::function<int(CUstream,CUevent,unsigned int)> Bound_cuStreamWaitEvent;
EXTERN_FLAG std::function<int(CUstream,CUstreamCallback,void *,unsigned int)> Bound_cuStreamAddCallback;
EXTERN_FLAG std::function<int(CUstream,CUdeviceptr,size_t,unsigned int)> Bound_cuStreamAttachMemAsync;
EXTERN_FLAG std::function<int(CUstream)> Bound_cuStreamQuery;
EXTERN_FLAG std::function<int(CUstream)> Bound_cuStreamSynchronize;
EXTERN_FLAG std::function<int(CUstream)> Bound_cuStreamDestroy;
EXTERN_FLAG std::function<int(CUevent *,unsigned int)> Bound_cuEventCreate;
EXTERN_FLAG std::function<int(CUevent,CUstream)> Bound_cuEventRecord;
EXTERN_FLAG std::function<int(CUevent)> Bound_cuEventQuery;
EXTERN_FLAG std::function<int(CUevent)> Bound_cuEventSynchronize;
EXTERN_FLAG std::function<int(CUevent)> Bound_cuEventDestroy;
EXTERN_FLAG std::function<int(float *,CUevent,CUevent)> Bound_cuEventElapsedTime;
EXTERN_FLAG std::function<int(CUstream,CUdeviceptr,cuuint32_t,unsigned int)> Bound_cuStreamWaitValue32;
EXTERN_FLAG std::function<int(CUstream,CUdeviceptr,cuuint32_t,unsigned int)> Bound_cuStreamWriteValue32;
EXTERN_FLAG std::function<int(CUstream,unsigned int,CUstreamBatchMemOpParams *,unsigned int)> Bound_cuStreamBatchMemOp;
EXTERN_FLAG std::function<int(int *,CUfunction_attribute,CUfunction)> Bound_cuFuncGetAttribute;
EXTERN_FLAG std::function<int(CUfunction,CUfunc_cache)> Bound_cuFuncSetCacheConfig;
EXTERN_FLAG std::function<int(CUfunction,CUsharedconfig)> Bound_cuFuncSetSharedMemConfig;
EXTERN_FLAG std::function<int(CUfunction,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,CUstream,void * *,void * *)> Bound_cuLaunchKernel;
EXTERN_FLAG std::function<int(CUfunction,int,int,int)> Bound_cuFuncSetBlockShape;
EXTERN_FLAG std::function<int(CUfunction,unsigned int)> Bound_cuFuncSetSharedSize;
EXTERN_FLAG std::function<int(CUfunction,unsigned int)> Bound_cuParamSetSize;
EXTERN_FLAG std::function<int(CUfunction,int,unsigned int)> Bound_cuParamSeti;
EXTERN_FLAG std::function<int(CUfunction,int,float)> Bound_cuParamSetf;
EXTERN_FLAG std::function<int(CUfunction,int,void *,unsigned int)> Bound_cuParamSetv;
EXTERN_FLAG std::function<int(CUfunction)> Bound_cuLaunch;
EXTERN_FLAG std::function<int(CUfunction,int,int)> Bound_cuLaunchGrid;
EXTERN_FLAG std::function<int(CUfunction,int,int,CUstream)> Bound_cuLaunchGridAsync;
EXTERN_FLAG std::function<int(CUfunction,int,CUtexref)> Bound_cuParamSetTexRef;
EXTERN_FLAG std::function<int(int *,CUfunction,int,size_t)> Bound_cuOccupancyMaxActiveBlocksPerMultiprocessor;
EXTERN_FLAG std::function<int(int *,CUfunction,int,size_t,unsigned int)> Bound_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags;
EXTERN_FLAG std::function<int(int *,int *,CUfunction,CUoccupancyB2DSize,size_t,int)> Bound_cuOccupancyMaxPotentialBlockSize;
EXTERN_FLAG std::function<int(int *,int *,CUfunction,CUoccupancyB2DSize,size_t,int,unsigned int)> Bound_cuOccupancyMaxPotentialBlockSizeWithFlags;
EXTERN_FLAG std::function<int(CUtexref,CUarray,unsigned int)> Bound_cuTexRefSetArray;
EXTERN_FLAG std::function<int(CUtexref,CUmipmappedArray,unsigned int)> Bound_cuTexRefSetMipmappedArray;
EXTERN_FLAG std::function<int(size_t *,CUtexref,CUdeviceptr,size_t)> Bound_cuTexRefSetAddress;
EXTERN_FLAG std::function<int(CUtexref,const CUDA_ARRAY_DESCRIPTOR *,CUdeviceptr,size_t)> Bound_cuTexRefSetAddress2D;
EXTERN_FLAG std::function<int(CUtexref,CUarray_format,int)> Bound_cuTexRefSetFormat;
EXTERN_FLAG std::function<int(CUtexref,int,CUaddress_mode)> Bound_cuTexRefSetAddressMode;
EXTERN_FLAG std::function<int(CUtexref,CUfilter_mode)> Bound_cuTexRefSetFilterMode;
EXTERN_FLAG std::function<int(CUtexref,CUfilter_mode)> Bound_cuTexRefSetMipmapFilterMode;
EXTERN_FLAG std::function<int(CUtexref,float)> Bound_cuTexRefSetMipmapLevelBias;
EXTERN_FLAG std::function<int(CUtexref,float,float)> Bound_cuTexRefSetMipmapLevelClamp;
EXTERN_FLAG std::function<int(CUtexref,unsigned int)> Bound_cuTexRefSetMaxAnisotropy;
EXTERN_FLAG std::function<int(CUtexref,float *)> Bound_cuTexRefSetBorderColor;
EXTERN_FLAG std::function<int(CUtexref,unsigned int)> Bound_cuTexRefSetFlags;
EXTERN_FLAG std::function<int(CUdeviceptr *,CUtexref)> Bound_cuTexRefGetAddress;
EXTERN_FLAG std::function<int(CUarray *,CUtexref)> Bound_cuTexRefGetArray;
EXTERN_FLAG std::function<int(CUmipmappedArray *,CUtexref)> Bound_cuTexRefGetMipmappedArray;
EXTERN_FLAG std::function<int(CUaddress_mode *,CUtexref,int)> Bound_cuTexRefGetAddressMode;
EXTERN_FLAG std::function<int(CUfilter_mode *,CUtexref)> Bound_cuTexRefGetFilterMode;
EXTERN_FLAG std::function<int(CUarray_format *,int *,CUtexref)> Bound_cuTexRefGetFormat;
EXTERN_FLAG std::function<int(CUfilter_mode *,CUtexref)> Bound_cuTexRefGetMipmapFilterMode;
EXTERN_FLAG std::function<int(float *,CUtexref)> Bound_cuTexRefGetMipmapLevelBias;
EXTERN_FLAG std::function<int(float *,float *,CUtexref)> Bound_cuTexRefGetMipmapLevelClamp;
EXTERN_FLAG std::function<int(int *,CUtexref)> Bound_cuTexRefGetMaxAnisotropy;
EXTERN_FLAG std::function<int(float *,CUtexref)> Bound_cuTexRefGetBorderColor;
EXTERN_FLAG std::function<int(unsigned int *,CUtexref)> Bound_cuTexRefGetFlags;
EXTERN_FLAG std::function<int(CUtexref *)> Bound_cuTexRefCreate;
EXTERN_FLAG std::function<int(CUtexref)> Bound_cuTexRefDestroy;
EXTERN_FLAG std::function<int(CUsurfref,CUarray,unsigned int)> Bound_cuSurfRefSetArray;
EXTERN_FLAG std::function<int(CUarray *,CUsurfref)> Bound_cuSurfRefGetArray;
EXTERN_FLAG std::function<int(CUtexObject *,const CUDA_RESOURCE_DESC *,const CUDA_TEXTURE_DESC *,const CUDA_RESOURCE_VIEW_DESC *)> Bound_cuTexObjectCreate;
EXTERN_FLAG std::function<int(CUtexObject)> Bound_cuTexObjectDestroy;
EXTERN_FLAG std::function<int(CUDA_RESOURCE_DESC *,CUtexObject)> Bound_cuTexObjectGetResourceDesc;
EXTERN_FLAG std::function<int(CUDA_TEXTURE_DESC *,CUtexObject)> Bound_cuTexObjectGetTextureDesc;
EXTERN_FLAG std::function<int(CUDA_RESOURCE_VIEW_DESC *,CUtexObject)> Bound_cuTexObjectGetResourceViewDesc;
EXTERN_FLAG std::function<int(CUsurfObject *,const CUDA_RESOURCE_DESC *)> Bound_cuSurfObjectCreate;
EXTERN_FLAG std::function<int(CUsurfObject)> Bound_cuSurfObjectDestroy;
EXTERN_FLAG std::function<int(CUDA_RESOURCE_DESC *,CUsurfObject)> Bound_cuSurfObjectGetResourceDesc;
EXTERN_FLAG std::function<int(int *,CUdevice,CUdevice)> Bound_cuDeviceCanAccessPeer;
EXTERN_FLAG std::function<int(int *,CUdevice_P2PAttribute,CUdevice,CUdevice)> Bound_cuDeviceGetP2PAttribute;
EXTERN_FLAG std::function<int(CUcontext,unsigned int)> Bound_cuCtxEnablePeerAccess;
EXTERN_FLAG std::function<int(CUcontext)> Bound_cuCtxDisablePeerAccess;
EXTERN_FLAG std::function<int(CUgraphicsResource)> Bound_cuGraphicsUnregisterResource;
EXTERN_FLAG std::function<int(CUarray *,CUgraphicsResource,unsigned int,unsigned int)> Bound_cuGraphicsSubResourceGetMappedArray;
EXTERN_FLAG std::function<int(CUmipmappedArray *,CUgraphicsResource)> Bound_cuGraphicsResourceGetMappedMipmappedArray;
EXTERN_FLAG std::function<int(CUdeviceptr *,size_t *,CUgraphicsResource)> Bound_cuGraphicsResourceGetMappedPointer;
EXTERN_FLAG std::function<int(CUgraphicsResource,unsigned int)> Bound_cuGraphicsResourceSetMapFlags;
EXTERN_FLAG std::function<int(unsigned int,CUgraphicsResource *,CUstream)> Bound_cuGraphicsMapResources;
EXTERN_FLAG std::function<int(unsigned int,CUgraphicsResource *,CUstream)> Bound_cuGraphicsUnmapResources;
EXTERN_FLAG std::function<int(const void * *,const CUuuid *)> Bound_cuGetExportTable;
EXTERN_FLAG std::function<int(CUtexref,const CUDA_ARRAY_DESCRIPTOR *,CUdeviceptr,size_t)> Bound_cuTexRefSetAddress2D_v2;
EXTERN_FLAG std::function<int(CUdeviceptr,const void *,size_t)> Bound_cuMemcpyHtoD_v2;
EXTERN_FLAG std::function<int(void *,CUdeviceptr,size_t)> Bound_cuMemcpyDtoH_v2;
EXTERN_FLAG std::function<int(CUdeviceptr,CUdeviceptr,size_t)> Bound_cuMemcpyDtoD_v2;
EXTERN_FLAG std::function<int(CUarray,size_t,CUdeviceptr,size_t)> Bound_cuMemcpyDtoA_v2;
EXTERN_FLAG std::function<int(CUdeviceptr,CUarray,size_t,size_t)> Bound_cuMemcpyAtoD_v2;
EXTERN_FLAG std::function<int(CUarray,size_t,const void *,size_t)> Bound_cuMemcpyHtoA_v2;
EXTERN_FLAG std::function<int(void *,CUarray,size_t,size_t)> Bound_cuMemcpyAtoH_v2;
EXTERN_FLAG std::function<int(CUarray,size_t,CUarray,size_t,size_t)> Bound_cuMemcpyAtoA_v2;
EXTERN_FLAG std::function<int(CUarray,size_t,const void *,size_t,CUstream)> Bound_cuMemcpyHtoAAsync_v2;
EXTERN_FLAG std::function<int(void *,CUarray,size_t,size_t,CUstream)> Bound_cuMemcpyAtoHAsync_v2;
EXTERN_FLAG std::function<int(const CUDA_MEMCPY2D *)> Bound_cuMemcpy2D_v2;
EXTERN_FLAG std::function<int(const CUDA_MEMCPY2D *)> Bound_cuMemcpy2DUnaligned_v2;
EXTERN_FLAG std::function<int(const CUDA_MEMCPY3D *)> Bound_cuMemcpy3D_v2;
EXTERN_FLAG std::function<int(CUdeviceptr,const void *,size_t,CUstream)> Bound_cuMemcpyHtoDAsync_v2;
EXTERN_FLAG std::function<int(void *,CUdeviceptr,size_t,CUstream)> Bound_cuMemcpyDtoHAsync_v2;
EXTERN_FLAG std::function<int(CUdeviceptr,CUdeviceptr,size_t,CUstream)> Bound_cuMemcpyDtoDAsync_v2;
EXTERN_FLAG std::function<int(const CUDA_MEMCPY2D *,CUstream)> Bound_cuMemcpy2DAsync_v2;
EXTERN_FLAG std::function<int(const CUDA_MEMCPY3D *,CUstream)> Bound_cuMemcpy3DAsync_v2;
EXTERN_FLAG std::function<int(CUdeviceptr,unsigned char,size_t)> Bound_cuMemsetD8_v2;
EXTERN_FLAG std::function<int(CUdeviceptr,unsigned short,size_t)> Bound_cuMemsetD16_v2;
EXTERN_FLAG std::function<int(CUdeviceptr,unsigned int,size_t)> Bound_cuMemsetD32_v2;
EXTERN_FLAG std::function<int(CUdeviceptr,size_t,unsigned char,size_t,size_t)> Bound_cuMemsetD2D8_v2;
EXTERN_FLAG std::function<int(CUdeviceptr,size_t,unsigned short,size_t,size_t)> Bound_cuMemsetD2D16_v2;
EXTERN_FLAG std::function<int(CUdeviceptr,size_t,unsigned int,size_t,size_t)> Bound_cuMemsetD2D32_v2;
