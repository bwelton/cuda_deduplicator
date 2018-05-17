// Stage 1 performs the following functions:
// 1. Generate stacktraces for synchronizations within the application (so we know what the profile).
#pragma once
#include <boost/program_options.hpp>
#include "BinaryRewriter.h"
#include "StacktraceInst.h"
#include "Constants.h"

class StageOne {
public:
	StageOne(boost::program_options::variables_map vm);
	bool Run();
private:
	boost::program_options::variables_map _vm;
	BinaryRewriter _rw;
};


// What each stage needs to output:
// 1. Stage One:
//    - NI_Dependencies.txt (\n seperated text list of libraries)
//    - NI_Synchronizations.key/bin StackKeyWriter/Reader (key file from libstacktrace.so)
// 2. Stage Two - Timing the synchroization calls:
//     Required Inputs:
//    - NI_Synchronizations.key/bin (keyfile from libstacktrace.so)
//     Outputs:
//    - TF_timekey.bin - StackKeyWriter/Reader
//    - TF_trace.bin - TFReaderWriter output (synch: dynId -> TF_timerIDMap, stackId ->  TF_timekey.bin, count, time) 
//    - TF_timerIdMap.txt (timerId,stackpoint)
// 3. Stage Three - load store analysis 
//    Required Inputs:
//    - NI_Synchronizations.txt
//    Instrimentation Outputs:
//    - BM_library.key (Binary Location Map Reader/Writer)
//    - BM_library.bin
//    Runtime Outputs:
//    - LS_StackKey.bin 
//    - LS_Trace.bin
