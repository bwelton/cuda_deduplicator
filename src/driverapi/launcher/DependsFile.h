#pragma once
#include <set>
#include <string>
#include <vector>
#include <stdio.h>

struct DependsFile {
	FILE * f;
	bool _write;
	DependsFile() { f = NULL; _write = false; };
	DependsFile(std::string name, bool writing) {
		if (writing)
			f = fopen(name.c_str(), "wb");
		else
			f = fopen(name.c_str(), "rb");
		if (f == NULL) { 
			std::cerr << "[DependsFile] ERROR - COULD NOT OPEN FILE - " << name << std::endl;
		}
		_write = writing;
	};
	~DependsFile() {
		if (f != NULL)
			fclose(f);
	};
	void InsertLibrary(std::string name) {
		if (_alreadyWritten.find(name) == _alreadyWritten.end() && _write == true) {
			char tmpStr = '\n';
			_alreadyWritten.insert(name);
			fwrite(name.c_str(), sizeof(char), name.size(), f);
			fwrite(&tmpStr, sizeof(char), 1, f);
		}
	};
	std::vector<std::string> ReadLibraries() { 
		std::vector<std::string> ret;		
		if (_write == false) {
			fseek(f, 0L, SEEK_END);
			size_t sz = ftell(f);
			fseek(f, 0L, SEEK_SET);
			std::cout << "Size: " << sz << std::endl;
			char * tmp = (char *) malloc(sz * sizeof(char));
			assert(fread(tmp, sz, 1, f) == 1);
  			std::string tmpToken = std::string(tmp);
  			std::istringstream ifstring(tmpToken);
  			std::string line;
  			while (getline(ifstring, line, '\n')) {
  				if (line.size() < 2)
  					continue;
  				ret.push_back(line);
  			}
		}
		return ret;
	};

	std::set<std::string> _alreadyWritten;		
};