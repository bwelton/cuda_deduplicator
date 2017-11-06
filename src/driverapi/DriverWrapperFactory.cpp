#include "DriverWrapperFactory.h"
#include "cuda.h"
DriverWrapperFactory::DriverWrapperFactory() { }
DriverWrapperFactory::~DriverWrapperFactory() { }
int DriverWrapperFactory::PerformAction(DriverAPICall t, std::shared_ptr<ParameterBase> params) {
	std::cerr << "Call to " << params.get()->GetName() << " was made" << std::endl;
	if (params.get()->GetID() == 20) {
		CUcontext * ctx = (CUcontext *)params.get()->GetParameter(0);
		if (*ctx == NULL)
			std::cerr << "Unsetting the context" << std::endl;
		else
			std::cerr << "Setting the context" << std::endl;
	}	
	if (50 == params.get()->GetID()){
		int ret = t();
		if (ret != CUDA_SUCCESS){
			int tmp = ORIGINAL_cuInit(0);
			std::cerr << "Re-CudaInit: " << tmp << std::endl;
		} else {
			return ret;
		}
	}
	return t();
}		