#pragma once
#include <iostream>
#include <fstream>    
#include <string>
#include <map>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <memory>
#include "DriverAPIHeader.h"
#include "DriverWrapperBase.h"
#include "Parameters.h"
class DriverWrapperFactory : public DriverWrapperBase{
private:
	// boost::recursive_mutex _mtx;
public:
	DriverWrapperFactory();
	int PerformAction(DriverAPICall t, std::shared_ptr<ParameterBase> params);
	~DriverWrapperFactory();
};

#define BUILD_FACTORY \
	if (DriverFactory.get() == NULL) { \
		fprintf(stderr, "%s\n", "Setting up our global data structure"); \
		DriverFactory.reset(new DriverWrapperFactory()); \
	} 

#define FACTORY_PTR DriverFactory.get()
