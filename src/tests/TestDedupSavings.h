#pragma once
#define BOOST_TEST_DYN_LINK
#include "CalculateDedupSavings.h"
#include <boost/test/unit_test.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <string>       
#include <iostream>     
#include <sstream>      
#include <time.h>

std::string CreateFakeTimeline(size_t elements, std::vector<uint64_t> & ids, 
							   std::vector<uint32_t> & hashes, std::vector<size_t> & sizes, 
							   std::vector<std::string> & types, std::vector<uint64_t> & duplicates) {
	std::stringstream ss;
	int duplicate;
	for (int i = 0; i < elements; i++) {
		ids.push_back(i+1);
		hashes.push_back(rand()%10000000);
		sizes.push_back(rand()%10000000);
		types.push_back(((rand() % 2 == 0) ? std::string("DeviceToHost") : std::string("HostToDevice")));
		if (rand() % 2 == 0 || i < 2){
			duplicates.push_back(0);
		} else {
			duplicates.push_back((rand() % (i - 1)) + 1);
		}
		ss << ids[i] << "," << hashes[i] << "," << sizes[i] << "," << types[i] << "," << duplicates[i] << std::endl;
	}
	return ss.str();
}

