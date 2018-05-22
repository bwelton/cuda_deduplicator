#pragma once
#include <map>
#include <string>
#include <memory>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <boost/filesystem.hpp>
#include <sstream>   
enum INST_TYPE_INSERTED {
	NO_TYPE = -1,
	ENTRY_INST = 0,
	EXIT_INST = 1,
	LOAD_STORE_INST_TRACK = 2,
	INST_END = 3,
};

class InstrimentationLogger {
public:
	void InitKey(std::string key);
	void WriteToString(std::string & ret);
	void Log(std::string libname, std::string name, INST_TYPE_INSERTED t);

private:
	std::map<std::string, std::vector<bool> > _storage;
};

typedef std::shared_ptr<InstrimentationLogger> InstrimentationLoggerPtr;
