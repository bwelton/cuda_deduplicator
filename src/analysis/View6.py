import json
import os
from TF_trace import TF_Trace
from Driver2 import JSStack, JSStackEntry, BuildMap

class NeighborStack:
	def __init__(self, stack):
		self._stack = stack
		self._data = {"Count": stack.GetCount(), "Remaining": stack.GetCount() - stack.GetSyncUses(), "UseAverage" :0.0,
					  "SyncUses" : stack.GetSyncUses(), "DeltaAvg" : 0.0}
		if  stack.GetCount() > 0:
			self._data["UseAverage"] = float(stack.GetTotalTime() / stack.GetCount())
		if stack.GetDelta()[0] > 0:
			self._data["DeltaAvg"] = float(stack.GetDelta()[1] / stack.GetDelta()[0])

	def GetUse(self):
		ret = {}
		if self._data["Remaining"] > 0:
			self._data["Remaining"] = self._data["Remaining"] - 1
			ret["UseAverage"] = self._data["UseAverage"]
			ret["DeltaAvg"] = self._data["DeltaAvg"]
			return ret
		return None


class StackEntry:
	def __init__(self, stack):
		## Equation: sum(timeSaveds) < sum(deltaSaves) = sum(timeSaves)
		self._stack = stack
		self._totalTime = 0.0
		self._count = 0
		self._deltaTimes = 0.0
		self._deltaCount = 0
		self._allStacks = {}
		self._neighbors = {}

	def GetTimeSavable(self):
		if (self._deltaTimes > self._totalTime):
			return self._totalTime
		return self._deltaTimes

	def BuildRelationships(self, idMap, idList, tf_records):
		myId = self._stack.GetID("tf_id")
		if myId == 0 or myId == 1:
			return
		for x in idMap:
			self._allStacks[x] = NeighborStack(idList[x])

		inChain = False
		for x in tf_records:
			entryId = int(x[2])
			if entryId == 0 or entryId not in self._allStacks:
				continue
			
			if entryId != myId and inChain == False:
				continue
			if entryId == myId:
				inChain = True

			useData = self._allStacks[entryId].GetUse()

			if useData == None:
				inChain = False
				continue
			if  entryId not in self._neighbors:
				self._neighbors[entryId] = self._allStacks[entryId]
			self._totalTime += useData["UseAverage"]
			self._deltaTimes += useData["DeltaAvg"]
			self._count += 1
			self._deltaCount += 1

class Aggregator:
	def __init__(self, stackEntry, cudaCall):
		self._stackEntry = stackEntry
		self._stacks = []
		self._cudaCall = cudaCall

	def AddStack(self, stack):
		self._stacks.append(stack)

	def GetUsageInfo(self):
		ret = {"CudaCall": self._cudaCall, "StackEntry" : self._stackEntry, "CallCount" : 0, "UnnecessaryCalls" : 0, "TotalTime" : 0.0, "TimeSaved" : 0.0}
		for x in self._stacks:
			ret["CallCount"] += x.GetCount()
			ret["UnnecessaryCalls"] += x.GetUnnecessaryCount()
			ret["TotalTime"] += x.GetTotalTime()
			ret["TimeSaved"] += x.GetEstimatedSavings()
		return ret

cudaFunctions = os.path.join(os.path.dirname(os.path.realpath(__file__)),"cudaFunctions.txt")
f = open(cudaFunctions, "r")
data = f.readlines()
f.close()

def RemoveNewline(line):
    return line.replace("\n","")

cudaCalls = {}
for x in data:
	cudaCalls[RemoveNewline(x)] = None


f = open("combined_stacks.json", "rb")
data = json.load(f)

stacks = []
for x in data:
	stacks.append(JSStack(data=x))


def GetFirstUserCall(stack):
	global cudaCalls
	tmp = stack.GetStacks()
	for x in range(0, len(tmp)):
		if tmp[x].GetFunctionName() in cudaCalls:
			return [tmp[x].GetFunctionName(),tmp[x-1]]
	return None

tf_trace = TF_Trace("TF_trace.bin")
tf_trace.DecodeFile()
indiPoints = {}
idMap = BuildMap(stacks, "tf_id")
stackEntries = []
for x in stacks:
	stackEntries.append(StackEntry(x))
	stackEntries[-1].BuildRelationships(idMap,stacks,tf_trace._records)

for x in stackEntries:
	print "Time saveable in global id - " + str(x._stack.GetGlobalId()) + " equals " +  str(x.GetTimeSavable())
	neighborIDs = []
	for y in x._neighbors:
		neighborIDs.append(x._neighbors[y]._stack.GetGlobalId())

	print "With the following neighbors:"
	print neighborIDs

	#print x
	# userCall = GetFirstUserCall(x)
	# #print userCall
	# if userCall == None:
	# 	continue
	# h = x.GetGlobalId()
	# if h not in indiPoints:
	# 	indiPoints[h] = Aggregator(userCall[1], userCall[0])
	# indiPoints[h].AddStack(x)



# print "%-60.60s | %-20.20s | %-20.20s | %-20.20s | %-20.20s | %-20.20s | %-4.4s" % ("File Name", 
# 	"Cuda Call", "Call Count", "Unnecessary Calls", "Total Time", "Time Saved", "ID")
# print ""

# tmpStore = []
# for x in indiPoints:
# 	usage = indiPoints[x].GetUsageInfo()
# 	stackInfo = usage["StackEntry"].to_dict()
# 	idList = ""
# 	for y in indiPoints[x]._stacks:
# 		idList += str(y.GetGlobalId()) + " "
# 	tmp = stackInfo["filename"].split("/")
# 	if len(tmp) > 0:
# 		stackInfo["filename"] = tmp[-1]
# 	tmpStore.append([usage["TimeSaved"],"%-60.60s | %-20.20s | %-20.20s | %-20.20s | %-20.20s | %-20.20s | %-4.4s" % (stackInfo["funcname"],
# 		usage["CudaCall"],str(usage["CallCount"]),str(usage["UnnecessaryCalls"]), str(usage["TotalTime"]), str(usage["TimeSaved"]), idList)])


# tmpStore.sort(key=lambda x: x[0])

# for x in tmpStore:
# 	print x[1]

# print "%-60.60s | %-20.20s | %-20.20s | %-20.20s | %-20.20s | %-20.20s | %-4.4s" % ("File Name", 
# 	"Cuda Call", "Call Count", "Unnecessary Calls", "Total Time", "Time Saved", "ID")