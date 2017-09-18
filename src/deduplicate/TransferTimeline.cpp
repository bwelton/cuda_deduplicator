#include "TransferTimeline.h"
const char * OUT_FILENAME="dedup_timeline.log"
void TransferTimeline::AddTransfer(std::string & type, uint32_t id, size_t size) {
	uint64_t origTransfer = 0;
	uint64_t count = 0;
	{
		boost::recursive_mutex::scoped_lock lock(_mtx);
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


void TransferTimeline::Write(std::string & a){
	_log.get()->Write(a);
}

TransferTimeline::TransferTimeline() {
	_log.reset(new LogInfo(fopen(OUT_FILENAME,"w")));
	_count = 1;
}


