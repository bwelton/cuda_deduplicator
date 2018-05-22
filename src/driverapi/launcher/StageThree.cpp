#include "StageThree.h"
#include "LoadStoreInstBinaryRewrite.h"
#include <fstream>
void StageThree::GetTimingList(std::vector<StackPoint> & timingList, CallIDGenerator & cmap) {
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

StageThree::StageThree(boost::program_options::variables_map vm) :
	_vm(vm) {
	std::vector<std::string> progName = _vm["prog"].as<std::vector<std::string> >();
	_stageOnePath = boost::filesystem::current_path();
	_stageThreePath = boost::filesystem::current_path();
	_stageOnePath /= "stageOne";
	_stageThreePath /= "stageThree";
	boost::filesystem::path dependsFile = _stageOnePath;
	dependsFile /= "NI_dependencies.txt";
	std::cout << "[StageThree] Looking for dependency file at location: " << dependsFile.string() << std::endl;
	_rw = BinaryRewriter(progName[0], true, std::string("stageThree"),true, dependsFile.string());
}

std::map<uint64_t, std::vector<StackPoint> >  StageThree::ReadStackKey() {
	boost::filesystem::path keyFile = _stageOnePath;
	keyFile /= "NI_synchronizations.key";
	std::cout << "[StageTwo] Reading Stack Key from file - " << keyFile.string() << std::endl;
	StackKeyReader reader(fopen(keyFile.string().c_str(), "rb"));
	return reader.ReadStacks();
}

void StageThree::ExtractLineInfo(std::map<uint64_t, StackRecord> & rec) {
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


void StageThree::Run() {
	logger.reset(new InstrimentationLogger());

	std::map<uint64_t, std::vector<StackPoint> > ret = ReadStackKey();
	boost::filesystem::path stageOneLibCuda = _stageOnePath;
	stageOneLibCuda /= "libcuda.so.1";

	std::string libcudaLocation = _gen.FindLibCuda();
	for (auto & i : ret)
		for (auto & z : i.second)
			if (z.libname.find("libcuda.so.1") != std::string::npos)
				z.libname = stageOneLibCuda.string();

	for (auto & i : ret)
		_stackRecords[i.first] = StackRecord(i.first, i.second);
	ExtractLineInfo(_stackRecords);
	boost::filesystem::path idMap = _stageThreePath; 
	idMap /= "TF_timerIdMap.txt";
	CallIDGenerator cmap(idMap.string(), true);
	for (auto & i : _stackRecords) {
		std::cout << "[StageThree] Adding " << i.second.GetFirstCudaCall().funcName << " with hash id " << i.first << std::endl;
		cmap.InsertCallname(i.second.GetFirstCudaCall().funcName);
	}
	std::vector<StackPoint> instPoints;
	GetTimingList(instPoints, cmap);
	//std::cout << "[StageThree] Timing Instrimentation will be inserted into " << instPoints.size() << " libcuda functions" << std::endl;
	// for (auto i : instPoints)
	// 	std::cout << "[StageThree] Timing Instrumentation will be inserted into - " << i.funcName << std::endl;
	for (auto & i : instPoints) {
		std::cout << "[StageThree] Setting Libcuda Location to - " << libcudaLocation << std::endl;
		i.libname = libcudaLocation;
	}

	// //_rw.OpenLibrary(libcudaLocation);
	// _rw.OpenLibrary(std::string(LOCAL_INSTALL_PATH) + std::string("/lib/plugins/libTimeCall.so"));
	// TimerInstrimentation TI(_rw.GetAppBinary()->GetAddressSpace(), _rw.GetAppBinary());
	// TI.InsertTimers(instPoints);
	// _rw.LoadObject(std::string("libcuda.so.1"));
	std::vector<uint64_t> skips;
	uint64_t total_functions = 0;
	std::string def(WRAPPER_DEF);
	InstWrapper instWrapper(&_rw,def);
	LoadStoreInstBinaryRewrite ls_rw(&_rw, logger);
	ls_rw.InsertLoadStoresInit(skips, total_functions, instPoints, _stackRecords, instWrapper.GetWrappedFuncNames());
	// instWrapper.Run(libcudaLocation);

	std::vector<std::string> pluginNames = {"libSynchTool"};
	CreatePluginFile(pluginNames);
	std::string outData;
	logger->WriteToString(outData);
	boost::filesystem::path outImap = _stageThreePath; 
	outImap /= "OutInstrimentation.txt";
	std::cout << outData << std::endl;
	std::cout << "Saving outinstrimentation to : " << outImap.string() << std::endl;
	std::ofstream outInst(outImap.string().c_str(), std::ofstream::out);
	outInst << outData << std::endl;
	outInst.close();
	// std::string def(WRAPPER_DEF);	
	// std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string> > extras;
	// LogInfo log(std::string("InstRun.txt"), std::string("[InstRun]"), true);
	// ProcessController proc(_vm, &log);
	// proc.SetRewriterMode(_rw.GetAppBinary());
	// proc.InsertInstrimentation(def);
	// std::vector<uint64_t> skips;
	// uint64_t total_functions = 0;
	// proc.InsertLoadStores(skips, total_functions, instPoints, _stackRecords);
	// {
	// 	std::shared_ptr<LoadStoreInst> lsPtr = proc.GetLoadStorePtr();
	// 	lsPtr->WriteBinLocation(_stageThreePath.string());
	// }
}

//#define PLUGIN_LIST {"@CMAKE_INSTALL_PREFIX@/lib/plugins/libCUPTIEventHandler.so","@CMAKE_INSTALL_PREFIX@/lib/plugins/libTimeCall.so","@CMAKE_INSTALL_PREFIX@/lib/plugins/libSynchTool.so"};
void StageThree::CreatePluginFile(std::vector<std::string> plugins) {
	std::vector<std::string> PluginList = PLUGIN_LIST;
	std::ofstream pfile;
	boost::filesystem::path pluginPath(_stageThreePath);
	_stageThreePath /= "pluginlist.txt";

	pfile.open(_stageThreePath.string().c_str());
	for (auto i : plugins) {
		for (auto z : PluginList) {
			if (z.find(i) != std::string::npos){
				pfile << z << std::endl;
				break;
			}
		}
	}
	pfile.close();
}
