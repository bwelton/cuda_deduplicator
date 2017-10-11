import sys
from ReadCUPTIEvents import ReadCUPTIEvents
from ReadTimingEvents import ReadTimingPacket
from MatchIDs import MatchIDs
ReadEvents = ReadCUPTIEvents(sys.argv[1])
ReadTimingLog = ReadTimingPacket(sys.argv[2])
match = MatchIDs(ReadEvents.Process(),ReadTimingLog.Process())
match.Process()