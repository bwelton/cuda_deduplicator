#include "CallTransformation.h"

CallTransformation::CallTransformation(GPUMallocVec & gpuVec,CPUMallocVec & cpuVec, 
	MemTransVec & memVec, std::map<int64_t, StackPoint> & idPoints) : _gpuVec(gpuVec), _cpuVec(cpuVec), _memVec(memVec), _idPoints(idPoints) {

	BuildGraph();
	BuildRequiredSet();
}


void CallTransformation::BuildRequiredSet() {
	StackKeyReader r(fopen("LS_stackkey.txt","rb"));
	std::map<uint64_t, std::vector<StackPoint> > m = r.ReadStacks();
	LSDependencyVec lvec;
	ReadDependencyFile dep(fopen("LS_syncaccess.bin", "rb"));
	dep.Read(lvec);
	LSStackGraphVec sgraph;
	std::map<uint64_t, int> _mapToSgraph;
	int pos = 0;
	for (auto i : m) {
		sgraph.push_back(LSStackGraph(i.second, i.first));
		_mapToSgraph[i.first] = pos;
		pos++;
	}
	StackPointTree tree(_idPoints);
	for (auto & i : sgraph) {
		if(i._found == true){
			int64_t id = tree.FindID( i._beforeLibcuda);
			i._idPointID = id;
			if (id >= 0) {
				std::cerr << "[CallTransformation::BuildRequiredSet] Found ID Match for Call - " << i._beforeLibcuda.libname << "@" << i._beforeLibcuda.libOffset << " [ID = " << id << "]" << std::endl;
			}
		}
	}

	for (auto i : lvec) {
		if(i->newDependents) {
			auto it = _mapToSgraph.find(i->id);
			if (it != _mapToSgraph.end()) {
				sgraph[it->second]._required = true;
				//std::cerr << "[CallTransformation::BuildRequiredSet] " 
			}
		}
	}
	std::vector<FreeSitePtr> freeSites;

	for (auto i : sgraph) {
		if (i._idPointID > 0) {
			FreeSitePtr tmp = _gpuGraph.GetFreeSite(i._idPointID);
			if (tmp != NULL) {
				if (i._required == true) {
					tmp->required = 1;
				} else {
					tmp->required = 0;
					freeSites.push_back(tmp);
				}
			}
		}
	}
	std::cerr << _gpuGraph.PrintRequiredSetFree() << std::endl;
	std::vector<MallocPtr> mallocSites;	
	_gpuGraph.TraverseFromPoint<FreeSitePtr,MallocPtr>(freeSites, mallocSites);

	RemovePointsPtr ret(new RemovePoints());
	for (auto i : freeSites) {
		if (i->required != 1) {
			ret->cudaFreeReqSync.push_back(i->p);
			std::cout << "[REQ]" << i->Print() << std::endl;
		} else {
			ret->cudaFreeReplacements.push_back(i->p);
			std::cout << "[REMOVE]" << i->Print() << std::endl;
		}
	}
	
	for (auto i : mallocSites) {
		std::cout << "[WRAP]" << i->Print() << std::endl;
		ret->cudaMallocReplacements.push_back(i->p);
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