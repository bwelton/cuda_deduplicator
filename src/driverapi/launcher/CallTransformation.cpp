#include "CallTransformation.h"

CallTransformation::CallTransformation(GPUMallocVec & gpuVec,CPUMallocVec & cpuVec, 
	MemTransVec & memVec, std::map<int64_t, StackPoint> & idPoints) : _gpuVec(gpuVec), _cpuVec(cpuVec), _memVec(memVec), _idPoints(idPoints) {

	BuildGraph();
	BuildRequiredSet();
}


void CallTransformation::BuildRequiredSet() {
	StackKeyReader r(fopen("LS_stackkey.txt","rb"));
	std::map<uint64_t, std::vector<StackPoint> > m = r.ReadStacks();
	LSDependency lvec;
	ReadDependencyFile dep(fopen("LS_syncaccess.bin", "rb"));
	dep.Read(lvec);
	LSStackGraphVec sgraph;
	for (auto i : m) {
		sgraph.push_back(LSStackGraph(i.second, i.first));
	}
}


void CallTransformation::BuildGraph() {
	BuildMemoryGraph(_cpuVec,_idPoints, _cpuGraph);
	BuildMemoryGraph(_gpuVec,_idPoints, _gpuGraph);
	for (auto i : _memVec) {
		_transGraph.AddTransfer(i->copyID, i->allocSite, i->count, _cpuGraph, _idPoints);
	}
	std::cerr << _cpuGraph.PrintMemoryGraph() << std::endl;
	std::cerr << _gpuGraph.PrintMemoryGraph() << std::endl;
	std::cerr << _transGraph.PrintTransferGraph() << std::endl;
}