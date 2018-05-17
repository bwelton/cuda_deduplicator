#pragma once
#include "DyninstIncludes.h"
#include "StackPoint.h"
#include "DynOpsClass.h"
#include <map>
#include "BPatchRewriter.h"

class TimerInstrimentation {
public:
	TimerInstrimentation(BPatch_addressSpace * addrSpace, BPatchBinaryPtr binary);
	void InsertTimers(std::vector<StackPoint> points);
	void GetModules(std::map<std::string, BPatch_object *> & objs);
private:
	DynOpsClass _ops;
	BPatch_addressSpace * _addrSpace;
	BPatchBinaryPtr _bpBinary;
};
