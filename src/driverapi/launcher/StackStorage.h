#include "StackPoint.h"
#include "SymbolLookup.h"

#define DEBUG_STACKRECORD 1

typedef std::map<std::string, std::shared_ptr<SymbolLookup> > SymbolMap;

struct SyncRangeRecord {
	uint64_t start;
	uint64_t end;
	SyncRangeRecord(uint64_t i) {
		start = i;
		end = i;
	};

	bool ExtendRange(uint64_t i) {
		if (end + 1 == i){
			end = end + 1;
			return true;
		}
		return false;
	};
	bool InRange(uint64_t i) {
		if (i == start || i == end || (i > start && i < end))
			return true;
		return false;
	};
};

struct TimingData {
	uint64_t start;
	uint64_t end;
	double time;
	TimingData() {}
	TimingData(uint64_t Start, uint64_t len, double Time) {
		start = Start;
		end = Start + len;
		time = Time;
	};
};



class StackRecord {
public:
	StackRecord();
	StackRecord(uint64_t id, std::vector<StackPoint> & points);
	void GetStackSymbols(SymbolMap & m);
	void AddStackRecord(uint64_t pos);
	void AddTimingData(uint64_t start, uint64_t len, double time);
	StackPoint GetFirstCudaCall();
private:
	uint64_t _id;
	std::vector<StackPoint> _points;
	std::vector<SyncRangeRecord> _ranges;
	std::vector<TimingData> _timingData;
};



