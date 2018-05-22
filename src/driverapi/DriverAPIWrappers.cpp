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
extern int ORIGINAL_cuGetErrorString( CUresult error, const char * * pStr ) ;

// This is the call that will take the place of the original
int INTER_cuGetErrorString( CUresult error, const char * * pStr ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&error,(void **)&pStr };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuGetErrorString, (void*) &ORIGINAL_cuGetErrorString, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuGetErrorName
extern int ORIGINAL_cuGetErrorName( CUresult error, const char * * pStr ) ;

// This is the call that will take the place of the original
int INTER_cuGetErrorName( CUresult error, const char * * pStr ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&error,(void **)&pStr };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuGetErrorName, (void*) &ORIGINAL_cuGetErrorName, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuInit
extern int ORIGINAL_cuInit( unsigned int Flags ); //{ fprintf(stderr, "%s\n", "WE SHOULD NEVER BE HERE WHY?????";

//void * ORIGINAL_SOMETHING = NULL;
// This is the call that will take the place of the original
int INTER_cuInit( unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY

	// fprintf(stderr, "Calling CUInit\n");
	// ORIGINAL_cuInit(Flags);
	// fprintf(stderr, "Done CUInit\n");
	std::vector<void **> params = { (void **)&Flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuInit, (void*) &ORIGINAL_cuInit, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDriverGetVersion
extern int ORIGINAL_cuDriverGetVersion( int * driverVersion ) ;

// This is the call that will take the place of the original
int INTER_cuDriverGetVersion( int * driverVersion ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&driverVersion };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDriverGetVersion, (void*) &ORIGINAL_cuDriverGetVersion, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDeviceGet
extern int ORIGINAL_cuDeviceGet( CUdevice * device, int ordinal ) ;

// This is the call that will take the place of the original
int INTER_cuDeviceGet( CUdevice * device, int ordinal ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&device,(void **)&ordinal };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDeviceGet, (void*) &ORIGINAL_cuDeviceGet, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDeviceGetCount
extern int ORIGINAL_cuDeviceGetCount( int * count ) ;

// This is the call that will take the place of the original
int INTER_cuDeviceGetCount( int * count ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&count };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDeviceGetCount, (void*) &ORIGINAL_cuDeviceGetCount, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDeviceGetName
extern int ORIGINAL_cuDeviceGetName( char * name, int len, CUdevice dev ) ;

// This is the call that will take the place of the original
int INTER_cuDeviceGetName( char * name, int len, CUdevice dev ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&name,(void **)&len,(void **)&dev };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDeviceGetName, (void*) &ORIGINAL_cuDeviceGetName, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDeviceTotalMem
extern int ORIGINAL_cuDeviceTotalMem( size_t * bytes, CUdevice dev ) ;

// This is the call that will take the place of the original
int INTER_cuDeviceTotalMem( size_t * bytes, CUdevice dev ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&bytes,(void **)&dev };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDeviceTotalMem, (void*) &ORIGINAL_cuDeviceTotalMem, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDeviceGetAttribute
extern int ORIGINAL_cuDeviceGetAttribute( int * pi, CUdevice_attribute attrib, CUdevice dev ) ;

// This is the call that will take the place of the original
int INTER_cuDeviceGetAttribute( int * pi, CUdevice_attribute attrib, CUdevice dev ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pi,(void **)&attrib,(void **)&dev };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDeviceGetAttribute, (void*) &ORIGINAL_cuDeviceGetAttribute, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDeviceGetProperties
extern int ORIGINAL_cuDeviceGetProperties( CUdevprop * prop, CUdevice dev ) ;

// This is the call that will take the place of the original
int INTER_cuDeviceGetProperties( CUdevprop * prop, CUdevice dev ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&prop,(void **)&dev };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDeviceGetProperties, (void*) &ORIGINAL_cuDeviceGetProperties, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDeviceComputeCapability
extern int ORIGINAL_cuDeviceComputeCapability( int * major, int * minor, CUdevice dev ) ;

// This is the call that will take the place of the original
int INTER_cuDeviceComputeCapability( int * major, int * minor, CUdevice dev ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&major,(void **)&minor,(void **)&dev };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDeviceComputeCapability, (void*) &ORIGINAL_cuDeviceComputeCapability, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDevicePrimaryCtxRetain
extern int ORIGINAL_cuDevicePrimaryCtxRetain( CUcontext * pctx, CUdevice dev ) ;

// This is the call that will take the place of the original
int INTER_cuDevicePrimaryCtxRetain( CUcontext * pctx, CUdevice dev ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pctx,(void **)&dev };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDevicePrimaryCtxRetain, (void*) &ORIGINAL_cuDevicePrimaryCtxRetain, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDevicePrimaryCtxRelease
extern int ORIGINAL_cuDevicePrimaryCtxRelease( CUdevice dev ) ;

// This is the call that will take the place of the original
int INTER_cuDevicePrimaryCtxRelease( CUdevice dev ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dev };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDevicePrimaryCtxRelease, (void*) &ORIGINAL_cuDevicePrimaryCtxRelease, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDevicePrimaryCtxSetFlags
extern int ORIGINAL_cuDevicePrimaryCtxSetFlags( CUdevice dev, unsigned int flags ) ;

// This is the call that will take the place of the original
int INTER_cuDevicePrimaryCtxSetFlags( CUdevice dev, unsigned int flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dev,(void **)&flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDevicePrimaryCtxSetFlags, (void*) &ORIGINAL_cuDevicePrimaryCtxSetFlags, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDevicePrimaryCtxGetState
extern int ORIGINAL_cuDevicePrimaryCtxGetState( CUdevice dev, unsigned int * flags, int * active ) ;

// This is the call that will take the place of the original
int INTER_cuDevicePrimaryCtxGetState( CUdevice dev, unsigned int * flags, int * active ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dev,(void **)&flags,(void **)&active };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDevicePrimaryCtxGetState, (void*) &ORIGINAL_cuDevicePrimaryCtxGetState, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDevicePrimaryCtxReset
extern int ORIGINAL_cuDevicePrimaryCtxReset( CUdevice dev ) ;

// This is the call that will take the place of the original
int INTER_cuDevicePrimaryCtxReset( CUdevice dev ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dev };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDevicePrimaryCtxReset, (void*) &ORIGINAL_cuDevicePrimaryCtxReset, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxCreate
extern int ORIGINAL_cuCtxCreate( CUcontext * pctx, unsigned int flags, CUdevice dev ) ;

// This is the call that will take the place of the original
int INTER_cuCtxCreate( CUcontext * pctx, unsigned int flags, CUdevice dev ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pctx,(void **)&flags,(void **)&dev };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxCreate, (void*) &ORIGINAL_cuCtxCreate, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxDestroy
extern int ORIGINAL_cuCtxDestroy( CUcontext ctx ) ;

// This is the call that will take the place of the original
int INTER_cuCtxDestroy( CUcontext ctx ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&ctx };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxDestroy, (void*) &ORIGINAL_cuCtxDestroy, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxPushCurrent
extern int ORIGINAL_cuCtxPushCurrent( CUcontext ctx ) ;

// This is the call that will take the place of the original
int INTER_cuCtxPushCurrent( CUcontext ctx ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&ctx };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxPushCurrent, (void*) &ORIGINAL_cuCtxPushCurrent, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxPopCurrent
extern int ORIGINAL_cuCtxPopCurrent( CUcontext * pctx ) ;

// This is the call that will take the place of the original
int INTER_cuCtxPopCurrent( CUcontext * pctx ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pctx };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxPopCurrent, (void*) &ORIGINAL_cuCtxPopCurrent, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxSetCurrent
extern int ORIGINAL_cuCtxSetCurrent( CUcontext ctx ) ;

// This is the call that will take the place of the original
int INTER_cuCtxSetCurrent( CUcontext ctx ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&ctx };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxSetCurrent, (void*) &ORIGINAL_cuCtxSetCurrent, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxGetCurrent
extern int ORIGINAL_cuCtxGetCurrent( CUcontext * pctx ) ;

// This is the call that will take the place of the original
int INTER_cuCtxGetCurrent( CUcontext * pctx ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pctx };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxGetCurrent, (void*) &ORIGINAL_cuCtxGetCurrent, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxGetDevice
extern int ORIGINAL_cuCtxGetDevice( CUdevice * device ) ;

// This is the call that will take the place of the original
int INTER_cuCtxGetDevice( CUdevice * device ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&device };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxGetDevice, (void*) &ORIGINAL_cuCtxGetDevice, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxGetFlags
extern int ORIGINAL_cuCtxGetFlags( unsigned int * flags ) ;

// This is the call that will take the place of the original
int INTER_cuCtxGetFlags( unsigned int * flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxGetFlags, (void*) &ORIGINAL_cuCtxGetFlags, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxSynchronize
extern int ORIGINAL_cuCtxSynchronize( void  ) ;

// This is the call that will take the place of the original
int INTER_cuCtxSynchronize( void  ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params;
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxSynchronize, (void*) &ORIGINAL_cuCtxSynchronize, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxSetLimit
extern int ORIGINAL_cuCtxSetLimit( CUlimit limit, size_t value ) ;

// This is the call that will take the place of the original
int INTER_cuCtxSetLimit( CUlimit limit, size_t value ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&limit,(void **)&value };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxSetLimit, (void*) &ORIGINAL_cuCtxSetLimit, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxGetLimit
extern int ORIGINAL_cuCtxGetLimit( size_t * pvalue, CUlimit limit ) ;

// This is the call that will take the place of the original
int INTER_cuCtxGetLimit( size_t * pvalue, CUlimit limit ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pvalue,(void **)&limit };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxGetLimit, (void*) &ORIGINAL_cuCtxGetLimit, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxGetCacheConfig
extern int ORIGINAL_cuCtxGetCacheConfig( CUfunc_cache * pconfig ) ;

// This is the call that will take the place of the original
int INTER_cuCtxGetCacheConfig( CUfunc_cache * pconfig ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pconfig };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxGetCacheConfig, (void*) &ORIGINAL_cuCtxGetCacheConfig, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxSetCacheConfig
extern int ORIGINAL_cuCtxSetCacheConfig( CUfunc_cache config ) ;

// This is the call that will take the place of the original
int INTER_cuCtxSetCacheConfig( CUfunc_cache config ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&config };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxSetCacheConfig, (void*) &ORIGINAL_cuCtxSetCacheConfig, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxGetSharedMemConfig
extern int ORIGINAL_cuCtxGetSharedMemConfig( CUsharedconfig * pConfig ) ;

// This is the call that will take the place of the original
int INTER_cuCtxGetSharedMemConfig( CUsharedconfig * pConfig ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pConfig };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxGetSharedMemConfig, (void*) &ORIGINAL_cuCtxGetSharedMemConfig, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxSetSharedMemConfig
extern int ORIGINAL_cuCtxSetSharedMemConfig( CUsharedconfig config ) ;

// This is the call that will take the place of the original
int INTER_cuCtxSetSharedMemConfig( CUsharedconfig config ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&config };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxSetSharedMemConfig, (void*) &ORIGINAL_cuCtxSetSharedMemConfig, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxGetApiVersion
extern int ORIGINAL_cuCtxGetApiVersion( CUcontext ctx, unsigned int * version ) ;

// This is the call that will take the place of the original
int INTER_cuCtxGetApiVersion( CUcontext ctx, unsigned int * version ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&ctx,(void **)&version };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxGetApiVersion, (void*) &ORIGINAL_cuCtxGetApiVersion, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxGetStreamPriorityRange
extern int ORIGINAL_cuCtxGetStreamPriorityRange( int * leastPriority, int * greatestPriority ) ;

// This is the call that will take the place of the original
int INTER_cuCtxGetStreamPriorityRange( int * leastPriority, int * greatestPriority ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&leastPriority,(void **)&greatestPriority };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxGetStreamPriorityRange, (void*) &ORIGINAL_cuCtxGetStreamPriorityRange, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxAttach
extern int ORIGINAL_cuCtxAttach( CUcontext * pctx, unsigned int flags ) ;

// This is the call that will take the place of the original
int INTER_cuCtxAttach( CUcontext * pctx, unsigned int flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pctx,(void **)&flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxAttach, (void*) &ORIGINAL_cuCtxAttach, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxDetach
extern int ORIGINAL_cuCtxDetach( CUcontext ctx ) ;

// This is the call that will take the place of the original
int INTER_cuCtxDetach( CUcontext ctx ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&ctx };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxDetach, (void*) &ORIGINAL_cuCtxDetach, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuModuleLoad
extern int ORIGINAL_cuModuleLoad( CUmodule * module, const char * fname ) ;

// This is the call that will take the place of the original
int INTER_cuModuleLoad( CUmodule * module, const char * fname ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&module,(void **)&fname };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuModuleLoad, (void*) &ORIGINAL_cuModuleLoad, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuModuleLoadData
extern int ORIGINAL_cuModuleLoadData( CUmodule * module, const void * image ) ;

// This is the call that will take the place of the original
int INTER_cuModuleLoadData( CUmodule * module, const void * image ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&module,(void **)&image };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuModuleLoadData, (void*) &ORIGINAL_cuModuleLoadData, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuModuleLoadDataEx
extern int ORIGINAL_cuModuleLoadDataEx( CUmodule * module, const void * image, unsigned int numOptions, CUjit_option * options, void * * optionValues ) ;

// This is the call that will take the place of the original
int INTER_cuModuleLoadDataEx( CUmodule * module, const void * image, unsigned int numOptions, CUjit_option * options, void * * optionValues ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&module,(void **)&image,(void **)&numOptions,(void **)&options,(void **)&optionValues };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuModuleLoadDataEx, (void*) &ORIGINAL_cuModuleLoadDataEx, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuModuleLoadFatBinary
extern int ORIGINAL_cuModuleLoadFatBinary( CUmodule * module, const void * fatCubin ) ;

// This is the call that will take the place of the original
int INTER_cuModuleLoadFatBinary( CUmodule * module, const void * fatCubin ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&module,(void **)&fatCubin };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuModuleLoadFatBinary, (void*) &ORIGINAL_cuModuleLoadFatBinary, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuModuleUnload
extern int ORIGINAL_cuModuleUnload( CUmodule hmod ) ;

// This is the call that will take the place of the original
int INTER_cuModuleUnload( CUmodule hmod ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hmod };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuModuleUnload, (void*) &ORIGINAL_cuModuleUnload, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuModuleGetFunction
extern int ORIGINAL_cuModuleGetFunction( CUfunction * hfunc, CUmodule hmod, const char * name ) ;

// This is the call that will take the place of the original
int INTER_cuModuleGetFunction( CUfunction * hfunc, CUmodule hmod, const char * name ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hfunc,(void **)&hmod,(void **)&name };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuModuleGetFunction, (void*) &ORIGINAL_cuModuleGetFunction, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuModuleGetGlobal
extern int ORIGINAL_cuModuleGetGlobal( CUdeviceptr * dptr, size_t * bytes, CUmodule hmod, const char * name ) ;

// This is the call that will take the place of the original
int INTER_cuModuleGetGlobal( CUdeviceptr * dptr, size_t * bytes, CUmodule hmod, const char * name ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dptr,(void **)&bytes,(void **)&hmod,(void **)&name };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuModuleGetGlobal, (void*) &ORIGINAL_cuModuleGetGlobal, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuModuleGetTexRef
extern int ORIGINAL_cuModuleGetTexRef( CUtexref * pTexRef, CUmodule hmod, const char * name ) ;

// This is the call that will take the place of the original
int INTER_cuModuleGetTexRef( CUtexref * pTexRef, CUmodule hmod, const char * name ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pTexRef,(void **)&hmod,(void **)&name };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuModuleGetTexRef, (void*) &ORIGINAL_cuModuleGetTexRef, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuModuleGetSurfRef
extern int ORIGINAL_cuModuleGetSurfRef( CUsurfref * pSurfRef, CUmodule hmod, const char * name ) ;

// This is the call that will take the place of the original
int INTER_cuModuleGetSurfRef( CUsurfref * pSurfRef, CUmodule hmod, const char * name ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pSurfRef,(void **)&hmod,(void **)&name };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuModuleGetSurfRef, (void*) &ORIGINAL_cuModuleGetSurfRef, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuLinkCreate
extern int ORIGINAL_cuLinkCreate( unsigned int numOptions, CUjit_option * options, void * * optionValues, CUlinkState * stateOut ) ;

// This is the call that will take the place of the original
int INTER_cuLinkCreate( unsigned int numOptions, CUjit_option * options, void * * optionValues, CUlinkState * stateOut ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&numOptions,(void **)&options,(void **)&optionValues,(void **)&stateOut };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuLinkCreate, (void*) &ORIGINAL_cuLinkCreate, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuLinkAddData
extern int ORIGINAL_cuLinkAddData( CUlinkState state, CUjitInputType type, void * data, size_t size, const char * name, unsigned int numOptions, CUjit_option * options, void * * optionValues ) ;

// This is the call that will take the place of the original
int INTER_cuLinkAddData( CUlinkState state, CUjitInputType type, void * data, size_t size, const char * name, unsigned int numOptions, CUjit_option * options, void * * optionValues ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&state,(void **)&type,(void **)&data,(void **)&size,(void **)&name,(void **)&numOptions,(void **)&options,(void **)&optionValues };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuLinkAddData, (void*) &ORIGINAL_cuLinkAddData, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuLinkAddFile
extern int ORIGINAL_cuLinkAddFile( CUlinkState state, CUjitInputType type, const char * path, unsigned int numOptions, CUjit_option * options, void * * optionValues ) ;

// This is the call that will take the place of the original
int INTER_cuLinkAddFile( CUlinkState state, CUjitInputType type, const char * path, unsigned int numOptions, CUjit_option * options, void * * optionValues ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&state,(void **)&type,(void **)&path,(void **)&numOptions,(void **)&options,(void **)&optionValues };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuLinkAddFile, (void*) &ORIGINAL_cuLinkAddFile, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuLinkComplete
extern int ORIGINAL_cuLinkComplete( CUlinkState state, void * * cubinOut, size_t * sizeOut ) ;

// This is the call that will take the place of the original
int INTER_cuLinkComplete( CUlinkState state, void * * cubinOut, size_t * sizeOut ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&state,(void **)&cubinOut,(void **)&sizeOut };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuLinkComplete, (void*) &ORIGINAL_cuLinkComplete, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuLinkDestroy
extern int ORIGINAL_cuLinkDestroy( CUlinkState state ) ;

// This is the call that will take the place of the original
int INTER_cuLinkDestroy( CUlinkState state ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&state };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuLinkDestroy, (void*) &ORIGINAL_cuLinkDestroy, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemGetInfo
extern int ORIGINAL_cuMemGetInfo( size_t * free, size_t * total ) ;

// This is the call that will take the place of the original
int INTER_cuMemGetInfo( size_t * free, size_t * total ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&free,(void **)&total };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemGetInfo, (void*) &ORIGINAL_cuMemGetInfo, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemAlloc
extern int ORIGINAL_cuMemAlloc( CUdeviceptr * dptr, size_t bytesize ) ;

// This is the call that will take the place of the original
int INTER_cuMemAlloc( CUdeviceptr * dptr, size_t bytesize ) {
	// Build the instriment factory
	BUILD_FACTORY
	
	std::vector<void **> params = { (void **)&dptr,(void **)&bytesize };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemAlloc, (void*) &ORIGINAL_cuMemAlloc, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemAllocPitch
extern int ORIGINAL_cuMemAllocPitch( CUdeviceptr * dptr, size_t * pPitch, size_t WidthInBytes, size_t Height, unsigned int ElementSizeBytes ) ;

// This is the call that will take the place of the original
int INTER_cuMemAllocPitch( CUdeviceptr * dptr, size_t * pPitch, size_t WidthInBytes, size_t Height, unsigned int ElementSizeBytes ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dptr,(void **)&pPitch,(void **)&WidthInBytes,(void **)&Height,(void **)&ElementSizeBytes };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemAllocPitch, (void*) &ORIGINAL_cuMemAllocPitch, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemFree
extern int ORIGINAL_cuMemFree( CUdeviceptr dptr ) ;

// This is the call that will take the place of the original
int INTER_cuMemFree( CUdeviceptr dptr ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dptr };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemFree, (void*) &ORIGINAL_cuMemFree, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemGetAddressRange
extern int ORIGINAL_cuMemGetAddressRange( CUdeviceptr * pbase, size_t * psize, CUdeviceptr dptr ) ;

// This is the call that will take the place of the original
int INTER_cuMemGetAddressRange( CUdeviceptr * pbase, size_t * psize, CUdeviceptr dptr ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pbase,(void **)&psize,(void **)&dptr };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemGetAddressRange, (void*) &ORIGINAL_cuMemGetAddressRange, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemAllocHost
extern int ORIGINAL_cuMemAllocHost( void * * pp, size_t bytesize ) ;

// This is the call that will take the place of the original
int INTER_cuMemAllocHost( void * * pp, size_t bytesize ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pp,(void **)&bytesize };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemAllocHost, (void*) &ORIGINAL_cuMemAllocHost, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemFreeHost
extern int ORIGINAL_cuMemFreeHost( void * p ) ;

// This is the call that will take the place of the original
int INTER_cuMemFreeHost( void * p ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&p };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemFreeHost, (void*) &ORIGINAL_cuMemFreeHost, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemHostAlloc
extern int ORIGINAL_cuMemHostAlloc( void * * pp, size_t bytesize, unsigned int Flags ) ;

// This is the call that will take the place of the original
int INTER_cuMemHostAlloc( void * * pp, size_t bytesize, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pp,(void **)&bytesize,(void **)&Flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemHostAlloc, (void*) &ORIGINAL_cuMemHostAlloc, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemHostGetDevicePointer
extern int ORIGINAL_cuMemHostGetDevicePointer( CUdeviceptr * pdptr, void * p, unsigned int Flags ) ;

// This is the call that will take the place of the original
int INTER_cuMemHostGetDevicePointer( CUdeviceptr * pdptr, void * p, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pdptr,(void **)&p,(void **)&Flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemHostGetDevicePointer, (void*) &ORIGINAL_cuMemHostGetDevicePointer, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemHostGetFlags
extern int ORIGINAL_cuMemHostGetFlags( unsigned int * pFlags, void * p ) ;

// This is the call that will take the place of the original
int INTER_cuMemHostGetFlags( unsigned int * pFlags, void * p ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pFlags,(void **)&p };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemHostGetFlags, (void*) &ORIGINAL_cuMemHostGetFlags, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemAllocManaged
extern int ORIGINAL_cuMemAllocManaged( CUdeviceptr * dptr, size_t bytesize, unsigned int flags ) ;

// This is the call that will take the place of the original
int INTER_cuMemAllocManaged( CUdeviceptr * dptr, size_t bytesize, unsigned int flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dptr,(void **)&bytesize,(void **)&flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemAllocManaged, (void*) &ORIGINAL_cuMemAllocManaged, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDeviceGetByPCIBusId
extern int ORIGINAL_cuDeviceGetByPCIBusId( CUdevice * dev, const char * pciBusId ) ;

// This is the call that will take the place of the original
int INTER_cuDeviceGetByPCIBusId( CUdevice * dev, const char * pciBusId ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dev,(void **)&pciBusId };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDeviceGetByPCIBusId, (void*) &ORIGINAL_cuDeviceGetByPCIBusId, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDeviceGetPCIBusId
extern int ORIGINAL_cuDeviceGetPCIBusId( char * pciBusId, int len, CUdevice dev ) ;

// This is the call that will take the place of the original
int INTER_cuDeviceGetPCIBusId( char * pciBusId, int len, CUdevice dev ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pciBusId,(void **)&len,(void **)&dev };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDeviceGetPCIBusId, (void*) &ORIGINAL_cuDeviceGetPCIBusId, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuIpcGetEventHandle
extern int ORIGINAL_cuIpcGetEventHandle( CUipcEventHandle * pHandle, CUevent event ) ;

// This is the call that will take the place of the original
int INTER_cuIpcGetEventHandle( CUipcEventHandle * pHandle, CUevent event ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pHandle,(void **)&event };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuIpcGetEventHandle, (void*) &ORIGINAL_cuIpcGetEventHandle, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuIpcOpenEventHandle
extern int ORIGINAL_cuIpcOpenEventHandle( CUevent * phEvent, CUipcEventHandle handle ) ;

// This is the call that will take the place of the original
int INTER_cuIpcOpenEventHandle( CUevent * phEvent, CUipcEventHandle handle ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&phEvent,(void **)&handle };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuIpcOpenEventHandle, (void*) &ORIGINAL_cuIpcOpenEventHandle, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuIpcGetMemHandle
extern int ORIGINAL_cuIpcGetMemHandle( CUipcMemHandle * pHandle, CUdeviceptr dptr ) ;

// This is the call that will take the place of the original
int INTER_cuIpcGetMemHandle( CUipcMemHandle * pHandle, CUdeviceptr dptr ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pHandle,(void **)&dptr };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuIpcGetMemHandle, (void*) &ORIGINAL_cuIpcGetMemHandle, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuIpcOpenMemHandle
extern int ORIGINAL_cuIpcOpenMemHandle( CUdeviceptr * pdptr, CUipcMemHandle handle, unsigned int Flags ) ;

// This is the call that will take the place of the original
int INTER_cuIpcOpenMemHandle( CUdeviceptr * pdptr, CUipcMemHandle handle, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pdptr,(void **)&handle,(void **)&Flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuIpcOpenMemHandle, (void*) &ORIGINAL_cuIpcOpenMemHandle, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuIpcCloseMemHandle
extern int ORIGINAL_cuIpcCloseMemHandle( CUdeviceptr dptr ) ;

// This is the call that will take the place of the original
int INTER_cuIpcCloseMemHandle( CUdeviceptr dptr ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dptr };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuIpcCloseMemHandle, (void*) &ORIGINAL_cuIpcCloseMemHandle, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemHostRegister
extern int ORIGINAL_cuMemHostRegister( void * p, size_t bytesize, unsigned int Flags ) ;

// This is the call that will take the place of the original
int INTER_cuMemHostRegister( void * p, size_t bytesize, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&p,(void **)&bytesize,(void **)&Flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemHostRegister, (void*) &ORIGINAL_cuMemHostRegister, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemHostUnregister
extern int ORIGINAL_cuMemHostUnregister( void * p ) ;

// This is the call that will take the place of the original
int INTER_cuMemHostUnregister( void * p ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&p };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemHostUnregister, (void*) &ORIGINAL_cuMemHostUnregister, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpy
extern int ORIGINAL_cuMemcpy( CUdeviceptr dst, CUdeviceptr src, size_t ByteCount ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpy( CUdeviceptr dst, CUdeviceptr src, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dst,(void **)&src,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpy, (void*) &ORIGINAL_cuMemcpy, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyPeer
extern int ORIGINAL_cuMemcpyPeer( CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpyPeer( CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&dstContext,(void **)&srcDevice,(void **)&srcContext,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyPeer, (void*) &ORIGINAL_cuMemcpyPeer, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyHtoD
extern int ORIGINAL_cuMemcpyHtoD( CUdeviceptr dstDevice, const void * srcHost, size_t ByteCount ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpyHtoD( CUdeviceptr dstDevice, const void * srcHost, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&srcHost,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyHtoD, (void*) &ORIGINAL_cuMemcpyHtoD, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyDtoH
extern int ORIGINAL_cuMemcpyDtoH( void * dstHost, CUdeviceptr srcDevice, size_t ByteCount ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpyDtoH( void * dstHost, CUdeviceptr srcDevice, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstHost,(void **)&srcDevice,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyDtoH, (void*) &ORIGINAL_cuMemcpyDtoH, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyDtoD
extern int ORIGINAL_cuMemcpyDtoD( CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpyDtoD( CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&srcDevice,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyDtoD, (void*) &ORIGINAL_cuMemcpyDtoD, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyDtoA
extern int ORIGINAL_cuMemcpyDtoA( CUarray dstArray, size_t dstOffset, CUdeviceptr srcDevice, size_t ByteCount ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpyDtoA( CUarray dstArray, size_t dstOffset, CUdeviceptr srcDevice, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstArray,(void **)&dstOffset,(void **)&srcDevice,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyDtoA, (void*) &ORIGINAL_cuMemcpyDtoA, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyAtoD
extern int ORIGINAL_cuMemcpyAtoD( CUdeviceptr dstDevice, CUarray srcArray, size_t srcOffset, size_t ByteCount ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpyAtoD( CUdeviceptr dstDevice, CUarray srcArray, size_t srcOffset, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&srcArray,(void **)&srcOffset,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyAtoD, (void*) &ORIGINAL_cuMemcpyAtoD, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyHtoA
extern int ORIGINAL_cuMemcpyHtoA( CUarray dstArray, size_t dstOffset, const void * srcHost, size_t ByteCount ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpyHtoA( CUarray dstArray, size_t dstOffset, const void * srcHost, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstArray,(void **)&dstOffset,(void **)&srcHost,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyHtoA, (void*) &ORIGINAL_cuMemcpyHtoA, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyAtoH
extern int ORIGINAL_cuMemcpyAtoH( void * dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpyAtoH( void * dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstHost,(void **)&srcArray,(void **)&srcOffset,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyAtoH, (void*) &ORIGINAL_cuMemcpyAtoH, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyAtoA
extern int ORIGINAL_cuMemcpyAtoA( CUarray dstArray, size_t dstOffset, CUarray srcArray, size_t srcOffset, size_t ByteCount ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpyAtoA( CUarray dstArray, size_t dstOffset, CUarray srcArray, size_t srcOffset, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstArray,(void **)&dstOffset,(void **)&srcArray,(void **)&srcOffset,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyAtoA, (void*) &ORIGINAL_cuMemcpyAtoA, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpy2D
extern int ORIGINAL_cuMemcpy2D( const CUDA_MEMCPY2D * pCopy ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpy2D( const CUDA_MEMCPY2D * pCopy ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pCopy };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpy2D, (void*) &ORIGINAL_cuMemcpy2D, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpy2DUnaligned
extern int ORIGINAL_cuMemcpy2DUnaligned( const CUDA_MEMCPY2D * pCopy ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpy2DUnaligned( const CUDA_MEMCPY2D * pCopy ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pCopy };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpy2DUnaligned, (void*) &ORIGINAL_cuMemcpy2DUnaligned, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpy3D
extern int ORIGINAL_cuMemcpy3D( const CUDA_MEMCPY3D * pCopy ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpy3D( const CUDA_MEMCPY3D * pCopy ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pCopy };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpy3D, (void*) &ORIGINAL_cuMemcpy3D, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpy3DPeer
extern int ORIGINAL_cuMemcpy3DPeer( const CUDA_MEMCPY3D_PEER * pCopy ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpy3DPeer( const CUDA_MEMCPY3D_PEER * pCopy ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pCopy };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpy3DPeer, (void*) &ORIGINAL_cuMemcpy3DPeer, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyAsync
extern int ORIGINAL_cuMemcpyAsync( CUdeviceptr dst, CUdeviceptr src, size_t ByteCount, CUstream hStream ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpyAsync( CUdeviceptr dst, CUdeviceptr src, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dst,(void **)&src,(void **)&ByteCount,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyAsync, (void*) &ORIGINAL_cuMemcpyAsync, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyPeerAsync
extern int ORIGINAL_cuMemcpyPeerAsync( CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount, CUstream hStream ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpyPeerAsync( CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&dstContext,(void **)&srcDevice,(void **)&srcContext,(void **)&ByteCount,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyPeerAsync, (void*) &ORIGINAL_cuMemcpyPeerAsync, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyHtoDAsync
extern int ORIGINAL_cuMemcpyHtoDAsync( CUdeviceptr dstDevice, const void * srcHost, size_t ByteCount, CUstream hStream ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpyHtoDAsync( CUdeviceptr dstDevice, const void * srcHost, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&srcHost,(void **)&ByteCount,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyHtoDAsync, (void*) &ORIGINAL_cuMemcpyHtoDAsync, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyDtoHAsync
extern int ORIGINAL_cuMemcpyDtoHAsync( void * dstHost, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpyDtoHAsync( void * dstHost, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstHost,(void **)&srcDevice,(void **)&ByteCount,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyDtoHAsync, (void*) &ORIGINAL_cuMemcpyDtoHAsync, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyDtoDAsync
extern int ORIGINAL_cuMemcpyDtoDAsync( CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpyDtoDAsync( CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&srcDevice,(void **)&ByteCount,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyDtoDAsync, (void*) &ORIGINAL_cuMemcpyDtoDAsync, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyHtoAAsync
extern int ORIGINAL_cuMemcpyHtoAAsync( CUarray dstArray, size_t dstOffset, const void * srcHost, size_t ByteCount, CUstream hStream ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpyHtoAAsync( CUarray dstArray, size_t dstOffset, const void * srcHost, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstArray,(void **)&dstOffset,(void **)&srcHost,(void **)&ByteCount,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyHtoAAsync, (void*) &ORIGINAL_cuMemcpyHtoAAsync, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyAtoHAsync
extern int ORIGINAL_cuMemcpyAtoHAsync( void * dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount, CUstream hStream ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpyAtoHAsync( void * dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstHost,(void **)&srcArray,(void **)&srcOffset,(void **)&ByteCount,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyAtoHAsync, (void*) &ORIGINAL_cuMemcpyAtoHAsync, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpy2DAsync
extern int ORIGINAL_cuMemcpy2DAsync( const CUDA_MEMCPY2D * pCopy, CUstream hStream ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpy2DAsync( const CUDA_MEMCPY2D * pCopy, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pCopy,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpy2DAsync, (void*) &ORIGINAL_cuMemcpy2DAsync, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpy3DAsync
extern int ORIGINAL_cuMemcpy3DAsync( const CUDA_MEMCPY3D * pCopy, CUstream hStream ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpy3DAsync( const CUDA_MEMCPY3D * pCopy, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pCopy,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpy3DAsync, (void*) &ORIGINAL_cuMemcpy3DAsync, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpy3DPeerAsync
extern int ORIGINAL_cuMemcpy3DPeerAsync( const CUDA_MEMCPY3D_PEER * pCopy, CUstream hStream ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpy3DPeerAsync( const CUDA_MEMCPY3D_PEER * pCopy, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pCopy,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpy3DPeerAsync, (void*) &ORIGINAL_cuMemcpy3DPeerAsync, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD8
extern int ORIGINAL_cuMemsetD8( CUdeviceptr dstDevice, unsigned char uc, size_t N ) ;

// This is the call that will take the place of the original
int INTER_cuMemsetD8( CUdeviceptr dstDevice, unsigned char uc, size_t N ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&uc,(void **)&N };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD8, (void*) &ORIGINAL_cuMemsetD8, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD16
extern int ORIGINAL_cuMemsetD16( CUdeviceptr dstDevice, unsigned short us, size_t N ) ;

// This is the call that will take the place of the original
int INTER_cuMemsetD16( CUdeviceptr dstDevice, unsigned short us, size_t N ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&us,(void **)&N };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD16, (void*) &ORIGINAL_cuMemsetD16, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD32
extern int ORIGINAL_cuMemsetD32( CUdeviceptr dstDevice, unsigned int ui, size_t N ) ;

// This is the call that will take the place of the original
int INTER_cuMemsetD32( CUdeviceptr dstDevice, unsigned int ui, size_t N ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&ui,(void **)&N };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD32, (void*) &ORIGINAL_cuMemsetD32, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD2D8
extern int ORIGINAL_cuMemsetD2D8( CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height ) ;

// This is the call that will take the place of the original
int INTER_cuMemsetD2D8( CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&dstPitch,(void **)&uc,(void **)&Width,(void **)&Height };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD2D8, (void*) &ORIGINAL_cuMemsetD2D8, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD2D16
extern int ORIGINAL_cuMemsetD2D16( CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height ) ;

// This is the call that will take the place of the original
int INTER_cuMemsetD2D16( CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&dstPitch,(void **)&us,(void **)&Width,(void **)&Height };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD2D16, (void*) &ORIGINAL_cuMemsetD2D16, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD2D32
extern int ORIGINAL_cuMemsetD2D32( CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height ) ;

// This is the call that will take the place of the original
int INTER_cuMemsetD2D32( CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&dstPitch,(void **)&ui,(void **)&Width,(void **)&Height };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD2D32, (void*) &ORIGINAL_cuMemsetD2D32, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD8Async
extern int ORIGINAL_cuMemsetD8Async( CUdeviceptr dstDevice, unsigned char uc, size_t N, CUstream hStream ) ;

// This is the call that will take the place of the original
int INTER_cuMemsetD8Async( CUdeviceptr dstDevice, unsigned char uc, size_t N, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&uc,(void **)&N,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD8Async, (void*) &ORIGINAL_cuMemsetD8Async, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD16Async
extern int ORIGINAL_cuMemsetD16Async( CUdeviceptr dstDevice, unsigned short us, size_t N, CUstream hStream ) ;

// This is the call that will take the place of the original
int INTER_cuMemsetD16Async( CUdeviceptr dstDevice, unsigned short us, size_t N, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&us,(void **)&N,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD16Async, (void*) &ORIGINAL_cuMemsetD16Async, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD32Async
extern int ORIGINAL_cuMemsetD32Async( CUdeviceptr dstDevice, unsigned int ui, size_t N, CUstream hStream ) ;

// This is the call that will take the place of the original
int INTER_cuMemsetD32Async( CUdeviceptr dstDevice, unsigned int ui, size_t N, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&ui,(void **)&N,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD32Async, (void*) &ORIGINAL_cuMemsetD32Async, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD2D8Async
extern int ORIGINAL_cuMemsetD2D8Async( CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height, CUstream hStream ) ;

// This is the call that will take the place of the original
int INTER_cuMemsetD2D8Async( CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&dstPitch,(void **)&uc,(void **)&Width,(void **)&Height,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD2D8Async, (void*) &ORIGINAL_cuMemsetD2D8Async, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD2D16Async
extern int ORIGINAL_cuMemsetD2D16Async( CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height, CUstream hStream ) ;

// This is the call that will take the place of the original
int INTER_cuMemsetD2D16Async( CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&dstPitch,(void **)&us,(void **)&Width,(void **)&Height,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD2D16Async, (void*) &ORIGINAL_cuMemsetD2D16Async, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD2D32Async
extern int ORIGINAL_cuMemsetD2D32Async( CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height, CUstream hStream ) ;

// This is the call that will take the place of the original
int INTER_cuMemsetD2D32Async( CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&dstPitch,(void **)&ui,(void **)&Width,(void **)&Height,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD2D32Async, (void*) &ORIGINAL_cuMemsetD2D32Async, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuArrayCreate
extern int ORIGINAL_cuArrayCreate( CUarray * pHandle, const CUDA_ARRAY_DESCRIPTOR * pAllocateArray ) ;

// This is the call that will take the place of the original
int INTER_cuArrayCreate( CUarray * pHandle, const CUDA_ARRAY_DESCRIPTOR * pAllocateArray ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pHandle,(void **)&pAllocateArray };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuArrayCreate, (void*) &ORIGINAL_cuArrayCreate, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuArrayGetDescriptor
extern int ORIGINAL_cuArrayGetDescriptor( CUDA_ARRAY_DESCRIPTOR * pArrayDescriptor, CUarray hArray ) ;

// This is the call that will take the place of the original
int INTER_cuArrayGetDescriptor( CUDA_ARRAY_DESCRIPTOR * pArrayDescriptor, CUarray hArray ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pArrayDescriptor,(void **)&hArray };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuArrayGetDescriptor, (void*) &ORIGINAL_cuArrayGetDescriptor, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuArrayDestroy
extern int ORIGINAL_cuArrayDestroy( CUarray hArray ) ;

// This is the call that will take the place of the original
int INTER_cuArrayDestroy( CUarray hArray ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hArray };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuArrayDestroy, (void*) &ORIGINAL_cuArrayDestroy, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuArray3DCreate
extern int ORIGINAL_cuArray3DCreate( CUarray * pHandle, const CUDA_ARRAY3D_DESCRIPTOR * pAllocateArray ) ;

// This is the call that will take the place of the original
int INTER_cuArray3DCreate( CUarray * pHandle, const CUDA_ARRAY3D_DESCRIPTOR * pAllocateArray ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pHandle,(void **)&pAllocateArray };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuArray3DCreate, (void*) &ORIGINAL_cuArray3DCreate, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuArray3DGetDescriptor
extern int ORIGINAL_cuArray3DGetDescriptor( CUDA_ARRAY3D_DESCRIPTOR * pArrayDescriptor, CUarray hArray ) ;

// This is the call that will take the place of the original
int INTER_cuArray3DGetDescriptor( CUDA_ARRAY3D_DESCRIPTOR * pArrayDescriptor, CUarray hArray ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pArrayDescriptor,(void **)&hArray };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuArray3DGetDescriptor, (void*) &ORIGINAL_cuArray3DGetDescriptor, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMipmappedArrayCreate
extern int ORIGINAL_cuMipmappedArrayCreate( CUmipmappedArray * pHandle, const CUDA_ARRAY3D_DESCRIPTOR * pMipmappedArrayDesc, unsigned int numMipmapLevels ) ;

// This is the call that will take the place of the original
int INTER_cuMipmappedArrayCreate( CUmipmappedArray * pHandle, const CUDA_ARRAY3D_DESCRIPTOR * pMipmappedArrayDesc, unsigned int numMipmapLevels ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pHandle,(void **)&pMipmappedArrayDesc,(void **)&numMipmapLevels };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMipmappedArrayCreate, (void*) &ORIGINAL_cuMipmappedArrayCreate, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMipmappedArrayGetLevel
extern int ORIGINAL_cuMipmappedArrayGetLevel( CUarray * pLevelArray, CUmipmappedArray hMipmappedArray, unsigned int level ) ;

// This is the call that will take the place of the original
int INTER_cuMipmappedArrayGetLevel( CUarray * pLevelArray, CUmipmappedArray hMipmappedArray, unsigned int level ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pLevelArray,(void **)&hMipmappedArray,(void **)&level };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMipmappedArrayGetLevel, (void*) &ORIGINAL_cuMipmappedArrayGetLevel, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMipmappedArrayDestroy
extern int ORIGINAL_cuMipmappedArrayDestroy( CUmipmappedArray hMipmappedArray ) ;

// This is the call that will take the place of the original
int INTER_cuMipmappedArrayDestroy( CUmipmappedArray hMipmappedArray ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hMipmappedArray };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMipmappedArrayDestroy, (void*) &ORIGINAL_cuMipmappedArrayDestroy, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuPointerGetAttribute
extern int ORIGINAL_cuPointerGetAttribute( void * data, CUpointer_attribute attribute, CUdeviceptr ptr ) ;

// This is the call that will take the place of the original
int INTER_cuPointerGetAttribute( void * data, CUpointer_attribute attribute, CUdeviceptr ptr ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&data,(void **)&attribute,(void **)&ptr };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuPointerGetAttribute, (void*) &ORIGINAL_cuPointerGetAttribute, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemPrefetchAsync
extern int ORIGINAL_cuMemPrefetchAsync( CUdeviceptr devPtr, size_t count, CUdevice dstDevice, CUstream hStream ) ;

// This is the call that will take the place of the original
int INTER_cuMemPrefetchAsync( CUdeviceptr devPtr, size_t count, CUdevice dstDevice, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&devPtr,(void **)&count,(void **)&dstDevice,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemPrefetchAsync, (void*) &ORIGINAL_cuMemPrefetchAsync, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemAdvise
extern int ORIGINAL_cuMemAdvise( CUdeviceptr devPtr, size_t count, CUmem_advise advice, CUdevice device ) ;

// This is the call that will take the place of the original
int INTER_cuMemAdvise( CUdeviceptr devPtr, size_t count, CUmem_advise advice, CUdevice device ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&devPtr,(void **)&count,(void **)&advice,(void **)&device };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemAdvise, (void*) &ORIGINAL_cuMemAdvise, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemRangeGetAttribute
extern int ORIGINAL_cuMemRangeGetAttribute( void * data, size_t dataSize, CUmem_range_attribute attribute, CUdeviceptr devPtr, size_t count ) ;

// This is the call that will take the place of the original
int INTER_cuMemRangeGetAttribute( void * data, size_t dataSize, CUmem_range_attribute attribute, CUdeviceptr devPtr, size_t count ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&data,(void **)&dataSize,(void **)&attribute,(void **)&devPtr,(void **)&count };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemRangeGetAttribute, (void*) &ORIGINAL_cuMemRangeGetAttribute, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemRangeGetAttributes
extern int ORIGINAL_cuMemRangeGetAttributes( void * * data, size_t * dataSizes, CUmem_range_attribute * attributes, size_t numAttributes, CUdeviceptr devPtr, size_t count ) ;

// This is the call that will take the place of the original
int INTER_cuMemRangeGetAttributes( void * * data, size_t * dataSizes, CUmem_range_attribute * attributes, size_t numAttributes, CUdeviceptr devPtr, size_t count ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&data,(void **)&dataSizes,(void **)&attributes,(void **)&numAttributes,(void **)&devPtr,(void **)&count };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemRangeGetAttributes, (void*) &ORIGINAL_cuMemRangeGetAttributes, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuPointerSetAttribute
extern int ORIGINAL_cuPointerSetAttribute( const void * value, CUpointer_attribute attribute, CUdeviceptr ptr ) ;

// This is the call that will take the place of the original
int INTER_cuPointerSetAttribute( const void * value, CUpointer_attribute attribute, CUdeviceptr ptr ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&value,(void **)&attribute,(void **)&ptr };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuPointerSetAttribute, (void*) &ORIGINAL_cuPointerSetAttribute, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuPointerGetAttributes
extern int ORIGINAL_cuPointerGetAttributes( unsigned int numAttributes, CUpointer_attribute * attributes, void * * data, CUdeviceptr ptr ) ;

// This is the call that will take the place of the original
int INTER_cuPointerGetAttributes( unsigned int numAttributes, CUpointer_attribute * attributes, void * * data, CUdeviceptr ptr ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&numAttributes,(void **)&attributes,(void **)&data,(void **)&ptr };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuPointerGetAttributes, (void*) &ORIGINAL_cuPointerGetAttributes, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuStreamCreate
extern int ORIGINAL_cuStreamCreate( CUstream * phStream, unsigned int Flags ) ;

// This is the call that will take the place of the original
int INTER_cuStreamCreate( CUstream * phStream, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&phStream,(void **)&Flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuStreamCreate, (void*) &ORIGINAL_cuStreamCreate, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuStreamCreateWithPriority
extern int ORIGINAL_cuStreamCreateWithPriority( CUstream * phStream, unsigned int flags, int priority ) ;

// This is the call that will take the place of the original
int INTER_cuStreamCreateWithPriority( CUstream * phStream, unsigned int flags, int priority ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&phStream,(void **)&flags,(void **)&priority };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuStreamCreateWithPriority, (void*) &ORIGINAL_cuStreamCreateWithPriority, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuStreamGetPriority
extern int ORIGINAL_cuStreamGetPriority( CUstream hStream, int * priority ) ;

// This is the call that will take the place of the original
int INTER_cuStreamGetPriority( CUstream hStream, int * priority ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hStream,(void **)&priority };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuStreamGetPriority, (void*) &ORIGINAL_cuStreamGetPriority, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuStreamGetFlags
extern int ORIGINAL_cuStreamGetFlags( CUstream hStream, unsigned int * flags ) ;

// This is the call that will take the place of the original
int INTER_cuStreamGetFlags( CUstream hStream, unsigned int * flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hStream,(void **)&flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuStreamGetFlags, (void*) &ORIGINAL_cuStreamGetFlags, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuStreamWaitEvent
extern int ORIGINAL_cuStreamWaitEvent( CUstream hStream, CUevent hEvent, unsigned int Flags ) ;

// This is the call that will take the place of the original
int INTER_cuStreamWaitEvent( CUstream hStream, CUevent hEvent, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hStream,(void **)&hEvent,(void **)&Flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuStreamWaitEvent, (void*) &ORIGINAL_cuStreamWaitEvent, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuStreamAddCallback
extern int ORIGINAL_cuStreamAddCallback( CUstream hStream, CUstreamCallback callback, void * userData, unsigned int flags ) ;

// This is the call that will take the place of the original
int INTER_cuStreamAddCallback( CUstream hStream, CUstreamCallback callback, void * userData, unsigned int flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hStream,(void **)&callback,(void **)&userData,(void **)&flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuStreamAddCallback, (void*) &ORIGINAL_cuStreamAddCallback, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuStreamAttachMemAsync
extern int ORIGINAL_cuStreamAttachMemAsync( CUstream hStream, CUdeviceptr dptr, size_t length, unsigned int flags ) ;

// This is the call that will take the place of the original
int INTER_cuStreamAttachMemAsync( CUstream hStream, CUdeviceptr dptr, size_t length, unsigned int flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hStream,(void **)&dptr,(void **)&length,(void **)&flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuStreamAttachMemAsync, (void*) &ORIGINAL_cuStreamAttachMemAsync, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuStreamQuery
extern int ORIGINAL_cuStreamQuery( CUstream hStream ) ;

// This is the call that will take the place of the original
int INTER_cuStreamQuery( CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuStreamQuery, (void*) &ORIGINAL_cuStreamQuery, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuStreamSynchronize
extern int ORIGINAL_cuStreamSynchronize( CUstream hStream ) ;

// This is the call that will take the place of the original
int INTER_cuStreamSynchronize( CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuStreamSynchronize, (void*) &ORIGINAL_cuStreamSynchronize, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuStreamDestroy
extern int ORIGINAL_cuStreamDestroy( CUstream hStream ) ;

// This is the call that will take the place of the original
int INTER_cuStreamDestroy( CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuStreamDestroy, (void*) &ORIGINAL_cuStreamDestroy, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuEventCreate
extern int ORIGINAL_cuEventCreate( CUevent * phEvent, unsigned int Flags ) ;

// This is the call that will take the place of the original
int INTER_cuEventCreate( CUevent * phEvent, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&phEvent,(void **)&Flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuEventCreate, (void*) &ORIGINAL_cuEventCreate, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuEventRecord
extern int ORIGINAL_cuEventRecord( CUevent hEvent, CUstream hStream ) ;

// This is the call that will take the place of the original
int INTER_cuEventRecord( CUevent hEvent, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hEvent,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuEventRecord, (void*) &ORIGINAL_cuEventRecord, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuEventQuery
extern int ORIGINAL_cuEventQuery( CUevent hEvent ) ;

// This is the call that will take the place of the original
int INTER_cuEventQuery( CUevent hEvent ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hEvent };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuEventQuery, (void*) &ORIGINAL_cuEventQuery, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuEventSynchronize
extern int ORIGINAL_cuEventSynchronize( CUevent hEvent ) ;

// This is the call that will take the place of the original
int INTER_cuEventSynchronize( CUevent hEvent ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hEvent };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuEventSynchronize, (void*) &ORIGINAL_cuEventSynchronize, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuEventDestroy
extern int ORIGINAL_cuEventDestroy( CUevent hEvent ) ;

// This is the call that will take the place of the original
int INTER_cuEventDestroy( CUevent hEvent ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hEvent };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuEventDestroy, (void*) &ORIGINAL_cuEventDestroy, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuEventElapsedTime
extern int ORIGINAL_cuEventElapsedTime( float * pMilliseconds, CUevent hStart, CUevent hEnd ) ;

// This is the call that will take the place of the original
int INTER_cuEventElapsedTime( float * pMilliseconds, CUevent hStart, CUevent hEnd ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pMilliseconds,(void **)&hStart,(void **)&hEnd };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuEventElapsedTime, (void*) &ORIGINAL_cuEventElapsedTime, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuStreamWaitValue32
extern int ORIGINAL_cuStreamWaitValue32( CUstream stream, CUdeviceptr addr, cuuint32_t value, unsigned int flags ) ;

// This is the call that will take the place of the original
int INTER_cuStreamWaitValue32( CUstream stream, CUdeviceptr addr, cuuint32_t value, unsigned int flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&stream,(void **)&addr,(void **)&value,(void **)&flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuStreamWaitValue32, (void*) &ORIGINAL_cuStreamWaitValue32, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuStreamWriteValue32
extern int ORIGINAL_cuStreamWriteValue32( CUstream stream, CUdeviceptr addr, cuuint32_t value, unsigned int flags ) ;

// This is the call that will take the place of the original
int INTER_cuStreamWriteValue32( CUstream stream, CUdeviceptr addr, cuuint32_t value, unsigned int flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&stream,(void **)&addr,(void **)&value,(void **)&flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuStreamWriteValue32, (void*) &ORIGINAL_cuStreamWriteValue32, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuStreamBatchMemOp
extern int ORIGINAL_cuStreamBatchMemOp( CUstream stream, unsigned int count, CUstreamBatchMemOpParams * paramArray, unsigned int flags ) ;

// This is the call that will take the place of the original
int INTER_cuStreamBatchMemOp( CUstream stream, unsigned int count, CUstreamBatchMemOpParams * paramArray, unsigned int flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&stream,(void **)&count,(void **)&paramArray,(void **)&flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuStreamBatchMemOp, (void*) &ORIGINAL_cuStreamBatchMemOp, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuFuncGetAttribute
extern int ORIGINAL_cuFuncGetAttribute( int * pi, CUfunction_attribute attrib, CUfunction hfunc ) ;

// This is the call that will take the place of the original
int INTER_cuFuncGetAttribute( int * pi, CUfunction_attribute attrib, CUfunction hfunc ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pi,(void **)&attrib,(void **)&hfunc };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuFuncGetAttribute, (void*) &ORIGINAL_cuFuncGetAttribute, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuFuncSetCacheConfig
extern int ORIGINAL_cuFuncSetCacheConfig( CUfunction hfunc, CUfunc_cache config ) ;

// This is the call that will take the place of the original
int INTER_cuFuncSetCacheConfig( CUfunction hfunc, CUfunc_cache config ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hfunc,(void **)&config };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuFuncSetCacheConfig, (void*) &ORIGINAL_cuFuncSetCacheConfig, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuFuncSetSharedMemConfig
extern int ORIGINAL_cuFuncSetSharedMemConfig( CUfunction hfunc, CUsharedconfig config ) ;

// This is the call that will take the place of the original
int INTER_cuFuncSetSharedMemConfig( CUfunction hfunc, CUsharedconfig config ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hfunc,(void **)&config };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuFuncSetSharedMemConfig, (void*) &ORIGINAL_cuFuncSetSharedMemConfig, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuLaunchKernel
extern int ORIGINAL_cuLaunchKernel( CUfunction f, unsigned int gridDimX, unsigned int gridDimY, unsigned int gridDimZ, unsigned int blockDimX, unsigned int blockDimY, unsigned int blockDimZ, unsigned int sharedMemBytes, CUstream hStream, void * * kernelParams, void * * extra ) ;

// This is the call that will take the place of the original
int INTER_cuLaunchKernel( CUfunction f, unsigned int gridDimX, unsigned int gridDimY, unsigned int gridDimZ, unsigned int blockDimX, unsigned int blockDimY, unsigned int blockDimZ, unsigned int sharedMemBytes, CUstream hStream, void * * kernelParams, void * * extra ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&f,(void **)&gridDimX,(void **)&gridDimY,(void **)&gridDimZ,(void **)&blockDimX,(void **)&blockDimY,(void **)&blockDimZ,(void **)&sharedMemBytes,(void **)&hStream,(void **)&kernelParams,(void **)&extra };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuLaunchKernel, (void*) &ORIGINAL_cuLaunchKernel, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuFuncSetBlockShape
extern int ORIGINAL_cuFuncSetBlockShape( CUfunction hfunc, int x, int y, int z ) ;

// This is the call that will take the place of the original
int INTER_cuFuncSetBlockShape( CUfunction hfunc, int x, int y, int z ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hfunc,(void **)&x,(void **)&y,(void **)&z };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuFuncSetBlockShape, (void*) &ORIGINAL_cuFuncSetBlockShape, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuFuncSetSharedSize
extern int ORIGINAL_cuFuncSetSharedSize( CUfunction hfunc, unsigned int bytes ) ;

// This is the call that will take the place of the original
int INTER_cuFuncSetSharedSize( CUfunction hfunc, unsigned int bytes ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hfunc,(void **)&bytes };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuFuncSetSharedSize, (void*) &ORIGINAL_cuFuncSetSharedSize, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuParamSetSize
extern int ORIGINAL_cuParamSetSize( CUfunction hfunc, unsigned int numbytes ) ;

// This is the call that will take the place of the original
int INTER_cuParamSetSize( CUfunction hfunc, unsigned int numbytes ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hfunc,(void **)&numbytes };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuParamSetSize, (void*) &ORIGINAL_cuParamSetSize, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuParamSeti
extern int ORIGINAL_cuParamSeti( CUfunction hfunc, int offset, unsigned int value ) ;

// This is the call that will take the place of the original
int INTER_cuParamSeti( CUfunction hfunc, int offset, unsigned int value ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hfunc,(void **)&offset,(void **)&value };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuParamSeti, (void*) &ORIGINAL_cuParamSeti, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuParamSetf
extern int ORIGINAL_cuParamSetf( CUfunction hfunc, int offset, float value ) ;

// This is the call that will take the place of the original
int INTER_cuParamSetf( CUfunction hfunc, int offset, float value ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hfunc,(void **)&offset,(void **)&value };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuParamSetf, (void*) &ORIGINAL_cuParamSetf, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuParamSetv
extern int ORIGINAL_cuParamSetv( CUfunction hfunc, int offset, void * ptr, unsigned int numbytes ) ;

// This is the call that will take the place of the original
int INTER_cuParamSetv( CUfunction hfunc, int offset, void * ptr, unsigned int numbytes ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hfunc,(void **)&offset,(void **)&ptr,(void **)&numbytes };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuParamSetv, (void*) &ORIGINAL_cuParamSetv, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuLaunch
extern int ORIGINAL_cuLaunch( CUfunction f ) ;

// This is the call that will take the place of the original
int INTER_cuLaunch( CUfunction f ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&f };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuLaunch, (void*) &ORIGINAL_cuLaunch, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuLaunchGrid
extern int ORIGINAL_cuLaunchGrid( CUfunction f, int grid_width, int grid_height ) ;

// This is the call that will take the place of the original
int INTER_cuLaunchGrid( CUfunction f, int grid_width, int grid_height ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&f,(void **)&grid_width,(void **)&grid_height };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuLaunchGrid, (void*) &ORIGINAL_cuLaunchGrid, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuLaunchGridAsync
extern int ORIGINAL_cuLaunchGridAsync( CUfunction f, int grid_width, int grid_height, CUstream hStream ) ;

// This is the call that will take the place of the original
int INTER_cuLaunchGridAsync( CUfunction f, int grid_width, int grid_height, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&f,(void **)&grid_width,(void **)&grid_height,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuLaunchGridAsync, (void*) &ORIGINAL_cuLaunchGridAsync, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuParamSetTexRef
extern int ORIGINAL_cuParamSetTexRef( CUfunction hfunc, int texunit, CUtexref hTexRef ) ;

// This is the call that will take the place of the original
int INTER_cuParamSetTexRef( CUfunction hfunc, int texunit, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hfunc,(void **)&texunit,(void **)&hTexRef };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuParamSetTexRef, (void*) &ORIGINAL_cuParamSetTexRef, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuOccupancyMaxActiveBlocksPerMultiprocessor
extern int ORIGINAL_cuOccupancyMaxActiveBlocksPerMultiprocessor( int * numBlocks, CUfunction func, int blockSize, size_t dynamicSMemSize ) ;

// This is the call that will take the place of the original
int INTER_cuOccupancyMaxActiveBlocksPerMultiprocessor( int * numBlocks, CUfunction func, int blockSize, size_t dynamicSMemSize ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&numBlocks,(void **)&func,(void **)&blockSize,(void **)&dynamicSMemSize };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuOccupancyMaxActiveBlocksPerMultiprocessor, (void*) &ORIGINAL_cuOccupancyMaxActiveBlocksPerMultiprocessor, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags
extern int ORIGINAL_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags( int * numBlocks, CUfunction func, int blockSize, size_t dynamicSMemSize, unsigned int flags ) ;

// This is the call that will take the place of the original
int INTER_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags( int * numBlocks, CUfunction func, int blockSize, size_t dynamicSMemSize, unsigned int flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&numBlocks,(void **)&func,(void **)&blockSize,(void **)&dynamicSMemSize,(void **)&flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags, (void*) &ORIGINAL_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuOccupancyMaxPotentialBlockSize
extern int ORIGINAL_cuOccupancyMaxPotentialBlockSize( int * minGridSize, int * blockSize, CUfunction func, CUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int blockSizeLimit ) ;

// This is the call that will take the place of the original
int INTER_cuOccupancyMaxPotentialBlockSize( int * minGridSize, int * blockSize, CUfunction func, CUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int blockSizeLimit ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&minGridSize,(void **)&blockSize,(void **)&func,(void **)&blockSizeToDynamicSMemSize,(void **)&dynamicSMemSize,(void **)&blockSizeLimit };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuOccupancyMaxPotentialBlockSize, (void*) &ORIGINAL_cuOccupancyMaxPotentialBlockSize, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuOccupancyMaxPotentialBlockSizeWithFlags
extern int ORIGINAL_cuOccupancyMaxPotentialBlockSizeWithFlags( int * minGridSize, int * blockSize, CUfunction func, CUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int blockSizeLimit, unsigned int flags ) ;

// This is the call that will take the place of the original
int INTER_cuOccupancyMaxPotentialBlockSizeWithFlags( int * minGridSize, int * blockSize, CUfunction func, CUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int blockSizeLimit, unsigned int flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&minGridSize,(void **)&blockSize,(void **)&func,(void **)&blockSizeToDynamicSMemSize,(void **)&dynamicSMemSize,(void **)&blockSizeLimit,(void **)&flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuOccupancyMaxPotentialBlockSizeWithFlags, (void*) &ORIGINAL_cuOccupancyMaxPotentialBlockSizeWithFlags, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefSetArray
extern int ORIGINAL_cuTexRefSetArray( CUtexref hTexRef, CUarray hArray, unsigned int Flags ) ;

// This is the call that will take the place of the original
int INTER_cuTexRefSetArray( CUtexref hTexRef, CUarray hArray, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hTexRef,(void **)&hArray,(void **)&Flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefSetArray, (void*) &ORIGINAL_cuTexRefSetArray, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefSetMipmappedArray
extern int ORIGINAL_cuTexRefSetMipmappedArray( CUtexref hTexRef, CUmipmappedArray hMipmappedArray, unsigned int Flags ) ;

// This is the call that will take the place of the original
int INTER_cuTexRefSetMipmappedArray( CUtexref hTexRef, CUmipmappedArray hMipmappedArray, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hTexRef,(void **)&hMipmappedArray,(void **)&Flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefSetMipmappedArray, (void*) &ORIGINAL_cuTexRefSetMipmappedArray, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefSetAddress
extern int ORIGINAL_cuTexRefSetAddress( size_t * ByteOffset, CUtexref hTexRef, CUdeviceptr dptr, size_t bytes ) ;

// This is the call that will take the place of the original
int INTER_cuTexRefSetAddress( size_t * ByteOffset, CUtexref hTexRef, CUdeviceptr dptr, size_t bytes ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&ByteOffset,(void **)&hTexRef,(void **)&dptr,(void **)&bytes };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefSetAddress, (void*) &ORIGINAL_cuTexRefSetAddress, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefSetAddress2D
extern int ORIGINAL_cuTexRefSetAddress2D( CUtexref hTexRef, const CUDA_ARRAY_DESCRIPTOR * desc, CUdeviceptr dptr, size_t Pitch ) ;

// This is the call that will take the place of the original
int INTER_cuTexRefSetAddress2D( CUtexref hTexRef, const CUDA_ARRAY_DESCRIPTOR * desc, CUdeviceptr dptr, size_t Pitch ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hTexRef,(void **)&desc,(void **)&dptr,(void **)&Pitch };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefSetAddress2D, (void*) &ORIGINAL_cuTexRefSetAddress2D, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefSetFormat
extern int ORIGINAL_cuTexRefSetFormat( CUtexref hTexRef, CUarray_format fmt, int NumPackedComponents ) ;

// This is the call that will take the place of the original
int INTER_cuTexRefSetFormat( CUtexref hTexRef, CUarray_format fmt, int NumPackedComponents ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hTexRef,(void **)&fmt,(void **)&NumPackedComponents };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefSetFormat, (void*) &ORIGINAL_cuTexRefSetFormat, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefSetAddressMode
extern int ORIGINAL_cuTexRefSetAddressMode( CUtexref hTexRef, int dim, CUaddress_mode am ) ;

// This is the call that will take the place of the original
int INTER_cuTexRefSetAddressMode( CUtexref hTexRef, int dim, CUaddress_mode am ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hTexRef,(void **)&dim,(void **)&am };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefSetAddressMode, (void*) &ORIGINAL_cuTexRefSetAddressMode, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefSetFilterMode
extern int ORIGINAL_cuTexRefSetFilterMode( CUtexref hTexRef, CUfilter_mode fm ) ;

// This is the call that will take the place of the original
int INTER_cuTexRefSetFilterMode( CUtexref hTexRef, CUfilter_mode fm ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hTexRef,(void **)&fm };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefSetFilterMode, (void*) &ORIGINAL_cuTexRefSetFilterMode, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefSetMipmapFilterMode
extern int ORIGINAL_cuTexRefSetMipmapFilterMode( CUtexref hTexRef, CUfilter_mode fm ) ;

// This is the call that will take the place of the original
int INTER_cuTexRefSetMipmapFilterMode( CUtexref hTexRef, CUfilter_mode fm ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hTexRef,(void **)&fm };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefSetMipmapFilterMode, (void*) &ORIGINAL_cuTexRefSetMipmapFilterMode, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefSetMipmapLevelBias
extern int ORIGINAL_cuTexRefSetMipmapLevelBias( CUtexref hTexRef, float bias ) ;

// This is the call that will take the place of the original
int INTER_cuTexRefSetMipmapLevelBias( CUtexref hTexRef, float bias ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hTexRef,(void **)&bias };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefSetMipmapLevelBias, (void*) &ORIGINAL_cuTexRefSetMipmapLevelBias, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefSetMipmapLevelClamp
extern int ORIGINAL_cuTexRefSetMipmapLevelClamp( CUtexref hTexRef, float minMipmapLevelClamp, float maxMipmapLevelClamp ) ;

// This is the call that will take the place of the original
int INTER_cuTexRefSetMipmapLevelClamp( CUtexref hTexRef, float minMipmapLevelClamp, float maxMipmapLevelClamp ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hTexRef,(void **)&minMipmapLevelClamp,(void **)&maxMipmapLevelClamp };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefSetMipmapLevelClamp, (void*) &ORIGINAL_cuTexRefSetMipmapLevelClamp, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefSetMaxAnisotropy
extern int ORIGINAL_cuTexRefSetMaxAnisotropy( CUtexref hTexRef, unsigned int maxAniso ) ;

// This is the call that will take the place of the original
int INTER_cuTexRefSetMaxAnisotropy( CUtexref hTexRef, unsigned int maxAniso ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hTexRef,(void **)&maxAniso };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefSetMaxAnisotropy, (void*) &ORIGINAL_cuTexRefSetMaxAnisotropy, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefSetBorderColor
extern int ORIGINAL_cuTexRefSetBorderColor( CUtexref hTexRef, float * pBorderColor ) ;

// This is the call that will take the place of the original
int INTER_cuTexRefSetBorderColor( CUtexref hTexRef, float * pBorderColor ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hTexRef,(void **)&pBorderColor };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefSetBorderColor, (void*) &ORIGINAL_cuTexRefSetBorderColor, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefSetFlags
extern int ORIGINAL_cuTexRefSetFlags( CUtexref hTexRef, unsigned int Flags ) ;

// This is the call that will take the place of the original
int INTER_cuTexRefSetFlags( CUtexref hTexRef, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hTexRef,(void **)&Flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefSetFlags, (void*) &ORIGINAL_cuTexRefSetFlags, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefGetAddress
extern int ORIGINAL_cuTexRefGetAddress( CUdeviceptr * pdptr, CUtexref hTexRef ) ;

// This is the call that will take the place of the original
int INTER_cuTexRefGetAddress( CUdeviceptr * pdptr, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pdptr,(void **)&hTexRef };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefGetAddress, (void*) &ORIGINAL_cuTexRefGetAddress, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefGetArray
extern int ORIGINAL_cuTexRefGetArray( CUarray * phArray, CUtexref hTexRef ) ;

// This is the call that will take the place of the original
int INTER_cuTexRefGetArray( CUarray * phArray, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&phArray,(void **)&hTexRef };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefGetArray, (void*) &ORIGINAL_cuTexRefGetArray, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefGetMipmappedArray
extern int ORIGINAL_cuTexRefGetMipmappedArray( CUmipmappedArray * phMipmappedArray, CUtexref hTexRef ) ;

// This is the call that will take the place of the original
int INTER_cuTexRefGetMipmappedArray( CUmipmappedArray * phMipmappedArray, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&phMipmappedArray,(void **)&hTexRef };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefGetMipmappedArray, (void*) &ORIGINAL_cuTexRefGetMipmappedArray, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefGetAddressMode
extern int ORIGINAL_cuTexRefGetAddressMode( CUaddress_mode * pam, CUtexref hTexRef, int dim ) ;

// This is the call that will take the place of the original
int INTER_cuTexRefGetAddressMode( CUaddress_mode * pam, CUtexref hTexRef, int dim ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pam,(void **)&hTexRef,(void **)&dim };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefGetAddressMode, (void*) &ORIGINAL_cuTexRefGetAddressMode, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefGetFilterMode
extern int ORIGINAL_cuTexRefGetFilterMode( CUfilter_mode * pfm, CUtexref hTexRef ) ;

// This is the call that will take the place of the original
int INTER_cuTexRefGetFilterMode( CUfilter_mode * pfm, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pfm,(void **)&hTexRef };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefGetFilterMode, (void*) &ORIGINAL_cuTexRefGetFilterMode, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefGetFormat
extern int ORIGINAL_cuTexRefGetFormat( CUarray_format * pFormat, int * pNumChannels, CUtexref hTexRef ) ;

// This is the call that will take the place of the original
int INTER_cuTexRefGetFormat( CUarray_format * pFormat, int * pNumChannels, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pFormat,(void **)&pNumChannels,(void **)&hTexRef };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefGetFormat, (void*) &ORIGINAL_cuTexRefGetFormat, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefGetMipmapFilterMode
extern int ORIGINAL_cuTexRefGetMipmapFilterMode( CUfilter_mode * pfm, CUtexref hTexRef ) ;

// This is the call that will take the place of the original
int INTER_cuTexRefGetMipmapFilterMode( CUfilter_mode * pfm, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pfm,(void **)&hTexRef };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefGetMipmapFilterMode, (void*) &ORIGINAL_cuTexRefGetMipmapFilterMode, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefGetMipmapLevelBias
extern int ORIGINAL_cuTexRefGetMipmapLevelBias( float * pbias, CUtexref hTexRef ) ;

// This is the call that will take the place of the original
int INTER_cuTexRefGetMipmapLevelBias( float * pbias, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pbias,(void **)&hTexRef };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefGetMipmapLevelBias, (void*) &ORIGINAL_cuTexRefGetMipmapLevelBias, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefGetMipmapLevelClamp
extern int ORIGINAL_cuTexRefGetMipmapLevelClamp( float * pminMipmapLevelClamp, float * pmaxMipmapLevelClamp, CUtexref hTexRef ) ;

// This is the call that will take the place of the original
int INTER_cuTexRefGetMipmapLevelClamp( float * pminMipmapLevelClamp, float * pmaxMipmapLevelClamp, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pminMipmapLevelClamp,(void **)&pmaxMipmapLevelClamp,(void **)&hTexRef };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefGetMipmapLevelClamp, (void*) &ORIGINAL_cuTexRefGetMipmapLevelClamp, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefGetMaxAnisotropy
extern int ORIGINAL_cuTexRefGetMaxAnisotropy( int * pmaxAniso, CUtexref hTexRef ) ;

// This is the call that will take the place of the original
int INTER_cuTexRefGetMaxAnisotropy( int * pmaxAniso, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pmaxAniso,(void **)&hTexRef };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefGetMaxAnisotropy, (void*) &ORIGINAL_cuTexRefGetMaxAnisotropy, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefGetBorderColor
extern int ORIGINAL_cuTexRefGetBorderColor( float * pBorderColor, CUtexref hTexRef ) ;

// This is the call that will take the place of the original
int INTER_cuTexRefGetBorderColor( float * pBorderColor, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pBorderColor,(void **)&hTexRef };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefGetBorderColor, (void*) &ORIGINAL_cuTexRefGetBorderColor, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefGetFlags
extern int ORIGINAL_cuTexRefGetFlags( unsigned int * pFlags, CUtexref hTexRef ) ;

// This is the call that will take the place of the original
int INTER_cuTexRefGetFlags( unsigned int * pFlags, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pFlags,(void **)&hTexRef };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefGetFlags, (void*) &ORIGINAL_cuTexRefGetFlags, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefCreate
extern int ORIGINAL_cuTexRefCreate( CUtexref * pTexRef ) ;

// This is the call that will take the place of the original
int INTER_cuTexRefCreate( CUtexref * pTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pTexRef };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefCreate, (void*) &ORIGINAL_cuTexRefCreate, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefDestroy
extern int ORIGINAL_cuTexRefDestroy( CUtexref hTexRef ) ;

// This is the call that will take the place of the original
int INTER_cuTexRefDestroy( CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hTexRef };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefDestroy, (void*) &ORIGINAL_cuTexRefDestroy, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuSurfRefSetArray
extern int ORIGINAL_cuSurfRefSetArray( CUsurfref hSurfRef, CUarray hArray, unsigned int Flags ) ;

// This is the call that will take the place of the original
int INTER_cuSurfRefSetArray( CUsurfref hSurfRef, CUarray hArray, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hSurfRef,(void **)&hArray,(void **)&Flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuSurfRefSetArray, (void*) &ORIGINAL_cuSurfRefSetArray, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuSurfRefGetArray
extern int ORIGINAL_cuSurfRefGetArray( CUarray * phArray, CUsurfref hSurfRef ) ;

// This is the call that will take the place of the original
int INTER_cuSurfRefGetArray( CUarray * phArray, CUsurfref hSurfRef ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&phArray,(void **)&hSurfRef };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuSurfRefGetArray, (void*) &ORIGINAL_cuSurfRefGetArray, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexObjectCreate
extern int ORIGINAL_cuTexObjectCreate( CUtexObject * pTexObject, const CUDA_RESOURCE_DESC * pResDesc, const CUDA_TEXTURE_DESC * pTexDesc, const CUDA_RESOURCE_VIEW_DESC * pResViewDesc ) ;

// This is the call that will take the place of the original
int INTER_cuTexObjectCreate( CUtexObject * pTexObject, const CUDA_RESOURCE_DESC * pResDesc, const CUDA_TEXTURE_DESC * pTexDesc, const CUDA_RESOURCE_VIEW_DESC * pResViewDesc ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pTexObject,(void **)&pResDesc,(void **)&pTexDesc,(void **)&pResViewDesc };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexObjectCreate, (void*) &ORIGINAL_cuTexObjectCreate, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexObjectDestroy
extern int ORIGINAL_cuTexObjectDestroy( CUtexObject texObject ) ;

// This is the call that will take the place of the original
int INTER_cuTexObjectDestroy( CUtexObject texObject ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&texObject };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexObjectDestroy, (void*) &ORIGINAL_cuTexObjectDestroy, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexObjectGetResourceDesc
extern int ORIGINAL_cuTexObjectGetResourceDesc( CUDA_RESOURCE_DESC * pResDesc, CUtexObject texObject ) ;

// This is the call that will take the place of the original
int INTER_cuTexObjectGetResourceDesc( CUDA_RESOURCE_DESC * pResDesc, CUtexObject texObject ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pResDesc,(void **)&texObject };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexObjectGetResourceDesc, (void*) &ORIGINAL_cuTexObjectGetResourceDesc, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexObjectGetTextureDesc
extern int ORIGINAL_cuTexObjectGetTextureDesc( CUDA_TEXTURE_DESC * pTexDesc, CUtexObject texObject ) ;

// This is the call that will take the place of the original
int INTER_cuTexObjectGetTextureDesc( CUDA_TEXTURE_DESC * pTexDesc, CUtexObject texObject ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pTexDesc,(void **)&texObject };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexObjectGetTextureDesc, (void*) &ORIGINAL_cuTexObjectGetTextureDesc, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexObjectGetResourceViewDesc
extern int ORIGINAL_cuTexObjectGetResourceViewDesc( CUDA_RESOURCE_VIEW_DESC * pResViewDesc, CUtexObject texObject ) ;

// This is the call that will take the place of the original
int INTER_cuTexObjectGetResourceViewDesc( CUDA_RESOURCE_VIEW_DESC * pResViewDesc, CUtexObject texObject ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pResViewDesc,(void **)&texObject };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexObjectGetResourceViewDesc, (void*) &ORIGINAL_cuTexObjectGetResourceViewDesc, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuSurfObjectCreate
extern int ORIGINAL_cuSurfObjectCreate( CUsurfObject * pSurfObject, const CUDA_RESOURCE_DESC * pResDesc ) ;

// This is the call that will take the place of the original
int INTER_cuSurfObjectCreate( CUsurfObject * pSurfObject, const CUDA_RESOURCE_DESC * pResDesc ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pSurfObject,(void **)&pResDesc };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuSurfObjectCreate, (void*) &ORIGINAL_cuSurfObjectCreate, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuSurfObjectDestroy
extern int ORIGINAL_cuSurfObjectDestroy( CUsurfObject surfObject ) ;

// This is the call that will take the place of the original
int INTER_cuSurfObjectDestroy( CUsurfObject surfObject ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&surfObject };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuSurfObjectDestroy, (void*) &ORIGINAL_cuSurfObjectDestroy, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuSurfObjectGetResourceDesc
extern int ORIGINAL_cuSurfObjectGetResourceDesc( CUDA_RESOURCE_DESC * pResDesc, CUsurfObject surfObject ) ;

// This is the call that will take the place of the original
int INTER_cuSurfObjectGetResourceDesc( CUDA_RESOURCE_DESC * pResDesc, CUsurfObject surfObject ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pResDesc,(void **)&surfObject };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuSurfObjectGetResourceDesc, (void*) &ORIGINAL_cuSurfObjectGetResourceDesc, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDeviceCanAccessPeer
extern int ORIGINAL_cuDeviceCanAccessPeer( int * canAccessPeer, CUdevice dev, CUdevice peerDev ) ;

// This is the call that will take the place of the original
int INTER_cuDeviceCanAccessPeer( int * canAccessPeer, CUdevice dev, CUdevice peerDev ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&canAccessPeer,(void **)&dev,(void **)&peerDev };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDeviceCanAccessPeer, (void*) &ORIGINAL_cuDeviceCanAccessPeer, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuDeviceGetP2PAttribute
extern int ORIGINAL_cuDeviceGetP2PAttribute( int * value, CUdevice_P2PAttribute attrib, CUdevice srcDevice, CUdevice dstDevice ) ;

// This is the call that will take the place of the original
int INTER_cuDeviceGetP2PAttribute( int * value, CUdevice_P2PAttribute attrib, CUdevice srcDevice, CUdevice dstDevice ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&value,(void **)&attrib,(void **)&srcDevice,(void **)&dstDevice };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuDeviceGetP2PAttribute, (void*) &ORIGINAL_cuDeviceGetP2PAttribute, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxEnablePeerAccess
extern int ORIGINAL_cuCtxEnablePeerAccess( CUcontext peerContext, unsigned int Flags ) ;

// This is the call that will take the place of the original
int INTER_cuCtxEnablePeerAccess( CUcontext peerContext, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&peerContext,(void **)&Flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxEnablePeerAccess, (void*) &ORIGINAL_cuCtxEnablePeerAccess, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuCtxDisablePeerAccess
extern int ORIGINAL_cuCtxDisablePeerAccess( CUcontext peerContext ) ;

// This is the call that will take the place of the original
int INTER_cuCtxDisablePeerAccess( CUcontext peerContext ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&peerContext };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuCtxDisablePeerAccess, (void*) &ORIGINAL_cuCtxDisablePeerAccess, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuGraphicsUnregisterResource
extern int ORIGINAL_cuGraphicsUnregisterResource( CUgraphicsResource resource ) ;

// This is the call that will take the place of the original
int INTER_cuGraphicsUnregisterResource( CUgraphicsResource resource ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&resource };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuGraphicsUnregisterResource, (void*) &ORIGINAL_cuGraphicsUnregisterResource, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuGraphicsSubResourceGetMappedArray
extern int ORIGINAL_cuGraphicsSubResourceGetMappedArray( CUarray * pArray, CUgraphicsResource resource, unsigned int arrayIndex, unsigned int mipLevel ) ;

// This is the call that will take the place of the original
int INTER_cuGraphicsSubResourceGetMappedArray( CUarray * pArray, CUgraphicsResource resource, unsigned int arrayIndex, unsigned int mipLevel ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pArray,(void **)&resource,(void **)&arrayIndex,(void **)&mipLevel };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuGraphicsSubResourceGetMappedArray, (void*) &ORIGINAL_cuGraphicsSubResourceGetMappedArray, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuGraphicsResourceGetMappedMipmappedArray
extern int ORIGINAL_cuGraphicsResourceGetMappedMipmappedArray( CUmipmappedArray * pMipmappedArray, CUgraphicsResource resource ) ;

// This is the call that will take the place of the original
int INTER_cuGraphicsResourceGetMappedMipmappedArray( CUmipmappedArray * pMipmappedArray, CUgraphicsResource resource ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pMipmappedArray,(void **)&resource };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuGraphicsResourceGetMappedMipmappedArray, (void*) &ORIGINAL_cuGraphicsResourceGetMappedMipmappedArray, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuGraphicsResourceGetMappedPointer
extern int ORIGINAL_cuGraphicsResourceGetMappedPointer( CUdeviceptr * pDevPtr, size_t * pSize, CUgraphicsResource resource ) ;

// This is the call that will take the place of the original
int INTER_cuGraphicsResourceGetMappedPointer( CUdeviceptr * pDevPtr, size_t * pSize, CUgraphicsResource resource ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pDevPtr,(void **)&pSize,(void **)&resource };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuGraphicsResourceGetMappedPointer, (void*) &ORIGINAL_cuGraphicsResourceGetMappedPointer, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuGraphicsResourceSetMapFlags
extern int ORIGINAL_cuGraphicsResourceSetMapFlags( CUgraphicsResource resource, unsigned int flags ) ;

// This is the call that will take the place of the original
int INTER_cuGraphicsResourceSetMapFlags( CUgraphicsResource resource, unsigned int flags ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&resource,(void **)&flags };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuGraphicsResourceSetMapFlags, (void*) &ORIGINAL_cuGraphicsResourceSetMapFlags, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuGraphicsMapResources
extern int ORIGINAL_cuGraphicsMapResources( unsigned int count, CUgraphicsResource * resources, CUstream hStream ) ;

// This is the call that will take the place of the original
int INTER_cuGraphicsMapResources( unsigned int count, CUgraphicsResource * resources, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&count,(void **)&resources,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuGraphicsMapResources, (void*) &ORIGINAL_cuGraphicsMapResources, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuGraphicsUnmapResources
extern int ORIGINAL_cuGraphicsUnmapResources( unsigned int count, CUgraphicsResource * resources, CUstream hStream ) ;

// This is the call that will take the place of the original
int INTER_cuGraphicsUnmapResources( unsigned int count, CUgraphicsResource * resources, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&count,(void **)&resources,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuGraphicsUnmapResources, (void*) &ORIGINAL_cuGraphicsUnmapResources, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuGetExportTable
extern int ORIGINAL_cuGetExportTable( const void * * ppExportTable, const CUuuid * pExportTableId ) ;

// This is the call that will take the place of the original
int INTER_cuGetExportTable( const void * * ppExportTable, const CUuuid * pExportTableId ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&ppExportTable,(void **)&pExportTableId };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuGetExportTable, (void*) &ORIGINAL_cuGetExportTable, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuTexRefSetAddress2D_v2
extern int ORIGINAL_cuTexRefSetAddress2D_v2( CUtexref hTexRef, const CUDA_ARRAY_DESCRIPTOR * desc, CUdeviceptr dptr, size_t Pitch ) ;

// This is the call that will take the place of the original
int INTER_cuTexRefSetAddress2D_v2( CUtexref hTexRef, const CUDA_ARRAY_DESCRIPTOR * desc, CUdeviceptr dptr, size_t Pitch ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&hTexRef,(void **)&desc,(void **)&dptr,(void **)&Pitch };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuTexRefSetAddress2D_v2, (void*) &ORIGINAL_cuTexRefSetAddress2D_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyHtoD_v2
extern int ORIGINAL_cuMemcpyHtoD_v2( CUdeviceptr dstDevice, const void * srcHost, size_t ByteCount ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpyHtoD_v2( CUdeviceptr dstDevice, const void * srcHost, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&srcHost,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyHtoD_v2, (void*) &ORIGINAL_cuMemcpyHtoD_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyDtoH_v2
extern int ORIGINAL_cuMemcpyDtoH_v2( void * dstHost, CUdeviceptr srcDevice, size_t ByteCount ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpyDtoH_v2( void * dstHost, CUdeviceptr srcDevice, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstHost,(void **)&srcDevice,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyDtoH_v2, (void*) &ORIGINAL_cuMemcpyDtoH_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyDtoD_v2
extern int ORIGINAL_cuMemcpyDtoD_v2( CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpyDtoD_v2( CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&srcDevice,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyDtoD_v2, (void*) &ORIGINAL_cuMemcpyDtoD_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyDtoA_v2
extern int ORIGINAL_cuMemcpyDtoA_v2( CUarray dstArray, size_t dstOffset, CUdeviceptr srcDevice, size_t ByteCount ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpyDtoA_v2( CUarray dstArray, size_t dstOffset, CUdeviceptr srcDevice, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstArray,(void **)&dstOffset,(void **)&srcDevice,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyDtoA_v2, (void*) &ORIGINAL_cuMemcpyDtoA_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyAtoD_v2
extern int ORIGINAL_cuMemcpyAtoD_v2( CUdeviceptr dstDevice, CUarray srcArray, size_t srcOffset, size_t ByteCount ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpyAtoD_v2( CUdeviceptr dstDevice, CUarray srcArray, size_t srcOffset, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&srcArray,(void **)&srcOffset,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyAtoD_v2, (void*) &ORIGINAL_cuMemcpyAtoD_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyHtoA_v2
extern int ORIGINAL_cuMemcpyHtoA_v2( CUarray dstArray, size_t dstOffset, const void * srcHost, size_t ByteCount ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpyHtoA_v2( CUarray dstArray, size_t dstOffset, const void * srcHost, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstArray,(void **)&dstOffset,(void **)&srcHost,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyHtoA_v2, (void*) &ORIGINAL_cuMemcpyHtoA_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyAtoH_v2
extern int ORIGINAL_cuMemcpyAtoH_v2( void * dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpyAtoH_v2( void * dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstHost,(void **)&srcArray,(void **)&srcOffset,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyAtoH_v2, (void*) &ORIGINAL_cuMemcpyAtoH_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyAtoA_v2
extern int ORIGINAL_cuMemcpyAtoA_v2( CUarray dstArray, size_t dstOffset, CUarray srcArray, size_t srcOffset, size_t ByteCount ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpyAtoA_v2( CUarray dstArray, size_t dstOffset, CUarray srcArray, size_t srcOffset, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstArray,(void **)&dstOffset,(void **)&srcArray,(void **)&srcOffset,(void **)&ByteCount };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyAtoA_v2, (void*) &ORIGINAL_cuMemcpyAtoA_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyHtoAAsync_v2
extern int ORIGINAL_cuMemcpyHtoAAsync_v2( CUarray dstArray, size_t dstOffset, const void * srcHost, size_t ByteCount, CUstream hStream ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpyHtoAAsync_v2( CUarray dstArray, size_t dstOffset, const void * srcHost, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	
	std::vector<void **> params = { (void **)&dstArray,(void **)&dstOffset,(void **)&srcHost,(void **)&ByteCount,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyHtoAAsync_v2, (void*) &ORIGINAL_cuMemcpyHtoAAsync_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyAtoHAsync_v2
extern int ORIGINAL_cuMemcpyAtoHAsync_v2( void * dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount, CUstream hStream ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpyAtoHAsync_v2( void * dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstHost,(void **)&srcArray,(void **)&srcOffset,(void **)&ByteCount,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyAtoHAsync_v2, (void*) &ORIGINAL_cuMemcpyAtoHAsync_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpy2D_v2
extern int ORIGINAL_cuMemcpy2D_v2( const CUDA_MEMCPY2D * pCopy ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpy2D_v2( const CUDA_MEMCPY2D * pCopy ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pCopy };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpy2D_v2, (void*) &ORIGINAL_cuMemcpy2D_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpy2DUnaligned_v2
extern int ORIGINAL_cuMemcpy2DUnaligned_v2( const CUDA_MEMCPY2D * pCopy ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpy2DUnaligned_v2( const CUDA_MEMCPY2D * pCopy ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pCopy };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpy2DUnaligned_v2, (void*) &ORIGINAL_cuMemcpy2DUnaligned_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpy3D_v2
extern int ORIGINAL_cuMemcpy3D_v2( const CUDA_MEMCPY3D * pCopy ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpy3D_v2( const CUDA_MEMCPY3D * pCopy ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pCopy };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpy3D_v2, (void*) &ORIGINAL_cuMemcpy3D_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyHtoDAsync_v2
extern int ORIGINAL_cuMemcpyHtoDAsync_v2( CUdeviceptr dstDevice, const void * srcHost, size_t ByteCount, CUstream hStream ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpyHtoDAsync_v2( CUdeviceptr dstDevice, const void * srcHost, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&srcHost,(void **)&ByteCount,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyHtoDAsync_v2, (void*) &ORIGINAL_cuMemcpyHtoDAsync_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyDtoHAsync_v2
extern int ORIGINAL_cuMemcpyDtoHAsync_v2( void * dstHost, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpyDtoHAsync_v2( void * dstHost, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	
	std::vector<void **> params = { (void **)&dstHost,(void **)&srcDevice,(void **)&ByteCount,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyDtoHAsync_v2, (void*) &ORIGINAL_cuMemcpyDtoHAsync_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpyDtoDAsync_v2
extern int ORIGINAL_cuMemcpyDtoDAsync_v2( CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpyDtoDAsync_v2( CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&srcDevice,(void **)&ByteCount,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpyDtoDAsync_v2, (void*) &ORIGINAL_cuMemcpyDtoDAsync_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpy2DAsync_v2
extern int ORIGINAL_cuMemcpy2DAsync_v2( const CUDA_MEMCPY2D * pCopy, CUstream hStream ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpy2DAsync_v2( const CUDA_MEMCPY2D * pCopy, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pCopy,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpy2DAsync_v2, (void*) &ORIGINAL_cuMemcpy2DAsync_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemcpy3DAsync_v2
extern int ORIGINAL_cuMemcpy3DAsync_v2( const CUDA_MEMCPY3D * pCopy, CUstream hStream ) ;

// This is the call that will take the place of the original
int INTER_cuMemcpy3DAsync_v2( const CUDA_MEMCPY3D * pCopy, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&pCopy,(void **)&hStream };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemcpy3DAsync_v2, (void*) &ORIGINAL_cuMemcpy3DAsync_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD8_v2
extern int ORIGINAL_cuMemsetD8_v2( CUdeviceptr dstDevice, unsigned char uc, size_t N ) ;

// This is the call that will take the place of the original
int INTER_cuMemsetD8_v2( CUdeviceptr dstDevice, unsigned char uc, size_t N ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&uc,(void **)&N };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD8_v2, (void*) &ORIGINAL_cuMemsetD8_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD16_v2
extern int ORIGINAL_cuMemsetD16_v2( CUdeviceptr dstDevice, unsigned short us, size_t N ) ;

// This is the call that will take the place of the original
int INTER_cuMemsetD16_v2( CUdeviceptr dstDevice, unsigned short us, size_t N ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&us,(void **)&N };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD16_v2, (void*) &ORIGINAL_cuMemsetD16_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD32_v2
extern int ORIGINAL_cuMemsetD32_v2( CUdeviceptr dstDevice, unsigned int ui, size_t N ) ;

// This is the call that will take the place of the original
int INTER_cuMemsetD32_v2( CUdeviceptr dstDevice, unsigned int ui, size_t N ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&ui,(void **)&N };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD32_v2, (void*) &ORIGINAL_cuMemsetD32_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD2D8_v2
extern int ORIGINAL_cuMemsetD2D8_v2( CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height ) ;

// This is the call that will take the place of the original
int INTER_cuMemsetD2D8_v2( CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&dstPitch,(void **)&uc,(void **)&Width,(void **)&Height };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD2D8_v2, (void*) &ORIGINAL_cuMemsetD2D8_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD2D16_v2
extern int ORIGINAL_cuMemsetD2D16_v2( CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height ) ;

// This is the call that will take the place of the original
int INTER_cuMemsetD2D16_v2( CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&dstPitch,(void **)&us,(void **)&Width,(void **)&Height };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD2D16_v2, (void*) &ORIGINAL_cuMemsetD2D16_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}
// This "function" will be rewritten to point to cuMemsetD2D32_v2
extern int ORIGINAL_cuMemsetD2D32_v2( CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height ) ;

// This is the call that will take the place of the original
int INTER_cuMemsetD2D32_v2( CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void **> params = { (void **)&dstDevice,(void **)&dstPitch,(void **)&ui,(void **)&Width,(void **)&Height };
	std::shared_ptr<Parameters> paramsPtr(new Parameters(ID_cuMemsetD2D32_v2, (void*) &ORIGINAL_cuMemsetD2D32_v2, params));
	int ret = ( int ) FACTORY_PTR->PerformAction(paramsPtr);
	return ret;
}

}

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
	//MANUALLY ADDED
	Bound_InternalSynchronization = std::bind(&ORIGINAL_InternalSynchronization,std::placeholders::_1,std::placeholders::_2, std::placeholders::_3);
	//
	//
	void * handle = dlopen("libcuda.so.1", RTLD_LAZY);

	Bound_cuInit = std::bind(&ORIGINAL_cuInit,std::placeholders::_1);
	Bound_cuGetErrorString = std::bind(&ORIGINAL_cuGetErrorString,std::placeholders::_1,std::placeholders::_2);
	Bound_cuGetErrorName = std::bind(&ORIGINAL_cuGetErrorName,std::placeholders::_1,std::placeholders::_2);
	Bound_cuInit = std::bind(&ORIGINAL_cuInit,std::placeholders::_1);


	//Bound_cuDriverGetVersion = std::bind(&ORIGINAL_cuDriverGetVersion,std::placeholders::_1);
	Bound_cuDriverGetVersion = std::bind((int(int *))dlsym(handle, "cuDriverGetVersion_dyninst"),std::placeholders::_1);
	Bound_cuDeviceGet = std::bind(&ORIGINAL_cuDeviceGet,std::placeholders::_1,std::placeholders::_2);
	Bound_cuDeviceGetCount = std::bind(&ORIGINAL_cuDeviceGetCount,std::placeholders::_1);
	Bound_cuDeviceGetName = std::bind(&ORIGINAL_cuDeviceGetName,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuDeviceTotalMem = std::bind(&ORIGINAL_cuDeviceTotalMem,std::placeholders::_1,std::placeholders::_2);
	Bound_cuDeviceGetAttribute = std::bind(&ORIGINAL_cuDeviceGetAttribute,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuDeviceGetProperties = std::bind(&ORIGINAL_cuDeviceGetProperties,std::placeholders::_1,std::placeholders::_2);
	Bound_cuDeviceComputeCapability = std::bind(&ORIGINAL_cuDeviceComputeCapability,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuDevicePrimaryCtxRetain = std::bind(&ORIGINAL_cuDevicePrimaryCtxRetain,std::placeholders::_1,std::placeholders::_2);
	Bound_cuDevicePrimaryCtxRelease = std::bind(&ORIGINAL_cuDevicePrimaryCtxRelease,std::placeholders::_1);
	Bound_cuDevicePrimaryCtxSetFlags = std::bind(&ORIGINAL_cuDevicePrimaryCtxSetFlags,std::placeholders::_1,std::placeholders::_2);
	Bound_cuDevicePrimaryCtxGetState = std::bind(&ORIGINAL_cuDevicePrimaryCtxGetState,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuDevicePrimaryCtxReset = std::bind(&ORIGINAL_cuDevicePrimaryCtxReset,std::placeholders::_1);
	Bound_cuCtxCreate = std::bind(&ORIGINAL_cuCtxCreate,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuCtxDestroy = std::bind(&ORIGINAL_cuCtxDestroy,std::placeholders::_1);
	Bound_cuCtxPushCurrent = std::bind(&ORIGINAL_cuCtxPushCurrent,std::placeholders::_1);
	Bound_cuCtxPopCurrent = std::bind(&ORIGINAL_cuCtxPopCurrent,std::placeholders::_1);
	Bound_cuCtxSetCurrent = std::bind(&ORIGINAL_cuCtxSetCurrent,std::placeholders::_1);
	Bound_cuCtxGetCurrent = std::bind(&ORIGINAL_cuCtxGetCurrent,std::placeholders::_1);
	Bound_cuCtxGetDevice = std::bind(&ORIGINAL_cuCtxGetDevice,std::placeholders::_1);
	Bound_cuCtxGetFlags = std::bind(&ORIGINAL_cuCtxGetFlags,std::placeholders::_1);
	Bound_cuCtxSynchronize = std::bind(&ORIGINAL_cuCtxSynchronize);
	Bound_cuCtxSetLimit = std::bind(&ORIGINAL_cuCtxSetLimit,std::placeholders::_1,std::placeholders::_2);
	Bound_cuCtxGetLimit = std::bind(&ORIGINAL_cuCtxGetLimit,std::placeholders::_1,std::placeholders::_2);
	Bound_cuCtxGetCacheConfig = std::bind(&ORIGINAL_cuCtxGetCacheConfig,std::placeholders::_1);
	Bound_cuCtxSetCacheConfig = std::bind(&ORIGINAL_cuCtxSetCacheConfig,std::placeholders::_1);
	Bound_cuCtxGetSharedMemConfig = std::bind(&ORIGINAL_cuCtxGetSharedMemConfig,std::placeholders::_1);
	Bound_cuCtxSetSharedMemConfig = std::bind(&ORIGINAL_cuCtxSetSharedMemConfig,std::placeholders::_1);
	Bound_cuCtxGetApiVersion = std::bind(&ORIGINAL_cuCtxGetApiVersion,std::placeholders::_1,std::placeholders::_2);
	Bound_cuCtxGetStreamPriorityRange = std::bind(&ORIGINAL_cuCtxGetStreamPriorityRange,std::placeholders::_1,std::placeholders::_2);
	Bound_cuCtxAttach = std::bind(&ORIGINAL_cuCtxAttach,std::placeholders::_1,std::placeholders::_2);
	Bound_cuCtxDetach = std::bind(&ORIGINAL_cuCtxDetach,std::placeholders::_1);
	Bound_cuModuleLoad = std::bind(&ORIGINAL_cuModuleLoad,std::placeholders::_1,std::placeholders::_2);
	Bound_cuModuleLoadData = std::bind(&ORIGINAL_cuModuleLoadData,std::placeholders::_1,std::placeholders::_2);
	Bound_cuModuleLoadDataEx = std::bind(&ORIGINAL_cuModuleLoadDataEx,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
	Bound_cuModuleLoadFatBinary = std::bind(&ORIGINAL_cuModuleLoadFatBinary,std::placeholders::_1,std::placeholders::_2);
	Bound_cuModuleUnload = std::bind(&ORIGINAL_cuModuleUnload,std::placeholders::_1);
	Bound_cuModuleGetFunction = std::bind(&ORIGINAL_cuModuleGetFunction,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuModuleGetGlobal = std::bind(&ORIGINAL_cuModuleGetGlobal,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuModuleGetTexRef = std::bind(&ORIGINAL_cuModuleGetTexRef,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuModuleGetSurfRef = std::bind(&ORIGINAL_cuModuleGetSurfRef,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuLinkCreate = std::bind(&ORIGINAL_cuLinkCreate,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuLinkAddData = std::bind(&ORIGINAL_cuLinkAddData,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5,std::placeholders::_6,std::placeholders::_7,std::placeholders::_8);
	Bound_cuLinkAddFile = std::bind(&ORIGINAL_cuLinkAddFile,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5,std::placeholders::_6);
	Bound_cuLinkComplete = std::bind(&ORIGINAL_cuLinkComplete,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuLinkDestroy = std::bind(&ORIGINAL_cuLinkDestroy,std::placeholders::_1);
	Bound_cuMemGetInfo = std::bind(&ORIGINAL_cuMemGetInfo,std::placeholders::_1,std::placeholders::_2);
	Bound_cuMemAlloc = std::bind(&ORIGINAL_cuMemAlloc,std::placeholders::_1,std::placeholders::_2);
	Bound_cuMemAllocPitch = std::bind(&ORIGINAL_cuMemAllocPitch,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
	Bound_cuMemFree = std::bind(&ORIGINAL_cuMemFree,std::placeholders::_1);
	Bound_cuMemGetAddressRange = std::bind(&ORIGINAL_cuMemGetAddressRange,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuMemAllocHost = std::bind(&ORIGINAL_cuMemAllocHost,std::placeholders::_1,std::placeholders::_2);
	Bound_cuMemFreeHost = std::bind(&ORIGINAL_cuMemFreeHost,std::placeholders::_1);
	Bound_cuMemHostAlloc = std::bind(&ORIGINAL_cuMemHostAlloc,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuMemHostGetDevicePointer = std::bind(&ORIGINAL_cuMemHostGetDevicePointer,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuMemHostGetFlags = std::bind(&ORIGINAL_cuMemHostGetFlags,std::placeholders::_1,std::placeholders::_2);
	Bound_cuMemAllocManaged = std::bind(&ORIGINAL_cuMemAllocManaged,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuDeviceGetByPCIBusId = std::bind(&ORIGINAL_cuDeviceGetByPCIBusId,std::placeholders::_1,std::placeholders::_2);
	Bound_cuDeviceGetPCIBusId = std::bind(&ORIGINAL_cuDeviceGetPCIBusId,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuIpcGetEventHandle = std::bind(&ORIGINAL_cuIpcGetEventHandle,std::placeholders::_1,std::placeholders::_2);
	Bound_cuIpcOpenEventHandle = std::bind(&ORIGINAL_cuIpcOpenEventHandle,std::placeholders::_1,std::placeholders::_2);
	Bound_cuIpcGetMemHandle = std::bind(&ORIGINAL_cuIpcGetMemHandle,std::placeholders::_1,std::placeholders::_2);
	Bound_cuIpcOpenMemHandle = std::bind(&ORIGINAL_cuIpcOpenMemHandle,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuIpcCloseMemHandle = std::bind(&ORIGINAL_cuIpcCloseMemHandle,std::placeholders::_1);
	Bound_cuMemHostRegister = std::bind(&ORIGINAL_cuMemHostRegister,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuMemHostUnregister = std::bind(&ORIGINAL_cuMemHostUnregister,std::placeholders::_1);
	Bound_cuMemcpy = std::bind(&ORIGINAL_cuMemcpy,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuMemcpyPeer = std::bind(&ORIGINAL_cuMemcpyPeer,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
	Bound_cuMemcpyHtoD = std::bind(&ORIGINAL_cuMemcpyHtoD,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuMemcpyDtoH = std::bind(&ORIGINAL_cuMemcpyDtoH,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuMemcpyDtoD = std::bind(&ORIGINAL_cuMemcpyDtoD,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuMemcpyDtoA = std::bind(&ORIGINAL_cuMemcpyDtoA,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuMemcpyAtoD = std::bind(&ORIGINAL_cuMemcpyAtoD,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuMemcpyHtoA = std::bind(&ORIGINAL_cuMemcpyHtoA,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuMemcpyAtoH = std::bind(&ORIGINAL_cuMemcpyAtoH,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuMemcpyAtoA = std::bind(&ORIGINAL_cuMemcpyAtoA,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
	Bound_cuMemcpy2D = std::bind(&ORIGINAL_cuMemcpy2D,std::placeholders::_1);
	Bound_cuMemcpy2DUnaligned = std::bind(&ORIGINAL_cuMemcpy2DUnaligned,std::placeholders::_1);
	Bound_cuMemcpy3D = std::bind(&ORIGINAL_cuMemcpy3D,std::placeholders::_1);
	Bound_cuMemcpy3DPeer = std::bind(&ORIGINAL_cuMemcpy3DPeer,std::placeholders::_1);
	Bound_cuMemcpyAsync = std::bind(&ORIGINAL_cuMemcpyAsync,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuMemcpyPeerAsync = std::bind(&ORIGINAL_cuMemcpyPeerAsync,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5,std::placeholders::_6);
	Bound_cuMemcpyHtoDAsync = std::bind(&ORIGINAL_cuMemcpyHtoDAsync,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuMemcpyDtoHAsync = std::bind(&ORIGINAL_cuMemcpyDtoHAsync,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuMemcpyDtoDAsync = std::bind(&ORIGINAL_cuMemcpyDtoDAsync,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuMemcpyHtoAAsync = std::bind(&ORIGINAL_cuMemcpyHtoAAsync,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
	Bound_cuMemcpyAtoHAsync = std::bind(&ORIGINAL_cuMemcpyAtoHAsync,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
	Bound_cuMemcpy2DAsync = std::bind(&ORIGINAL_cuMemcpy2DAsync,std::placeholders::_1,std::placeholders::_2);
	Bound_cuMemcpy3DAsync = std::bind(&ORIGINAL_cuMemcpy3DAsync,std::placeholders::_1,std::placeholders::_2);
	Bound_cuMemcpy3DPeerAsync = std::bind(&ORIGINAL_cuMemcpy3DPeerAsync,std::placeholders::_1,std::placeholders::_2);
	Bound_cuMemsetD8 = std::bind(&ORIGINAL_cuMemsetD8,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuMemsetD16 = std::bind(&ORIGINAL_cuMemsetD16,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuMemsetD32 = std::bind(&ORIGINAL_cuMemsetD32,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuMemsetD2D8 = std::bind(&ORIGINAL_cuMemsetD2D8,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
	Bound_cuMemsetD2D16 = std::bind(&ORIGINAL_cuMemsetD2D16,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
	Bound_cuMemsetD2D32 = std::bind(&ORIGINAL_cuMemsetD2D32,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
	Bound_cuMemsetD8Async = std::bind(&ORIGINAL_cuMemsetD8Async,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuMemsetD16Async = std::bind(&ORIGINAL_cuMemsetD16Async,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuMemsetD32Async = std::bind(&ORIGINAL_cuMemsetD32Async,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuMemsetD2D8Async = std::bind(&ORIGINAL_cuMemsetD2D8Async,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5,std::placeholders::_6);
	Bound_cuMemsetD2D16Async = std::bind(&ORIGINAL_cuMemsetD2D16Async,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5,std::placeholders::_6);
	Bound_cuMemsetD2D32Async = std::bind(&ORIGINAL_cuMemsetD2D32Async,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5,std::placeholders::_6);
	Bound_cuArrayCreate = std::bind(&ORIGINAL_cuArrayCreate,std::placeholders::_1,std::placeholders::_2);
	Bound_cuArrayGetDescriptor = std::bind(&ORIGINAL_cuArrayGetDescriptor,std::placeholders::_1,std::placeholders::_2);
	Bound_cuArrayDestroy = std::bind(&ORIGINAL_cuArrayDestroy,std::placeholders::_1);
	Bound_cuArray3DCreate = std::bind(&ORIGINAL_cuArray3DCreate,std::placeholders::_1,std::placeholders::_2);
	Bound_cuArray3DGetDescriptor = std::bind(&ORIGINAL_cuArray3DGetDescriptor,std::placeholders::_1,std::placeholders::_2);
	Bound_cuMipmappedArrayCreate = std::bind(&ORIGINAL_cuMipmappedArrayCreate,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuMipmappedArrayGetLevel = std::bind(&ORIGINAL_cuMipmappedArrayGetLevel,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuMipmappedArrayDestroy = std::bind(&ORIGINAL_cuMipmappedArrayDestroy,std::placeholders::_1);
	Bound_cuPointerGetAttribute = std::bind(&ORIGINAL_cuPointerGetAttribute,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuMemPrefetchAsync = std::bind(&ORIGINAL_cuMemPrefetchAsync,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuMemAdvise = std::bind(&ORIGINAL_cuMemAdvise,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuMemRangeGetAttribute = std::bind(&ORIGINAL_cuMemRangeGetAttribute,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
	Bound_cuMemRangeGetAttributes = std::bind(&ORIGINAL_cuMemRangeGetAttributes,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5,std::placeholders::_6);
	Bound_cuPointerSetAttribute = std::bind(&ORIGINAL_cuPointerSetAttribute,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuPointerGetAttributes = std::bind(&ORIGINAL_cuPointerGetAttributes,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuStreamCreate = std::bind(&ORIGINAL_cuStreamCreate,std::placeholders::_1,std::placeholders::_2);
	Bound_cuStreamCreateWithPriority = std::bind(&ORIGINAL_cuStreamCreateWithPriority,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuStreamGetPriority = std::bind(&ORIGINAL_cuStreamGetPriority,std::placeholders::_1,std::placeholders::_2);
	Bound_cuStreamGetFlags = std::bind(&ORIGINAL_cuStreamGetFlags,std::placeholders::_1,std::placeholders::_2);
	Bound_cuStreamWaitEvent = std::bind(&ORIGINAL_cuStreamWaitEvent,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuStreamAddCallback = std::bind(&ORIGINAL_cuStreamAddCallback,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuStreamAttachMemAsync = std::bind(&ORIGINAL_cuStreamAttachMemAsync,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuStreamQuery = std::bind(&ORIGINAL_cuStreamQuery,std::placeholders::_1);
	Bound_cuStreamSynchronize = std::bind(&ORIGINAL_cuStreamSynchronize,std::placeholders::_1);
	Bound_cuStreamDestroy = std::bind(&ORIGINAL_cuStreamDestroy,std::placeholders::_1);
	Bound_cuEventCreate = std::bind(&ORIGINAL_cuEventCreate,std::placeholders::_1,std::placeholders::_2);
	Bound_cuEventRecord = std::bind(&ORIGINAL_cuEventRecord,std::placeholders::_1,std::placeholders::_2);
	Bound_cuEventQuery = std::bind(&ORIGINAL_cuEventQuery,std::placeholders::_1);
	Bound_cuEventSynchronize = std::bind(&ORIGINAL_cuEventSynchronize,std::placeholders::_1);
	Bound_cuEventDestroy = std::bind(&ORIGINAL_cuEventDestroy,std::placeholders::_1);
	Bound_cuEventElapsedTime = std::bind(&ORIGINAL_cuEventElapsedTime,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuStreamWaitValue32 = std::bind(&ORIGINAL_cuStreamWaitValue32,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuStreamWriteValue32 = std::bind(&ORIGINAL_cuStreamWriteValue32,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuStreamBatchMemOp = std::bind(&ORIGINAL_cuStreamBatchMemOp,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuFuncGetAttribute = std::bind(&ORIGINAL_cuFuncGetAttribute,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuFuncSetCacheConfig = std::bind(&ORIGINAL_cuFuncSetCacheConfig,std::placeholders::_1,std::placeholders::_2);
	Bound_cuFuncSetSharedMemConfig = std::bind(&ORIGINAL_cuFuncSetSharedMemConfig,std::placeholders::_1,std::placeholders::_2);
	Bound_cuLaunchKernel = std::bind(&ORIGINAL_cuLaunchKernel,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5,std::placeholders::_6,std::placeholders::_7,std::placeholders::_8,std::placeholders::_9,std::placeholders::_10,std::placeholders::_11);
	Bound_cuFuncSetBlockShape = std::bind(&ORIGINAL_cuFuncSetBlockShape,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuFuncSetSharedSize = std::bind(&ORIGINAL_cuFuncSetSharedSize,std::placeholders::_1,std::placeholders::_2);
	Bound_cuParamSetSize = std::bind(&ORIGINAL_cuParamSetSize,std::placeholders::_1,std::placeholders::_2);
	Bound_cuParamSeti = std::bind(&ORIGINAL_cuParamSeti,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuParamSetf = std::bind(&ORIGINAL_cuParamSetf,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuParamSetv = std::bind(&ORIGINAL_cuParamSetv,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuLaunch = std::bind(&ORIGINAL_cuLaunch,std::placeholders::_1);
	Bound_cuLaunchGrid = std::bind(&ORIGINAL_cuLaunchGrid,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuLaunchGridAsync = std::bind(&ORIGINAL_cuLaunchGridAsync,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuParamSetTexRef = std::bind(&ORIGINAL_cuParamSetTexRef,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuOccupancyMaxActiveBlocksPerMultiprocessor = std::bind(&ORIGINAL_cuOccupancyMaxActiveBlocksPerMultiprocessor,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags = std::bind(&ORIGINAL_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
	Bound_cuOccupancyMaxPotentialBlockSize = std::bind(&ORIGINAL_cuOccupancyMaxPotentialBlockSize,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5,std::placeholders::_6);
	Bound_cuOccupancyMaxPotentialBlockSizeWithFlags = std::bind(&ORIGINAL_cuOccupancyMaxPotentialBlockSizeWithFlags,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5,std::placeholders::_6,std::placeholders::_7);
	Bound_cuTexRefSetArray = std::bind(&ORIGINAL_cuTexRefSetArray,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuTexRefSetMipmappedArray = std::bind(&ORIGINAL_cuTexRefSetMipmappedArray,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuTexRefSetAddress = std::bind(&ORIGINAL_cuTexRefSetAddress,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuTexRefSetAddress2D = std::bind(&ORIGINAL_cuTexRefSetAddress2D,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuTexRefSetFormat = std::bind(&ORIGINAL_cuTexRefSetFormat,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuTexRefSetAddressMode = std::bind(&ORIGINAL_cuTexRefSetAddressMode,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuTexRefSetFilterMode = std::bind(&ORIGINAL_cuTexRefSetFilterMode,std::placeholders::_1,std::placeholders::_2);
	Bound_cuTexRefSetMipmapFilterMode = std::bind(&ORIGINAL_cuTexRefSetMipmapFilterMode,std::placeholders::_1,std::placeholders::_2);
	Bound_cuTexRefSetMipmapLevelBias = std::bind(&ORIGINAL_cuTexRefSetMipmapLevelBias,std::placeholders::_1,std::placeholders::_2);
	Bound_cuTexRefSetMipmapLevelClamp = std::bind(&ORIGINAL_cuTexRefSetMipmapLevelClamp,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuTexRefSetMaxAnisotropy = std::bind(&ORIGINAL_cuTexRefSetMaxAnisotropy,std::placeholders::_1,std::placeholders::_2);
	Bound_cuTexRefSetBorderColor = std::bind(&ORIGINAL_cuTexRefSetBorderColor,std::placeholders::_1,std::placeholders::_2);
	Bound_cuTexRefSetFlags = std::bind(&ORIGINAL_cuTexRefSetFlags,std::placeholders::_1,std::placeholders::_2);
	Bound_cuTexRefGetAddress = std::bind(&ORIGINAL_cuTexRefGetAddress,std::placeholders::_1,std::placeholders::_2);
	Bound_cuTexRefGetArray = std::bind(&ORIGINAL_cuTexRefGetArray,std::placeholders::_1,std::placeholders::_2);
	Bound_cuTexRefGetMipmappedArray = std::bind(&ORIGINAL_cuTexRefGetMipmappedArray,std::placeholders::_1,std::placeholders::_2);
	Bound_cuTexRefGetAddressMode = std::bind(&ORIGINAL_cuTexRefGetAddressMode,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuTexRefGetFilterMode = std::bind(&ORIGINAL_cuTexRefGetFilterMode,std::placeholders::_1,std::placeholders::_2);
	Bound_cuTexRefGetFormat = std::bind(&ORIGINAL_cuTexRefGetFormat,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuTexRefGetMipmapFilterMode = std::bind(&ORIGINAL_cuTexRefGetMipmapFilterMode,std::placeholders::_1,std::placeholders::_2);
	Bound_cuTexRefGetMipmapLevelBias = std::bind(&ORIGINAL_cuTexRefGetMipmapLevelBias,std::placeholders::_1,std::placeholders::_2);
	Bound_cuTexRefGetMipmapLevelClamp = std::bind(&ORIGINAL_cuTexRefGetMipmapLevelClamp,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuTexRefGetMaxAnisotropy = std::bind(&ORIGINAL_cuTexRefGetMaxAnisotropy,std::placeholders::_1,std::placeholders::_2);
	Bound_cuTexRefGetBorderColor = std::bind(&ORIGINAL_cuTexRefGetBorderColor,std::placeholders::_1,std::placeholders::_2);
	Bound_cuTexRefGetFlags = std::bind(&ORIGINAL_cuTexRefGetFlags,std::placeholders::_1,std::placeholders::_2);
	Bound_cuTexRefCreate = std::bind(&ORIGINAL_cuTexRefCreate,std::placeholders::_1);
	Bound_cuTexRefDestroy = std::bind(&ORIGINAL_cuTexRefDestroy,std::placeholders::_1);
	Bound_cuSurfRefSetArray = std::bind(&ORIGINAL_cuSurfRefSetArray,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuSurfRefGetArray = std::bind(&ORIGINAL_cuSurfRefGetArray,std::placeholders::_1,std::placeholders::_2);
	Bound_cuTexObjectCreate = std::bind(&ORIGINAL_cuTexObjectCreate,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuTexObjectDestroy = std::bind(&ORIGINAL_cuTexObjectDestroy,std::placeholders::_1);
	Bound_cuTexObjectGetResourceDesc = std::bind(&ORIGINAL_cuTexObjectGetResourceDesc,std::placeholders::_1,std::placeholders::_2);
	Bound_cuTexObjectGetTextureDesc = std::bind(&ORIGINAL_cuTexObjectGetTextureDesc,std::placeholders::_1,std::placeholders::_2);
	Bound_cuTexObjectGetResourceViewDesc = std::bind(&ORIGINAL_cuTexObjectGetResourceViewDesc,std::placeholders::_1,std::placeholders::_2);
	Bound_cuSurfObjectCreate = std::bind(&ORIGINAL_cuSurfObjectCreate,std::placeholders::_1,std::placeholders::_2);
	Bound_cuSurfObjectDestroy = std::bind(&ORIGINAL_cuSurfObjectDestroy,std::placeholders::_1);
	Bound_cuSurfObjectGetResourceDesc = std::bind(&ORIGINAL_cuSurfObjectGetResourceDesc,std::placeholders::_1,std::placeholders::_2);
	Bound_cuDeviceCanAccessPeer = std::bind(&ORIGINAL_cuDeviceCanAccessPeer,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuDeviceGetP2PAttribute = std::bind(&ORIGINAL_cuDeviceGetP2PAttribute,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuCtxEnablePeerAccess = std::bind(&ORIGINAL_cuCtxEnablePeerAccess,std::placeholders::_1,std::placeholders::_2);
	Bound_cuCtxDisablePeerAccess = std::bind(&ORIGINAL_cuCtxDisablePeerAccess,std::placeholders::_1);
	Bound_cuGraphicsUnregisterResource = std::bind(&ORIGINAL_cuGraphicsUnregisterResource,std::placeholders::_1);
	Bound_cuGraphicsSubResourceGetMappedArray = std::bind(&ORIGINAL_cuGraphicsSubResourceGetMappedArray,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuGraphicsResourceGetMappedMipmappedArray = std::bind(&ORIGINAL_cuGraphicsResourceGetMappedMipmappedArray,std::placeholders::_1,std::placeholders::_2);
	Bound_cuGraphicsResourceGetMappedPointer = std::bind(&ORIGINAL_cuGraphicsResourceGetMappedPointer,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuGraphicsResourceSetMapFlags = std::bind(&ORIGINAL_cuGraphicsResourceSetMapFlags,std::placeholders::_1,std::placeholders::_2);
	Bound_cuGraphicsMapResources = std::bind(&ORIGINAL_cuGraphicsMapResources,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuGraphicsUnmapResources = std::bind(&ORIGINAL_cuGraphicsUnmapResources,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuGetExportTable = std::bind(&ORIGINAL_cuGetExportTable,std::placeholders::_1,std::placeholders::_2);
	Bound_cuTexRefSetAddress2D_v2 = std::bind(&ORIGINAL_cuTexRefSetAddress2D_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuMemcpyHtoD_v2 = std::bind(&ORIGINAL_cuMemcpyHtoD_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuMemcpyDtoH_v2 = std::bind(&ORIGINAL_cuMemcpyDtoH_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuMemcpyDtoD_v2 = std::bind(&ORIGINAL_cuMemcpyDtoD_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuMemcpyDtoA_v2 = std::bind(&ORIGINAL_cuMemcpyDtoA_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuMemcpyAtoD_v2 = std::bind(&ORIGINAL_cuMemcpyAtoD_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuMemcpyHtoA_v2 = std::bind(&ORIGINAL_cuMemcpyHtoA_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuMemcpyAtoH_v2 = std::bind(&ORIGINAL_cuMemcpyAtoH_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuMemcpyAtoA_v2 = std::bind(&ORIGINAL_cuMemcpyAtoA_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
	Bound_cuMemcpyHtoAAsync_v2 = std::bind(&ORIGINAL_cuMemcpyHtoAAsync_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
	Bound_cuMemcpyAtoHAsync_v2 = std::bind(&ORIGINAL_cuMemcpyAtoHAsync_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
	Bound_cuMemcpy2D_v2 = std::bind(&ORIGINAL_cuMemcpy2D_v2,std::placeholders::_1);
	Bound_cuMemcpy2DUnaligned_v2 = std::bind(&ORIGINAL_cuMemcpy2DUnaligned_v2,std::placeholders::_1);
	Bound_cuMemcpy3D_v2 = std::bind(&ORIGINAL_cuMemcpy3D_v2,std::placeholders::_1);
	Bound_cuMemcpyHtoDAsync_v2 = std::bind(&ORIGINAL_cuMemcpyHtoDAsync_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuMemcpyDtoHAsync_v2 = std::bind(&ORIGINAL_cuMemcpyDtoHAsync_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuMemcpyDtoDAsync_v2 = std::bind(&ORIGINAL_cuMemcpyDtoDAsync_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
	Bound_cuMemcpy2DAsync_v2 = std::bind(&ORIGINAL_cuMemcpy2DAsync_v2,std::placeholders::_1,std::placeholders::_2);
	Bound_cuMemcpy3DAsync_v2 = std::bind(&ORIGINAL_cuMemcpy3DAsync_v2,std::placeholders::_1,std::placeholders::_2);
	Bound_cuMemsetD8_v2 = std::bind(&ORIGINAL_cuMemsetD8_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuMemsetD16_v2 = std::bind(&ORIGINAL_cuMemsetD16_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuMemsetD32_v2 = std::bind(&ORIGINAL_cuMemsetD32_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
	Bound_cuMemsetD2D8_v2 = std::bind(&ORIGINAL_cuMemsetD2D8_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
	Bound_cuMemsetD2D16_v2 = std::bind(&ORIGINAL_cuMemsetD2D16_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
	Bound_cuMemsetD2D32_v2 = std::bind(&ORIGINAL_cuMemsetD2D32_v2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);

}
