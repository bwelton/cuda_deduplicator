#include "GeneralFunctions.h"

std::vector<std::string> GeneralFunctions::GetTokensFromLine(std::string line, std::string seperator) {
	std::vector<std::string> ret;
	boost::char_separator<char> seperators(seperator.c_str());
	boost::tokenizer<boost::char_separator<char>> tokens(line, seperators);
    for (const auto& t : tokens) {
    	ret.push_back(std::string(t));
    }
    return ret;
};

std::string GeneralFunctions::FindLibCuda() {
	// Search LD_LIBRARY_PATH for Libcuda
	const char* env_p = std::getenv("LD_LIBRARY_PATH");
	std::vector<std::string> pathsToTry = GetTokensFromLine(std::string(env_p), std::string(":"));
	for (auto i : pathsToTry) {
		
		boost::filesystem::path directory(i);
		std::cout << "[GeneralFunctions] Searching Directory " << directory.string() << " for libcuda.so.1" << std::endl;
		if(boost::filesystem::is_directory(directory))
			for(auto& entry : boost::make_iterator_range(boost::filesystem::directory_iterator(directory), {}))
				if(std::string(entry).find("libcuda.so.1") != std::string::npos)
					return std::string(entry);
	}
	return std::string("");

}