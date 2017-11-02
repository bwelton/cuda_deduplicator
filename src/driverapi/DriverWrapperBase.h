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
	template <typename T> 
	virtual int PerformAction(DriverAPICall t, T params) = 0;
	virtual ~DriverWrapperBase() = 0;
};
