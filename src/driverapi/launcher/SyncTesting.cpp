#include "SyncTesting.h"

SyncTesting::SyncTesting(boost::program_options::variables_map vm) :
	_vm(vm) {

}

void SyncTesting::Run() {
	TimeApplications base(_vm);
	double time = base.Run();
}