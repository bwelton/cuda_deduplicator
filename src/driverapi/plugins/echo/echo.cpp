#include "echo.h"

std::shared_ptr<Echo> Worker;

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

PluginReturn Echo::Precall(std::shared_ptr<ParameterBase> params) {
	std::cout << "[PRECALL] Call: " << _cmdToName[params.get()->GetID()] << " Param Count:" << params.get()->GetLen() << std::endl;
	return NO_ACTION;
}

PluginReturn Echo::Postcall(std::shared_ptr<ParameterBase> params) {
	std::cout << "[POSTCALL] Call: " << _cmdToName[params.get()->GetID()] << " Param Count:" << params.get()->GetLen() << " Performed: " << params.get()->Called() << std::endl;
	if (CallPerfromed)
		callcount++;
	return NO_ACTION;
}

extern "C"{

void init(std::vector<std::string> & cmd_list) {
	PLUG_BUILD_FACTORY(cmd_list)
}

CallReturn Precall(std::shared_ptr<ParameterBase> params){
	return PLUG_FACTORY_PTR->Precall(params);
}

CallReturn Postcall(std::shared_ptr<ParameterBase> params) {
	return PLUG_FACTORY_PTR->Postcall(params);
}

}