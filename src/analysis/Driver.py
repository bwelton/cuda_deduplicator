import sys
import os
from  ReadStackFiles import StackReader
from LS_TraceBin import LS_TraceBin
from TF_trace import TF_Trace

class MatchTimeToLSStack:
    def __init__(self, TF_timekey, LS_stackkey):
        self._tf = TF_timekey
        self._ls = LS_stackkey

    def PruneTFStack(self, stack):
        ret = stack._stack
        ret = ret
        return ret


    def CompareStacks(self, ls, tf):
        #ls stack will always be longer
        for x in range(0,len(ls)):
            found = False
            for y in range(0,len(tf)):
                if ls[x] == tf[y]:
                    found = True
                    break
            if (found == False):
                return False

            #if str(ls[x]) != str(tf[x]):
            #    return False
        return True


    def GetMatchSet(self):
        # returns [(TFNum,LSNum)]
        ret = []
        tf_stacks = self._tf.GetAllStacks()
        ls_stacks = self._ls.GetAllStacks()
        for x in tf_stacks:
            tmp = self.PruneTFStack(tf_stacks[x])
            for y in ls_stacks:
                tmp2 = ls_stacks[y]._stack
                if self.CompareStacks(tmp2, tmp):
                    ret.append([tf_stacks[x]._ident,ls_stacks[y]._ident])
        print "MATCH SET"
        print ret
        return ret


class DuplicateEntry:
    def __init__(self, overwrite, prevTransferHash, prevTransferID):
        self._overwrite = overwrite
        self._prevTransferHash = prevTransferHash


class DataTransfer:
    def __init__(self, hashVal, position, stack):
        self._hash = hashVal
        self._pos = position
        self._stack = stack
        self._preSync = 0.0
        self._totalTime = 0.0
        self._cpuOverhead = 0.0
        self._duplicates = []

    def AddTotalTime(self, time):
        self._totalTime = time

    def AddCPUOverhead(self, time):
        self._cpuOverhead = time

    def AddDuplicate(self, dupEntry):
        self._duplicates.append(dupEntry)

    def PreTransSynchronization(self, time):
        self._preSync = time





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

        for x in self._stackStore["DSTIME_stacks.bin"].GetAllStacks():
            hashedStacks[x.HashStackDataTransfer()] = x
            dstime_idToHash[x._ident] = x.HashStackDataTransfer()

        timing_files = ["DSTIME_trace.bin", "DCPUTIME_trace.bin", "DTOTIME_trace.bin"]
        for x in timing_files:
            transferTime = TF_Trace(os.path.join(self._inDir, x))
            transferTime.DecodeFile()
            for y in transferTime._records:
                hValue = dstime_idToHash[y[0]]
                if "DSTIME_trace.bin" in x:
                    hashedStacks[hValue].PreTransSynchronization(y[-1])
                elif "DCPUTIME_trace.bin" in x:
                    hashedStacks[hValue].AddCPUOverhead(y[-1])
                elif "DTOTIME_trace.bin" in x:
                    hashedStacks[hValue].AddTotalTime(y[-1])
                else:
                    print "error, should not be here"
                    print y
                    print x

        for x in self._stackStore["DT_stacks.bin"].GetAllStacks():
            hashedIssueStacks[x.HashStackDataTransfer()] = x
            dtstack_idToHash[x._ident] = x.HashStackDataTransfer()




if __name__ == "__main__":
    d = Driver()
    d.Run()