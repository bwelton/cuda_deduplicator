#include "DataSyncTimer.h"
std::shared_ptr<DataSyncTimer> Worker;
thread_local int exited;

DataSyncTimer::DataSyncTimer(std::vector<std::string> & cmd_list) {
	exited = 0;
	_outFile.reset(new TFReaderWriter());
	_outFile->Open("DSTIME_trace.bin", TF_WRITE);
	//_out.reset(new CollisionOut(std::string("DT_collisions.txt")));
	_keyFile.reset(new StackKeyWriter(fopen("DSTIME_stacks.bin","w")));
}

DataSyncTimer::~DataSyncTimer() {
	exited = 1;
}

PluginReturn DataSyncTimer::Precall(std::shared_ptr<Parameters> params) {
	MemoryTransfer * mem = params->GetMemtrans();
	if (mem->IsTransfer() == true){
		mem->SetHashGeneration(true);
		mem->PreTransfer();		
	}
	return NO_ACTION;
}

PluginReturn DataSyncTimer::Postcall(std::shared_ptr<Parameters> params) {
	MemoryTransfer * mem = params->GetMemtrans();
	if (mem->IsTransfer() == true){

		auto start = std::chrono::high_resolution_clock::now();
		mem->Synchronize();
		auto stop = std::chrono::high_resolution_clock::now();
		// mem->SetHashGeneration(true);
		// mem->PostTransfer();		
		// std::vector<StackPoint> points;
		bool ret = GET_FP_STACKWALK(points);
		uint64_t pos = 0;
		if (ret == false) {
			std::cout << "unknown timing stack, discarding time" << std::endl;
			return NO_ACTION;
		} else {
			pos = _keyFile->InsertStack(points);
		}
		TF_Record rec;
		rec.type = TF_TRANSFERREC;
		rec.r.dynId = pos;
		rec.r.stackId = pos;
		std::chrono::duration<double> diff = stop-start;
		rec.r.time = diff.count();
		_outFile->Write(rec);
		
		// uint64_t originData = mem->GetOriginHash();
		// uint64_t transferedHash = mem->GetTransferHash();
		// if (transferedHash == 0) {
		// 	std::cerr << "[DataSyncTimer] Error getting hash of transfered data at stack id " << pos << std::endl;
		// 	return NO_ACTION;
		// }
		// bool duplicate = false;
		// bool overwrite = false;
		// bool prevTransfer = false;
		// uint64_t previousID = 0;

		// if (originData == transferedHash && originData != 0) {
		// 	duplicate = true;
		// 	overwrite = true;
		// }
		// if (_prevTransfers.find(transferedHash) != _prevTransfers.end()) {
		// 	duplicate =  true;
		// 	prevTransfer = true;
		// 	previousID = _prevTransfers[transferedHash];
		// } else {
		// 	_prevTransfers[transferedHash] = pos;
		// }
		// if (duplicate == true) {
		// 	_out->Write(pos, (overwrite ? uint64_t(1) : uint64_t(0)), (prevTransfer ? uint64_t(1) : uint64_t(0)), previousID);
		// }
	}
	return NO_ACTION;
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