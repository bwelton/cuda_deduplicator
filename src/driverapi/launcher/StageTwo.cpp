#include "StageTwo.h"
void StageTwo::GetTimingList(std::vector<StackPoint> & timingList, CallIDGenerator & cmap) {
	std::set<uint64_t> alreadyPresent;
	for (auto i : _stackRecords) {
		StackPoint p = i.second.GetFirstCudaCall();
		if (p.libname.find("libcuda.so") != std::string::npos)
			if (alreadyPresent.find(p.libOffset) == alreadyPresent.end()) {
				alreadyPresent.insert(p.libOffset);
				p.timerID = cmap.InsertCallname(p.funcName);
				timingList.push_back(p);
			}
	}
}

StageTwo::StageTwo(boost::program_options::variables_map vm) :
	_vm(vm) {
	std::vector<std::string> progName = _vm["prog"].as<std::vector<std::string> >();
	_stageOnePath = boost::filesystem::current_path();
	_stageTwoPath = boost::filesystem::current_path();
	_stageOnePath /= "stageOne";
	_stageTwoPath /= "stageTwo";
	boost::filesystem::path dependsFile = _stageOnePath;
	dependsFile /= "NI_dependencies.txt";
	std::cout << "[StageTwo] Looking for dependency file at location: " << dependsFile.string() << std::endl;
	_rw = BinaryRewriter(progName[0], true, std::string("stageTwo"),true, dependsFile.string());
}

std::map<uint64_t, std::vector<StackPoint> >  StageTwo::ReadStackKey() {
	boost::filesystem::path keyFile = _stageOnePath;
	_stageOnePath /= "NI_synchronizations.key";
	std::cout << "[StageTwo] Reading Stack Key from file - " << keyFile.string() << std::endl;
	StackKeyReader reader(fopen(keyFile.string().c_str(), "rb"));
	return reader.ReadStacks();
}

void StageTwo::ExtractLineInfo(std::map<uint64_t, StackRecord> & rec) {
	SymbolMap symbolInfo;
	// Open all symtabs for functions found on the stack. 
	for (auto i : rec) {
		std::vector<std::string> lnames = i.second.GetLibNames();
		for (auto z : lnames){
			if (symbolInfo.find(z) == symbolInfo.end())
				symbolInfo[z] = std::shared_ptr<SymbolLookup>(new SymbolLookup(z));
		}	
	}
	for (auto & i : rec)
		i.second.GetStackSymbols(symbolInfo);
}

void StageTwo::Run() {
	std::map<uint64_t, std::vector<StackPoint> > ret = ReadStackKey();
	for (auto & i : ret)
		_stackRecords[i.first] = StackRecord(i.first, i.second);
	ExtractLineInfo(_stackRecords);
	boost::filesystem::path idMap = _stageTwoPath; 
	idMap /= "TF_timerIdMap.txt";
	CallIDGenerator cmap(idMap.string(), true);
	for (auto & i : _stackRecords) {
		std::cout << "[StageTwo] Adding " << i.second.GetFirstCudaCall().funcName << " with hash id " << i.first << std::endl;
		cmap.InsertCallname(i.second.GetFirstCudaCall().funcName, i.first);
	}
	std::vector<StackPoint> instPoints;
	GetTimingList(instPoints, cmap);
	std::cout << "[StageTwo] Timing Instrimentation will be inserted into " << instPoints.size() << " libcuda functions" << std::endl;
	for (auto i : instPoints)
		std::cout << "[StageTwo] Timing Instrumentation will be inserted into - " << i.funcName << std::endl;
}
