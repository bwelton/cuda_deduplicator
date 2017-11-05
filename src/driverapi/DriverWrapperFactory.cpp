#include "DriverWrapperFactory.h"
extern const std::vector<const char *> CallVector;
DriverWrapperFactory::DriverWrapperFactory() { }
DriverWrapperFactory::~DriverWrapperFactory() { }
template <typename T> 
int DriverWrapperFactory::PerformAction(DriverAPICall t, T params) {
	int call = std::get<0>(params);
	std::cerr << "Call to " << CallVector[call] << " was made" << std::endl;
	return t();
}		