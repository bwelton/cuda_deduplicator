import sys
import os
import struct
from sets import set
from  ReadStackFiles import StackReader
from LS_TraceBin import LS_TraceBin
from TF_trace import TF_Trace

class MatchTimeToLSStack:
    def __init__(self, TF_timekey, LS_stackkey):
        self._tf = TF_timekey
        self._ls = LS_stackkey

    def CompareStacks(self, ls, tf):
        #ls stack will always be longer
        start = 0
        for x in ls:
            found = False
            nextPos = start
            for y in range(start, len(tf)):
                nextPos += 1
                if x == tf[y]:
                    found = True
                else if start != 0:
                    found = False
                    break
            if found == False:
                return False
            start = nextPos


        # for x in range(0,len(ls)):
        #     found = False
        #     for y in range(0,len(tf)):
        #         if ls[x] == tf[y]:
        #             found = True
        #             break
        #     if (found == False):
        #         return False

            #if str(ls[x]) != str(tf[x]):
            #    return False
        return True


    def PruneStack(self, stack):
        ## Remove all elements at the beginning of the stack such as 
        ## startmain.
        removeElements = []
        for x in range(0, len(stack)):
            if "/lib64/libc" in stack[x]._libname or "main" == stack[x]._funcname:
                removeElements.append(x)
            else:
                break

        removeElements = list(set(removeElements))
        ret = []
        for x in range(0, len(stack)):
            if x in removeElements:
                continue
            else:
                ret.append(stack[x])
        return ret

    def GetMatchSet(self):
        # returns [(TFNum,LSNum)]
        ret = []
        tf_stacks = self._tf.GetAllStacks()
        ls_stacks = self._ls.GetAllStacks()
        for x in tf_stacks:
            individaulStack = x.GetStack()
            pruned = self.PruneStack(individaulStack)
            for y in ls_stacks:
                if self.CompareStacks(y, pruned):
                    ret.append([x._ident,y._ident])
        print "MATCH SET"
        print ret
        return ret


class DuplicateEntry:
    def __init__(self, overwrite, prevTransferHash):
        self._overwrite = overwrite
        self._prevTransferHash = prevTransferHash

    def IsDuplicate(self):
        if self._overwrite == 1 or self._prevTransferHash != 0:
            return True
        return False

class DataTransfer:
    def __init__(self, hashVal, position, stack):
        self._hash = hashVal
        self._pos = position
        self._stack = stack
        self._preSync = []
        self._totalTime = []
        self._cpuOverhead = []
        self._duplicates = []

    def FindSavings(self, idToHash):
        tmpHash = {}
        for x in idToHash:
            tmpHash[idToHash[x]] = x
        overwriteIssues = 0
        previousTransfers = 0
        previousTransferList = []
        totalTimeSavings = 0.0
        for x in range(0,len(self._duplicates)):
            if self._duplicates[x].IsDuplicate():
                if len(self._totalTime) > x:
                    totalTimeSavings += self._totalTime[x]
                if self._duplicates[x]._overwrite == 1:
                    overwriteIssues += 1
                else:
                    previousTransfers += 1
                    if self._duplicates[x]._prevTransferHash in tmpHash:
                        previousTransferList.append(tmpHash[self._duplicates[x]._prevTransferHash])
        return [totalTimeSavings, overwriteIssues, previousTransferList]

    def Analysis(self, idToHash):
        ret = {}
        ret["id"] = str(self._pos)
        ret["Total Time Aggragate"] = str(sum(self._totalTime))
        ret["CPU Overhead Aggragate"] = str(sum(self._cpuOverhead))
        ret["Pre-transfer Synchronization Time Aggragate"] = str(sum(self._preSync))
        ret["Call Count"] = str(len(self._preSync))
        ret["Cuda Call"] = self._stack.TransGetFirstLibCuda()
        ret["First User Call"] = self._stack.TransGetFirstUserCall()
        ret["Duplicate Count"] = str(len(self._duplicates))
        savings = self.FindSavings(idToHash)
        ret["Estimated Savings"] = str(savings[0])
        ret["Overwrite Issues"] = str(savings[1])
        ret["Duplicate Matches Transfer"] = ""
        for x in savings[2]:
            ret["Duplicate Matches Transfer"] += str(x) + " | "
        return ret

    def CreateOutput(self, idToHash):
        ret = self.Analysis(idToHash)
        return ret["id"] + "," + ret["Call Count"] + "," + ret["Cuda Call"] + "," + ret["First User Call"] + "," + ret["Duplicate Count"] + "," + ret["Estimated Savings"] + "," + ret["Overwrite Issues"]  + "," +  ret["Duplicate Matches Transfer"]


    def AddTotalTime(self, time):
        self._totalTime.append(time)

    def AddCPUOverhead(self, time):
        self._cpuOverhead.append(time)

    def AddDuplicate(self, dupEntry):
        self._duplicates.append(dupEntry)

    def PreTransSynchronization(self, time):
        self._preSync.append(time)

    def CopyDuplicates(self, other):
        self._duplicates = other._duplicates



