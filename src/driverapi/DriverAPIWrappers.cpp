#include "DriverAPIHeader.h"
#include <tuple>
#include "DriverWrapperBase.h"
#include "DriverWrapperFactory.h"
#include "cuda.h"
std::shared_ptr<DriverWrapperFactory> DriverFactory;
extern "C" {// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuGetErrorString( CUresult error, const char * * pStr ) { }

// This is the call that will take the place of the original
int INTER_cuGetErrorString( CUresult error, const char * * pStr ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUresult,const char * *> params = std::make_tuple(0 ,error,pStr);
	DriverAPICall call = std::bind(ORIGINAL_cuGetErrorString ,error,pStr);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUresult,const char * *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuGetErrorName( CUresult error, const char * * pStr ) { }

// This is the call that will take the place of the original
int INTER_cuGetErrorName( CUresult error, const char * * pStr ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUresult,const char * *> params = std::make_tuple(1 ,error,pStr);
	DriverAPICall call = std::bind(ORIGINAL_cuGetErrorName ,error,pStr);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUresult,const char * *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuInit( unsigned int Flags ) { }

// This is the call that will take the place of the original
int INTER_cuInit( unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,unsigned int> params = std::make_tuple(2 ,Flags);
	DriverAPICall call = std::bind(ORIGINAL_cuInit ,Flags);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,unsigned int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuDriverGetVersion( int * driverVersion ) { }

// This is the call that will take the place of the original
int INTER_cuDriverGetVersion( int * driverVersion ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,int *> params = std::make_tuple(3 ,driverVersion);
	DriverAPICall call = std::bind(ORIGINAL_cuDriverGetVersion ,driverVersion);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,int *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuDeviceGet( CUdevice * device, int ordinal ) { }

// This is the call that will take the place of the original
int INTER_cuDeviceGet( CUdevice * device, int ordinal ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdevice *,int> params = std::make_tuple(4 ,device,ordinal);
	DriverAPICall call = std::bind(ORIGINAL_cuDeviceGet ,device,ordinal);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdevice *,int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuDeviceGetCount( int * count ) { }

// This is the call that will take the place of the original
int INTER_cuDeviceGetCount( int * count ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,int *> params = std::make_tuple(5 ,count);
	DriverAPICall call = std::bind(ORIGINAL_cuDeviceGetCount ,count);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,int *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuDeviceGetName( char * name, int len, CUdevice dev ) { }

// This is the call that will take the place of the original
int INTER_cuDeviceGetName( char * name, int len, CUdevice dev ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,char *,int,CUdevice> params = std::make_tuple(6 ,name,len,dev);
	DriverAPICall call = std::bind(ORIGINAL_cuDeviceGetName ,name,len,dev);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,char *,int,CUdevice> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuDeviceTotalMem( size_t * bytes, CUdevice dev ) { }

// This is the call that will take the place of the original
int INTER_cuDeviceTotalMem( size_t * bytes, CUdevice dev ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,size_t *,CUdevice> params = std::make_tuple(7 ,bytes,dev);
	DriverAPICall call = std::bind(ORIGINAL_cuDeviceTotalMem ,bytes,dev);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,size_t *,CUdevice> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuDeviceGetAttribute( int * pi, CUdevice_attribute attrib, CUdevice dev ) { }

// This is the call that will take the place of the original
int INTER_cuDeviceGetAttribute( int * pi, CUdevice_attribute attrib, CUdevice dev ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,int *,CUdevice_attribute,CUdevice> params = std::make_tuple(8 ,pi,attrib,dev);
	DriverAPICall call = std::bind(ORIGINAL_cuDeviceGetAttribute ,pi,attrib,dev);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,int *,CUdevice_attribute,CUdevice> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuDeviceGetProperties( CUdevprop * prop, CUdevice dev ) { }

// This is the call that will take the place of the original
int INTER_cuDeviceGetProperties( CUdevprop * prop, CUdevice dev ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdevprop *,CUdevice> params = std::make_tuple(9 ,prop,dev);
	DriverAPICall call = std::bind(ORIGINAL_cuDeviceGetProperties ,prop,dev);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdevprop *,CUdevice> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuDeviceComputeCapability( int * major, int * minor, CUdevice dev ) { }

// This is the call that will take the place of the original
int INTER_cuDeviceComputeCapability( int * major, int * minor, CUdevice dev ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,int *,int *,CUdevice> params = std::make_tuple(10 ,major,minor,dev);
	DriverAPICall call = std::bind(ORIGINAL_cuDeviceComputeCapability ,major,minor,dev);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,int *,int *,CUdevice> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuDevicePrimaryCtxRetain( CUcontext * pctx, CUdevice dev ) { }

// This is the call that will take the place of the original
int INTER_cuDevicePrimaryCtxRetain( CUcontext * pctx, CUdevice dev ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUcontext *,CUdevice> params = std::make_tuple(11 ,pctx,dev);
	DriverAPICall call = std::bind(ORIGINAL_cuDevicePrimaryCtxRetain ,pctx,dev);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUcontext *,CUdevice> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuDevicePrimaryCtxRelease( CUdevice dev ) { }

// This is the call that will take the place of the original
int INTER_cuDevicePrimaryCtxRelease( CUdevice dev ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdevice> params = std::make_tuple(12 ,dev);
	DriverAPICall call = std::bind(ORIGINAL_cuDevicePrimaryCtxRelease ,dev);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdevice> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuDevicePrimaryCtxSetFlags( CUdevice dev, unsigned int flags ) { }

// This is the call that will take the place of the original
int INTER_cuDevicePrimaryCtxSetFlags( CUdevice dev, unsigned int flags ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdevice,unsigned int> params = std::make_tuple(13 ,dev,flags);
	DriverAPICall call = std::bind(ORIGINAL_cuDevicePrimaryCtxSetFlags ,dev,flags);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdevice,unsigned int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuDevicePrimaryCtxGetState( CUdevice dev, unsigned int * flags, int * active ) { }

// This is the call that will take the place of the original
int INTER_cuDevicePrimaryCtxGetState( CUdevice dev, unsigned int * flags, int * active ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdevice,unsigned int *,int *> params = std::make_tuple(14 ,dev,flags,active);
	DriverAPICall call = std::bind(ORIGINAL_cuDevicePrimaryCtxGetState ,dev,flags,active);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdevice,unsigned int *,int *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuDevicePrimaryCtxReset( CUdevice dev ) { }

// This is the call that will take the place of the original
int INTER_cuDevicePrimaryCtxReset( CUdevice dev ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdevice> params = std::make_tuple(15 ,dev);
	DriverAPICall call = std::bind(ORIGINAL_cuDevicePrimaryCtxReset ,dev);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdevice> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuCtxCreate( CUcontext * pctx, unsigned int flags, CUdevice dev ) { }

// This is the call that will take the place of the original
int INTER_cuCtxCreate( CUcontext * pctx, unsigned int flags, CUdevice dev ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUcontext *,unsigned int,CUdevice> params = std::make_tuple(16 ,pctx,flags,dev);
	DriverAPICall call = std::bind(ORIGINAL_cuCtxCreate ,pctx,flags,dev);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUcontext *,unsigned int,CUdevice> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuCtxDestroy( CUcontext ctx ) { }

// This is the call that will take the place of the original
int INTER_cuCtxDestroy( CUcontext ctx ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUcontext> params = std::make_tuple(17 ,ctx);
	DriverAPICall call = std::bind(ORIGINAL_cuCtxDestroy ,ctx);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUcontext> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuCtxPushCurrent( CUcontext ctx ) { }

// This is the call that will take the place of the original
int INTER_cuCtxPushCurrent( CUcontext ctx ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUcontext> params = std::make_tuple(18 ,ctx);
	DriverAPICall call = std::bind(ORIGINAL_cuCtxPushCurrent ,ctx);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUcontext> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuCtxPopCurrent( CUcontext * pctx ) { }

// This is the call that will take the place of the original
int INTER_cuCtxPopCurrent( CUcontext * pctx ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUcontext *> params = std::make_tuple(19 ,pctx);
	DriverAPICall call = std::bind(ORIGINAL_cuCtxPopCurrent ,pctx);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUcontext *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuCtxSetCurrent( CUcontext ctx ) { }

// This is the call that will take the place of the original
int INTER_cuCtxSetCurrent( CUcontext ctx ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUcontext> params = std::make_tuple(20 ,ctx);
	DriverAPICall call = std::bind(ORIGINAL_cuCtxSetCurrent ,ctx);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUcontext> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuCtxGetCurrent( CUcontext * pctx ) { }

// This is the call that will take the place of the original
int INTER_cuCtxGetCurrent( CUcontext * pctx ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUcontext *> params = std::make_tuple(21 ,pctx);
	DriverAPICall call = std::bind(ORIGINAL_cuCtxGetCurrent ,pctx);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUcontext *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuCtxGetDevice( CUdevice * device ) { }

// This is the call that will take the place of the original
int INTER_cuCtxGetDevice( CUdevice * device ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdevice *> params = std::make_tuple(22 ,device);
	DriverAPICall call = std::bind(ORIGINAL_cuCtxGetDevice ,device);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdevice *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuCtxGetFlags( unsigned int * flags ) { }

// This is the call that will take the place of the original
int INTER_cuCtxGetFlags( unsigned int * flags ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,unsigned int *> params = std::make_tuple(23 ,flags);
	DriverAPICall call = std::bind(ORIGINAL_cuCtxGetFlags ,flags);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,unsigned int *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuCtxSynchronize( void  ) { }

// This is the call that will take the place of the original
int INTER_cuCtxSynchronize( void  ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,void> params = std::make_tuple(24 );
	DriverAPICall call = std::bind(ORIGINAL_cuCtxSynchronize );
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,void> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuCtxSetLimit( CUlimit limit, size_t value ) { }

// This is the call that will take the place of the original
int INTER_cuCtxSetLimit( CUlimit limit, size_t value ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUlimit,size_t> params = std::make_tuple(25 ,limit,value);
	DriverAPICall call = std::bind(ORIGINAL_cuCtxSetLimit ,limit,value);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUlimit,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuCtxGetLimit( size_t * pvalue, CUlimit limit ) { }

// This is the call that will take the place of the original
int INTER_cuCtxGetLimit( size_t * pvalue, CUlimit limit ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,size_t *,CUlimit> params = std::make_tuple(26 ,pvalue,limit);
	DriverAPICall call = std::bind(ORIGINAL_cuCtxGetLimit ,pvalue,limit);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,size_t *,CUlimit> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuCtxGetCacheConfig( CUfunc_cache * pconfig ) { }

// This is the call that will take the place of the original
int INTER_cuCtxGetCacheConfig( CUfunc_cache * pconfig ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUfunc_cache *> params = std::make_tuple(27 ,pconfig);
	DriverAPICall call = std::bind(ORIGINAL_cuCtxGetCacheConfig ,pconfig);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUfunc_cache *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuCtxSetCacheConfig( CUfunc_cache config ) { }

// This is the call that will take the place of the original
int INTER_cuCtxSetCacheConfig( CUfunc_cache config ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUfunc_cache> params = std::make_tuple(28 ,config);
	DriverAPICall call = std::bind(ORIGINAL_cuCtxSetCacheConfig ,config);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUfunc_cache> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuCtxGetSharedMemConfig( CUsharedconfig * pConfig ) { }

// This is the call that will take the place of the original
int INTER_cuCtxGetSharedMemConfig( CUsharedconfig * pConfig ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUsharedconfig *> params = std::make_tuple(29 ,pConfig);
	DriverAPICall call = std::bind(ORIGINAL_cuCtxGetSharedMemConfig ,pConfig);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUsharedconfig *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuCtxSetSharedMemConfig( CUsharedconfig config ) { }

// This is the call that will take the place of the original
int INTER_cuCtxSetSharedMemConfig( CUsharedconfig config ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUsharedconfig> params = std::make_tuple(30 ,config);
	DriverAPICall call = std::bind(ORIGINAL_cuCtxSetSharedMemConfig ,config);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUsharedconfig> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuCtxGetApiVersion( CUcontext ctx, unsigned int * version ) { }

// This is the call that will take the place of the original
int INTER_cuCtxGetApiVersion( CUcontext ctx, unsigned int * version ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUcontext,unsigned int *> params = std::make_tuple(31 ,ctx,version);
	DriverAPICall call = std::bind(ORIGINAL_cuCtxGetApiVersion ,ctx,version);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUcontext,unsigned int *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuCtxGetStreamPriorityRange( int * leastPriority, int * greatestPriority ) { }

// This is the call that will take the place of the original
int INTER_cuCtxGetStreamPriorityRange( int * leastPriority, int * greatestPriority ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,int *,int *> params = std::make_tuple(32 ,leastPriority,greatestPriority);
	DriverAPICall call = std::bind(ORIGINAL_cuCtxGetStreamPriorityRange ,leastPriority,greatestPriority);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,int *,int *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuCtxAttach( CUcontext * pctx, unsigned int flags ) { }

// This is the call that will take the place of the original
int INTER_cuCtxAttach( CUcontext * pctx, unsigned int flags ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUcontext *,unsigned int> params = std::make_tuple(33 ,pctx,flags);
	DriverAPICall call = std::bind(ORIGINAL_cuCtxAttach ,pctx,flags);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUcontext *,unsigned int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuCtxDetach( CUcontext ctx ) { }

// This is the call that will take the place of the original
int INTER_cuCtxDetach( CUcontext ctx ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUcontext> params = std::make_tuple(34 ,ctx);
	DriverAPICall call = std::bind(ORIGINAL_cuCtxDetach ,ctx);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUcontext> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuModuleLoad( CUmodule * module, const char * fname ) { }

// This is the call that will take the place of the original
int INTER_cuModuleLoad( CUmodule * module, const char * fname ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUmodule *,const char *> params = std::make_tuple(35 ,module,fname);
	DriverAPICall call = std::bind(ORIGINAL_cuModuleLoad ,module,fname);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUmodule *,const char *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuModuleLoadData( CUmodule * module, const void * image ) { }

// This is the call that will take the place of the original
int INTER_cuModuleLoadData( CUmodule * module, const void * image ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUmodule *,const void *> params = std::make_tuple(36 ,module,image);
	DriverAPICall call = std::bind(ORIGINAL_cuModuleLoadData ,module,image);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUmodule *,const void *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuModuleLoadDataEx( CUmodule * module, const void * image, unsigned int numOptions, CUjit_option * options, void * * optionValues ) { }

// This is the call that will take the place of the original
int INTER_cuModuleLoadDataEx( CUmodule * module, const void * image, unsigned int numOptions, CUjit_option * options, void * * optionValues ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUmodule *,const void *,unsigned int,CUjit_option *,void * *> params = std::make_tuple(37 ,module,image,numOptions,options,optionValues);
	DriverAPICall call = std::bind(ORIGINAL_cuModuleLoadDataEx ,module,image,numOptions,options,optionValues);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUmodule *,const void *,unsigned int,CUjit_option *,void * *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuModuleLoadFatBinary( CUmodule * module, const void * fatCubin ) { }

// This is the call that will take the place of the original
int INTER_cuModuleLoadFatBinary( CUmodule * module, const void * fatCubin ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUmodule *,const void *> params = std::make_tuple(38 ,module,fatCubin);
	DriverAPICall call = std::bind(ORIGINAL_cuModuleLoadFatBinary ,module,fatCubin);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUmodule *,const void *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuModuleUnload( CUmodule hmod ) { }

// This is the call that will take the place of the original
int INTER_cuModuleUnload( CUmodule hmod ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUmodule> params = std::make_tuple(39 ,hmod);
	DriverAPICall call = std::bind(ORIGINAL_cuModuleUnload ,hmod);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUmodule> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuModuleGetFunction( CUfunction * hfunc, CUmodule hmod, const char * name ) { }

// This is the call that will take the place of the original
int INTER_cuModuleGetFunction( CUfunction * hfunc, CUmodule hmod, const char * name ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUfunction *,CUmodule,const char *> params = std::make_tuple(40 ,hfunc,hmod,name);
	DriverAPICall call = std::bind(ORIGINAL_cuModuleGetFunction ,hfunc,hmod,name);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUfunction *,CUmodule,const char *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuModuleGetGlobal( CUdeviceptr * dptr, size_t * bytes, CUmodule hmod, const char * name ) { }

// This is the call that will take the place of the original
int INTER_cuModuleGetGlobal( CUdeviceptr * dptr, size_t * bytes, CUmodule hmod, const char * name ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr *,size_t *,CUmodule,const char *> params = std::make_tuple(41 ,dptr,bytes,hmod,name);
	DriverAPICall call = std::bind(ORIGINAL_cuModuleGetGlobal ,dptr,bytes,hmod,name);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr *,size_t *,CUmodule,const char *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuModuleGetTexRef( CUtexref * pTexRef, CUmodule hmod, const char * name ) { }

// This is the call that will take the place of the original
int INTER_cuModuleGetTexRef( CUtexref * pTexRef, CUmodule hmod, const char * name ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUtexref *,CUmodule,const char *> params = std::make_tuple(42 ,pTexRef,hmod,name);
	DriverAPICall call = std::bind(ORIGINAL_cuModuleGetTexRef ,pTexRef,hmod,name);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUtexref *,CUmodule,const char *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuModuleGetSurfRef( CUsurfref * pSurfRef, CUmodule hmod, const char * name ) { }

// This is the call that will take the place of the original
int INTER_cuModuleGetSurfRef( CUsurfref * pSurfRef, CUmodule hmod, const char * name ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUsurfref *,CUmodule,const char *> params = std::make_tuple(43 ,pSurfRef,hmod,name);
	DriverAPICall call = std::bind(ORIGINAL_cuModuleGetSurfRef ,pSurfRef,hmod,name);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUsurfref *,CUmodule,const char *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuLinkCreate( unsigned int numOptions, CUjit_option * options, void * * optionValues, CUlinkState * stateOut ) { }

// This is the call that will take the place of the original
int INTER_cuLinkCreate( unsigned int numOptions, CUjit_option * options, void * * optionValues, CUlinkState * stateOut ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,unsigned int,CUjit_option *,void * *,CUlinkState *> params = std::make_tuple(44 ,numOptions,options,optionValues,stateOut);
	DriverAPICall call = std::bind(ORIGINAL_cuLinkCreate ,numOptions,options,optionValues,stateOut);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,unsigned int,CUjit_option *,void * *,CUlinkState *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuLinkAddData( CUlinkState state, CUjitInputType type, void * data, size_t size, const char * name, unsigned int numOptions, CUjit_option * options, void * * optionValues ) { }

// This is the call that will take the place of the original
int INTER_cuLinkAddData( CUlinkState state, CUjitInputType type, void * data, size_t size, const char * name, unsigned int numOptions, CUjit_option * options, void * * optionValues ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUlinkState,CUjitInputType,void *,size_t,const char *,unsigned int,CUjit_option *,void * *> params = std::make_tuple(45 ,state,type,data,size,name,numOptions,options,optionValues);
	DriverAPICall call = std::bind(ORIGINAL_cuLinkAddData ,state,type,data,size,name,numOptions,options,optionValues);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUlinkState,CUjitInputType,void *,size_t,const char *,unsigned int,CUjit_option *,void * *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuLinkAddFile( CUlinkState state, CUjitInputType type, const char * path, unsigned int numOptions, CUjit_option * options, void * * optionValues ) { }

// This is the call that will take the place of the original
int INTER_cuLinkAddFile( CUlinkState state, CUjitInputType type, const char * path, unsigned int numOptions, CUjit_option * options, void * * optionValues ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUlinkState,CUjitInputType,const char *,unsigned int,CUjit_option *,void * *> params = std::make_tuple(46 ,state,type,path,numOptions,options,optionValues);
	DriverAPICall call = std::bind(ORIGINAL_cuLinkAddFile ,state,type,path,numOptions,options,optionValues);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUlinkState,CUjitInputType,const char *,unsigned int,CUjit_option *,void * *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuLinkComplete( CUlinkState state, void * * cubinOut, size_t * sizeOut ) { }

// This is the call that will take the place of the original
int INTER_cuLinkComplete( CUlinkState state, void * * cubinOut, size_t * sizeOut ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUlinkState,void * *,size_t *> params = std::make_tuple(47 ,state,cubinOut,sizeOut);
	DriverAPICall call = std::bind(ORIGINAL_cuLinkComplete ,state,cubinOut,sizeOut);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUlinkState,void * *,size_t *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuLinkDestroy( CUlinkState state ) { }

// This is the call that will take the place of the original
int INTER_cuLinkDestroy( CUlinkState state ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUlinkState> params = std::make_tuple(48 ,state);
	DriverAPICall call = std::bind(ORIGINAL_cuLinkDestroy ,state);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUlinkState> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemGetInfo( size_t * free, size_t * total ) { }

// This is the call that will take the place of the original
int INTER_cuMemGetInfo( size_t * free, size_t * total ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,size_t *,size_t *> params = std::make_tuple(49 ,free,total);
	DriverAPICall call = std::bind(ORIGINAL_cuMemGetInfo ,free,total);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,size_t *,size_t *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemAlloc( CUdeviceptr * dptr, size_t bytesize ) { }

// This is the call that will take the place of the original
int INTER_cuMemAlloc( CUdeviceptr * dptr, size_t bytesize ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr *,size_t> params = std::make_tuple(50 ,dptr,bytesize);
	DriverAPICall call = std::bind(ORIGINAL_cuMemAlloc ,dptr,bytesize);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr *,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemAllocPitch( CUdeviceptr * dptr, size_t * pPitch, size_t WidthInBytes, size_t Height, unsigned int ElementSizeBytes ) { }

// This is the call that will take the place of the original
int INTER_cuMemAllocPitch( CUdeviceptr * dptr, size_t * pPitch, size_t WidthInBytes, size_t Height, unsigned int ElementSizeBytes ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr *,size_t *,size_t,size_t,unsigned int> params = std::make_tuple(51 ,dptr,pPitch,WidthInBytes,Height,ElementSizeBytes);
	DriverAPICall call = std::bind(ORIGINAL_cuMemAllocPitch ,dptr,pPitch,WidthInBytes,Height,ElementSizeBytes);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr *,size_t *,size_t,size_t,unsigned int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemFree( CUdeviceptr dptr ) { }

// This is the call that will take the place of the original
int INTER_cuMemFree( CUdeviceptr dptr ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr> params = std::make_tuple(52 ,dptr);
	DriverAPICall call = std::bind(ORIGINAL_cuMemFree ,dptr);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemGetAddressRange( CUdeviceptr * pbase, size_t * psize, CUdeviceptr dptr ) { }

// This is the call that will take the place of the original
int INTER_cuMemGetAddressRange( CUdeviceptr * pbase, size_t * psize, CUdeviceptr dptr ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr *,size_t *,CUdeviceptr> params = std::make_tuple(53 ,pbase,psize,dptr);
	DriverAPICall call = std::bind(ORIGINAL_cuMemGetAddressRange ,pbase,psize,dptr);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr *,size_t *,CUdeviceptr> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemAllocHost( void * * pp, size_t bytesize ) { }

// This is the call that will take the place of the original
int INTER_cuMemAllocHost( void * * pp, size_t bytesize ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,void * *,size_t> params = std::make_tuple(54 ,pp,bytesize);
	DriverAPICall call = std::bind(ORIGINAL_cuMemAllocHost ,pp,bytesize);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,void * *,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemFreeHost( void * p ) { }

// This is the call that will take the place of the original
int INTER_cuMemFreeHost( void * p ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,void *> params = std::make_tuple(55 ,p);
	DriverAPICall call = std::bind(ORIGINAL_cuMemFreeHost ,p);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,void *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemHostAlloc( void * * pp, size_t bytesize, unsigned int Flags ) { }

// This is the call that will take the place of the original
int INTER_cuMemHostAlloc( void * * pp, size_t bytesize, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,void * *,size_t,unsigned int> params = std::make_tuple(56 ,pp,bytesize,Flags);
	DriverAPICall call = std::bind(ORIGINAL_cuMemHostAlloc ,pp,bytesize,Flags);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,void * *,size_t,unsigned int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemHostGetDevicePointer( CUdeviceptr * pdptr, void * p, unsigned int Flags ) { }

// This is the call that will take the place of the original
int INTER_cuMemHostGetDevicePointer( CUdeviceptr * pdptr, void * p, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr *,void *,unsigned int> params = std::make_tuple(57 ,pdptr,p,Flags);
	DriverAPICall call = std::bind(ORIGINAL_cuMemHostGetDevicePointer ,pdptr,p,Flags);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr *,void *,unsigned int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemHostGetFlags( unsigned int * pFlags, void * p ) { }

// This is the call that will take the place of the original
int INTER_cuMemHostGetFlags( unsigned int * pFlags, void * p ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,unsigned int *,void *> params = std::make_tuple(58 ,pFlags,p);
	DriverAPICall call = std::bind(ORIGINAL_cuMemHostGetFlags ,pFlags,p);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,unsigned int *,void *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemAllocManaged( CUdeviceptr * dptr, size_t bytesize, unsigned int flags ) { }

// This is the call that will take the place of the original
int INTER_cuMemAllocManaged( CUdeviceptr * dptr, size_t bytesize, unsigned int flags ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr *,size_t,unsigned int> params = std::make_tuple(59 ,dptr,bytesize,flags);
	DriverAPICall call = std::bind(ORIGINAL_cuMemAllocManaged ,dptr,bytesize,flags);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr *,size_t,unsigned int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuDeviceGetByPCIBusId( CUdevice * dev, const char * pciBusId ) { }

// This is the call that will take the place of the original
int INTER_cuDeviceGetByPCIBusId( CUdevice * dev, const char * pciBusId ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdevice *,const char *> params = std::make_tuple(60 ,dev,pciBusId);
	DriverAPICall call = std::bind(ORIGINAL_cuDeviceGetByPCIBusId ,dev,pciBusId);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdevice *,const char *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuDeviceGetPCIBusId( char * pciBusId, int len, CUdevice dev ) { }

// This is the call that will take the place of the original
int INTER_cuDeviceGetPCIBusId( char * pciBusId, int len, CUdevice dev ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,char *,int,CUdevice> params = std::make_tuple(61 ,pciBusId,len,dev);
	DriverAPICall call = std::bind(ORIGINAL_cuDeviceGetPCIBusId ,pciBusId,len,dev);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,char *,int,CUdevice> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuIpcGetEventHandle( CUipcEventHandle * pHandle, CUevent event ) { }

// This is the call that will take the place of the original
int INTER_cuIpcGetEventHandle( CUipcEventHandle * pHandle, CUevent event ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUipcEventHandle *,CUevent> params = std::make_tuple(62 ,pHandle,event);
	DriverAPICall call = std::bind(ORIGINAL_cuIpcGetEventHandle ,pHandle,event);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUipcEventHandle *,CUevent> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuIpcOpenEventHandle( CUevent * phEvent, CUipcEventHandle handle ) { }

// This is the call that will take the place of the original
int INTER_cuIpcOpenEventHandle( CUevent * phEvent, CUipcEventHandle handle ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUevent *,CUipcEventHandle> params = std::make_tuple(63 ,phEvent,handle);
	DriverAPICall call = std::bind(ORIGINAL_cuIpcOpenEventHandle ,phEvent,handle);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUevent *,CUipcEventHandle> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuIpcGetMemHandle( CUipcMemHandle * pHandle, CUdeviceptr dptr ) { }

// This is the call that will take the place of the original
int INTER_cuIpcGetMemHandle( CUipcMemHandle * pHandle, CUdeviceptr dptr ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUipcMemHandle *,CUdeviceptr> params = std::make_tuple(64 ,pHandle,dptr);
	DriverAPICall call = std::bind(ORIGINAL_cuIpcGetMemHandle ,pHandle,dptr);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUipcMemHandle *,CUdeviceptr> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuIpcOpenMemHandle( CUdeviceptr * pdptr, CUipcMemHandle handle, unsigned int Flags ) { }

// This is the call that will take the place of the original
int INTER_cuIpcOpenMemHandle( CUdeviceptr * pdptr, CUipcMemHandle handle, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr *,CUipcMemHandle,unsigned int> params = std::make_tuple(65 ,pdptr,handle,Flags);
	DriverAPICall call = std::bind(ORIGINAL_cuIpcOpenMemHandle ,pdptr,handle,Flags);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr *,CUipcMemHandle,unsigned int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuIpcCloseMemHandle( CUdeviceptr dptr ) { }

// This is the call that will take the place of the original
int INTER_cuIpcCloseMemHandle( CUdeviceptr dptr ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr> params = std::make_tuple(66 ,dptr);
	DriverAPICall call = std::bind(ORIGINAL_cuIpcCloseMemHandle ,dptr);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemHostRegister( void * p, size_t bytesize, unsigned int Flags ) { }

// This is the call that will take the place of the original
int INTER_cuMemHostRegister( void * p, size_t bytesize, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,void *,size_t,unsigned int> params = std::make_tuple(67 ,p,bytesize,Flags);
	DriverAPICall call = std::bind(ORIGINAL_cuMemHostRegister ,p,bytesize,Flags);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,void *,size_t,unsigned int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemHostUnregister( void * p ) { }

// This is the call that will take the place of the original
int INTER_cuMemHostUnregister( void * p ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,void *> params = std::make_tuple(68 ,p);
	DriverAPICall call = std::bind(ORIGINAL_cuMemHostUnregister ,p);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,void *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpy( CUdeviceptr dst, CUdeviceptr src, size_t ByteCount ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpy( CUdeviceptr dst, CUdeviceptr src, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr,CUdeviceptr,size_t> params = std::make_tuple(69 ,dst,src,ByteCount);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpy ,dst,src,ByteCount);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr,CUdeviceptr,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpyPeer( CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpyPeer( CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr,CUcontext,CUdeviceptr,CUcontext,size_t> params = std::make_tuple(70 ,dstDevice,dstContext,srcDevice,srcContext,ByteCount);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyPeer ,dstDevice,dstContext,srcDevice,srcContext,ByteCount);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr,CUcontext,CUdeviceptr,CUcontext,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpyHtoD( CUdeviceptr dstDevice, const void * srcHost, size_t ByteCount ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpyHtoD( CUdeviceptr dstDevice, const void * srcHost, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr,const void *,size_t> params = std::make_tuple(71 ,dstDevice,srcHost,ByteCount);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyHtoD ,dstDevice,srcHost,ByteCount);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr,const void *,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpyDtoH( void * dstHost, CUdeviceptr srcDevice, size_t ByteCount ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpyDtoH( void * dstHost, CUdeviceptr srcDevice, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,void *,CUdeviceptr,size_t> params = std::make_tuple(72 ,dstHost,srcDevice,ByteCount);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyDtoH ,dstHost,srcDevice,ByteCount);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,void *,CUdeviceptr,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpyDtoD( CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpyDtoD( CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr,CUdeviceptr,size_t> params = std::make_tuple(73 ,dstDevice,srcDevice,ByteCount);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyDtoD ,dstDevice,srcDevice,ByteCount);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr,CUdeviceptr,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpyDtoA( CUarray dstArray, size_t dstOffset, CUdeviceptr srcDevice, size_t ByteCount ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpyDtoA( CUarray dstArray, size_t dstOffset, CUdeviceptr srcDevice, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUarray,size_t,CUdeviceptr,size_t> params = std::make_tuple(74 ,dstArray,dstOffset,srcDevice,ByteCount);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyDtoA ,dstArray,dstOffset,srcDevice,ByteCount);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUarray,size_t,CUdeviceptr,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpyAtoD( CUdeviceptr dstDevice, CUarray srcArray, size_t srcOffset, size_t ByteCount ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpyAtoD( CUdeviceptr dstDevice, CUarray srcArray, size_t srcOffset, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr,CUarray,size_t,size_t> params = std::make_tuple(75 ,dstDevice,srcArray,srcOffset,ByteCount);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyAtoD ,dstDevice,srcArray,srcOffset,ByteCount);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr,CUarray,size_t,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpyHtoA( CUarray dstArray, size_t dstOffset, const void * srcHost, size_t ByteCount ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpyHtoA( CUarray dstArray, size_t dstOffset, const void * srcHost, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUarray,size_t,const void *,size_t> params = std::make_tuple(76 ,dstArray,dstOffset,srcHost,ByteCount);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyHtoA ,dstArray,dstOffset,srcHost,ByteCount);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUarray,size_t,const void *,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpyAtoH( void * dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpyAtoH( void * dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,void *,CUarray,size_t,size_t> params = std::make_tuple(77 ,dstHost,srcArray,srcOffset,ByteCount);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyAtoH ,dstHost,srcArray,srcOffset,ByteCount);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,void *,CUarray,size_t,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpyAtoA( CUarray dstArray, size_t dstOffset, CUarray srcArray, size_t srcOffset, size_t ByteCount ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpyAtoA( CUarray dstArray, size_t dstOffset, CUarray srcArray, size_t srcOffset, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUarray,size_t,CUarray,size_t,size_t> params = std::make_tuple(78 ,dstArray,dstOffset,srcArray,srcOffset,ByteCount);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyAtoA ,dstArray,dstOffset,srcArray,srcOffset,ByteCount);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUarray,size_t,CUarray,size_t,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpy2D( const CUDA_MEMCPY2D * pCopy ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpy2D( const CUDA_MEMCPY2D * pCopy ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,const CUDA_MEMCPY2D *> params = std::make_tuple(79 ,pCopy);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpy2D ,pCopy);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,const CUDA_MEMCPY2D *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpy2DUnaligned( const CUDA_MEMCPY2D * pCopy ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpy2DUnaligned( const CUDA_MEMCPY2D * pCopy ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,const CUDA_MEMCPY2D *> params = std::make_tuple(80 ,pCopy);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpy2DUnaligned ,pCopy);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,const CUDA_MEMCPY2D *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpy3D( const CUDA_MEMCPY3D * pCopy ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpy3D( const CUDA_MEMCPY3D * pCopy ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,const CUDA_MEMCPY3D *> params = std::make_tuple(81 ,pCopy);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpy3D ,pCopy);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,const CUDA_MEMCPY3D *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpy3DPeer( const CUDA_MEMCPY3D_PEER * pCopy ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpy3DPeer( const CUDA_MEMCPY3D_PEER * pCopy ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,const CUDA_MEMCPY3D_PEER *> params = std::make_tuple(82 ,pCopy);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpy3DPeer ,pCopy);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,const CUDA_MEMCPY3D_PEER *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpyAsync( CUdeviceptr dst, CUdeviceptr src, size_t ByteCount, CUstream hStream ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpyAsync( CUdeviceptr dst, CUdeviceptr src, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr,CUdeviceptr,size_t,CUstream> params = std::make_tuple(83 ,dst,src,ByteCount,hStream);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyAsync ,dst,src,ByteCount,hStream);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr,CUdeviceptr,size_t,CUstream> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpyPeerAsync( CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount, CUstream hStream ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpyPeerAsync( CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr,CUcontext,CUdeviceptr,CUcontext,size_t,CUstream> params = std::make_tuple(84 ,dstDevice,dstContext,srcDevice,srcContext,ByteCount,hStream);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyPeerAsync ,dstDevice,dstContext,srcDevice,srcContext,ByteCount,hStream);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr,CUcontext,CUdeviceptr,CUcontext,size_t,CUstream> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpyHtoDAsync( CUdeviceptr dstDevice, const void * srcHost, size_t ByteCount, CUstream hStream ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpyHtoDAsync( CUdeviceptr dstDevice, const void * srcHost, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr,const void *,size_t,CUstream> params = std::make_tuple(85 ,dstDevice,srcHost,ByteCount,hStream);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyHtoDAsync ,dstDevice,srcHost,ByteCount,hStream);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr,const void *,size_t,CUstream> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpyDtoHAsync( void * dstHost, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpyDtoHAsync( void * dstHost, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,void *,CUdeviceptr,size_t,CUstream> params = std::make_tuple(86 ,dstHost,srcDevice,ByteCount,hStream);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyDtoHAsync ,dstHost,srcDevice,ByteCount,hStream);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,void *,CUdeviceptr,size_t,CUstream> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpyDtoDAsync( CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpyDtoDAsync( CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr,CUdeviceptr,size_t,CUstream> params = std::make_tuple(87 ,dstDevice,srcDevice,ByteCount,hStream);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyDtoDAsync ,dstDevice,srcDevice,ByteCount,hStream);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr,CUdeviceptr,size_t,CUstream> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpyHtoAAsync( CUarray dstArray, size_t dstOffset, const void * srcHost, size_t ByteCount, CUstream hStream ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpyHtoAAsync( CUarray dstArray, size_t dstOffset, const void * srcHost, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUarray,size_t,const void *,size_t,CUstream> params = std::make_tuple(88 ,dstArray,dstOffset,srcHost,ByteCount,hStream);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyHtoAAsync ,dstArray,dstOffset,srcHost,ByteCount,hStream);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUarray,size_t,const void *,size_t,CUstream> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpyAtoHAsync( void * dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount, CUstream hStream ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpyAtoHAsync( void * dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,void *,CUarray,size_t,size_t,CUstream> params = std::make_tuple(89 ,dstHost,srcArray,srcOffset,ByteCount,hStream);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyAtoHAsync ,dstHost,srcArray,srcOffset,ByteCount,hStream);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,void *,CUarray,size_t,size_t,CUstream> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpy2DAsync( const CUDA_MEMCPY2D * pCopy, CUstream hStream ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpy2DAsync( const CUDA_MEMCPY2D * pCopy, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,const CUDA_MEMCPY2D *,CUstream> params = std::make_tuple(90 ,pCopy,hStream);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpy2DAsync ,pCopy,hStream);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,const CUDA_MEMCPY2D *,CUstream> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpy3DAsync( const CUDA_MEMCPY3D * pCopy, CUstream hStream ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpy3DAsync( const CUDA_MEMCPY3D * pCopy, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,const CUDA_MEMCPY3D *,CUstream> params = std::make_tuple(91 ,pCopy,hStream);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpy3DAsync ,pCopy,hStream);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,const CUDA_MEMCPY3D *,CUstream> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpy3DPeerAsync( const CUDA_MEMCPY3D_PEER * pCopy, CUstream hStream ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpy3DPeerAsync( const CUDA_MEMCPY3D_PEER * pCopy, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,const CUDA_MEMCPY3D_PEER *,CUstream> params = std::make_tuple(92 ,pCopy,hStream);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpy3DPeerAsync ,pCopy,hStream);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,const CUDA_MEMCPY3D_PEER *,CUstream> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemsetD8( CUdeviceptr dstDevice, unsigned char uc, size_t N ) { }

// This is the call that will take the place of the original
int INTER_cuMemsetD8( CUdeviceptr dstDevice, unsigned char uc, size_t N ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr,unsigned char,size_t> params = std::make_tuple(93 ,dstDevice,uc,N);
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD8 ,dstDevice,uc,N);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr,unsigned char,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemsetD16( CUdeviceptr dstDevice, unsigned short us, size_t N ) { }

// This is the call that will take the place of the original
int INTER_cuMemsetD16( CUdeviceptr dstDevice, unsigned short us, size_t N ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr,unsigned short,size_t> params = std::make_tuple(94 ,dstDevice,us,N);
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD16 ,dstDevice,us,N);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr,unsigned short,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemsetD32( CUdeviceptr dstDevice, unsigned int ui, size_t N ) { }

// This is the call that will take the place of the original
int INTER_cuMemsetD32( CUdeviceptr dstDevice, unsigned int ui, size_t N ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr,unsigned int,size_t> params = std::make_tuple(95 ,dstDevice,ui,N);
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD32 ,dstDevice,ui,N);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr,unsigned int,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemsetD2D8( CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height ) { }

// This is the call that will take the place of the original
int INTER_cuMemsetD2D8( CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr,size_t,unsigned char,size_t,size_t> params = std::make_tuple(96 ,dstDevice,dstPitch,uc,Width,Height);
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD2D8 ,dstDevice,dstPitch,uc,Width,Height);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr,size_t,unsigned char,size_t,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemsetD2D16( CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height ) { }

// This is the call that will take the place of the original
int INTER_cuMemsetD2D16( CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr,size_t,unsigned short,size_t,size_t> params = std::make_tuple(97 ,dstDevice,dstPitch,us,Width,Height);
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD2D16 ,dstDevice,dstPitch,us,Width,Height);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr,size_t,unsigned short,size_t,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemsetD2D32( CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height ) { }

// This is the call that will take the place of the original
int INTER_cuMemsetD2D32( CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr,size_t,unsigned int,size_t,size_t> params = std::make_tuple(98 ,dstDevice,dstPitch,ui,Width,Height);
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD2D32 ,dstDevice,dstPitch,ui,Width,Height);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr,size_t,unsigned int,size_t,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemsetD8Async( CUdeviceptr dstDevice, unsigned char uc, size_t N, CUstream hStream ) { }

// This is the call that will take the place of the original
int INTER_cuMemsetD8Async( CUdeviceptr dstDevice, unsigned char uc, size_t N, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr,unsigned char,size_t,CUstream> params = std::make_tuple(99 ,dstDevice,uc,N,hStream);
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD8Async ,dstDevice,uc,N,hStream);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr,unsigned char,size_t,CUstream> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemsetD16Async( CUdeviceptr dstDevice, unsigned short us, size_t N, CUstream hStream ) { }

// This is the call that will take the place of the original
int INTER_cuMemsetD16Async( CUdeviceptr dstDevice, unsigned short us, size_t N, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr,unsigned short,size_t,CUstream> params = std::make_tuple(100 ,dstDevice,us,N,hStream);
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD16Async ,dstDevice,us,N,hStream);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr,unsigned short,size_t,CUstream> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemsetD32Async( CUdeviceptr dstDevice, unsigned int ui, size_t N, CUstream hStream ) { }

// This is the call that will take the place of the original
int INTER_cuMemsetD32Async( CUdeviceptr dstDevice, unsigned int ui, size_t N, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr,unsigned int,size_t,CUstream> params = std::make_tuple(101 ,dstDevice,ui,N,hStream);
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD32Async ,dstDevice,ui,N,hStream);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr,unsigned int,size_t,CUstream> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemsetD2D8Async( CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height, CUstream hStream ) { }

// This is the call that will take the place of the original
int INTER_cuMemsetD2D8Async( CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr,size_t,unsigned char,size_t,size_t,CUstream> params = std::make_tuple(102 ,dstDevice,dstPitch,uc,Width,Height,hStream);
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD2D8Async ,dstDevice,dstPitch,uc,Width,Height,hStream);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr,size_t,unsigned char,size_t,size_t,CUstream> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemsetD2D16Async( CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height, CUstream hStream ) { }

// This is the call that will take the place of the original
int INTER_cuMemsetD2D16Async( CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr,size_t,unsigned short,size_t,size_t,CUstream> params = std::make_tuple(103 ,dstDevice,dstPitch,us,Width,Height,hStream);
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD2D16Async ,dstDevice,dstPitch,us,Width,Height,hStream);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr,size_t,unsigned short,size_t,size_t,CUstream> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemsetD2D32Async( CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height, CUstream hStream ) { }

// This is the call that will take the place of the original
int INTER_cuMemsetD2D32Async( CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr,size_t,unsigned int,size_t,size_t,CUstream> params = std::make_tuple(104 ,dstDevice,dstPitch,ui,Width,Height,hStream);
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD2D32Async ,dstDevice,dstPitch,ui,Width,Height,hStream);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr,size_t,unsigned int,size_t,size_t,CUstream> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuArrayCreate( CUarray * pHandle, const CUDA_ARRAY_DESCRIPTOR * pAllocateArray ) { }

// This is the call that will take the place of the original
int INTER_cuArrayCreate( CUarray * pHandle, const CUDA_ARRAY_DESCRIPTOR * pAllocateArray ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUarray *,const CUDA_ARRAY_DESCRIPTOR *> params = std::make_tuple(105 ,pHandle,pAllocateArray);
	DriverAPICall call = std::bind(ORIGINAL_cuArrayCreate ,pHandle,pAllocateArray);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUarray *,const CUDA_ARRAY_DESCRIPTOR *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuArrayGetDescriptor( CUDA_ARRAY_DESCRIPTOR * pArrayDescriptor, CUarray hArray ) { }

// This is the call that will take the place of the original
int INTER_cuArrayGetDescriptor( CUDA_ARRAY_DESCRIPTOR * pArrayDescriptor, CUarray hArray ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUDA_ARRAY_DESCRIPTOR *,CUarray> params = std::make_tuple(106 ,pArrayDescriptor,hArray);
	DriverAPICall call = std::bind(ORIGINAL_cuArrayGetDescriptor ,pArrayDescriptor,hArray);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUDA_ARRAY_DESCRIPTOR *,CUarray> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuArrayDestroy( CUarray hArray ) { }

// This is the call that will take the place of the original
int INTER_cuArrayDestroy( CUarray hArray ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUarray> params = std::make_tuple(107 ,hArray);
	DriverAPICall call = std::bind(ORIGINAL_cuArrayDestroy ,hArray);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUarray> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuArray3DCreate( CUarray * pHandle, const CUDA_ARRAY3D_DESCRIPTOR * pAllocateArray ) { }

// This is the call that will take the place of the original
int INTER_cuArray3DCreate( CUarray * pHandle, const CUDA_ARRAY3D_DESCRIPTOR * pAllocateArray ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUarray *,const CUDA_ARRAY3D_DESCRIPTOR *> params = std::make_tuple(108 ,pHandle,pAllocateArray);
	DriverAPICall call = std::bind(ORIGINAL_cuArray3DCreate ,pHandle,pAllocateArray);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUarray *,const CUDA_ARRAY3D_DESCRIPTOR *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuArray3DGetDescriptor( CUDA_ARRAY3D_DESCRIPTOR * pArrayDescriptor, CUarray hArray ) { }

// This is the call that will take the place of the original
int INTER_cuArray3DGetDescriptor( CUDA_ARRAY3D_DESCRIPTOR * pArrayDescriptor, CUarray hArray ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUDA_ARRAY3D_DESCRIPTOR *,CUarray> params = std::make_tuple(109 ,pArrayDescriptor,hArray);
	DriverAPICall call = std::bind(ORIGINAL_cuArray3DGetDescriptor ,pArrayDescriptor,hArray);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUDA_ARRAY3D_DESCRIPTOR *,CUarray> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMipmappedArrayCreate( CUmipmappedArray * pHandle, const CUDA_ARRAY3D_DESCRIPTOR * pMipmappedArrayDesc, unsigned int numMipmapLevels ) { }

// This is the call that will take the place of the original
int INTER_cuMipmappedArrayCreate( CUmipmappedArray * pHandle, const CUDA_ARRAY3D_DESCRIPTOR * pMipmappedArrayDesc, unsigned int numMipmapLevels ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUmipmappedArray *,const CUDA_ARRAY3D_DESCRIPTOR *,unsigned int> params = std::make_tuple(110 ,pHandle,pMipmappedArrayDesc,numMipmapLevels);
	DriverAPICall call = std::bind(ORIGINAL_cuMipmappedArrayCreate ,pHandle,pMipmappedArrayDesc,numMipmapLevels);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUmipmappedArray *,const CUDA_ARRAY3D_DESCRIPTOR *,unsigned int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMipmappedArrayGetLevel( CUarray * pLevelArray, CUmipmappedArray hMipmappedArray, unsigned int level ) { }

// This is the call that will take the place of the original
int INTER_cuMipmappedArrayGetLevel( CUarray * pLevelArray, CUmipmappedArray hMipmappedArray, unsigned int level ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUarray *,CUmipmappedArray,unsigned int> params = std::make_tuple(111 ,pLevelArray,hMipmappedArray,level);
	DriverAPICall call = std::bind(ORIGINAL_cuMipmappedArrayGetLevel ,pLevelArray,hMipmappedArray,level);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUarray *,CUmipmappedArray,unsigned int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMipmappedArrayDestroy( CUmipmappedArray hMipmappedArray ) { }

// This is the call that will take the place of the original
int INTER_cuMipmappedArrayDestroy( CUmipmappedArray hMipmappedArray ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUmipmappedArray> params = std::make_tuple(112 ,hMipmappedArray);
	DriverAPICall call = std::bind(ORIGINAL_cuMipmappedArrayDestroy ,hMipmappedArray);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUmipmappedArray> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuPointerGetAttribute( void * data, CUpointer_attribute attribute, CUdeviceptr ptr ) { }

// This is the call that will take the place of the original
int INTER_cuPointerGetAttribute( void * data, CUpointer_attribute attribute, CUdeviceptr ptr ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,void *,CUpointer_attribute,CUdeviceptr> params = std::make_tuple(113 ,data,attribute,ptr);
	DriverAPICall call = std::bind(ORIGINAL_cuPointerGetAttribute ,data,attribute,ptr);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,void *,CUpointer_attribute,CUdeviceptr> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuPointerSetAttribute( const void * value, CUpointer_attribute attribute, CUdeviceptr ptr ) { }

// This is the call that will take the place of the original
int INTER_cuPointerSetAttribute( const void * value, CUpointer_attribute attribute, CUdeviceptr ptr ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,const void *,CUpointer_attribute,CUdeviceptr> params = std::make_tuple(114 ,value,attribute,ptr);
	DriverAPICall call = std::bind(ORIGINAL_cuPointerSetAttribute ,value,attribute,ptr);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,const void *,CUpointer_attribute,CUdeviceptr> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuPointerGetAttributes( unsigned int numAttributes, CUpointer_attribute * attributes, void * * data, CUdeviceptr ptr ) { }

// This is the call that will take the place of the original
int INTER_cuPointerGetAttributes( unsigned int numAttributes, CUpointer_attribute * attributes, void * * data, CUdeviceptr ptr ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,unsigned int,CUpointer_attribute *,void * *,CUdeviceptr> params = std::make_tuple(115 ,numAttributes,attributes,data,ptr);
	DriverAPICall call = std::bind(ORIGINAL_cuPointerGetAttributes ,numAttributes,attributes,data,ptr);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,unsigned int,CUpointer_attribute *,void * *,CUdeviceptr> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuStreamCreate( CUstream * phStream, unsigned int Flags ) { }

// This is the call that will take the place of the original
int INTER_cuStreamCreate( CUstream * phStream, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUstream *,unsigned int> params = std::make_tuple(116 ,phStream,Flags);
	DriverAPICall call = std::bind(ORIGINAL_cuStreamCreate ,phStream,Flags);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUstream *,unsigned int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuStreamCreateWithPriority( CUstream * phStream, unsigned int flags, int priority ) { }

// This is the call that will take the place of the original
int INTER_cuStreamCreateWithPriority( CUstream * phStream, unsigned int flags, int priority ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUstream *,unsigned int,int> params = std::make_tuple(117 ,phStream,flags,priority);
	DriverAPICall call = std::bind(ORIGINAL_cuStreamCreateWithPriority ,phStream,flags,priority);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUstream *,unsigned int,int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuStreamGetPriority( CUstream hStream, int * priority ) { }

// This is the call that will take the place of the original
int INTER_cuStreamGetPriority( CUstream hStream, int * priority ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUstream,int *> params = std::make_tuple(118 ,hStream,priority);
	DriverAPICall call = std::bind(ORIGINAL_cuStreamGetPriority ,hStream,priority);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUstream,int *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuStreamGetFlags( CUstream hStream, unsigned int * flags ) { }

// This is the call that will take the place of the original
int INTER_cuStreamGetFlags( CUstream hStream, unsigned int * flags ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUstream,unsigned int *> params = std::make_tuple(119 ,hStream,flags);
	DriverAPICall call = std::bind(ORIGINAL_cuStreamGetFlags ,hStream,flags);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUstream,unsigned int *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuStreamWaitEvent( CUstream hStream, CUevent hEvent, unsigned int Flags ) { }

// This is the call that will take the place of the original
int INTER_cuStreamWaitEvent( CUstream hStream, CUevent hEvent, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUstream,CUevent,unsigned int> params = std::make_tuple(120 ,hStream,hEvent,Flags);
	DriverAPICall call = std::bind(ORIGINAL_cuStreamWaitEvent ,hStream,hEvent,Flags);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUstream,CUevent,unsigned int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuStreamAddCallback( CUstream hStream, CUstreamCallback callback, void * userData, unsigned int flags ) { }

// This is the call that will take the place of the original
int INTER_cuStreamAddCallback( CUstream hStream, CUstreamCallback callback, void * userData, unsigned int flags ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUstream,CUstreamCallback,void *,unsigned int> params = std::make_tuple(121 ,hStream,callback,userData,flags);
	DriverAPICall call = std::bind(ORIGINAL_cuStreamAddCallback ,hStream,callback,userData,flags);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUstream,CUstreamCallback,void *,unsigned int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuStreamAttachMemAsync( CUstream hStream, CUdeviceptr dptr, size_t length, unsigned int flags ) { }

// This is the call that will take the place of the original
int INTER_cuStreamAttachMemAsync( CUstream hStream, CUdeviceptr dptr, size_t length, unsigned int flags ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUstream,CUdeviceptr,size_t,unsigned int> params = std::make_tuple(122 ,hStream,dptr,length,flags);
	DriverAPICall call = std::bind(ORIGINAL_cuStreamAttachMemAsync ,hStream,dptr,length,flags);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUstream,CUdeviceptr,size_t,unsigned int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuStreamQuery( CUstream hStream ) { }

// This is the call that will take the place of the original
int INTER_cuStreamQuery( CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUstream> params = std::make_tuple(123 ,hStream);
	DriverAPICall call = std::bind(ORIGINAL_cuStreamQuery ,hStream);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUstream> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuStreamSynchronize( CUstream hStream ) { }

// This is the call that will take the place of the original
int INTER_cuStreamSynchronize( CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUstream> params = std::make_tuple(124 ,hStream);
	DriverAPICall call = std::bind(ORIGINAL_cuStreamSynchronize ,hStream);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUstream> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuStreamDestroy( CUstream hStream ) { }

// This is the call that will take the place of the original
int INTER_cuStreamDestroy( CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUstream> params = std::make_tuple(125 ,hStream);
	DriverAPICall call = std::bind(ORIGINAL_cuStreamDestroy ,hStream);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUstream> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuEventCreate( CUevent * phEvent, unsigned int Flags ) { }

// This is the call that will take the place of the original
int INTER_cuEventCreate( CUevent * phEvent, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUevent *,unsigned int> params = std::make_tuple(126 ,phEvent,Flags);
	DriverAPICall call = std::bind(ORIGINAL_cuEventCreate ,phEvent,Flags);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUevent *,unsigned int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuEventRecord( CUevent hEvent, CUstream hStream ) { }

// This is the call that will take the place of the original
int INTER_cuEventRecord( CUevent hEvent, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUevent,CUstream> params = std::make_tuple(127 ,hEvent,hStream);
	DriverAPICall call = std::bind(ORIGINAL_cuEventRecord ,hEvent,hStream);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUevent,CUstream> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuEventQuery( CUevent hEvent ) { }

// This is the call that will take the place of the original
int INTER_cuEventQuery( CUevent hEvent ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUevent> params = std::make_tuple(128 ,hEvent);
	DriverAPICall call = std::bind(ORIGINAL_cuEventQuery ,hEvent);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUevent> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuEventSynchronize( CUevent hEvent ) { }

// This is the call that will take the place of the original
int INTER_cuEventSynchronize( CUevent hEvent ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUevent> params = std::make_tuple(129 ,hEvent);
	DriverAPICall call = std::bind(ORIGINAL_cuEventSynchronize ,hEvent);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUevent> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuEventDestroy( CUevent hEvent ) { }

// This is the call that will take the place of the original
int INTER_cuEventDestroy( CUevent hEvent ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUevent> params = std::make_tuple(130 ,hEvent);
	DriverAPICall call = std::bind(ORIGINAL_cuEventDestroy ,hEvent);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUevent> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuEventElapsedTime( float * pMilliseconds, CUevent hStart, CUevent hEnd ) { }

// This is the call that will take the place of the original
int INTER_cuEventElapsedTime( float * pMilliseconds, CUevent hStart, CUevent hEnd ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,float *,CUevent,CUevent> params = std::make_tuple(131 ,pMilliseconds,hStart,hEnd);
	DriverAPICall call = std::bind(ORIGINAL_cuEventElapsedTime ,pMilliseconds,hStart,hEnd);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,float *,CUevent,CUevent> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuFuncGetAttribute( int * pi, CUfunction_attribute attrib, CUfunction hfunc ) { }

// This is the call that will take the place of the original
int INTER_cuFuncGetAttribute( int * pi, CUfunction_attribute attrib, CUfunction hfunc ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,int *,CUfunction_attribute,CUfunction> params = std::make_tuple(132 ,pi,attrib,hfunc);
	DriverAPICall call = std::bind(ORIGINAL_cuFuncGetAttribute ,pi,attrib,hfunc);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,int *,CUfunction_attribute,CUfunction> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuFuncSetCacheConfig( CUfunction hfunc, CUfunc_cache config ) { }

// This is the call that will take the place of the original
int INTER_cuFuncSetCacheConfig( CUfunction hfunc, CUfunc_cache config ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUfunction,CUfunc_cache> params = std::make_tuple(133 ,hfunc,config);
	DriverAPICall call = std::bind(ORIGINAL_cuFuncSetCacheConfig ,hfunc,config);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUfunction,CUfunc_cache> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuFuncSetSharedMemConfig( CUfunction hfunc, CUsharedconfig config ) { }

// This is the call that will take the place of the original
int INTER_cuFuncSetSharedMemConfig( CUfunction hfunc, CUsharedconfig config ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUfunction,CUsharedconfig> params = std::make_tuple(134 ,hfunc,config);
	DriverAPICall call = std::bind(ORIGINAL_cuFuncSetSharedMemConfig ,hfunc,config);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUfunction,CUsharedconfig> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuLaunchKernel( CUfunction f, unsigned int gridDimX, unsigned int gridDimY, unsigned int gridDimZ, unsigned int blockDimX, unsigned int blockDimY, unsigned int blockDimZ, unsigned int sharedMemBytes, CUstream hStream, void * * kernelParams, void * * extra ) { }

// This is the call that will take the place of the original
int INTER_cuLaunchKernel( CUfunction f, unsigned int gridDimX, unsigned int gridDimY, unsigned int gridDimZ, unsigned int blockDimX, unsigned int blockDimY, unsigned int blockDimZ, unsigned int sharedMemBytes, CUstream hStream, void * * kernelParams, void * * extra ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUfunction,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,CUstream,void * *,void * *> params = std::make_tuple(135 ,f,gridDimX,gridDimY,gridDimZ,blockDimX,blockDimY,blockDimZ,sharedMemBytes,hStream,kernelParams,extra);
	DriverAPICall call = std::bind(ORIGINAL_cuLaunchKernel ,f,gridDimX,gridDimY,gridDimZ,blockDimX,blockDimY,blockDimZ,sharedMemBytes,hStream,kernelParams,extra);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUfunction,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,CUstream,void * *,void * *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuFuncSetBlockShape( CUfunction hfunc, int x, int y, int z ) { }

// This is the call that will take the place of the original
int INTER_cuFuncSetBlockShape( CUfunction hfunc, int x, int y, int z ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUfunction,int,int,int> params = std::make_tuple(136 ,hfunc,x,y,z);
	DriverAPICall call = std::bind(ORIGINAL_cuFuncSetBlockShape ,hfunc,x,y,z);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUfunction,int,int,int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuFuncSetSharedSize( CUfunction hfunc, unsigned int bytes ) { }

// This is the call that will take the place of the original
int INTER_cuFuncSetSharedSize( CUfunction hfunc, unsigned int bytes ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUfunction,unsigned int> params = std::make_tuple(137 ,hfunc,bytes);
	DriverAPICall call = std::bind(ORIGINAL_cuFuncSetSharedSize ,hfunc,bytes);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUfunction,unsigned int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuParamSetSize( CUfunction hfunc, unsigned int numbytes ) { }

// This is the call that will take the place of the original
int INTER_cuParamSetSize( CUfunction hfunc, unsigned int numbytes ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUfunction,unsigned int> params = std::make_tuple(138 ,hfunc,numbytes);
	DriverAPICall call = std::bind(ORIGINAL_cuParamSetSize ,hfunc,numbytes);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUfunction,unsigned int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuParamSeti( CUfunction hfunc, int offset, unsigned int value ) { }

// This is the call that will take the place of the original
int INTER_cuParamSeti( CUfunction hfunc, int offset, unsigned int value ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUfunction,int,unsigned int> params = std::make_tuple(139 ,hfunc,offset,value);
	DriverAPICall call = std::bind(ORIGINAL_cuParamSeti ,hfunc,offset,value);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUfunction,int,unsigned int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuParamSetf( CUfunction hfunc, int offset, float value ) { }

// This is the call that will take the place of the original
int INTER_cuParamSetf( CUfunction hfunc, int offset, float value ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUfunction,int,float> params = std::make_tuple(140 ,hfunc,offset,value);
	DriverAPICall call = std::bind(ORIGINAL_cuParamSetf ,hfunc,offset,value);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUfunction,int,float> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuParamSetv( CUfunction hfunc, int offset, void * ptr, unsigned int numbytes ) { }

// This is the call that will take the place of the original
int INTER_cuParamSetv( CUfunction hfunc, int offset, void * ptr, unsigned int numbytes ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUfunction,int,void *,unsigned int> params = std::make_tuple(141 ,hfunc,offset,ptr,numbytes);
	DriverAPICall call = std::bind(ORIGINAL_cuParamSetv ,hfunc,offset,ptr,numbytes);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUfunction,int,void *,unsigned int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuLaunch( CUfunction f ) { }

// This is the call that will take the place of the original
int INTER_cuLaunch( CUfunction f ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUfunction> params = std::make_tuple(142 ,f);
	DriverAPICall call = std::bind(ORIGINAL_cuLaunch ,f);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUfunction> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuLaunchGrid( CUfunction f, int grid_width, int grid_height ) { }

// This is the call that will take the place of the original
int INTER_cuLaunchGrid( CUfunction f, int grid_width, int grid_height ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUfunction,int,int> params = std::make_tuple(143 ,f,grid_width,grid_height);
	DriverAPICall call = std::bind(ORIGINAL_cuLaunchGrid ,f,grid_width,grid_height);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUfunction,int,int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuLaunchGridAsync( CUfunction f, int grid_width, int grid_height, CUstream hStream ) { }

// This is the call that will take the place of the original
int INTER_cuLaunchGridAsync( CUfunction f, int grid_width, int grid_height, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUfunction,int,int,CUstream> params = std::make_tuple(144 ,f,grid_width,grid_height,hStream);
	DriverAPICall call = std::bind(ORIGINAL_cuLaunchGridAsync ,f,grid_width,grid_height,hStream);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUfunction,int,int,CUstream> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuParamSetTexRef( CUfunction hfunc, int texunit, CUtexref hTexRef ) { }

// This is the call that will take the place of the original
int INTER_cuParamSetTexRef( CUfunction hfunc, int texunit, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUfunction,int,CUtexref> params = std::make_tuple(145 ,hfunc,texunit,hTexRef);
	DriverAPICall call = std::bind(ORIGINAL_cuParamSetTexRef ,hfunc,texunit,hTexRef);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUfunction,int,CUtexref> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuOccupancyMaxActiveBlocksPerMultiprocessor( int * numBlocks, CUfunction func, int blockSize, size_t dynamicSMemSize ) { }

// This is the call that will take the place of the original
int INTER_cuOccupancyMaxActiveBlocksPerMultiprocessor( int * numBlocks, CUfunction func, int blockSize, size_t dynamicSMemSize ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,int *,CUfunction,int,size_t> params = std::make_tuple(146 ,numBlocks,func,blockSize,dynamicSMemSize);
	DriverAPICall call = std::bind(ORIGINAL_cuOccupancyMaxActiveBlocksPerMultiprocessor ,numBlocks,func,blockSize,dynamicSMemSize);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,int *,CUfunction,int,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags( int * numBlocks, CUfunction func, int blockSize, size_t dynamicSMemSize, unsigned int flags ) { }

// This is the call that will take the place of the original
int INTER_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags( int * numBlocks, CUfunction func, int blockSize, size_t dynamicSMemSize, unsigned int flags ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,int *,CUfunction,int,size_t,unsigned int> params = std::make_tuple(147 ,numBlocks,func,blockSize,dynamicSMemSize,flags);
	DriverAPICall call = std::bind(ORIGINAL_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags ,numBlocks,func,blockSize,dynamicSMemSize,flags);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,int *,CUfunction,int,size_t,unsigned int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuOccupancyMaxPotentialBlockSize( int * minGridSize, int * blockSize, CUfunction func, CUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int blockSizeLimit ) { }

// This is the call that will take the place of the original
int INTER_cuOccupancyMaxPotentialBlockSize( int * minGridSize, int * blockSize, CUfunction func, CUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int blockSizeLimit ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,int *,int *,CUfunction,CUoccupancyB2DSize,size_t,int> params = std::make_tuple(148 ,minGridSize,blockSize,func,blockSizeToDynamicSMemSize,dynamicSMemSize,blockSizeLimit);
	DriverAPICall call = std::bind(ORIGINAL_cuOccupancyMaxPotentialBlockSize ,minGridSize,blockSize,func,blockSizeToDynamicSMemSize,dynamicSMemSize,blockSizeLimit);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,int *,int *,CUfunction,CUoccupancyB2DSize,size_t,int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuOccupancyMaxPotentialBlockSizeWithFlags( int * minGridSize, int * blockSize, CUfunction func, CUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int blockSizeLimit, unsigned int flags ) { }

// This is the call that will take the place of the original
int INTER_cuOccupancyMaxPotentialBlockSizeWithFlags( int * minGridSize, int * blockSize, CUfunction func, CUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int blockSizeLimit, unsigned int flags ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,int *,int *,CUfunction,CUoccupancyB2DSize,size_t,int,unsigned int> params = std::make_tuple(149 ,minGridSize,blockSize,func,blockSizeToDynamicSMemSize,dynamicSMemSize,blockSizeLimit,flags);
	DriverAPICall call = std::bind(ORIGINAL_cuOccupancyMaxPotentialBlockSizeWithFlags ,minGridSize,blockSize,func,blockSizeToDynamicSMemSize,dynamicSMemSize,blockSizeLimit,flags);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,int *,int *,CUfunction,CUoccupancyB2DSize,size_t,int,unsigned int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuTexRefSetArray( CUtexref hTexRef, CUarray hArray, unsigned int Flags ) { }

// This is the call that will take the place of the original
int INTER_cuTexRefSetArray( CUtexref hTexRef, CUarray hArray, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUtexref,CUarray,unsigned int> params = std::make_tuple(150 ,hTexRef,hArray,Flags);
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefSetArray ,hTexRef,hArray,Flags);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUtexref,CUarray,unsigned int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuTexRefSetMipmappedArray( CUtexref hTexRef, CUmipmappedArray hMipmappedArray, unsigned int Flags ) { }

// This is the call that will take the place of the original
int INTER_cuTexRefSetMipmappedArray( CUtexref hTexRef, CUmipmappedArray hMipmappedArray, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUtexref,CUmipmappedArray,unsigned int> params = std::make_tuple(151 ,hTexRef,hMipmappedArray,Flags);
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefSetMipmappedArray ,hTexRef,hMipmappedArray,Flags);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUtexref,CUmipmappedArray,unsigned int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuTexRefSetAddress( size_t * ByteOffset, CUtexref hTexRef, CUdeviceptr dptr, size_t bytes ) { }

// This is the call that will take the place of the original
int INTER_cuTexRefSetAddress( size_t * ByteOffset, CUtexref hTexRef, CUdeviceptr dptr, size_t bytes ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,size_t *,CUtexref,CUdeviceptr,size_t> params = std::make_tuple(152 ,ByteOffset,hTexRef,dptr,bytes);
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefSetAddress ,ByteOffset,hTexRef,dptr,bytes);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,size_t *,CUtexref,CUdeviceptr,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuTexRefSetAddress2D( CUtexref hTexRef, const CUDA_ARRAY_DESCRIPTOR * desc, CUdeviceptr dptr, size_t Pitch ) { }

// This is the call that will take the place of the original
int INTER_cuTexRefSetAddress2D( CUtexref hTexRef, const CUDA_ARRAY_DESCRIPTOR * desc, CUdeviceptr dptr, size_t Pitch ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUtexref,const CUDA_ARRAY_DESCRIPTOR *,CUdeviceptr,size_t> params = std::make_tuple(153 ,hTexRef,desc,dptr,Pitch);
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefSetAddress2D ,hTexRef,desc,dptr,Pitch);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUtexref,const CUDA_ARRAY_DESCRIPTOR *,CUdeviceptr,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuTexRefSetFormat( CUtexref hTexRef, CUarray_format fmt, int NumPackedComponents ) { }

// This is the call that will take the place of the original
int INTER_cuTexRefSetFormat( CUtexref hTexRef, CUarray_format fmt, int NumPackedComponents ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUtexref,CUarray_format,int> params = std::make_tuple(154 ,hTexRef,fmt,NumPackedComponents);
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefSetFormat ,hTexRef,fmt,NumPackedComponents);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUtexref,CUarray_format,int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuTexRefSetAddressMode( CUtexref hTexRef, int dim, CUaddress_mode am ) { }

// This is the call that will take the place of the original
int INTER_cuTexRefSetAddressMode( CUtexref hTexRef, int dim, CUaddress_mode am ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUtexref,int,CUaddress_mode> params = std::make_tuple(155 ,hTexRef,dim,am);
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefSetAddressMode ,hTexRef,dim,am);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUtexref,int,CUaddress_mode> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuTexRefSetFilterMode( CUtexref hTexRef, CUfilter_mode fm ) { }

// This is the call that will take the place of the original
int INTER_cuTexRefSetFilterMode( CUtexref hTexRef, CUfilter_mode fm ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUtexref,CUfilter_mode> params = std::make_tuple(156 ,hTexRef,fm);
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefSetFilterMode ,hTexRef,fm);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUtexref,CUfilter_mode> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuTexRefSetMipmapFilterMode( CUtexref hTexRef, CUfilter_mode fm ) { }

// This is the call that will take the place of the original
int INTER_cuTexRefSetMipmapFilterMode( CUtexref hTexRef, CUfilter_mode fm ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUtexref,CUfilter_mode> params = std::make_tuple(157 ,hTexRef,fm);
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefSetMipmapFilterMode ,hTexRef,fm);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUtexref,CUfilter_mode> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuTexRefSetMipmapLevelBias( CUtexref hTexRef, float bias ) { }

// This is the call that will take the place of the original
int INTER_cuTexRefSetMipmapLevelBias( CUtexref hTexRef, float bias ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUtexref,float> params = std::make_tuple(158 ,hTexRef,bias);
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefSetMipmapLevelBias ,hTexRef,bias);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUtexref,float> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuTexRefSetMipmapLevelClamp( CUtexref hTexRef, float minMipmapLevelClamp, float maxMipmapLevelClamp ) { }

// This is the call that will take the place of the original
int INTER_cuTexRefSetMipmapLevelClamp( CUtexref hTexRef, float minMipmapLevelClamp, float maxMipmapLevelClamp ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUtexref,float,float> params = std::make_tuple(159 ,hTexRef,minMipmapLevelClamp,maxMipmapLevelClamp);
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefSetMipmapLevelClamp ,hTexRef,minMipmapLevelClamp,maxMipmapLevelClamp);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUtexref,float,float> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuTexRefSetMaxAnisotropy( CUtexref hTexRef, unsigned int maxAniso ) { }

// This is the call that will take the place of the original
int INTER_cuTexRefSetMaxAnisotropy( CUtexref hTexRef, unsigned int maxAniso ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUtexref,unsigned int> params = std::make_tuple(160 ,hTexRef,maxAniso);
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefSetMaxAnisotropy ,hTexRef,maxAniso);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUtexref,unsigned int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuTexRefSetFlags( CUtexref hTexRef, unsigned int Flags ) { }

// This is the call that will take the place of the original
int INTER_cuTexRefSetFlags( CUtexref hTexRef, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUtexref,unsigned int> params = std::make_tuple(161 ,hTexRef,Flags);
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefSetFlags ,hTexRef,Flags);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUtexref,unsigned int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuTexRefGetAddress( CUdeviceptr * pdptr, CUtexref hTexRef ) { }

// This is the call that will take the place of the original
int INTER_cuTexRefGetAddress( CUdeviceptr * pdptr, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr *,CUtexref> params = std::make_tuple(162 ,pdptr,hTexRef);
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefGetAddress ,pdptr,hTexRef);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr *,CUtexref> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuTexRefGetArray( CUarray * phArray, CUtexref hTexRef ) { }

// This is the call that will take the place of the original
int INTER_cuTexRefGetArray( CUarray * phArray, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUarray *,CUtexref> params = std::make_tuple(163 ,phArray,hTexRef);
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefGetArray ,phArray,hTexRef);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUarray *,CUtexref> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuTexRefGetMipmappedArray( CUmipmappedArray * phMipmappedArray, CUtexref hTexRef ) { }

// This is the call that will take the place of the original
int INTER_cuTexRefGetMipmappedArray( CUmipmappedArray * phMipmappedArray, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUmipmappedArray *,CUtexref> params = std::make_tuple(164 ,phMipmappedArray,hTexRef);
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefGetMipmappedArray ,phMipmappedArray,hTexRef);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUmipmappedArray *,CUtexref> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuTexRefGetAddressMode( CUaddress_mode * pam, CUtexref hTexRef, int dim ) { }

// This is the call that will take the place of the original
int INTER_cuTexRefGetAddressMode( CUaddress_mode * pam, CUtexref hTexRef, int dim ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUaddress_mode *,CUtexref,int> params = std::make_tuple(165 ,pam,hTexRef,dim);
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefGetAddressMode ,pam,hTexRef,dim);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUaddress_mode *,CUtexref,int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuTexRefGetFilterMode( CUfilter_mode * pfm, CUtexref hTexRef ) { }

// This is the call that will take the place of the original
int INTER_cuTexRefGetFilterMode( CUfilter_mode * pfm, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUfilter_mode *,CUtexref> params = std::make_tuple(166 ,pfm,hTexRef);
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefGetFilterMode ,pfm,hTexRef);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUfilter_mode *,CUtexref> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuTexRefGetFormat( CUarray_format * pFormat, int * pNumChannels, CUtexref hTexRef ) { }

// This is the call that will take the place of the original
int INTER_cuTexRefGetFormat( CUarray_format * pFormat, int * pNumChannels, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUarray_format *,int *,CUtexref> params = std::make_tuple(167 ,pFormat,pNumChannels,hTexRef);
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefGetFormat ,pFormat,pNumChannels,hTexRef);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUarray_format *,int *,CUtexref> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuTexRefGetMipmapFilterMode( CUfilter_mode * pfm, CUtexref hTexRef ) { }

// This is the call that will take the place of the original
int INTER_cuTexRefGetMipmapFilterMode( CUfilter_mode * pfm, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUfilter_mode *,CUtexref> params = std::make_tuple(168 ,pfm,hTexRef);
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefGetMipmapFilterMode ,pfm,hTexRef);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUfilter_mode *,CUtexref> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuTexRefGetMipmapLevelBias( float * pbias, CUtexref hTexRef ) { }

// This is the call that will take the place of the original
int INTER_cuTexRefGetMipmapLevelBias( float * pbias, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,float *,CUtexref> params = std::make_tuple(169 ,pbias,hTexRef);
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefGetMipmapLevelBias ,pbias,hTexRef);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,float *,CUtexref> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuTexRefGetMipmapLevelClamp( float * pminMipmapLevelClamp, float * pmaxMipmapLevelClamp, CUtexref hTexRef ) { }

// This is the call that will take the place of the original
int INTER_cuTexRefGetMipmapLevelClamp( float * pminMipmapLevelClamp, float * pmaxMipmapLevelClamp, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,float *,float *,CUtexref> params = std::make_tuple(170 ,pminMipmapLevelClamp,pmaxMipmapLevelClamp,hTexRef);
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefGetMipmapLevelClamp ,pminMipmapLevelClamp,pmaxMipmapLevelClamp,hTexRef);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,float *,float *,CUtexref> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuTexRefGetMaxAnisotropy( int * pmaxAniso, CUtexref hTexRef ) { }

// This is the call that will take the place of the original
int INTER_cuTexRefGetMaxAnisotropy( int * pmaxAniso, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,int *,CUtexref> params = std::make_tuple(171 ,pmaxAniso,hTexRef);
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefGetMaxAnisotropy ,pmaxAniso,hTexRef);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,int *,CUtexref> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuTexRefGetFlags( unsigned int * pFlags, CUtexref hTexRef ) { }

// This is the call that will take the place of the original
int INTER_cuTexRefGetFlags( unsigned int * pFlags, CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,unsigned int *,CUtexref> params = std::make_tuple(172 ,pFlags,hTexRef);
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefGetFlags ,pFlags,hTexRef);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,unsigned int *,CUtexref> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuTexRefCreate( CUtexref * pTexRef ) { }

// This is the call that will take the place of the original
int INTER_cuTexRefCreate( CUtexref * pTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUtexref *> params = std::make_tuple(173 ,pTexRef);
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefCreate ,pTexRef);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUtexref *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuTexRefDestroy( CUtexref hTexRef ) { }

// This is the call that will take the place of the original
int INTER_cuTexRefDestroy( CUtexref hTexRef ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUtexref> params = std::make_tuple(174 ,hTexRef);
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefDestroy ,hTexRef);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUtexref> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuSurfRefSetArray( CUsurfref hSurfRef, CUarray hArray, unsigned int Flags ) { }

// This is the call that will take the place of the original
int INTER_cuSurfRefSetArray( CUsurfref hSurfRef, CUarray hArray, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUsurfref,CUarray,unsigned int> params = std::make_tuple(175 ,hSurfRef,hArray,Flags);
	DriverAPICall call = std::bind(ORIGINAL_cuSurfRefSetArray ,hSurfRef,hArray,Flags);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUsurfref,CUarray,unsigned int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuSurfRefGetArray( CUarray * phArray, CUsurfref hSurfRef ) { }

// This is the call that will take the place of the original
int INTER_cuSurfRefGetArray( CUarray * phArray, CUsurfref hSurfRef ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUarray *,CUsurfref> params = std::make_tuple(176 ,phArray,hSurfRef);
	DriverAPICall call = std::bind(ORIGINAL_cuSurfRefGetArray ,phArray,hSurfRef);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUarray *,CUsurfref> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuTexObjectCreate( CUtexObject * pTexObject, const CUDA_RESOURCE_DESC * pResDesc, const CUDA_TEXTURE_DESC * pTexDesc, const CUDA_RESOURCE_VIEW_DESC * pResViewDesc ) { }

// This is the call that will take the place of the original
int INTER_cuTexObjectCreate( CUtexObject * pTexObject, const CUDA_RESOURCE_DESC * pResDesc, const CUDA_TEXTURE_DESC * pTexDesc, const CUDA_RESOURCE_VIEW_DESC * pResViewDesc ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUtexObject *,const CUDA_RESOURCE_DESC *,const CUDA_TEXTURE_DESC *,const CUDA_RESOURCE_VIEW_DESC *> params = std::make_tuple(177 ,pTexObject,pResDesc,pTexDesc,pResViewDesc);
	DriverAPICall call = std::bind(ORIGINAL_cuTexObjectCreate ,pTexObject,pResDesc,pTexDesc,pResViewDesc);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUtexObject *,const CUDA_RESOURCE_DESC *,const CUDA_TEXTURE_DESC *,const CUDA_RESOURCE_VIEW_DESC *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuTexObjectDestroy( CUtexObject texObject ) { }

// This is the call that will take the place of the original
int INTER_cuTexObjectDestroy( CUtexObject texObject ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUtexObject> params = std::make_tuple(178 ,texObject);
	DriverAPICall call = std::bind(ORIGINAL_cuTexObjectDestroy ,texObject);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUtexObject> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuTexObjectGetResourceDesc( CUDA_RESOURCE_DESC * pResDesc, CUtexObject texObject ) { }

// This is the call that will take the place of the original
int INTER_cuTexObjectGetResourceDesc( CUDA_RESOURCE_DESC * pResDesc, CUtexObject texObject ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUDA_RESOURCE_DESC *,CUtexObject> params = std::make_tuple(179 ,pResDesc,texObject);
	DriverAPICall call = std::bind(ORIGINAL_cuTexObjectGetResourceDesc ,pResDesc,texObject);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUDA_RESOURCE_DESC *,CUtexObject> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuTexObjectGetTextureDesc( CUDA_TEXTURE_DESC * pTexDesc, CUtexObject texObject ) { }

// This is the call that will take the place of the original
int INTER_cuTexObjectGetTextureDesc( CUDA_TEXTURE_DESC * pTexDesc, CUtexObject texObject ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUDA_TEXTURE_DESC *,CUtexObject> params = std::make_tuple(180 ,pTexDesc,texObject);
	DriverAPICall call = std::bind(ORIGINAL_cuTexObjectGetTextureDesc ,pTexDesc,texObject);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUDA_TEXTURE_DESC *,CUtexObject> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuTexObjectGetResourceViewDesc( CUDA_RESOURCE_VIEW_DESC * pResViewDesc, CUtexObject texObject ) { }

// This is the call that will take the place of the original
int INTER_cuTexObjectGetResourceViewDesc( CUDA_RESOURCE_VIEW_DESC * pResViewDesc, CUtexObject texObject ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUDA_RESOURCE_VIEW_DESC *,CUtexObject> params = std::make_tuple(181 ,pResViewDesc,texObject);
	DriverAPICall call = std::bind(ORIGINAL_cuTexObjectGetResourceViewDesc ,pResViewDesc,texObject);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUDA_RESOURCE_VIEW_DESC *,CUtexObject> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuSurfObjectCreate( CUsurfObject * pSurfObject, const CUDA_RESOURCE_DESC * pResDesc ) { }

// This is the call that will take the place of the original
int INTER_cuSurfObjectCreate( CUsurfObject * pSurfObject, const CUDA_RESOURCE_DESC * pResDesc ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUsurfObject *,const CUDA_RESOURCE_DESC *> params = std::make_tuple(182 ,pSurfObject,pResDesc);
	DriverAPICall call = std::bind(ORIGINAL_cuSurfObjectCreate ,pSurfObject,pResDesc);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUsurfObject *,const CUDA_RESOURCE_DESC *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuSurfObjectDestroy( CUsurfObject surfObject ) { }

// This is the call that will take the place of the original
int INTER_cuSurfObjectDestroy( CUsurfObject surfObject ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUsurfObject> params = std::make_tuple(183 ,surfObject);
	DriverAPICall call = std::bind(ORIGINAL_cuSurfObjectDestroy ,surfObject);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUsurfObject> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuSurfObjectGetResourceDesc( CUDA_RESOURCE_DESC * pResDesc, CUsurfObject surfObject ) { }

// This is the call that will take the place of the original
int INTER_cuSurfObjectGetResourceDesc( CUDA_RESOURCE_DESC * pResDesc, CUsurfObject surfObject ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUDA_RESOURCE_DESC *,CUsurfObject> params = std::make_tuple(184 ,pResDesc,surfObject);
	DriverAPICall call = std::bind(ORIGINAL_cuSurfObjectGetResourceDesc ,pResDesc,surfObject);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUDA_RESOURCE_DESC *,CUsurfObject> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuDeviceCanAccessPeer( int * canAccessPeer, CUdevice dev, CUdevice peerDev ) { }

// This is the call that will take the place of the original
int INTER_cuDeviceCanAccessPeer( int * canAccessPeer, CUdevice dev, CUdevice peerDev ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,int *,CUdevice,CUdevice> params = std::make_tuple(185 ,canAccessPeer,dev,peerDev);
	DriverAPICall call = std::bind(ORIGINAL_cuDeviceCanAccessPeer ,canAccessPeer,dev,peerDev);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,int *,CUdevice,CUdevice> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuCtxEnablePeerAccess( CUcontext peerContext, unsigned int Flags ) { }

// This is the call that will take the place of the original
int INTER_cuCtxEnablePeerAccess( CUcontext peerContext, unsigned int Flags ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUcontext,unsigned int> params = std::make_tuple(186 ,peerContext,Flags);
	DriverAPICall call = std::bind(ORIGINAL_cuCtxEnablePeerAccess ,peerContext,Flags);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUcontext,unsigned int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuCtxDisablePeerAccess( CUcontext peerContext ) { }

// This is the call that will take the place of the original
int INTER_cuCtxDisablePeerAccess( CUcontext peerContext ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUcontext> params = std::make_tuple(187 ,peerContext);
	DriverAPICall call = std::bind(ORIGINAL_cuCtxDisablePeerAccess ,peerContext);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUcontext> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuGraphicsUnregisterResource( CUgraphicsResource resource ) { }

// This is the call that will take the place of the original
int INTER_cuGraphicsUnregisterResource( CUgraphicsResource resource ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUgraphicsResource> params = std::make_tuple(188 ,resource);
	DriverAPICall call = std::bind(ORIGINAL_cuGraphicsUnregisterResource ,resource);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUgraphicsResource> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuGraphicsSubResourceGetMappedArray( CUarray * pArray, CUgraphicsResource resource, unsigned int arrayIndex, unsigned int mipLevel ) { }

// This is the call that will take the place of the original
int INTER_cuGraphicsSubResourceGetMappedArray( CUarray * pArray, CUgraphicsResource resource, unsigned int arrayIndex, unsigned int mipLevel ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUarray *,CUgraphicsResource,unsigned int,unsigned int> params = std::make_tuple(189 ,pArray,resource,arrayIndex,mipLevel);
	DriverAPICall call = std::bind(ORIGINAL_cuGraphicsSubResourceGetMappedArray ,pArray,resource,arrayIndex,mipLevel);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUarray *,CUgraphicsResource,unsigned int,unsigned int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuGraphicsResourceGetMappedMipmappedArray( CUmipmappedArray * pMipmappedArray, CUgraphicsResource resource ) { }

// This is the call that will take the place of the original
int INTER_cuGraphicsResourceGetMappedMipmappedArray( CUmipmappedArray * pMipmappedArray, CUgraphicsResource resource ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUmipmappedArray *,CUgraphicsResource> params = std::make_tuple(190 ,pMipmappedArray,resource);
	DriverAPICall call = std::bind(ORIGINAL_cuGraphicsResourceGetMappedMipmappedArray ,pMipmappedArray,resource);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUmipmappedArray *,CUgraphicsResource> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuGraphicsResourceGetMappedPointer( CUdeviceptr * pDevPtr, size_t * pSize, CUgraphicsResource resource ) { }

// This is the call that will take the place of the original
int INTER_cuGraphicsResourceGetMappedPointer( CUdeviceptr * pDevPtr, size_t * pSize, CUgraphicsResource resource ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr *,size_t *,CUgraphicsResource> params = std::make_tuple(191 ,pDevPtr,pSize,resource);
	DriverAPICall call = std::bind(ORIGINAL_cuGraphicsResourceGetMappedPointer ,pDevPtr,pSize,resource);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr *,size_t *,CUgraphicsResource> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuGraphicsResourceSetMapFlags( CUgraphicsResource resource, unsigned int flags ) { }

// This is the call that will take the place of the original
int INTER_cuGraphicsResourceSetMapFlags( CUgraphicsResource resource, unsigned int flags ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUgraphicsResource,unsigned int> params = std::make_tuple(192 ,resource,flags);
	DriverAPICall call = std::bind(ORIGINAL_cuGraphicsResourceSetMapFlags ,resource,flags);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUgraphicsResource,unsigned int> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuGraphicsMapResources( unsigned int count, CUgraphicsResource * resources, CUstream hStream ) { }

// This is the call that will take the place of the original
int INTER_cuGraphicsMapResources( unsigned int count, CUgraphicsResource * resources, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,unsigned int,CUgraphicsResource *,CUstream> params = std::make_tuple(193 ,count,resources,hStream);
	DriverAPICall call = std::bind(ORIGINAL_cuGraphicsMapResources ,count,resources,hStream);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,unsigned int,CUgraphicsResource *,CUstream> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuGraphicsUnmapResources( unsigned int count, CUgraphicsResource * resources, CUstream hStream ) { }

// This is the call that will take the place of the original
int INTER_cuGraphicsUnmapResources( unsigned int count, CUgraphicsResource * resources, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,unsigned int,CUgraphicsResource *,CUstream> params = std::make_tuple(194 ,count,resources,hStream);
	DriverAPICall call = std::bind(ORIGINAL_cuGraphicsUnmapResources ,count,resources,hStream);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,unsigned int,CUgraphicsResource *,CUstream> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuGetExportTable( const void * * ppExportTable, const CUuuid * pExportTableId ) { }

// This is the call that will take the place of the original
int INTER_cuGetExportTable( const void * * ppExportTable, const CUuuid * pExportTableId ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,const void * *,const CUuuid *> params = std::make_tuple(195 ,ppExportTable,pExportTableId);
	DriverAPICall call = std::bind(ORIGINAL_cuGetExportTable ,ppExportTable,pExportTableId);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,const void * *,const CUuuid *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuTexRefSetAddress2D_v2( CUtexref hTexRef, const CUDA_ARRAY_DESCRIPTOR * desc, CUdeviceptr dptr, size_t Pitch ) { }

// This is the call that will take the place of the original
int INTER_cuTexRefSetAddress2D_v2( CUtexref hTexRef, const CUDA_ARRAY_DESCRIPTOR * desc, CUdeviceptr dptr, size_t Pitch ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUtexref,const CUDA_ARRAY_DESCRIPTOR *,CUdeviceptr,size_t> params = std::make_tuple(196 ,hTexRef,desc,dptr,Pitch);
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefSetAddress2D_v2 ,hTexRef,desc,dptr,Pitch);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUtexref,const CUDA_ARRAY_DESCRIPTOR *,CUdeviceptr,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpyHtoD_v2( CUdeviceptr dstDevice, const void * srcHost, size_t ByteCount ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpyHtoD_v2( CUdeviceptr dstDevice, const void * srcHost, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr,const void *,size_t> params = std::make_tuple(197 ,dstDevice,srcHost,ByteCount);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyHtoD_v2 ,dstDevice,srcHost,ByteCount);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr,const void *,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpyDtoH_v2( void * dstHost, CUdeviceptr srcDevice, size_t ByteCount ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpyDtoH_v2( void * dstHost, CUdeviceptr srcDevice, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,void *,CUdeviceptr,size_t> params = std::make_tuple(198 ,dstHost,srcDevice,ByteCount);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyDtoH_v2 ,dstHost,srcDevice,ByteCount);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,void *,CUdeviceptr,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpyDtoD_v2( CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpyDtoD_v2( CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr,CUdeviceptr,size_t> params = std::make_tuple(199 ,dstDevice,srcDevice,ByteCount);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyDtoD_v2 ,dstDevice,srcDevice,ByteCount);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr,CUdeviceptr,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpyDtoA_v2( CUarray dstArray, size_t dstOffset, CUdeviceptr srcDevice, size_t ByteCount ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpyDtoA_v2( CUarray dstArray, size_t dstOffset, CUdeviceptr srcDevice, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUarray,size_t,CUdeviceptr,size_t> params = std::make_tuple(200 ,dstArray,dstOffset,srcDevice,ByteCount);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyDtoA_v2 ,dstArray,dstOffset,srcDevice,ByteCount);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUarray,size_t,CUdeviceptr,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpyAtoD_v2( CUdeviceptr dstDevice, CUarray srcArray, size_t srcOffset, size_t ByteCount ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpyAtoD_v2( CUdeviceptr dstDevice, CUarray srcArray, size_t srcOffset, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr,CUarray,size_t,size_t> params = std::make_tuple(201 ,dstDevice,srcArray,srcOffset,ByteCount);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyAtoD_v2 ,dstDevice,srcArray,srcOffset,ByteCount);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr,CUarray,size_t,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpyHtoA_v2( CUarray dstArray, size_t dstOffset, const void * srcHost, size_t ByteCount ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpyHtoA_v2( CUarray dstArray, size_t dstOffset, const void * srcHost, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUarray,size_t,const void *,size_t> params = std::make_tuple(202 ,dstArray,dstOffset,srcHost,ByteCount);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyHtoA_v2 ,dstArray,dstOffset,srcHost,ByteCount);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUarray,size_t,const void *,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpyAtoH_v2( void * dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpyAtoH_v2( void * dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,void *,CUarray,size_t,size_t> params = std::make_tuple(203 ,dstHost,srcArray,srcOffset,ByteCount);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyAtoH_v2 ,dstHost,srcArray,srcOffset,ByteCount);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,void *,CUarray,size_t,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpyAtoA_v2( CUarray dstArray, size_t dstOffset, CUarray srcArray, size_t srcOffset, size_t ByteCount ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpyAtoA_v2( CUarray dstArray, size_t dstOffset, CUarray srcArray, size_t srcOffset, size_t ByteCount ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUarray,size_t,CUarray,size_t,size_t> params = std::make_tuple(204 ,dstArray,dstOffset,srcArray,srcOffset,ByteCount);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyAtoA_v2 ,dstArray,dstOffset,srcArray,srcOffset,ByteCount);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUarray,size_t,CUarray,size_t,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpyHtoAAsync_v2( CUarray dstArray, size_t dstOffset, const void * srcHost, size_t ByteCount, CUstream hStream ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpyHtoAAsync_v2( CUarray dstArray, size_t dstOffset, const void * srcHost, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUarray,size_t,const void *,size_t,CUstream> params = std::make_tuple(205 ,dstArray,dstOffset,srcHost,ByteCount,hStream);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyHtoAAsync_v2 ,dstArray,dstOffset,srcHost,ByteCount,hStream);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUarray,size_t,const void *,size_t,CUstream> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpyAtoHAsync_v2( void * dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount, CUstream hStream ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpyAtoHAsync_v2( void * dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,void *,CUarray,size_t,size_t,CUstream> params = std::make_tuple(206 ,dstHost,srcArray,srcOffset,ByteCount,hStream);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyAtoHAsync_v2 ,dstHost,srcArray,srcOffset,ByteCount,hStream);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,void *,CUarray,size_t,size_t,CUstream> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpy2D_v2( const CUDA_MEMCPY2D * pCopy ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpy2D_v2( const CUDA_MEMCPY2D * pCopy ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,const CUDA_MEMCPY2D *> params = std::make_tuple(207 ,pCopy);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpy2D_v2 ,pCopy);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,const CUDA_MEMCPY2D *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpy2DUnaligned_v2( const CUDA_MEMCPY2D * pCopy ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpy2DUnaligned_v2( const CUDA_MEMCPY2D * pCopy ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,const CUDA_MEMCPY2D *> params = std::make_tuple(208 ,pCopy);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpy2DUnaligned_v2 ,pCopy);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,const CUDA_MEMCPY2D *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpy3D_v2( const CUDA_MEMCPY3D * pCopy ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpy3D_v2( const CUDA_MEMCPY3D * pCopy ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,const CUDA_MEMCPY3D *> params = std::make_tuple(209 ,pCopy);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpy3D_v2 ,pCopy);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,const CUDA_MEMCPY3D *> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpyHtoDAsync_v2( CUdeviceptr dstDevice, const void * srcHost, size_t ByteCount, CUstream hStream ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpyHtoDAsync_v2( CUdeviceptr dstDevice, const void * srcHost, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr,const void *,size_t,CUstream> params = std::make_tuple(210 ,dstDevice,srcHost,ByteCount,hStream);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyHtoDAsync_v2 ,dstDevice,srcHost,ByteCount,hStream);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr,const void *,size_t,CUstream> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpyDtoHAsync_v2( void * dstHost, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpyDtoHAsync_v2( void * dstHost, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,void *,CUdeviceptr,size_t,CUstream> params = std::make_tuple(211 ,dstHost,srcDevice,ByteCount,hStream);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyDtoHAsync_v2 ,dstHost,srcDevice,ByteCount,hStream);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,void *,CUdeviceptr,size_t,CUstream> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpyDtoDAsync_v2( CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpyDtoDAsync_v2( CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr,CUdeviceptr,size_t,CUstream> params = std::make_tuple(212 ,dstDevice,srcDevice,ByteCount,hStream);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyDtoDAsync_v2 ,dstDevice,srcDevice,ByteCount,hStream);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr,CUdeviceptr,size_t,CUstream> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpy2DAsync_v2( const CUDA_MEMCPY2D * pCopy, CUstream hStream ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpy2DAsync_v2( const CUDA_MEMCPY2D * pCopy, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,const CUDA_MEMCPY2D *,CUstream> params = std::make_tuple(213 ,pCopy,hStream);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpy2DAsync_v2 ,pCopy,hStream);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,const CUDA_MEMCPY2D *,CUstream> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemcpy3DAsync_v2( const CUDA_MEMCPY3D * pCopy, CUstream hStream ) { }

// This is the call that will take the place of the original
int INTER_cuMemcpy3DAsync_v2( const CUDA_MEMCPY3D * pCopy, CUstream hStream ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,const CUDA_MEMCPY3D *,CUstream> params = std::make_tuple(214 ,pCopy,hStream);
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpy3DAsync_v2 ,pCopy,hStream);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,const CUDA_MEMCPY3D *,CUstream> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemsetD8_v2( CUdeviceptr dstDevice, unsigned char uc, size_t N ) { }

// This is the call that will take the place of the original
int INTER_cuMemsetD8_v2( CUdeviceptr dstDevice, unsigned char uc, size_t N ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr,unsigned char,size_t> params = std::make_tuple(215 ,dstDevice,uc,N);
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD8_v2 ,dstDevice,uc,N);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr,unsigned char,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemsetD16_v2( CUdeviceptr dstDevice, unsigned short us, size_t N ) { }

// This is the call that will take the place of the original
int INTER_cuMemsetD16_v2( CUdeviceptr dstDevice, unsigned short us, size_t N ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr,unsigned short,size_t> params = std::make_tuple(216 ,dstDevice,us,N);
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD16_v2 ,dstDevice,us,N);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr,unsigned short,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemsetD32_v2( CUdeviceptr dstDevice, unsigned int ui, size_t N ) { }

// This is the call that will take the place of the original
int INTER_cuMemsetD32_v2( CUdeviceptr dstDevice, unsigned int ui, size_t N ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr,unsigned int,size_t> params = std::make_tuple(217 ,dstDevice,ui,N);
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD32_v2 ,dstDevice,ui,N);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr,unsigned int,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemsetD2D8_v2( CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height ) { }

// This is the call that will take the place of the original
int INTER_cuMemsetD2D8_v2( CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr,size_t,unsigned char,size_t,size_t> params = std::make_tuple(218 ,dstDevice,dstPitch,uc,Width,Height);
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD2D8_v2 ,dstDevice,dstPitch,uc,Width,Height);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr,size_t,unsigned char,size_t,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemsetD2D16_v2( CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height ) { }

// This is the call that will take the place of the original
int INTER_cuMemsetD2D16_v2( CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr,size_t,unsigned short,size_t,size_t> params = std::make_tuple(219 ,dstDevice,dstPitch,us,Width,Height);
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD2D16_v2 ,dstDevice,dstPitch,us,Width,Height);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr,size_t,unsigned short,size_t,size_t> >(call, params);
	return ret;
}
// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;

// This is the prototype of the file
int ORIGINAL_cuMemsetD2D32_v2( CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height ) { }

// This is the call that will take the place of the original
int INTER_cuMemsetD2D32_v2( CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height ) {
	// Build the instriment factory
	BUILD_FACTORY

	std::tuple<int,CUdeviceptr,size_t,unsigned int,size_t,size_t> params = std::make_tuple(220 ,dstDevice,dstPitch,ui,Width,Height);
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD2D32_v2 ,dstDevice,dstPitch,ui,Width,Height);
	int ret = FACTORY_PTR->PerformAction<std::tuple<int,CUdeviceptr,size_t,unsigned int,size_t,size_t> >(call, params);
	return ret;
}

}