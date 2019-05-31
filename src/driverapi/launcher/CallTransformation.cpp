#include "CallTransformation.h"

CallTransformation::CallTransformation(GPUMallocVec & gpuVec,CPUMallocVec & cpuVec, 
	MemTransVec & memVec, std::map<int64_t, StackPoint> & idPoints) : _gpuVec(gpuVec), _cpuVec(cpuVec), _memVec(memVec), _idPoints(idPoints) {

	BuildGraph();

}
void CallTransformation::BuildGraph() {
	BuildMemoryGraph(_cpuVec,_idPoints, _cpuGraph);
	BuildMemoryGraph(_gpuVec,_idPoints, _gpuGraph);


	for (auto i : _memVec) {
		_transGraph.AddTransfer(i->copyID, i->allocSite, _cpuGraph, _idPoints);
	}

	std::cerr << _cpuGraph.PrintMemoryGraph() << std::endl;
	std::cerr << _gpuGraph.PrintMemoryGraph() << std::endl;
	std::cerr << _transGraph.PrintTransferGraph() << std::endl;

}