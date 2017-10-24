from FileClasses import ReadDatFiles, CorrelateTimlineWithTiming
if __name__ == "__main__":
	x = ReadDatFiles("dedup_timeline.txt", "timing_info.txt", "timing_packet_corr.txt")
	tmp = CorrelateTimlineWithTiming(x.GetLists())
	tmp.Correlate()
	tmp.CalculateTS()