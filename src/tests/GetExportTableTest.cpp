#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <string>
#include <fstream>
#include "cuda.h"
int main(int argc, char * argv[]) {
	std::stringstream ss; 
	unsigned int value = 0;
	CUuuid pExportTableId; 
	std::ifstream t;
	t.open(argv[1],std::ifstream::in);
	std::string line;
	cuInit(0);
	while (std::getline(t, line)) {
		std::string backup = line;
		void * ppExportTable;
		int pos = 0;
		std::string token = line.substr(0, line.find(std::string(",")));
		while (token.size() > 0) {
			ss << token;
			ss >> std::hex >> value;
			pExportTableId.bytes[pos] = (char)uint8_t(value);
			
			if (line.find(std::string(",")) == std::string::npos)
				break;
			line = line.substr(line.find(std::string(",")) + 1, line.size());
			// line.erase(0, line.find(std::string(",")) + 1);
			token = line.substr(0, line.find(std::string(",")));
			ss.clear();
			pos++;
		}
		ss.clear();
		int ret = (int) cuGetExportTable((const void **)&ppExportTable, &pExportTableId);
		if (ret == 0) {
			uint64_t count = (*((uint64_t **)ppExportTable))[0] / 8;
			std::cout << "Valid Table: " << backup << " Ret = " << ret << " Function Count: " << count << std::endl;
		}
	}
}