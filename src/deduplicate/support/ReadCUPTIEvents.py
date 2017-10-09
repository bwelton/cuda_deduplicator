import os
from sets import Set
import sys

class TransferEvent:
	def __init__(self, coorId):
		self._corrId = coorId
		self._events = []

	def __lt__(self, other):
		return self._corrId < other._corrId

	def AddEvent(self, event):
		self._events.append(event)

	def ContainsTransfer(self):
		for x in self._events:
			if x.IsTransfer() == True:
				return True
		return False

	def IsSynchronous(self):
		for x in self._events:
			if x.GetSynch() == True:
				return True
		return False
		


class ProcessEvents:
	def __init__(self, processId, threadId):
		self._processId = processId
		self._threadId = threadId
		self._events = []
		self._correlationIds = Set()

	def AddEvent(self, event):
		self._events.append(event)
		self._correlationIds.add(event.GetCoorelationID())

	def GenTransfers(self):
		retEvents = {}

		for x in self._correlationIds:
			retEvents[x] = TransferEvent(x)
		for x in _events:
			retEvents[x.GetCoorelationID()].AddEvent(x)

		orderedEvents = []
		for x in retEvents.keys():
			orderedEvents.append(retEvents[x])
		orderedEvents.sort()
		self._orderedEvents = orderedEvents


	def IsInProcess(self, event):
		if event.GetCoorelationID() in self._correlationIds:
			return 1

		if self._processId == event.GetProcessID():
			if self._threadId == event.GetThreadID():
				return 1
			elif event.GetThreadID() != -1:
				return -1
		elif event.GetProcessID() != -1:
			return -1
		return 0


class CUPTIEvent:
	def __init__(self, correlationId, eventType, textName, processId = -1, threadId = -1,
					startTime = 0, endTime = 0, size = 0, synch = False, contextId = -1, 
					streamId = -1, deviceId = -1, runtimeCorrelation = -1):
		self._processId = processId
		self._threadId = threadId
		self._correlationId = correlationId
		self._eventType = eventType
		self._size = size
		self._synch = synch
		self._textName = textName
		self._contextId = contextId
		self._streamId = streamId
		self._deviceId = deviceId
		self._runtimeCorrelation = runtimeCorrelation
		self.DetermineSync()

	def DetermineSync():
		if "async" not in self._textName.lower():
			self._synch = True
		self._synch = False

	def GetSynch():
		return self._synch

	def GetProcessID():
		return self._processId

	def GetThreadID():
		return self._threadId

	def GetCoorelationID(self):
		return int(self._correlationId)

	def IsTransfer(self):
		if "cumem" in self._textName.lower() or "Memcpy" in self._textName.lower() or "CP" in self._eventType:
			return True
		else:
			return False


class ReadCUPTIEvents:
	def __init__(self, filename):
		f = open(filename, "r")
		if f == None:
			print "Could not open CUPTI events file"
			return
		self._data = f.readlines()
		f.close()

	def ParseRuntime(self, line):
		return CUPTIEvent(int(line[4]), "RR", str(line[1]), int(line[2]), int(line[3]), int(line[5]), int(line[6]))

	def ParseDriver(self, line):
		return CUPTIEvent(int(line[4]), "DR", str(line[1]), int(line[2]), int(line[3]), int(line[5]), int(line[6]))

	def ParseCopy(self, line):
		return CUPTIEvent(int(line[5]), "CP", line[1], startTime=int(line[3]), endTime=int(line[4]), 
					size=int(line[2]), contextId=int(line[7]), streamId=int(line[9]),  deviceId=int(line[8]), 
					runtimeCorrelation=int(line[6]))

	def GenProcesses(self, events):
		ProcessHandles = Set()
		retProcess = []
		##
		# Find all possible processes
		for x in events:
			tmp = str(x.GetProcessID()) + "&" + str(x.GetThreadID())
			ProcessHandles.add(tmp)

		for x in ProcessHandles:
			tmp = x.split("&")
			retProcess.append(ProcessEvents(tmp[0],tmp[1]))

		##
		# Iterate through events assigning them to processes
		couldNotId = []
		for x in events:
			found = False
			for y in retProcess:
				if y.IsInProcess(x) == 1:
					y.AddEvent(x)
					found = True
					break
			if found == False:
				couldNotId.append(x)

		##
		# Second pass of the unfound id's. They may be identifiable now.
		for x in couldNotId:
			found = False
			for y in retProcess:
				if y.IsInProcess(x) == 1:
					y.AddEvent(x)
					found = True
					break
			if found == False:
				print "Could not associate event with correlationId " + x.GetCoorelationID() + " to a process"
		return retProcess

	def Process():
		events = []
		TET = []
		for x in self._data:
			tmp = x.split(",")
			if "\n" in tmp[-1]:
				tmp[-1] = tmp[-1][:-1]
			if "RR" in tmp[0]:
				events.append(ParseRuntime(tmp))
			elif "CP" in tmp[0]:
				events.append(ParseCopy(tmp))
			elif "DR" in tmp[0]:
				events.append(ParseDriver(tmp))
			elif "TET" in tmp[0]:
				TET.append(float(tmp[1]))
		del self._data
		procs = GenProcesses()

				
