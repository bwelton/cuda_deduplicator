#include "CallTransformation.h"

CallTransformation::CallTransformation(GPUMallocVec & gpuVec,CPUMallocVec & cpuVec, 
	MemTransVec & memVec, std::map<int64_t, StackPoint> & idPoints, std::unordered_map<std::string, StackPoint> & wrapperReplacements) : _gpuVec(gpuVec), _cpuVec(cpuVec), _memVec(memVec), _idPoints(idPoints), _wrapperReplacements(wrapperReplacements) {

	BuildGraph();
	BuildRequiredSet();
}

std::map<uint64_t, std::vector<StackPoint> > CallTransformation::ReadMemRecorderKeys() {
	StackKeyReader r(fopen("DIOENES_MemRecUnknowns.bin","rb"));
	std::map<uint64_t, std::vector<StackPoint> > m = r.ReadStacks();
	for (auto & i : m) {
		StackPoint tmp = i.second.back();
		i.second.pop_back();
		std::reverse(i.second.begin(), i.second.end());
		for(int x = i.second.size() - 1; x >= 0; x--) {
			if(i.second[x].libname.find("lib/plugins/") != std::string::npos)
				i.second.pop_back();
			else {
				i.second.push_back(_wrapperReplacements[tmp.libname]);
				break;
			}
		}
	}	
	return m;
}


std::map<uint64_t, uint64_t> CallTransformation::MatchLStoMR(std::map<uint64_t, std::vector<StackPoint> > & LS, std::map<uint64_t, std::vector<StackPoint> > & MR) {
	std::map<uint64_t, uint64_t> ret;
	MatchLoadStoreStacksRecursive LSRecursive;
	for (auto i : LS) {
		LSRecursive.InsertEntry(i.second, 0, i.first);
	}
	
	for (auto i : MR) {
		uint64_t tmp = LSRecursive.FindEntry(i.second, 0);
		std::cout << "[CallTransformation::MatchLStoMR] MR " << std::dec << i.first << " has matched with LR " << std::dec << tmp << std::endl;
		if (tmp == 0){
			std::cout << "[CallTransformation::MatchLStoMR] WARNING COULD NOT MATCH MR " << std::dec << i.first << std::endl;
			continue;
		}
		if (ret.find(tmp) != ret.end()){
			std::cout << "[CallTransformation::MatchLStoMR] WARNING DUPLICATE EXISTS AT " << std::dec << i.first << " matched with LR " << std::dec << tmp << std::endl;
			std::cout << "[CallTransformation::MatchLStoMR] ORIGINAL VALUES! " << std::dec << ret[tmp] << " matched with LR " << std::dec << tmp << std::endl;
		}
		ret[tmp] = i.first;
	}	
	return ret;

}


void CallTransformation::BuildRequiredSet() {
	StackKeyReader r(fopen("LS_stackkey.txt","rb"));
	std::map<uint64_t, std::vector<StackPoint> > LS = r.ReadStacks();
	std::map<uint64_t, std::vector<StackPoint> > MR = ReadMemRecorderKeys();
	std::map<uint64_t, uint64_t> matchSet = MatchLStoMR(LS,MR);

	LSDependencyVec lvec;
	ReadDependencyFile dep(fopen("LS_syncaccess.bin", "rb"));
	dep.Read(lvec);
	ReadLSTraceDepFile traceDep(fopen("LS_trace.bin", "rb"));
	traceDep.Read();

	LSStackGraphVec sgraph;
	std::map<uint64_t, int> _mapToSgraph;
	int pos = 0;
	for (auto i : LS) {
		sgraph.push_back(LSStackGraph(i.second, i.first));
		_mapToSgraph[i.first] = pos;
		if (matchSet.find(i.first) != matchSet.end())
			sgraph.back()._idPointID = matchSet[i.first];
		pos++;
	}

	/*
	StackPointTree tree(_idPoints);
	for (auto & i : sgraph) {
		if(i._found == true){
			int64_t id = tree.FindID( i._beforeLibcuda);
			i._idPointID = id;
			if (id >= 0) {
				std::cerr << "[CallTransformation::BuildRequiredSet] Found ID Match for Call - " << i._beforeLibcuda.libname << "@" << i._beforeLibcuda.libOffset << " [ID = " << id << "]" << std::endl;
			} else {
				std::cerr << "[CallTransformation::BuildRequiredSet] NO MATCH Match for Call - " << i._beforeLibcuda.libname << "@" << i._beforeLibcuda.libOffset << " [ID = " << id << "]" << std::endl;			
			}
		}
	}*/

	for (size_t i = 0; i < lvec.size(); i++) {
		auto tmp = lvec[i];
		if (tmp->newDependents) {
			if (i < lvec.size() - 1) {
				if (!traceDep.IsInSet(lvec[i+1]->id))
					continue;
			} 
			auto it = _mapToSgraph.find(tmp->id);
			if (it != _mapToSgraph.end()) {
				sgraph[it->second]._required = true;
			}
		}
	}
/*
	for (auto i : lvec) {
		if(i->newDependents) {
			auto it = _mapToSgraph.find(i->id);
			if (it != _mapToSgraph.end()) {
				sgraph[it->second]._required = true;
				//std::cerr << "[CallTransformation::BuildRequiredSet] " 
			}
		}
	}
*/
	std::vector<FreeSitePtr> freeSites;

	for (auto i : sgraph) {
		if (i._idPointID > 0) {
			FreeSitePtr tmp = _gpuGraph.GetFreeSite(i._idPointID);
			if (tmp != NULL) {
				if (i._required == true) {
					tmp->required = 1;
					freeSites.push_back(tmp);
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
		if (i->required != 0) {
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


	// cudaMemTransfer replacement
	for (auto i : _transGraph.transfers) {
		if (i.first == -1)
			continue;
		if(ret->CheckArrayAndAddToIndex(CUMEMCPY_REP, i.second->p) == NEW_ENTRY) {
			ret->cudaMemcpyAsyncRepl.push_back(i.second->p);
			MallocSiteSet tmp = i.second->GetMallocSites();
			for (auto n : tmp) {
				if(ret->CheckArrayAndAddToIndex(MALLOC_REP, n->p) == NEW_ENTRY && n->IsEmpty() == false) 
					ret->mallocReplacements.push_back(n->p);
			}
		}
	}

	std::cout << ret->Print() << std::endl;
	_removeCalls = ret;	
}


RemovePointsPtr CallTransformation::GetRemoveCalls() {
	return _removeCalls;
}

void CallTransformation::BuildGraph() {
	auto MR = ReadMemRecorderKeys();
	std::map<int64_t, StackPoint> idPointKeys;
	for (auto i : MR) {
		idPointKeys[int64_t(i.first)] = i.second.back();
	}
	BuildMemoryGraph(_cpuVec,idPointKeys, _cpuGraph);
	BuildMemoryGraph(_gpuVec,idPointKeys, _gpuGraph);
	for (auto i : _memVec) {
		_transGraph.AddTransfer(i->copyID, i->allocSite, i->count, _cpuGraph, idPointKeys);
	}
	std::cerr << _cpuGraph.PrintMemoryGraph() << std::endl;
	std::cerr << _gpuGraph.PrintMemoryGraph() << std::endl;
	_gpuGraph.CheckForExitFrees();
	std::cerr << _transGraph.PrintTransferGraph() << std::endl;
}
