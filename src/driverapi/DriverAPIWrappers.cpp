#include "DriverAPIHeader.h"
#include <tuple>
#include "DriverWrapperBase.h"
#include "DriverWrapperFactory.h"
#include "cuda.h"
std::shared_ptr<DriverWrapperFactory> DriverFactory;
extern "C" {
// MANUALLY ADDED.....
extern int ORIGINAL_InternalSynchronization( void * a, void * b, void * c);

int INTER_InternalSynchronization( void * a, void * b, void * c) {
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&a,(void **)&b, (void**)&c };	
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_InternalSynchronization, (void*) &ORIGINAL_InternalSynchronization, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}

void JustGenStackTrace() {
	BUILD_FACTORY
	FACTORY_PTR->PrintStack();
	return;
}


void CheckInit_DriverAPI() {
	
}
// This "function" will be rewritten to point to cuGetErrorString
//int ORIGINAL_cuGetErrorString( CUresult error, const char * * pStr ) { }

void * PTR_ORIGINAL_cuGetErrorString;
// This is the call that will take the place of the original
int INTER_cuGetErrorString( CUresult error, const char * * pStr ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&error,(void **)&pStr };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuGetErrorString, (void*) PTR_ORIGINAL_cuGetErrorString, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuGetErrorName
//int ORIGINAL_cuGetErrorName( CUresult error, const char * * pStr ) { }

void * PTR_ORIGINAL_cuGetErrorName;
// This is the call that will take the place of the original
int INTER_cuGetErrorName( CUresult error, const char * * pStr ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&error,(void **)&pStr };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuGetErrorName, (void*) PTR_ORIGINAL_cuGetErrorName, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuInit
//int ORIGINAL_cuInit( unsigned int Flags ) { }

