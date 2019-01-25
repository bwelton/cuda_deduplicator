import json
import os
from TF_trace import TF_Trace
from Driver2 import JSStack, JSStackEntry, BuildMap
import copy
FOLD_ID = 1
TOTAL_TIME = 0.0
cudaFunctions = os.path.join(os.path.dirname(os.path.realpath(__file__)),"cudaFunctions.txt")
f = open(cudaFunctions, "r")
data = f.readlines()
f.close()

def RemoveNewline(line):
    return line.replace("\n","")

cudaCalls = {}
for x in data:
    cudaCalls[RemoveNewline(x)] = None

def IsCudaCall(funcName):
    global cudaCalls
    if funcName in cudaCalls:
        return True
    return False

class EntryList:
    def __init__(self, nextStackDepth):
        self._data = {"DepthLevel" : nextStackDepth, "IdList" : []}


    def GetDepthID(self):
        return nextStackDepth._data["FoldID"]

    def Get(self, ident):
        if ident not in self._data:
            return None
        return self._data[ident]

    def AddStack(self, globalID):
        self._data["IdList"].append(globalID)


class StackDepthLevel:
    def __init__(self):
        global FOLD_ID
        self._data = {"EntryLists" : {} , "FoldID" : FOLD_ID}
        FOLD_ID = FOLD_ID + 1
        self._entires = {}

    def __CreateEntryList(self, name):
        if name not in self._data["EntryLists"]:
            self._data["EntryLists"][name] = EntryLists(StackDepthLevel())
        
    def AddEntry(self, stack, pos, nextMode = "Up"):
        funcName = stack.StripTemplate(pos)
        if funcName == None:
            return False
        self.__CreateEntryList(funcName)
        ret = False 
        if nextMode == "Up":
            ret = self._data["EntryLists"][funcName].Get("DepthLevel").AddEntry(stack, pos - 1)
        else:
            ret = self._data["EntryLists"][funcName].Get("DepthLevel").AddEntry(stack, pos + 1)

        if ret != False:
            self._data["EntryLists"][funcName].AddStack(stack.GetGlobalId())

        return True


    def GetRecursiveTime(self, entry):
        return [0.0,0.0]

    def GetAllTime(self, entry):
        ret = [0.0, 0.0]
        for x in self._data["EntryLists"]:
            tmp = self.GetRecursiveTime(self._data["EntryLists"][x])
            ret[0] += tmp[0]
            ret[1] += tmp[1]
        return ret

    def GetDependencies(self, entry):
        return ["None"]


    def GetMyString(self, priors = []):
        myDepth = len(priors) * 2
        ret = "=" * 100 + "\n"
        ret = " " + "FOLD_ID=" + str(self._data["FoldID"]) + "\n"
        for x in range(0,len(priors)):
            ret += " " + "  " * x + priors[x] + "\n"
        for x in self._data["EntryLists"]:
            times = self.GetRecursiveTime(self._data["EntryLists"][x])
            ret += " " + myDepth * "  " + "{0:3.3f}({1:2.2f}) {2:s} (Fold ID: {3:d})".format(times[0], times[1] *100, x, self._data["EntryLists"][x].GetDepthID()) + "\n"
            ret += " " + myDepth * "  " + "      Depends on synchronizations/transfers at\n"

            for y in self.GetDependencies(self._data["EntryList"][x]):
                ret += " " + myDepth * "  " + "           "  + y + "\n"

        return ret
    def GetOuputStrings(self, prior = []):
        ret = [self.GetMyString()]
        for x in self._data["EntryLists"]:
            newList = prior
            newList.append(x)
            ret.append(self._data["EntryLists"][x].Get("DepthLevel").GetOuputStrings(newList))
        return ret


class TemplateFolder:
    def __init__(self, stacks):
        global cudaCalls
        self._data = {"JSONStacks": copy.deepcopy(stacks), "EntryListsBot" : {}}
        for x in stacks["JSONStacks"]:
            x.TruncateToCudaCall(cudaCalls)

    def BuildBottomUp(self):
        global cudaCalls
        for x in self._data["JSONStacks"]:
            funcName = x.StripTemplate(x.GetStackLen() - 1)
            assert funcName != None
            if funcName not in cudaCalls:
                print "Unknown func - " + str(funcName)

            if funcName not in self._data["EntryListsBot"]:
                self._data["EntryListsBot"][funcName] =  EntryLists(StackDepthLevel())
            self._data["EntryListsBot"][funcName].Get("DepthLevel").AddEntry(x, x.GetStackLen() - 2)


    def BuildTopDown(self):
        for x in self._data["JSONStacks"]:
            funcName = x.StripTemplate(0)
            assert funcName != None
            if funcName not in self._data["EntryListsTop"]:
                self._data["EntryListsTop"][funcName] =  EntryLists(StackDepthLevel())
            self._data["EntryListsTop"][funcName].Get("DepthLevel").AddEntry(x, 1, "Down")     

    def Build(self):
        #self.BuildTopDown()
        self.BuildBottomUp()
        f = open("BottomUpTest.txt", "w")
        for x in self._data["EntryListsBot"]:
            times = self._data["EntryListsBot"].GetAllTime()
            startID = "{0:3.3f}({1:2.2f}) {2:s} (Fold ID: {3:d})".format(times[0], times[1] *100, x, self._data["EntryListsBot"][x].GetDepthID())
            ret = self._data["EntryListsBot"][x].GetOuputStrings()
            for y in ret:
                f.write(y + "\n")
        f.close()

if __name__ == "__main__":
    f = open("combined_stacks.json", "rb")
    data = json.load(f)
    test = TemplateFolder(data)
    test.Build()

