#pragma once
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>
#include <cassert>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>

class GeneralFunctions {
public:
	std::vector<std::string> GetTokensFromLine(std::string line, std::string seperator);
	std::string FindLibCuda();

};