class ReadTransferCollisions:
    def __init__(self, filename):
        self._filename = filename
        self._pos = 0
        f = open(self._filename,"rb")
        self._data = f.read()
        f.close()

    def DecodeRecord(self):
        if self._pos >= len(self._data):
            return None
        tmp = struct.unpack_from("QQQQ", self._data, offset=self._pos)
        self._pos += (8*4)
        return list(tmp)

class Driver:
    def __init__(self):
        self._inDir = sys.argv[1]
        self._outDir = sys.argv[2]

    def Run(self):
        ## TIme in Seconds
        TIME = 109.00
        self._stackStore = {}
        ## LS_stackkey -> Necessary Synchronization
        ## LS_tracekey -> Locations of first access
        ## TF_timekey -> Timing for each synchronization.
        stack_files = ["LS_stackkey.txt", "LS_tracekey.txt", "TF_timekey.txt"]

        for x in stack_files:
            self._stackStore[x] = StackReader(os.path.join(self._inDir, x))
        self._stackStore["TF_timekey.txt"].InverseStacks()
        for x in self._stackStore:
            print str(self._stackStore[x])

        ## LS_trace Reader
        ls_trace = LS_TraceBin(os.path.join(self._inDir, "LS_trace.bin"))
        ls_trace.DecodeFile()
        #print str(ls_trace)

        ## TF_Trace Decorder 
        tf_trace = TF_Trace(os.path.join(self._inDir, "TF_trace.bin"))
        tf_trace.DecodeFile()
        #print str(tf_trace)
        match = MatchTimeToLSStack(self._stackStore["TF_timekey.txt"], self._stackStore["LS_stackkey.txt"])
        m = match.GetMatchSet()
        singleSetTF = []
        for x in m:
            singleSetTF.append(x[0])
        notInSet = tf_trace.GetNotInSet(singleSetTF)
        #print notInSet
        timeSavedEstimate = 0.0
        for x in notInSet:
            timeSavedEstimate += x[-1]
        tmp_sort = {}
        for x in notInSet:
            if x[2] not in tmp_sort:
                tmp_sort[x[2]] = x
            else:
                tmp_sort[x[2]][-1] += x[-1]
                tmp_sort[x[2]][-2] += x[-2]
        notInSet = []
        for x in tmp_sort:
            notInSet.append(tmp_sort[x])
        print "\n\n\n\n"
        print "Estimated time savings from unnecessary synchroniations/data transfers: " + str(timeSavedEstimate)
        print "Table of unnecessary operation\n"
        print '%-20.20s | %-20.20s | %-20.20s | %-10.10s | %-20.20s | %-10.10s | %-10.10s' % ('App Bin','App Function','Cuda Call','Stack ID','Type','Call Count', 'Est Impact')
        outFD = open("results_output.csv", "w")
        outFD.write('%-20.20s,%-20.20s,%-20.20s,%-10.10s,%-20.20s,%-10.10s,%-10.10s\n' % ('App Bin','App Function','Cuda Call','Stack ID','Type','Call Count', 'Est Impact'))
        for x in notInSet:
            i = x[2]
            stack = self._stackStore["TF_timekey.txt"].GetStackAtID(int(i))
            ucall = stack.FindFirstUserCall()
            ccall = stack.FindFirstLibCuda()
            print '%-20.20s | %-20.20s | %-20.20s | %-10.10s | %-20.20s | %-10.10s | %-10.10s' % (ucall.GetFilename(),str(ucall._funcname),str(ccall._funcname),str(i),"Sync",str(x[3]), str(x[4]))
            outFD.write('%-20.20s,%-20.20s,%-20.20s,%-10.10s,%-20.20s,%-10.10s,%-10.10s\n' % (ucall.GetFilename(),str(ucall._funcname),str(ccall._funcname),str(i),"Sync",str(x[3]), str(x[4])))
        outFD.close()
        self.DataDeduplication()

    def DataDeduplication(self):
        hashedIssueStacks = {}
        dtstack_idToHash = {}
        hashedStacks = {}
        dstime_idToHash = {}
        stack_files = ["DSTIME_stacks.bin", "DT_stacks.bin"]
        for x in stack_files:
            self._stackStore[x] = StackReader(os.path.join(self._inDir, x))
            self._stackStore[x].InverseStacks()
        for x in stack_files:
            print str(self._stackStore[x])

        tmpStack = self._stackStore["DSTIME_stacks.bin"].GetAllStacks()
        for x in tmpStack:
            hashedStacks[tmpStack[x].HashStackDataTransfer()] = DataTransfer(tmpStack[x].HashStackDataTransfer(),int(x), tmpStack[x])
            dstime_idToHash[x] = tmpStack[x].HashStackDataTransfer()

        timing_files = ["DSTIME_trace.bin", "DCPUTIME_trace.bin", "DTOTIME_trace.bin"]
        for x in timing_files:
            transferTime = TF_Trace(os.path.join(self._inDir, x))
            transferTime.DecodeFile()
            for y in transferTime._records:
                hValue = dstime_idToHash[y[1]]
                if "DSTIME_trace.bin" in x:
                    hashedStacks[hValue].PreTransSynchronization(y[-1])
                elif "DCPUTIME_trace.bin" in x:
                    hashedStacks[hValue].AddCPUOverhead(y[-1])
                elif "DTOTIME_trace.bin" in x:
                    print y
                    hashedStacks[hValue].AddTotalTime(y[-1])
                else:
                    print "error, should not be here"
                    print y
                    print x
        tmpStack = self._stackStore["DT_stacks.bin"].GetAllStacks()
        for x in tmpStack:
            hashedIssueStacks[tmpStack[x].HashStackDataTransfer()] = DataTransfer(tmpStack[x].HashStackDataTransfer(),int(x), tmpStack[x])
            dtstack_idToHash[x] = tmpStack[x].HashStackDataTransfer()

        readCollisionFile = ReadTransferCollisions(os.path.join(self._inDir, "DT_collisions.txt"))
        while 1:
            rec = readCollisionFile.DecodeRecord()
            if rec == None:
                break

            prevHash = 0
            if rec[2] == 1:
                prevHash = dtstack_idToHash[rec[3]]
            hashedIssueStacks[dtstack_idToHash[int(rec[0])]].AddDuplicate(DuplicateEntry(rec[1],prevHash))

        ## Map the collision stacks to timing
        colToTiming = {}
        for x in hashedIssueStacks:
            if x in hashedStacks:
                hashedStacks[x].CopyDuplicates(hashedIssueStacks[x])
            else:
                print "Unknown Transfer - " + str(x)

        f = open("dtrans_out.csv", "w")
        for x in hashedStacks:
            f.write(str(hashedStacks[x].CreateOutput(dstime_idToHash)) + "\n")
        f.close()


if __name__ == "__main__":
    d = Driver()
    d.Run()