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

#include "PluginCommon.h"
typedef std::function<CallReturn(std::vector<std::string> &)> InitFunc;
typedef std::function<CallReturn(DriverAPICall, std::shared_ptr<ParameterBase>)> PrecallFunc;
typedef std::function<CallReturn(DriverAPICall, std::shared_ptr<ParameterBase>, bool)> PostcallFunc;

class DriverWrapperFactory : public DriverWrapperBase{
private:
	// boost::recursive_mutex _mtx;
	StackTraceGen * _stack;
	bool firstExec;
	std::vector<std::tuple<InitFunc, PrecallFunc, PostcallFunc> > _plugins;
public:
	DriverWrapperFactory();
	int PerformAction(DriverAPICall t, std::shared_ptr<ParameterBase> params);
	~DriverWrapperFactory();
	void LoadLibraries(std::vector<std::string> libs);
	std::vector<std::string> GetLibraryNames(const char * file);
	void PrintStack();
};

#define BUILD_FACTORY \
	if (DriverFactory.get() == NULL) { \
		fprintf(stderr, "%s\n", "Setting up our global data structure"); \
		DriverFactory.reset(new DriverWrapperFactory()); \
	} 

#define FACTORY_PTR DriverFactory.get()
