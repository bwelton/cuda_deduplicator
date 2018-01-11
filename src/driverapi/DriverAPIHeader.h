#pragma once
#include "PluginCommon.h"
#include <vector>
#include "Parameters.h"
#include "cuda.h"
#include "DriverWrapperBase.h"
#include <vector>
extern "C" {
int ORIGINAL_InternalSynchronization( void * a, void * b);
void CheckInit_DriverAPI();
void DefineBinders();
int ORIGINAL_cuGetErrorString( CUresult error, const char ** pStr );
int ORIGINAL_cuGetErrorName( CUresult error, const char ** pStr );
int ORIGINAL_cuInit( unsigned int Flags );
int ORIGINAL_cuDriverGetVersion( int * driverVersion );
int ORIGINAL_cuDeviceGet( CUdevice * device, int ordinal );
int ORIGINAL_cuDeviceGetCount( int * count );
int ORIGINAL_cuDeviceGetName( char * name, int len, CUdevice dev );
int ORIGINAL_cuDeviceTotalMem( size_t * bytes, CUdevice dev );
int ORIGINAL_cuDeviceGetAttribute( int * pi, CUdevice_attribute attrib, CUdevice dev );
int ORIGINAL_cuDeviceGetProperties( CUdevprop * prop, CUdevice dev );
int ORIGINAL_cuDeviceComputeCapability( int * major, int * minor, CUdevice dev );
int ORIGINAL_cuDevicePrimaryCtxRetain( CUcontext * pctx, CUdevice dev );
int ORIGINAL_cuDevicePrimaryCtxRelease( CUdevice dev );
int ORIGINAL_cuDevicePrimaryCtxSetFlags( CUdevice dev, unsigned int flags );
int ORIGINAL_cuDevicePrimaryCtxGetState( CUdevice dev, unsigned int * flags, int * active );
int ORIGINAL_cuDevicePrimaryCtxReset( CUdevice dev );
int ORIGINAL_cuCtxCreate( CUcontext * pctx, unsigned int flags, CUdevice dev );
int ORIGINAL_cuCtxDestroy( CUcontext ctx );
int ORIGINAL_cuCtxPushCurrent( CUcontext ctx );
int ORIGINAL_cuCtxPopCurrent( CUcontext * pctx );
int ORIGINAL_cuCtxSetCurrent( CUcontext ctx );
int ORIGINAL_cuCtxGetCurrent( CUcontext * pctx );
int ORIGINAL_cuCtxGetDevice( CUdevice * device );
int ORIGINAL_cuCtxGetFlags( unsigned int * flags );
int ORIGINAL_cuCtxSynchronize( void  );
int ORIGINAL_cuCtxSetLimit( CUlimit limit, size_t value );
int ORIGINAL_cuCtxGetLimit( size_t * pvalue, CUlimit limit );
int ORIGINAL_cuCtxGetCacheConfig( CUfunc_cache * pconfig );
int ORIGINAL_cuCtxSetCacheConfig( CUfunc_cache config );
int ORIGINAL_cuCtxGetSharedMemConfig( CUsharedconfig * pConfig );
int ORIGINAL_cuCtxSetSharedMemConfig( CUsharedconfig config );
int ORIGINAL_cuCtxGetApiVersion( CUcontext ctx, unsigned int * version );
int ORIGINAL_cuCtxGetStreamPriorityRange( int * leastPriority, int * greatestPriority );
int ORIGINAL_cuCtxAttach( CUcontext * pctx, unsigned int flags );
int ORIGINAL_cuCtxDetach( CUcontext ctx );
int ORIGINAL_cuModuleLoad( CUmodule * module, const char * fname );
int ORIGINAL_cuModuleLoadData( CUmodule * module, const void * image );
int ORIGINAL_cuModuleLoadDataEx( CUmodule * module, const void * image, unsigned int numOptions, CUjit_option * options, void * * optionValues );
int ORIGINAL_cuModuleLoadFatBinary( CUmodule * module, const void * fatCubin );
int ORIGINAL_cuModuleUnload( CUmodule hmod );
int ORIGINAL_cuModuleGetFunction( CUfunction * hfunc, CUmodule hmod, const char * name );
int ORIGINAL_cuModuleGetGlobal( CUdeviceptr * dptr, size_t * bytes, CUmodule hmod, const char * name );
int ORIGINAL_cuModuleGetTexRef( CUtexref * pTexRef, CUmodule hmod, const char * name );
int ORIGINAL_cuModuleGetSurfRef( CUsurfref * pSurfRef, CUmodule hmod, const char * name );
int ORIGINAL_cuLinkCreate( unsigned int numOptions, CUjit_option * options, void * * optionValues, CUlinkState * stateOut );
int ORIGINAL_cuLinkAddData( CUlinkState state, CUjitInputType type, void * data, size_t size, const char * name, unsigned int numOptions, CUjit_option * options, void * * optionValues );
int ORIGINAL_cuLinkAddFile( CUlinkState state, CUjitInputType type, const char * path, unsigned int numOptions, CUjit_option * options, void * * optionValues );
int ORIGINAL_cuLinkComplete( CUlinkState state, void * * cubinOut, size_t * sizeOut );
int ORIGINAL_cuLinkDestroy( CUlinkState state );
int ORIGINAL_cuMemGetInfo( size_t * free, size_t * total );
int ORIGINAL_cuMemAlloc( CUdeviceptr * dptr, size_t bytesize );
int ORIGINAL_cuMemAllocPitch( CUdeviceptr * dptr, size_t * pPitch, size_t WidthInBytes, size_t Height, unsigned int ElementSizeBytes );
int ORIGINAL_cuMemFree( CUdeviceptr dptr );
int ORIGINAL_cuMemGetAddressRange( CUdeviceptr * pbase, size_t * psize, CUdeviceptr dptr );
int ORIGINAL_cuMemAllocHost( void * * pp, size_t bytesize );
int ORIGINAL_cuMemFreeHost( void * p );
int ORIGINAL_cuMemHostAlloc( void * * pp, size_t bytesize, unsigned int Flags );
int ORIGINAL_cuMemHostGetDevicePointer( CUdeviceptr * pdptr, void * p, unsigned int Flags );
int ORIGINAL_cuMemHostGetFlags( unsigned int * pFlags, void * p );
int ORIGINAL_cuMemAllocManaged( CUdeviceptr * dptr, size_t bytesize, unsigned int flags );
int ORIGINAL_cuDeviceGetByPCIBusId( CUdevice * dev, const char * pciBusId );
int ORIGINAL_cuDeviceGetPCIBusId( char * pciBusId, int len, CUdevice dev );
int ORIGINAL_cuIpcGetEventHandle( CUipcEventHandle * pHandle, CUevent event );
int ORIGINAL_cuIpcOpenEventHandle( CUevent * phEvent, CUipcEventHandle handle );
int ORIGINAL_cuIpcGetMemHandle( CUipcMemHandle * pHandle, CUdeviceptr dptr );
int ORIGINAL_cuIpcOpenMemHandle( CUdeviceptr * pdptr, CUipcMemHandle handle, unsigned int Flags );
int ORIGINAL_cuIpcCloseMemHandle( CUdeviceptr dptr );
int ORIGINAL_cuMemHostRegister( void * p, size_t bytesize, unsigned int Flags );
int ORIGINAL_cuMemHostUnregister( void * p );
int ORIGINAL_cuMemcpy( CUdeviceptr dst, CUdeviceptr src, size_t ByteCount );
int ORIGINAL_cuMemcpyPeer( CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount );
int ORIGINAL_cuMemcpyHtoD( CUdeviceptr dstDevice, const void * srcHost, size_t ByteCount );
int ORIGINAL_cuMemcpyDtoH( void * dstHost, CUdeviceptr srcDevice, size_t ByteCount );
int ORIGINAL_cuMemcpyDtoD( CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount );
int ORIGINAL_cuMemcpyDtoA( CUarray dstArray, size_t dstOffset, CUdeviceptr srcDevice, size_t ByteCount );
int ORIGINAL_cuMemcpyAtoD( CUdeviceptr dstDevice, CUarray srcArray, size_t srcOffset, size_t ByteCount );
int ORIGINAL_cuMemcpyHtoA( CUarray dstArray, size_t dstOffset, const void * srcHost, size_t ByteCount );
int ORIGINAL_cuMemcpyAtoH( void * dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount );
int ORIGINAL_cuMemcpyAtoA( CUarray dstArray, size_t dstOffset, CUarray srcArray, size_t srcOffset, size_t ByteCount );
int ORIGINAL_cuMemcpy2D( const CUDA_MEMCPY2D * pCopy );
int ORIGINAL_cuMemcpy2DUnaligned( const CUDA_MEMCPY2D * pCopy );
int ORIGINAL_cuMemcpy3D( const CUDA_MEMCPY3D * pCopy );
int ORIGINAL_cuMemcpy3DPeer( const CUDA_MEMCPY3D_PEER * pCopy );
int ORIGINAL_cuMemcpyAsync( CUdeviceptr dst, CUdeviceptr src, size_t ByteCount, CUstream hStream );
int ORIGINAL_cuMemcpyPeerAsync( CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount, CUstream hStream );
int ORIGINAL_cuMemcpyHtoDAsync( CUdeviceptr dstDevice, const void * srcHost, size_t ByteCount, CUstream hStream );
int ORIGINAL_cuMemcpyDtoHAsync( void * dstHost, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream );
int ORIGINAL_cuMemcpyDtoDAsync( CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream );
int ORIGINAL_cuMemcpyHtoAAsync( CUarray dstArray, size_t dstOffset, const void * srcHost, size_t ByteCount, CUstream hStream );
int ORIGINAL_cuMemcpyAtoHAsync( void * dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount, CUstream hStream );
int ORIGINAL_cuMemcpy2DAsync( const CUDA_MEMCPY2D * pCopy, CUstream hStream );
int ORIGINAL_cuMemcpy3DAsync( const CUDA_MEMCPY3D * pCopy, CUstream hStream );
int ORIGINAL_cuMemcpy3DPeerAsync( const CUDA_MEMCPY3D_PEER * pCopy, CUstream hStream );
int ORIGINAL_cuMemsetD8( CUdeviceptr dstDevice, unsigned char uc, size_t N );
int ORIGINAL_cuMemsetD16( CUdeviceptr dstDevice, unsigned short us, size_t N );
int ORIGINAL_cuMemsetD32( CUdeviceptr dstDevice, unsigned int ui, size_t N );
int ORIGINAL_cuMemsetD2D8( CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height );
int ORIGINAL_cuMemsetD2D16( CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height );
int ORIGINAL_cuMemsetD2D32( CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height );
int ORIGINAL_cuMemsetD8Async( CUdeviceptr dstDevice, unsigned char uc, size_t N, CUstream hStream );
int ORIGINAL_cuMemsetD16Async( CUdeviceptr dstDevice, unsigned short us, size_t N, CUstream hStream );
int ORIGINAL_cuMemsetD32Async( CUdeviceptr dstDevice, unsigned int ui, size_t N, CUstream hStream );
int ORIGINAL_cuMemsetD2D8Async( CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height, CUstream hStream );
int ORIGINAL_cuMemsetD2D16Async( CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height, CUstream hStream );
int ORIGINAL_cuMemsetD2D32Async( CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height, CUstream hStream );
int ORIGINAL_cuArrayCreate( CUarray * pHandle, const CUDA_ARRAY_DESCRIPTOR * pAllocateArray );
int ORIGINAL_cuArrayGetDescriptor( CUDA_ARRAY_DESCRIPTOR * pArrayDescriptor, CUarray hArray );
int ORIGINAL_cuArrayDestroy( CUarray hArray );
int ORIGINAL_cuArray3DCreate( CUarray * pHandle, const CUDA_ARRAY3D_DESCRIPTOR * pAllocateArray );
int ORIGINAL_cuArray3DGetDescriptor( CUDA_ARRAY3D_DESCRIPTOR * pArrayDescriptor, CUarray hArray );
int ORIGINAL_cuMipmappedArrayCreate( CUmipmappedArray * pHandle, const CUDA_ARRAY3D_DESCRIPTOR * pMipmappedArrayDesc, unsigned int numMipmapLevels );
int ORIGINAL_cuMipmappedArrayGetLevel( CUarray * pLevelArray, CUmipmappedArray hMipmappedArray, unsigned int level );
int ORIGINAL_cuMipmappedArrayDestroy( CUmipmappedArray hMipmappedArray );
int ORIGINAL_cuPointerGetAttribute( void * data, CUpointer_attribute attribute, CUdeviceptr ptr );
int ORIGINAL_cuMemPrefetchAsync( CUdeviceptr devPtr, size_t count, CUdevice dstDevice, CUstream hStream );
int ORIGINAL_cuMemAdvise( CUdeviceptr devPtr, size_t count, CUmem_advise advice, CUdevice device );
int ORIGINAL_cuMemRangeGetAttribute( void * data, size_t dataSize, CUmem_range_attribute attribute, CUdeviceptr devPtr, size_t count );
int ORIGINAL_cuMemRangeGetAttributes( void * * data, size_t * dataSizes, CUmem_range_attribute * attributes, size_t numAttributes, CUdeviceptr devPtr, size_t count );
int ORIGINAL_cuPointerSetAttribute( const void * value, CUpointer_attribute attribute, CUdeviceptr ptr );
int ORIGINAL_cuPointerGetAttributes( unsigned int numAttributes, CUpointer_attribute * attributes, void * * data, CUdeviceptr ptr );
int ORIGINAL_cuStreamCreate( CUstream * phStream, unsigned int Flags );
int ORIGINAL_cuStreamCreateWithPriority( CUstream * phStream, unsigned int flags, int priority );
int ORIGINAL_cuStreamGetPriority( CUstream hStream, int * priority );
int ORIGINAL_cuStreamGetFlags( CUstream hStream, unsigned int * flags );
int ORIGINAL_cuStreamWaitEvent( CUstream hStream, CUevent hEvent, unsigned int Flags );
int ORIGINAL_cuStreamAddCallback( CUstream hStream, CUstreamCallback callback, void * userData, unsigned int flags );
int ORIGINAL_cuStreamAttachMemAsync( CUstream hStream, CUdeviceptr dptr, size_t length, unsigned int flags );
int ORIGINAL_cuStreamQuery( CUstream hStream );
int ORIGINAL_cuStreamSynchronize( CUstream hStream );
int ORIGINAL_cuStreamDestroy( CUstream hStream );
int ORIGINAL_cuEventCreate( CUevent * phEvent, unsigned int Flags );
int ORIGINAL_cuEventRecord( CUevent hEvent, CUstream hStream );
int ORIGINAL_cuEventQuery( CUevent hEvent );
int ORIGINAL_cuEventSynchronize( CUevent hEvent );
int ORIGINAL_cuEventDestroy( CUevent hEvent );
int ORIGINAL_cuEventElapsedTime( float * pMilliseconds, CUevent hStart, CUevent hEnd );
int ORIGINAL_cuStreamWaitValue32( CUstream stream, CUdeviceptr addr, cuuint32_t value, unsigned int flags );
int ORIGINAL_cuStreamWriteValue32( CUstream stream, CUdeviceptr addr, cuuint32_t value, unsigned int flags );
int ORIGINAL_cuStreamBatchMemOp( CUstream stream, unsigned int count, CUstreamBatchMemOpParams * paramArray, unsigned int flags );
int ORIGINAL_cuFuncGetAttribute( int * pi, CUfunction_attribute attrib, CUfunction hfunc );
int ORIGINAL_cuFuncSetCacheConfig( CUfunction hfunc, CUfunc_cache config );
int ORIGINAL_cuFuncSetSharedMemConfig( CUfunction hfunc, CUsharedconfig config );
int ORIGINAL_cuLaunchKernel( CUfunction f, unsigned int gridDimX, unsigned int gridDimY, unsigned int gridDimZ, unsigned int blockDimX, unsigned int blockDimY, unsigned int blockDimZ, unsigned int sharedMemBytes, CUstream hStream, void * * kernelParams, void * * extra );
int ORIGINAL_cuFuncSetBlockShape( CUfunction hfunc, int x, int y, int z );
int ORIGINAL_cuFuncSetSharedSize( CUfunction hfunc, unsigned int bytes );
int ORIGINAL_cuParamSetSize( CUfunction hfunc, unsigned int numbytes );
int ORIGINAL_cuParamSeti( CUfunction hfunc, int offset, unsigned int value );
int ORIGINAL_cuParamSetf( CUfunction hfunc, int offset, float value );
int ORIGINAL_cuParamSetv( CUfunction hfunc, int offset, void * ptr, unsigned int numbytes );
int ORIGINAL_cuLaunch( CUfunction f );
int ORIGINAL_cuLaunchGrid( CUfunction f, int grid_width, int grid_height );
int ORIGINAL_cuLaunchGridAsync( CUfunction f, int grid_width, int grid_height, CUstream hStream );
int ORIGINAL_cuParamSetTexRef( CUfunction hfunc, int texunit, CUtexref hTexRef );
int ORIGINAL_cuOccupancyMaxActiveBlocksPerMultiprocessor( int * numBlocks, CUfunction func, int blockSize, size_t dynamicSMemSize );
int ORIGINAL_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags( int * numBlocks, CUfunction func, int blockSize, size_t dynamicSMemSize, unsigned int flags );
int ORIGINAL_cuOccupancyMaxPotentialBlockSize( int * minGridSize, int * blockSize, CUfunction func, CUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int blockSizeLimit );
int ORIGINAL_cuOccupancyMaxPotentialBlockSizeWithFlags( int * minGridSize, int * blockSize, CUfunction func, CUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int blockSizeLimit, unsigned int flags );
int ORIGINAL_cuTexRefSetArray( CUtexref hTexRef, CUarray hArray, unsigned int Flags );
int ORIGINAL_cuTexRefSetMipmappedArray( CUtexref hTexRef, CUmipmappedArray hMipmappedArray, unsigned int Flags );
int ORIGINAL_cuTexRefSetAddress( size_t * ByteOffset, CUtexref hTexRef, CUdeviceptr dptr, size_t bytes );
int ORIGINAL_cuTexRefSetAddress2D( CUtexref hTexRef, const CUDA_ARRAY_DESCRIPTOR * desc, CUdeviceptr dptr, size_t Pitch );
int ORIGINAL_cuTexRefSetFormat( CUtexref hTexRef, CUarray_format fmt, int NumPackedComponents );
int ORIGINAL_cuTexRefSetAddressMode( CUtexref hTexRef, int dim, CUaddress_mode am );
int ORIGINAL_cuTexRefSetFilterMode( CUtexref hTexRef, CUfilter_mode fm );
int ORIGINAL_cuTexRefSetMipmapFilterMode( CUtexref hTexRef, CUfilter_mode fm );
int ORIGINAL_cuTexRefSetMipmapLevelBias( CUtexref hTexRef, float bias );
int ORIGINAL_cuTexRefSetMipmapLevelClamp( CUtexref hTexRef, float minMipmapLevelClamp, float maxMipmapLevelClamp );
int ORIGINAL_cuTexRefSetMaxAnisotropy( CUtexref hTexRef, unsigned int maxAniso );
int ORIGINAL_cuTexRefSetBorderColor( CUtexref hTexRef, float * pBorderColor );
int ORIGINAL_cuTexRefSetFlags( CUtexref hTexRef, unsigned int Flags );
int ORIGINAL_cuTexRefGetAddress( CUdeviceptr * pdptr, CUtexref hTexRef );
int ORIGINAL_cuTexRefGetArray( CUarray * phArray, CUtexref hTexRef );
int ORIGINAL_cuTexRefGetMipmappedArray( CUmipmappedArray * phMipmappedArray, CUtexref hTexRef );
int ORIGINAL_cuTexRefGetAddressMode( CUaddress_mode * pam, CUtexref hTexRef, int dim );
int ORIGINAL_cuTexRefGetFilterMode( CUfilter_mode * pfm, CUtexref hTexRef );
int ORIGINAL_cuTexRefGetFormat( CUarray_format * pFormat, int * pNumChannels, CUtexref hTexRef );
int ORIGINAL_cuTexRefGetMipmapFilterMode( CUfilter_mode * pfm, CUtexref hTexRef );
int ORIGINAL_cuTexRefGetMipmapLevelBias( float * pbias, CUtexref hTexRef );
int ORIGINAL_cuTexRefGetMipmapLevelClamp( float * pminMipmapLevelClamp, float * pmaxMipmapLevelClamp, CUtexref hTexRef );
int ORIGINAL_cuTexRefGetMaxAnisotropy( int * pmaxAniso, CUtexref hTexRef );
int ORIGINAL_cuTexRefGetBorderColor( float * pBorderColor, CUtexref hTexRef );
int ORIGINAL_cuTexRefGetFlags( unsigned int * pFlags, CUtexref hTexRef );
int ORIGINAL_cuTexRefCreate( CUtexref * pTexRef );
int ORIGINAL_cuTexRefDestroy( CUtexref hTexRef );
int ORIGINAL_cuSurfRefSetArray( CUsurfref hSurfRef, CUarray hArray, unsigned int Flags );
int ORIGINAL_cuSurfRefGetArray( CUarray * phArray, CUsurfref hSurfRef );
int ORIGINAL_cuTexObjectCreate( CUtexObject * pTexObject, const CUDA_RESOURCE_DESC * pResDesc, const CUDA_TEXTURE_DESC * pTexDesc, const CUDA_RESOURCE_VIEW_DESC * pResViewDesc );
int ORIGINAL_cuTexObjectDestroy( CUtexObject texObject );
int ORIGINAL_cuTexObjectGetResourceDesc( CUDA_RESOURCE_DESC * pResDesc, CUtexObject texObject );
int ORIGINAL_cuTexObjectGetTextureDesc( CUDA_TEXTURE_DESC * pTexDesc, CUtexObject texObject );
int ORIGINAL_cuTexObjectGetResourceViewDesc( CUDA_RESOURCE_VIEW_DESC * pResViewDesc, CUtexObject texObject );
int ORIGINAL_cuSurfObjectCreate( CUsurfObject * pSurfObject, const CUDA_RESOURCE_DESC * pResDesc );
int ORIGINAL_cuSurfObjectDestroy( CUsurfObject surfObject );
int ORIGINAL_cuSurfObjectGetResourceDesc( CUDA_RESOURCE_DESC * pResDesc, CUsurfObject surfObject );
int ORIGINAL_cuDeviceCanAccessPeer( int * canAccessPeer, CUdevice dev, CUdevice peerDev );
int ORIGINAL_cuDeviceGetP2PAttribute( int * value, CUdevice_P2PAttribute attrib, CUdevice srcDevice, CUdevice dstDevice );
int ORIGINAL_cuCtxEnablePeerAccess( CUcontext peerContext, unsigned int Flags );
int ORIGINAL_cuCtxDisablePeerAccess( CUcontext peerContext );
int ORIGINAL_cuGraphicsUnregisterResource( CUgraphicsResource resource );
int ORIGINAL_cuGraphicsSubResourceGetMappedArray( CUarray * pArray, CUgraphicsResource resource, unsigned int arrayIndex, unsigned int mipLevel );
int ORIGINAL_cuGraphicsResourceGetMappedMipmappedArray( CUmipmappedArray * pMipmappedArray, CUgraphicsResource resource );
int ORIGINAL_cuGraphicsResourceGetMappedPointer( CUdeviceptr * pDevPtr, size_t * pSize, CUgraphicsResource resource );
int ORIGINAL_cuGraphicsResourceSetMapFlags( CUgraphicsResource resource, unsigned int flags );
int ORIGINAL_cuGraphicsMapResources( unsigned int count, CUgraphicsResource * resources, CUstream hStream );
int ORIGINAL_cuGraphicsUnmapResources( unsigned int count, CUgraphicsResource * resources, CUstream hStream );
int ORIGINAL_cuGetExportTable( const void * * ppExportTable, const CUuuid * pExportTableId );
int ORIGINAL_cuTexRefSetAddress2D_v2( CUtexref hTexRef, const CUDA_ARRAY_DESCRIPTOR * desc, CUdeviceptr dptr, size_t Pitch );
int ORIGINAL_cuMemcpyHtoD_v2( CUdeviceptr dstDevice, const void * srcHost, size_t ByteCount );
int ORIGINAL_cuMemcpyDtoH_v2( void * dstHost, CUdeviceptr srcDevice, size_t ByteCount );
int ORIGINAL_cuMemcpyDtoD_v2( CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount );
int ORIGINAL_cuMemcpyDtoA_v2( CUarray dstArray, size_t dstOffset, CUdeviceptr srcDevice, size_t ByteCount );
int ORIGINAL_cuMemcpyAtoD_v2( CUdeviceptr dstDevice, CUarray srcArray, size_t srcOffset, size_t ByteCount );
int ORIGINAL_cuMemcpyHtoA_v2( CUarray dstArray, size_t dstOffset, const void * srcHost, size_t ByteCount );
int ORIGINAL_cuMemcpyAtoH_v2( void * dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount );
int ORIGINAL_cuMemcpyAtoA_v2( CUarray dstArray, size_t dstOffset, CUarray srcArray, size_t srcOffset, size_t ByteCount );
int ORIGINAL_cuMemcpyHtoAAsync_v2( CUarray dstArray, size_t dstOffset, const void * srcHost, size_t ByteCount, CUstream hStream );
int ORIGINAL_cuMemcpyAtoHAsync_v2( void * dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount, CUstream hStream );
int ORIGINAL_cuMemcpy2D_v2( const CUDA_MEMCPY2D * pCopy );
int ORIGINAL_cuMemcpy2DUnaligned_v2( const CUDA_MEMCPY2D * pCopy );
int ORIGINAL_cuMemcpy3D_v2( const CUDA_MEMCPY3D * pCopy );
int ORIGINAL_cuMemcpyHtoDAsync_v2( CUdeviceptr dstDevice, const void * srcHost, size_t ByteCount, CUstream hStream );
int ORIGINAL_cuMemcpyDtoHAsync_v2( void * dstHost, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream );
int ORIGINAL_cuMemcpyDtoDAsync_v2( CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream );
int ORIGINAL_cuMemcpy2DAsync_v2( const CUDA_MEMCPY2D * pCopy, CUstream hStream );
int ORIGINAL_cuMemcpy3DAsync_v2( const CUDA_MEMCPY3D * pCopy, CUstream hStream );
int ORIGINAL_cuMemsetD8_v2( CUdeviceptr dstDevice, unsigned char uc, size_t N );
int ORIGINAL_cuMemsetD16_v2( CUdeviceptr dstDevice, unsigned short us, size_t N );
int ORIGINAL_cuMemsetD32_v2( CUdeviceptr dstDevice, unsigned int ui, size_t N );
int ORIGINAL_cuMemsetD2D8_v2( CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height );
int ORIGINAL_cuMemsetD2D16_v2( CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height );
int ORIGINAL_cuMemsetD2D32_v2( CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height );

}
