#pragma once
#include "DyninstProcess.h"
#include "Constants.h"
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <string>
#include <vector>
#include <map>
#include <cassert>
#include <iostream>
#include <memory>
#include <algorithm>
#include <sys/types.h>
#include <unistd.h>
#include "APICaptureInstrimentation.h"

#include "DynOpsClass.h"
#include "Common.h"

// Dyninst includes
#include "CodeObject.h"
#include "CFG.h"
#include "PatchObject.h"
#include "PatchMgr.h"
#include "Point.h"
#include "BPatch_object.h"
#include "BPatch_snippet.h"
#include "BPatch.h"
#include "BPatch_binaryEdit.h"
#include "BPatch_image.h"
#include "BPatch_function.h"
#include "BPatch_Vector.h"
#include "BPatch_point.h"
#include "BPatch_addressSpace.h"
#include "BPatch_statement.h"
#include "BPatch_basicBlock.h"
#include "InstructionCategories.h"
#include "dynC.h"
#include "set"
#include "LogInfo.h"
#include "Constants.h"
#include "StackPoint.h"
#include "StackStorage.h"
#include "ReadStackKeys.h"
#include "TFReaderWriter.h"
#include "InstrimentationTracker.h"
#include "BinaryLocationIDMap.h"

#include "DyninstFunctionWraps.h"
#include "DyninstFunction.h"
#include "DyninstCallsite.h"
#include "MemRecDataFile.h"

/*typedef std::vector<CUMallocTracker *> GPUMallocVec;
typedef std::vector<GLIBMallocTracker *> CPUMallocVec;
typedef std::vector<CUMemTransferTracker *> MemTransVec;
*/

typedef	std::vector<int64_t> Int64Vec;

struct MallocSite;
struct FreeSite;
struct TransferPoint;

typedef std::shared_ptr<MallocSite> MallocPtr;
typedef std::shared_ptr<FreeSite> FreeSitePtr;
typedef std::shared_ptr<TransferPoint> TransferPointPtr;

typedef std::map<int64_t, TransferPointPtr> TransferPointMap;
typedef std::set<MallocPtr> MallocSiteSet;
typedef std::set<FreeSitePtr> FreeSiteSet;

struct FreeSite{	
	int64_t id;
	StackPoint p;
	uint64_t count;
	FreeSite(int64_t _id, StackPoint _p) : id(_id), p(_p), count(0) {};

	void AddFree(int64_t inCount) {
		count += inCount;
	};
	MallocSiteSet parents;
};

struct MallocSite {
	int64_t	id;
	StackPoint p;
	uint64_t count;
	FreeSiteSet children;

	MallocSite(int64_t _id, StackPoint _p) : id(_id), p(_p), count(0) {};

	void AddAlloc(FreeSitePtr destroyer, MallocPtr myself, int64_t inCount) {
		count += inCount;
		children.insert(destroyer);
		destroyer->AddFree(inCount);
		destroyer->parents.insert(myself);

	};

	void Destroy() {
		children.clear();
	};
};

struct TransferPoint {
	int64_t id;
	StackPoint p;
	uint64_t count;

	TransferPoint(int64_t _id, StackPoint _p) : id(_id), p(_p), count(0) {};

	void AddTransfer(MallocPtr m, int64_t inCount) {
		count += inCount;
		memAllocLocations.insert(m);
	}

	MallocSiteSet memAllocLocations;
};

template<typename T> 
void PrintSet(T & a, std::stringstream & out) {
	for (auto i : a)
		out << i->id << ",";
};

struct MemGraph {
	std::map<int64_t, MallocPtr> mallocPoints;
	std::map<int64_t, FreeSitePtr> freePoints;

