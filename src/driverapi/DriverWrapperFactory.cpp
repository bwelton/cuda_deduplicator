#include "DriverWrapperFactory.h"
#include <unistd.h>
std::vector<std::string> DriverWrapperFactory::GetLibraryNames(const char * file) {
	std::cerr << "Loading function file : " << file << std::endl;
	std::vector<std::string> ret;
	std::ifstream t;
	std::string line;
	t.open(file,std::ifstream::in);
	while (std::getline(t, line)) {
		ret.push_back(line);
	}
	return ret;
}

void DriverWrapperFactory::LoadLibraries(std::vector<std::string> libs) {
	std::vector<const char *> DriverCVec = {"cuGetErrorString","cuGetErrorName","cuInit","cuDriverGetVersion","cuDeviceGet","cuDeviceGetCount","cuDeviceGetName","cuDeviceTotalMem","cuDeviceGetAttribute","cuDeviceGetProperties","cuDeviceComputeCapability","cuDevicePrimaryCtxRetain","cuDevicePrimaryCtxRelease","cuDevicePrimaryCtxSetFlags","cuDevicePrimaryCtxGetState","cuDevicePrimaryCtxReset","cuCtxCreate","cuCtxDestroy","cuCtxPushCurrent","cuCtxPopCurrent","cuCtxSetCurrent","cuCtxGetCurrent","cuCtxGetDevice","cuCtxGetFlags","cuCtxSynchronize","cuCtxSetLimit","cuCtxGetLimit","cuCtxGetCacheConfig","cuCtxSetCacheConfig","cuCtxGetSharedMemConfig","cuCtxSetSharedMemConfig","cuCtxGetApiVersion","cuCtxGetStreamPriorityRange","cuCtxAttach","cuCtxDetach","cuModuleLoad","cuModuleLoadData","cuModuleLoadDataEx","cuModuleLoadFatBinary","cuModuleUnload","cuModuleGetFunction","cuModuleGetGlobal","cuModuleGetTexRef","cuModuleGetSurfRef","cuLinkCreate","cuLinkAddData","cuLinkAddFile","cuLinkComplete","cuLinkDestroy","cuMemGetInfo","cuMemAlloc","cuMemAllocPitch","cuMemFree","cuMemGetAddressRange","cuMemAllocHost","cuMemFreeHost","cuMemHostAlloc","cuMemHostGetDevicePointer","cuMemHostGetFlags","cuMemAllocManaged","cuDeviceGetByPCIBusId","cuDeviceGetPCIBusId","cuIpcGetEventHandle","cuIpcOpenEventHandle","cuIpcGetMemHandle","cuIpcOpenMemHandle","cuIpcCloseMemHandle","cuMemHostRegister","cuMemHostUnregister","cuMemcpy","cuMemcpyPeer","cuMemcpyHtoD","cuMemcpyDtoH","cuMemcpyDtoD","cuMemcpyDtoA","cuMemcpyAtoD","cuMemcpyHtoA","cuMemcpyAtoH","cuMemcpyAtoA","cuMemcpy2D","cuMemcpy2DUnaligned","cuMemcpy3D","cuMemcpy3DPeer","cuMemcpyAsync","cuMemcpyPeerAsync","cuMemcpyHtoDAsync","cuMemcpyDtoHAsync","cuMemcpyDtoDAsync","cuMemcpyHtoAAsync","cuMemcpyAtoHAsync","cuMemcpy2DAsync","cuMemcpy3DAsync","cuMemcpy3DPeerAsync","cuMemsetD8","cuMemsetD16","cuMemsetD32","cuMemsetD2D8","cuMemsetD2D16","cuMemsetD2D32","cuMemsetD8Async","cuMemsetD16Async","cuMemsetD32Async","cuMemsetD2D8Async","cuMemsetD2D16Async","cuMemsetD2D32Async","cuArrayCreate","cuArrayGetDescriptor","cuArrayDestroy","cuArray3DCreate","cuArray3DGetDescriptor","cuMipmappedArrayCreate","cuMipmappedArrayGetLevel","cuMipmappedArrayDestroy","cuPointerGetAttribute","cuPointerSetAttribute","cuPointerGetAttributes","cuStreamCreate","cuStreamCreateWithPriority","cuStreamGetPriority","cuStreamGetFlags","cuStreamWaitEvent","cuStreamAddCallback","cuStreamAttachMemAsync","cuStreamQuery","cuStreamSynchronize","cuStreamDestroy","cuEventCreate","cuEventRecord","cuEventQuery","cuEventSynchronize","cuEventDestroy","cuEventElapsedTime","cuFuncGetAttribute","cuFuncSetCacheConfig","cuFuncSetSharedMemConfig","cuLaunchKernel","cuFuncSetBlockShape","cuFuncSetSharedSize","cuParamSetSize","cuParamSeti","cuParamSetf","cuParamSetv","cuLaunch","cuLaunchGrid","cuLaunchGridAsync","cuParamSetTexRef","cuOccupancyMaxActiveBlocksPerMultiprocessor","cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags","cuOccupancyMaxPotentialBlockSize","cuOccupancyMaxPotentialBlockSizeWithFlags","cuTexRefSetArray","cuTexRefSetMipmappedArray","cuTexRefSetAddress","cuTexRefSetAddress2D","cuTexRefSetFormat","cuTexRefSetAddressMode","cuTexRefSetFilterMode","cuTexRefSetMipmapFilterMode","cuTexRefSetMipmapLevelBias","cuTexRefSetMipmapLevelClamp","cuTexRefSetMaxAnisotropy","cuTexRefSetFlags","cuTexRefGetAddress","cuTexRefGetArray","cuTexRefGetMipmappedArray","cuTexRefGetAddressMode","cuTexRefGetFilterMode","cuTexRefGetFormat","cuTexRefGetMipmapFilterMode","cuTexRefGetMipmapLevelBias","cuTexRefGetMipmapLevelClamp","cuTexRefGetMaxAnisotropy","cuTexRefGetFlags","cuTexRefCreate","cuTexRefDestroy","cuSurfRefSetArray","cuSurfRefGetArray","cuTexObjectCreate","cuTexObjectDestroy","cuTexObjectGetResourceDesc","cuTexObjectGetTextureDesc","cuTexObjectGetResourceViewDesc","cuSurfObjectCreate","cuSurfObjectDestroy","cuSurfObjectGetResourceDesc","cuDeviceCanAccessPeer","cuCtxEnablePeerAccess","cuCtxDisablePeerAccess","cuGraphicsUnregisterResource","cuGraphicsSubResourceGetMappedArray","cuGraphicsResourceGetMappedMipmappedArray","cuGraphicsResourceGetMappedPointer","cuGraphicsResourceSetMapFlags","cuGraphicsMapResources","cuGraphicsUnmapResources","cuGetExportTable","cuTexRefSetAddress2D_v2","cuMemcpyHtoD_v2","cuMemcpyDtoH_v2","cuMemcpyDtoD_v2","cuMemcpyDtoA_v2","cuMemcpyAtoD_v2","cuMemcpyHtoA_v2","cuMemcpyAtoH_v2","cuMemcpyAtoA_v2","cuMemcpyHtoAAsync_v2","cuMemcpyAtoHAsync_v2","cuMemcpy2D_v2","cuMemcpy2DUnaligned_v2","cuMemcpy3D_v2","cuMemcpyHtoDAsync_v2","cuMemcpyDtoHAsync_v2","cuMemcpyDtoDAsync_v2","cuMemcpy2DAsync_v2","cuMemcpy3DAsync_v2","cuMemsetD8_v2","cuMemsetD16_v2","cuMemsetD32_v2","cuMemsetD2D8_v2","cuMemsetD2D16_v2","cuMemsetD2D32_v2"};
	std::vector<std::string> DriverAPICalls;
	for(auto i : DriverCVec)
		DriverAPICalls.push_back(std::string(i));
	for(auto i : libs) {
		void * handle = dlopen(i.c_str(), RTLD_LAZY | RTLD_NODELETE);
		// Fail immediately if wrapper cannot be loaded
		assert(handle != NULL);
		PluginReturn (*initF)(std::vector<std::string> &);
		PluginReturn (*precallF)(std::shared_ptr<Parameters>);
		PluginReturn (*postcallF)(std::shared_ptr<Parameters>);

		initF = (PluginReturn (*)(std::vector<std::string> &)) dlsym(handle, "init");
		precallF = (PluginReturn (*)(std::shared_ptr<Parameters>)) dlsym(handle, "Precall");
		postcallF = (PluginReturn (*)(std::shared_ptr<Parameters>)) dlsym(handle, "Postcall");
		InitFunc finit = std::bind(initF, std::placeholders::_1);
		PrecallFunc pcf = std::bind(precallF, std::placeholders::_1);
		PostcallFunc postcf = std::bind(postcallF, std::placeholders::_1);
		assert(initF != NULL);
		assert(precallF != NULL);
		assert(postcallF != NULL);
		_plugins.push_back(std::make_tuple(finit, pcf, postcf));
	}
	for (auto i : _plugins) {
		std::get<0>(i)(DriverAPICalls);
	}
}

