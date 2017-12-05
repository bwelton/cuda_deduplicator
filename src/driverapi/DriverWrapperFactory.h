#pragma once
#include <iostream>
#include <fstream>    
#include <string>
#include <map>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <memory>

#include "DriverWrapperBase.h"
#include "Parameters.h"
#include "StackTraceGen.h"
#ifndef INTERPOSITION_BUILD
#include "DriverAPIHeader.h"
#include "cuda.h"
#else
#include "InterpositionHeader.h"
#endif

class DriverWrapperFactory : public DriverWrapperBase{
private:
	// boost::recursive_mutex _mtx;
	StackTraceGen * _stack;
	bool firstExec;
public:
	DriverWrapperFactory();
	int PerformAction(DriverAPICall t, std::shared_ptr<ParameterBase> params);
	~DriverWrapperFactory();
	void PrintStack();
};

#define BUILD_FACTORY \
	if (DriverFactory.get() == NULL) { \
		fprintf(stderr, "%s\n", "Setting up our global data structure"); \
		DriverFactory.reset(new DriverWrapperFactory()); \
	} 

#define FACTORY_PTR DriverFactory.get()
