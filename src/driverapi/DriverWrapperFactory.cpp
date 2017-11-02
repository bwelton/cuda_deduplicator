#include "DriverWrapperFactory.h"
DriverWrapperFactory::DriverWrapperFactory() { }
DriverWrapperFactory::~DriverWrapperFactory() { }
template <typename T> 
int DriverWrapperFactory::PerformAction(DriverAPICall t, T params) {
	return t();
}		