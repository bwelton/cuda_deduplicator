#include "PerformanceModel.h"

#define DEBUG_MODEL 1
PerformanceModel::PerformanceModel() : _fastestExecTime(std::numeric_limits<double>::max()), _totalSyncs(0) {

}

void PerformanceModel::AddExecutionTime(double secs) {
	if (secs < _fastestExecTime) {
		std::cerr << "[PerfModel] Updating lowest execution time - " << _fastestExecTime << "=>" << secs << std::endl;
		_fastestExecTime = secs;
	}
}

void PerformanceModel::CaptureSyncTime() {
	std::ifstream ifs ("callDelay.out", std::ifstream::in);
	std::string line;
  	while (std::getline(ifs, line)) {
  		std::vector<std::string> params;
  		std::stringstream ss(line);
  		while(ss.good()){
  			std::string substr;
  			getline( ss, substr, ',' );
  			params.push_back(substr);
  		}
  		assert(params.size() == 3);
  		if (params[0][0] == ' ')
  			params[0].erase(0,1);
  		_callPoints.push_back(CallPoint(params[0], std::stod(params[1]), uint64_t(std::stoi(params[2]))));
  	}
#ifdef DEBUG_MODEL
  	std::cerr << "Call info read from callDelay file" << std::endl;
  	for (auto i : _callPoints)
  		std::cerr << i.libCudaCallname << "," << i.time << "," << i.syncCount << std::endl;
#endif

  	// Check against the total number of syncs we have captured and their stack traces
  	uint64_t orderPos = 0;
  	for (auto i : _callPoints) {
  		int count = i.syncCount;
  		for (int n = orderPos; n < _stackOrder.size(); n++) {
  			bool found = false;
  			// Search the line info of this stack ordering for the call 
  			for (auto m : _lineInfo[_stackOrder[n]]) {
  				if (m.first == i.libCudaCallname) {
  					found = true;
  					break;
  				}
  			}
  			
  			// If we cant find the callname in the stacks, our stack ordering DOES NOT match the timing data
  			// this run is useless.
  			if (found == false){
  				std::cerr << i.libCudaCallname << " NOT FOUND IN EXISTING LINE INFO FROM PREVIOUS RUNS! " << std::endl;
  				assert(found == true);
  			}

  			count -= 1;
 #ifdef DEBUG_MODEL
  			std::cerr << "Found " << i.libCudaCallname << " with " << count << " calls remaining" << std::endl;
 #endif

  			if (count == 0) {
  				orderPos = n+1;
  				break;
  			}
  		}
  		if (count > 0) {
  			std::cerr << "Stacks do not align between timing and synchronization run, exiting now!" << std::endl;
  			assert(count == 0);
  		}
  	}
  	std::cerr << "Timing data matches previous run, continuing profiling" << std::endl;
}

void PerformanceModel::AddStack(std::vector<StackPoint> stack) {
	std::stringstream ss;
	_totalSyncs+=1;
	for (auto z : stack) {
		ss << z.framePtr << std::endl;
	}
	uint64_t hash = std::hash<std::string>()(ss.str());
	std::cerr << hash << std::endl;
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
			// std::cerr << "Looking up " << z.libOffset << " in " << z.libname << std::endl;
			// std::cerr << "Returned Function Name: " << tmp.first << std::endl;
#endif
		}
	}
#ifdef DEBUG_MODEL
	// for(auto i : _lineInfo) {
	// 	std::cerr << "Stack with Synchronization" << std::endl;
	// 	for (auto z : i.second){
	// 		std::cerr << z.first << "," << z.second.filename << "," << z.second.lineNum << std::endl;
	// 	}
	// }
#endif
	std::cerr << "Synchronization Count: " << _totalSyncs << std::endl;
	ProcessStacks();
}


void PerformanceModel::ProcessStacks() {
	std::vector<std::string> cudaLibs = {"libcudnn.so","libaccinj64.so","libcublas.so","libcudart.so","libcufft.so","libcufftw.so","libcuinj64.so","libcurand.so","libcusolver.so","libcusparse.so","libnppc.so","libnppial.so","libnppicc.so","libnppicom.so","libnppidei.so","libnppif.so","libnppig.so","libnppim.so","libnppist.so","libnppisu.so","libnppitc.so","libnpps.so","libnvblas.so","libnvgraph.so","libnvrtc-builtins.so","libnvrtc.so"};
	// Find first user CUDA call and the parent who made the call.
	for (auto i : _stackPoints) {
		std::string parentParentCall;
		std::string parentCall;
		std::string cudaCall;
		for (int z = i.second.size() - 1;  z > 0; z = z - 1){
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
			else {
				parentParentCall = parentCall;
				parentCall = _lineInfo[i.first][z].first;
			}
		}
		_callPair[i.first] = std::make_tuple(parentParentCall,parentCall,cudaCall);
	}
#ifdef DEBUG_MODEL
	//for (auto i : _callPair)
	//	std::cerr << "Synch at " << std::get<0>(i.second) << "," << std::get<1>(i.second) << "," << std::get<2>(i.second) << std::endl;
#endif

}

void PerformanceModel::GetTimingList(std::vector<StackPoint> & timingList) {
	std::set<uint64_t> alreadyPresent;
	for (auto i : _stackPoints) {
		StackPoint found;
		for (int z = i.second.size() - 1;  z > 0; z = z - 1) {
			if (i.second[z].libname.find("libcuda.so") != std::string::npos){
				found = i.second[z];
				found.funcName = _lineInfo[i.first][z].first;
				break;
			}
		}
		assert(found.funcOffset != 0);
		if (alreadyPresent.find(found.funcOffset) == alreadyPresent.end()){
			timingList.push_back(found);
			alreadyPresent.insert(found.funcOffset);
		}
	}
#ifdef DEBUG_MODEL
	//for (auto i : timingList)
	//	std::cerr << "Inserting timing info into - " << i.funcName << std::endl;
#endif
}