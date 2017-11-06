#include "DriverWrapperFactory.h"
#include "cuda.h"
DriverWrapperFactory::DriverWrapperFactory() { }
DriverWrapperFactory::~DriverWrapperFactory() { }
int DriverWrapperFactory::PerformAction(DriverAPICall t, std::shared_ptr<ParameterBase> params) {
	std::cerr << "Call to " << params.get()->GetName() << " was made" << std::endl;
	if (params.get()->GetID() == 20) {
		CUcontext * ctx = (CUcontext *)params.get()->GetParameter(0);
		if (*ctx == NULL)
			std::cerr << "Unsetting the context" << std::endl:
		else
			std::cerr << "Setting the context" << std::endl;
	}
	return t();
}		