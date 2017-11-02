#include "DriverWrapperBase.h"
DriverWrapperBase::~DriverWrapperBase() {}

template <typename T> 
int DriverWrapperBase::PerformAction(DriverAPICall t, T params) {return -1;}