	~MemGraph() {
		for (auto i : mallocPoints)
			i.second->Destroy();
	};
	MallocPtr GetMallocSite(int64_t id) {
		if (mallocPoints.find(id) == mallocPoints.end())
			return NULL;
		return mallocPoints[id];
	}
	std::string PrintMemoryGraph() {
		std::stringstream ss;
		for (auto i : mallocPoints) {
			ss << "[Malloc ID=" << i.first << "]" << " Call Count = " << i.second->count << " Associated FreeSites = ";
			PrintSet<FreeSiteSet>(i.second->children, ss);
			ss << std::endl;
		}

		for (auto i : freePoints) {
			ss << "[Free ID=" << i.first << "]" << " Call Count = " << i.second->count << " Associated MallocSites = ";
			PrintSet<MallocSiteSet>(i.second->parents, ss);
			ss << std::endl;
		}
		return ss.str();
	};
};

struct TransferGraph {
	TransferPointMap transfers;
	MallocPtr emptyMalloc;

	TransferGraph() {
		StackPoint p;
		emptyMalloc.reset(new MallocSite(-1,p));
	}

	void AddTransfer(int64_t id, int64_t mallocID, int64_t count, MemGraph & cpuGraph, std::map<int64_t, StackPoint> & idPoints) {
		MallocPtr tmp = cpuGraph.GetMallocSite(mallocID);
		TransferPointPtr tpoint;
		if (tmp == NULL) {
			tmp = emptyMalloc;
		}
		if (transfers.find(id) == transfers.end()) {
			tpoint.reset(new TransferPoint(id, idPoints[id]));
			transfers[id] = tpoint;
		} else {
			tpoint = transfers[id];
		}
		tpoint->AddTransfer(tmp, count);
	};

	std::string PrintTransferGraph() {
		std::stringstream ss;
		ss << "[TransferPoint::PrintTransferGraph] Transfer Graph" << std::endl;

		for (auto i : transfers) {
			ss << "[TransferGraph::PrintTransferGraph] Transfer ID " << i.first << " call count = " << i.second->count << " Associated MallocSites=";
			PrintSet<MallocSiteSet>(i.second->memAllocLocations, ss);
			ss << std::endl;
		}
		return ss.str();
	};
};


template<typename T> 
void BuildMemoryGraph(std::vector<T> & memSites, std::map<int64_t, StackPoint> & _idPoints, MemGraph & ret) {
	MallocPtr tmpMalloc;
	FreeSitePtr tmpFreePtr;
	for (auto i : memSites) {
		if (ret.mallocPoints.find(i->allocSite) == ret.mallocPoints.end()) {
			tmpMalloc.reset(new MallocSite(i->allocSite, _idPoints[i->allocSite]));
			ret.mallocPoints[i->allocSite] = tmpMalloc;
		} else {
			tmpMalloc = ret.mallocPoints[i->allocSite];
		}
		if (ret.freePoints.find(i->freeSite) == ret.freePoints.end()) {
			tmpFreePtr.reset(new FreeSite(i->freeSite, _idPoints[i->freeSite]));
			ret.freePoints[i->freeSite] = tmpFreePtr;
		} else {
			tmpFreePtr = ret.freePoints[i->freeSite];
		}
		tmpMalloc->AddAlloc(tmpFreePtr, tmpMalloc, i->count);
	}
}

class CallTransformation {
public:
	CallTransformation(GPUMallocVec & gpuVec,CPUMallocVec & cpuVec, MemTransVec & memVec, std::map<int64_t, StackPoint> & idPoints);

	//void GetCudaFreeMallocPairs(std::map<uint64_t, std::shared_ptr<DyninstFunction> > & funcMap, CudaFreeCallsites & callsites);
	//void GetMemTransReplacement(std::map<uint64_t, std::shared_ptr<DyninstFunction> > & funcMap, MemTransCallsites & callsites);
private:
	void BuildGraph();
	MemGraph _cpuGraph;
	MemGraph _gpuGraph;
	TransferGraph _transGraph;
	GPUMallocVec _gpuVec;
	CPUMallocVec _cpuVec;
	MemTransVec _memVec;
	std::map<int64_t, StackPoint> _idPoints;
};

typedef std::shared_ptr<CallTransformation> CallTransPtr;


// TransMap
	// 
