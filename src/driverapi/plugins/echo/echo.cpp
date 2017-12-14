#include "echo.h"

std::shared_ptr<DriverWrapperFactory> Worker;

Echo::Echo(std::vector<std::string> & cmd_list) {
	int count = 0;
	for (auto i : cmd_list) {
		_cmdToName[count] = i;
		count++;
	}
	callcount = 0;
}

Echo::~Echo() {
	std::cout << "[ECHO-END] Call Count: " << callcount << std::endl;
}

CallReturn Echo::Precall(DriverAPICall t, std::shared_ptr<ParameterBase> params) {
	std::cout << "[PRECALL] Call: " << _cmdToName[params.get()->GetID()] << " Param Count:" << params.get()->GetLen() << std::endl;
	return NO_ACTION;
}

CallReturn Echo::Postcall(DriverAPICall t, std::shared_ptr<ParameterBase> params, bool CallPerfromed) {
	std::cout << "[POSTCALL] Call: " << _cmdToName[params.get()->GetID()] << " Param Count:" << params.get()->GetLen() << " Performed: " << CallPerfromed << std::endl;
	if (CallPerfromed)
		callcount++;
	return NO_ACTION;
}

extern "C" {

void init(std::vector<std::string> & cmd_list) {
	BUILD_FACTORY(cmd_list)
}

CallReturn Precall(DriverAPICall t, std::shared_ptr<ParameterBase> params){
	return BUILD_FACTORY->Precall(t, params);
}

CallReturn Postcall(DriverAPICall t, std::shared_ptr<ParameterBase> params, bool CallPerfromed) {
	return BUILD_FACTORY->Precall(t, params, CallPerfromed);
}

}