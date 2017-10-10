import os

class TimingProcess:
	def __init__(self, ident):
		self._ident = ident
		self._events = []

	def AddEvent(self, ident, size, stream):
		self._events.append([ident, size, stream])


class ReadTimingPacket:
	def __init__(self, filename):
		f = open(filename, "r")
		if f == None:
			print "Could not open CUPTI events file"
			return
		self._data = f.readlines()
		f.close()

	def Process():
		timingProcs = {}
		for x in self._data:
			tmp = x.split(",")
			key = tmp[3] + "," + tmp[4] + "," + tmp[5]
			if key not in timingProcs:
				timingProcs[key] = TimingProcess(key)
			timingProcs[key].AddEvent(int(tmp[0]), int(tmp[1]), int(tmp[2]))
		return timingProcs

