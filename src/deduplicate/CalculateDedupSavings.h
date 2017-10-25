// 
#pragma once
#include <map>
#include <tuple>
#include <iostream>
#include <sstream> 
#include <utility> 
#include <map>

//               Timline id,   size, duplicate id
typedef std::tuple<uint64_t, size_t, uint64_t> TimelineRec;

//                Timeline id, stream, procid, threadid
typedef std::tuple<uint64_t, uint64_t, uint64_t, uint64_t> CorrelationRec;

//               Timline id, size, duplicate id, stream, procid, threadid
typedef std::tuple<uint64_t, size_t, uint64_t, uint64_t, uint64_t, uint64_t> CombinedRecord;

//                 corr id, type_key, cname_key, start_time, end_time,   procid, threadid,     size, runcorr, ctx, dev, stream,   
typedef std::tuple<uint64_t, uint32_t, uint32_t,   uint64_t, uint64_t, uint64_t, uint64_t, uint64_t,     int, int, int, uint64_t > TimingRec;


class CalculateDedupSavings {
private:
	char * _timeline_file;
	char * _correlation_file;
	char * _timing_file;
	std::map<uint32_t, std::string> _typeKeys;
public:
	CalculateDedupSavings(char * timeline_file, char * correlation_file, char * timing_file);
	void ReadTimeline(std::vector<TimelineRec> & records);
	void ReadCorrelation(std::vector<CorrelationRec> & records);
	void ReadTiming(std::vector<TimingRec> & records, double & finalTime);
	void CombineTimelineCorrelation(std::vector<TimelineRec> & timeline, 
									std::vector<CorrelationRec> & correlation,
									std::vector<CombinedRecord> & output);
};
