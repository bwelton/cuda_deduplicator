#include "PerformanceModel.h"

#define DEBUG_MODEL 1
PerformanceModel::PerformanceModel() : _fastestExecTime(std::numeric_limits<double>::max()) {

}

void PerformanceModel::AddExecutionTime(double secs) {
	if (secs < _fastestExecTime) {
		std::cerr << "[PerfModel] Updating lowest execution time - " << _fastestExecTime << "=>" << secs << std::endl;
		_fastestExecTime = secs;
	}
}

void PerformanceModel::AddStack(std::vector<StackPoint> stack) {
	std::stringstream ss;
	for (auto z : stack) {
		ss << z.framePtr << std::endl;
	}
	uint64_t hash = std::hash<std::string>()(ss.str());
	_stackOrder.push_back(hash);
	if (_stackCount.find(hash) == _stackCount.end())
		_stackCount[hash] = 0;
	_stackCount[hash] += 1;
	if (_stackPoints.find(hash) == _stackPoints.end())
		_stackPoints[hash] = stack;	
}

void PerformanceModel::ExtractLineInfo() {
	std::map<std::string, std::shared_ptr<SymbolLookup> > symbolInfo;
	
	// Open all symtabs for functions found on the stack. 
	for (auto i : _stackPoints) {
		for (auto z : i.second){
			if (symbolInfo.find(z.libname) == symbolInfo.end())
				symbolInfo[z.libname] = std::shared_ptr<SymbolLookup>(new SymbolLookup(z.libname));
		}	
	}

	// Decode line info for every stack
	for (auto i : _stackPoints) {
		_lineInfo[i.first] = std::vector<std::pair<std::string, LineInfo> >();
		for(auto z : i.second) {
			// Convert to line info and add  to _lineInfo
			if (symbolInfo.find(z.libname) == symbolInfo.end())
				continue;
			std::pair<std::string, LineInfo> tmp;
			symbolInfo[z.libname]->GetInfoAtLocation(z.libOffset, tmp);
			_lineInfo[i.first].push_back(tmp);
#ifdef DEBUG_MODEL
			std::cerr << "Looking up " << z.libOffset << " in " << z.libname << std::endl;
			std::cerr << "Returned Function Name: " << tmp.first << std::endl;
#endif
		}
	}
#ifdef DEBUG_MODEL
	for(auto i : _lineInfo) {
		std::cerr << "Stack with Synchronization" << std::endl;
		for (auto z : i.second){
			std::cerr << z.first << "," << z.second.filename << "," << z.second.lineNum << std::endl;
		}
	}
#endif
	ProcessStacks();
}


void PerformanceModel::ProcessStacks() {
	std::vector<std::string> cudaLibs = {"libcudnn.so","libaccinj64.so","libcublas.so","libcudart.so","libcufft.so","libcufftw.so","libcuinj64.so","libcurand.so","libcusolver.so","libcusparse.so","libnppc.so","libnppial.so","libnppicc.so","libnppicom.so","libnppidei.so","libnppif.so","libnppig.so","libnppim.so","libnppist.so","libnppisu.so","libnppitc.so","libnpps.so","libnvblas.so","libnvgraph.so","libnvrtc-builtins.so","libnvrtc.so"};
	// Find first user CUDA call and the parent who made the call.
	for (auto i : _stackPoints) {
		std::string parentCall;
		std::string cudaCall;
		for (int z = 0;  z < i.second.size(); z++){
			bool found = false;
			for (auto n : cudaLibs){
				if (i.second[z].libname.find(n) != std::string::npos){
					found = true;
					break;
				}
			}
			if (found != true) {
				if (_lineInfo[i.first][z].first.find("_ZN6cudart") != std::string::npos)
					found = true;
			}

			if (found == true) {
				cudaCall = _lineInfo[i.first][z].first;
				break;
			}
			else 
				parentCall = _lineInfo[i.first][z].first;
		}
		_callPair[i.first] = std::make_pair(parentCall,cudaCall);
	}
#ifdef DEBUG_MODEL
	for (auto i : _callPair)
		std::cerr << "Synch at " << i.second.first << "," << i.second.second << std::endl;
#endif
}