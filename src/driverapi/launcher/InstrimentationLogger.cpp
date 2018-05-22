#include "InstrimentationLogger.h"
void InstrimentationLogger::InitKey(std::string key) {
	_storage[key] = std::vector<bool>(INST_END, false);
}

void InstrimentationLogger::Log(std::string libname, std::string name, INST_TYPE_INSERTED t) {
	std::string key = libname + "$" + name;
	if (_storage.find(key) != _storage.end()) {
		if (t != NO_TYPE)
			_storage[key][t] = true;
		return;
	}
	InitKey(key);
	if (t != NO_TYPE)
		_storage[key][t] = true;
	return;
}

void InstrimentationLogger::WriteToString(std::string & ret) {
	std::stringstream ss;
	ss << std::setfill(' ') << std::setw(30) << "Library Name" << " | " << std::setfill(' ') << std::setw(25) << "Function Name"
	   << " | " << std::setfill(' ') << std::setw(10) << "Entry Inst" << " | " <<  std::setfill(' ') << std::setw(10) << "Exit Inst" 
	   << " | " << std::setfill(' ') << std::setw(10) << "LS Inst" << std::endl;
	for (auto i : _storage) {
		boost::filesystem::path p(i.first.substr(0,i.first.find("$")));
		std::string tmp = i.first.substr(i.first.find("$")+1,i.first.size());
		if (tmp.size() > 25)
			tmp = tmp.substr(tmp.size()-24, tmp.size());

		ss << std::setfill(' ') << std::setw(30) << p.filename().string() << " | " << std::setfill(' ') << std::setw(25) << tmp << " | " << std::setfill(' ') << std::setw(10) << i.second[0] << " | " <<  std::setfill(' ') << std::setw(10) <<  i.second[1]  << " | " << std::setfill(' ') << std::setw(10) << i.second[2]  << std::endl;
	}
	ret = ss.str();
} 
