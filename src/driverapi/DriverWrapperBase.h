#pragma once
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <memory>

typedef std::function<int(void)> DriverAPICall;

class DriverWrapperBase {
public: 
	virtual ~DriverWrapperBase() = 0;
};
