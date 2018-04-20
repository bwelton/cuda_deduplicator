#include "ReadLoadStoreFiles.h"

ReadLoadStoreFiles::ReadLoadStoreFiles(BinaryLocationIDMap * locationMap) : _map(locationMap) {}

std::map<uint64_t, std::vector<StackPoint> > ReadLoadStoreFiles::ReadKeyFile(std::string ifname) {
	std::map<uint64_t, std::vector<StackPoint> > ret;
	FILE * inFile = fopen(ifname.c_str(), "rb");
	if (inFile == NULL)
		return ret;
	fseek(inFile, 0, SEEK_END);
	uint64_t elementCount = ftell(inFile);
	fseek(inFile, 0, SEEK_SET);
	uint64_t readCount = 0;
	uint64_t size, stackId, locationId;
	while (readCount < elementCount) {
		size = 0;
		fread(&size, 1, sizeof(uint64_t), inFile);
		readCount += sizeof(uint64_t);
		fread(&stackId, 1, sizeof(uint64_t), inFile);
		ret[stackId] = std::vector<StackPoint>();
		readCount += sizeof(uint64_t);
		size -= sizeof(uint64_t);
		while (size > 0)  {
			fread(&locationId,1,sizeof(uint64_t), inFile);
			ret[stackId].push_back(_map->BuildStackPoint(locationId));
			size -= sizeof(uint64_t);
			readCount += sizeof(uint64_t);
		}
	}
	fclose(inFile);
	return ret;
}	

void ReadLoadStoreFiles::OutputTraceKey(std::string inDataFile, std::string outFile) {
	std::set<uint64_t> seenIds;
	FILE * inFile = fopen(inDataFile.c_str(), "rb");
	if (inFile == NULL)
		return;
	FILE * out = fopen(outFile.c_str(), "rb");
	StackKeyWriter writer(out);
	fseek(inFile, 0, SEEK_END);
	uint64_t elementCount = ftell(inFile);
	fseek(inFile, 0, SEEK_SET);
	uint64_t readCount = 0;
	uint64_t stackId, locationId;
	while (readCount < elementCount) {
		fread(&locationId, 1, sizeof(uint64_t), inFile);
		fread(&stackId, 1, sizeof(uint64_t), inFile);
		std::vector<StackPoint> tmp;
		if(seenIds.find(locationId) == seenIds.end()){
			tmp.push_back(_map->BuildStackPoint(locationId))
			writer.InsertStack(locationId, tmp);
			seenIds.insert(locationId);
		}
		readCount += (sizeof(uint64_t) * 2);
	}
	fclose(inFile);
}

void ReadLoadStoreFiles::CreateStackKey(std::string inFile, std::string outFile) {
	std::map<uint64_t, std::vector<StackPoint> > keys = ReadKeyFile(inFile);
	if (keys.size() == 0)
		return;
	FILE * out = fopen(outFile.c_str(), "rb");
	StackKeyWriter writer(out);
	for (auto i : keys) {
		writer.InsertStack(i.first, i.second);
	}
}