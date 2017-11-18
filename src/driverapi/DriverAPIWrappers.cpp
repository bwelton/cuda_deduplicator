#include "DriverAPIHeader.h"
#include <tuple>
#include "DriverWrapperBase.h"
#include "DriverWrapperFactory.h"
#include "cuda.h"
#include <vector>
std::shared_ptr<DriverWrapperFactory> DriverFactory;
extern "C" {// typedef boost::function<int(void)> DriverAPICall;
// std::shared_ptr<InstrumentFactory> InstFactory;


void CheckInit_DriverAPI() {
	
}

// This is the prototype of the file
int ORIGINAL_cuGetErrorString( CUresult error, const char * * pStr ) { }

// This is the call that will take the place of the original
int INTER_cuGetErrorString( CUresult error, const char * * pStr ) {
	// Build the instriment factory
	BUILD_FACTORY
	std::vector<void *> params = { (void *)&error,(void *)&pStr };
	// std::tuple<int,CUresult,const char * *> params = std::make_tuple(0 ,error,pStr);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(0, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuGetErrorString ,error,pStr);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&error,(void *)&pStr };
	// std::tuple<int,CUresult,const char * *> params = std::make_tuple(1 ,error,pStr);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(1, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuGetErrorName ,error,pStr);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&Flags };
	// std::tuple<int,unsigned int> params = std::make_tuple(2 ,Flags);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(2, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuInit ,Flags);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&driverVersion };
	// std::tuple<int,int *> params = std::make_tuple(3 ,driverVersion);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(3, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuDriverGetVersion ,driverVersion);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&device,(void *)&ordinal };
	// std::tuple<int,CUdevice *,int> params = std::make_tuple(4 ,device,ordinal);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(4, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuDeviceGet ,device,ordinal);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&count };
	// std::tuple<int,int *> params = std::make_tuple(5 ,count);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(5, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuDeviceGetCount ,count);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&name,(void *)&len,(void *)&dev };
	// std::tuple<int,char *,int,CUdevice> params = std::make_tuple(6 ,name,len,dev);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(6, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuDeviceGetName ,name,len,dev);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&bytes,(void *)&dev };
	// std::tuple<int,size_t *,CUdevice> params = std::make_tuple(7 ,bytes,dev);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(7, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuDeviceTotalMem ,bytes,dev);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pi,(void *)&attrib,(void *)&dev };
	// std::tuple<int,int *,CUdevice_attribute,CUdevice> params = std::make_tuple(8 ,pi,attrib,dev);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(8, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuDeviceGetAttribute ,pi,attrib,dev);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&prop,(void *)&dev };
	// std::tuple<int,CUdevprop *,CUdevice> params = std::make_tuple(9 ,prop,dev);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(9, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuDeviceGetProperties ,prop,dev);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&major,(void *)&minor,(void *)&dev };
	// std::tuple<int,int *,int *,CUdevice> params = std::make_tuple(10 ,major,minor,dev);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(10, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuDeviceComputeCapability ,major,minor,dev);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pctx,(void *)&dev };
	// std::tuple<int,CUcontext *,CUdevice> params = std::make_tuple(11 ,pctx,dev);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(11, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuDevicePrimaryCtxRetain ,pctx,dev);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dev };
	// std::tuple<int,CUdevice> params = std::make_tuple(12 ,dev);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(12, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuDevicePrimaryCtxRelease ,dev);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dev,(void *)&flags };
	// std::tuple<int,CUdevice,unsigned int> params = std::make_tuple(13 ,dev,flags);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(13, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuDevicePrimaryCtxSetFlags ,dev,flags);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dev,(void *)&flags,(void *)&active };
	// std::tuple<int,CUdevice,unsigned int *,int *> params = std::make_tuple(14 ,dev,flags,active);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(14, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuDevicePrimaryCtxGetState ,dev,flags,active);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dev };
	// std::tuple<int,CUdevice> params = std::make_tuple(15 ,dev);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(15, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuDevicePrimaryCtxReset ,dev);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pctx,(void *)&flags,(void *)&dev };
	// std::tuple<int,CUcontext *,unsigned int,CUdevice> params = std::make_tuple(16 ,pctx,flags,dev);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(16, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuCtxCreate ,pctx,flags,dev);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&ctx };
	// std::tuple<int,CUcontext> params = std::make_tuple(17 ,ctx);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(17, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuCtxDestroy ,ctx);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&ctx };
	// std::tuple<int,CUcontext> params = std::make_tuple(18 ,ctx);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(18, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuCtxPushCurrent ,ctx);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pctx };
	// std::tuple<int,CUcontext *> params = std::make_tuple(19 ,pctx);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(19, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuCtxPopCurrent ,pctx);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&ctx };
	// std::tuple<int,CUcontext> params = std::make_tuple(20 ,ctx);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(20, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuCtxSetCurrent ,ctx);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pctx };
	// std::tuple<int,CUcontext *> params = std::make_tuple(21 ,pctx);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(21, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuCtxGetCurrent ,pctx);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&device };
	// std::tuple<int,CUdevice *> params = std::make_tuple(22 ,device);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(22, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuCtxGetDevice ,device);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&flags };
	// std::tuple<int,unsigned int *> params = std::make_tuple(23 ,flags);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(23, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuCtxGetFlags ,flags);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = {  };
	// std::tuple<int> params = std::make_tuple(24 );
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(24, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuCtxSynchronize );
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&limit,(void *)&value };
	// std::tuple<int,CUlimit,size_t> params = std::make_tuple(25 ,limit,value);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(25, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuCtxSetLimit ,limit,value);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pvalue,(void *)&limit };
	// std::tuple<int,size_t *,CUlimit> params = std::make_tuple(26 ,pvalue,limit);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(26, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuCtxGetLimit ,pvalue,limit);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pconfig };
	// std::tuple<int,CUfunc_cache *> params = std::make_tuple(27 ,pconfig);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(27, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuCtxGetCacheConfig ,pconfig);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&config };
	// std::tuple<int,CUfunc_cache> params = std::make_tuple(28 ,config);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(28, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuCtxSetCacheConfig ,config);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pConfig };
	// std::tuple<int,CUsharedconfig *> params = std::make_tuple(29 ,pConfig);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(29, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuCtxGetSharedMemConfig ,pConfig);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&config };
	// std::tuple<int,CUsharedconfig> params = std::make_tuple(30 ,config);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(30, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuCtxSetSharedMemConfig ,config);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&ctx,(void *)&version };
	// std::tuple<int,CUcontext,unsigned int *> params = std::make_tuple(31 ,ctx,version);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(31, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuCtxGetApiVersion ,ctx,version);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&leastPriority,(void *)&greatestPriority };
	// std::tuple<int,int *,int *> params = std::make_tuple(32 ,leastPriority,greatestPriority);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(32, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuCtxGetStreamPriorityRange ,leastPriority,greatestPriority);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pctx,(void *)&flags };
	// std::tuple<int,CUcontext *,unsigned int> params = std::make_tuple(33 ,pctx,flags);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(33, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuCtxAttach ,pctx,flags);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&ctx };
	// std::tuple<int,CUcontext> params = std::make_tuple(34 ,ctx);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(34, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuCtxDetach ,ctx);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&module,(void *)&fname };
	// std::tuple<int,CUmodule *,const char *> params = std::make_tuple(35 ,module,fname);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(35, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuModuleLoad ,module,fname);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&module,(void *)&image };
	// std::tuple<int,CUmodule *,const void *> params = std::make_tuple(36 ,module,image);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(36, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuModuleLoadData ,module,image);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&module,(void *)&image,(void *)&numOptions,(void *)&options,(void *)&optionValues };
	// std::tuple<int,CUmodule *,const void *,unsigned int,CUjit_option *,void * *> params = std::make_tuple(37 ,module,image,numOptions,options,optionValues);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(37, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuModuleLoadDataEx ,module,image,numOptions,options,optionValues);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&module,(void *)&fatCubin };
	// std::tuple<int,CUmodule *,const void *> params = std::make_tuple(38 ,module,fatCubin);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(38, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuModuleLoadFatBinary ,module,fatCubin);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hmod };
	// std::tuple<int,CUmodule> params = std::make_tuple(39 ,hmod);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(39, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuModuleUnload ,hmod);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hfunc,(void *)&hmod,(void *)&name };
	// std::tuple<int,CUfunction *,CUmodule,const char *> params = std::make_tuple(40 ,hfunc,hmod,name);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(40, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuModuleGetFunction ,hfunc,hmod,name);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dptr,(void *)&bytes,(void *)&hmod,(void *)&name };
	// std::tuple<int,CUdeviceptr *,size_t *,CUmodule,const char *> params = std::make_tuple(41 ,dptr,bytes,hmod,name);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(41, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuModuleGetGlobal ,dptr,bytes,hmod,name);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pTexRef,(void *)&hmod,(void *)&name };
	// std::tuple<int,CUtexref *,CUmodule,const char *> params = std::make_tuple(42 ,pTexRef,hmod,name);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(42, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuModuleGetTexRef ,pTexRef,hmod,name);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pSurfRef,(void *)&hmod,(void *)&name };
	// std::tuple<int,CUsurfref *,CUmodule,const char *> params = std::make_tuple(43 ,pSurfRef,hmod,name);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(43, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuModuleGetSurfRef ,pSurfRef,hmod,name);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&numOptions,(void *)&options,(void *)&optionValues,(void *)&stateOut };
	// std::tuple<int,unsigned int,CUjit_option *,void * *,CUlinkState *> params = std::make_tuple(44 ,numOptions,options,optionValues,stateOut);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(44, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuLinkCreate ,numOptions,options,optionValues,stateOut);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&state,(void *)&type,(void *)&data,(void *)&size,(void *)&name,(void *)&numOptions,(void *)&options,(void *)&optionValues };
	// std::tuple<int,CUlinkState,CUjitInputType,void *,size_t,const char *,unsigned int,CUjit_option *,void * *> params = std::make_tuple(45 ,state,type,data,size,name,numOptions,options,optionValues);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(45, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuLinkAddData ,state,type,data,size,name,numOptions,options,optionValues);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&state,(void *)&type,(void *)&path,(void *)&numOptions,(void *)&options,(void *)&optionValues };
	// std::tuple<int,CUlinkState,CUjitInputType,const char *,unsigned int,CUjit_option *,void * *> params = std::make_tuple(46 ,state,type,path,numOptions,options,optionValues);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(46, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuLinkAddFile ,state,type,path,numOptions,options,optionValues);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&state,(void *)&cubinOut,(void *)&sizeOut };
	// std::tuple<int,CUlinkState,void * *,size_t *> params = std::make_tuple(47 ,state,cubinOut,sizeOut);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(47, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuLinkComplete ,state,cubinOut,sizeOut);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&state };
	// std::tuple<int,CUlinkState> params = std::make_tuple(48 ,state);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(48, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuLinkDestroy ,state);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&free,(void *)&total };
	// std::tuple<int,size_t *,size_t *> params = std::make_tuple(49 ,free,total);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(49, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemGetInfo ,free,total);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dptr,(void *)&bytesize };
	// std::tuple<int,CUdeviceptr *,size_t> params = std::make_tuple(50 ,dptr,bytesize);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(50, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemAlloc ,dptr,bytesize);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dptr,(void *)&pPitch,(void *)&WidthInBytes,(void *)&Height,(void *)&ElementSizeBytes };
	// std::tuple<int,CUdeviceptr *,size_t *,size_t,size_t,unsigned int> params = std::make_tuple(51 ,dptr,pPitch,WidthInBytes,Height,ElementSizeBytes);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(51, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemAllocPitch ,dptr,pPitch,WidthInBytes,Height,ElementSizeBytes);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dptr };
	// std::tuple<int,CUdeviceptr> params = std::make_tuple(52 ,dptr);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(52, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemFree ,dptr);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pbase,(void *)&psize,(void *)&dptr };
	// std::tuple<int,CUdeviceptr *,size_t *,CUdeviceptr> params = std::make_tuple(53 ,pbase,psize,dptr);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(53, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemGetAddressRange ,pbase,psize,dptr);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pp,(void *)&bytesize };
	// std::tuple<int,void * *,size_t> params = std::make_tuple(54 ,pp,bytesize);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(54, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemAllocHost ,pp,bytesize);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&p };
	// std::tuple<int,void *> params = std::make_tuple(55 ,p);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(55, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemFreeHost ,p);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pp,(void *)&bytesize,(void *)&Flags };
	// std::tuple<int,void * *,size_t,unsigned int> params = std::make_tuple(56 ,pp,bytesize,Flags);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(56, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemHostAlloc ,pp,bytesize,Flags);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pdptr,(void *)&p,(void *)&Flags };
	// std::tuple<int,CUdeviceptr *,void *,unsigned int> params = std::make_tuple(57 ,pdptr,p,Flags);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(57, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemHostGetDevicePointer ,pdptr,p,Flags);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pFlags,(void *)&p };
	// std::tuple<int,unsigned int *,void *> params = std::make_tuple(58 ,pFlags,p);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(58, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemHostGetFlags ,pFlags,p);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dptr,(void *)&bytesize,(void *)&flags };
	// std::tuple<int,CUdeviceptr *,size_t,unsigned int> params = std::make_tuple(59 ,dptr,bytesize,flags);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(59, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemAllocManaged ,dptr,bytesize,flags);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dev,(void *)&pciBusId };
	// std::tuple<int,CUdevice *,const char *> params = std::make_tuple(60 ,dev,pciBusId);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(60, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuDeviceGetByPCIBusId ,dev,pciBusId);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pciBusId,(void *)&len,(void *)&dev };
	// std::tuple<int,char *,int,CUdevice> params = std::make_tuple(61 ,pciBusId,len,dev);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(61, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuDeviceGetPCIBusId ,pciBusId,len,dev);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pHandle,(void *)&event };
	// std::tuple<int,CUipcEventHandle *,CUevent> params = std::make_tuple(62 ,pHandle,event);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(62, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuIpcGetEventHandle ,pHandle,event);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&phEvent,(void *)&handle };
	// std::tuple<int,CUevent *,CUipcEventHandle> params = std::make_tuple(63 ,phEvent,handle);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(63, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuIpcOpenEventHandle ,phEvent,handle);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pHandle,(void *)&dptr };
	// std::tuple<int,CUipcMemHandle *,CUdeviceptr> params = std::make_tuple(64 ,pHandle,dptr);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(64, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuIpcGetMemHandle ,pHandle,dptr);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pdptr,(void *)&handle,(void *)&Flags };
	// std::tuple<int,CUdeviceptr *,CUipcMemHandle,unsigned int> params = std::make_tuple(65 ,pdptr,handle,Flags);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(65, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuIpcOpenMemHandle ,pdptr,handle,Flags);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dptr };
	// std::tuple<int,CUdeviceptr> params = std::make_tuple(66 ,dptr);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(66, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuIpcCloseMemHandle ,dptr);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&p,(void *)&bytesize,(void *)&Flags };
	// std::tuple<int,void *,size_t,unsigned int> params = std::make_tuple(67 ,p,bytesize,Flags);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(67, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemHostRegister ,p,bytesize,Flags);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&p };
	// std::tuple<int,void *> params = std::make_tuple(68 ,p);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(68, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemHostUnregister ,p);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dst,(void *)&src,(void *)&ByteCount };
	// std::tuple<int,CUdeviceptr,CUdeviceptr,size_t> params = std::make_tuple(69 ,dst,src,ByteCount);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(69, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpy ,dst,src,ByteCount);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstDevice,(void *)&dstContext,(void *)&srcDevice,(void *)&srcContext,(void *)&ByteCount };
	// std::tuple<int,CUdeviceptr,CUcontext,CUdeviceptr,CUcontext,size_t> params = std::make_tuple(70 ,dstDevice,dstContext,srcDevice,srcContext,ByteCount);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(70, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyPeer ,dstDevice,dstContext,srcDevice,srcContext,ByteCount);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstDevice,(void *)&srcHost,(void *)&ByteCount };
	// std::tuple<int,CUdeviceptr,const void *,size_t> params = std::make_tuple(71 ,dstDevice,srcHost,ByteCount);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(71, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyHtoD ,dstDevice,srcHost,ByteCount);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstHost,(void *)&srcDevice,(void *)&ByteCount };
	// std::tuple<int,void *,CUdeviceptr,size_t> params = std::make_tuple(72 ,dstHost,srcDevice,ByteCount);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(72, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyDtoH ,dstHost,srcDevice,ByteCount);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstDevice,(void *)&srcDevice,(void *)&ByteCount };
	// std::tuple<int,CUdeviceptr,CUdeviceptr,size_t> params = std::make_tuple(73 ,dstDevice,srcDevice,ByteCount);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(73, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyDtoD ,dstDevice,srcDevice,ByteCount);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstArray,(void *)&dstOffset,(void *)&srcDevice,(void *)&ByteCount };
	// std::tuple<int,CUarray,size_t,CUdeviceptr,size_t> params = std::make_tuple(74 ,dstArray,dstOffset,srcDevice,ByteCount);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(74, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyDtoA ,dstArray,dstOffset,srcDevice,ByteCount);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstDevice,(void *)&srcArray,(void *)&srcOffset,(void *)&ByteCount };
	// std::tuple<int,CUdeviceptr,CUarray,size_t,size_t> params = std::make_tuple(75 ,dstDevice,srcArray,srcOffset,ByteCount);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(75, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyAtoD ,dstDevice,srcArray,srcOffset,ByteCount);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstArray,(void *)&dstOffset,(void *)&srcHost,(void *)&ByteCount };
	// std::tuple<int,CUarray,size_t,const void *,size_t> params = std::make_tuple(76 ,dstArray,dstOffset,srcHost,ByteCount);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(76, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyHtoA ,dstArray,dstOffset,srcHost,ByteCount);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstHost,(void *)&srcArray,(void *)&srcOffset,(void *)&ByteCount };
	// std::tuple<int,void *,CUarray,size_t,size_t> params = std::make_tuple(77 ,dstHost,srcArray,srcOffset,ByteCount);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(77, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyAtoH ,dstHost,srcArray,srcOffset,ByteCount);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstArray,(void *)&dstOffset,(void *)&srcArray,(void *)&srcOffset,(void *)&ByteCount };
	// std::tuple<int,CUarray,size_t,CUarray,size_t,size_t> params = std::make_tuple(78 ,dstArray,dstOffset,srcArray,srcOffset,ByteCount);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(78, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyAtoA ,dstArray,dstOffset,srcArray,srcOffset,ByteCount);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pCopy };
	// std::tuple<int,const CUDA_MEMCPY2D *> params = std::make_tuple(79 ,pCopy);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(79, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpy2D ,pCopy);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pCopy };
	// std::tuple<int,const CUDA_MEMCPY2D *> params = std::make_tuple(80 ,pCopy);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(80, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpy2DUnaligned ,pCopy);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pCopy };
	// std::tuple<int,const CUDA_MEMCPY3D *> params = std::make_tuple(81 ,pCopy);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(81, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpy3D ,pCopy);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pCopy };
	// std::tuple<int,const CUDA_MEMCPY3D_PEER *> params = std::make_tuple(82 ,pCopy);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(82, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpy3DPeer ,pCopy);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dst,(void *)&src,(void *)&ByteCount,(void *)&hStream };
	// std::tuple<int,CUdeviceptr,CUdeviceptr,size_t,CUstream> params = std::make_tuple(83 ,dst,src,ByteCount,hStream);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(83, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyAsync ,dst,src,ByteCount,hStream);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstDevice,(void *)&dstContext,(void *)&srcDevice,(void *)&srcContext,(void *)&ByteCount,(void *)&hStream };
	// std::tuple<int,CUdeviceptr,CUcontext,CUdeviceptr,CUcontext,size_t,CUstream> params = std::make_tuple(84 ,dstDevice,dstContext,srcDevice,srcContext,ByteCount,hStream);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(84, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyPeerAsync ,dstDevice,dstContext,srcDevice,srcContext,ByteCount,hStream);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstDevice,(void *)&srcHost,(void *)&ByteCount,(void *)&hStream };
	// std::tuple<int,CUdeviceptr,const void *,size_t,CUstream> params = std::make_tuple(85 ,dstDevice,srcHost,ByteCount,hStream);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(85, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyHtoDAsync ,dstDevice,srcHost,ByteCount,hStream);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstHost,(void *)&srcDevice,(void *)&ByteCount,(void *)&hStream };
	// std::tuple<int,void *,CUdeviceptr,size_t,CUstream> params = std::make_tuple(86 ,dstHost,srcDevice,ByteCount,hStream);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(86, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyDtoHAsync ,dstHost,srcDevice,ByteCount,hStream);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstDevice,(void *)&srcDevice,(void *)&ByteCount,(void *)&hStream };
	// std::tuple<int,CUdeviceptr,CUdeviceptr,size_t,CUstream> params = std::make_tuple(87 ,dstDevice,srcDevice,ByteCount,hStream);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(87, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyDtoDAsync ,dstDevice,srcDevice,ByteCount,hStream);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstArray,(void *)&dstOffset,(void *)&srcHost,(void *)&ByteCount,(void *)&hStream };
	// std::tuple<int,CUarray,size_t,const void *,size_t,CUstream> params = std::make_tuple(88 ,dstArray,dstOffset,srcHost,ByteCount,hStream);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(88, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyHtoAAsync ,dstArray,dstOffset,srcHost,ByteCount,hStream);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstHost,(void *)&srcArray,(void *)&srcOffset,(void *)&ByteCount,(void *)&hStream };
	// std::tuple<int,void *,CUarray,size_t,size_t,CUstream> params = std::make_tuple(89 ,dstHost,srcArray,srcOffset,ByteCount,hStream);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(89, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyAtoHAsync ,dstHost,srcArray,srcOffset,ByteCount,hStream);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pCopy,(void *)&hStream };
	// std::tuple<int,const CUDA_MEMCPY2D *,CUstream> params = std::make_tuple(90 ,pCopy,hStream);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(90, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpy2DAsync ,pCopy,hStream);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pCopy,(void *)&hStream };
	// std::tuple<int,const CUDA_MEMCPY3D *,CUstream> params = std::make_tuple(91 ,pCopy,hStream);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(91, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpy3DAsync ,pCopy,hStream);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pCopy,(void *)&hStream };
	// std::tuple<int,const CUDA_MEMCPY3D_PEER *,CUstream> params = std::make_tuple(92 ,pCopy,hStream);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(92, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpy3DPeerAsync ,pCopy,hStream);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstDevice,(void *)&uc,(void *)&N };
	// std::tuple<int,CUdeviceptr,unsigned char,size_t> params = std::make_tuple(93 ,dstDevice,uc,N);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(93, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD8 ,dstDevice,uc,N);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstDevice,(void *)&us,(void *)&N };
	// std::tuple<int,CUdeviceptr,unsigned short,size_t> params = std::make_tuple(94 ,dstDevice,us,N);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(94, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD16 ,dstDevice,us,N);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstDevice,(void *)&ui,(void *)&N };
	// std::tuple<int,CUdeviceptr,unsigned int,size_t> params = std::make_tuple(95 ,dstDevice,ui,N);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(95, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD32 ,dstDevice,ui,N);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstDevice,(void *)&dstPitch,(void *)&uc,(void *)&Width,(void *)&Height };
	// std::tuple<int,CUdeviceptr,size_t,unsigned char,size_t,size_t> params = std::make_tuple(96 ,dstDevice,dstPitch,uc,Width,Height);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(96, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD2D8 ,dstDevice,dstPitch,uc,Width,Height);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstDevice,(void *)&dstPitch,(void *)&us,(void *)&Width,(void *)&Height };
	// std::tuple<int,CUdeviceptr,size_t,unsigned short,size_t,size_t> params = std::make_tuple(97 ,dstDevice,dstPitch,us,Width,Height);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(97, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD2D16 ,dstDevice,dstPitch,us,Width,Height);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstDevice,(void *)&dstPitch,(void *)&ui,(void *)&Width,(void *)&Height };
	// std::tuple<int,CUdeviceptr,size_t,unsigned int,size_t,size_t> params = std::make_tuple(98 ,dstDevice,dstPitch,ui,Width,Height);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(98, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD2D32 ,dstDevice,dstPitch,ui,Width,Height);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstDevice,(void *)&uc,(void *)&N,(void *)&hStream };
	// std::tuple<int,CUdeviceptr,unsigned char,size_t,CUstream> params = std::make_tuple(99 ,dstDevice,uc,N,hStream);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(99, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD8Async ,dstDevice,uc,N,hStream);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstDevice,(void *)&us,(void *)&N,(void *)&hStream };
	// std::tuple<int,CUdeviceptr,unsigned short,size_t,CUstream> params = std::make_tuple(100 ,dstDevice,us,N,hStream);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(100, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD16Async ,dstDevice,us,N,hStream);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstDevice,(void *)&ui,(void *)&N,(void *)&hStream };
	// std::tuple<int,CUdeviceptr,unsigned int,size_t,CUstream> params = std::make_tuple(101 ,dstDevice,ui,N,hStream);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(101, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD32Async ,dstDevice,ui,N,hStream);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstDevice,(void *)&dstPitch,(void *)&uc,(void *)&Width,(void *)&Height,(void *)&hStream };
	// std::tuple<int,CUdeviceptr,size_t,unsigned char,size_t,size_t,CUstream> params = std::make_tuple(102 ,dstDevice,dstPitch,uc,Width,Height,hStream);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(102, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD2D8Async ,dstDevice,dstPitch,uc,Width,Height,hStream);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstDevice,(void *)&dstPitch,(void *)&us,(void *)&Width,(void *)&Height,(void *)&hStream };
	// std::tuple<int,CUdeviceptr,size_t,unsigned short,size_t,size_t,CUstream> params = std::make_tuple(103 ,dstDevice,dstPitch,us,Width,Height,hStream);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(103, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD2D16Async ,dstDevice,dstPitch,us,Width,Height,hStream);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstDevice,(void *)&dstPitch,(void *)&ui,(void *)&Width,(void *)&Height,(void *)&hStream };
	// std::tuple<int,CUdeviceptr,size_t,unsigned int,size_t,size_t,CUstream> params = std::make_tuple(104 ,dstDevice,dstPitch,ui,Width,Height,hStream);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(104, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD2D32Async ,dstDevice,dstPitch,ui,Width,Height,hStream);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pHandle,(void *)&pAllocateArray };
	// std::tuple<int,CUarray *,const CUDA_ARRAY_DESCRIPTOR *> params = std::make_tuple(105 ,pHandle,pAllocateArray);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(105, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuArrayCreate ,pHandle,pAllocateArray);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pArrayDescriptor,(void *)&hArray };
	// std::tuple<int,CUDA_ARRAY_DESCRIPTOR *,CUarray> params = std::make_tuple(106 ,pArrayDescriptor,hArray);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(106, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuArrayGetDescriptor ,pArrayDescriptor,hArray);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hArray };
	// std::tuple<int,CUarray> params = std::make_tuple(107 ,hArray);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(107, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuArrayDestroy ,hArray);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pHandle,(void *)&pAllocateArray };
	// std::tuple<int,CUarray *,const CUDA_ARRAY3D_DESCRIPTOR *> params = std::make_tuple(108 ,pHandle,pAllocateArray);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(108, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuArray3DCreate ,pHandle,pAllocateArray);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pArrayDescriptor,(void *)&hArray };
	// std::tuple<int,CUDA_ARRAY3D_DESCRIPTOR *,CUarray> params = std::make_tuple(109 ,pArrayDescriptor,hArray);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(109, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuArray3DGetDescriptor ,pArrayDescriptor,hArray);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pHandle,(void *)&pMipmappedArrayDesc,(void *)&numMipmapLevels };
	// std::tuple<int,CUmipmappedArray *,const CUDA_ARRAY3D_DESCRIPTOR *,unsigned int> params = std::make_tuple(110 ,pHandle,pMipmappedArrayDesc,numMipmapLevels);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(110, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMipmappedArrayCreate ,pHandle,pMipmappedArrayDesc,numMipmapLevels);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pLevelArray,(void *)&hMipmappedArray,(void *)&level };
	// std::tuple<int,CUarray *,CUmipmappedArray,unsigned int> params = std::make_tuple(111 ,pLevelArray,hMipmappedArray,level);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(111, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMipmappedArrayGetLevel ,pLevelArray,hMipmappedArray,level);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hMipmappedArray };
	// std::tuple<int,CUmipmappedArray> params = std::make_tuple(112 ,hMipmappedArray);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(112, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMipmappedArrayDestroy ,hMipmappedArray);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&data,(void *)&attribute,(void *)&ptr };
	// std::tuple<int,void *,CUpointer_attribute,CUdeviceptr> params = std::make_tuple(113 ,data,attribute,ptr);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(113, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuPointerGetAttribute ,data,attribute,ptr);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&value,(void *)&attribute,(void *)&ptr };
	// std::tuple<int,const void *,CUpointer_attribute,CUdeviceptr> params = std::make_tuple(114 ,value,attribute,ptr);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(114, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuPointerSetAttribute ,value,attribute,ptr);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&numAttributes,(void *)&attributes,(void *)&data,(void *)&ptr };
	// std::tuple<int,unsigned int,CUpointer_attribute *,void * *,CUdeviceptr> params = std::make_tuple(115 ,numAttributes,attributes,data,ptr);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(115, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuPointerGetAttributes ,numAttributes,attributes,data,ptr);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&phStream,(void *)&Flags };
	// std::tuple<int,CUstream *,unsigned int> params = std::make_tuple(116 ,phStream,Flags);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(116, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuStreamCreate ,phStream,Flags);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&phStream,(void *)&flags,(void *)&priority };
	// std::tuple<int,CUstream *,unsigned int,int> params = std::make_tuple(117 ,phStream,flags,priority);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(117, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuStreamCreateWithPriority ,phStream,flags,priority);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hStream,(void *)&priority };
	// std::tuple<int,CUstream,int *> params = std::make_tuple(118 ,hStream,priority);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(118, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuStreamGetPriority ,hStream,priority);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hStream,(void *)&flags };
	// std::tuple<int,CUstream,unsigned int *> params = std::make_tuple(119 ,hStream,flags);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(119, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuStreamGetFlags ,hStream,flags);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hStream,(void *)&hEvent,(void *)&Flags };
	// std::tuple<int,CUstream,CUevent,unsigned int> params = std::make_tuple(120 ,hStream,hEvent,Flags);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(120, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuStreamWaitEvent ,hStream,hEvent,Flags);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hStream,(void *)&callback,(void *)&userData,(void *)&flags };
	// std::tuple<int,CUstream,CUstreamCallback,void *,unsigned int> params = std::make_tuple(121 ,hStream,callback,userData,flags);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(121, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuStreamAddCallback ,hStream,callback,userData,flags);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hStream,(void *)&dptr,(void *)&length,(void *)&flags };
	// std::tuple<int,CUstream,CUdeviceptr,size_t,unsigned int> params = std::make_tuple(122 ,hStream,dptr,length,flags);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(122, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuStreamAttachMemAsync ,hStream,dptr,length,flags);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hStream };
	// std::tuple<int,CUstream> params = std::make_tuple(123 ,hStream);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(123, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuStreamQuery ,hStream);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hStream };
	// std::tuple<int,CUstream> params = std::make_tuple(124 ,hStream);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(124, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuStreamSynchronize ,hStream);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hStream };
	// std::tuple<int,CUstream> params = std::make_tuple(125 ,hStream);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(125, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuStreamDestroy ,hStream);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&phEvent,(void *)&Flags };
	// std::tuple<int,CUevent *,unsigned int> params = std::make_tuple(126 ,phEvent,Flags);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(126, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuEventCreate ,phEvent,Flags);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hEvent,(void *)&hStream };
	// std::tuple<int,CUevent,CUstream> params = std::make_tuple(127 ,hEvent,hStream);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(127, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuEventRecord ,hEvent,hStream);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hEvent };
	// std::tuple<int,CUevent> params = std::make_tuple(128 ,hEvent);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(128, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuEventQuery ,hEvent);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hEvent };
	// std::tuple<int,CUevent> params = std::make_tuple(129 ,hEvent);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(129, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuEventSynchronize ,hEvent);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hEvent };
	// std::tuple<int,CUevent> params = std::make_tuple(130 ,hEvent);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(130, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuEventDestroy ,hEvent);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pMilliseconds,(void *)&hStart,(void *)&hEnd };
	// std::tuple<int,float *,CUevent,CUevent> params = std::make_tuple(131 ,pMilliseconds,hStart,hEnd);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(131, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuEventElapsedTime ,pMilliseconds,hStart,hEnd);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pi,(void *)&attrib,(void *)&hfunc };
	// std::tuple<int,int *,CUfunction_attribute,CUfunction> params = std::make_tuple(132 ,pi,attrib,hfunc);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(132, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuFuncGetAttribute ,pi,attrib,hfunc);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hfunc,(void *)&config };
	// std::tuple<int,CUfunction,CUfunc_cache> params = std::make_tuple(133 ,hfunc,config);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(133, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuFuncSetCacheConfig ,hfunc,config);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hfunc,(void *)&config };
	// std::tuple<int,CUfunction,CUsharedconfig> params = std::make_tuple(134 ,hfunc,config);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(134, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuFuncSetSharedMemConfig ,hfunc,config);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&f,(void *)&gridDimX,(void *)&gridDimY,(void *)&gridDimZ,(void *)&blockDimX,(void *)&blockDimY,(void *)&blockDimZ,(void *)&sharedMemBytes,(void *)&hStream,(void *)&kernelParams,(void *)&extra };
	// std::tuple<int,CUfunction,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,CUstream,void * *,void * *> params = std::make_tuple(135 ,f,gridDimX,gridDimY,gridDimZ,blockDimX,blockDimY,blockDimZ,sharedMemBytes,hStream,kernelParams,extra);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(135, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuLaunchKernel ,f,gridDimX,gridDimY,gridDimZ,blockDimX,blockDimY,blockDimZ,sharedMemBytes,hStream,kernelParams,extra);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hfunc,(void *)&x,(void *)&y,(void *)&z };
	// std::tuple<int,CUfunction,int,int,int> params = std::make_tuple(136 ,hfunc,x,y,z);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(136, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuFuncSetBlockShape ,hfunc,x,y,z);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hfunc,(void *)&bytes };
	// std::tuple<int,CUfunction,unsigned int> params = std::make_tuple(137 ,hfunc,bytes);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(137, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuFuncSetSharedSize ,hfunc,bytes);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hfunc,(void *)&numbytes };
	// std::tuple<int,CUfunction,unsigned int> params = std::make_tuple(138 ,hfunc,numbytes);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(138, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuParamSetSize ,hfunc,numbytes);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hfunc,(void *)&offset,(void *)&value };
	// std::tuple<int,CUfunction,int,unsigned int> params = std::make_tuple(139 ,hfunc,offset,value);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(139, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuParamSeti ,hfunc,offset,value);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hfunc,(void *)&offset,(void *)&value };
	// std::tuple<int,CUfunction,int,float> params = std::make_tuple(140 ,hfunc,offset,value);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(140, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuParamSetf ,hfunc,offset,value);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hfunc,(void *)&offset,(void *)&ptr,(void *)&numbytes };
	// std::tuple<int,CUfunction,int,void *,unsigned int> params = std::make_tuple(141 ,hfunc,offset,ptr,numbytes);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(141, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuParamSetv ,hfunc,offset,ptr,numbytes);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&f };
	// std::tuple<int,CUfunction> params = std::make_tuple(142 ,f);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(142, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuLaunch ,f);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&f,(void *)&grid_width,(void *)&grid_height };
	// std::tuple<int,CUfunction,int,int> params = std::make_tuple(143 ,f,grid_width,grid_height);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(143, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuLaunchGrid ,f,grid_width,grid_height);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&f,(void *)&grid_width,(void *)&grid_height,(void *)&hStream };
	// std::tuple<int,CUfunction,int,int,CUstream> params = std::make_tuple(144 ,f,grid_width,grid_height,hStream);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(144, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuLaunchGridAsync ,f,grid_width,grid_height,hStream);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hfunc,(void *)&texunit,(void *)&hTexRef };
	// std::tuple<int,CUfunction,int,CUtexref> params = std::make_tuple(145 ,hfunc,texunit,hTexRef);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(145, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuParamSetTexRef ,hfunc,texunit,hTexRef);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&numBlocks,(void *)&func,(void *)&blockSize,(void *)&dynamicSMemSize };
	// std::tuple<int,int *,CUfunction,int,size_t> params = std::make_tuple(146 ,numBlocks,func,blockSize,dynamicSMemSize);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(146, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuOccupancyMaxActiveBlocksPerMultiprocessor ,numBlocks,func,blockSize,dynamicSMemSize);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&numBlocks,(void *)&func,(void *)&blockSize,(void *)&dynamicSMemSize,(void *)&flags };
	// std::tuple<int,int *,CUfunction,int,size_t,unsigned int> params = std::make_tuple(147 ,numBlocks,func,blockSize,dynamicSMemSize,flags);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(147, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags ,numBlocks,func,blockSize,dynamicSMemSize,flags);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&minGridSize,(void *)&blockSize,(void *)&func,(void *)&blockSizeToDynamicSMemSize,(void *)&dynamicSMemSize,(void *)&blockSizeLimit };
	// std::tuple<int,int *,int *,CUfunction,CUoccupancyB2DSize,size_t,int> params = std::make_tuple(148 ,minGridSize,blockSize,func,blockSizeToDynamicSMemSize,dynamicSMemSize,blockSizeLimit);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(148, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuOccupancyMaxPotentialBlockSize ,minGridSize,blockSize,func,blockSizeToDynamicSMemSize,dynamicSMemSize,blockSizeLimit);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&minGridSize,(void *)&blockSize,(void *)&func,(void *)&blockSizeToDynamicSMemSize,(void *)&dynamicSMemSize,(void *)&blockSizeLimit,(void *)&flags };
	// std::tuple<int,int *,int *,CUfunction,CUoccupancyB2DSize,size_t,int,unsigned int> params = std::make_tuple(149 ,minGridSize,blockSize,func,blockSizeToDynamicSMemSize,dynamicSMemSize,blockSizeLimit,flags);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(149, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuOccupancyMaxPotentialBlockSizeWithFlags ,minGridSize,blockSize,func,blockSizeToDynamicSMemSize,dynamicSMemSize,blockSizeLimit,flags);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hTexRef,(void *)&hArray,(void *)&Flags };
	// std::tuple<int,CUtexref,CUarray,unsigned int> params = std::make_tuple(150 ,hTexRef,hArray,Flags);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(150, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefSetArray ,hTexRef,hArray,Flags);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hTexRef,(void *)&hMipmappedArray,(void *)&Flags };
	// std::tuple<int,CUtexref,CUmipmappedArray,unsigned int> params = std::make_tuple(151 ,hTexRef,hMipmappedArray,Flags);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(151, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefSetMipmappedArray ,hTexRef,hMipmappedArray,Flags);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&ByteOffset,(void *)&hTexRef,(void *)&dptr,(void *)&bytes };
	// std::tuple<int,size_t *,CUtexref,CUdeviceptr,size_t> params = std::make_tuple(152 ,ByteOffset,hTexRef,dptr,bytes);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(152, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefSetAddress ,ByteOffset,hTexRef,dptr,bytes);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hTexRef,(void *)&desc,(void *)&dptr,(void *)&Pitch };
	// std::tuple<int,CUtexref,const CUDA_ARRAY_DESCRIPTOR *,CUdeviceptr,size_t> params = std::make_tuple(153 ,hTexRef,desc,dptr,Pitch);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(153, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefSetAddress2D ,hTexRef,desc,dptr,Pitch);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hTexRef,(void *)&fmt,(void *)&NumPackedComponents };
	// std::tuple<int,CUtexref,CUarray_format,int> params = std::make_tuple(154 ,hTexRef,fmt,NumPackedComponents);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(154, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefSetFormat ,hTexRef,fmt,NumPackedComponents);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hTexRef,(void *)&dim,(void *)&am };
	// std::tuple<int,CUtexref,int,CUaddress_mode> params = std::make_tuple(155 ,hTexRef,dim,am);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(155, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefSetAddressMode ,hTexRef,dim,am);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hTexRef,(void *)&fm };
	// std::tuple<int,CUtexref,CUfilter_mode> params = std::make_tuple(156 ,hTexRef,fm);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(156, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefSetFilterMode ,hTexRef,fm);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hTexRef,(void *)&fm };
	// std::tuple<int,CUtexref,CUfilter_mode> params = std::make_tuple(157 ,hTexRef,fm);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(157, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefSetMipmapFilterMode ,hTexRef,fm);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hTexRef,(void *)&bias };
	// std::tuple<int,CUtexref,float> params = std::make_tuple(158 ,hTexRef,bias);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(158, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefSetMipmapLevelBias ,hTexRef,bias);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hTexRef,(void *)&minMipmapLevelClamp,(void *)&maxMipmapLevelClamp };
	// std::tuple<int,CUtexref,float,float> params = std::make_tuple(159 ,hTexRef,minMipmapLevelClamp,maxMipmapLevelClamp);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(159, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefSetMipmapLevelClamp ,hTexRef,minMipmapLevelClamp,maxMipmapLevelClamp);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hTexRef,(void *)&maxAniso };
	// std::tuple<int,CUtexref,unsigned int> params = std::make_tuple(160 ,hTexRef,maxAniso);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(160, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefSetMaxAnisotropy ,hTexRef,maxAniso);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hTexRef,(void *)&Flags };
	// std::tuple<int,CUtexref,unsigned int> params = std::make_tuple(161 ,hTexRef,Flags);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(161, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefSetFlags ,hTexRef,Flags);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pdptr,(void *)&hTexRef };
	// std::tuple<int,CUdeviceptr *,CUtexref> params = std::make_tuple(162 ,pdptr,hTexRef);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(162, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefGetAddress ,pdptr,hTexRef);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&phArray,(void *)&hTexRef };
	// std::tuple<int,CUarray *,CUtexref> params = std::make_tuple(163 ,phArray,hTexRef);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(163, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefGetArray ,phArray,hTexRef);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&phMipmappedArray,(void *)&hTexRef };
	// std::tuple<int,CUmipmappedArray *,CUtexref> params = std::make_tuple(164 ,phMipmappedArray,hTexRef);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(164, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefGetMipmappedArray ,phMipmappedArray,hTexRef);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pam,(void *)&hTexRef,(void *)&dim };
	// std::tuple<int,CUaddress_mode *,CUtexref,int> params = std::make_tuple(165 ,pam,hTexRef,dim);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(165, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefGetAddressMode ,pam,hTexRef,dim);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pfm,(void *)&hTexRef };
	// std::tuple<int,CUfilter_mode *,CUtexref> params = std::make_tuple(166 ,pfm,hTexRef);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(166, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefGetFilterMode ,pfm,hTexRef);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pFormat,(void *)&pNumChannels,(void *)&hTexRef };
	// std::tuple<int,CUarray_format *,int *,CUtexref> params = std::make_tuple(167 ,pFormat,pNumChannels,hTexRef);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(167, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefGetFormat ,pFormat,pNumChannels,hTexRef);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pfm,(void *)&hTexRef };
	// std::tuple<int,CUfilter_mode *,CUtexref> params = std::make_tuple(168 ,pfm,hTexRef);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(168, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefGetMipmapFilterMode ,pfm,hTexRef);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pbias,(void *)&hTexRef };
	// std::tuple<int,float *,CUtexref> params = std::make_tuple(169 ,pbias,hTexRef);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(169, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefGetMipmapLevelBias ,pbias,hTexRef);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pminMipmapLevelClamp,(void *)&pmaxMipmapLevelClamp,(void *)&hTexRef };
	// std::tuple<int,float *,float *,CUtexref> params = std::make_tuple(170 ,pminMipmapLevelClamp,pmaxMipmapLevelClamp,hTexRef);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(170, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefGetMipmapLevelClamp ,pminMipmapLevelClamp,pmaxMipmapLevelClamp,hTexRef);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pmaxAniso,(void *)&hTexRef };
	// std::tuple<int,int *,CUtexref> params = std::make_tuple(171 ,pmaxAniso,hTexRef);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(171, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefGetMaxAnisotropy ,pmaxAniso,hTexRef);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pFlags,(void *)&hTexRef };
	// std::tuple<int,unsigned int *,CUtexref> params = std::make_tuple(172 ,pFlags,hTexRef);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(172, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefGetFlags ,pFlags,hTexRef);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pTexRef };
	// std::tuple<int,CUtexref *> params = std::make_tuple(173 ,pTexRef);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(173, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefCreate ,pTexRef);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hTexRef };
	// std::tuple<int,CUtexref> params = std::make_tuple(174 ,hTexRef);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(174, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefDestroy ,hTexRef);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&hSurfRef,(void *)&hArray,(void *)&Flags };
	// std::tuple<int,CUsurfref,CUarray,unsigned int> params = std::make_tuple(175 ,hSurfRef,hArray,Flags);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(175, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuSurfRefSetArray ,hSurfRef,hArray,Flags);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&phArray,(void *)&hSurfRef };
	// std::tuple<int,CUarray *,CUsurfref> params = std::make_tuple(176 ,phArray,hSurfRef);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(176, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuSurfRefGetArray ,phArray,hSurfRef);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pTexObject,(void *)&pResDesc,(void *)&pTexDesc,(void *)&pResViewDesc };
	// std::tuple<int,CUtexObject *,const CUDA_RESOURCE_DESC *,const CUDA_TEXTURE_DESC *,const CUDA_RESOURCE_VIEW_DESC *> params = std::make_tuple(177 ,pTexObject,pResDesc,pTexDesc,pResViewDesc);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(177, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuTexObjectCreate ,pTexObject,pResDesc,pTexDesc,pResViewDesc);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&texObject };
	// std::tuple<int,CUtexObject> params = std::make_tuple(178 ,texObject);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(178, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuTexObjectDestroy ,texObject);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pResDesc,(void *)&texObject };
	// std::tuple<int,CUDA_RESOURCE_DESC *,CUtexObject> params = std::make_tuple(179 ,pResDesc,texObject);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(179, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuTexObjectGetResourceDesc ,pResDesc,texObject);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pTexDesc,(void *)&texObject };
	// std::tuple<int,CUDA_TEXTURE_DESC *,CUtexObject> params = std::make_tuple(180 ,pTexDesc,texObject);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(180, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuTexObjectGetTextureDesc ,pTexDesc,texObject);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pResViewDesc,(void *)&texObject };
	// std::tuple<int,CUDA_RESOURCE_VIEW_DESC *,CUtexObject> params = std::make_tuple(181 ,pResViewDesc,texObject);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(181, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuTexObjectGetResourceViewDesc ,pResViewDesc,texObject);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pSurfObject,(void *)&pResDesc };
	// std::tuple<int,CUsurfObject *,const CUDA_RESOURCE_DESC *> params = std::make_tuple(182 ,pSurfObject,pResDesc);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(182, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuSurfObjectCreate ,pSurfObject,pResDesc);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&surfObject };
	// std::tuple<int,CUsurfObject> params = std::make_tuple(183 ,surfObject);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(183, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuSurfObjectDestroy ,surfObject);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pResDesc,(void *)&surfObject };
	// std::tuple<int,CUDA_RESOURCE_DESC *,CUsurfObject> params = std::make_tuple(184 ,pResDesc,surfObject);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(184, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuSurfObjectGetResourceDesc ,pResDesc,surfObject);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&canAccessPeer,(void *)&dev,(void *)&peerDev };
	// std::tuple<int,int *,CUdevice,CUdevice> params = std::make_tuple(185 ,canAccessPeer,dev,peerDev);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(185, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuDeviceCanAccessPeer ,canAccessPeer,dev,peerDev);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&peerContext,(void *)&Flags };
	// std::tuple<int,CUcontext,unsigned int> params = std::make_tuple(186 ,peerContext,Flags);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(186, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuCtxEnablePeerAccess ,peerContext,Flags);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&peerContext };
	// std::tuple<int,CUcontext> params = std::make_tuple(187 ,peerContext);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(187, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuCtxDisablePeerAccess ,peerContext);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&resource };
	// std::tuple<int,CUgraphicsResource> params = std::make_tuple(188 ,resource);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(188, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuGraphicsUnregisterResource ,resource);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pArray,(void *)&resource,(void *)&arrayIndex,(void *)&mipLevel };
	// std::tuple<int,CUarray *,CUgraphicsResource,unsigned int,unsigned int> params = std::make_tuple(189 ,pArray,resource,arrayIndex,mipLevel);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(189, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuGraphicsSubResourceGetMappedArray ,pArray,resource,arrayIndex,mipLevel);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pMipmappedArray,(void *)&resource };
	// std::tuple<int,CUmipmappedArray *,CUgraphicsResource> params = std::make_tuple(190 ,pMipmappedArray,resource);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(190, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuGraphicsResourceGetMappedMipmappedArray ,pMipmappedArray,resource);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pDevPtr,(void *)&pSize,(void *)&resource };
	// std::tuple<int,CUdeviceptr *,size_t *,CUgraphicsResource> params = std::make_tuple(191 ,pDevPtr,pSize,resource);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(191, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuGraphicsResourceGetMappedPointer ,pDevPtr,pSize,resource);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&resource,(void *)&flags };
	// std::tuple<int,CUgraphicsResource,unsigned int> params = std::make_tuple(192 ,resource,flags);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(192, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuGraphicsResourceSetMapFlags ,resource,flags);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&count,(void *)&resources,(void *)&hStream };
	// std::tuple<int,unsigned int,CUgraphicsResource *,CUstream> params = std::make_tuple(193 ,count,resources,hStream);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(193, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuGraphicsMapResources ,count,resources,hStream);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&count,(void *)&resources,(void *)&hStream };
	// std::tuple<int,unsigned int,CUgraphicsResource *,CUstream> params = std::make_tuple(194 ,count,resources,hStream);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(194, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuGraphicsUnmapResources ,count,resources,hStream);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&ppExportTable,(void *)&pExportTableId };

	// std::tuple<int,const void * *,const CUuuid *> params = std::make_tuple(195 ,ppExportTable,pExportTableId);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(195, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuGetExportTable ,ppExportTable,pExportTableId);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
	volatile void * expTable = (void *)*ppExportTable;
	volatile CUuuid * expTableId = (CUuuid *)pExportTableId;
	for (int i = 0; i < 100; i++) {
		fprintf(stderr, "FuncPtr: %p\n", ppExportTable[i]);
		fprintf(stderr, "UUID: %d\n", pExportTableId[i]);
	}

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
	std::vector<void *> params = { (void *)&hTexRef,(void *)&desc,(void *)&dptr,(void *)&Pitch };
	// std::tuple<int,CUtexref,const CUDA_ARRAY_DESCRIPTOR *,CUdeviceptr,size_t> params = std::make_tuple(196 ,hTexRef,desc,dptr,Pitch);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(196, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuTexRefSetAddress2D_v2 ,hTexRef,desc,dptr,Pitch);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstDevice,(void *)&srcHost,(void *)&ByteCount };
	// std::tuple<int,CUdeviceptr,const void *,size_t> params = std::make_tuple(197 ,dstDevice,srcHost,ByteCount);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(197, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyHtoD_v2 ,dstDevice,srcHost,ByteCount);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstHost,(void *)&srcDevice,(void *)&ByteCount };
	// std::tuple<int,void *,CUdeviceptr,size_t> params = std::make_tuple(198 ,dstHost,srcDevice,ByteCount);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(198, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyDtoH_v2 ,dstHost,srcDevice,ByteCount);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstDevice,(void *)&srcDevice,(void *)&ByteCount };
	// std::tuple<int,CUdeviceptr,CUdeviceptr,size_t> params = std::make_tuple(199 ,dstDevice,srcDevice,ByteCount);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(199, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyDtoD_v2 ,dstDevice,srcDevice,ByteCount);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstArray,(void *)&dstOffset,(void *)&srcDevice,(void *)&ByteCount };
	// std::tuple<int,CUarray,size_t,CUdeviceptr,size_t> params = std::make_tuple(200 ,dstArray,dstOffset,srcDevice,ByteCount);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(200, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyDtoA_v2 ,dstArray,dstOffset,srcDevice,ByteCount);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstDevice,(void *)&srcArray,(void *)&srcOffset,(void *)&ByteCount };
	// std::tuple<int,CUdeviceptr,CUarray,size_t,size_t> params = std::make_tuple(201 ,dstDevice,srcArray,srcOffset,ByteCount);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(201, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyAtoD_v2 ,dstDevice,srcArray,srcOffset,ByteCount);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstArray,(void *)&dstOffset,(void *)&srcHost,(void *)&ByteCount };
	// std::tuple<int,CUarray,size_t,const void *,size_t> params = std::make_tuple(202 ,dstArray,dstOffset,srcHost,ByteCount);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(202, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyHtoA_v2 ,dstArray,dstOffset,srcHost,ByteCount);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstHost,(void *)&srcArray,(void *)&srcOffset,(void *)&ByteCount };
	// std::tuple<int,void *,CUarray,size_t,size_t> params = std::make_tuple(203 ,dstHost,srcArray,srcOffset,ByteCount);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(203, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyAtoH_v2 ,dstHost,srcArray,srcOffset,ByteCount);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstArray,(void *)&dstOffset,(void *)&srcArray,(void *)&srcOffset,(void *)&ByteCount };
	// std::tuple<int,CUarray,size_t,CUarray,size_t,size_t> params = std::make_tuple(204 ,dstArray,dstOffset,srcArray,srcOffset,ByteCount);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(204, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyAtoA_v2 ,dstArray,dstOffset,srcArray,srcOffset,ByteCount);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstArray,(void *)&dstOffset,(void *)&srcHost,(void *)&ByteCount,(void *)&hStream };
	// std::tuple<int,CUarray,size_t,const void *,size_t,CUstream> params = std::make_tuple(205 ,dstArray,dstOffset,srcHost,ByteCount,hStream);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(205, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyHtoAAsync_v2 ,dstArray,dstOffset,srcHost,ByteCount,hStream);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstHost,(void *)&srcArray,(void *)&srcOffset,(void *)&ByteCount,(void *)&hStream };
	// std::tuple<int,void *,CUarray,size_t,size_t,CUstream> params = std::make_tuple(206 ,dstHost,srcArray,srcOffset,ByteCount,hStream);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(206, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyAtoHAsync_v2 ,dstHost,srcArray,srcOffset,ByteCount,hStream);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pCopy };
	// std::tuple<int,const CUDA_MEMCPY2D *> params = std::make_tuple(207 ,pCopy);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(207, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpy2D_v2 ,pCopy);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pCopy };
	// std::tuple<int,const CUDA_MEMCPY2D *> params = std::make_tuple(208 ,pCopy);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(208, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpy2DUnaligned_v2 ,pCopy);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pCopy };
	// std::tuple<int,const CUDA_MEMCPY3D *> params = std::make_tuple(209 ,pCopy);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(209, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpy3D_v2 ,pCopy);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstDevice,(void *)&srcHost,(void *)&ByteCount,(void *)&hStream };
	// std::tuple<int,CUdeviceptr,const void *,size_t,CUstream> params = std::make_tuple(210 ,dstDevice,srcHost,ByteCount,hStream);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(210, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyHtoDAsync_v2 ,dstDevice,srcHost,ByteCount,hStream);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstHost,(void *)&srcDevice,(void *)&ByteCount,(void *)&hStream };
	// std::tuple<int,void *,CUdeviceptr,size_t,CUstream> params = std::make_tuple(211 ,dstHost,srcDevice,ByteCount,hStream);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(211, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyDtoHAsync_v2 ,dstHost,srcDevice,ByteCount,hStream);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstDevice,(void *)&srcDevice,(void *)&ByteCount,(void *)&hStream };
	// std::tuple<int,CUdeviceptr,CUdeviceptr,size_t,CUstream> params = std::make_tuple(212 ,dstDevice,srcDevice,ByteCount,hStream);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(212, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpyDtoDAsync_v2 ,dstDevice,srcDevice,ByteCount,hStream);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pCopy,(void *)&hStream };
	// std::tuple<int,const CUDA_MEMCPY2D *,CUstream> params = std::make_tuple(213 ,pCopy,hStream);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(213, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpy2DAsync_v2 ,pCopy,hStream);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&pCopy,(void *)&hStream };
	// std::tuple<int,const CUDA_MEMCPY3D *,CUstream> params = std::make_tuple(214 ,pCopy,hStream);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(214, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemcpy3DAsync_v2 ,pCopy,hStream);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstDevice,(void *)&uc,(void *)&N };
	// std::tuple<int,CUdeviceptr,unsigned char,size_t> params = std::make_tuple(215 ,dstDevice,uc,N);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(215, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD8_v2 ,dstDevice,uc,N);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstDevice,(void *)&us,(void *)&N };
	// std::tuple<int,CUdeviceptr,unsigned short,size_t> params = std::make_tuple(216 ,dstDevice,us,N);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(216, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD16_v2 ,dstDevice,us,N);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstDevice,(void *)&ui,(void *)&N };
	// std::tuple<int,CUdeviceptr,unsigned int,size_t> params = std::make_tuple(217 ,dstDevice,ui,N);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(217, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD32_v2 ,dstDevice,ui,N);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstDevice,(void *)&dstPitch,(void *)&uc,(void *)&Width,(void *)&Height };
	// std::tuple<int,CUdeviceptr,size_t,unsigned char,size_t,size_t> params = std::make_tuple(218 ,dstDevice,dstPitch,uc,Width,Height);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(218, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD2D8_v2 ,dstDevice,dstPitch,uc,Width,Height);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstDevice,(void *)&dstPitch,(void *)&us,(void *)&Width,(void *)&Height };
	// std::tuple<int,CUdeviceptr,size_t,unsigned short,size_t,size_t> params = std::make_tuple(219 ,dstDevice,dstPitch,us,Width,Height);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(219, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD2D16_v2 ,dstDevice,dstPitch,us,Width,Height);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
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
	std::vector<void *> params = { (void *)&dstDevice,(void *)&dstPitch,(void *)&ui,(void *)&Width,(void *)&Height };
	// std::tuple<int,CUdeviceptr,size_t,unsigned int,size_t,size_t> params = std::make_tuple(220 ,dstDevice,dstPitch,ui,Width,Height);
	std::shared_ptr<ParameterBase> paramsPtr(new ParameterImpl(220, &params));
	DriverAPICall call = std::bind(ORIGINAL_cuMemsetD2D32_v2 ,dstDevice,dstPitch,ui,Width,Height);
	int ret = ( int ) FACTORY_PTR->PerformAction(call, paramsPtr);
	return ret;
}

}

