#include "DriverWrapperFactory.h"

DriverWrapperFactory::DriverWrapperFactory() {  }
DriverWrapperFactory::~DriverWrapperFactory() { }
int DriverWrapperFactory::PerformAction(DriverAPICall t, std::shared_ptr<ParameterBase> params) {
	std::cerr << "Call to " << params.get()->GetName() << " was made" << std::endl;
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
	return t();
}		