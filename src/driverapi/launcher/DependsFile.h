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
			char * line = NULL;
    		size_t len = 0;
    		ssize_t read;
			while ((read = getline(&line, &len, f)) != -1) {
				ret.push_back(std::string(line, len));
			}
		}
		return ret;
	};

	std::set<std::string> _alreadyWritten;		
};