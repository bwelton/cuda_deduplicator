#define BOOST_TEST_MODULE dedupsavings_test
#define BOOST_TEST_MAIN
#include "TestDedupSavings.h"

BOOST_AUTO_TEST_SUITE( test_dedupsavings )

BOOST_AUTO_TEST_CASE(TestReadTimeline) {
	std::vector<uint64_t> ids;
	std::vector<uint32_t> hashes; 
	std::vector<size_t> sizes; 
	std::vector<uint64_t> duplicates;
	std::vector<std::string> types; 

	// Generate the fake timeline
	std::string out_timeline = CreateFakeTimeline(10000, ids, hashes, sizes, duplicates, types);
	
	// Write the timeline to a file
	std::ofstream ofs ("ReadTimelineTest.txt", std::ofstream::out);
	ofs << out_timeline;
	ofs.close();

	// Have dedup savings read it back to us. 
	CalculateDedupSavings x("ReadTimelineTest.txt","BLANK","BLANK");
	std::vector<TimelineRec> records;
	x.ReadTimeline(records);
	uint64_t id, dupid;
	size_t size;
	for (int i = 0; i < records.size(); i++) {
		std::tie(id, dupid, size) = records[i];
		BOOST_CHECK_EQUAL(id, ids[i]);
		BOOST_CHECK_EQUAL(dupid, duplicates[i]);
		BOOST_CHECK_EQUAL(size, sizes[i]);
	}
}
BOOST_AUTO_TEST_SUITE_END()