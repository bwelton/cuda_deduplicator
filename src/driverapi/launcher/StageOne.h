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
	ProcessRewriter _rw;
};


