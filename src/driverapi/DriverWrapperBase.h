#pragma once
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
typedef std::function<int(void)> DriverAPICall;

class DriverWrapperBase {
public: 
	virtual int PerformAction(DriverAPICall t) = 0;
	virtual ~DriverWrapperBase() = 0;
};
