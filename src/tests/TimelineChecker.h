#pragma once
#include <cuda_runtime_api.h>
#include <cuda.h>
#include <boost/test/unit_test.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <sys/wait.h>
#include <stdio.h>
#include <memory>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <fstream>
#include <streambuf>
#include <utility>
#include <tuple>
#include <iostream>
#include <map>
#include "xxhash32.h"
#include "BaseTesting.h"

typedef std::map<int, std::tuple<uint32_t, size_t, std::string, int> >  TimelineMap;

template <typename T> 
uint32_t GetHash(std::shared_ptr<DeviceMemory<T> > mem) {
	return XXHash32::hash((char*)mem.get()->_cpuStore, mem.get()->_size * sizeof(T), 0);
}

template <typename T> 
uint32_t GetHash(T * data, size_t size) {
	return XXHash32::hash((char*)data, size * sizeof(T), 0);
}

TimelineMap ParseTimeline() {
	TimelineMap ret;
	std::ifstream t("dedup_timeline.txt");
	for (std::string line; std::getline(t, line); ){
		if(line.size() < 3) {
			break;
		}
		std::vector<std::string> tmp;
		char * tmp_str = strdup(line.c_str());
		char * pch = strtok(tmp_str,",");
		while (pch != NULL) {
			tmp.push_back(std::string(pch));
			pch = strtok(NULL,",");
		}
		free(tmp_str);
		if (tmp.size() != 5){
			std::cout << "Expected 5 arguments per line of timeline file, got " << tmp.size() << std::endl;
			BOOST_FAIL("Mismatch between timeline parser and the number of columns in timeline csv file");
		}
		try {
			ret[std::stoi(tmp[0])] = std::make_tuple(uint32_t(std::stoul(tmp[1])),size_t(std::stoull(tmp[2])), tmp[3], std::stoi(tmp[4])); 
		} catch(...) {
			BOOST_FAIL("Could not write timeline csv info to timeline map");
		}
	}
	return ret;
}