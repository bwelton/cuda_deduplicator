import os
from ReadCUPTIEvents import ReadCUPTIEvents
from ReadTimingEvents import ReadTimingPacket

class MatchIDs:
	def __init__(self, cuptiEvents, timingEvents):
		self._cuptiEvents = cuptiEvents
		self._timingEvents = timingEvents

	def Correlate(self):
		cuptiProcs = self._cuptiEvents.keys()
		timingProcs = self._timingEvents.keys()
		correlation = {}
		for x in timingProcs:
			found = False
			tEvent = self._timingEvents[x].GetNextEvent()
			for y in cuptiProcs:
				for z in range(0,10):
					cEvent = self._cuptiEvents[y].GetNextTransferEvent() 
					print cEvent
					print tEvent
					if cEvent.Compare(tEvent[1], tEvent[2]):
						print y + " correlates to " + x
						correlation[y] = x
						found = True
						break
				self._cuptiEvents[y].ResetPosition()
				if found == True:
					break
			self._timingEvents[x].ResetPosition()
		print correlation
		self._correlation = correlation

	def Process(self):
		self.Correlate()