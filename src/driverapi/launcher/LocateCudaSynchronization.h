#pragma once
#include <string>
#include <map>
#include <sstream> 
#include <cstdlib>
#include <sys/types.h>
#include <dirent.h>
#include <cassert>
#include <boost/filesystem.hpp>
#include <openssl/md5.h>
#include <iostream>
#include <fstream>
#include "Common.h"

class LocateCudaSynchronization {
public:
	uint64_t FindLibcudaOffset();
	std::map<std::string, uint64_t> ReadDriverList();
	std::string GetMD5Sum(boost::filesystem::path ret);
	boost::filesystem::path FindLibCuda();
};
