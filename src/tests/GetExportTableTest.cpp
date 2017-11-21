#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "cuda.h"
int main(int argc, char * argv[]) {
	std::stringstream ss; 
	unsigned int value = 0;
	CUuuid pExportTableId; 
	std::ifstream t(std::string(argv[1]));
	std::string line;
	while (std::getline(t, line)) {
		void * ppExportTable;
		int pos = 0;
		printf("\nTable ID: ");
		std::string token = line.substr(0, line.find(std::string(",")));
		while (token.size() > 0) {
			ss << token;
			ss >> std::hex >> value;
			pExportTableId.bytes[pos] = (char)uint8_t(value);
			printf("%hhx:", pExportTableId.bytes[pos]);
			line.erase(0, line.find(std::string(",")) + 1);
			token = line.substr(0, line.find(std::string(",")));
		}
		int ret = (int) cuGetExportTable((const void **)&ppExportTable, &pExportTableId);
		printf(" - ret: %d\n",ret);
	}
}