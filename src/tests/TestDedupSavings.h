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

std::string CreateFakeCorrelation(size_t numProcs, size_t numThreads, size_t numStreams, std::vector<uint64_t> ids, 
		std::vector<size_t> sizes, std::vector<uint64_t> & streams, std::vector<uint64_t> & procid, std::vector<uint64_t> & threadid) {
	std::vector<uint64_t> procs;
	std::vector<uint64_t> threads;
	std::vector<uint64_t> nstreams;
	std::stringstream ss;
	for(int i = 0; i < numProcs; i++){
		procs.push_back((rand() % 20000) + 200);
	}
	for(int i = 0; i < numThreads; i++){
		threads.push_back((rand() % 50000) + 500000);
	}
	for(int i = 0; i < numStreams; i++){
		nstreams.push_back((rand() % 200)+1);
	}
	for (auto i : sizes){
		streams.push_back(nstreams[rand() % nstreams.size()]);
		threadid.push_back(threads[rand() % threads.size()]);
		procid.push_back(procs[rand() % procs.size()]);
	}
	for (int i = 0; i < ids.size(); i++) {
		ss << ids[i] << "," << sizes[i] << "," << streams[i] << "," << procid[i] << "," << threadid[i] << std::endl;
	}
	return ss.str();
}