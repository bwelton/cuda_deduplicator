#include "DriverWrapperFactory.h"
DriverWrapperFactory::DriverWrapperFactory() { }
DriverWrapperFactory::~DriverWrapperFactory() { }
int DriverWrapperFactory::PerformAction(DriverAPICall t) {
	return t();
}		