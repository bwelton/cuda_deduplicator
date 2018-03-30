#include "StackPoint.h"
#include "SymbolLookup.h"

#define DEBUG_STACKRECORD 1

typedef std::map<std::string, std::shared_ptr<SymbolLookup> > SymbolMap;

struct SyncRangeRecord {
	uint64_t start;
	uint64_t end;
	uint64_t id;
	SyncRangeRecord(uint64_t i) {
		start = i;
		end = i;
		id = 0;
	};

	SyncRangeRecord(uint64_t i, uint64_t ident) {
		start = i;
		end = i;
		id = ident;
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
	uint64_t id;
	double time;

	TimingData() {}
	TimingData(uint64_t Start, uint64_t len, double Time) {
		start = Start;
		end = Start + len;
		time = Time;
	};
	TimingData(uint64_t Start, uint64_t len, double Time, uint64_t ident) {
		start = Start;
		end = Start + len;
		time = Time;
		id = ident;
	};
};


class StackRecord {
public:
	StackRecord();
	StackRecord(uint64_t id, std::vector<StackPoint> & points);

	std::vector<std::string> GetLibNames();
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



class CudaCallMap {
public: 
	CudaCallMap();
	// ID for stack record containing the cuda call s.
	void InsertStackID(std::string & s, uint64_t id);
	uint64_t StackIDToGeneral(uint64_t id);
	uint64_t NameToGeneral(std::string s);

	// // Takes timer ID and sees if matches those for the c
	// void DoesIDMatch(std::string & s, uint64_t id);
	// uint64_t GetCallId(std::string & v);
	// uint64_t GetCallId(uint64_t v);
	// std::string GetCallFromString()
private:
	std::map<uint64_t, uint64_t> _stackToGeneral;
	//std::map<uint64_t, uint64_t> _generalToStack;
	std::map<std::string, uint64_t > _nameToGeneralID;
	uint64_t _pos;
	// StackID -> GeneralID
	// GeneralID,time,count
};

CudaCallMap::CudaCallMap() : _pos(1) {
	_nameToGeneralID[std::string("unknown")] = 0;
	_stackToGeneral[0] = 0;
}

void CudaCallMap::InsertStackID(std::string & s, uint64_t id) {
	if (_nameToGeneralID.find(s) == _nameToGeneralID.end()){
		_nameToGeneralID[s] = _pos;
		_stackToGeneral[id] = _pos;
		_pos++;
	}
}

uint64_t CudaCallMap::StackIDToGeneral(uint64_t id) {
	if (_stackToGeneral.find(id) == _stackToGeneral.end())
		assert(1 == 0);
	return _stackToGeneral[id];
}

uint64_t CudaCallMap::NameToGeneral(std::string s) {
	if (_nameToGeneralID.find(s) == _nameToGeneralID.end())
		assert(1 == 0);
	return _nameToGeneralID[s];
}




// class AppVisibleStacks {
// public:
// 	AppVisibleStacks();
// 	std::vector<StackPoint> GetUniqueCudaCalls();
// 	std::vector<uint64_t> GetIDs();
// 	//void AddStackRecord(StackRecord & rec);
// 	bool IsMember(StackRecord & rec);
// 	void AddStackRecord(uint64_t pos);
// 	void CheckTimingData(uint64_t start, uint64_t len, double time);
// private:
// 	std::vector<SyncRangeRecord> _ranges;
// };
