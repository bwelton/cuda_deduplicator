#pragma once
#include <boost/function.hpp>
#include <boost/bind.hpp>
typedef boost::function<int(void)> DriverAPICall;

class DriverWrapperBase {
public: 
	virtual int PerformAction(DriverAPICall t) = 0;
	virtual ~DriverWrapperBase() = 0;
};
