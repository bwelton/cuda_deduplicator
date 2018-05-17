#pragma once
#include <boost/tokenizer.hpp>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>

struct CallIDGenerator {
	std::map<std::string, uint64_t> _ids;
	std::ofstream _out;
	std::ifstream _in;
	uint64_t _curID;
	bool _write;
	bool _read;
	
	std::vector<std::string> GetTokensFromLine(std::string line, std::string seperator) {
		std::vector<std::string> ret;
		boost::char_separator<char> seperators(seperator.c_str());
		boost::tokenizer<boost::char_separator<char>> tokens(line, seperators);
	    for (const auto& t : tokens) {
	    	ret.push_back(std::string(t));
	    }
	    return ret;
	};
	~CallIDGenerator() {
		if (write)
			_out.close();
		else
			_in.close();
	}
	CallIDGenerator(std::string fname, bool write) {
		_write = write;
		_curID = 1;
		_read = false;
		if (write)
			_out.open(fname, std::ofstream::out);
		else
			_in.open(fname, std::ios::binary);
	};
	void ReadIDs() {
		if(_read)
			return;
		assert(write == false);
		for (std::string line; std::getline(_in, line); ){
			std::vector<std::string> items = GetTokensFromLine(line, std::string("$"));
			_ids[items[0]] = std::stoull(items[1]);
			std::cout << "[CallIDGenerator] Read item with Call Name: " << items[0] << " and id: " <<  std::stoull(items[1]) << std::endl;
		}
		_read = true;
	};	
	uint64_t InsertCallname(std::string s) {
		uint64_t ret = 0;
		if (!write){
			ReadIDs();
			if (_ids.find(s) != _ids.end())
				ret = _ids[s];
		} else {
			if(_ids.find(s) == _ids.end()){
				_out << _curID << "$" << s << std::endl;
				_ids[s] = _curID;
				_curID++;
			}
			ret = _ids[s];
		}
		return ret;
	};
		
};