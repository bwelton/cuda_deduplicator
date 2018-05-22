#pragma once
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>
#include <cassert>
#include <fstream>
#include "BinaryRewriter.h"
#include "StacktraceInst.h"
#include "Constants.h"
#include "StackPoint.h"
#include "SymbolLookup.h"
#include "StackStorage.h"
#include "CallIDGenerator.h"
#include "GeneralFunctions.h"
#include "TimerInstrimentation.h"
#include "SyncTesting.h"
#include "ProcessControl.h"
#include "InstWrapper.h"
#include "InstrimentationLogger.h"
class StageThree {
public:
	StageThree(boost::program_options::variables_map vm);
	void Run();
	void ExtractLineInfo(std::map<uint64_t, StackRecord> & rec);
	std::map<uint64_t, std::vector<StackPoint> >  ReadStackKey();
	void GetTimingList(std::vector<StackPoint> & timingList, CallIDGenerator & cmap);
	void CreatePluginFile(std::vector<std::string> plugins);
private:
	InstrimentationLoggerPtr logger;
	GeneralFunctions _gen;
	boost::program_options::variables_map _vm;	
	BinaryRewriter _rw;
	std::map<uint64_t, StackRecord> _stackRecords;
	boost::filesystem::path _stageOnePath;
	boost::filesystem::path _stageThreePath;
};
