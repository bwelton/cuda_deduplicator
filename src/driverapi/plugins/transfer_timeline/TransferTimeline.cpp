#include "TransferTimeline.h"
std::shared_ptr<TransferTimeline> Worker;
int exited = 0;

PluginReturn TransferTimeline::Precall(std::shared_ptr<Parameters> params) {
	MemoryTransfer * mem = params.get()->GetMemtrans();
	if (mem->CallIsTransfer() == false)
		return NO_ACTION;

	mem->PreTransfer();
	std::cerr << "[TRANSFER-TIMELINE] - Captured transfer: " << params.get()->GetName() << std::endl;
	return NO_ACTION;
}

PluginReturn TransferTimeline::Postcall(std::shared_ptr<Parameters> params) {
	if (params.get()->GetMemtrans()->CallIsTransfer() == false)
		return NO_ACTION;

	std::cerr << "[TRANSFER-TIMELINE] - Captured transfer Completed: " << params.get()->GetName() << std::endl;
	return NO_ACTION;
}

TransferTimeline::TransferTimeline(std::vector<std::string> & cmd_list) {
	exited = 0;
}

TransferTimeline::~TransferTimeline() {
	exited = 1;
}


extern "C"{

void init(std::vector<std::string> & cmd_list) {
	PLUG_BUILD_FACTORY(cmd_list)
}

PluginReturn Precall(std::shared_ptr<Parameters> params){
	if (exited == 1)
		return NO_ACTION;
	return PLUG_FACTORY_PTR->Precall(params);
}

PluginReturn Postcall(std::shared_ptr<Parameters> params) {
	if (exited == 1)
		return NO_ACTION;
	return PLUG_FACTORY_PTR->Postcall(params);
}

}