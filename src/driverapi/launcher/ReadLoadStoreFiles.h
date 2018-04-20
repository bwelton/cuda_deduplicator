#pragma once

#include <map>
#include <set>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "StackPoint.h"
#include "BinaryLocationIDMap.h"
class ReadLoadStoreFiles {
public:
	ReadLoadStoreFiles(BinaryLocationIDMap * locationMap);
	void OutputTraceKey(std::string inDataFile, std::string outFile);
	void CreateStackKey(std::string inFile, std::string outFile);
private:
	std::map<uint64_t, std::vector<StackPoint> > ReadKeyFile(std::string inFile);
	FILE * _dataFile;
	FILE * _stackKeyFile;
	BinaryLocationIDMap * _map;


};