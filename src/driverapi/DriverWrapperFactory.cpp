#include "DriverWrapperFactory.h"

DriverWrapperFactory::DriverWrapperFactory() { }
DriverWrapperFactory::~DriverWrapperFactory() { }
int DriverWrapperFactory::PerformAction(DriverAPICall t, std::shared_ptr<ParameterBase> params) {
	std::cerr << "Call to " << params.get()->GetName() << " was made" << std::endl;
	return t();
}		