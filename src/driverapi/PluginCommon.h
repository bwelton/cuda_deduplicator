#pragma Once

#include <iostream>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <memory>
#include <map>
#include <vector>

#include "ParameterBase.h"
#include "DriverWrapperBase.h"

enum CallReturn{
	NO_ACTION = 0,         
	NOTIFY_ON_CHANGE,	// Notify when the parameter has changed
	DO_NOT_PERFORM,		// Instruct driver to not perform the action
	PERFORMED_ACTION,	// This plugin performed the action, do not perform again
	MODIFIED_PARAMS,	// This plugin modified the parameters
	FAILED				// This plugin has failed
}
