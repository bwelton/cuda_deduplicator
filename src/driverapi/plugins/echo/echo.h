#pragma ONCE

#include "PluginCommon.h"

extern "C" {
	void init(std::vector<std::string> & cmd_list);
	CallReturn Precall(DriverAPICall t, std::shared_ptr<ParameterBase> params);
	CallReturn Postcall(DriverAPICall t, std::shared_ptr<ParameterBase> params, bool CallPerfromed);
}

class Echo {
public:
	Echo(std::vector<std::string> & cmd_list);
	~Echo();
	CallReturn Precall(DriverAPICall t, std::shared_ptr<ParameterBase> params);
	CallReturn Postcall(DriverAPICall t, std::shared_ptr<ParameterBase> params, bool CallPerfromed);
private:
	std::map<int,std::string> _cmdToName;
	size_t callcount;
};

#define PLUG_BUILD_FACTORY(param) \
	if (Worker.get() == NULL) { \
		Worker.reset(new Echo(param)); \
	} 

#define PLUG_FACTORY_PTR Worker.get()