void * PTR_ORIGINAL_cuInit;
// This is the call that will take the place of the original
int INTER_cuInit( unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&Flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuInit, (void*) PTR_ORIGINAL_cuInit, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDriverGetVersion
//int ORIGINAL_cuDriverGetVersion( int * driverVersion ) { }

void * PTR_ORIGINAL_cuDriverGetVersion;
// This is the call that will take the place of the original
int INTER_cuDriverGetVersion( int * driverVersion ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&driverVersion };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDriverGetVersion, (void*) PTR_ORIGINAL_cuDriverGetVersion, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDeviceGet
//int ORIGINAL_cuDeviceGet( CUdevice * device, int ordinal ) { }

void * PTR_ORIGINAL_cuDeviceGet;
// This is the call that will take the place of the original
int INTER_cuDeviceGet( CUdevice * device, int ordinal ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&device,(void **)&ordinal };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDeviceGet, (void*) PTR_ORIGINAL_cuDeviceGet, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDeviceGetCount
//int ORIGINAL_cuDeviceGetCount( int * count ) { }

void * PTR_ORIGINAL_cuDeviceGetCount;
// This is the call that will take the place of the original
int INTER_cuDeviceGetCount( int * count ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&count };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDeviceGetCount, (void*) PTR_ORIGINAL_cuDeviceGetCount, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDeviceGetName
//int ORIGINAL_cuDeviceGetName( char * name, int len, CUdevice dev ) { }

void * PTR_ORIGINAL_cuDeviceGetName;
// This is the call that will take the place of the original
int INTER_cuDeviceGetName( char * name, int len, CUdevice dev ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&name,(void **)&len,(void **)&dev };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDeviceGetName, (void*) PTR_ORIGINAL_cuDeviceGetName, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDeviceTotalMem
//int ORIGINAL_cuDeviceTotalMem( size_t * bytes, CUdevice dev ) { }

void * PTR_ORIGINAL_cuDeviceTotalMem;
// This is the call that will take the place of the original
int INTER_cuDeviceTotalMem( size_t * bytes, CUdevice dev ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&bytes,(void **)&dev };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDeviceTotalMem, (void*) PTR_ORIGINAL_cuDeviceTotalMem, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDeviceGetAttribute
//int ORIGINAL_cuDeviceGetAttribute( int * pi, CUdevice_attribute attrib, CUdevice dev ) { }

void * PTR_ORIGINAL_cuDeviceGetAttribute;
// This is the call that will take the place of the original
int INTER_cuDeviceGetAttribute( int * pi, CUdevice_attribute attrib, CUdevice dev ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pi,(void **)&attrib,(void **)&dev };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDeviceGetAttribute, (void*) PTR_ORIGINAL_cuDeviceGetAttribute, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDeviceGetProperties
//int ORIGINAL_cuDeviceGetProperties( CUdevprop * prop, CUdevice dev ) { }

void * PTR_ORIGINAL_cuDeviceGetProperties;
// This is the call that will take the place of the original
int INTER_cuDeviceGetProperties( CUdevprop * prop, CUdevice dev ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&prop,(void **)&dev };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDeviceGetProperties, (void*) PTR_ORIGINAL_cuDeviceGetProperties, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDeviceComputeCapability
//int ORIGINAL_cuDeviceComputeCapability( int * major, int * minor, CUdevice dev ) { }

void * PTR_ORIGINAL_cuDeviceComputeCapability;
// This is the call that will take the place of the original
int INTER_cuDeviceComputeCapability( int * major, int * minor, CUdevice dev ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&major,(void **)&minor,(void **)&dev };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDeviceComputeCapability, (void*) PTR_ORIGINAL_cuDeviceComputeCapability, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDevicePrimaryCtxRetain
//int ORIGINAL_cuDevicePrimaryCtxRetain( CUcontext * pctx, CUdevice dev ) { }

void * PTR_ORIGINAL_cuDevicePrimaryCtxRetain;
// This is the call that will take the place of the original
int INTER_cuDevicePrimaryCtxRetain( CUcontext * pctx, CUdevice dev ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pctx,(void **)&dev };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDevicePrimaryCtxRetain, (void*) PTR_ORIGINAL_cuDevicePrimaryCtxRetain, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDevicePrimaryCtxRelease
//int ORIGINAL_cuDevicePrimaryCtxRelease( CUdevice dev ) { }

void * PTR_ORIGINAL_cuDevicePrimaryCtxRelease;
// This is the call that will take the place of the original
int INTER_cuDevicePrimaryCtxRelease( CUdevice dev ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dev };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDevicePrimaryCtxRelease, (void*) PTR_ORIGINAL_cuDevicePrimaryCtxRelease, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDevicePrimaryCtxSetFlags
//int ORIGINAL_cuDevicePrimaryCtxSetFlags( CUdevice dev, unsigned int flags ) { }

void * PTR_ORIGINAL_cuDevicePrimaryCtxSetFlags;
// This is the call that will take the place of the original
int INTER_cuDevicePrimaryCtxSetFlags( CUdevice dev, unsigned int flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dev,(void **)&flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDevicePrimaryCtxSetFlags, (void*) PTR_ORIGINAL_cuDevicePrimaryCtxSetFlags, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDevicePrimaryCtxGetState
//int ORIGINAL_cuDevicePrimaryCtxGetState( CUdevice dev, unsigned int * flags, int * active ) { }

void * PTR_ORIGINAL_cuDevicePrimaryCtxGetState;
// This is the call that will take the place of the original
int INTER_cuDevicePrimaryCtxGetState( CUdevice dev, unsigned int * flags, int * active ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dev,(void **)&flags,(void **)&active };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDevicePrimaryCtxGetState, (void*) PTR_ORIGINAL_cuDevicePrimaryCtxGetState, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDevicePrimaryCtxReset
//int ORIGINAL_cuDevicePrimaryCtxReset( CUdevice dev ) { }

void * PTR_ORIGINAL_cuDevicePrimaryCtxReset;
// This is the call that will take the place of the original
int INTER_cuDevicePrimaryCtxReset( CUdevice dev ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dev };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDevicePrimaryCtxReset, (void*) PTR_ORIGINAL_cuDevicePrimaryCtxReset, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxCreate
//int ORIGINAL_cuCtxCreate( CUcontext * pctx, unsigned int flags, CUdevice dev ) { }

void * PTR_ORIGINAL_cuCtxCreate;
// This is the call that will take the place of the original
int INTER_cuCtxCreate( CUcontext * pctx, unsigned int flags, CUdevice dev ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pctx,(void **)&flags,(void **)&dev };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxCreate, (void*) PTR_ORIGINAL_cuCtxCreate, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxDestroy
//int ORIGINAL_cuCtxDestroy( CUcontext ctx ) { }

void * PTR_ORIGINAL_cuCtxDestroy;
// This is the call that will take the place of the original
int INTER_cuCtxDestroy( CUcontext ctx ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&ctx };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxDestroy, (void*) PTR_ORIGINAL_cuCtxDestroy, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxPushCurrent
//int ORIGINAL_cuCtxPushCurrent( CUcontext ctx ) { }

void * PTR_ORIGINAL_cuCtxPushCurrent;
// This is the call that will take the place of the original
int INTER_cuCtxPushCurrent( CUcontext ctx ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&ctx };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxPushCurrent, (void*) PTR_ORIGINAL_cuCtxPushCurrent, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxPopCurrent
//int ORIGINAL_cuCtxPopCurrent( CUcontext * pctx ) { }

void * PTR_ORIGINAL_cuCtxPopCurrent;
// This is the call that will take the place of the original
int INTER_cuCtxPopCurrent( CUcontext * pctx ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pctx };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxPopCurrent, (void*) PTR_ORIGINAL_cuCtxPopCurrent, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxSetCurrent
//int ORIGINAL_cuCtxSetCurrent( CUcontext ctx ) { }

void * PTR_ORIGINAL_cuCtxSetCurrent;
// This is the call that will take the place of the original
int INTER_cuCtxSetCurrent( CUcontext ctx ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&ctx };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxSetCurrent, (void*) PTR_ORIGINAL_cuCtxSetCurrent, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxGetCurrent
//int ORIGINAL_cuCtxGetCurrent( CUcontext * pctx ) { }

void * PTR_ORIGINAL_cuCtxGetCurrent;
// This is the call that will take the place of the original
int INTER_cuCtxGetCurrent( CUcontext * pctx ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pctx };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxGetCurrent, (void*) PTR_ORIGINAL_cuCtxGetCurrent, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxGetDevice
//int ORIGINAL_cuCtxGetDevice( CUdevice * device ) { }

void * PTR_ORIGINAL_cuCtxGetDevice;
// This is the call that will take the place of the original
int INTER_cuCtxGetDevice( CUdevice * device ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&device };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxGetDevice, (void*) PTR_ORIGINAL_cuCtxGetDevice, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxGetFlags
//int ORIGINAL_cuCtxGetFlags( unsigned int * flags ) { }

void * PTR_ORIGINAL_cuCtxGetFlags;
// This is the call that will take the place of the original
int INTER_cuCtxGetFlags( unsigned int * flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxGetFlags, (void*) PTR_ORIGINAL_cuCtxGetFlags, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxSynchronize
//int ORIGINAL_cuCtxSynchronize( void  ) { }

void * PTR_ORIGINAL_cuCtxSynchronize;
// This is the call that will take the place of the original
int INTER_cuCtxSynchronize( void  ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = {  };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxSynchronize, (void*) PTR_ORIGINAL_cuCtxSynchronize, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxSetLimit
//int ORIGINAL_cuCtxSetLimit( CUlimit limit, size_t value ) { }

void * PTR_ORIGINAL_cuCtxSetLimit;
// This is the call that will take the place of the original
int INTER_cuCtxSetLimit( CUlimit limit, size_t value ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&limit,(void **)&value };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxSetLimit, (void*) PTR_ORIGINAL_cuCtxSetLimit, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxGetLimit
//int ORIGINAL_cuCtxGetLimit( size_t * pvalue, CUlimit limit ) { }

void * PTR_ORIGINAL_cuCtxGetLimit;
// This is the call that will take the place of the original
int INTER_cuCtxGetLimit( size_t * pvalue, CUlimit limit ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pvalue,(void **)&limit };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxGetLimit, (void*) PTR_ORIGINAL_cuCtxGetLimit, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxGetCacheConfig
//int ORIGINAL_cuCtxGetCacheConfig( CUfunc_cache * pconfig ) { }

void * PTR_ORIGINAL_cuCtxGetCacheConfig;
// This is the call that will take the place of the original
int INTER_cuCtxGetCacheConfig( CUfunc_cache * pconfig ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pconfig };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxGetCacheConfig, (void*) PTR_ORIGINAL_cuCtxGetCacheConfig, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxSetCacheConfig
//int ORIGINAL_cuCtxSetCacheConfig( CUfunc_cache config ) { }

void * PTR_ORIGINAL_cuCtxSetCacheConfig;
// This is the call that will take the place of the original
int INTER_cuCtxSetCacheConfig( CUfunc_cache config ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&config };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxSetCacheConfig, (void*) PTR_ORIGINAL_cuCtxSetCacheConfig, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxGetSharedMemConfig
//int ORIGINAL_cuCtxGetSharedMemConfig( CUsharedconfig * pConfig ) { }

void * PTR_ORIGINAL_cuCtxGetSharedMemConfig;
// This is the call that will take the place of the original
int INTER_cuCtxGetSharedMemConfig( CUsharedconfig * pConfig ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pConfig };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxGetSharedMemConfig, (void*) PTR_ORIGINAL_cuCtxGetSharedMemConfig, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxSetSharedMemConfig
//int ORIGINAL_cuCtxSetSharedMemConfig( CUsharedconfig config ) { }

void * PTR_ORIGINAL_cuCtxSetSharedMemConfig;
// This is the call that will take the place of the original
int INTER_cuCtxSetSharedMemConfig( CUsharedconfig config ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&config };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxSetSharedMemConfig, (void*) PTR_ORIGINAL_cuCtxSetSharedMemConfig, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxGetApiVersion
//int ORIGINAL_cuCtxGetApiVersion( CUcontext ctx, unsigned int * version ) { }

void * PTR_ORIGINAL_cuCtxGetApiVersion;
// This is the call that will take the place of the original
int INTER_cuCtxGetApiVersion( CUcontext ctx, unsigned int * version ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&ctx,(void **)&version };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxGetApiVersion, (void*) PTR_ORIGINAL_cuCtxGetApiVersion, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxGetStreamPriorityRange
//int ORIGINAL_cuCtxGetStreamPriorityRange( int * leastPriority, int * greatestPriority ) { }

void * PTR_ORIGINAL_cuCtxGetStreamPriorityRange;
// This is the call that will take the place of the original
int INTER_cuCtxGetStreamPriorityRange( int * leastPriority, int * greatestPriority ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&leastPriority,(void **)&greatestPriority };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxGetStreamPriorityRange, (void*) PTR_ORIGINAL_cuCtxGetStreamPriorityRange, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxAttach
//int ORIGINAL_cuCtxAttach( CUcontext * pctx, unsigned int flags ) { }

void * PTR_ORIGINAL_cuCtxAttach;
// This is the call that will take the place of the original
int INTER_cuCtxAttach( CUcontext * pctx, unsigned int flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pctx,(void **)&flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxAttach, (void*) PTR_ORIGINAL_cuCtxAttach, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxDetach
//int ORIGINAL_cuCtxDetach( CUcontext ctx ) { }

void * PTR_ORIGINAL_cuCtxDetach;
// This is the call that will take the place of the original
int INTER_cuCtxDetach( CUcontext ctx ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&ctx };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxDetach, (void*) PTR_ORIGINAL_cuCtxDetach, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuModuleLoad
//int ORIGINAL_cuModuleLoad( CUmodule * module, const char * fname ) { }

void * PTR_ORIGINAL_cuModuleLoad;
// This is the call that will take the place of the original
int INTER_cuModuleLoad( CUmodule * module, const char * fname ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&module,(void **)&fname };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuModuleLoad, (void*) PTR_ORIGINAL_cuModuleLoad, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuModuleLoadData
//int ORIGINAL_cuModuleLoadData( CUmodule * module, const void * image ) { }

void * PTR_ORIGINAL_cuModuleLoadData;
// This is the call that will take the place of the original
int INTER_cuModuleLoadData( CUmodule * module, const void * image ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&module,(void **)&image };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuModuleLoadData, (void*) PTR_ORIGINAL_cuModuleLoadData, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuModuleLoadDataEx
//int ORIGINAL_cuModuleLoadDataEx( CUmodule * module, const void * image, unsigned int numOptions, CUjit_option * options, void * * optionValues ) { }

void * PTR_ORIGINAL_cuModuleLoadDataEx;
// This is the call that will take the place of the original
int INTER_cuModuleLoadDataEx( CUmodule * module, const void * image, unsigned int numOptions, CUjit_option * options, void * * optionValues ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&module,(void **)&image,(void **)&numOptions,(void **)&options,(void **)&optionValues };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuModuleLoadDataEx, (void*) PTR_ORIGINAL_cuModuleLoadDataEx, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuModuleLoadFatBinary
//int ORIGINAL_cuModuleLoadFatBinary( CUmodule * module, const void * fatCubin ) { }

void * PTR_ORIGINAL_cuModuleLoadFatBinary;
// This is the call that will take the place of the original
int INTER_cuModuleLoadFatBinary( CUmodule * module, const void * fatCubin ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&module,(void **)&fatCubin };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuModuleLoadFatBinary, (void*) PTR_ORIGINAL_cuModuleLoadFatBinary, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuModuleUnload
//int ORIGINAL_cuModuleUnload( CUmodule hmod ) { }

void * PTR_ORIGINAL_cuModuleUnload;
// This is the call that will take the place of the original
int INTER_cuModuleUnload( CUmodule hmod ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hmod };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuModuleUnload, (void*) PTR_ORIGINAL_cuModuleUnload, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuModuleGetFunction
//int ORIGINAL_cuModuleGetFunction( CUfunction * hfunc, CUmodule hmod, const char * name ) { }

void * PTR_ORIGINAL_cuModuleGetFunction;
// This is the call that will take the place of the original
int INTER_cuModuleGetFunction( CUfunction * hfunc, CUmodule hmod, const char * name ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hfunc,(void **)&hmod,(void **)&name };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuModuleGetFunction, (void*) PTR_ORIGINAL_cuModuleGetFunction, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuModuleGetGlobal
//int ORIGINAL_cuModuleGetGlobal( CUdeviceptr * dptr, size_t * bytes, CUmodule hmod, const char * name ) { }

void * PTR_ORIGINAL_cuModuleGetGlobal;
// This is the call that will take the place of the original
int INTER_cuModuleGetGlobal( CUdeviceptr * dptr, size_t * bytes, CUmodule hmod, const char * name ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dptr,(void **)&bytes,(void **)&hmod,(void **)&name };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuModuleGetGlobal, (void*) PTR_ORIGINAL_cuModuleGetGlobal, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuModuleGetTexRef
//int ORIGINAL_cuModuleGetTexRef( CUtexref * pTexRef, CUmodule hmod, const char * name ) { }

void * PTR_ORIGINAL_cuModuleGetTexRef;
// This is the call that will take the place of the original
int INTER_cuModuleGetTexRef( CUtexref * pTexRef, CUmodule hmod, const char * name ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pTexRef,(void **)&hmod,(void **)&name };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuModuleGetTexRef, (void*) PTR_ORIGINAL_cuModuleGetTexRef, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuModuleGetSurfRef
//int ORIGINAL_cuModuleGetSurfRef( CUsurfref * pSurfRef, CUmodule hmod, const char * name ) { }

void * PTR_ORIGINAL_cuModuleGetSurfRef;
// This is the call that will take the place of the original
int INTER_cuModuleGetSurfRef( CUsurfref * pSurfRef, CUmodule hmod, const char * name ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pSurfRef,(void **)&hmod,(void **)&name };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuModuleGetSurfRef, (void*) PTR_ORIGINAL_cuModuleGetSurfRef, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuLinkCreate
//int ORIGINAL_cuLinkCreate( unsigned int numOptions, CUjit_option * options, void * * optionValues, CUlinkState * stateOut ) { }

void * PTR_ORIGINAL_cuLinkCreate;
// This is the call that will take the place of the original
int INTER_cuLinkCreate( unsigned int numOptions, CUjit_option * options, void * * optionValues, CUlinkState * stateOut ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&numOptions,(void **)&options,(void **)&optionValues,(void **)&stateOut };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuLinkCreate, (void*) PTR_ORIGINAL_cuLinkCreate, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuLinkAddData
//int ORIGINAL_cuLinkAddData( CUlinkState state, CUjitInputType type, void * data, size_t size, const char * name, unsigned int numOptions, CUjit_option * options, void * * optionValues ) { }

void * PTR_ORIGINAL_cuLinkAddData;
// This is the call that will take the place of the original
int INTER_cuLinkAddData( CUlinkState state, CUjitInputType type, void * data, size_t size, const char * name, unsigned int numOptions, CUjit_option * options, void * * optionValues ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&state,(void **)&type,(void **)&data,(void **)&size,(void **)&name,(void **)&numOptions,(void **)&options,(void **)&optionValues };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuLinkAddData, (void*) PTR_ORIGINAL_cuLinkAddData, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuLinkAddFile
//int ORIGINAL_cuLinkAddFile( CUlinkState state, CUjitInputType type, const char * path, unsigned int numOptions, CUjit_option * options, void * * optionValues ) { }

void * PTR_ORIGINAL_cuLinkAddFile;
// This is the call that will take the place of the original
int INTER_cuLinkAddFile( CUlinkState state, CUjitInputType type, const char * path, unsigned int numOptions, CUjit_option * options, void * * optionValues ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&state,(void **)&type,(void **)&path,(void **)&numOptions,(void **)&options,(void **)&optionValues };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuLinkAddFile, (void*) PTR_ORIGINAL_cuLinkAddFile, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuLinkComplete
//int ORIGINAL_cuLinkComplete( CUlinkState state, void * * cubinOut, size_t * sizeOut ) { }

void * PTR_ORIGINAL_cuLinkComplete;
// This is the call that will take the place of the original
int INTER_cuLinkComplete( CUlinkState state, void * * cubinOut, size_t * sizeOut ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&state,(void **)&cubinOut,(void **)&sizeOut };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuLinkComplete, (void*) PTR_ORIGINAL_cuLinkComplete, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuLinkDestroy
//int ORIGINAL_cuLinkDestroy( CUlinkState state ) { }

void * PTR_ORIGINAL_cuLinkDestroy;
// This is the call that will take the place of the original
int INTER_cuLinkDestroy( CUlinkState state ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&state };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuLinkDestroy, (void*) PTR_ORIGINAL_cuLinkDestroy, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemGetInfo
//int ORIGINAL_cuMemGetInfo( size_t * free, size_t * total ) { }

void * PTR_ORIGINAL_cuMemGetInfo;
// This is the call that will take the place of the original
int INTER_cuMemGetInfo( size_t * free, size_t * total ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&free,(void **)&total };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemGetInfo, (void*) PTR_ORIGINAL_cuMemGetInfo, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemAlloc
//int ORIGINAL_cuMemAlloc( CUdeviceptr * dptr, size_t bytesize ) { }

void * PTR_ORIGINAL_cuMemAlloc;
// This is the call that will take the place of the original
int INTER_cuMemAlloc( CUdeviceptr * dptr, size_t bytesize ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dptr,(void **)&bytesize };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemAlloc, (void*) PTR_ORIGINAL_cuMemAlloc, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemAllocPitch
//int ORIGINAL_cuMemAllocPitch( CUdeviceptr * dptr, size_t * pPitch, size_t WidthInBytes, size_t Height, unsigned int ElementSizeBytes ) { }

void * PTR_ORIGINAL_cuMemAllocPitch;
// This is the call that will take the place of the original
int INTER_cuMemAllocPitch( CUdeviceptr * dptr, size_t * pPitch, size_t WidthInBytes, size_t Height, unsigned int ElementSizeBytes ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dptr,(void **)&pPitch,(void **)&WidthInBytes,(void **)&Height,(void **)&ElementSizeBytes };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemAllocPitch, (void*) PTR_ORIGINAL_cuMemAllocPitch, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemFree
//int ORIGINAL_cuMemFree( CUdeviceptr dptr ) { }

void * PTR_ORIGINAL_cuMemFree;
// This is the call that will take the place of the original
int INTER_cuMemFree( CUdeviceptr dptr ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dptr };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemFree, (void*) PTR_ORIGINAL_cuMemFree, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemGetAddressRange
//int ORIGINAL_cuMemGetAddressRange( CUdeviceptr * pbase, size_t * psize, CUdeviceptr dptr ) { }

void * PTR_ORIGINAL_cuMemGetAddressRange;
// This is the call that will take the place of the original
int INTER_cuMemGetAddressRange( CUdeviceptr * pbase, size_t * psize, CUdeviceptr dptr ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pbase,(void **)&psize,(void **)&dptr };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemGetAddressRange, (void*) PTR_ORIGINAL_cuMemGetAddressRange, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemAllocHost
//int ORIGINAL_cuMemAllocHost( void * * pp, size_t bytesize ) { }

void * PTR_ORIGINAL_cuMemAllocHost;
// This is the call that will take the place of the original
int INTER_cuMemAllocHost( void * * pp, size_t bytesize ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pp,(void **)&bytesize };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemAllocHost, (void*) PTR_ORIGINAL_cuMemAllocHost, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemFreeHost
//int ORIGINAL_cuMemFreeHost( void * p ) { }

void * PTR_ORIGINAL_cuMemFreeHost;
// This is the call that will take the place of the original
int INTER_cuMemFreeHost( void * p ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&p };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemFreeHost, (void*) PTR_ORIGINAL_cuMemFreeHost, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemHostAlloc
//int ORIGINAL_cuMemHostAlloc( void * * pp, size_t bytesize, unsigned int Flags ) { }

void * PTR_ORIGINAL_cuMemHostAlloc;
// This is the call that will take the place of the original
int INTER_cuMemHostAlloc( void * * pp, size_t bytesize, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pp,(void **)&bytesize,(void **)&Flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemHostAlloc, (void*) PTR_ORIGINAL_cuMemHostAlloc, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemHostGetDevicePointer
//int ORIGINAL_cuMemHostGetDevicePointer( CUdeviceptr * pdptr, void * p, unsigned int Flags ) { }

void * PTR_ORIGINAL_cuMemHostGetDevicePointer;
// This is the call that will take the place of the original
int INTER_cuMemHostGetDevicePointer( CUdeviceptr * pdptr, void * p, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pdptr,(void **)&p,(void **)&Flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemHostGetDevicePointer, (void*) PTR_ORIGINAL_cuMemHostGetDevicePointer, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemHostGetFlags
//int ORIGINAL_cuMemHostGetFlags( unsigned int * pFlags, void * p ) { }

void * PTR_ORIGINAL_cuMemHostGetFlags;
// This is the call that will take the place of the original
int INTER_cuMemHostGetFlags( unsigned int * pFlags, void * p ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pFlags,(void **)&p };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemHostGetFlags, (void*) PTR_ORIGINAL_cuMemHostGetFlags, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemAllocManaged
//int ORIGINAL_cuMemAllocManaged( CUdeviceptr * dptr, size_t bytesize, unsigned int flags ) { }

void * PTR_ORIGINAL_cuMemAllocManaged;
// This is the call that will take the place of the original
int INTER_cuMemAllocManaged( CUdeviceptr * dptr, size_t bytesize, unsigned int flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dptr,(void **)&bytesize,(void **)&flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemAllocManaged, (void*) PTR_ORIGINAL_cuMemAllocManaged, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDeviceGetByPCIBusId
//int ORIGINAL_cuDeviceGetByPCIBusId( CUdevice * dev, const char * pciBusId ) { }

void * PTR_ORIGINAL_cuDeviceGetByPCIBusId;
// This is the call that will take the place of the original
int INTER_cuDeviceGetByPCIBusId( CUdevice * dev, const char * pciBusId ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dev,(void **)&pciBusId };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDeviceGetByPCIBusId, (void*) PTR_ORIGINAL_cuDeviceGetByPCIBusId, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDeviceGetPCIBusId
//int ORIGINAL_cuDeviceGetPCIBusId( char * pciBusId, int len, CUdevice dev ) { }

void * PTR_ORIGINAL_cuDeviceGetPCIBusId;
// This is the call that will take the place of the original
int INTER_cuDeviceGetPCIBusId( char * pciBusId, int len, CUdevice dev ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pciBusId,(void **)&len,(void **)&dev };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDeviceGetPCIBusId, (void*) PTR_ORIGINAL_cuDeviceGetPCIBusId, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuIpcGetEventHandle
//int ORIGINAL_cuIpcGetEventHandle( CUipcEventHandle * pHandle, CUevent event ) { }

void * PTR_ORIGINAL_cuIpcGetEventHandle;
// This is the call that will take the place of the original
int INTER_cuIpcGetEventHandle( CUipcEventHandle * pHandle, CUevent event ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pHandle,(void **)&event };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuIpcGetEventHandle, (void*) PTR_ORIGINAL_cuIpcGetEventHandle, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuIpcOpenEventHandle
//int ORIGINAL_cuIpcOpenEventHandle( CUevent * phEvent, CUipcEventHandle handle ) { }

void * PTR_ORIGINAL_cuIpcOpenEventHandle;
// This is the call that will take the place of the original
int INTER_cuIpcOpenEventHandle( CUevent * phEvent, CUipcEventHandle handle ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&phEvent,(void **)&handle };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuIpcOpenEventHandle, (void*) PTR_ORIGINAL_cuIpcOpenEventHandle, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuIpcGetMemHandle
//int ORIGINAL_cuIpcGetMemHandle( CUipcMemHandle * pHandle, CUdeviceptr dptr ) { }

void * PTR_ORIGINAL_cuIpcGetMemHandle;
// This is the call that will take the place of the original
int INTER_cuIpcGetMemHandle( CUipcMemHandle * pHandle, CUdeviceptr dptr ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pHandle,(void **)&dptr };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuIpcGetMemHandle, (void*) PTR_ORIGINAL_cuIpcGetMemHandle, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuIpcOpenMemHandle
//int ORIGINAL_cuIpcOpenMemHandle( CUdeviceptr * pdptr, CUipcMemHandle handle, unsigned int Flags ) { }

void * PTR_ORIGINAL_cuIpcOpenMemHandle;
// This is the call that will take the place of the original
int INTER_cuIpcOpenMemHandle( CUdeviceptr * pdptr, CUipcMemHandle handle, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pdptr,(void **)&handle,(void **)&Flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuIpcOpenMemHandle, (void*) PTR_ORIGINAL_cuIpcOpenMemHandle, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuIpcCloseMemHandle
//int ORIGINAL_cuIpcCloseMemHandle( CUdeviceptr dptr ) { }

void * PTR_ORIGINAL_cuIpcCloseMemHandle;
// This is the call that will take the place of the original
int INTER_cuIpcCloseMemHandle( CUdeviceptr dptr ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dptr };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuIpcCloseMemHandle, (void*) PTR_ORIGINAL_cuIpcCloseMemHandle, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemHostRegister
//int ORIGINAL_cuMemHostRegister( void * p, size_t bytesize, unsigned int Flags ) { }

void * PTR_ORIGINAL_cuMemHostRegister;
// This is the call that will take the place of the original
int INTER_cuMemHostRegister( void * p, size_t bytesize, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&p,(void **)&bytesize,(void **)&Flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemHostRegister, (void*) PTR_ORIGINAL_cuMemHostRegister, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemHostUnregister
//int ORIGINAL_cuMemHostUnregister( void * p ) { }

void * PTR_ORIGINAL_cuMemHostUnregister;
// This is the call that will take the place of the original
int INTER_cuMemHostUnregister( void * p ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&p };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemHostUnregister, (void*) PTR_ORIGINAL_cuMemHostUnregister, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpy
//int ORIGINAL_cuMemcpy( CUdeviceptr dst, CUdeviceptr src, size_t ByteCount ) { }

void * PTR_ORIGINAL_cuMemcpy;
// This is the call that will take the place of the original
int INTER_cuMemcpy( CUdeviceptr dst, CUdeviceptr src, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dst,(void **)&src,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpy, (void*) PTR_ORIGINAL_cuMemcpy, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyPeer
//int ORIGINAL_cuMemcpyPeer( CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount ) { }

void * PTR_ORIGINAL_cuMemcpyPeer;
// This is the call that will take the place of the original
int INTER_cuMemcpyPeer( CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&dstContext,(void **)&srcDevice,(void **)&srcContext,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyPeer, (void*) PTR_ORIGINAL_cuMemcpyPeer, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyHtoD
//int ORIGINAL_cuMemcpyHtoD( CUdeviceptr dstDevice, const void * srcHost, size_t ByteCount ) { }

void * PTR_ORIGINAL_cuMemcpyHtoD;
// This is the call that will take the place of the original
int INTER_cuMemcpyHtoD( CUdeviceptr dstDevice, const void * srcHost, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&srcHost,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyHtoD, (void*) PTR_ORIGINAL_cuMemcpyHtoD, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyDtoH
//int ORIGINAL_cuMemcpyDtoH( void * dstHost, CUdeviceptr srcDevice, size_t ByteCount ) { }

void * PTR_ORIGINAL_cuMemcpyDtoH;
// This is the call that will take the place of the original
int INTER_cuMemcpyDtoH( void * dstHost, CUdeviceptr srcDevice, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstHost,(void **)&srcDevice,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyDtoH, (void*) PTR_ORIGINAL_cuMemcpyDtoH, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyDtoD
//int ORIGINAL_cuMemcpyDtoD( CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount ) { }

void * PTR_ORIGINAL_cuMemcpyDtoD;
// This is the call that will take the place of the original
int INTER_cuMemcpyDtoD( CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&srcDevice,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyDtoD, (void*) PTR_ORIGINAL_cuMemcpyDtoD, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyDtoA
//int ORIGINAL_cuMemcpyDtoA( CUarray dstArray, size_t dstOffset, CUdeviceptr srcDevice, size_t ByteCount ) { }

void * PTR_ORIGINAL_cuMemcpyDtoA;
// This is the call that will take the place of the original
int INTER_cuMemcpyDtoA( CUarray dstArray, size_t dstOffset, CUdeviceptr srcDevice, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstArray,(void **)&dstOffset,(void **)&srcDevice,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyDtoA, (void*) PTR_ORIGINAL_cuMemcpyDtoA, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyAtoD
//int ORIGINAL_cuMemcpyAtoD( CUdeviceptr dstDevice, CUarray srcArray, size_t srcOffset, size_t ByteCount ) { }

void * PTR_ORIGINAL_cuMemcpyAtoD;
// This is the call that will take the place of the original
int INTER_cuMemcpyAtoD( CUdeviceptr dstDevice, CUarray srcArray, size_t srcOffset, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&srcArray,(void **)&srcOffset,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyAtoD, (void*) PTR_ORIGINAL_cuMemcpyAtoD, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyHtoA
//int ORIGINAL_cuMemcpyHtoA( CUarray dstArray, size_t dstOffset, const void * srcHost, size_t ByteCount ) { }

void * PTR_ORIGINAL_cuMemcpyHtoA;
// This is the call that will take the place of the original
int INTER_cuMemcpyHtoA( CUarray dstArray, size_t dstOffset, const void * srcHost, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstArray,(void **)&dstOffset,(void **)&srcHost,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyHtoA, (void*) PTR_ORIGINAL_cuMemcpyHtoA, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyAtoH
//int ORIGINAL_cuMemcpyAtoH( void * dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount ) { }

void * PTR_ORIGINAL_cuMemcpyAtoH;
// This is the call that will take the place of the original
int INTER_cuMemcpyAtoH( void * dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstHost,(void **)&srcArray,(void **)&srcOffset,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyAtoH, (void*) PTR_ORIGINAL_cuMemcpyAtoH, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyAtoA
//int ORIGINAL_cuMemcpyAtoA( CUarray dstArray, size_t dstOffset, CUarray srcArray, size_t srcOffset, size_t ByteCount ) { }

void * PTR_ORIGINAL_cuMemcpyAtoA;
// This is the call that will take the place of the original
int INTER_cuMemcpyAtoA( CUarray dstArray, size_t dstOffset, CUarray srcArray, size_t srcOffset, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstArray,(void **)&dstOffset,(void **)&srcArray,(void **)&srcOffset,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyAtoA, (void*) PTR_ORIGINAL_cuMemcpyAtoA, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpy2D
//int ORIGINAL_cuMemcpy2D( const CUDA_MEMCPY2D * pCopy ) { }

void * PTR_ORIGINAL_cuMemcpy2D;
// This is the call that will take the place of the original
int INTER_cuMemcpy2D( const CUDA_MEMCPY2D * pCopy ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pCopy };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpy2D, (void*) PTR_ORIGINAL_cuMemcpy2D, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpy2DUnaligned
//int ORIGINAL_cuMemcpy2DUnaligned( const CUDA_MEMCPY2D * pCopy ) { }

void * PTR_ORIGINAL_cuMemcpy2DUnaligned;
// This is the call that will take the place of the original
int INTER_cuMemcpy2DUnaligned( const CUDA_MEMCPY2D * pCopy ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pCopy };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpy2DUnaligned, (void*) PTR_ORIGINAL_cuMemcpy2DUnaligned, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpy3D
//int ORIGINAL_cuMemcpy3D( const CUDA_MEMCPY3D * pCopy ) { }

void * PTR_ORIGINAL_cuMemcpy3D;
// This is the call that will take the place of the original
int INTER_cuMemcpy3D( const CUDA_MEMCPY3D * pCopy ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pCopy };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpy3D, (void*) PTR_ORIGINAL_cuMemcpy3D, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpy3DPeer
//int ORIGINAL_cuMemcpy3DPeer( const CUDA_MEMCPY3D_PEER * pCopy ) { }

void * PTR_ORIGINAL_cuMemcpy3DPeer;
// This is the call that will take the place of the original
int INTER_cuMemcpy3DPeer( const CUDA_MEMCPY3D_PEER * pCopy ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pCopy };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpy3DPeer, (void*) PTR_ORIGINAL_cuMemcpy3DPeer, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyAsync
//int ORIGINAL_cuMemcpyAsync( CUdeviceptr dst, CUdeviceptr src, size_t ByteCount, CUstream hStream ) { }

void * PTR_ORIGINAL_cuMemcpyAsync;
// This is the call that will take the place of the original
int INTER_cuMemcpyAsync( CUdeviceptr dst, CUdeviceptr src, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dst,(void **)&src,(void **)&ByteCount,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyAsync, (void*) PTR_ORIGINAL_cuMemcpyAsync, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyPeerAsync
//int ORIGINAL_cuMemcpyPeerAsync( CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount, CUstream hStream ) { }

void * PTR_ORIGINAL_cuMemcpyPeerAsync;
// This is the call that will take the place of the original
int INTER_cuMemcpyPeerAsync( CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&dstContext,(void **)&srcDevice,(void **)&srcContext,(void **)&ByteCount,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyPeerAsync, (void*) PTR_ORIGINAL_cuMemcpyPeerAsync, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyHtoDAsync
//int ORIGINAL_cuMemcpyHtoDAsync( CUdeviceptr dstDevice, const void * srcHost, size_t ByteCount, CUstream hStream ) { }

void * PTR_ORIGINAL_cuMemcpyHtoDAsync;
// This is the call that will take the place of the original
int INTER_cuMemcpyHtoDAsync( CUdeviceptr dstDevice, const void * srcHost, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&srcHost,(void **)&ByteCount,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyHtoDAsync, (void*) PTR_ORIGINAL_cuMemcpyHtoDAsync, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyDtoHAsync
//int ORIGINAL_cuMemcpyDtoHAsync( void * dstHost, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream ) { }

void * PTR_ORIGINAL_cuMemcpyDtoHAsync;
// This is the call that will take the place of the original
int INTER_cuMemcpyDtoHAsync( void * dstHost, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstHost,(void **)&srcDevice,(void **)&ByteCount,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyDtoHAsync, (void*) PTR_ORIGINAL_cuMemcpyDtoHAsync, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyDtoDAsync
//int ORIGINAL_cuMemcpyDtoDAsync( CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream ) { }

void * PTR_ORIGINAL_cuMemcpyDtoDAsync;
// This is the call that will take the place of the original
int INTER_cuMemcpyDtoDAsync( CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&srcDevice,(void **)&ByteCount,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyDtoDAsync, (void*) PTR_ORIGINAL_cuMemcpyDtoDAsync, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyHtoAAsync
//int ORIGINAL_cuMemcpyHtoAAsync( CUarray dstArray, size_t dstOffset, const void * srcHost, size_t ByteCount, CUstream hStream ) { }

void * PTR_ORIGINAL_cuMemcpyHtoAAsync;
// This is the call that will take the place of the original
int INTER_cuMemcpyHtoAAsync( CUarray dstArray, size_t dstOffset, const void * srcHost, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstArray,(void **)&dstOffset,(void **)&srcHost,(void **)&ByteCount,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyHtoAAsync, (void*) PTR_ORIGINAL_cuMemcpyHtoAAsync, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyAtoHAsync
//int ORIGINAL_cuMemcpyAtoHAsync( void * dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount, CUstream hStream ) { }

void * PTR_ORIGINAL_cuMemcpyAtoHAsync;
// This is the call that will take the place of the original
int INTER_cuMemcpyAtoHAsync( void * dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstHost,(void **)&srcArray,(void **)&srcOffset,(void **)&ByteCount,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyAtoHAsync, (void*) PTR_ORIGINAL_cuMemcpyAtoHAsync, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpy2DAsync
//int ORIGINAL_cuMemcpy2DAsync( const CUDA_MEMCPY2D * pCopy, CUstream hStream ) { }

void * PTR_ORIGINAL_cuMemcpy2DAsync;
// This is the call that will take the place of the original
int INTER_cuMemcpy2DAsync( const CUDA_MEMCPY2D * pCopy, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pCopy,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpy2DAsync, (void*) PTR_ORIGINAL_cuMemcpy2DAsync, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpy3DAsync
//int ORIGINAL_cuMemcpy3DAsync( const CUDA_MEMCPY3D * pCopy, CUstream hStream ) { }

void * PTR_ORIGINAL_cuMemcpy3DAsync;
// This is the call that will take the place of the original
int INTER_cuMemcpy3DAsync( const CUDA_MEMCPY3D * pCopy, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pCopy,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpy3DAsync, (void*) PTR_ORIGINAL_cuMemcpy3DAsync, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpy3DPeerAsync
//int ORIGINAL_cuMemcpy3DPeerAsync( const CUDA_MEMCPY3D_PEER * pCopy, CUstream hStream ) { }

void * PTR_ORIGINAL_cuMemcpy3DPeerAsync;
// This is the call that will take the place of the original
int INTER_cuMemcpy3DPeerAsync( const CUDA_MEMCPY3D_PEER * pCopy, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pCopy,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpy3DPeerAsync, (void*) PTR_ORIGINAL_cuMemcpy3DPeerAsync, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD8
//int ORIGINAL_cuMemsetD8( CUdeviceptr dstDevice, unsigned char uc, size_t N ) { }

void * PTR_ORIGINAL_cuMemsetD8;
// This is the call that will take the place of the original
int INTER_cuMemsetD8( CUdeviceptr dstDevice, unsigned char uc, size_t N ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&uc,(void **)&N };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD8, (void*) PTR_ORIGINAL_cuMemsetD8, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD16
//int ORIGINAL_cuMemsetD16( CUdeviceptr dstDevice, unsigned short us, size_t N ) { }

void * PTR_ORIGINAL_cuMemsetD16;
// This is the call that will take the place of the original
int INTER_cuMemsetD16( CUdeviceptr dstDevice, unsigned short us, size_t N ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&us,(void **)&N };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD16, (void*) PTR_ORIGINAL_cuMemsetD16, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD32
//int ORIGINAL_cuMemsetD32( CUdeviceptr dstDevice, unsigned int ui, size_t N ) { }

void * PTR_ORIGINAL_cuMemsetD32;
// This is the call that will take the place of the original
int INTER_cuMemsetD32( CUdeviceptr dstDevice, unsigned int ui, size_t N ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&ui,(void **)&N };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD32, (void*) PTR_ORIGINAL_cuMemsetD32, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD2D8
//int ORIGINAL_cuMemsetD2D8( CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height ) { }

void * PTR_ORIGINAL_cuMemsetD2D8;
// This is the call that will take the place of the original
int INTER_cuMemsetD2D8( CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&dstPitch,(void **)&uc,(void **)&Width,(void **)&Height };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD2D8, (void*) PTR_ORIGINAL_cuMemsetD2D8, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD2D16
//int ORIGINAL_cuMemsetD2D16( CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height ) { }

void * PTR_ORIGINAL_cuMemsetD2D16;
// This is the call that will take the place of the original
int INTER_cuMemsetD2D16( CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&dstPitch,(void **)&us,(void **)&Width,(void **)&Height };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD2D16, (void*) PTR_ORIGINAL_cuMemsetD2D16, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD2D32
//int ORIGINAL_cuMemsetD2D32( CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height ) { }

void * PTR_ORIGINAL_cuMemsetD2D32;
// This is the call that will take the place of the original
int INTER_cuMemsetD2D32( CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&dstPitch,(void **)&ui,(void **)&Width,(void **)&Height };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD2D32, (void*) PTR_ORIGINAL_cuMemsetD2D32, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD8Async
//int ORIGINAL_cuMemsetD8Async( CUdeviceptr dstDevice, unsigned char uc, size_t N, CUstream hStream ) { }

void * PTR_ORIGINAL_cuMemsetD8Async;
// This is the call that will take the place of the original
int INTER_cuMemsetD8Async( CUdeviceptr dstDevice, unsigned char uc, size_t N, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&uc,(void **)&N,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD8Async, (void*) PTR_ORIGINAL_cuMemsetD8Async, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD16Async
//int ORIGINAL_cuMemsetD16Async( CUdeviceptr dstDevice, unsigned short us, size_t N, CUstream hStream ) { }

void * PTR_ORIGINAL_cuMemsetD16Async;
// This is the call that will take the place of the original
int INTER_cuMemsetD16Async( CUdeviceptr dstDevice, unsigned short us, size_t N, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&us,(void **)&N,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD16Async, (void*) PTR_ORIGINAL_cuMemsetD16Async, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD32Async
//int ORIGINAL_cuMemsetD32Async( CUdeviceptr dstDevice, unsigned int ui, size_t N, CUstream hStream ) { }

void * PTR_ORIGINAL_cuMemsetD32Async;
// This is the call that will take the place of the original
int INTER_cuMemsetD32Async( CUdeviceptr dstDevice, unsigned int ui, size_t N, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&ui,(void **)&N,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD32Async, (void*) PTR_ORIGINAL_cuMemsetD32Async, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD2D8Async
//int ORIGINAL_cuMemsetD2D8Async( CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height, CUstream hStream ) { }

void * PTR_ORIGINAL_cuMemsetD2D8Async;
// This is the call that will take the place of the original
int INTER_cuMemsetD2D8Async( CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&dstPitch,(void **)&uc,(void **)&Width,(void **)&Height,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD2D8Async, (void*) PTR_ORIGINAL_cuMemsetD2D8Async, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD2D16Async
//int ORIGINAL_cuMemsetD2D16Async( CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height, CUstream hStream ) { }

void * PTR_ORIGINAL_cuMemsetD2D16Async;
// This is the call that will take the place of the original
int INTER_cuMemsetD2D16Async( CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&dstPitch,(void **)&us,(void **)&Width,(void **)&Height,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD2D16Async, (void*) PTR_ORIGINAL_cuMemsetD2D16Async, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD2D32Async
//int ORIGINAL_cuMemsetD2D32Async( CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height, CUstream hStream ) { }

void * PTR_ORIGINAL_cuMemsetD2D32Async;
// This is the call that will take the place of the original
int INTER_cuMemsetD2D32Async( CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&dstPitch,(void **)&ui,(void **)&Width,(void **)&Height,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD2D32Async, (void*) PTR_ORIGINAL_cuMemsetD2D32Async, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuArrayCreate
//int ORIGINAL_cuArrayCreate( CUarray * pHandle, const CUDA_ARRAY_DESCRIPTOR * pAllocateArray ) { }

void * PTR_ORIGINAL_cuArrayCreate;
// This is the call that will take the place of the original
int INTER_cuArrayCreate( CUarray * pHandle, const CUDA_ARRAY_DESCRIPTOR * pAllocateArray ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pHandle,(void **)&pAllocateArray };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuArrayCreate, (void*) PTR_ORIGINAL_cuArrayCreate, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuArrayGetDescriptor
//int ORIGINAL_cuArrayGetDescriptor( CUDA_ARRAY_DESCRIPTOR * pArrayDescriptor, CUarray hArray ) { }

void * PTR_ORIGINAL_cuArrayGetDescriptor;
// This is the call that will take the place of the original
int INTER_cuArrayGetDescriptor( CUDA_ARRAY_DESCRIPTOR * pArrayDescriptor, CUarray hArray ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pArrayDescriptor,(void **)&hArray };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuArrayGetDescriptor, (void*) PTR_ORIGINAL_cuArrayGetDescriptor, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuArrayDestroy
//int ORIGINAL_cuArrayDestroy( CUarray hArray ) { }

void * PTR_ORIGINAL_cuArrayDestroy;
// This is the call that will take the place of the original
int INTER_cuArrayDestroy( CUarray hArray ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hArray };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuArrayDestroy, (void*) PTR_ORIGINAL_cuArrayDestroy, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuArray3DCreate
//int ORIGINAL_cuArray3DCreate( CUarray * pHandle, const CUDA_ARRAY3D_DESCRIPTOR * pAllocateArray ) { }

void * PTR_ORIGINAL_cuArray3DCreate;
// This is the call that will take the place of the original
int INTER_cuArray3DCreate( CUarray * pHandle, const CUDA_ARRAY3D_DESCRIPTOR * pAllocateArray ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pHandle,(void **)&pAllocateArray };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuArray3DCreate, (void*) PTR_ORIGINAL_cuArray3DCreate, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuArray3DGetDescriptor
//int ORIGINAL_cuArray3DGetDescriptor( CUDA_ARRAY3D_DESCRIPTOR * pArrayDescriptor, CUarray hArray ) { }

void * PTR_ORIGINAL_cuArray3DGetDescriptor;
// This is the call that will take the place of the original
int INTER_cuArray3DGetDescriptor( CUDA_ARRAY3D_DESCRIPTOR * pArrayDescriptor, CUarray hArray ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pArrayDescriptor,(void **)&hArray };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuArray3DGetDescriptor, (void*) PTR_ORIGINAL_cuArray3DGetDescriptor, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMipmappedArrayCreate
//int ORIGINAL_cuMipmappedArrayCreate( CUmipmappedArray * pHandle, const CUDA_ARRAY3D_DESCRIPTOR * pMipmappedArrayDesc, unsigned int numMipmapLevels ) { }

void * PTR_ORIGINAL_cuMipmappedArrayCreate;
// This is the call that will take the place of the original
int INTER_cuMipmappedArrayCreate( CUmipmappedArray * pHandle, const CUDA_ARRAY3D_DESCRIPTOR * pMipmappedArrayDesc, unsigned int numMipmapLevels ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pHandle,(void **)&pMipmappedArrayDesc,(void **)&numMipmapLevels };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMipmappedArrayCreate, (void*) PTR_ORIGINAL_cuMipmappedArrayCreate, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMipmappedArrayGetLevel
//int ORIGINAL_cuMipmappedArrayGetLevel( CUarray * pLevelArray, CUmipmappedArray hMipmappedArray, unsigned int level ) { }

void * PTR_ORIGINAL_cuMipmappedArrayGetLevel;
// This is the call that will take the place of the original
int INTER_cuMipmappedArrayGetLevel( CUarray * pLevelArray, CUmipmappedArray hMipmappedArray, unsigned int level ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pLevelArray,(void **)&hMipmappedArray,(void **)&level };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMipmappedArrayGetLevel, (void*) PTR_ORIGINAL_cuMipmappedArrayGetLevel, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMipmappedArrayDestroy
//int ORIGINAL_cuMipmappedArrayDestroy( CUmipmappedArray hMipmappedArray ) { }

void * PTR_ORIGINAL_cuMipmappedArrayDestroy;
// This is the call that will take the place of the original
int INTER_cuMipmappedArrayDestroy( CUmipmappedArray hMipmappedArray ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hMipmappedArray };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMipmappedArrayDestroy, (void*) PTR_ORIGINAL_cuMipmappedArrayDestroy, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuPointerGetAttribute
//int ORIGINAL_cuPointerGetAttribute( void * data, CUpointer_attribute attribute, CUdeviceptr ptr ) { }

void * PTR_ORIGINAL_cuPointerGetAttribute;
// This is the call that will take the place of the original
int INTER_cuPointerGetAttribute( void * data, CUpointer_attribute attribute, CUdeviceptr ptr ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&data,(void **)&attribute,(void **)&ptr };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuPointerGetAttribute, (void*) PTR_ORIGINAL_cuPointerGetAttribute, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemPrefetchAsync
//int ORIGINAL_cuMemPrefetchAsync( CUdeviceptr devPtr, size_t count, CUdevice dstDevice, CUstream hStream ) { }

void * PTR_ORIGINAL_cuMemPrefetchAsync;
// This is the call that will take the place of the original
int INTER_cuMemPrefetchAsync( CUdeviceptr devPtr, size_t count, CUdevice dstDevice, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&devPtr,(void **)&count,(void **)&dstDevice,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemPrefetchAsync, (void*) PTR_ORIGINAL_cuMemPrefetchAsync, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemAdvise
//int ORIGINAL_cuMemAdvise( CUdeviceptr devPtr, size_t count, CUmem_advise advice, CUdevice device ) { }

void * PTR_ORIGINAL_cuMemAdvise;
// This is the call that will take the place of the original
int INTER_cuMemAdvise( CUdeviceptr devPtr, size_t count, CUmem_advise advice, CUdevice device ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&devPtr,(void **)&count,(void **)&advice,(void **)&device };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemAdvise, (void*) PTR_ORIGINAL_cuMemAdvise, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemRangeGetAttribute
//int ORIGINAL_cuMemRangeGetAttribute( void * data, size_t dataSize, CUmem_range_attribute attribute, CUdeviceptr devPtr, size_t count ) { }

void * PTR_ORIGINAL_cuMemRangeGetAttribute;
// This is the call that will take the place of the original
int INTER_cuMemRangeGetAttribute( void * data, size_t dataSize, CUmem_range_attribute attribute, CUdeviceptr devPtr, size_t count ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&data,(void **)&dataSize,(void **)&attribute,(void **)&devPtr,(void **)&count };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemRangeGetAttribute, (void*) PTR_ORIGINAL_cuMemRangeGetAttribute, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemRangeGetAttributes
//int ORIGINAL_cuMemRangeGetAttributes( void * * data, size_t * dataSizes, CUmem_range_attribute * attributes, size_t numAttributes, CUdeviceptr devPtr, size_t count ) { }

void * PTR_ORIGINAL_cuMemRangeGetAttributes;
// This is the call that will take the place of the original
int INTER_cuMemRangeGetAttributes( void * * data, size_t * dataSizes, CUmem_range_attribute * attributes, size_t numAttributes, CUdeviceptr devPtr, size_t count ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&data,(void **)&dataSizes,(void **)&attributes,(void **)&numAttributes,(void **)&devPtr,(void **)&count };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemRangeGetAttributes, (void*) PTR_ORIGINAL_cuMemRangeGetAttributes, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuPointerSetAttribute
//int ORIGINAL_cuPointerSetAttribute( const void * value, CUpointer_attribute attribute, CUdeviceptr ptr ) { }

void * PTR_ORIGINAL_cuPointerSetAttribute;
// This is the call that will take the place of the original
int INTER_cuPointerSetAttribute( const void * value, CUpointer_attribute attribute, CUdeviceptr ptr ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&value,(void **)&attribute,(void **)&ptr };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuPointerSetAttribute, (void*) PTR_ORIGINAL_cuPointerSetAttribute, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuPointerGetAttributes
//int ORIGINAL_cuPointerGetAttributes( unsigned int numAttributes, CUpointer_attribute * attributes, void * * data, CUdeviceptr ptr ) { }

void * PTR_ORIGINAL_cuPointerGetAttributes;
// This is the call that will take the place of the original
int INTER_cuPointerGetAttributes( unsigned int numAttributes, CUpointer_attribute * attributes, void * * data, CUdeviceptr ptr ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&numAttributes,(void **)&attributes,(void **)&data,(void **)&ptr };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuPointerGetAttributes, (void*) PTR_ORIGINAL_cuPointerGetAttributes, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuStreamCreate
//int ORIGINAL_cuStreamCreate( CUstream * phStream, unsigned int Flags ) { }

void * PTR_ORIGINAL_cuStreamCreate;
// This is the call that will take the place of the original
int INTER_cuStreamCreate( CUstream * phStream, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&phStream,(void **)&Flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuStreamCreate, (void*) PTR_ORIGINAL_cuStreamCreate, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuStreamCreateWithPriority
//int ORIGINAL_cuStreamCreateWithPriority( CUstream * phStream, unsigned int flags, int priority ) { }

void * PTR_ORIGINAL_cuStreamCreateWithPriority;
// This is the call that will take the place of the original
int INTER_cuStreamCreateWithPriority( CUstream * phStream, unsigned int flags, int priority ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&phStream,(void **)&flags,(void **)&priority };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuStreamCreateWithPriority, (void*) PTR_ORIGINAL_cuStreamCreateWithPriority, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuStreamGetPriority
//int ORIGINAL_cuStreamGetPriority( CUstream hStream, int * priority ) { }

void * PTR_ORIGINAL_cuStreamGetPriority;
// This is the call that will take the place of the original
int INTER_cuStreamGetPriority( CUstream hStream, int * priority ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hStream,(void **)&priority };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuStreamGetPriority, (void*) PTR_ORIGINAL_cuStreamGetPriority, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuStreamGetFlags
//int ORIGINAL_cuStreamGetFlags( CUstream hStream, unsigned int * flags ) { }

void * PTR_ORIGINAL_cuStreamGetFlags;
// This is the call that will take the place of the original
int INTER_cuStreamGetFlags( CUstream hStream, unsigned int * flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hStream,(void **)&flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuStreamGetFlags, (void*) PTR_ORIGINAL_cuStreamGetFlags, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuStreamWaitEvent
//int ORIGINAL_cuStreamWaitEvent( CUstream hStream, CUevent hEvent, unsigned int Flags ) { }

void * PTR_ORIGINAL_cuStreamWaitEvent;
// This is the call that will take the place of the original
int INTER_cuStreamWaitEvent( CUstream hStream, CUevent hEvent, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hStream,(void **)&hEvent,(void **)&Flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuStreamWaitEvent, (void*) PTR_ORIGINAL_cuStreamWaitEvent, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuStreamAddCallback
//int ORIGINAL_cuStreamAddCallback( CUstream hStream, CUstreamCallback callback, void * userData, unsigned int flags ) { }

void * PTR_ORIGINAL_cuStreamAddCallback;
// This is the call that will take the place of the original
int INTER_cuStreamAddCallback( CUstream hStream, CUstreamCallback callback, void * userData, unsigned int flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hStream,(void **)&callback,(void **)&userData,(void **)&flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuStreamAddCallback, (void*) PTR_ORIGINAL_cuStreamAddCallback, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuStreamAttachMemAsync
//int ORIGINAL_cuStreamAttachMemAsync( CUstream hStream, CUdeviceptr dptr, size_t length, unsigned int flags ) { }

void * PTR_ORIGINAL_cuStreamAttachMemAsync;
// This is the call that will take the place of the original
int INTER_cuStreamAttachMemAsync( CUstream hStream, CUdeviceptr dptr, size_t length, unsigned int flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hStream,(void **)&dptr,(void **)&length,(void **)&flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuStreamAttachMemAsync, (void*) PTR_ORIGINAL_cuStreamAttachMemAsync, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuStreamQuery
//int ORIGINAL_cuStreamQuery( CUstream hStream ) { }

void * PTR_ORIGINAL_cuStreamQuery;
// This is the call that will take the place of the original
int INTER_cuStreamQuery( CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuStreamQuery, (void*) PTR_ORIGINAL_cuStreamQuery, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuStreamSynchronize
//int ORIGINAL_cuStreamSynchronize( CUstream hStream ) { }

void * PTR_ORIGINAL_cuStreamSynchronize;
// This is the call that will take the place of the original
int INTER_cuStreamSynchronize( CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuStreamSynchronize, (void*) PTR_ORIGINAL_cuStreamSynchronize, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuStreamDestroy
//int ORIGINAL_cuStreamDestroy( CUstream hStream ) { }

void * PTR_ORIGINAL_cuStreamDestroy;
// This is the call that will take the place of the original
int INTER_cuStreamDestroy( CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuStreamDestroy, (void*) PTR_ORIGINAL_cuStreamDestroy, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuEventCreate
//int ORIGINAL_cuEventCreate( CUevent * phEvent, unsigned int Flags ) { }

void * PTR_ORIGINAL_cuEventCreate;
// This is the call that will take the place of the original
int INTER_cuEventCreate( CUevent * phEvent, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&phEvent,(void **)&Flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuEventCreate, (void*) PTR_ORIGINAL_cuEventCreate, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuEventRecord
//int ORIGINAL_cuEventRecord( CUevent hEvent, CUstream hStream ) { }

void * PTR_ORIGINAL_cuEventRecord;
// This is the call that will take the place of the original
int INTER_cuEventRecord( CUevent hEvent, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hEvent,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuEventRecord, (void*) PTR_ORIGINAL_cuEventRecord, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuEventQuery
//int ORIGINAL_cuEventQuery( CUevent hEvent ) { }

void * PTR_ORIGINAL_cuEventQuery;
// This is the call that will take the place of the original
int INTER_cuEventQuery( CUevent hEvent ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hEvent };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuEventQuery, (void*) PTR_ORIGINAL_cuEventQuery, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuEventSynchronize
//int ORIGINAL_cuEventSynchronize( CUevent hEvent ) { }

void * PTR_ORIGINAL_cuEventSynchronize;
// This is the call that will take the place of the original
int INTER_cuEventSynchronize( CUevent hEvent ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hEvent };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuEventSynchronize, (void*) PTR_ORIGINAL_cuEventSynchronize, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuEventDestroy
//int ORIGINAL_cuEventDestroy( CUevent hEvent ) { }

void * PTR_ORIGINAL_cuEventDestroy;
// This is the call that will take the place of the original
int INTER_cuEventDestroy( CUevent hEvent ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hEvent };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuEventDestroy, (void*) PTR_ORIGINAL_cuEventDestroy, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuEventElapsedTime
//int ORIGINAL_cuEventElapsedTime( float * pMilliseconds, CUevent hStart, CUevent hEnd ) { }

void * PTR_ORIGINAL_cuEventElapsedTime;
// This is the call that will take the place of the original
int INTER_cuEventElapsedTime( float * pMilliseconds, CUevent hStart, CUevent hEnd ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pMilliseconds,(void **)&hStart,(void **)&hEnd };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuEventElapsedTime, (void*) PTR_ORIGINAL_cuEventElapsedTime, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuStreamWaitValue32
//int ORIGINAL_cuStreamWaitValue32( CUstream stream, CUdeviceptr addr, cuuint32_t value, unsigned int flags ) { }

void * PTR_ORIGINAL_cuStreamWaitValue32;
// This is the call that will take the place of the original
int INTER_cuStreamWaitValue32( CUstream stream, CUdeviceptr addr, cuuint32_t value, unsigned int flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&stream,(void **)&addr,(void **)&value,(void **)&flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuStreamWaitValue32, (void*) PTR_ORIGINAL_cuStreamWaitValue32, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuStreamWriteValue32
//int ORIGINAL_cuStreamWriteValue32( CUstream stream, CUdeviceptr addr, cuuint32_t value, unsigned int flags ) { }

void * PTR_ORIGINAL_cuStreamWriteValue32;
// This is the call that will take the place of the original
int INTER_cuStreamWriteValue32( CUstream stream, CUdeviceptr addr, cuuint32_t value, unsigned int flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&stream,(void **)&addr,(void **)&value,(void **)&flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuStreamWriteValue32, (void*) PTR_ORIGINAL_cuStreamWriteValue32, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuStreamBatchMemOp
//int ORIGINAL_cuStreamBatchMemOp( CUstream stream, unsigned int count, CUstreamBatchMemOpParams * paramArray, unsigned int flags ) { }

void * PTR_ORIGINAL_cuStreamBatchMemOp;
// This is the call that will take the place of the original
int INTER_cuStreamBatchMemOp( CUstream stream, unsigned int count, CUstreamBatchMemOpParams * paramArray, unsigned int flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&stream,(void **)&count,(void **)&paramArray,(void **)&flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuStreamBatchMemOp, (void*) PTR_ORIGINAL_cuStreamBatchMemOp, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuFuncGetAttribute
//int ORIGINAL_cuFuncGetAttribute( int * pi, CUfunction_attribute attrib, CUfunction hfunc ) { }

void * PTR_ORIGINAL_cuFuncGetAttribute;
// This is the call that will take the place of the original
int INTER_cuFuncGetAttribute( int * pi, CUfunction_attribute attrib, CUfunction hfunc ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pi,(void **)&attrib,(void **)&hfunc };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuFuncGetAttribute, (void*) PTR_ORIGINAL_cuFuncGetAttribute, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuFuncSetCacheConfig
//int ORIGINAL_cuFuncSetCacheConfig( CUfunction hfunc, CUfunc_cache config ) { }

void * PTR_ORIGINAL_cuFuncSetCacheConfig;
// This is the call that will take the place of the original
int INTER_cuFuncSetCacheConfig( CUfunction hfunc, CUfunc_cache config ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hfunc,(void **)&config };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuFuncSetCacheConfig, (void*) PTR_ORIGINAL_cuFuncSetCacheConfig, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuFuncSetSharedMemConfig
//int ORIGINAL_cuFuncSetSharedMemConfig( CUfunction hfunc, CUsharedconfig config ) { }

void * PTR_ORIGINAL_cuFuncSetSharedMemConfig;
// This is the call that will take the place of the original
int INTER_cuFuncSetSharedMemConfig( CUfunction hfunc, CUsharedconfig config ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hfunc,(void **)&config };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuFuncSetSharedMemConfig, (void*) PTR_ORIGINAL_cuFuncSetSharedMemConfig, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuLaunchKernel
//int ORIGINAL_cuLaunchKernel( CUfunction f, unsigned int gridDimX, unsigned int gridDimY, unsigned int gridDimZ, unsigned int blockDimX, unsigned int blockDimY, unsigned int blockDimZ, unsigned int sharedMemBytes, CUstream hStream, void * * kernelParams, void * * extra ) { }

void * PTR_ORIGINAL_cuLaunchKernel;
// This is the call that will take the place of the original
int INTER_cuLaunchKernel( CUfunction f, unsigned int gridDimX, unsigned int gridDimY, unsigned int gridDimZ, unsigned int blockDimX, unsigned int blockDimY, unsigned int blockDimZ, unsigned int sharedMemBytes, CUstream hStream, void * * kernelParams, void * * extra ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&f,(void **)&gridDimX,(void **)&gridDimY,(void **)&gridDimZ,(void **)&blockDimX,(void **)&blockDimY,(void **)&blockDimZ,(void **)&sharedMemBytes,(void **)&hStream,(void **)&kernelParams,(void **)&extra };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuLaunchKernel, (void*) PTR_ORIGINAL_cuLaunchKernel, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuFuncSetBlockShape
//int ORIGINAL_cuFuncSetBlockShape( CUfunction hfunc, int x, int y, int z ) { }

void * PTR_ORIGINAL_cuFuncSetBlockShape;
// This is the call that will take the place of the original
int INTER_cuFuncSetBlockShape( CUfunction hfunc, int x, int y, int z ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hfunc,(void **)&x,(void **)&y,(void **)&z };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuFuncSetBlockShape, (void*) PTR_ORIGINAL_cuFuncSetBlockShape, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuFuncSetSharedSize
//int ORIGINAL_cuFuncSetSharedSize( CUfunction hfunc, unsigned int bytes ) { }

void * PTR_ORIGINAL_cuFuncSetSharedSize;
// This is the call that will take the place of the original
int INTER_cuFuncSetSharedSize( CUfunction hfunc, unsigned int bytes ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hfunc,(void **)&bytes };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuFuncSetSharedSize, (void*) PTR_ORIGINAL_cuFuncSetSharedSize, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuParamSetSize
//int ORIGINAL_cuParamSetSize( CUfunction hfunc, unsigned int numbytes ) { }

void * PTR_ORIGINAL_cuParamSetSize;
// This is the call that will take the place of the original
int INTER_cuParamSetSize( CUfunction hfunc, unsigned int numbytes ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hfunc,(void **)&numbytes };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuParamSetSize, (void*) PTR_ORIGINAL_cuParamSetSize, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuParamSeti
//int ORIGINAL_cuParamSeti( CUfunction hfunc, int offset, unsigned int value ) { }

void * PTR_ORIGINAL_cuParamSeti;
// This is the call that will take the place of the original
int INTER_cuParamSeti( CUfunction hfunc, int offset, unsigned int value ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hfunc,(void **)&offset,(void **)&value };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuParamSeti, (void*) PTR_ORIGINAL_cuParamSeti, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuParamSetf
//int ORIGINAL_cuParamSetf( CUfunction hfunc, int offset, float value ) { }

void * PTR_ORIGINAL_cuParamSetf;
// This is the call that will take the place of the original
int INTER_cuParamSetf( CUfunction hfunc, int offset, float value ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hfunc,(void **)&offset,(void **)&value };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuParamSetf, (void*) PTR_ORIGINAL_cuParamSetf, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuParamSetv
//int ORIGINAL_cuParamSetv( CUfunction hfunc, int offset, void * ptr, unsigned int numbytes ) { }

void * PTR_ORIGINAL_cuParamSetv;
// This is the call that will take the place of the original
int INTER_cuParamSetv( CUfunction hfunc, int offset, void * ptr, unsigned int numbytes ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hfunc,(void **)&offset,(void **)&ptr,(void **)&numbytes };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuParamSetv, (void*) PTR_ORIGINAL_cuParamSetv, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuLaunch
//int ORIGINAL_cuLaunch( CUfunction f ) { }

void * PTR_ORIGINAL_cuLaunch;
// This is the call that will take the place of the original
int INTER_cuLaunch( CUfunction f ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&f };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuLaunch, (void*) PTR_ORIGINAL_cuLaunch, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuLaunchGrid
//int ORIGINAL_cuLaunchGrid( CUfunction f, int grid_width, int grid_height ) { }

void * PTR_ORIGINAL_cuLaunchGrid;
// This is the call that will take the place of the original
int INTER_cuLaunchGrid( CUfunction f, int grid_width, int grid_height ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&f,(void **)&grid_width,(void **)&grid_height };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuLaunchGrid, (void*) PTR_ORIGINAL_cuLaunchGrid, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuLaunchGridAsync
//int ORIGINAL_cuLaunchGridAsync( CUfunction f, int grid_width, int grid_height, CUstream hStream ) { }

void * PTR_ORIGINAL_cuLaunchGridAsync;
// This is the call that will take the place of the original
int INTER_cuLaunchGridAsync( CUfunction f, int grid_width, int grid_height, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&f,(void **)&grid_width,(void **)&grid_height,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuLaunchGridAsync, (void*) PTR_ORIGINAL_cuLaunchGridAsync, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuParamSetTexRef
//int ORIGINAL_cuParamSetTexRef( CUfunction hfunc, int texunit, CUtexref hTexRef ) { }

void * PTR_ORIGINAL_cuParamSetTexRef;
// This is the call that will take the place of the original
int INTER_cuParamSetTexRef( CUfunction hfunc, int texunit, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hfunc,(void **)&texunit,(void **)&hTexRef };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuParamSetTexRef, (void*) PTR_ORIGINAL_cuParamSetTexRef, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuOccupancyMaxActiveBlocksPerMultiprocessor
//int ORIGINAL_cuOccupancyMaxActiveBlocksPerMultiprocessor( int * numBlocks, CUfunction func, int blockSize, size_t dynamicSMemSize ) { }

void * PTR_ORIGINAL_cuOccupancyMaxActiveBlocksPerMultiprocessor;
// This is the call that will take the place of the original
int INTER_cuOccupancyMaxActiveBlocksPerMultiprocessor( int * numBlocks, CUfunction func, int blockSize, size_t dynamicSMemSize ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&numBlocks,(void **)&func,(void **)&blockSize,(void **)&dynamicSMemSize };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuOccupancyMaxActiveBlocksPerMultiprocessor, (void*) PTR_ORIGINAL_cuOccupancyMaxActiveBlocksPerMultiprocessor, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags
//int ORIGINAL_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags( int * numBlocks, CUfunction func, int blockSize, size_t dynamicSMemSize, unsigned int flags ) { }

void * PTR_ORIGINAL_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags;
// This is the call that will take the place of the original
int INTER_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags( int * numBlocks, CUfunction func, int blockSize, size_t dynamicSMemSize, unsigned int flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&numBlocks,(void **)&func,(void **)&blockSize,(void **)&dynamicSMemSize,(void **)&flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags, (void*) PTR_ORIGINAL_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuOccupancyMaxPotentialBlockSize
//int ORIGINAL_cuOccupancyMaxPotentialBlockSize( int * minGridSize, int * blockSize, CUfunction func, CUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int blockSizeLimit ) { }

void * PTR_ORIGINAL_cuOccupancyMaxPotentialBlockSize;
// This is the call that will take the place of the original
int INTER_cuOccupancyMaxPotentialBlockSize( int * minGridSize, int * blockSize, CUfunction func, CUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int blockSizeLimit ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&minGridSize,(void **)&blockSize,(void **)&func,(void **)&blockSizeToDynamicSMemSize,(void **)&dynamicSMemSize,(void **)&blockSizeLimit };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuOccupancyMaxPotentialBlockSize, (void*) PTR_ORIGINAL_cuOccupancyMaxPotentialBlockSize, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuOccupancyMaxPotentialBlockSizeWithFlags
//int ORIGINAL_cuOccupancyMaxPotentialBlockSizeWithFlags( int * minGridSize, int * blockSize, CUfunction func, CUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int blockSizeLimit, unsigned int flags ) { }

void * PTR_ORIGINAL_cuOccupancyMaxPotentialBlockSizeWithFlags;
// This is the call that will take the place of the original
int INTER_cuOccupancyMaxPotentialBlockSizeWithFlags( int * minGridSize, int * blockSize, CUfunction func, CUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int blockSizeLimit, unsigned int flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&minGridSize,(void **)&blockSize,(void **)&func,(void **)&blockSizeToDynamicSMemSize,(void **)&dynamicSMemSize,(void **)&blockSizeLimit,(void **)&flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuOccupancyMaxPotentialBlockSizeWithFlags, (void*) PTR_ORIGINAL_cuOccupancyMaxPotentialBlockSizeWithFlags, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefSetArray
//int ORIGINAL_cuTexRefSetArray( CUtexref hTexRef, CUarray hArray, unsigned int Flags ) { }

void * PTR_ORIGINAL_cuTexRefSetArray;
// This is the call that will take the place of the original
int INTER_cuTexRefSetArray( CUtexref hTexRef, CUarray hArray, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hTexRef,(void **)&hArray,(void **)&Flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefSetArray, (void*) PTR_ORIGINAL_cuTexRefSetArray, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefSetMipmappedArray
//int ORIGINAL_cuTexRefSetMipmappedArray( CUtexref hTexRef, CUmipmappedArray hMipmappedArray, unsigned int Flags ) { }

void * PTR_ORIGINAL_cuTexRefSetMipmappedArray;
// This is the call that will take the place of the original
int INTER_cuTexRefSetMipmappedArray( CUtexref hTexRef, CUmipmappedArray hMipmappedArray, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hTexRef,(void **)&hMipmappedArray,(void **)&Flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefSetMipmappedArray, (void*) PTR_ORIGINAL_cuTexRefSetMipmappedArray, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefSetAddress
//int ORIGINAL_cuTexRefSetAddress( size_t * ByteOffset, CUtexref hTexRef, CUdeviceptr dptr, size_t bytes ) { }

void * PTR_ORIGINAL_cuTexRefSetAddress;
// This is the call that will take the place of the original
int INTER_cuTexRefSetAddress( size_t * ByteOffset, CUtexref hTexRef, CUdeviceptr dptr, size_t bytes ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&ByteOffset,(void **)&hTexRef,(void **)&dptr,(void **)&bytes };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefSetAddress, (void*) PTR_ORIGINAL_cuTexRefSetAddress, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefSetAddress2D
//int ORIGINAL_cuTexRefSetAddress2D( CUtexref hTexRef, const CUDA_ARRAY_DESCRIPTOR * desc, CUdeviceptr dptr, size_t Pitch ) { }

void * PTR_ORIGINAL_cuTexRefSetAddress2D;
// This is the call that will take the place of the original
int INTER_cuTexRefSetAddress2D( CUtexref hTexRef, const CUDA_ARRAY_DESCRIPTOR * desc, CUdeviceptr dptr, size_t Pitch ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hTexRef,(void **)&desc,(void **)&dptr,(void **)&Pitch };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefSetAddress2D, (void*) PTR_ORIGINAL_cuTexRefSetAddress2D, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefSetFormat
//int ORIGINAL_cuTexRefSetFormat( CUtexref hTexRef, CUarray_format fmt, int NumPackedComponents ) { }

void * PTR_ORIGINAL_cuTexRefSetFormat;
// This is the call that will take the place of the original
int INTER_cuTexRefSetFormat( CUtexref hTexRef, CUarray_format fmt, int NumPackedComponents ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hTexRef,(void **)&fmt,(void **)&NumPackedComponents };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefSetFormat, (void*) PTR_ORIGINAL_cuTexRefSetFormat, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefSetAddressMode
//int ORIGINAL_cuTexRefSetAddressMode( CUtexref hTexRef, int dim, CUaddress_mode am ) { }

void * PTR_ORIGINAL_cuTexRefSetAddressMode;
// This is the call that will take the place of the original
int INTER_cuTexRefSetAddressMode( CUtexref hTexRef, int dim, CUaddress_mode am ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hTexRef,(void **)&dim,(void **)&am };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefSetAddressMode, (void*) PTR_ORIGINAL_cuTexRefSetAddressMode, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefSetFilterMode
//int ORIGINAL_cuTexRefSetFilterMode( CUtexref hTexRef, CUfilter_mode fm ) { }

void * PTR_ORIGINAL_cuTexRefSetFilterMode;
// This is the call that will take the place of the original
int INTER_cuTexRefSetFilterMode( CUtexref hTexRef, CUfilter_mode fm ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hTexRef,(void **)&fm };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefSetFilterMode, (void*) PTR_ORIGINAL_cuTexRefSetFilterMode, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefSetMipmapFilterMode
//int ORIGINAL_cuTexRefSetMipmapFilterMode( CUtexref hTexRef, CUfilter_mode fm ) { }

void * PTR_ORIGINAL_cuTexRefSetMipmapFilterMode;
// This is the call that will take the place of the original
int INTER_cuTexRefSetMipmapFilterMode( CUtexref hTexRef, CUfilter_mode fm ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hTexRef,(void **)&fm };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefSetMipmapFilterMode, (void*) PTR_ORIGINAL_cuTexRefSetMipmapFilterMode, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefSetMipmapLevelBias
//int ORIGINAL_cuTexRefSetMipmapLevelBias( CUtexref hTexRef, float bias ) { }

void * PTR_ORIGINAL_cuTexRefSetMipmapLevelBias;
// This is the call that will take the place of the original
int INTER_cuTexRefSetMipmapLevelBias( CUtexref hTexRef, float bias ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hTexRef,(void **)&bias };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefSetMipmapLevelBias, (void*) PTR_ORIGINAL_cuTexRefSetMipmapLevelBias, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefSetMipmapLevelClamp
//int ORIGINAL_cuTexRefSetMipmapLevelClamp( CUtexref hTexRef, float minMipmapLevelClamp, float maxMipmapLevelClamp ) { }

void * PTR_ORIGINAL_cuTexRefSetMipmapLevelClamp;
// This is the call that will take the place of the original
int INTER_cuTexRefSetMipmapLevelClamp( CUtexref hTexRef, float minMipmapLevelClamp, float maxMipmapLevelClamp ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hTexRef,(void **)&minMipmapLevelClamp,(void **)&maxMipmapLevelClamp };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefSetMipmapLevelClamp, (void*) PTR_ORIGINAL_cuTexRefSetMipmapLevelClamp, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefSetMaxAnisotropy
//int ORIGINAL_cuTexRefSetMaxAnisotropy( CUtexref hTexRef, unsigned int maxAniso ) { }

void * PTR_ORIGINAL_cuTexRefSetMaxAnisotropy;
// This is the call that will take the place of the original
int INTER_cuTexRefSetMaxAnisotropy( CUtexref hTexRef, unsigned int maxAniso ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hTexRef,(void **)&maxAniso };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefSetMaxAnisotropy, (void*) PTR_ORIGINAL_cuTexRefSetMaxAnisotropy, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefSetBorderColor
//int ORIGINAL_cuTexRefSetBorderColor( CUtexref hTexRef, float * pBorderColor ) { }

void * PTR_ORIGINAL_cuTexRefSetBorderColor;
// This is the call that will take the place of the original
int INTER_cuTexRefSetBorderColor( CUtexref hTexRef, float * pBorderColor ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hTexRef,(void **)&pBorderColor };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefSetBorderColor, (void*) PTR_ORIGINAL_cuTexRefSetBorderColor, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefSetFlags
//int ORIGINAL_cuTexRefSetFlags( CUtexref hTexRef, unsigned int Flags ) { }

void * PTR_ORIGINAL_cuTexRefSetFlags;
// This is the call that will take the place of the original
int INTER_cuTexRefSetFlags( CUtexref hTexRef, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hTexRef,(void **)&Flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefSetFlags, (void*) PTR_ORIGINAL_cuTexRefSetFlags, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefGetAddress
//int ORIGINAL_cuTexRefGetAddress( CUdeviceptr * pdptr, CUtexref hTexRef ) { }

void * PTR_ORIGINAL_cuTexRefGetAddress;
// This is the call that will take the place of the original
int INTER_cuTexRefGetAddress( CUdeviceptr * pdptr, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pdptr,(void **)&hTexRef };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefGetAddress, (void*) PTR_ORIGINAL_cuTexRefGetAddress, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefGetArray
//int ORIGINAL_cuTexRefGetArray( CUarray * phArray, CUtexref hTexRef ) { }

void * PTR_ORIGINAL_cuTexRefGetArray;
// This is the call that will take the place of the original
int INTER_cuTexRefGetArray( CUarray * phArray, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&phArray,(void **)&hTexRef };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefGetArray, (void*) PTR_ORIGINAL_cuTexRefGetArray, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefGetMipmappedArray
//int ORIGINAL_cuTexRefGetMipmappedArray( CUmipmappedArray * phMipmappedArray, CUtexref hTexRef ) { }

void * PTR_ORIGINAL_cuTexRefGetMipmappedArray;
// This is the call that will take the place of the original
int INTER_cuTexRefGetMipmappedArray( CUmipmappedArray * phMipmappedArray, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&phMipmappedArray,(void **)&hTexRef };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefGetMipmappedArray, (void*) PTR_ORIGINAL_cuTexRefGetMipmappedArray, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefGetAddressMode
//int ORIGINAL_cuTexRefGetAddressMode( CUaddress_mode * pam, CUtexref hTexRef, int dim ) { }

void * PTR_ORIGINAL_cuTexRefGetAddressMode;
// This is the call that will take the place of the original
int INTER_cuTexRefGetAddressMode( CUaddress_mode * pam, CUtexref hTexRef, int dim ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pam,(void **)&hTexRef,(void **)&dim };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefGetAddressMode, (void*) PTR_ORIGINAL_cuTexRefGetAddressMode, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefGetFilterMode
//int ORIGINAL_cuTexRefGetFilterMode( CUfilter_mode * pfm, CUtexref hTexRef ) { }

void * PTR_ORIGINAL_cuTexRefGetFilterMode;
// This is the call that will take the place of the original
int INTER_cuTexRefGetFilterMode( CUfilter_mode * pfm, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pfm,(void **)&hTexRef };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefGetFilterMode, (void*) PTR_ORIGINAL_cuTexRefGetFilterMode, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefGetFormat
//int ORIGINAL_cuTexRefGetFormat( CUarray_format * pFormat, int * pNumChannels, CUtexref hTexRef ) { }

void * PTR_ORIGINAL_cuTexRefGetFormat;
// This is the call that will take the place of the original
int INTER_cuTexRefGetFormat( CUarray_format * pFormat, int * pNumChannels, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pFormat,(void **)&pNumChannels,(void **)&hTexRef };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefGetFormat, (void*) PTR_ORIGINAL_cuTexRefGetFormat, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefGetMipmapFilterMode
//int ORIGINAL_cuTexRefGetMipmapFilterMode( CUfilter_mode * pfm, CUtexref hTexRef ) { }

void * PTR_ORIGINAL_cuTexRefGetMipmapFilterMode;
// This is the call that will take the place of the original
int INTER_cuTexRefGetMipmapFilterMode( CUfilter_mode * pfm, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pfm,(void **)&hTexRef };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefGetMipmapFilterMode, (void*) PTR_ORIGINAL_cuTexRefGetMipmapFilterMode, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefGetMipmapLevelBias
//int ORIGINAL_cuTexRefGetMipmapLevelBias( float * pbias, CUtexref hTexRef ) { }

void * PTR_ORIGINAL_cuTexRefGetMipmapLevelBias;
// This is the call that will take the place of the original
int INTER_cuTexRefGetMipmapLevelBias( float * pbias, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pbias,(void **)&hTexRef };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefGetMipmapLevelBias, (void*) PTR_ORIGINAL_cuTexRefGetMipmapLevelBias, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefGetMipmapLevelClamp
//int ORIGINAL_cuTexRefGetMipmapLevelClamp( float * pminMipmapLevelClamp, float * pmaxMipmapLevelClamp, CUtexref hTexRef ) { }

void * PTR_ORIGINAL_cuTexRefGetMipmapLevelClamp;
// This is the call that will take the place of the original
int INTER_cuTexRefGetMipmapLevelClamp( float * pminMipmapLevelClamp, float * pmaxMipmapLevelClamp, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pminMipmapLevelClamp,(void **)&pmaxMipmapLevelClamp,(void **)&hTexRef };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefGetMipmapLevelClamp, (void*) PTR_ORIGINAL_cuTexRefGetMipmapLevelClamp, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefGetMaxAnisotropy
//int ORIGINAL_cuTexRefGetMaxAnisotropy( int * pmaxAniso, CUtexref hTexRef ) { }

void * PTR_ORIGINAL_cuTexRefGetMaxAnisotropy;
// This is the call that will take the place of the original
int INTER_cuTexRefGetMaxAnisotropy( int * pmaxAniso, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pmaxAniso,(void **)&hTexRef };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefGetMaxAnisotropy, (void*) PTR_ORIGINAL_cuTexRefGetMaxAnisotropy, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefGetBorderColor
//int ORIGINAL_cuTexRefGetBorderColor( float * pBorderColor, CUtexref hTexRef ) { }

void * PTR_ORIGINAL_cuTexRefGetBorderColor;
// This is the call that will take the place of the original
int INTER_cuTexRefGetBorderColor( float * pBorderColor, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pBorderColor,(void **)&hTexRef };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefGetBorderColor, (void*) PTR_ORIGINAL_cuTexRefGetBorderColor, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefGetFlags
//int ORIGINAL_cuTexRefGetFlags( unsigned int * pFlags, CUtexref hTexRef ) { }

void * PTR_ORIGINAL_cuTexRefGetFlags;
// This is the call that will take the place of the original
int INTER_cuTexRefGetFlags( unsigned int * pFlags, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pFlags,(void **)&hTexRef };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefGetFlags, (void*) PTR_ORIGINAL_cuTexRefGetFlags, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefCreate
//int ORIGINAL_cuTexRefCreate( CUtexref * pTexRef ) { }

void * PTR_ORIGINAL_cuTexRefCreate;
// This is the call that will take the place of the original
int INTER_cuTexRefCreate( CUtexref * pTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pTexRef };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefCreate, (void*) PTR_ORIGINAL_cuTexRefCreate, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefDestroy
//int ORIGINAL_cuTexRefDestroy( CUtexref hTexRef ) { }

void * PTR_ORIGINAL_cuTexRefDestroy;
// This is the call that will take the place of the original
int INTER_cuTexRefDestroy( CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hTexRef };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefDestroy, (void*) PTR_ORIGINAL_cuTexRefDestroy, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuSurfRefSetArray
//int ORIGINAL_cuSurfRefSetArray( CUsurfref hSurfRef, CUarray hArray, unsigned int Flags ) { }

void * PTR_ORIGINAL_cuSurfRefSetArray;
// This is the call that will take the place of the original
int INTER_cuSurfRefSetArray( CUsurfref hSurfRef, CUarray hArray, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hSurfRef,(void **)&hArray,(void **)&Flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuSurfRefSetArray, (void*) PTR_ORIGINAL_cuSurfRefSetArray, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuSurfRefGetArray
//int ORIGINAL_cuSurfRefGetArray( CUarray * phArray, CUsurfref hSurfRef ) { }

void * PTR_ORIGINAL_cuSurfRefGetArray;
// This is the call that will take the place of the original
int INTER_cuSurfRefGetArray( CUarray * phArray, CUsurfref hSurfRef ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&phArray,(void **)&hSurfRef };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuSurfRefGetArray, (void*) PTR_ORIGINAL_cuSurfRefGetArray, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexObjectCreate
//int ORIGINAL_cuTexObjectCreate( CUtexObject * pTexObject, const CUDA_RESOURCE_DESC * pResDesc, const CUDA_TEXTURE_DESC * pTexDesc, const CUDA_RESOURCE_VIEW_DESC * pResViewDesc ) { }

void * PTR_ORIGINAL_cuTexObjectCreate;
// This is the call that will take the place of the original
int INTER_cuTexObjectCreate( CUtexObject * pTexObject, const CUDA_RESOURCE_DESC * pResDesc, const CUDA_TEXTURE_DESC * pTexDesc, const CUDA_RESOURCE_VIEW_DESC * pResViewDesc ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pTexObject,(void **)&pResDesc,(void **)&pTexDesc,(void **)&pResViewDesc };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexObjectCreate, (void*) PTR_ORIGINAL_cuTexObjectCreate, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexObjectDestroy
//int ORIGINAL_cuTexObjectDestroy( CUtexObject texObject ) { }

void * PTR_ORIGINAL_cuTexObjectDestroy;
// This is the call that will take the place of the original
int INTER_cuTexObjectDestroy( CUtexObject texObject ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&texObject };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexObjectDestroy, (void*) PTR_ORIGINAL_cuTexObjectDestroy, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexObjectGetResourceDesc
//int ORIGINAL_cuTexObjectGetResourceDesc( CUDA_RESOURCE_DESC * pResDesc, CUtexObject texObject ) { }

void * PTR_ORIGINAL_cuTexObjectGetResourceDesc;
// This is the call that will take the place of the original
int INTER_cuTexObjectGetResourceDesc( CUDA_RESOURCE_DESC * pResDesc, CUtexObject texObject ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pResDesc,(void **)&texObject };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexObjectGetResourceDesc, (void*) PTR_ORIGINAL_cuTexObjectGetResourceDesc, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexObjectGetTextureDesc
//int ORIGINAL_cuTexObjectGetTextureDesc( CUDA_TEXTURE_DESC * pTexDesc, CUtexObject texObject ) { }

void * PTR_ORIGINAL_cuTexObjectGetTextureDesc;
// This is the call that will take the place of the original
int INTER_cuTexObjectGetTextureDesc( CUDA_TEXTURE_DESC * pTexDesc, CUtexObject texObject ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pTexDesc,(void **)&texObject };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexObjectGetTextureDesc, (void*) PTR_ORIGINAL_cuTexObjectGetTextureDesc, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexObjectGetResourceViewDesc
//int ORIGINAL_cuTexObjectGetResourceViewDesc( CUDA_RESOURCE_VIEW_DESC * pResViewDesc, CUtexObject texObject ) { }

void * PTR_ORIGINAL_cuTexObjectGetResourceViewDesc;
// This is the call that will take the place of the original
int INTER_cuTexObjectGetResourceViewDesc( CUDA_RESOURCE_VIEW_DESC * pResViewDesc, CUtexObject texObject ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pResViewDesc,(void **)&texObject };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexObjectGetResourceViewDesc, (void*) PTR_ORIGINAL_cuTexObjectGetResourceViewDesc, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuSurfObjectCreate
//int ORIGINAL_cuSurfObjectCreate( CUsurfObject * pSurfObject, const CUDA_RESOURCE_DESC * pResDesc ) { }

void * PTR_ORIGINAL_cuSurfObjectCreate;
// This is the call that will take the place of the original
int INTER_cuSurfObjectCreate( CUsurfObject * pSurfObject, const CUDA_RESOURCE_DESC * pResDesc ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pSurfObject,(void **)&pResDesc };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuSurfObjectCreate, (void*) PTR_ORIGINAL_cuSurfObjectCreate, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuSurfObjectDestroy
//int ORIGINAL_cuSurfObjectDestroy( CUsurfObject surfObject ) { }

void * PTR_ORIGINAL_cuSurfObjectDestroy;
// This is the call that will take the place of the original
int INTER_cuSurfObjectDestroy( CUsurfObject surfObject ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&surfObject };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuSurfObjectDestroy, (void*) PTR_ORIGINAL_cuSurfObjectDestroy, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuSurfObjectGetResourceDesc
//int ORIGINAL_cuSurfObjectGetResourceDesc( CUDA_RESOURCE_DESC * pResDesc, CUsurfObject surfObject ) { }

void * PTR_ORIGINAL_cuSurfObjectGetResourceDesc;
// This is the call that will take the place of the original
int INTER_cuSurfObjectGetResourceDesc( CUDA_RESOURCE_DESC * pResDesc, CUsurfObject surfObject ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pResDesc,(void **)&surfObject };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuSurfObjectGetResourceDesc, (void*) PTR_ORIGINAL_cuSurfObjectGetResourceDesc, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDeviceCanAccessPeer
//int ORIGINAL_cuDeviceCanAccessPeer( int * canAccessPeer, CUdevice dev, CUdevice peerDev ) { }

void * PTR_ORIGINAL_cuDeviceCanAccessPeer;
// This is the call that will take the place of the original
int INTER_cuDeviceCanAccessPeer( int * canAccessPeer, CUdevice dev, CUdevice peerDev ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&canAccessPeer,(void **)&dev,(void **)&peerDev };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDeviceCanAccessPeer, (void*) PTR_ORIGINAL_cuDeviceCanAccessPeer, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDeviceGetP2PAttribute
//int ORIGINAL_cuDeviceGetP2PAttribute( int * value, CUdevice_P2PAttribute attrib, CUdevice srcDevice, CUdevice dstDevice ) { }

void * PTR_ORIGINAL_cuDeviceGetP2PAttribute;
// This is the call that will take the place of the original
int INTER_cuDeviceGetP2PAttribute( int * value, CUdevice_P2PAttribute attrib, CUdevice srcDevice, CUdevice dstDevice ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&value,(void **)&attrib,(void **)&srcDevice,(void **)&dstDevice };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDeviceGetP2PAttribute, (void*) PTR_ORIGINAL_cuDeviceGetP2PAttribute, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxEnablePeerAccess
//int ORIGINAL_cuCtxEnablePeerAccess( CUcontext peerContext, unsigned int Flags ) { }

void * PTR_ORIGINAL_cuCtxEnablePeerAccess;
// This is the call that will take the place of the original
int INTER_cuCtxEnablePeerAccess( CUcontext peerContext, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&peerContext,(void **)&Flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxEnablePeerAccess, (void*) PTR_ORIGINAL_cuCtxEnablePeerAccess, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxDisablePeerAccess
//int ORIGINAL_cuCtxDisablePeerAccess( CUcontext peerContext ) { }

void * PTR_ORIGINAL_cuCtxDisablePeerAccess;
// This is the call that will take the place of the original
int INTER_cuCtxDisablePeerAccess( CUcontext peerContext ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&peerContext };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxDisablePeerAccess, (void*) PTR_ORIGINAL_cuCtxDisablePeerAccess, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuGraphicsUnregisterResource
//int ORIGINAL_cuGraphicsUnregisterResource( CUgraphicsResource resource ) { }

void * PTR_ORIGINAL_cuGraphicsUnregisterResource;
// This is the call that will take the place of the original
int INTER_cuGraphicsUnregisterResource( CUgraphicsResource resource ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&resource };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuGraphicsUnregisterResource, (void*) PTR_ORIGINAL_cuGraphicsUnregisterResource, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuGraphicsSubResourceGetMappedArray
//int ORIGINAL_cuGraphicsSubResourceGetMappedArray( CUarray * pArray, CUgraphicsResource resource, unsigned int arrayIndex, unsigned int mipLevel ) { }

void * PTR_ORIGINAL_cuGraphicsSubResourceGetMappedArray;
// This is the call that will take the place of the original
int INTER_cuGraphicsSubResourceGetMappedArray( CUarray * pArray, CUgraphicsResource resource, unsigned int arrayIndex, unsigned int mipLevel ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pArray,(void **)&resource,(void **)&arrayIndex,(void **)&mipLevel };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuGraphicsSubResourceGetMappedArray, (void*) PTR_ORIGINAL_cuGraphicsSubResourceGetMappedArray, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuGraphicsResourceGetMappedMipmappedArray
//int ORIGINAL_cuGraphicsResourceGetMappedMipmappedArray( CUmipmappedArray * pMipmappedArray, CUgraphicsResource resource ) { }

void * PTR_ORIGINAL_cuGraphicsResourceGetMappedMipmappedArray;
// This is the call that will take the place of the original
int INTER_cuGraphicsResourceGetMappedMipmappedArray( CUmipmappedArray * pMipmappedArray, CUgraphicsResource resource ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pMipmappedArray,(void **)&resource };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuGraphicsResourceGetMappedMipmappedArray, (void*) PTR_ORIGINAL_cuGraphicsResourceGetMappedMipmappedArray, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuGraphicsResourceGetMappedPointer
//int ORIGINAL_cuGraphicsResourceGetMappedPointer( CUdeviceptr * pDevPtr, size_t * pSize, CUgraphicsResource resource ) { }

void * PTR_ORIGINAL_cuGraphicsResourceGetMappedPointer;
// This is the call that will take the place of the original
int INTER_cuGraphicsResourceGetMappedPointer( CUdeviceptr * pDevPtr, size_t * pSize, CUgraphicsResource resource ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pDevPtr,(void **)&pSize,(void **)&resource };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuGraphicsResourceGetMappedPointer, (void*) PTR_ORIGINAL_cuGraphicsResourceGetMappedPointer, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuGraphicsResourceSetMapFlags
//int ORIGINAL_cuGraphicsResourceSetMapFlags( CUgraphicsResource resource, unsigned int flags ) { }

void * PTR_ORIGINAL_cuGraphicsResourceSetMapFlags;
// This is the call that will take the place of the original
int INTER_cuGraphicsResourceSetMapFlags( CUgraphicsResource resource, unsigned int flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&resource,(void **)&flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuGraphicsResourceSetMapFlags, (void*) PTR_ORIGINAL_cuGraphicsResourceSetMapFlags, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuGraphicsMapResources
//int ORIGINAL_cuGraphicsMapResources( unsigned int count, CUgraphicsResource * resources, CUstream hStream ) { }

void * PTR_ORIGINAL_cuGraphicsMapResources;
// This is the call that will take the place of the original
int INTER_cuGraphicsMapResources( unsigned int count, CUgraphicsResource * resources, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&count,(void **)&resources,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuGraphicsMapResources, (void*) PTR_ORIGINAL_cuGraphicsMapResources, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuGraphicsUnmapResources
//int ORIGINAL_cuGraphicsUnmapResources( unsigned int count, CUgraphicsResource * resources, CUstream hStream ) { }

void * PTR_ORIGINAL_cuGraphicsUnmapResources;
// This is the call that will take the place of the original
int INTER_cuGraphicsUnmapResources( unsigned int count, CUgraphicsResource * resources, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&count,(void **)&resources,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuGraphicsUnmapResources, (void*) PTR_ORIGINAL_cuGraphicsUnmapResources, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuGetExportTable
//int ORIGINAL_cuGetExportTable( const void * * ppExportTable, const CUuuid * pExportTableId ) { }

void * PTR_ORIGINAL_cuGetExportTable;
// This is the call that will take the place of the original
int INTER_cuGetExportTable( const void * * ppExportTable, const CUuuid * pExportTableId ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&ppExportTable,(void **)&pExportTableId };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuGetExportTable, (void*) PTR_ORIGINAL_cuGetExportTable, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefSetAddress2D_v2
//int ORIGINAL_cuTexRefSetAddress2D_v2( CUtexref hTexRef, const CUDA_ARRAY_DESCRIPTOR * desc, CUdeviceptr dptr, size_t Pitch ) { }

void * PTR_ORIGINAL_cuTexRefSetAddress2D_v2;
// This is the call that will take the place of the original
int INTER_cuTexRefSetAddress2D_v2( CUtexref hTexRef, const CUDA_ARRAY_DESCRIPTOR * desc, CUdeviceptr dptr, size_t Pitch ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hTexRef,(void **)&desc,(void **)&dptr,(void **)&Pitch };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefSetAddress2D_v2, (void*) PTR_ORIGINAL_cuTexRefSetAddress2D_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyHtoD_v2
//int ORIGINAL_cuMemcpyHtoD_v2( CUdeviceptr dstDevice, const void * srcHost, size_t ByteCount ) { }

void * PTR_ORIGINAL_cuMemcpyHtoD_v2;
// This is the call that will take the place of the original
int INTER_cuMemcpyHtoD_v2( CUdeviceptr dstDevice, const void * srcHost, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&srcHost,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyHtoD_v2, (void*) PTR_ORIGINAL_cuMemcpyHtoD_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyDtoH_v2
//int ORIGINAL_cuMemcpyDtoH_v2( void * dstHost, CUdeviceptr srcDevice, size_t ByteCount ) { }

void * PTR_ORIGINAL_cuMemcpyDtoH_v2;
// This is the call that will take the place of the original
int INTER_cuMemcpyDtoH_v2( void * dstHost, CUdeviceptr srcDevice, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstHost,(void **)&srcDevice,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyDtoH_v2, (void*) PTR_ORIGINAL_cuMemcpyDtoH_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyDtoD_v2
//int ORIGINAL_cuMemcpyDtoD_v2( CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount ) { }

void * PTR_ORIGINAL_cuMemcpyDtoD_v2;
// This is the call that will take the place of the original
int INTER_cuMemcpyDtoD_v2( CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&srcDevice,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyDtoD_v2, (void*) PTR_ORIGINAL_cuMemcpyDtoD_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyDtoA_v2
//int ORIGINAL_cuMemcpyDtoA_v2( CUarray dstArray, size_t dstOffset, CUdeviceptr srcDevice, size_t ByteCount ) { }

void * PTR_ORIGINAL_cuMemcpyDtoA_v2;
// This is the call that will take the place of the original
int INTER_cuMemcpyDtoA_v2( CUarray dstArray, size_t dstOffset, CUdeviceptr srcDevice, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstArray,(void **)&dstOffset,(void **)&srcDevice,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyDtoA_v2, (void*) PTR_ORIGINAL_cuMemcpyDtoA_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyAtoD_v2
//int ORIGINAL_cuMemcpyAtoD_v2( CUdeviceptr dstDevice, CUarray srcArray, size_t srcOffset, size_t ByteCount ) { }

void * PTR_ORIGINAL_cuMemcpyAtoD_v2;
// This is the call that will take the place of the original
int INTER_cuMemcpyAtoD_v2( CUdeviceptr dstDevice, CUarray srcArray, size_t srcOffset, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&srcArray,(void **)&srcOffset,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyAtoD_v2, (void*) PTR_ORIGINAL_cuMemcpyAtoD_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyHtoA_v2
//int ORIGINAL_cuMemcpyHtoA_v2( CUarray dstArray, size_t dstOffset, const void * srcHost, size_t ByteCount ) { }

void * PTR_ORIGINAL_cuMemcpyHtoA_v2;
// This is the call that will take the place of the original
int INTER_cuMemcpyHtoA_v2( CUarray dstArray, size_t dstOffset, const void * srcHost, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstArray,(void **)&dstOffset,(void **)&srcHost,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyHtoA_v2, (void*) PTR_ORIGINAL_cuMemcpyHtoA_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyAtoH_v2
//int ORIGINAL_cuMemcpyAtoH_v2( void * dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount ) { }

void * PTR_ORIGINAL_cuMemcpyAtoH_v2;
// This is the call that will take the place of the original
int INTER_cuMemcpyAtoH_v2( void * dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstHost,(void **)&srcArray,(void **)&srcOffset,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyAtoH_v2, (void*) PTR_ORIGINAL_cuMemcpyAtoH_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyAtoA_v2
//int ORIGINAL_cuMemcpyAtoA_v2( CUarray dstArray, size_t dstOffset, CUarray srcArray, size_t srcOffset, size_t ByteCount ) { }

void * PTR_ORIGINAL_cuMemcpyAtoA_v2;
// This is the call that will take the place of the original
int INTER_cuMemcpyAtoA_v2( CUarray dstArray, size_t dstOffset, CUarray srcArray, size_t srcOffset, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstArray,(void **)&dstOffset,(void **)&srcArray,(void **)&srcOffset,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyAtoA_v2, (void*) PTR_ORIGINAL_cuMemcpyAtoA_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyHtoAAsync_v2
//int ORIGINAL_cuMemcpyHtoAAsync_v2( CUarray dstArray, size_t dstOffset, const void * srcHost, size_t ByteCount, CUstream hStream ) { }

void * PTR_ORIGINAL_cuMemcpyHtoAAsync_v2;
// This is the call that will take the place of the original
int INTER_cuMemcpyHtoAAsync_v2( CUarray dstArray, size_t dstOffset, const void * srcHost, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstArray,(void **)&dstOffset,(void **)&srcHost,(void **)&ByteCount,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyHtoAAsync_v2, (void*) PTR_ORIGINAL_cuMemcpyHtoAAsync_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyAtoHAsync_v2
//int ORIGINAL_cuMemcpyAtoHAsync_v2( void * dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount, CUstream hStream ) { }

void * PTR_ORIGINAL_cuMemcpyAtoHAsync_v2;
// This is the call that will take the place of the original
int INTER_cuMemcpyAtoHAsync_v2( void * dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstHost,(void **)&srcArray,(void **)&srcOffset,(void **)&ByteCount,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyAtoHAsync_v2, (void*) PTR_ORIGINAL_cuMemcpyAtoHAsync_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpy2D_v2
//int ORIGINAL_cuMemcpy2D_v2( const CUDA_MEMCPY2D * pCopy ) { }

void * PTR_ORIGINAL_cuMemcpy2D_v2;
// This is the call that will take the place of the original
int INTER_cuMemcpy2D_v2( const CUDA_MEMCPY2D * pCopy ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pCopy };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpy2D_v2, (void*) PTR_ORIGINAL_cuMemcpy2D_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpy2DUnaligned_v2
//int ORIGINAL_cuMemcpy2DUnaligned_v2( const CUDA_MEMCPY2D * pCopy ) { }

void * PTR_ORIGINAL_cuMemcpy2DUnaligned_v2;
// This is the call that will take the place of the original
int INTER_cuMemcpy2DUnaligned_v2( const CUDA_MEMCPY2D * pCopy ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pCopy };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpy2DUnaligned_v2, (void*) PTR_ORIGINAL_cuMemcpy2DUnaligned_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpy3D_v2
//int ORIGINAL_cuMemcpy3D_v2( const CUDA_MEMCPY3D * pCopy ) { }

void * PTR_ORIGINAL_cuMemcpy3D_v2;
// This is the call that will take the place of the original
int INTER_cuMemcpy3D_v2( const CUDA_MEMCPY3D * pCopy ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pCopy };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpy3D_v2, (void*) PTR_ORIGINAL_cuMemcpy3D_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyHtoDAsync_v2
//int ORIGINAL_cuMemcpyHtoDAsync_v2( CUdeviceptr dstDevice, const void * srcHost, size_t ByteCount, CUstream hStream ) { }

void * PTR_ORIGINAL_cuMemcpyHtoDAsync_v2;
// This is the call that will take the place of the original
int INTER_cuMemcpyHtoDAsync_v2( CUdeviceptr dstDevice, const void * srcHost, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&srcHost,(void **)&ByteCount,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyHtoDAsync_v2, (void*) PTR_ORIGINAL_cuMemcpyHtoDAsync_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyDtoHAsync_v2
//int ORIGINAL_cuMemcpyDtoHAsync_v2( void * dstHost, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream ) { }

void * PTR_ORIGINAL_cuMemcpyDtoHAsync_v2;
// This is the call that will take the place of the original
int INTER_cuMemcpyDtoHAsync_v2( void * dstHost, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstHost,(void **)&srcDevice,(void **)&ByteCount,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyDtoHAsync_v2, (void*) PTR_ORIGINAL_cuMemcpyDtoHAsync_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyDtoDAsync_v2
//int ORIGINAL_cuMemcpyDtoDAsync_v2( CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream ) { }

void * PTR_ORIGINAL_cuMemcpyDtoDAsync_v2;
// This is the call that will take the place of the original
int INTER_cuMemcpyDtoDAsync_v2( CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&srcDevice,(void **)&ByteCount,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyDtoDAsync_v2, (void*) PTR_ORIGINAL_cuMemcpyDtoDAsync_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpy2DAsync_v2
//int ORIGINAL_cuMemcpy2DAsync_v2( const CUDA_MEMCPY2D * pCopy, CUstream hStream ) { }

void * PTR_ORIGINAL_cuMemcpy2DAsync_v2;
// This is the call that will take the place of the original
int INTER_cuMemcpy2DAsync_v2( const CUDA_MEMCPY2D * pCopy, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pCopy,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpy2DAsync_v2, (void*) PTR_ORIGINAL_cuMemcpy2DAsync_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpy3DAsync_v2
//int ORIGINAL_cuMemcpy3DAsync_v2( const CUDA_MEMCPY3D * pCopy, CUstream hStream ) { }

void * PTR_ORIGINAL_cuMemcpy3DAsync_v2;
// This is the call that will take the place of the original
int INTER_cuMemcpy3DAsync_v2( const CUDA_MEMCPY3D * pCopy, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pCopy,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpy3DAsync_v2, (void*) PTR_ORIGINAL_cuMemcpy3DAsync_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD8_v2
//int ORIGINAL_cuMemsetD8_v2( CUdeviceptr dstDevice, unsigned char uc, size_t N ) { }

void * PTR_ORIGINAL_cuMemsetD8_v2;
// This is the call that will take the place of the original
int INTER_cuMemsetD8_v2( CUdeviceptr dstDevice, unsigned char uc, size_t N ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&uc,(void **)&N };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD8_v2, (void*) PTR_ORIGINAL_cuMemsetD8_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD16_v2
//int ORIGINAL_cuMemsetD16_v2( CUdeviceptr dstDevice, unsigned short us, size_t N ) { }

void * PTR_ORIGINAL_cuMemsetD16_v2;
// This is the call that will take the place of the original
int INTER_cuMemsetD16_v2( CUdeviceptr dstDevice, unsigned short us, size_t N ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&us,(void **)&N };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD16_v2, (void*) PTR_ORIGINAL_cuMemsetD16_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD32_v2
//int ORIGINAL_cuMemsetD32_v2( CUdeviceptr dstDevice, unsigned int ui, size_t N ) { }

void * PTR_ORIGINAL_cuMemsetD32_v2;
// This is the call that will take the place of the original
int INTER_cuMemsetD32_v2( CUdeviceptr dstDevice, unsigned int ui, size_t N ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&ui,(void **)&N };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD32_v2, (void*) PTR_ORIGINAL_cuMemsetD32_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD2D8_v2
//int ORIGINAL_cuMemsetD2D8_v2( CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height ) { }

void * PTR_ORIGINAL_cuMemsetD2D8_v2;
// This is the call that will take the place of the original
int INTER_cuMemsetD2D8_v2( CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&dstPitch,(void **)&uc,(void **)&Width,(void **)&Height };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD2D8_v2, (void*) PTR_ORIGINAL_cuMemsetD2D8_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD2D16_v2
//int ORIGINAL_cuMemsetD2D16_v2( CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height ) { }

void * PTR_ORIGINAL_cuMemsetD2D16_v2;
// This is the call that will take the place of the original
int INTER_cuMemsetD2D16_v2( CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&dstPitch,(void **)&us,(void **)&Width,(void **)&Height };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD2D16_v2, (void*) PTR_ORIGINAL_cuMemsetD2D16_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD2D32_v2
//int ORIGINAL_cuMemsetD2D32_v2( CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height ) { }

void * PTR_ORIGINAL_cuMemsetD2D32_v2;
// This is the call that will take the place of the original
int INTER_cuMemsetD2D32_v2( CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&dstPitch,(void **)&ui,(void **)&Width,(void **)&Height };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD2D32_v2, (void*) PTR_ORIGINAL_cuMemsetD2D32_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}

}static const std::vector<const char *> CallVector = {"cuGetErrorString","cuGetErrorName","cuInit","cuDriverGetVersion","cuDeviceGet","cuDeviceGetCount","cuDeviceGetName","cuDeviceTotalMem","cuDeviceGetAttribute","cuDeviceGetProperties","cuDeviceComputeCapability","cuDevicePrimaryCtxRetain","cuDevicePrimaryCtxRelease","cuDevicePrimaryCtxSetFlags","cuDevicePrimaryCtxGetState","cuDevicePrimaryCtxReset","cuCtxCreate","cuCtxDestroy","cuCtxPushCurrent","cuCtxPopCurrent","cuCtxSetCurrent","cuCtxGetCurrent","cuCtxGetDevice","cuCtxGetFlags","cuCtxSynchronize","cuCtxSetLimit","cuCtxGetLimit","cuCtxGetCacheConfig","cuCtxSetCacheConfig","cuCtxGetSharedMemConfig","cuCtxSetSharedMemConfig","cuCtxGetApiVersion","cuCtxGetStreamPriorityRange","cuCtxAttach","cuCtxDetach","cuModuleLoad","cuModuleLoadData","cuModuleLoadDataEx","cuModuleLoadFatBinary","cuModuleUnload","cuModuleGetFunction","cuModuleGetGlobal","cuModuleGetTexRef","cuModuleGetSurfRef","cuLinkCreate","cuLinkAddData","cuLinkAddFile","cuLinkComplete","cuLinkDestroy","cuMemGetInfo","cuMemAlloc","cuMemAllocPitch","cuMemFree","cuMemGetAddressRange","cuMemAllocHost","cuMemFreeHost","cuMemHostAlloc","cuMemHostGetDevicePointer","cuMemHostGetFlags","cuMemAllocManaged","cuDeviceGetByPCIBusId","cuDeviceGetPCIBusId","cuIpcGetEventHandle","cuIpcOpenEventHandle","cuIpcGetMemHandle","cuIpcOpenMemHandle","cuIpcCloseMemHandle","cuMemHostRegister","cuMemHostUnregister","cuMemcpy","cuMemcpyPeer","cuMemcpyHtoD","cuMemcpyDtoH","cuMemcpyDtoD","cuMemcpyDtoA","cuMemcpyAtoD","cuMemcpyHtoA","cuMemcpyAtoH","cuMemcpyAtoA","cuMemcpy2D","cuMemcpy2DUnaligned","cuMemcpy3D","cuMemcpy3DPeer","cuMemcpyAsync","cuMemcpyPeerAsync","cuMemcpyHtoDAsync","cuMemcpyDtoHAsync","cuMemcpyDtoDAsync","cuMemcpyHtoAAsync","cuMemcpyAtoHAsync","cuMemcpy2DAsync","cuMemcpy3DAsync","cuMemcpy3DPeerAsync","cuMemsetD8","cuMemsetD16","cuMemsetD32","cuMemsetD2D8","cuMemsetD2D16","cuMemsetD2D32","cuMemsetD8Async","cuMemsetD16Async","cuMemsetD32Async","cuMemsetD2D8Async","cuMemsetD2D16Async","cuMemsetD2D32Async","cuArrayCreate","cuArrayGetDescriptor","cuArrayDestroy","cuArray3DCreate","cuArray3DGetDescriptor","cuMipmappedArrayCreate","cuMipmappedArrayGetLevel","cuMipmappedArrayDestroy","cuPointerGetAttribute","cuMemPrefetchAsync","cuMemAdvise","cuMemRangeGetAttribute","cuMemRangeGetAttributes","cuPointerSetAttribute","cuPointerGetAttributes","cuStreamCreate","cuStreamCreateWithPriority","cuStreamGetPriority","cuStreamGetFlags","cuStreamWaitEvent","cuStreamAddCallback","cuStreamAttachMemAsync","cuStreamQuery","cuStreamSynchronize","cuStreamDestroy","cuEventCreate","cuEventRecord","cuEventQuery","cuEventSynchronize","cuEventDestroy","cuEventElapsedTime","cuStreamWaitValue32","cuStreamWriteValue32","cuStreamBatchMemOp","cuFuncGetAttribute","cuFuncSetCacheConfig","cuFuncSetSharedMemConfig","cuLaunchKernel","cuFuncSetBlockShape","cuFuncSetSharedSize","cuParamSetSize","cuParamSeti","cuParamSetf","cuParamSetv","cuLaunch","cuLaunchGrid","cuLaunchGridAsync","cuParamSetTexRef","cuOccupancyMaxActiveBlocksPerMultiprocessor","cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags","cuOccupancyMaxPotentialBlockSize","cuOccupancyMaxPotentialBlockSizeWithFlags","cuTexRefSetArray","cuTexRefSetMipmappedArray","cuTexRefSetAddress","cuTexRefSetAddress2D","cuTexRefSetFormat","cuTexRefSetAddressMode","cuTexRefSetFilterMode","cuTexRefSetMipmapFilterMode","cuTexRefSetMipmapLevelBias","cuTexRefSetMipmapLevelClamp","cuTexRefSetMaxAnisotropy","cuTexRefSetBorderColor","cuTexRefSetFlags","cuTexRefGetAddress","cuTexRefGetArray","cuTexRefGetMipmappedArray","cuTexRefGetAddressMode","cuTexRefGetFilterMode","cuTexRefGetFormat","cuTexRefGetMipmapFilterMode","cuTexRefGetMipmapLevelBias","cuTexRefGetMipmapLevelClamp","cuTexRefGetMaxAnisotropy","cuTexRefGetBorderColor","cuTexRefGetFlags","cuTexRefCreate","cuTexRefDestroy","cuSurfRefSetArray","cuSurfRefGetArray","cuTexObjectCreate","cuTexObjectDestroy","cuTexObjectGetResourceDesc","cuTexObjectGetTextureDesc","cuTexObjectGetResourceViewDesc","cuSurfObjectCreate","cuSurfObjectDestroy","cuSurfObjectGetResourceDesc","cuDeviceCanAccessPeer","cuDeviceGetP2PAttribute","cuCtxEnablePeerAccess","cuCtxDisablePeerAccess","cuGraphicsUnregisterResource","cuGraphicsSubResourceGetMappedArray","cuGraphicsResourceGetMappedMipmappedArray","cuGraphicsResourceGetMappedPointer","cuGraphicsResourceSetMapFlags","cuGraphicsMapResources","cuGraphicsUnmapResources","cuGetExportTable","cuTexRefSetAddress2D_v2","cuMemcpyHtoD_v2","cuMemcpyDtoH_v2","cuMemcpyDtoD_v2","cuMemcpyDtoA_v2","cuMemcpyAtoD_v2","cuMemcpyHtoA_v2","cuMemcpyAtoH_v2","cuMemcpyAtoA_v2","cuMemcpyHtoAAsync_v2","cuMemcpyAtoHAsync_v2","cuMemcpy2D_v2","cuMemcpy2DUnaligned_v2","cuMemcpy3D_v2","cuMemcpyHtoDAsync_v2","cuMemcpyDtoHAsync_v2","cuMemcpyDtoDAsync_v2","cuMemcpy2DAsync_v2","cuMemcpy3DAsync_v2","cuMemsetD8_v2","cuMemsetD16_v2","cuMemsetD32_v2","cuMemsetD2D8_v2","cuMemsetD2D16_v2","cuMemsetD2D32_v2"};

#define DEFINED_TEMPLATES 1
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

// MANUALLY ADDED
EXTERN_FLAG std::function<int(void *, void *, void *)> Bound_InternalSynchronization;
extern "C" void DefineBinders() {
	 void * handle = (void *)dlopen("libcuda.so.1", RTLD_LAZY);
	assert(handle != NULL);
	int (*TMP_PTR_cuGetErrorString)(CUresult,const char * *) = (int(*)(CUresult,const char * *)) dlsym(handle,"PTR_ORIGINAL_cuGetErrorString");
	PTR_ORIGINAL_cuGetErrorString = (void *)dlsym(handle,"PTR_ORIGINAL_cuGetErrorString");
	Bound_cuGetErrorString = std::bind(TMP_PTR_cuGetErrorString,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuGetErrorName)(CUresult,const char * *) = (int(*)(CUresult,const char * *)) dlsym(handle,"PTR_ORIGINAL_cuGetErrorName");
	PTR_ORIGINAL_cuGetErrorName = (void *)dlsym(handle,"PTR_ORIGINAL_cuGetErrorName");
	Bound_cuGetErrorName = std::bind(TMP_PTR_cuGetErrorName,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuInit)(unsigned int) = (int(*)(unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuInit");
	PTR_ORIGINAL_cuInit = (void *)dlsym(handle,"PTR_ORIGINAL_cuInit");
	Bound_cuInit = std::bind(TMP_PTR_cuInit,std::placeholders::_1);
	int (*TMP_PTR_cuDriverGetVersion)(int *) = (int(*)(int *)) dlsym(handle,"PTR_ORIGINAL_cuDriverGetVersion");
	PTR_ORIGINAL_cuDriverGetVersion = (void *)dlsym(handle,"PTR_ORIGINAL_cuDriverGetVersion");
	Bound_cuDriverGetVersion = std::bind(TMP_PTR_cuDriverGetVersion,std::placeholders::_1);
	int (*TMP_PTR_cuDeviceGet)(CUdevice *,int) = (int(*)(CUdevice *,int)) dlsym(handle,"PTR_ORIGINAL_cuDeviceGet");
	PTR_ORIGINAL_cuDeviceGet = (void *)dlsym(handle,"PTR_ORIGINAL_cuDeviceGet");
	Bound_cuDeviceGet = std::bind(TMP_PTR_cuDeviceGet,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuDeviceGetCount)(int *) = (int(*)(int *)) dlsym(handle,"PTR_ORIGINAL_cuDeviceGetCount");
	PTR_ORIGINAL_cuDeviceGetCount = (void *)dlsym(handle,"PTR_ORIGINAL_cuDeviceGetCount");
	Bound_cuDeviceGetCount = std::bind(TMP_PTR_cuDeviceGetCount,std::placeholders::_1);
	int (*TMP_PTR_cuDeviceGetName)(char *,int,CUdevice) = (int(*)(char *,int,CUdevice)) dlsym(handle,"PTR_ORIGINAL_cuDeviceGetName");
	PTR_ORIGINAL_cuDeviceGetName = (void *)dlsym(handle,"PTR_ORIGINAL_cuDeviceGetName");
	Bound_cuDeviceGetName = std::bind(TMP_PTR_cuDeviceGetName,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuDeviceTotalMem)(size_t *,CUdevice) = (int(*)(size_t *,CUdevice)) dlsym(handle,"PTR_ORIGINAL_cuDeviceTotalMem");
	PTR_ORIGINAL_cuDeviceTotalMem = (void *)dlsym(handle,"PTR_ORIGINAL_cuDeviceTotalMem");
	Bound_cuDeviceTotalMem = std::bind(TMP_PTR_cuDeviceTotalMem,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuDeviceGetAttribute)(int *,CUdevice_attribute,CUdevice) = (int(*)(int *,CUdevice_attribute,CUdevice)) dlsym(handle,"PTR_ORIGINAL_cuDeviceGetAttribute");
	PTR_ORIGINAL_cuDeviceGetAttribute = (void *)dlsym(handle,"PTR_ORIGINAL_cuDeviceGetAttribute");
	Bound_cuDeviceGetAttribute = std::bind(TMP_PTR_cuDeviceGetAttribute,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuDeviceGetProperties)(CUdevprop *,CUdevice) = (int(*)(CUdevprop *,CUdevice)) dlsym(handle,"PTR_ORIGINAL_cuDeviceGetProperties");
	PTR_ORIGINAL_cuDeviceGetProperties = (void *)dlsym(handle,"PTR_ORIGINAL_cuDeviceGetProperties");
	Bound_cuDeviceGetProperties = std::bind(TMP_PTR_cuDeviceGetProperties,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuDeviceComputeCapability)(int *,int *,CUdevice) = (int(*)(int *,int *,CUdevice)) dlsym(handle,"PTR_ORIGINAL_cuDeviceComputeCapability");
	PTR_ORIGINAL_cuDeviceComputeCapability = (void *)dlsym(handle,"PTR_ORIGINAL_cuDeviceComputeCapability");
	Bound_cuDeviceComputeCapability = std::bind(TMP_PTR_cuDeviceComputeCapability,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuDevicePrimaryCtxRetain)(CUcontext *,CUdevice) = (int(*)(CUcontext *,CUdevice)) dlsym(handle,"PTR_ORIGINAL_cuDevicePrimaryCtxRetain");
	PTR_ORIGINAL_cuDevicePrimaryCtxRetain = (void *)dlsym(handle,"PTR_ORIGINAL_cuDevicePrimaryCtxRetain");
	Bound_cuDevicePrimaryCtxRetain = std::bind(TMP_PTR_cuDevicePrimaryCtxRetain,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuDevicePrimaryCtxRelease)(CUdevice) = (int(*)(CUdevice)) dlsym(handle,"PTR_ORIGINAL_cuDevicePrimaryCtxRelease");
	PTR_ORIGINAL_cuDevicePrimaryCtxRelease = (void *)dlsym(handle,"PTR_ORIGINAL_cuDevicePrimaryCtxRelease");
	Bound_cuDevicePrimaryCtxRelease = std::bind(TMP_PTR_cuDevicePrimaryCtxRelease,std::placeholders::_1);
	int (*TMP_PTR_cuDevicePrimaryCtxSetFlags)(CUdevice,unsigned int) = (int(*)(CUdevice,unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuDevicePrimaryCtxSetFlags");
	PTR_ORIGINAL_cuDevicePrimaryCtxSetFlags = (void *)dlsym(handle,"PTR_ORIGINAL_cuDevicePrimaryCtxSetFlags");
	Bound_cuDevicePrimaryCtxSetFlags = std::bind(TMP_PTR_cuDevicePrimaryCtxSetFlags,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuDevicePrimaryCtxGetState)(CUdevice,unsigned int *,int *) = (int(*)(CUdevice,unsigned int *,int *)) dlsym(handle,"PTR_ORIGINAL_cuDevicePrimaryCtxGetState");
	PTR_ORIGINAL_cuDevicePrimaryCtxGetState = (void *)dlsym(handle,"PTR_ORIGINAL_cuDevicePrimaryCtxGetState");
	Bound_cuDevicePrimaryCtxGetState = std::bind(TMP_PTR_cuDevicePrimaryCtxGetState,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuDevicePrimaryCtxReset)(CUdevice) = (int(*)(CUdevice)) dlsym(handle,"PTR_ORIGINAL_cuDevicePrimaryCtxReset");
	PTR_ORIGINAL_cuDevicePrimaryCtxReset = (void *)dlsym(handle,"PTR_ORIGINAL_cuDevicePrimaryCtxReset");
	Bound_cuDevicePrimaryCtxReset = std::bind(TMP_PTR_cuDevicePrimaryCtxReset,std::placeholders::_1);
	int (*TMP_PTR_cuCtxCreate)(CUcontext *,unsigned int,CUdevice) = (int(*)(CUcontext *,unsigned int,CUdevice)) dlsym(handle,"PTR_ORIGINAL_cuCtxCreate");
	PTR_ORIGINAL_cuCtxCreate = (void *)dlsym(handle,"PTR_ORIGINAL_cuCtxCreate");
	Bound_cuCtxCreate = std::bind(TMP_PTR_cuCtxCreate,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuCtxDestroy)(CUcontext) = (int(*)(CUcontext)) dlsym(handle,"PTR_ORIGINAL_cuCtxDestroy");
	PTR_ORIGINAL_cuCtxDestroy = (void *)dlsym(handle,"PTR_ORIGINAL_cuCtxDestroy");
	Bound_cuCtxDestroy = std::bind(TMP_PTR_cuCtxDestroy,std::placeholders::_1);
	int (*TMP_PTR_cuCtxPushCurrent)(CUcontext) = (int(*)(CUcontext)) dlsym(handle,"PTR_ORIGINAL_cuCtxPushCurrent");
	PTR_ORIGINAL_cuCtxPushCurrent = (void *)dlsym(handle,"PTR_ORIGINAL_cuCtxPushCurrent");
	Bound_cuCtxPushCurrent = std::bind(TMP_PTR_cuCtxPushCurrent,std::placeholders::_1);
	int (*TMP_PTR_cuCtxPopCurrent)(CUcontext *) = (int(*)(CUcontext *)) dlsym(handle,"PTR_ORIGINAL_cuCtxPopCurrent");
	PTR_ORIGINAL_cuCtxPopCurrent = (void *)dlsym(handle,"PTR_ORIGINAL_cuCtxPopCurrent");
	Bound_cuCtxPopCurrent = std::bind(TMP_PTR_cuCtxPopCurrent,std::placeholders::_1);
	int (*TMP_PTR_cuCtxSetCurrent)(CUcontext) = (int(*)(CUcontext)) dlsym(handle,"PTR_ORIGINAL_cuCtxSetCurrent");
	PTR_ORIGINAL_cuCtxSetCurrent = (void *)dlsym(handle,"PTR_ORIGINAL_cuCtxSetCurrent");
	Bound_cuCtxSetCurrent = std::bind(TMP_PTR_cuCtxSetCurrent,std::placeholders::_1);
	int (*TMP_PTR_cuCtxGetCurrent)(CUcontext *) = (int(*)(CUcontext *)) dlsym(handle,"PTR_ORIGINAL_cuCtxGetCurrent");
	PTR_ORIGINAL_cuCtxGetCurrent = (void *)dlsym(handle,"PTR_ORIGINAL_cuCtxGetCurrent");
	Bound_cuCtxGetCurrent = std::bind(TMP_PTR_cuCtxGetCurrent,std::placeholders::_1);
	int (*TMP_PTR_cuCtxGetDevice)(CUdevice *) = (int(*)(CUdevice *)) dlsym(handle,"PTR_ORIGINAL_cuCtxGetDevice");
	PTR_ORIGINAL_cuCtxGetDevice = (void *)dlsym(handle,"PTR_ORIGINAL_cuCtxGetDevice");
	Bound_cuCtxGetDevice = std::bind(TMP_PTR_cuCtxGetDevice,std::placeholders::_1);
	int (*TMP_PTR_cuCtxGetFlags)(unsigned int *) = (int(*)(unsigned int *)) dlsym(handle,"PTR_ORIGINAL_cuCtxGetFlags");
	PTR_ORIGINAL_cuCtxGetFlags = (void *)dlsym(handle,"PTR_ORIGINAL_cuCtxGetFlags");
	Bound_cuCtxGetFlags = std::bind(TMP_PTR_cuCtxGetFlags,std::placeholders::_1);
	int (*TMP_PTR_cuCtxSynchronize)(void) = (int(*)(void)) dlsym(handle,"PTR_ORIGINAL_cuCtxSynchronize");
	PTR_ORIGINAL_cuCtxSynchronize = (void *)dlsym(handle,"PTR_ORIGINAL_cuCtxSynchronize");
	Bound_cuCtxSynchronize = std::bind(TMP_PTR_cuCtxSynchronize);
	int (*TMP_PTR_cuCtxSetLimit)(CUlimit,size_t) = (int(*)(CUlimit,size_t)) dlsym(handle,"PTR_ORIGINAL_cuCtxSetLimit");
	PTR_ORIGINAL_cuCtxSetLimit = (void *)dlsym(handle,"PTR_ORIGINAL_cuCtxSetLimit");
	Bound_cuCtxSetLimit = std::bind(TMP_PTR_cuCtxSetLimit,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuCtxGetLimit)(size_t *,CUlimit) = (int(*)(size_t *,CUlimit)) dlsym(handle,"PTR_ORIGINAL_cuCtxGetLimit");
	PTR_ORIGINAL_cuCtxGetLimit = (void *)dlsym(handle,"PTR_ORIGINAL_cuCtxGetLimit");
	Bound_cuCtxGetLimit = std::bind(TMP_PTR_cuCtxGetLimit,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuCtxGetCacheConfig)(CUfunc_cache *) = (int(*)(CUfunc_cache *)) dlsym(handle,"PTR_ORIGINAL_cuCtxGetCacheConfig");
	PTR_ORIGINAL_cuCtxGetCacheConfig = (void *)dlsym(handle,"PTR_ORIGINAL_cuCtxGetCacheConfig");
	Bound_cuCtxGetCacheConfig = std::bind(TMP_PTR_cuCtxGetCacheConfig,std::placeholders::_1);
	int (*TMP_PTR_cuCtxSetCacheConfig)(CUfunc_cache) = (int(*)(CUfunc_cache)) dlsym(handle,"PTR_ORIGINAL_cuCtxSetCacheConfig");
	PTR_ORIGINAL_cuCtxSetCacheConfig = (void *)dlsym(handle,"PTR_ORIGINAL_cuCtxSetCacheConfig");
	Bound_cuCtxSetCacheConfig = std::bind(TMP_PTR_cuCtxSetCacheConfig,std::placeholders::_1);
	int (*TMP_PTR_cuCtxGetSharedMemConfig)(CUsharedconfig *) = (int(*)(CUsharedconfig *)) dlsym(handle,"PTR_ORIGINAL_cuCtxGetSharedMemConfig");
	PTR_ORIGINAL_cuCtxGetSharedMemConfig = (void *)dlsym(handle,"PTR_ORIGINAL_cuCtxGetSharedMemConfig");
	Bound_cuCtxGetSharedMemConfig = std::bind(TMP_PTR_cuCtxGetSharedMemConfig,std::placeholders::_1);
	int (*TMP_PTR_cuCtxSetSharedMemConfig)(CUsharedconfig) = (int(*)(CUsharedconfig)) dlsym(handle,"PTR_ORIGINAL_cuCtxSetSharedMemConfig");
	PTR_ORIGINAL_cuCtxSetSharedMemConfig = (void *)dlsym(handle,"PTR_ORIGINAL_cuCtxSetSharedMemConfig");
	Bound_cuCtxSetSharedMemConfig = std::bind(TMP_PTR_cuCtxSetSharedMemConfig,std::placeholders::_1);
	int (*TMP_PTR_cuCtxGetApiVersion)(CUcontext,unsigned int *) = (int(*)(CUcontext,unsigned int *)) dlsym(handle,"PTR_ORIGINAL_cuCtxGetApiVersion");
	PTR_ORIGINAL_cuCtxGetApiVersion = (void *)dlsym(handle,"PTR_ORIGINAL_cuCtxGetApiVersion");
	Bound_cuCtxGetApiVersion = std::bind(TMP_PTR_cuCtxGetApiVersion,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuCtxGetStreamPriorityRange)(int *,int *) = (int(*)(int *,int *)) dlsym(handle,"PTR_ORIGINAL_cuCtxGetStreamPriorityRange");
	PTR_ORIGINAL_cuCtxGetStreamPriorityRange = (void *)dlsym(handle,"PTR_ORIGINAL_cuCtxGetStreamPriorityRange");
	Bound_cuCtxGetStreamPriorityRange = std::bind(TMP_PTR_cuCtxGetStreamPriorityRange,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuCtxAttach)(CUcontext *,unsigned int) = (int(*)(CUcontext *,unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuCtxAttach");
	PTR_ORIGINAL_cuCtxAttach = (void *)dlsym(handle,"PTR_ORIGINAL_cuCtxAttach");
	Bound_cuCtxAttach = std::bind(TMP_PTR_cuCtxAttach,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuCtxDetach)(CUcontext) = (int(*)(CUcontext)) dlsym(handle,"PTR_ORIGINAL_cuCtxDetach");
	PTR_ORIGINAL_cuCtxDetach = (void *)dlsym(handle,"PTR_ORIGINAL_cuCtxDetach");
	Bound_cuCtxDetach = std::bind(TMP_PTR_cuCtxDetach,std::placeholders::_1);
	int (*TMP_PTR_cuModuleLoad)(CUmodule *,const char *) = (int(*)(CUmodule *,const char *)) dlsym(handle,"PTR_ORIGINAL_cuModuleLoad");
	PTR_ORIGINAL_cuModuleLoad = (void *)dlsym(handle,"PTR_ORIGINAL_cuModuleLoad");
	Bound_cuModuleLoad = std::bind(TMP_PTR_cuModuleLoad,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuModuleLoadData)(CUmodule *,const void *) = (int(*)(CUmodule *,const void *)) dlsym(handle,"PTR_ORIGINAL_cuModuleLoadData");
	PTR_ORIGINAL_cuModuleLoadData = (void *)dlsym(handle,"PTR_ORIGINAL_cuModuleLoadData");
	Bound_cuModuleLoadData = std::bind(TMP_PTR_cuModuleLoadData,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuModuleLoadDataEx)(CUmodule *,const void *,unsigned int,CUjit_option *,void * *) = (int(*)(CUmodule *,const void *,unsigned int,CUjit_option *,void * *)) dlsym(handle,"PTR_ORIGINAL_cuModuleLoadDataEx");
	PTR_ORIGINAL_cuModuleLoadDataEx = (void *)dlsym(handle,"PTR_ORIGINAL_cuModuleLoadDataEx");
	Bound_cuModuleLoadDataEx = std::bind(TMP_PTR_cuModuleLoadDataEx,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
	int (*TMP_PTR_cuModuleLoadFatBinary)(CUmodule *,const void *) = (int(*)(CUmodule *,const void *)) dlsym(handle,"PTR_ORIGINAL_cuModuleLoadFatBinary");
	PTR_ORIGINAL_cuModuleLoadFatBinary = (void *)dlsym(handle,"PTR_ORIGINAL_cuModuleLoadFatBinary");
	Bound_cuModuleLoadFatBinary = std::bind(TMP_PTR_cuModuleLoadFatBinary,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuModuleUnload)(CUmodule) = (int(*)(CUmodule)) dlsym(handle,"PTR_ORIGINAL_cuModuleUnload");
	PTR_ORIGINAL_cuModuleUnload = (void *)dlsym(handle,"PTR_ORIGINAL_cuModuleUnload");
	Bound_cuModuleUnload = std::bind(TMP_PTR_cuModuleUnload,std::placeholders::_1);
	int (*TMP_PTR_cuModuleGetFunction)(CUfunction *,CUmodule,const char *) = (int(*)(CUfunction *,CUmodule,const char *)) dlsym(handle,"PTR_ORIGINAL_cuModuleGetFunction");
	PTR_ORIGINAL_cuModuleGetFunction = (void *)dlsym(handle,"PTR_ORIGINAL_cuModuleGetFunction");
	Bound_cuModuleGetFunction = std::bind(TMP_PTR_cuModuleGetFunction,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuModuleGetGlobal)(CUdeviceptr *,size_t *,CUmodule,const char *) = (int(*)(CUdeviceptr *,size_t *,CUmodule,const char *)) dlsym(handle,"PTR_ORIGINAL_cuModuleGetGlobal");
	PTR_ORIGINAL_cuModuleGetGlobal = (void *)dlsym(handle,"PTR_ORIGINAL_cuModuleGetGlobal");
	Bound_cuModuleGetGlobal = std::bind(TMP_PTR_cuModuleGetGlobal,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuModuleGetTexRef)(CUtexref *,CUmodule,const char *) = (int(*)(CUtexref *,CUmodule,const char *)) dlsym(handle,"PTR_ORIGINAL_cuModuleGetTexRef");
	PTR_ORIGINAL_cuModuleGetTexRef = (void *)dlsym(handle,"PTR_ORIGINAL_cuModuleGetTexRef");
	Bound_cuModuleGetTexRef = std::bind(TMP_PTR_cuModuleGetTexRef,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuModuleGetSurfRef)(CUsurfref *,CUmodule,const char *) = (int(*)(CUsurfref *,CUmodule,const char *)) dlsym(handle,"PTR_ORIGINAL_cuModuleGetSurfRef");
	PTR_ORIGINAL_cuModuleGetSurfRef = (void *)dlsym(handle,"PTR_ORIGINAL_cuModuleGetSurfRef");
	Bound_cuModuleGetSurfRef = std::bind(TMP_PTR_cuModuleGetSurfRef,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuLinkCreate)(unsigned int,CUjit_option *,void * *,CUlinkState *) = (int(*)(unsigned int,CUjit_option *,void * *,CUlinkState *)) dlsym(handle,"PTR_ORIGINAL_cuLinkCreate");
	PTR_ORIGINAL_cuLinkCreate = (void *)dlsym(handle,"PTR_ORIGINAL_cuLinkCreate");
	Bound_cuLinkCreate = std::bind(TMP_PTR_cuLinkCreate,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuLinkAddData)(CUlinkState,CUjitInputType,void *,size_t,const char *,unsigned int,CUjit_option *,void * *) = (int(*)(CUlinkState,CUjitInputType,void *,size_t,const char *,unsigned int,CUjit_option *,void * *)) dlsym(handle,"PTR_ORIGINAL_cuLinkAddData");
	PTR_ORIGINAL_cuLinkAddData = (void *)dlsym(handle,"PTR_ORIGINAL_cuLinkAddData");
	Bound_cuLinkAddData = std::bind(TMP_PTR_cuLinkAddData,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5,std::placeholders::_6,std::placeholders::_7,std::placeholders::_8);
	int (*TMP_PTR_cuLinkAddFile)(CUlinkState,CUjitInputType,const char *,unsigned int,CUjit_option *,void * *) = (int(*)(CUlinkState,CUjitInputType,const char *,unsigned int,CUjit_option *,void * *)) dlsym(handle,"PTR_ORIGINAL_cuLinkAddFile");
	PTR_ORIGINAL_cuLinkAddFile = (void *)dlsym(handle,"PTR_ORIGINAL_cuLinkAddFile");
	Bound_cuLinkAddFile = std::bind(TMP_PTR_cuLinkAddFile,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5,std::placeholders::_6);
	int (*TMP_PTR_cuLinkComplete)(CUlinkState,void * *,size_t *) = (int(*)(CUlinkState,void * *,size_t *)) dlsym(handle,"PTR_ORIGINAL_cuLinkComplete");
	PTR_ORIGINAL_cuLinkComplete = (void *)dlsym(handle,"PTR_ORIGINAL_cuLinkComplete");
	Bound_cuLinkComplete = std::bind(TMP_PTR_cuLinkComplete,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuLinkDestroy)(CUlinkState) = (int(*)(CUlinkState)) dlsym(handle,"PTR_ORIGINAL_cuLinkDestroy");
	PTR_ORIGINAL_cuLinkDestroy = (void *)dlsym(handle,"PTR_ORIGINAL_cuLinkDestroy");
	Bound_cuLinkDestroy = std::bind(TMP_PTR_cuLinkDestroy,std::placeholders::_1);
	int (*TMP_PTR_cuMemGetInfo)(size_t *,size_t *) = (int(*)(size_t *,size_t *)) dlsym(handle,"PTR_ORIGINAL_cuMemGetInfo");
	PTR_ORIGINAL_cuMemGetInfo = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemGetInfo");
	Bound_cuMemGetInfo = std::bind(TMP_PTR_cuMemGetInfo,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuMemAlloc)(CUdeviceptr *,size_t) = (int(*)(CUdeviceptr *,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemAlloc");
	PTR_ORIGINAL_cuMemAlloc = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemAlloc");
	Bound_cuMemAlloc = std::bind(TMP_PTR_cuMemAlloc,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuMemAllocPitch)(CUdeviceptr *,size_t *,size_t,size_t,unsigned int) = (int(*)(CUdeviceptr *,size_t *,size_t,size_t,unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuMemAllocPitch");
	PTR_ORIGINAL_cuMemAllocPitch = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemAllocPitch");
	Bound_cuMemAllocPitch = std::bind(TMP_PTR_cuMemAllocPitch,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
	int (*TMP_PTR_cuMemFree)(CUdeviceptr) = (int(*)(CUdeviceptr)) dlsym(handle,"PTR_ORIGINAL_cuMemFree");
	PTR_ORIGINAL_cuMemFree = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemFree");
	Bound_cuMemFree = std::bind(TMP_PTR_cuMemFree,std::placeholders::_1);
	int (*TMP_PTR_cuMemGetAddressRange)(CUdeviceptr *,size_t *,CUdeviceptr) = (int(*)(CUdeviceptr *,size_t *,CUdeviceptr)) dlsym(handle,"PTR_ORIGINAL_cuMemGetAddressRange");
	PTR_ORIGINAL_cuMemGetAddressRange = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemGetAddressRange");
	Bound_cuMemGetAddressRange = std::bind(TMP_PTR_cuMemGetAddressRange,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuMemAllocHost)(void * *,size_t) = (int(*)(void * *,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemAllocHost");
	PTR_ORIGINAL_cuMemAllocHost = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemAllocHost");
	Bound_cuMemAllocHost = std::bind(TMP_PTR_cuMemAllocHost,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuMemFreeHost)(void *) = (int(*)(void *)) dlsym(handle,"PTR_ORIGINAL_cuMemFreeHost");
	PTR_ORIGINAL_cuMemFreeHost = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemFreeHost");
	Bound_cuMemFreeHost = std::bind(TMP_PTR_cuMemFreeHost,std::placeholders::_1);
	int (*TMP_PTR_cuMemHostAlloc)(void * *,size_t,unsigned int) = (int(*)(void * *,size_t,unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuMemHostAlloc");
	PTR_ORIGINAL_cuMemHostAlloc = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemHostAlloc");
	Bound_cuMemHostAlloc = std::bind(TMP_PTR_cuMemHostAlloc,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuMemHostGetDevicePointer)(CUdeviceptr *,void *,unsigned int) = (int(*)(CUdeviceptr *,void *,unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuMemHostGetDevicePointer");
	PTR_ORIGINAL_cuMemHostGetDevicePointer = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemHostGetDevicePointer");
	Bound_cuMemHostGetDevicePointer = std::bind(TMP_PTR_cuMemHostGetDevicePointer,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuMemHostGetFlags)(unsigned int *,void *) = (int(*)(unsigned int *,void *)) dlsym(handle,"PTR_ORIGINAL_cuMemHostGetFlags");
	PTR_ORIGINAL_cuMemHostGetFlags = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemHostGetFlags");
	Bound_cuMemHostGetFlags = std::bind(TMP_PTR_cuMemHostGetFlags,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuMemAllocManaged)(CUdeviceptr *,size_t,unsigned int) = (int(*)(CUdeviceptr *,size_t,unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuMemAllocManaged");
	PTR_ORIGINAL_cuMemAllocManaged = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemAllocManaged");
	Bound_cuMemAllocManaged = std::bind(TMP_PTR_cuMemAllocManaged,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuDeviceGetByPCIBusId)(CUdevice *,const char *) = (int(*)(CUdevice *,const char *)) dlsym(handle,"PTR_ORIGINAL_cuDeviceGetByPCIBusId");
	PTR_ORIGINAL_cuDeviceGetByPCIBusId = (void *)dlsym(handle,"PTR_ORIGINAL_cuDeviceGetByPCIBusId");
	Bound_cuDeviceGetByPCIBusId = std::bind(TMP_PTR_cuDeviceGetByPCIBusId,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuDeviceGetPCIBusId)(char *,int,CUdevice) = (int(*)(char *,int,CUdevice)) dlsym(handle,"PTR_ORIGINAL_cuDeviceGetPCIBusId");
	PTR_ORIGINAL_cuDeviceGetPCIBusId = (void *)dlsym(handle,"PTR_ORIGINAL_cuDeviceGetPCIBusId");
	Bound_cuDeviceGetPCIBusId = std::bind(TMP_PTR_cuDeviceGetPCIBusId,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuIpcGetEventHandle)(CUipcEventHandle *,CUevent) = (int(*)(CUipcEventHandle *,CUevent)) dlsym(handle,"PTR_ORIGINAL_cuIpcGetEventHandle");
	PTR_ORIGINAL_cuIpcGetEventHandle = (void *)dlsym(handle,"PTR_ORIGINAL_cuIpcGetEventHandle");
	Bound_cuIpcGetEventHandle = std::bind(TMP_PTR_cuIpcGetEventHandle,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuIpcOpenEventHandle)(CUevent *,CUipcEventHandle) = (int(*)(CUevent *,CUipcEventHandle)) dlsym(handle,"PTR_ORIGINAL_cuIpcOpenEventHandle");
	PTR_ORIGINAL_cuIpcOpenEventHandle = (void *)dlsym(handle,"PTR_ORIGINAL_cuIpcOpenEventHandle");
	Bound_cuIpcOpenEventHandle = std::bind(TMP_PTR_cuIpcOpenEventHandle,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuIpcGetMemHandle)(CUipcMemHandle *,CUdeviceptr) = (int(*)(CUipcMemHandle *,CUdeviceptr)) dlsym(handle,"PTR_ORIGINAL_cuIpcGetMemHandle");
	PTR_ORIGINAL_cuIpcGetMemHandle = (void *)dlsym(handle,"PTR_ORIGINAL_cuIpcGetMemHandle");
	Bound_cuIpcGetMemHandle = std::bind(TMP_PTR_cuIpcGetMemHandle,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuIpcOpenMemHandle)(CUdeviceptr *,CUipcMemHandle,unsigned int) = (int(*)(CUdeviceptr *,CUipcMemHandle,unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuIpcOpenMemHandle");
	PTR_ORIGINAL_cuIpcOpenMemHandle = (void *)dlsym(handle,"PTR_ORIGINAL_cuIpcOpenMemHandle");
	Bound_cuIpcOpenMemHandle = std::bind(TMP_PTR_cuIpcOpenMemHandle,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuIpcCloseMemHandle)(CUdeviceptr) = (int(*)(CUdeviceptr)) dlsym(handle,"PTR_ORIGINAL_cuIpcCloseMemHandle");
	PTR_ORIGINAL_cuIpcCloseMemHandle = (void *)dlsym(handle,"PTR_ORIGINAL_cuIpcCloseMemHandle");
	Bound_cuIpcCloseMemHandle = std::bind(TMP_PTR_cuIpcCloseMemHandle,std::placeholders::_1);
	int (*TMP_PTR_cuMemHostRegister)(void *,size_t,unsigned int) = (int(*)(void *,size_t,unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuMemHostRegister");
	PTR_ORIGINAL_cuMemHostRegister = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemHostRegister");
	Bound_cuMemHostRegister = std::bind(TMP_PTR_cuMemHostRegister,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuMemHostUnregister)(void *) = (int(*)(void *)) dlsym(handle,"PTR_ORIGINAL_cuMemHostUnregister");
	PTR_ORIGINAL_cuMemHostUnregister = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemHostUnregister");
	Bound_cuMemHostUnregister = std::bind(TMP_PTR_cuMemHostUnregister,std::placeholders::_1);
	int (*TMP_PTR_cuMemcpy)(CUdeviceptr,CUdeviceptr,size_t) = (int(*)(CUdeviceptr,CUdeviceptr,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemcpy");
	PTR_ORIGINAL_cuMemcpy = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpy");
	Bound_cuMemcpy = std::bind(TMP_PTR_cuMemcpy,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuMemcpyPeer)(CUdeviceptr,CUcontext,CUdeviceptr,CUcontext,size_t) = (int(*)(CUdeviceptr,CUcontext,CUdeviceptr,CUcontext,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemcpyPeer");
	PTR_ORIGINAL_cuMemcpyPeer = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpyPeer");
	Bound_cuMemcpyPeer = std::bind(TMP_PTR_cuMemcpyPeer,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
	int (*TMP_PTR_cuMemcpyHtoD)(CUdeviceptr,const void *,size_t) = (int(*)(CUdeviceptr,const void *,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemcpyHtoD");
	PTR_ORIGINAL_cuMemcpyHtoD = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpyHtoD");
	Bound_cuMemcpyHtoD = std::bind(TMP_PTR_cuMemcpyHtoD,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuMemcpyDtoH)(void *,CUdeviceptr,size_t) = (int(*)(void *,CUdeviceptr,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemcpyDtoH");
	PTR_ORIGINAL_cuMemcpyDtoH = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpyDtoH");
	Bound_cuMemcpyDtoH = std::bind(TMP_PTR_cuMemcpyDtoH,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuMemcpyDtoD)(CUdeviceptr,CUdeviceptr,size_t) = (int(*)(CUdeviceptr,CUdeviceptr,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemcpyDtoD");
	PTR_ORIGINAL_cuMemcpyDtoD = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpyDtoD");
	Bound_cuMemcpyDtoD = std::bind(TMP_PTR_cuMemcpyDtoD,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuMemcpyDtoA)(CUarray,size_t,CUdeviceptr,size_t) = (int(*)(CUarray,size_t,CUdeviceptr,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemcpyDtoA");
	PTR_ORIGINAL_cuMemcpyDtoA = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpyDtoA");
	Bound_cuMemcpyDtoA = std::bind(TMP_PTR_cuMemcpyDtoA,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuMemcpyAtoD)(CUdeviceptr,CUarray,size_t,size_t) = (int(*)(CUdeviceptr,CUarray,size_t,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemcpyAtoD");
	PTR_ORIGINAL_cuMemcpyAtoD = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpyAtoD");
	Bound_cuMemcpyAtoD = std::bind(TMP_PTR_cuMemcpyAtoD,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuMemcpyHtoA)(CUarray,size_t,const void *,size_t) = (int(*)(CUarray,size_t,const void *,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemcpyHtoA");
	PTR_ORIGINAL_cuMemcpyHtoA = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpyHtoA");
	Bound_cuMemcpyHtoA = std::bind(TMP_PTR_cuMemcpyHtoA,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuMemcpyAtoH)(void *,CUarray,size_t,size_t) = (int(*)(void *,CUarray,size_t,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemcpyAtoH");
	PTR_ORIGINAL_cuMemcpyAtoH = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpyAtoH");
	Bound_cuMemcpyAtoH = std::bind(TMP_PTR_cuMemcpyAtoH,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuMemcpyAtoA)(CUarray,size_t,CUarray,size_t,size_t) = (int(*)(CUarray,size_t,CUarray,size_t,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemcpyAtoA");
	PTR_ORIGINAL_cuMemcpyAtoA = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpyAtoA");
	Bound_cuMemcpyAtoA = std::bind(TMP_PTR_cuMemcpyAtoA,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
	int (*TMP_PTR_cuMemcpy2D)(const CUDA_MEMCPY2D *) = (int(*)(const CUDA_MEMCPY2D *)) dlsym(handle,"PTR_ORIGINAL_cuMemcpy2D");
	PTR_ORIGINAL_cuMemcpy2D = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpy2D");
	Bound_cuMemcpy2D = std::bind(TMP_PTR_cuMemcpy2D,std::placeholders::_1);
	int (*TMP_PTR_cuMemcpy2DUnaligned)(const CUDA_MEMCPY2D *) = (int(*)(const CUDA_MEMCPY2D *)) dlsym(handle,"PTR_ORIGINAL_cuMemcpy2DUnaligned");
	PTR_ORIGINAL_cuMemcpy2DUnaligned = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpy2DUnaligned");
	Bound_cuMemcpy2DUnaligned = std::bind(TMP_PTR_cuMemcpy2DUnaligned,std::placeholders::_1);
	int (*TMP_PTR_cuMemcpy3D)(const CUDA_MEMCPY3D *) = (int(*)(const CUDA_MEMCPY3D *)) dlsym(handle,"PTR_ORIGINAL_cuMemcpy3D");
	PTR_ORIGINAL_cuMemcpy3D = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpy3D");
	Bound_cuMemcpy3D = std::bind(TMP_PTR_cuMemcpy3D,std::placeholders::_1);
	int (*TMP_PTR_cuMemcpy3DPeer)(const CUDA_MEMCPY3D_PEER *) = (int(*)(const CUDA_MEMCPY3D_PEER *)) dlsym(handle,"PTR_ORIGINAL_cuMemcpy3DPeer");
	PTR_ORIGINAL_cuMemcpy3DPeer = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpy3DPeer");
	Bound_cuMemcpy3DPeer = std::bind(TMP_PTR_cuMemcpy3DPeer,std::placeholders::_1);
	int (*TMP_PTR_cuMemcpyAsync)(CUdeviceptr,CUdeviceptr,size_t,CUstream) = (int(*)(CUdeviceptr,CUdeviceptr,size_t,CUstream)) dlsym(handle,"PTR_ORIGINAL_cuMemcpyAsync");
	PTR_ORIGINAL_cuMemcpyAsync = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpyAsync");
	Bound_cuMemcpyAsync = std::bind(TMP_PTR_cuMemcpyAsync,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuMemcpyPeerAsync)(CUdeviceptr,CUcontext,CUdeviceptr,CUcontext,size_t,CUstream) = (int(*)(CUdeviceptr,CUcontext,CUdeviceptr,CUcontext,size_t,CUstream)) dlsym(handle,"PTR_ORIGINAL_cuMemcpyPeerAsync");
	PTR_ORIGINAL_cuMemcpyPeerAsync = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpyPeerAsync");
	Bound_cuMemcpyPeerAsync = std::bind(TMP_PTR_cuMemcpyPeerAsync,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5,std::placeholders::_6);
	int (*TMP_PTR_cuMemcpyHtoDAsync)(CUdeviceptr,const void *,size_t,CUstream) = (int(*)(CUdeviceptr,const void *,size_t,CUstream)) dlsym(handle,"PTR_ORIGINAL_cuMemcpyHtoDAsync");
	PTR_ORIGINAL_cuMemcpyHtoDAsync = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpyHtoDAsync");
	Bound_cuMemcpyHtoDAsync = std::bind(TMP_PTR_cuMemcpyHtoDAsync,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuMemcpyDtoHAsync)(void *,CUdeviceptr,size_t,CUstream) = (int(*)(void *,CUdeviceptr,size_t,CUstream)) dlsym(handle,"PTR_ORIGINAL_cuMemcpyDtoHAsync");
	PTR_ORIGINAL_cuMemcpyDtoHAsync = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpyDtoHAsync");
	Bound_cuMemcpyDtoHAsync = std::bind(TMP_PTR_cuMemcpyDtoHAsync,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuMemcpyDtoDAsync)(CUdeviceptr,CUdeviceptr,size_t,CUstream) = (int(*)(CUdeviceptr,CUdeviceptr,size_t,CUstream)) dlsym(handle,"PTR_ORIGINAL_cuMemcpyDtoDAsync");
	PTR_ORIGINAL_cuMemcpyDtoDAsync = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpyDtoDAsync");
	Bound_cuMemcpyDtoDAsync = std::bind(TMP_PTR_cuMemcpyDtoDAsync,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuMemcpyHtoAAsync)(CUarray,size_t,const void *,size_t,CUstream) = (int(*)(CUarray,size_t,const void *,size_t,CUstream)) dlsym(handle,"PTR_ORIGINAL_cuMemcpyHtoAAsync");
	PTR_ORIGINAL_cuMemcpyHtoAAsync = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpyHtoAAsync");
	Bound_cuMemcpyHtoAAsync = std::bind(TMP_PTR_cuMemcpyHtoAAsync,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
	int (*TMP_PTR_cuMemcpyAtoHAsync)(void *,CUarray,size_t,size_t,CUstream) = (int(*)(void *,CUarray,size_t,size_t,CUstream)) dlsym(handle,"PTR_ORIGINAL_cuMemcpyAtoHAsync");
	PTR_ORIGINAL_cuMemcpyAtoHAsync = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpyAtoHAsync");
	Bound_cuMemcpyAtoHAsync = std::bind(TMP_PTR_cuMemcpyAtoHAsync,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
	int (*TMP_PTR_cuMemcpy2DAsync)(const CUDA_MEMCPY2D *,CUstream) = (int(*)(const CUDA_MEMCPY2D *,CUstream)) dlsym(handle,"PTR_ORIGINAL_cuMemcpy2DAsync");
	PTR_ORIGINAL_cuMemcpy2DAsync = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpy2DAsync");
	Bound_cuMemcpy2DAsync = std::bind(TMP_PTR_cuMemcpy2DAsync,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuMemcpy3DAsync)(const CUDA_MEMCPY3D *,CUstream) = (int(*)(const CUDA_MEMCPY3D *,CUstream)) dlsym(handle,"PTR_ORIGINAL_cuMemcpy3DAsync");
	PTR_ORIGINAL_cuMemcpy3DAsync = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpy3DAsync");
	Bound_cuMemcpy3DAsync = std::bind(TMP_PTR_cuMemcpy3DAsync,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuMemcpy3DPeerAsync)(const CUDA_MEMCPY3D_PEER *,CUstream) = (int(*)(const CUDA_MEMCPY3D_PEER *,CUstream)) dlsym(handle,"PTR_ORIGINAL_cuMemcpy3DPeerAsync");
	PTR_ORIGINAL_cuMemcpy3DPeerAsync = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpy3DPeerAsync");
	Bound_cuMemcpy3DPeerAsync = std::bind(TMP_PTR_cuMemcpy3DPeerAsync,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuMemsetD8)(CUdeviceptr,unsigned char,size_t) = (int(*)(CUdeviceptr,unsigned char,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemsetD8");
	PTR_ORIGINAL_cuMemsetD8 = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemsetD8");
	Bound_cuMemsetD8 = std::bind(TMP_PTR_cuMemsetD8,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuMemsetD16)(CUdeviceptr,unsigned short,size_t) = (int(*)(CUdeviceptr,unsigned short,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemsetD16");
	PTR_ORIGINAL_cuMemsetD16 = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemsetD16");
	Bound_cuMemsetD16 = std::bind(TMP_PTR_cuMemsetD16,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuMemsetD32)(CUdeviceptr,unsigned int,size_t) = (int(*)(CUdeviceptr,unsigned int,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemsetD32");
	PTR_ORIGINAL_cuMemsetD32 = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemsetD32");
	Bound_cuMemsetD32 = std::bind(TMP_PTR_cuMemsetD32,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuMemsetD2D8)(CUdeviceptr,size_t,unsigned char,size_t,size_t) = (int(*)(CUdeviceptr,size_t,unsigned char,size_t,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemsetD2D8");
	PTR_ORIGINAL_cuMemsetD2D8 = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemsetD2D8");
	Bound_cuMemsetD2D8 = std::bind(TMP_PTR_cuMemsetD2D8,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
	int (*TMP_PTR_cuMemsetD2D16)(CUdeviceptr,size_t,unsigned short,size_t,size_t) = (int(*)(CUdeviceptr,size_t,unsigned short,size_t,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemsetD2D16");
	PTR_ORIGINAL_cuMemsetD2D16 = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemsetD2D16");
	Bound_cuMemsetD2D16 = std::bind(TMP_PTR_cuMemsetD2D16,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
	int (*TMP_PTR_cuMemsetD2D32)(CUdeviceptr,size_t,unsigned int,size_t,size_t) = (int(*)(CUdeviceptr,size_t,unsigned int,size_t,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemsetD2D32");
	PTR_ORIGINAL_cuMemsetD2D32 = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemsetD2D32");
	Bound_cuMemsetD2D32 = std::bind(TMP_PTR_cuMemsetD2D32,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
	int (*TMP_PTR_cuMemsetD8Async)(CUdeviceptr,unsigned char,size_t,CUstream) = (int(*)(CUdeviceptr,unsigned char,size_t,CUstream)) dlsym(handle,"PTR_ORIGINAL_cuMemsetD8Async");
	PTR_ORIGINAL_cuMemsetD8Async = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemsetD8Async");
	Bound_cuMemsetD8Async = std::bind(TMP_PTR_cuMemsetD8Async,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuMemsetD16Async)(CUdeviceptr,unsigned short,size_t,CUstream) = (int(*)(CUdeviceptr,unsigned short,size_t,CUstream)) dlsym(handle,"PTR_ORIGINAL_cuMemsetD16Async");
	PTR_ORIGINAL_cuMemsetD16Async = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemsetD16Async");
	Bound_cuMemsetD16Async = std::bind(TMP_PTR_cuMemsetD16Async,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuMemsetD32Async)(CUdeviceptr,unsigned int,size_t,CUstream) = (int(*)(CUdeviceptr,unsigned int,size_t,CUstream)) dlsym(handle,"PTR_ORIGINAL_cuMemsetD32Async");
	PTR_ORIGINAL_cuMemsetD32Async = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemsetD32Async");
	Bound_cuMemsetD32Async = std::bind(TMP_PTR_cuMemsetD32Async,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuMemsetD2D8Async)(CUdeviceptr,size_t,unsigned char,size_t,size_t,CUstream) = (int(*)(CUdeviceptr,size_t,unsigned char,size_t,size_t,CUstream)) dlsym(handle,"PTR_ORIGINAL_cuMemsetD2D8Async");
	PTR_ORIGINAL_cuMemsetD2D8Async = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemsetD2D8Async");
	Bound_cuMemsetD2D8Async = std::bind(TMP_PTR_cuMemsetD2D8Async,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5,std::placeholders::_6);
	int (*TMP_PTR_cuMemsetD2D16Async)(CUdeviceptr,size_t,unsigned short,size_t,size_t,CUstream) = (int(*)(CUdeviceptr,size_t,unsigned short,size_t,size_t,CUstream)) dlsym(handle,"PTR_ORIGINAL_cuMemsetD2D16Async");
	PTR_ORIGINAL_cuMemsetD2D16Async = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemsetD2D16Async");
	Bound_cuMemsetD2D16Async = std::bind(TMP_PTR_cuMemsetD2D16Async,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5,std::placeholders::_6);
	int (*TMP_PTR_cuMemsetD2D32Async)(CUdeviceptr,size_t,unsigned int,size_t,size_t,CUstream) = (int(*)(CUdeviceptr,size_t,unsigned int,size_t,size_t,CUstream)) dlsym(handle,"PTR_ORIGINAL_cuMemsetD2D32Async");
	PTR_ORIGINAL_cuMemsetD2D32Async = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemsetD2D32Async");
	Bound_cuMemsetD2D32Async = std::bind(TMP_PTR_cuMemsetD2D32Async,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5,std::placeholders::_6);
	int (*TMP_PTR_cuArrayCreate)(CUarray *,const CUDA_ARRAY_DESCRIPTOR *) = (int(*)(CUarray *,const CUDA_ARRAY_DESCRIPTOR *)) dlsym(handle,"PTR_ORIGINAL_cuArrayCreate");
	PTR_ORIGINAL_cuArrayCreate = (void *)dlsym(handle,"PTR_ORIGINAL_cuArrayCreate");
	Bound_cuArrayCreate = std::bind(TMP_PTR_cuArrayCreate,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuArrayGetDescriptor)(CUDA_ARRAY_DESCRIPTOR *,CUarray) = (int(*)(CUDA_ARRAY_DESCRIPTOR *,CUarray)) dlsym(handle,"PTR_ORIGINAL_cuArrayGetDescriptor");
	PTR_ORIGINAL_cuArrayGetDescriptor = (void *)dlsym(handle,"PTR_ORIGINAL_cuArrayGetDescriptor");
	Bound_cuArrayGetDescriptor = std::bind(TMP_PTR_cuArrayGetDescriptor,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuArrayDestroy)(CUarray) = (int(*)(CUarray)) dlsym(handle,"PTR_ORIGINAL_cuArrayDestroy");
	PTR_ORIGINAL_cuArrayDestroy = (void *)dlsym(handle,"PTR_ORIGINAL_cuArrayDestroy");
	Bound_cuArrayDestroy = std::bind(TMP_PTR_cuArrayDestroy,std::placeholders::_1);
	int (*TMP_PTR_cuArray3DCreate)(CUarray *,const CUDA_ARRAY3D_DESCRIPTOR *) = (int(*)(CUarray *,const CUDA_ARRAY3D_DESCRIPTOR *)) dlsym(handle,"PTR_ORIGINAL_cuArray3DCreate");
	PTR_ORIGINAL_cuArray3DCreate = (void *)dlsym(handle,"PTR_ORIGINAL_cuArray3DCreate");
	Bound_cuArray3DCreate = std::bind(TMP_PTR_cuArray3DCreate,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuArray3DGetDescriptor)(CUDA_ARRAY3D_DESCRIPTOR *,CUarray) = (int(*)(CUDA_ARRAY3D_DESCRIPTOR *,CUarray)) dlsym(handle,"PTR_ORIGINAL_cuArray3DGetDescriptor");
	PTR_ORIGINAL_cuArray3DGetDescriptor = (void *)dlsym(handle,"PTR_ORIGINAL_cuArray3DGetDescriptor");
	Bound_cuArray3DGetDescriptor = std::bind(TMP_PTR_cuArray3DGetDescriptor,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuMipmappedArrayCreate)(CUmipmappedArray *,const CUDA_ARRAY3D_DESCRIPTOR *,unsigned int) = (int(*)(CUmipmappedArray *,const CUDA_ARRAY3D_DESCRIPTOR *,unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuMipmappedArrayCreate");
	PTR_ORIGINAL_cuMipmappedArrayCreate = (void *)dlsym(handle,"PTR_ORIGINAL_cuMipmappedArrayCreate");
	Bound_cuMipmappedArrayCreate = std::bind(TMP_PTR_cuMipmappedArrayCreate,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuMipmappedArrayGetLevel)(CUarray *,CUmipmappedArray,unsigned int) = (int(*)(CUarray *,CUmipmappedArray,unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuMipmappedArrayGetLevel");
	PTR_ORIGINAL_cuMipmappedArrayGetLevel = (void *)dlsym(handle,"PTR_ORIGINAL_cuMipmappedArrayGetLevel");
	Bound_cuMipmappedArrayGetLevel = std::bind(TMP_PTR_cuMipmappedArrayGetLevel,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuMipmappedArrayDestroy)(CUmipmappedArray) = (int(*)(CUmipmappedArray)) dlsym(handle,"PTR_ORIGINAL_cuMipmappedArrayDestroy");
	PTR_ORIGINAL_cuMipmappedArrayDestroy = (void *)dlsym(handle,"PTR_ORIGINAL_cuMipmappedArrayDestroy");
	Bound_cuMipmappedArrayDestroy = std::bind(TMP_PTR_cuMipmappedArrayDestroy,std::placeholders::_1);
	int (*TMP_PTR_cuPointerGetAttribute)(void *,CUpointer_attribute,CUdeviceptr) = (int(*)(void *,CUpointer_attribute,CUdeviceptr)) dlsym(handle,"PTR_ORIGINAL_cuPointerGetAttribute");
	PTR_ORIGINAL_cuPointerGetAttribute = (void *)dlsym(handle,"PTR_ORIGINAL_cuPointerGetAttribute");
	Bound_cuPointerGetAttribute = std::bind(TMP_PTR_cuPointerGetAttribute,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuMemPrefetchAsync)(CUdeviceptr,size_t,CUdevice,CUstream) = (int(*)(CUdeviceptr,size_t,CUdevice,CUstream)) dlsym(handle,"PTR_ORIGINAL_cuMemPrefetchAsync");
	PTR_ORIGINAL_cuMemPrefetchAsync = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemPrefetchAsync");
	Bound_cuMemPrefetchAsync = std::bind(TMP_PTR_cuMemPrefetchAsync,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuMemAdvise)(CUdeviceptr,size_t,CUmem_advise,CUdevice) = (int(*)(CUdeviceptr,size_t,CUmem_advise,CUdevice)) dlsym(handle,"PTR_ORIGINAL_cuMemAdvise");
	PTR_ORIGINAL_cuMemAdvise = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemAdvise");
	Bound_cuMemAdvise = std::bind(TMP_PTR_cuMemAdvise,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuMemRangeGetAttribute)(void *,size_t,CUmem_range_attribute,CUdeviceptr,size_t) = (int(*)(void *,size_t,CUmem_range_attribute,CUdeviceptr,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemRangeGetAttribute");
	PTR_ORIGINAL_cuMemRangeGetAttribute = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemRangeGetAttribute");
	Bound_cuMemRangeGetAttribute = std::bind(TMP_PTR_cuMemRangeGetAttribute,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
	int (*TMP_PTR_cuMemRangeGetAttributes)(void * *,size_t *,CUmem_range_attribute *,size_t,CUdeviceptr,size_t) = (int(*)(void * *,size_t *,CUmem_range_attribute *,size_t,CUdeviceptr,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemRangeGetAttributes");
	PTR_ORIGINAL_cuMemRangeGetAttributes = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemRangeGetAttributes");
	Bound_cuMemRangeGetAttributes = std::bind(TMP_PTR_cuMemRangeGetAttributes,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5,std::placeholders::_6);
	int (*TMP_PTR_cuPointerSetAttribute)(const void *,CUpointer_attribute,CUdeviceptr) = (int(*)(const void *,CUpointer_attribute,CUdeviceptr)) dlsym(handle,"PTR_ORIGINAL_cuPointerSetAttribute");
	PTR_ORIGINAL_cuPointerSetAttribute = (void *)dlsym(handle,"PTR_ORIGINAL_cuPointerSetAttribute");
	Bound_cuPointerSetAttribute = std::bind(TMP_PTR_cuPointerSetAttribute,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuPointerGetAttributes)(unsigned int,CUpointer_attribute *,void * *,CUdeviceptr) = (int(*)(unsigned int,CUpointer_attribute *,void * *,CUdeviceptr)) dlsym(handle,"PTR_ORIGINAL_cuPointerGetAttributes");
	PTR_ORIGINAL_cuPointerGetAttributes = (void *)dlsym(handle,"PTR_ORIGINAL_cuPointerGetAttributes");
	Bound_cuPointerGetAttributes = std::bind(TMP_PTR_cuPointerGetAttributes,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuStreamCreate)(CUstream *,unsigned int) = (int(*)(CUstream *,unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuStreamCreate");
	PTR_ORIGINAL_cuStreamCreate = (void *)dlsym(handle,"PTR_ORIGINAL_cuStreamCreate");
	Bound_cuStreamCreate = std::bind(TMP_PTR_cuStreamCreate,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuStreamCreateWithPriority)(CUstream *,unsigned int,int) = (int(*)(CUstream *,unsigned int,int)) dlsym(handle,"PTR_ORIGINAL_cuStreamCreateWithPriority");
	PTR_ORIGINAL_cuStreamCreateWithPriority = (void *)dlsym(handle,"PTR_ORIGINAL_cuStreamCreateWithPriority");
	Bound_cuStreamCreateWithPriority = std::bind(TMP_PTR_cuStreamCreateWithPriority,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuStreamGetPriority)(CUstream,int *) = (int(*)(CUstream,int *)) dlsym(handle,"PTR_ORIGINAL_cuStreamGetPriority");
	PTR_ORIGINAL_cuStreamGetPriority = (void *)dlsym(handle,"PTR_ORIGINAL_cuStreamGetPriority");
	Bound_cuStreamGetPriority = std::bind(TMP_PTR_cuStreamGetPriority,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuStreamGetFlags)(CUstream,unsigned int *) = (int(*)(CUstream,unsigned int *)) dlsym(handle,"PTR_ORIGINAL_cuStreamGetFlags");
	PTR_ORIGINAL_cuStreamGetFlags = (void *)dlsym(handle,"PTR_ORIGINAL_cuStreamGetFlags");
	Bound_cuStreamGetFlags = std::bind(TMP_PTR_cuStreamGetFlags,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuStreamWaitEvent)(CUstream,CUevent,unsigned int) = (int(*)(CUstream,CUevent,unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuStreamWaitEvent");
	PTR_ORIGINAL_cuStreamWaitEvent = (void *)dlsym(handle,"PTR_ORIGINAL_cuStreamWaitEvent");
	Bound_cuStreamWaitEvent = std::bind(TMP_PTR_cuStreamWaitEvent,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuStreamAddCallback)(CUstream,CUstreamCallback,void *,unsigned int) = (int(*)(CUstream,CUstreamCallback,void *,unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuStreamAddCallback");
	PTR_ORIGINAL_cuStreamAddCallback = (void *)dlsym(handle,"PTR_ORIGINAL_cuStreamAddCallback");
	Bound_cuStreamAddCallback = std::bind(TMP_PTR_cuStreamAddCallback,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuStreamAttachMemAsync)(CUstream,CUdeviceptr,size_t,unsigned int) = (int(*)(CUstream,CUdeviceptr,size_t,unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuStreamAttachMemAsync");
	PTR_ORIGINAL_cuStreamAttachMemAsync = (void *)dlsym(handle,"PTR_ORIGINAL_cuStreamAttachMemAsync");
	Bound_cuStreamAttachMemAsync = std::bind(TMP_PTR_cuStreamAttachMemAsync,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuStreamQuery)(CUstream) = (int(*)(CUstream)) dlsym(handle,"PTR_ORIGINAL_cuStreamQuery");
	PTR_ORIGINAL_cuStreamQuery = (void *)dlsym(handle,"PTR_ORIGINAL_cuStreamQuery");
	Bound_cuStreamQuery = std::bind(TMP_PTR_cuStreamQuery,std::placeholders::_1);
	int (*TMP_PTR_cuStreamSynchronize)(CUstream) = (int(*)(CUstream)) dlsym(handle,"PTR_ORIGINAL_cuStreamSynchronize");
	PTR_ORIGINAL_cuStreamSynchronize = (void *)dlsym(handle,"PTR_ORIGINAL_cuStreamSynchronize");
	Bound_cuStreamSynchronize = std::bind(TMP_PTR_cuStreamSynchronize,std::placeholders::_1);
	int (*TMP_PTR_cuStreamDestroy)(CUstream) = (int(*)(CUstream)) dlsym(handle,"PTR_ORIGINAL_cuStreamDestroy");
	PTR_ORIGINAL_cuStreamDestroy = (void *)dlsym(handle,"PTR_ORIGINAL_cuStreamDestroy");
	Bound_cuStreamDestroy = std::bind(TMP_PTR_cuStreamDestroy,std::placeholders::_1);
	int (*TMP_PTR_cuEventCreate)(CUevent *,unsigned int) = (int(*)(CUevent *,unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuEventCreate");
	PTR_ORIGINAL_cuEventCreate = (void *)dlsym(handle,"PTR_ORIGINAL_cuEventCreate");
	Bound_cuEventCreate = std::bind(TMP_PTR_cuEventCreate,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuEventRecord)(CUevent,CUstream) = (int(*)(CUevent,CUstream)) dlsym(handle,"PTR_ORIGINAL_cuEventRecord");
	PTR_ORIGINAL_cuEventRecord = (void *)dlsym(handle,"PTR_ORIGINAL_cuEventRecord");
	Bound_cuEventRecord = std::bind(TMP_PTR_cuEventRecord,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuEventQuery)(CUevent) = (int(*)(CUevent)) dlsym(handle,"PTR_ORIGINAL_cuEventQuery");
	PTR_ORIGINAL_cuEventQuery = (void *)dlsym(handle,"PTR_ORIGINAL_cuEventQuery");
	Bound_cuEventQuery = std::bind(TMP_PTR_cuEventQuery,std::placeholders::_1);
	int (*TMP_PTR_cuEventSynchronize)(CUevent) = (int(*)(CUevent)) dlsym(handle,"PTR_ORIGINAL_cuEventSynchronize");
	PTR_ORIGINAL_cuEventSynchronize = (void *)dlsym(handle,"PTR_ORIGINAL_cuEventSynchronize");
	Bound_cuEventSynchronize = std::bind(TMP_PTR_cuEventSynchronize,std::placeholders::_1);
	int (*TMP_PTR_cuEventDestroy)(CUevent) = (int(*)(CUevent)) dlsym(handle,"PTR_ORIGINAL_cuEventDestroy");
	PTR_ORIGINAL_cuEventDestroy = (void *)dlsym(handle,"PTR_ORIGINAL_cuEventDestroy");
	Bound_cuEventDestroy = std::bind(TMP_PTR_cuEventDestroy,std::placeholders::_1);
	int (*TMP_PTR_cuEventElapsedTime)(float *,CUevent,CUevent) = (int(*)(float *,CUevent,CUevent)) dlsym(handle,"PTR_ORIGINAL_cuEventElapsedTime");
	PTR_ORIGINAL_cuEventElapsedTime = (void *)dlsym(handle,"PTR_ORIGINAL_cuEventElapsedTime");
	Bound_cuEventElapsedTime = std::bind(TMP_PTR_cuEventElapsedTime,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuStreamWaitValue32)(CUstream,CUdeviceptr,cuuint32_t,unsigned int) = (int(*)(CUstream,CUdeviceptr,cuuint32_t,unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuStreamWaitValue32");
	PTR_ORIGINAL_cuStreamWaitValue32 = (void *)dlsym(handle,"PTR_ORIGINAL_cuStreamWaitValue32");
	Bound_cuStreamWaitValue32 = std::bind(TMP_PTR_cuStreamWaitValue32,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuStreamWriteValue32)(CUstream,CUdeviceptr,cuuint32_t,unsigned int) = (int(*)(CUstream,CUdeviceptr,cuuint32_t,unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuStreamWriteValue32");
	PTR_ORIGINAL_cuStreamWriteValue32 = (void *)dlsym(handle,"PTR_ORIGINAL_cuStreamWriteValue32");
	Bound_cuStreamWriteValue32 = std::bind(TMP_PTR_cuStreamWriteValue32,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuStreamBatchMemOp)(CUstream,unsigned int,CUstreamBatchMemOpParams *,unsigned int) = (int(*)(CUstream,unsigned int,CUstreamBatchMemOpParams *,unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuStreamBatchMemOp");
	PTR_ORIGINAL_cuStreamBatchMemOp = (void *)dlsym(handle,"PTR_ORIGINAL_cuStreamBatchMemOp");
	Bound_cuStreamBatchMemOp = std::bind(TMP_PTR_cuStreamBatchMemOp,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuFuncGetAttribute)(int *,CUfunction_attribute,CUfunction) = (int(*)(int *,CUfunction_attribute,CUfunction)) dlsym(handle,"PTR_ORIGINAL_cuFuncGetAttribute");
	PTR_ORIGINAL_cuFuncGetAttribute = (void *)dlsym(handle,"PTR_ORIGINAL_cuFuncGetAttribute");
	Bound_cuFuncGetAttribute = std::bind(TMP_PTR_cuFuncGetAttribute,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuFuncSetCacheConfig)(CUfunction,CUfunc_cache) = (int(*)(CUfunction,CUfunc_cache)) dlsym(handle,"PTR_ORIGINAL_cuFuncSetCacheConfig");
	PTR_ORIGINAL_cuFuncSetCacheConfig = (void *)dlsym(handle,"PTR_ORIGINAL_cuFuncSetCacheConfig");
	Bound_cuFuncSetCacheConfig = std::bind(TMP_PTR_cuFuncSetCacheConfig,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuFuncSetSharedMemConfig)(CUfunction,CUsharedconfig) = (int(*)(CUfunction,CUsharedconfig)) dlsym(handle,"PTR_ORIGINAL_cuFuncSetSharedMemConfig");
	PTR_ORIGINAL_cuFuncSetSharedMemConfig = (void *)dlsym(handle,"PTR_ORIGINAL_cuFuncSetSharedMemConfig");
	Bound_cuFuncSetSharedMemConfig = std::bind(TMP_PTR_cuFuncSetSharedMemConfig,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuLaunchKernel)(CUfunction,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,CUstream,void * *,void * *) = (int(*)(CUfunction,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,CUstream,void * *,void * *)) dlsym(handle,"PTR_ORIGINAL_cuLaunchKernel");
	PTR_ORIGINAL_cuLaunchKernel = (void *)dlsym(handle,"PTR_ORIGINAL_cuLaunchKernel");
	Bound_cuLaunchKernel = std::bind(TMP_PTR_cuLaunchKernel,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5,std::placeholders::_6,std::placeholders::_7,std::placeholders::_8,std::placeholders::_9,std::placeholders::_10,std::placeholders::_11);
	int (*TMP_PTR_cuFuncSetBlockShape)(CUfunction,int,int,int) = (int(*)(CUfunction,int,int,int)) dlsym(handle,"PTR_ORIGINAL_cuFuncSetBlockShape");
	PTR_ORIGINAL_cuFuncSetBlockShape = (void *)dlsym(handle,"PTR_ORIGINAL_cuFuncSetBlockShape");
	Bound_cuFuncSetBlockShape = std::bind(TMP_PTR_cuFuncSetBlockShape,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuFuncSetSharedSize)(CUfunction,unsigned int) = (int(*)(CUfunction,unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuFuncSetSharedSize");
	PTR_ORIGINAL_cuFuncSetSharedSize = (void *)dlsym(handle,"PTR_ORIGINAL_cuFuncSetSharedSize");
	Bound_cuFuncSetSharedSize = std::bind(TMP_PTR_cuFuncSetSharedSize,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuParamSetSize)(CUfunction,unsigned int) = (int(*)(CUfunction,unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuParamSetSize");
	PTR_ORIGINAL_cuParamSetSize = (void *)dlsym(handle,"PTR_ORIGINAL_cuParamSetSize");
	Bound_cuParamSetSize = std::bind(TMP_PTR_cuParamSetSize,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuParamSeti)(CUfunction,int,unsigned int) = (int(*)(CUfunction,int,unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuParamSeti");
	PTR_ORIGINAL_cuParamSeti = (void *)dlsym(handle,"PTR_ORIGINAL_cuParamSeti");
	Bound_cuParamSeti = std::bind(TMP_PTR_cuParamSeti,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuParamSetf)(CUfunction,int,float) = (int(*)(CUfunction,int,float)) dlsym(handle,"PTR_ORIGINAL_cuParamSetf");
	PTR_ORIGINAL_cuParamSetf = (void *)dlsym(handle,"PTR_ORIGINAL_cuParamSetf");
	Bound_cuParamSetf = std::bind(TMP_PTR_cuParamSetf,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuParamSetv)(CUfunction,int,void *,unsigned int) = (int(*)(CUfunction,int,void *,unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuParamSetv");
	PTR_ORIGINAL_cuParamSetv = (void *)dlsym(handle,"PTR_ORIGINAL_cuParamSetv");
	Bound_cuParamSetv = std::bind(TMP_PTR_cuParamSetv,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuLaunch)(CUfunction) = (int(*)(CUfunction)) dlsym(handle,"PTR_ORIGINAL_cuLaunch");
	PTR_ORIGINAL_cuLaunch = (void *)dlsym(handle,"PTR_ORIGINAL_cuLaunch");
	Bound_cuLaunch = std::bind(TMP_PTR_cuLaunch,std::placeholders::_1);
	int (*TMP_PTR_cuLaunchGrid)(CUfunction,int,int) = (int(*)(CUfunction,int,int)) dlsym(handle,"PTR_ORIGINAL_cuLaunchGrid");
	PTR_ORIGINAL_cuLaunchGrid = (void *)dlsym(handle,"PTR_ORIGINAL_cuLaunchGrid");
	Bound_cuLaunchGrid = std::bind(TMP_PTR_cuLaunchGrid,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuLaunchGridAsync)(CUfunction,int,int,CUstream) = (int(*)(CUfunction,int,int,CUstream)) dlsym(handle,"PTR_ORIGINAL_cuLaunchGridAsync");
	PTR_ORIGINAL_cuLaunchGridAsync = (void *)dlsym(handle,"PTR_ORIGINAL_cuLaunchGridAsync");
	Bound_cuLaunchGridAsync = std::bind(TMP_PTR_cuLaunchGridAsync,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuParamSetTexRef)(CUfunction,int,CUtexref) = (int(*)(CUfunction,int,CUtexref)) dlsym(handle,"PTR_ORIGINAL_cuParamSetTexRef");
	PTR_ORIGINAL_cuParamSetTexRef = (void *)dlsym(handle,"PTR_ORIGINAL_cuParamSetTexRef");
	Bound_cuParamSetTexRef = std::bind(TMP_PTR_cuParamSetTexRef,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuOccupancyMaxActiveBlocksPerMultiprocessor)(int *,CUfunction,int,size_t) = (int(*)(int *,CUfunction,int,size_t)) dlsym(handle,"PTR_ORIGINAL_cuOccupancyMaxActiveBlocksPerMultiprocessor");
	PTR_ORIGINAL_cuOccupancyMaxActiveBlocksPerMultiprocessor = (void *)dlsym(handle,"PTR_ORIGINAL_cuOccupancyMaxActiveBlocksPerMultiprocessor");
	Bound_cuOccupancyMaxActiveBlocksPerMultiprocessor = std::bind(TMP_PTR_cuOccupancyMaxActiveBlocksPerMultiprocessor,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags)(int *,CUfunction,int,size_t,unsigned int) = (int(*)(int *,CUfunction,int,size_t,unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags");
	PTR_ORIGINAL_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags = (void *)dlsym(handle,"PTR_ORIGINAL_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags");
	Bound_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags = std::bind(TMP_PTR_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
	int (*TMP_PTR_cuOccupancyMaxPotentialBlockSize)(int *,int *,CUfunction,CUoccupancyB2DSize,size_t,int) = (int(*)(int *,int *,CUfunction,CUoccupancyB2DSize,size_t,int)) dlsym(handle,"PTR_ORIGINAL_cuOccupancyMaxPotentialBlockSize");
	PTR_ORIGINAL_cuOccupancyMaxPotentialBlockSize = (void *)dlsym(handle,"PTR_ORIGINAL_cuOccupancyMaxPotentialBlockSize");
	Bound_cuOccupancyMaxPotentialBlockSize = std::bind(TMP_PTR_cuOccupancyMaxPotentialBlockSize,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5,std::placeholders::_6);
	int (*TMP_PTR_cuOccupancyMaxPotentialBlockSizeWithFlags)(int *,int *,CUfunction,CUoccupancyB2DSize,size_t,int,unsigned int) = (int(*)(int *,int *,CUfunction,CUoccupancyB2DSize,size_t,int,unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuOccupancyMaxPotentialBlockSizeWithFlags");
	PTR_ORIGINAL_cuOccupancyMaxPotentialBlockSizeWithFlags = (void *)dlsym(handle,"PTR_ORIGINAL_cuOccupancyMaxPotentialBlockSizeWithFlags");
	Bound_cuOccupancyMaxPotentialBlockSizeWithFlags = std::bind(TMP_PTR_cuOccupancyMaxPotentialBlockSizeWithFlags,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5,std::placeholders::_6,std::placeholders::_7);
	int (*TMP_PTR_cuTexRefSetArray)(CUtexref,CUarray,unsigned int) = (int(*)(CUtexref,CUarray,unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuTexRefSetArray");
	PTR_ORIGINAL_cuTexRefSetArray = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexRefSetArray");
	Bound_cuTexRefSetArray = std::bind(TMP_PTR_cuTexRefSetArray,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuTexRefSetMipmappedArray)(CUtexref,CUmipmappedArray,unsigned int) = (int(*)(CUtexref,CUmipmappedArray,unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuTexRefSetMipmappedArray");
	PTR_ORIGINAL_cuTexRefSetMipmappedArray = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexRefSetMipmappedArray");
	Bound_cuTexRefSetMipmappedArray = std::bind(TMP_PTR_cuTexRefSetMipmappedArray,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuTexRefSetAddress)(size_t *,CUtexref,CUdeviceptr,size_t) = (int(*)(size_t *,CUtexref,CUdeviceptr,size_t)) dlsym(handle,"PTR_ORIGINAL_cuTexRefSetAddress");
	PTR_ORIGINAL_cuTexRefSetAddress = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexRefSetAddress");
	Bound_cuTexRefSetAddress = std::bind(TMP_PTR_cuTexRefSetAddress,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuTexRefSetAddress2D)(CUtexref,const CUDA_ARRAY_DESCRIPTOR *,CUdeviceptr,size_t) = (int(*)(CUtexref,const CUDA_ARRAY_DESCRIPTOR *,CUdeviceptr,size_t)) dlsym(handle,"PTR_ORIGINAL_cuTexRefSetAddress2D");
	PTR_ORIGINAL_cuTexRefSetAddress2D = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexRefSetAddress2D");
	Bound_cuTexRefSetAddress2D = std::bind(TMP_PTR_cuTexRefSetAddress2D,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuTexRefSetFormat)(CUtexref,CUarray_format,int) = (int(*)(CUtexref,CUarray_format,int)) dlsym(handle,"PTR_ORIGINAL_cuTexRefSetFormat");
	PTR_ORIGINAL_cuTexRefSetFormat = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexRefSetFormat");
	Bound_cuTexRefSetFormat = std::bind(TMP_PTR_cuTexRefSetFormat,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuTexRefSetAddressMode)(CUtexref,int,CUaddress_mode) = (int(*)(CUtexref,int,CUaddress_mode)) dlsym(handle,"PTR_ORIGINAL_cuTexRefSetAddressMode");
	PTR_ORIGINAL_cuTexRefSetAddressMode = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexRefSetAddressMode");
	Bound_cuTexRefSetAddressMode = std::bind(TMP_PTR_cuTexRefSetAddressMode,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuTexRefSetFilterMode)(CUtexref,CUfilter_mode) = (int(*)(CUtexref,CUfilter_mode)) dlsym(handle,"PTR_ORIGINAL_cuTexRefSetFilterMode");
	PTR_ORIGINAL_cuTexRefSetFilterMode = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexRefSetFilterMode");
	Bound_cuTexRefSetFilterMode = std::bind(TMP_PTR_cuTexRefSetFilterMode,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuTexRefSetMipmapFilterMode)(CUtexref,CUfilter_mode) = (int(*)(CUtexref,CUfilter_mode)) dlsym(handle,"PTR_ORIGINAL_cuTexRefSetMipmapFilterMode");
	PTR_ORIGINAL_cuTexRefSetMipmapFilterMode = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexRefSetMipmapFilterMode");
	Bound_cuTexRefSetMipmapFilterMode = std::bind(TMP_PTR_cuTexRefSetMipmapFilterMode,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuTexRefSetMipmapLevelBias)(CUtexref,float) = (int(*)(CUtexref,float)) dlsym(handle,"PTR_ORIGINAL_cuTexRefSetMipmapLevelBias");
	PTR_ORIGINAL_cuTexRefSetMipmapLevelBias = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexRefSetMipmapLevelBias");
	Bound_cuTexRefSetMipmapLevelBias = std::bind(TMP_PTR_cuTexRefSetMipmapLevelBias,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuTexRefSetMipmapLevelClamp)(CUtexref,float,float) = (int(*)(CUtexref,float,float)) dlsym(handle,"PTR_ORIGINAL_cuTexRefSetMipmapLevelClamp");
	PTR_ORIGINAL_cuTexRefSetMipmapLevelClamp = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexRefSetMipmapLevelClamp");
	Bound_cuTexRefSetMipmapLevelClamp = std::bind(TMP_PTR_cuTexRefSetMipmapLevelClamp,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuTexRefSetMaxAnisotropy)(CUtexref,unsigned int) = (int(*)(CUtexref,unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuTexRefSetMaxAnisotropy");
	PTR_ORIGINAL_cuTexRefSetMaxAnisotropy = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexRefSetMaxAnisotropy");
	Bound_cuTexRefSetMaxAnisotropy = std::bind(TMP_PTR_cuTexRefSetMaxAnisotropy,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuTexRefSetBorderColor)(CUtexref,float *) = (int(*)(CUtexref,float *)) dlsym(handle,"PTR_ORIGINAL_cuTexRefSetBorderColor");
	PTR_ORIGINAL_cuTexRefSetBorderColor = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexRefSetBorderColor");
	Bound_cuTexRefSetBorderColor = std::bind(TMP_PTR_cuTexRefSetBorderColor,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuTexRefSetFlags)(CUtexref,unsigned int) = (int(*)(CUtexref,unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuTexRefSetFlags");
	PTR_ORIGINAL_cuTexRefSetFlags = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexRefSetFlags");
	Bound_cuTexRefSetFlags = std::bind(TMP_PTR_cuTexRefSetFlags,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuTexRefGetAddress)(CUdeviceptr *,CUtexref) = (int(*)(CUdeviceptr *,CUtexref)) dlsym(handle,"PTR_ORIGINAL_cuTexRefGetAddress");
	PTR_ORIGINAL_cuTexRefGetAddress = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexRefGetAddress");
	Bound_cuTexRefGetAddress = std::bind(TMP_PTR_cuTexRefGetAddress,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuTexRefGetArray)(CUarray *,CUtexref) = (int(*)(CUarray *,CUtexref)) dlsym(handle,"PTR_ORIGINAL_cuTexRefGetArray");
	PTR_ORIGINAL_cuTexRefGetArray = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexRefGetArray");
	Bound_cuTexRefGetArray = std::bind(TMP_PTR_cuTexRefGetArray,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuTexRefGetMipmappedArray)(CUmipmappedArray *,CUtexref) = (int(*)(CUmipmappedArray *,CUtexref)) dlsym(handle,"PTR_ORIGINAL_cuTexRefGetMipmappedArray");
	PTR_ORIGINAL_cuTexRefGetMipmappedArray = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexRefGetMipmappedArray");
	Bound_cuTexRefGetMipmappedArray = std::bind(TMP_PTR_cuTexRefGetMipmappedArray,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuTexRefGetAddressMode)(CUaddress_mode *,CUtexref,int) = (int(*)(CUaddress_mode *,CUtexref,int)) dlsym(handle,"PTR_ORIGINAL_cuTexRefGetAddressMode");
	PTR_ORIGINAL_cuTexRefGetAddressMode = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexRefGetAddressMode");
	Bound_cuTexRefGetAddressMode = std::bind(TMP_PTR_cuTexRefGetAddressMode,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuTexRefGetFilterMode)(CUfilter_mode *,CUtexref) = (int(*)(CUfilter_mode *,CUtexref)) dlsym(handle,"PTR_ORIGINAL_cuTexRefGetFilterMode");
	PTR_ORIGINAL_cuTexRefGetFilterMode = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexRefGetFilterMode");
	Bound_cuTexRefGetFilterMode = std::bind(TMP_PTR_cuTexRefGetFilterMode,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuTexRefGetFormat)(CUarray_format *,int *,CUtexref) = (int(*)(CUarray_format *,int *,CUtexref)) dlsym(handle,"PTR_ORIGINAL_cuTexRefGetFormat");
	PTR_ORIGINAL_cuTexRefGetFormat = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexRefGetFormat");
	Bound_cuTexRefGetFormat = std::bind(TMP_PTR_cuTexRefGetFormat,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuTexRefGetMipmapFilterMode)(CUfilter_mode *,CUtexref) = (int(*)(CUfilter_mode *,CUtexref)) dlsym(handle,"PTR_ORIGINAL_cuTexRefGetMipmapFilterMode");
	PTR_ORIGINAL_cuTexRefGetMipmapFilterMode = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexRefGetMipmapFilterMode");
	Bound_cuTexRefGetMipmapFilterMode = std::bind(TMP_PTR_cuTexRefGetMipmapFilterMode,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuTexRefGetMipmapLevelBias)(float *,CUtexref) = (int(*)(float *,CUtexref)) dlsym(handle,"PTR_ORIGINAL_cuTexRefGetMipmapLevelBias");
	PTR_ORIGINAL_cuTexRefGetMipmapLevelBias = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexRefGetMipmapLevelBias");
	Bound_cuTexRefGetMipmapLevelBias = std::bind(TMP_PTR_cuTexRefGetMipmapLevelBias,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuTexRefGetMipmapLevelClamp)(float *,float *,CUtexref) = (int(*)(float *,float *,CUtexref)) dlsym(handle,"PTR_ORIGINAL_cuTexRefGetMipmapLevelClamp");
	PTR_ORIGINAL_cuTexRefGetMipmapLevelClamp = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexRefGetMipmapLevelClamp");
	Bound_cuTexRefGetMipmapLevelClamp = std::bind(TMP_PTR_cuTexRefGetMipmapLevelClamp,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuTexRefGetMaxAnisotropy)(int *,CUtexref) = (int(*)(int *,CUtexref)) dlsym(handle,"PTR_ORIGINAL_cuTexRefGetMaxAnisotropy");
	PTR_ORIGINAL_cuTexRefGetMaxAnisotropy = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexRefGetMaxAnisotropy");
	Bound_cuTexRefGetMaxAnisotropy = std::bind(TMP_PTR_cuTexRefGetMaxAnisotropy,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuTexRefGetBorderColor)(float *,CUtexref) = (int(*)(float *,CUtexref)) dlsym(handle,"PTR_ORIGINAL_cuTexRefGetBorderColor");
	PTR_ORIGINAL_cuTexRefGetBorderColor = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexRefGetBorderColor");
	Bound_cuTexRefGetBorderColor = std::bind(TMP_PTR_cuTexRefGetBorderColor,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuTexRefGetFlags)(unsigned int *,CUtexref) = (int(*)(unsigned int *,CUtexref)) dlsym(handle,"PTR_ORIGINAL_cuTexRefGetFlags");
	PTR_ORIGINAL_cuTexRefGetFlags = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexRefGetFlags");
	Bound_cuTexRefGetFlags = std::bind(TMP_PTR_cuTexRefGetFlags,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuTexRefCreate)(CUtexref *) = (int(*)(CUtexref *)) dlsym(handle,"PTR_ORIGINAL_cuTexRefCreate");
	PTR_ORIGINAL_cuTexRefCreate = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexRefCreate");
	Bound_cuTexRefCreate = std::bind(TMP_PTR_cuTexRefCreate,std::placeholders::_1);
	int (*TMP_PTR_cuTexRefDestroy)(CUtexref) = (int(*)(CUtexref)) dlsym(handle,"PTR_ORIGINAL_cuTexRefDestroy");
	PTR_ORIGINAL_cuTexRefDestroy = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexRefDestroy");
	Bound_cuTexRefDestroy = std::bind(TMP_PTR_cuTexRefDestroy,std::placeholders::_1);
	int (*TMP_PTR_cuSurfRefSetArray)(CUsurfref,CUarray,unsigned int) = (int(*)(CUsurfref,CUarray,unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuSurfRefSetArray");
	PTR_ORIGINAL_cuSurfRefSetArray = (void *)dlsym(handle,"PTR_ORIGINAL_cuSurfRefSetArray");
	Bound_cuSurfRefSetArray = std::bind(TMP_PTR_cuSurfRefSetArray,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuSurfRefGetArray)(CUarray *,CUsurfref) = (int(*)(CUarray *,CUsurfref)) dlsym(handle,"PTR_ORIGINAL_cuSurfRefGetArray");
	PTR_ORIGINAL_cuSurfRefGetArray = (void *)dlsym(handle,"PTR_ORIGINAL_cuSurfRefGetArray");
	Bound_cuSurfRefGetArray = std::bind(TMP_PTR_cuSurfRefGetArray,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuTexObjectCreate)(CUtexObject *,const CUDA_RESOURCE_DESC *,const CUDA_TEXTURE_DESC *,const CUDA_RESOURCE_VIEW_DESC *) = (int(*)(CUtexObject *,const CUDA_RESOURCE_DESC *,const CUDA_TEXTURE_DESC *,const CUDA_RESOURCE_VIEW_DESC *)) dlsym(handle,"PTR_ORIGINAL_cuTexObjectCreate");
	PTR_ORIGINAL_cuTexObjectCreate = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexObjectCreate");
	Bound_cuTexObjectCreate = std::bind(TMP_PTR_cuTexObjectCreate,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuTexObjectDestroy)(CUtexObject) = (int(*)(CUtexObject)) dlsym(handle,"PTR_ORIGINAL_cuTexObjectDestroy");
	PTR_ORIGINAL_cuTexObjectDestroy = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexObjectDestroy");
	Bound_cuTexObjectDestroy = std::bind(TMP_PTR_cuTexObjectDestroy,std::placeholders::_1);
	int (*TMP_PTR_cuTexObjectGetResourceDesc)(CUDA_RESOURCE_DESC *,CUtexObject) = (int(*)(CUDA_RESOURCE_DESC *,CUtexObject)) dlsym(handle,"PTR_ORIGINAL_cuTexObjectGetResourceDesc");
	PTR_ORIGINAL_cuTexObjectGetResourceDesc = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexObjectGetResourceDesc");
	Bound_cuTexObjectGetResourceDesc = std::bind(TMP_PTR_cuTexObjectGetResourceDesc,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuTexObjectGetTextureDesc)(CUDA_TEXTURE_DESC *,CUtexObject) = (int(*)(CUDA_TEXTURE_DESC *,CUtexObject)) dlsym(handle,"PTR_ORIGINAL_cuTexObjectGetTextureDesc");
	PTR_ORIGINAL_cuTexObjectGetTextureDesc = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexObjectGetTextureDesc");
	Bound_cuTexObjectGetTextureDesc = std::bind(TMP_PTR_cuTexObjectGetTextureDesc,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuTexObjectGetResourceViewDesc)(CUDA_RESOURCE_VIEW_DESC *,CUtexObject) = (int(*)(CUDA_RESOURCE_VIEW_DESC *,CUtexObject)) dlsym(handle,"PTR_ORIGINAL_cuTexObjectGetResourceViewDesc");
	PTR_ORIGINAL_cuTexObjectGetResourceViewDesc = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexObjectGetResourceViewDesc");
	Bound_cuTexObjectGetResourceViewDesc = std::bind(TMP_PTR_cuTexObjectGetResourceViewDesc,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuSurfObjectCreate)(CUsurfObject *,const CUDA_RESOURCE_DESC *) = (int(*)(CUsurfObject *,const CUDA_RESOURCE_DESC *)) dlsym(handle,"PTR_ORIGINAL_cuSurfObjectCreate");
	PTR_ORIGINAL_cuSurfObjectCreate = (void *)dlsym(handle,"PTR_ORIGINAL_cuSurfObjectCreate");
	Bound_cuSurfObjectCreate = std::bind(TMP_PTR_cuSurfObjectCreate,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuSurfObjectDestroy)(CUsurfObject) = (int(*)(CUsurfObject)) dlsym(handle,"PTR_ORIGINAL_cuSurfObjectDestroy");
	PTR_ORIGINAL_cuSurfObjectDestroy = (void *)dlsym(handle,"PTR_ORIGINAL_cuSurfObjectDestroy");
	Bound_cuSurfObjectDestroy = std::bind(TMP_PTR_cuSurfObjectDestroy,std::placeholders::_1);
	int (*TMP_PTR_cuSurfObjectGetResourceDesc)(CUDA_RESOURCE_DESC *,CUsurfObject) = (int(*)(CUDA_RESOURCE_DESC *,CUsurfObject)) dlsym(handle,"PTR_ORIGINAL_cuSurfObjectGetResourceDesc");
	PTR_ORIGINAL_cuSurfObjectGetResourceDesc = (void *)dlsym(handle,"PTR_ORIGINAL_cuSurfObjectGetResourceDesc");
	Bound_cuSurfObjectGetResourceDesc = std::bind(TMP_PTR_cuSurfObjectGetResourceDesc,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuDeviceCanAccessPeer)(int *,CUdevice,CUdevice) = (int(*)(int *,CUdevice,CUdevice)) dlsym(handle,"PTR_ORIGINAL_cuDeviceCanAccessPeer");
	PTR_ORIGINAL_cuDeviceCanAccessPeer = (void *)dlsym(handle,"PTR_ORIGINAL_cuDeviceCanAccessPeer");
	Bound_cuDeviceCanAccessPeer = std::bind(TMP_PTR_cuDeviceCanAccessPeer,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuDeviceGetP2PAttribute)(int *,CUdevice_P2PAttribute,CUdevice,CUdevice) = (int(*)(int *,CUdevice_P2PAttribute,CUdevice,CUdevice)) dlsym(handle,"PTR_ORIGINAL_cuDeviceGetP2PAttribute");
	PTR_ORIGINAL_cuDeviceGetP2PAttribute = (void *)dlsym(handle,"PTR_ORIGINAL_cuDeviceGetP2PAttribute");
	Bound_cuDeviceGetP2PAttribute = std::bind(TMP_PTR_cuDeviceGetP2PAttribute,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuCtxEnablePeerAccess)(CUcontext,unsigned int) = (int(*)(CUcontext,unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuCtxEnablePeerAccess");
	PTR_ORIGINAL_cuCtxEnablePeerAccess = (void *)dlsym(handle,"PTR_ORIGINAL_cuCtxEnablePeerAccess");
	Bound_cuCtxEnablePeerAccess = std::bind(TMP_PTR_cuCtxEnablePeerAccess,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuCtxDisablePeerAccess)(CUcontext) = (int(*)(CUcontext)) dlsym(handle,"PTR_ORIGINAL_cuCtxDisablePeerAccess");
	PTR_ORIGINAL_cuCtxDisablePeerAccess = (void *)dlsym(handle,"PTR_ORIGINAL_cuCtxDisablePeerAccess");
	Bound_cuCtxDisablePeerAccess = std::bind(TMP_PTR_cuCtxDisablePeerAccess,std::placeholders::_1);
	int (*TMP_PTR_cuGraphicsUnregisterResource)(CUgraphicsResource) = (int(*)(CUgraphicsResource)) dlsym(handle,"PTR_ORIGINAL_cuGraphicsUnregisterResource");
	PTR_ORIGINAL_cuGraphicsUnregisterResource = (void *)dlsym(handle,"PTR_ORIGINAL_cuGraphicsUnregisterResource");
	Bound_cuGraphicsUnregisterResource = std::bind(TMP_PTR_cuGraphicsUnregisterResource,std::placeholders::_1);
	int (*TMP_PTR_cuGraphicsSubResourceGetMappedArray)(CUarray *,CUgraphicsResource,unsigned int,unsigned int) = (int(*)(CUarray *,CUgraphicsResource,unsigned int,unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuGraphicsSubResourceGetMappedArray");
	PTR_ORIGINAL_cuGraphicsSubResourceGetMappedArray = (void *)dlsym(handle,"PTR_ORIGINAL_cuGraphicsSubResourceGetMappedArray");
	Bound_cuGraphicsSubResourceGetMappedArray = std::bind(TMP_PTR_cuGraphicsSubResourceGetMappedArray,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuGraphicsResourceGetMappedMipmappedArray)(CUmipmappedArray *,CUgraphicsResource) = (int(*)(CUmipmappedArray *,CUgraphicsResource)) dlsym(handle,"PTR_ORIGINAL_cuGraphicsResourceGetMappedMipmappedArray");
	PTR_ORIGINAL_cuGraphicsResourceGetMappedMipmappedArray = (void *)dlsym(handle,"PTR_ORIGINAL_cuGraphicsResourceGetMappedMipmappedArray");
	Bound_cuGraphicsResourceGetMappedMipmappedArray = std::bind(TMP_PTR_cuGraphicsResourceGetMappedMipmappedArray,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuGraphicsResourceGetMappedPointer)(CUdeviceptr *,size_t *,CUgraphicsResource) = (int(*)(CUdeviceptr *,size_t *,CUgraphicsResource)) dlsym(handle,"PTR_ORIGINAL_cuGraphicsResourceGetMappedPointer");
	PTR_ORIGINAL_cuGraphicsResourceGetMappedPointer = (void *)dlsym(handle,"PTR_ORIGINAL_cuGraphicsResourceGetMappedPointer");
	Bound_cuGraphicsResourceGetMappedPointer = std::bind(TMP_PTR_cuGraphicsResourceGetMappedPointer,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuGraphicsResourceSetMapFlags)(CUgraphicsResource,unsigned int) = (int(*)(CUgraphicsResource,unsigned int)) dlsym(handle,"PTR_ORIGINAL_cuGraphicsResourceSetMapFlags");
	PTR_ORIGINAL_cuGraphicsResourceSetMapFlags = (void *)dlsym(handle,"PTR_ORIGINAL_cuGraphicsResourceSetMapFlags");
	Bound_cuGraphicsResourceSetMapFlags = std::bind(TMP_PTR_cuGraphicsResourceSetMapFlags,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuGraphicsMapResources)(unsigned int,CUgraphicsResource *,CUstream) = (int(*)(unsigned int,CUgraphicsResource *,CUstream)) dlsym(handle,"PTR_ORIGINAL_cuGraphicsMapResources");
	PTR_ORIGINAL_cuGraphicsMapResources = (void *)dlsym(handle,"PTR_ORIGINAL_cuGraphicsMapResources");
	Bound_cuGraphicsMapResources = std::bind(TMP_PTR_cuGraphicsMapResources,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuGraphicsUnmapResources)(unsigned int,CUgraphicsResource *,CUstream) = (int(*)(unsigned int,CUgraphicsResource *,CUstream)) dlsym(handle,"PTR_ORIGINAL_cuGraphicsUnmapResources");
	PTR_ORIGINAL_cuGraphicsUnmapResources = (void *)dlsym(handle,"PTR_ORIGINAL_cuGraphicsUnmapResources");
	Bound_cuGraphicsUnmapResources = std::bind(TMP_PTR_cuGraphicsUnmapResources,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuGetExportTable)(const void * *,const CUuuid *) = (int(*)(const void * *,const CUuuid *)) dlsym(handle,"PTR_ORIGINAL_cuGetExportTable");
	PTR_ORIGINAL_cuGetExportTable = (void *)dlsym(handle,"PTR_ORIGINAL_cuGetExportTable");
	Bound_cuGetExportTable = std::bind(TMP_PTR_cuGetExportTable,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuTexRefSetAddress2D_v2)(CUtexref,const CUDA_ARRAY_DESCRIPTOR *,CUdeviceptr,size_t) = (int(*)(CUtexref,const CUDA_ARRAY_DESCRIPTOR *,CUdeviceptr,size_t)) dlsym(handle,"PTR_ORIGINAL_cuTexRefSetAddress2D_v2");
	PTR_ORIGINAL_cuTexRefSetAddress2D_v2 = (void *)dlsym(handle,"PTR_ORIGINAL_cuTexRefSetAddress2D_v2");
	Bound_cuTexRefSetAddress2D_v2 = std::bind(TMP_PTR_cuTexRefSetAddress2D_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuMemcpyHtoD_v2)(CUdeviceptr,const void *,size_t) = (int(*)(CUdeviceptr,const void *,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemcpyHtoD_v2");
	PTR_ORIGINAL_cuMemcpyHtoD_v2 = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpyHtoD_v2");
	Bound_cuMemcpyHtoD_v2 = std::bind(TMP_PTR_cuMemcpyHtoD_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuMemcpyDtoH_v2)(void *,CUdeviceptr,size_t) = (int(*)(void *,CUdeviceptr,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemcpyDtoH_v2");
	PTR_ORIGINAL_cuMemcpyDtoH_v2 = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpyDtoH_v2");
	Bound_cuMemcpyDtoH_v2 = std::bind(TMP_PTR_cuMemcpyDtoH_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuMemcpyDtoD_v2)(CUdeviceptr,CUdeviceptr,size_t) = (int(*)(CUdeviceptr,CUdeviceptr,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemcpyDtoD_v2");
	PTR_ORIGINAL_cuMemcpyDtoD_v2 = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpyDtoD_v2");
	Bound_cuMemcpyDtoD_v2 = std::bind(TMP_PTR_cuMemcpyDtoD_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuMemcpyDtoA_v2)(CUarray,size_t,CUdeviceptr,size_t) = (int(*)(CUarray,size_t,CUdeviceptr,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemcpyDtoA_v2");
	PTR_ORIGINAL_cuMemcpyDtoA_v2 = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpyDtoA_v2");
	Bound_cuMemcpyDtoA_v2 = std::bind(TMP_PTR_cuMemcpyDtoA_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuMemcpyAtoD_v2)(CUdeviceptr,CUarray,size_t,size_t) = (int(*)(CUdeviceptr,CUarray,size_t,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemcpyAtoD_v2");
	PTR_ORIGINAL_cuMemcpyAtoD_v2 = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpyAtoD_v2");
	Bound_cuMemcpyAtoD_v2 = std::bind(TMP_PTR_cuMemcpyAtoD_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuMemcpyHtoA_v2)(CUarray,size_t,const void *,size_t) = (int(*)(CUarray,size_t,const void *,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemcpyHtoA_v2");
	PTR_ORIGINAL_cuMemcpyHtoA_v2 = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpyHtoA_v2");
	Bound_cuMemcpyHtoA_v2 = std::bind(TMP_PTR_cuMemcpyHtoA_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuMemcpyAtoH_v2)(void *,CUarray,size_t,size_t) = (int(*)(void *,CUarray,size_t,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemcpyAtoH_v2");
	PTR_ORIGINAL_cuMemcpyAtoH_v2 = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpyAtoH_v2");
	Bound_cuMemcpyAtoH_v2 = std::bind(TMP_PTR_cuMemcpyAtoH_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuMemcpyAtoA_v2)(CUarray,size_t,CUarray,size_t,size_t) = (int(*)(CUarray,size_t,CUarray,size_t,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemcpyAtoA_v2");
	PTR_ORIGINAL_cuMemcpyAtoA_v2 = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpyAtoA_v2");
	Bound_cuMemcpyAtoA_v2 = std::bind(TMP_PTR_cuMemcpyAtoA_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
	int (*TMP_PTR_cuMemcpyHtoAAsync_v2)(CUarray,size_t,const void *,size_t,CUstream) = (int(*)(CUarray,size_t,const void *,size_t,CUstream)) dlsym(handle,"PTR_ORIGINAL_cuMemcpyHtoAAsync_v2");
	PTR_ORIGINAL_cuMemcpyHtoAAsync_v2 = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpyHtoAAsync_v2");
	Bound_cuMemcpyHtoAAsync_v2 = std::bind(TMP_PTR_cuMemcpyHtoAAsync_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
	int (*TMP_PTR_cuMemcpyAtoHAsync_v2)(void *,CUarray,size_t,size_t,CUstream) = (int(*)(void *,CUarray,size_t,size_t,CUstream)) dlsym(handle,"PTR_ORIGINAL_cuMemcpyAtoHAsync_v2");
	PTR_ORIGINAL_cuMemcpyAtoHAsync_v2 = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpyAtoHAsync_v2");
	Bound_cuMemcpyAtoHAsync_v2 = std::bind(TMP_PTR_cuMemcpyAtoHAsync_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
	int (*TMP_PTR_cuMemcpy2D_v2)(const CUDA_MEMCPY2D *) = (int(*)(const CUDA_MEMCPY2D *)) dlsym(handle,"PTR_ORIGINAL_cuMemcpy2D_v2");
	PTR_ORIGINAL_cuMemcpy2D_v2 = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpy2D_v2");
	Bound_cuMemcpy2D_v2 = std::bind(TMP_PTR_cuMemcpy2D_v2,std::placeholders::_1);
	int (*TMP_PTR_cuMemcpy2DUnaligned_v2)(const CUDA_MEMCPY2D *) = (int(*)(const CUDA_MEMCPY2D *)) dlsym(handle,"PTR_ORIGINAL_cuMemcpy2DUnaligned_v2");
	PTR_ORIGINAL_cuMemcpy2DUnaligned_v2 = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpy2DUnaligned_v2");
	Bound_cuMemcpy2DUnaligned_v2 = std::bind(TMP_PTR_cuMemcpy2DUnaligned_v2,std::placeholders::_1);
	int (*TMP_PTR_cuMemcpy3D_v2)(const CUDA_MEMCPY3D *) = (int(*)(const CUDA_MEMCPY3D *)) dlsym(handle,"PTR_ORIGINAL_cuMemcpy3D_v2");
	PTR_ORIGINAL_cuMemcpy3D_v2 = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpy3D_v2");
	Bound_cuMemcpy3D_v2 = std::bind(TMP_PTR_cuMemcpy3D_v2,std::placeholders::_1);
	int (*TMP_PTR_cuMemcpyHtoDAsync_v2)(CUdeviceptr,const void *,size_t,CUstream) = (int(*)(CUdeviceptr,const void *,size_t,CUstream)) dlsym(handle,"PTR_ORIGINAL_cuMemcpyHtoDAsync_v2");
	PTR_ORIGINAL_cuMemcpyHtoDAsync_v2 = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpyHtoDAsync_v2");
	Bound_cuMemcpyHtoDAsync_v2 = std::bind(TMP_PTR_cuMemcpyHtoDAsync_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuMemcpyDtoHAsync_v2)(void *,CUdeviceptr,size_t,CUstream) = (int(*)(void *,CUdeviceptr,size_t,CUstream)) dlsym(handle,"PTR_ORIGINAL_cuMemcpyDtoHAsync_v2");
	PTR_ORIGINAL_cuMemcpyDtoHAsync_v2 = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpyDtoHAsync_v2");
	Bound_cuMemcpyDtoHAsync_v2 = std::bind(TMP_PTR_cuMemcpyDtoHAsync_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuMemcpyDtoDAsync_v2)(CUdeviceptr,CUdeviceptr,size_t,CUstream) = (int(*)(CUdeviceptr,CUdeviceptr,size_t,CUstream)) dlsym(handle,"PTR_ORIGINAL_cuMemcpyDtoDAsync_v2");
	PTR_ORIGINAL_cuMemcpyDtoDAsync_v2 = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpyDtoDAsync_v2");
	Bound_cuMemcpyDtoDAsync_v2 = std::bind(TMP_PTR_cuMemcpyDtoDAsync_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	int (*TMP_PTR_cuMemcpy2DAsync_v2)(const CUDA_MEMCPY2D *,CUstream) = (int(*)(const CUDA_MEMCPY2D *,CUstream)) dlsym(handle,"PTR_ORIGINAL_cuMemcpy2DAsync_v2");
	PTR_ORIGINAL_cuMemcpy2DAsync_v2 = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpy2DAsync_v2");
	Bound_cuMemcpy2DAsync_v2 = std::bind(TMP_PTR_cuMemcpy2DAsync_v2,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuMemcpy3DAsync_v2)(const CUDA_MEMCPY3D *,CUstream) = (int(*)(const CUDA_MEMCPY3D *,CUstream)) dlsym(handle,"PTR_ORIGINAL_cuMemcpy3DAsync_v2");
	PTR_ORIGINAL_cuMemcpy3DAsync_v2 = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemcpy3DAsync_v2");
	Bound_cuMemcpy3DAsync_v2 = std::bind(TMP_PTR_cuMemcpy3DAsync_v2,std::placeholders::_1,std::placeholders::_2);
	int (*TMP_PTR_cuMemsetD8_v2)(CUdeviceptr,unsigned char,size_t) = (int(*)(CUdeviceptr,unsigned char,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemsetD8_v2");
	PTR_ORIGINAL_cuMemsetD8_v2 = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemsetD8_v2");
	Bound_cuMemsetD8_v2 = std::bind(TMP_PTR_cuMemsetD8_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuMemsetD16_v2)(CUdeviceptr,unsigned short,size_t) = (int(*)(CUdeviceptr,unsigned short,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemsetD16_v2");
	PTR_ORIGINAL_cuMemsetD16_v2 = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemsetD16_v2");
	Bound_cuMemsetD16_v2 = std::bind(TMP_PTR_cuMemsetD16_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuMemsetD32_v2)(CUdeviceptr,unsigned int,size_t) = (int(*)(CUdeviceptr,unsigned int,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemsetD32_v2");
	PTR_ORIGINAL_cuMemsetD32_v2 = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemsetD32_v2");
	Bound_cuMemsetD32_v2 = std::bind(TMP_PTR_cuMemsetD32_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	int (*TMP_PTR_cuMemsetD2D8_v2)(CUdeviceptr,size_t,unsigned char,size_t,size_t) = (int(*)(CUdeviceptr,size_t,unsigned char,size_t,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemsetD2D8_v2");
	PTR_ORIGINAL_cuMemsetD2D8_v2 = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemsetD2D8_v2");
	Bound_cuMemsetD2D8_v2 = std::bind(TMP_PTR_cuMemsetD2D8_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
	int (*TMP_PTR_cuMemsetD2D16_v2)(CUdeviceptr,size_t,unsigned short,size_t,size_t) = (int(*)(CUdeviceptr,size_t,unsigned short,size_t,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemsetD2D16_v2");
	PTR_ORIGINAL_cuMemsetD2D16_v2 = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemsetD2D16_v2");
	Bound_cuMemsetD2D16_v2 = std::bind(TMP_PTR_cuMemsetD2D16_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
	int (*TMP_PTR_cuMemsetD2D32_v2)(CUdeviceptr,size_t,unsigned int,size_t,size_t) = (int(*)(CUdeviceptr,size_t,unsigned int,size_t,size_t)) dlsym(handle,"PTR_ORIGINAL_cuMemsetD2D32_v2");
	PTR_ORIGINAL_cuMemsetD2D32_v2 = (void *)dlsym(handle,"PTR_ORIGINAL_cuMemsetD2D32_v2");
	Bound_cuMemsetD2D32_v2 = std::bind(TMP_PTR_cuMemsetD2D32_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);

}
