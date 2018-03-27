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

void PerformanceModel::AddFirstUses(std::map<uint64_t, StackPoint> uses) {
	_firstUses = uses;
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
  		std::cerr << params[0] << "," << params[1] << "," << params[2] << std::endl;
  		_callPoints.push_back(CallPoint(params[0], uint64_t(std::stoi(params[2])), ::atof(params[1].c_str())));
  	}
  	// Temporary fix for failure to capture first synchronization.
  	_callPoints[0].syncCount = _callPoints[0].syncCount - 1;
#ifdef DEBUG_MODEL
  	std::cerr << "Call info read from callDelay file" << std::endl;
  	for (auto i : _callPoints)
  		std::cerr << i.libCudaCallname << "," << i.time << "," << i.syncCount << std::endl;
#endif

  	// Check against the total number of syncs we have captured and their stack traces
  	uint64_t orderPos = 0;
  	for (auto & i : _callPoints) {
  		int count = i.syncCount;
  		i.startPos = orderPos;
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


void PerformanceModel::ReadStackFile(std::string s) {

#ifdef DEBUG_MODEL
	std::cerr << "Reading file : " << s << std::endl;
#endif
	FILE * inFile = fopen(s.c_str(), "rb");
	assert(inFile != NULL);
	while(!feof(inFile)) {
		int stackSize = 0;
		int pos = 0;
		if(fread(&stackSize, 1, sizeof(int), inFile) == 0)
			break;
		char * tmp = (char *) malloc(stackSize);
		int s = fread(tmp, 1, stackSize, inFile);
		assert(s == stackSize);
		uint64_t numRecords = ((uint64_t *)tmp)[0];
		pos += sizeof(uint64_t);
		std::vector<StackPoint> points;
		for (uint64_t i = 0; i < numRecords; i++) {
			StackPoint sp;
			pos += sp.Deserialize(&(tmp[pos]), stackSize - pos);
			points.push_back(sp);
		}
		AddStack(points);
	}
}

void PerformanceModel::ReadStackFiles() {
	// Read all files in the directory looking for stackOut files. 
	std::vector<std::string> files;
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (".")) != NULL) {
		while ((ent = readdir (dir)) != NULL) {
			if (strncmp(ent->d_name, "stackOut.", 9) == 0)
				files.push_back(std::string(ent->d_name));
		}
		closedir(dir);
	}
	assert(files.size() > 0);

	if (files.size() > 1) {
		std::cerr << "We have more than one stack output directory, multithreaded synchronization support not yet availible" << std::endl;
		assert(files.size() == 1);
	}
	ReadStackFile(files[0]);

}


void PerformanceModel::FinalProcessing() {
	std::stringstream sortByUse;
	std::stringstream sortByTime;
	std::vector<int> unncessarySyncs;

	uint64_t unnecssaryCount = 0;
	double unnecssaryTime = 0.0;
	for (int x = 0; x < _callPoints.size(); x++) {
		if (_firstUses.find(x) == _firstUses.end()) {
			unnecssaryCount += 1;
			unnecssaryTime += _callPoints[x].time;
			unncessarySyncs.push_back(x);
		}
	}

	std::cerr << "Unnecssary Synchronization Count: " << unnecssaryCount << "/" << _callPoints.size() << " " << float(unnecssaryCount) / float(_callPoints.size()) * 100 << "% unncessary" << std::endl;
	std::cerr << "Potential time savings: " << unnecssaryTime << "/" << _fastestExecTime << " " << unnecssaryTime / _fastestExecTime * 100 << "% of exectuion time wasted" << std::endl;

	// Sort by count
	std::map<uint64_t, uint64_t> unncessaryStack;
	for (auto x : unncessarySyncs) {
		uint64_t myStack = _stackOrder[_callPoints[x].startPos];
		if (unncessaryStack.find(myStack) == unncessaryStack.end())
			unncessaryStack[myStack] = 0;
		unncessaryStack[myStack] += 1;
	}

	sortByUse << "Table Performane Model Count: " << std::endl;
	sortByUse << "StackID\tStackCount" << std::endl;

	// Likely should be iterating over the key, should fix this since we shouldn't be iterating backward.
	for (auto iter : unncessaryStack) {
		sortByUse << iter.first << "\t\t" << iter.second << std::endl; 
	}
	for (auto iter : unncessaryStack) {
		sortByUse << "Stack with unncessary synchronization - " << iter.first << std::endl;
		for(auto i : _lineInfo[iter.first]) {
			sortByUse <<  i.first << "," << i.second.filename << "," << i.second.lineNum << std::endl;
		}
	}

	// Sort by time...
	std::map<uint64_t, double> unncessaryStackTime;
	for (auto x : unncessarySyncs) {
		uint64_t myStack = _stackOrder[_callPoints[x].startPos];
		if (unncessaryStack.find(myStack) == unncessaryStack.end())
			unncessaryStackTime[myStack] = 0.0;
		unncessaryStackTime[myStack] += _callPoints[x].time;
	}

	sortByTime << "Table Performance Model Time: " << std::endl;
	sortByTime << "StackID\tTime Wasted" << std::endl;
	for(auto x : unncessaryStackTime) {
		sortByTime << x.first << "\t\t" << x.second << std::endl;
	}
	for (auto x : unncessaryStackTime) {
		sortByTime << "Stack with unncessary synchronization: " << x.first << std::endl;
		for(auto i : _lineInfo[x.first]) {	
			sortByTime <<  i.first << "," << i.second.filename << "," << i.second.lineNum << std::endl;
		}
	}

	std::ofstream pfile;
	pfile.open("UnncessarySyncsCount.txt");
	pfile << sortByUse.str() << std::endl;
	pfile.close();
	pfile.open("UnncessarySyncsTime.txt");
	pfile << sortByTime.str() << std::endl;
	pfile.close();
	std::cerr << "Performance model is complete" << std::endl;
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
	for (auto & i : _stackPoints) {
		_lineInfo[i.first] = std::vector<std::pair<std::string, LineInfo> >();
		for(auto & z : i.second) {
			// Convert to line info and add  to _lineInfo
			if (symbolInfo.find(z.libname) == symbolInfo.end())
				continue;
			std::pair<std::string, LineInfo> tmp;
			symbolInfo[z.libname]->GetInfoAtLocation(z.libOffset, tmp);
			z.funcOffset = symbolInfo[z.libname]->GetFunctionOffset(z.libOffset);
			z.funcName = symbolInfo[z.libname]->GetFuncName(z.libOffset);
			z.fname = z.funcName;
			assert(z.funcOffset != 0);
			_lineInfo[i.first].push_back(tmp);
#ifdef DEBUG_MODEL
			// std::cerr << "Looking up " << z.libOffset << " in " << z.libname << std::endl;
			// std::cerr << "Returned Function Name: " << tmp.first << std::endl;
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
//#ifdef DEBUG_MODEL
	for (auto i : _callPair)
		std::cerr << "Synch at " << std::get<0>(i.second) << "," << std::get<1>(i.second) << "," << std::get<2>(i.second) << std::endl;
//#endif

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
		std::cerr << found.libname << std::endl;
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