#include "CallTransformation.h"

CallTransformation::CallTransformation(GPUMallocVec & gpuVec,CPUMallocVec & cpuVec, 
	MemTransVec & memVec, std::map<int64_t, StackPoint> & idPoints) : _gpuVec(gpuVec), _cpuVec(cpuVec), _memVec(memVec), _idPoints(idPoints) { }


void CallTransformation::BuildGraph() {
	BuildMemoryGraph(cpuVec,_idPoints, _cpuGraph);

	std::cerr << _cpuGraph.PrintMemoryGraph() << std::endl;
}