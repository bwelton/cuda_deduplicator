#pragma once
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
typedef std::function<int(void)> DriverAPICall;

class DriverWrapperBase {
public: 
	template <typename T> 
	int PerformAction(DriverAPICall t, T params);
	virtual ~DriverWrapperBase() = 0;
};
