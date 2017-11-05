#include "DriverWrapperFactory.h"
DriverWrapperFactory::DriverWrapperFactory() { }
DriverWrapperFactory::~DriverWrapperFactory() { }
template <typename T> 
extern static const std::vector<const char *> CallVector;
int DriverWrapperFactory::PerformAction(DriverAPICall t, T params) {
	int call = std::get<0>(params);
	std::cerr << "Call to " << CallVector[call] << " was made" << std::endl;
	return t();
}		