DriverWrapperFactory::DriverWrapperFactory() {
	DefineBinders();
	std::string libraryFile = std::string("pluginlist.txt");
	std::vector<std::string> libs = GetLibraryNames(libraryFile.c_str());
	LoadLibraries(libs);
}
DriverWrapperFactory::~DriverWrapperFactory() { 

}
void DriverWrapperFactory::PrintStack() {
	//_stack->GenStackTrace();
}
int DriverWrapperFactory::PerformAction(std::shared_ptr<Parameters> params) {
	// Call precall's
	for (auto i : _plugins) 
		std::get<1>(i)(params);

	if (params.get()->Called() == false)
		params.get()->Call();

	for (auto i : _plugins) 
		std::get<2>(i)(params);

	return params.get()->GetReturn();
	//std::cerr << "Call to " << params.get()->GetName() << " was made" << std::endl;
	// CallReturn status = NO_ACTION;
	// int ret = 0;
	// for (auto i : _plugins) {
	// 	CallReturn v = std::get<1>(i)(t, params);
	// 	assert(v != FAILED);
	// 	if (v == PERFORMED_ACTION || v == DO_NOT_PERFORM){
	// 		status = v;
	// 	}
	// }
	// if (status != DO_NOT_PERFORM && status != PERFORMED_ACTION) {
	// 	ret = t();
	// 	status = PERFORMED_ACTION;
	// }
	// for (auto i : _plugins) {
	// 	if (status == PERFORMED_ACTION)
	// 		CallReturn v = std::get<2>(i)(t, params, true);
	// 	else
	// 		CallReturn v = std::get<2>(i)(t, params, false);
	// }

	// if (params.get()->GetID() == 195)
	// 	_stack->PerformAction(t, params);

	// if (params.get()->GetID() == 20) {
	// 	CUcontext * ctx = (CUcontext *)params.get()->GetParameter(0);
	// 	if (*ctx == NULL)
	// 		std::cerr << "Unsetting the context" << std::endl;
	// 	else
	// 		std::cerr << "Setting the context" << std::endl;
	// }
	// if (195 == params.get()->GetID()) {
	// 	t();
	// 	void ** functions = *(( void ***)params.get()->GetParameter(0));
	// 	fprintf(stderr, "cuMemAlloc: %p\n", &ORIGINAL_cuMemAlloc);

	// 	std::cerr << "Function PTRS in exporttable: " << std::endl;
	// 	int pos = 0;
	// 	while(0){
	// 		if (functions[pos] == NULL)
	// 			break;
	// 		fprintf(stderr, "Function %d: %p\n", pos, functions[pos]);
	// 		pos++;
	// 	}
	// }
	// if (40 == params.get()->GetID()) {
	// 	// cuModuleGetFunction
	// 	const char * name = *((const char **)params.get()->GetParameter(2));
	// 	std::cerr << "Getting Module function: " << name << std::endl;
	// }
	// if (50 == params.get()->GetID()){
	// 	int ret = t();
	// 	std::cerr << "We returned " << ret << std::endl;
	// 	if (ret != CUDA_SUCCESS){
	// 		int tmp = ORIGINAL_cuInit(0);
	// 		std::cerr << "Re-CudaInit: " << tmp << std::endl;
	// 	} else {
	// 		return ret;
	// 	}
	// }
	//return 0;
}		