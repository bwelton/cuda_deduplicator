#include "TransferTimeline.h"
const char * OUT_FILENAME="dedup_timeline.log";
boost::recursive_mutex _timeline_mtx;
void TransferTimeline::AddTransfer(std::string type, uint32_t id, size_t size) {
	uint64_t origTransfer = 0;
	uint64_t count = 0;
	{
		boost::recursive_mutex::scoped_lock lock(_timeline_mtx);
		if (_pastTransfers.find(id) != _pastTransfers.end())
			origTransfer = _pastTransfers[id];
		else
			_pastTransfers[id] = _count;
		count = _count;
		_count++;
	}
	WriteLogEntry(type, id, size, count, origTransfer);
}

void TransferTimeline::WriteLogEntry(std::string & type, uint32_t id, size_t size, uint64_t count, uint64_t origTransfer) {
	std::stringstream s;
	s << count << "," << id << "," << size << "," << type << "," << origTransfer << std::endl;
	Write(s.str());
}


void TransferTimeline::Write(std::string a){
	_timeline_log.get()->Write(a);
}

TransferTimeline::TransferTimeline() {
	FILE * pfile = fopen("dedup_timeline.log", "w");
	if (pfile == NULL){
		fprintf(stderr, "%s\n", "Could not open timeline log file, writing output to stderr" );
		_timeline_log.reset(new LogInfo(stderr));
	}
	else {
		_timeline_log.reset(new LogInfo(pfile));
	}
	_count = 1;
}

TransferTimeline::~TransferTimeline() {
	
}


