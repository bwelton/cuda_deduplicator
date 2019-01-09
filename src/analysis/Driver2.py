import hashlib
import json
import os
import subprocess
import os.path
import struct
from TF_trace import TF_Trace
from LS_TraceBin import LS_TraceBin
from FI_TraceBin import FI_TraceBin

cachedMD5 = {}
stackPoints = {}

def RemoveNewline(line):
    return line.replace("\n","")

def md5(fname):
    global cachedMD5
    if fname in cachedMD5:
        return cachedMD5[fname]

    md5hasher = hashlib.md5()
    try:
        f = open(fname, "rb")
        data = f.read()
        md5hasher.update(data)
        cachedMD5[fname] = md5hasher.hexdigest()
        print fname + " hashed to " + cachedMD5[fname]
        f.close()
    except Exception as e:
        print e
        print "Error: Could not fine file with name - " + fname
        cachedMD5[fname] = None
    return cachedMD5[fname]

def AddStackPoint(libname, offset):
    global stackPoints
    decodeString = libname + "@" + str(offset)
    if decodeString not in stackPoints:
        stackPoints[decodeString] = {"line_num" : 0, "filename" : "", "funcname" : ""}

def GetStackPoint(libname, offset):
    global stackPoints
    decodeString = libname + "@" + str(offset)
    if decodeString in stackPoints:
        return stackPoints[decodeString]
    return None


def GetLineInfo():
    f = open("tmp_encoded_stack.txt","w")
    count = 1
    idToStackpoint = {}
    for x in stackPoints:
        f.write(str(count) + "$" + str(x) +"\n")
        idToStackpoint[count] = x
        count += 1
    f.close()
    try:
        os.remove("tmp_decoded_stack.txt")
    except:
        pass
    subprocess.call("/g/g17/welton2/repo/spack/opt/spack/linux-rhel7-ppc64le/gcc-4.9.3/cudadedup-develop-sfolqw2eykf4ubdm3umxxvnky2ul6k7r/bin/LaunchCUInstriment -d -i tmp_encoded_stack.txt -o tmp_decoded_stack.txt &> debug_symtab.txt", shell=True)
    f = open("tmp_decoded_stack.txt", "r")
    for x in f.readlines():
        entry = {"line_num" : 0, "filename" : "", "funcname" : ""}
        tmp = x.split("$")
        count = tmp[0]
        tmp[1] = "".join(tmp[1:])
        tmp[1] = RemoveNewline(tmp[1])
        index = int(count,16)
        a = tmp[1].split("@")
        if "<Unknown at Offset" in a[1]:
            entry["funcname"] = "Unknown"
            continue
        lines = os.popen("/usr/bin/c++filt " + a[1]).read().splitlines()
        if len(lines) == 0:
            entry["funcname"] = "Unknown"
        else:
            entry["funcname"] = lines[0]
        lineMapSplit = a[3].split("|")
        if len(lineMapSplit) == 2:
            if lineMapSplit[1] != "":
                entry["line_num"] = int(lineMapSplit[1],16)
            if lineMapSplit[0] != "":
                entry["filename"] = lineMapSplit[0]

        if index not in idToStackpoint:
            print "Unknown index of " + str(index)
            print lines
            continue
        print "associating " + a[0] + "@" + str(int(a[2],16)) + " with stack entry " + idToStackpoint[index]
        stackPoints[idToStackpoint[index]] = entry

            #print a[1]

class JSStackEntry:

    def __init__(self, data = None, libname = None, liboffset = None, pos = None):
        self._libName = ""
        self._libOffset = 0
        self._funcName = ""
        self._lineNum = 0
        self._fileName = ""
        self._md5sum = None
        self._pos = 0
        self._compare = None
        if libname != None:
            self._libName = libname
        if liboffset != None:
            self._libOffset = int(liboffset)
        if pos != None:
            self._pos = int(pos)
        if data != None:
            self.from_dict(data)
        else:
            self._md5sum = md5(libname)
            AddStackPoint(libname, liboffset)

    def GetComparitor(self):
        if self._compare != None:
            return self._compare

        if self._md5sum != None:
            self._compare = self._md5sum + "@" + str(self._libOffset)
        else:
            self._compare = self._libName + "@" + str(self._libOffset)
        return self._compare

    def GetFunctionName(self):
        return self._funcName

    def GetLibName(self):
        return self._libName

    def GetNameInfo(self):
        ret = GetStackPoint(self._libName, self._libOffset)
        if ret == None:
            return
        self._funcName = ret["funcname"]
        self._lineNum = ret["line_num"]
        self._fileName = ret["filename"]

    def SetPos(self,pos):
        self._pos = pos

    def to_dict(self):
        return {"libname": self._libName, "liboffset" : self._libOffset, "funcname" : self._funcName,
                "linenum" : self._lineNum, "filename" : self._fileName, "position": self._pos,
                "md5sum" : self._md5sum, "compare" : self._compare}

    def from_dict(self, data):
        global cachedMD5
        self._libName = data["libname"]
        self._libOffset = data["liboffset"]
        self._funcName = data["funcname"]
        self._lineNum = data["linenum"]
        self._fileName = data["filename"]
        self._pos = data["position"]
        self._md5sum = data["md5sum"]
        if self._md5sum != "":
            cachedMD5[self._libName] = self._md5sum




class JSStack:
    def __init__(self, data = None):
        self._globalID = 0
        self._chopped = False
        if data != None:
            self.from_dict(data)
            return
        self._stack = []
        self._ident = {"tf_id": 0, "ls_id" : 0, "dstime_id" : 0, "fi_id" : 0, "dt_id" : 0}
        self._count = 0
        self._ttime = 0.0
        self._syncUses = 0
        self._useDelay = 0.0
        self._fiCount = 0
        self._duplicates = 0
        self._transTime = 0.0
        self._transferCount = 0
        self._transferCollisions = []
        self._overwrites = 0

    def AddTransferCollision(self, otherGlobalId, overwrite):
        if otherGlobalId != 0:
            self._transferCollisions.append(otherGlobalId)
        else:
            if overwrite == 1:
                self._overwrites += 1

    def GetLineInfo(self):
        for x in self._stack:
            x.GetNameInfo()

    def AddTotalTime(self, time):
        self._count += 1
        self._ttime += time

    def AddSyncUses(self, count):
        self._syncUses += count

    def AddDataTransfer(self, time):
        self._transTime += time
        self._transferCount += 1

    def AddFirstUse(self, uses):
        for x in range(1, len(uses)):
            if uses[x][0] > 0:
                self._useDelay = self._useDelay + (uses[x][1] - uses[x-1][1])
                self._fiCount += 1



    def GetStackCompairtors(self):
        ret = []
        for x in self._stack:
            ret.append(x.GetComparitor())
        return ret

    def AddEntry(self, libname, liboffset):
        self._stack.append(JSStackEntry(data=None,libname=libname, liboffset=int(liboffset), pos=len(self._stack)))

    def SetID(self, idName, value):
        self._ident[idName] = int(value)

    def GetID(self, idName):
        return self._ident[idName]

    def InverseStacks(self):
        tmp = []
        count = 0
        for x in range(len(self._stack) - 1, 0, -1):
            tmp.append(self._stack[x])
            tmp[count].SetPos(count)
            count += 1

        self._stack = tmp

    def ChopStack(self):
        ## remove diogenes crap from these stacks
        if self._chopped == True:
            return
        for x in range(0,len(self._stack)):
            if "libDriverAPIWrapper" in self._stack[x].GetLibName():
                self._stack = self._stack[0:x]
                self._chopped = True
                return
        self._chopped = True


    def CompareFIToLS(self, other):
        myself = self.GetStackCompairtors()
        otherComps = other.GetStackCompairtors()
        # print otherComps
        # print myself
        if len(myself) != len(otherComps):
            return False
        for x in range(0, len(myself)):
            if myself[x] != otherComps[x]:
                return False
        return True

    def CompareFIToTF(self, other):
        myself = self.GetStackCompairtors()
        other = other.GetStackCompairtors()

        curPos = 0
        for x in myself:
            found = False
            for y in range(curPos, len(other)):
                if x == other[y]:
                    found = True
                    curPos = y + 1
                    break
            if found == False:
                return False
        return True

    def CompareTFToDT(self, other):
        return self.CompareFIToTF(other)

    def CompareDStoDT(self, other):
        return self.CompareFIToLS(other)


    def to_dict(self):
        ret = dict(self._ident)
        ret["GlobalID"] = self._globalID
        ret["count"] = self._count
        ret["total_time"] = float(self._ttime)
        ret["Sync Uses"] = int(self._syncUses)
        ret["Use Delay"] = float(self._useDelay)
        ret["Duplicates"] = int(self._duplicates)
        ret["FICount"] = int(self._fiCount)
        ret["Transfer Time"] = float(self._transTime)
        ret["Transfer Count"] = int(self._transferCount)
        ret["Stack"] = [x.to_dict() for x in self._stack]
        ret["TransferCollisions"] = self._transferCollisions 
        ret["TransferOverwrites"] = self._overwrites
        return ret

    def GetGlobalId(self):
        return self._globalID
    def from_dict(self, data):
        for x in self._ident:
            self._ident[x] = data[x]
        self._globalID = ret["GlobalID"]
        self._count = data["count"] 
        self._ttime = data["total_time"] 
        self._syncUses = data["Sync Uses"] 
        self._useDelay = data["Use Delay"] 
        self._duplicates = data["Duplicates"]
        self._fiCount = data["FICount"]
        self._transferCount = ret["Transfer Count"]
        self._transTime = ret["Transfer Time"]
        self._transferCollisions = ret["TransferCollisions"]
        self._overwrites = ret["TransferOverwrites"]
        for x in ret["Stack"]:
            self._stack.append(JSStackEntry(x))



def BuildMap(stacks, key_id):
    ret = {}
    for x in range(0, len(stacks)):
        if stacks[x].GetID(key_id) != 0:
            print stacks[x].GetID(key_id)
            assert stacks[x].GetID(key_id) not in ret
            ret[stacks[x].GetID(key_id)] = x
    return ret
class ProcessTimeFile:
    def __init__(self, final):
        self._final = final

    def Process(self):
        m = BuildMap(self._final, "tf_id")
        tf_trace = TF_Trace("TF_trace.bin")
        tf_trace.DecodeFile()
        for x in tf_trace._records:
            ## x[0] = format (2 = sync record)
            ## x[1] = dynId
            ## x[2] = stackId
            ## x[3] = count (only used on x86_64)
            ## x[4] = time (double)

            assert x[0] == 1
            if x[2] not in m:
                print "Error: Missing entry for TF Stack ID - " + str(x[2])
            else:
                self._final[m[x[2]]].AddTotalTime(float(x[4]))
        return self._final

class ProcessLSTrace:
    def __init__(self, final):
        self._final = final

    def Process(self):
        m = BuildMap(self._final, "ls_id")
        ls_trace = LS_TraceBin( "LS_trace.bin")
        ls_trace.DecodeFile()
        for x in ls_trace._entriesMap:
            if int(x) not in m and int(x) != 0:
                print "Error: Could not find ls id of - " + str(x)
            elif int(x) != 0:
                self._final[m[x]].AddSyncUses(len(ls_trace._entriesMap[x]))
        return self._final


class ProcessFITrace:
    def __init__(self, final):
        self._final = final

    def Process(self):
        m = BuildMap(self._final, "fi_id")
        fi_tracebin = FI_TraceBin("FI_trace.bin")
        fi_tracebin.DecodeFile()
        for x in fi_tracebin._entriesMap:
            if int(x) not in m and int(x) != 0:
                print "Warn: Could not find fi id of - " + str(x)
            elif int(x) != 0:
                self._final[m[x]].AddFirstUse(fi_tracebin._entriesMap[x])
        return self._final    

class ProcessDSTime:
    def __init__(self, final):
        self._final = final

    def Process(self):
        m = BuildMap(self._final, "dstime_id")
        transferTime = TF_Trace("DTOTIME_trace.bin")
        transferTime.DecodeFile()
        for x in transferTime._records:
            assert x[0] == 2
            stackId = int(x[2])
            time = float(x[3])
            if stackId not in m and stackId != 0:
                print "Error could not find dstiming stack with id of - " + str(stackId)
            elif stackId != 0:
                self._final[m[stackId]].AddDataTransfer(time)
        return self._final

class ReadTransferCollisions:
    def __init__(self, filename):
        self._filename = filename
        self._pos = 0
        try:
            f = open(self._filename,"rb")
            self._data = f.read()
            f.close()
        except:
            self._data = ""


    def DecodeRecord(self):
        if self._pos >= len(self._data):
            return None
        tmp = struct.unpack_from("QQQQ", self._data, offset=self._pos)
        self._pos += (8*4)
        return list(tmp)

class ProcessTransCollisions:
    def __init__(self, final):
        self._final = final
    def Process(self):
        m = BuildMap(self._final, "dt_id")
        readCollisionFile = ReadTransferCollisions( "DT_collisions.txt")
        while 1:
            rec = readCollisionFile.DecodeRecord()
            if rec == None:
                break
            if rec[0] == 0:
                continue
            prevHash = 0
            if rec[2] == 1:
                prevHash = int(rec[3])
            if rec[1] == 0 and rec[2] == 0:
                continue
            if prevHash != 0:
                if prevHash not in m:
                    print "Could not find previous hash id of - " + str(prevHash)
                    prevHash = 999999999
                else:
                    prevHash = self._final[m[prevHash]].GetGlobalId()
            if int(rec[0]) not in m:
                print "Could not find transfer with dt_id of - " + str(rec[0])
            else:
                self._final[m[int(rec[0])]].AddTransferCollision(prevHash, rec[1])
        return self._final


class StackContainer:
    def __init__(self):
        self._stacks = []
        self._filenames = {"tf_id": "", "ls_id" : "", "dstime_id" : "", "fi_id" : "", "dt_id" : ""}

    def GetFilenameStack(self):
        return self._filenames


    def ReadSingleFile(self, filename, id_key):
        try:
            f = open(filename, "rb")
            data = f.readlines()
            f.close()
        except:
            return None
        ret = []
        for x in data:
            tmp = RemoveNewline(x).split("$")
            stack = JSStack()
            stack.SetID(id_key, int(tmp[0]))
            for y in tmp[1:]:
                ms = y.split("@")
                stack.AddEntry(ms[0], int(ms[1]))
            if id_key == "tf_id" or id_key == "dt_id" or id_key == "dstime_id":
                stack.InverseStacks()
            ret.append(stack)
        return ret

    def DumpStack(self, stack, outName):
        dump = []
        for y in stack:
            dump.append(y.to_dict())

        j = json.dumps(dump, indent=4)
        f = open(outName +".json", "wb")
        f.write(j)
        f.close()


    def DumpStacks(self, stacks):
        for x in stacks:
            self.DumpStack(stacks[x], x)

    def ReadStackFiles(self, filenames):
        stacks = {}
        for x in filenames:
            stacks[x] = self.ReadSingleFile(filenames[x], x)
        discards = []
        
        if stacks["fi_id"] != None:
            for x in stacks["ls_id"]:
                found = False
                for y in stacks["fi_id"]:
                    if x.CompareFIToLS(y):
                        found = True
                        assert y.GetID("ls_id") == 0
                        y.SetID("ls_id", x.GetID("ls_id"))
                        break
                if found == False:
                    print "Could not find an associated LS stack for LS ID - " + str(x.GetID("ls_id"))
                    discards.append(x)
        else:
            stacks["fi_id"] = stacks["ls_id"]
        self.DumpStacks(stacks)
        # for x in stacks["ls_id"]:
        #     print "ls_id: " + str(x.GetID("fi_id"))
        #     print x.GetStackCompairtors()            
        
        for x in stacks["fi_id"]:
            found = False
            for y in stacks["tf_id"]:
                if x.CompareFIToTF(y):
                    found = True
                    assert y.GetID("ls_id") == 0 and y.GetID("fi_id") == 0
                    y.SetID("ls_id", x.GetID("ls_id"))
                    y.SetID("fi_id", x.GetID("fi_id"))
                    break
            if found == False:
                print "Could not find an associated FI stack for FI ID - " + str(x.GetID("fi_id")) + "," + str(x.GetID("ls_id"))
                discards.append(x)
        final = []
        for x in stacks["dt_id"]:
            found = False
            x.ChopStack()
            for y in stacks["dstime_id"]:
                y.ChopStack()
                if x.CompareDStoDT(y):
                    found = True
                    assert y.GetID("dt_id") == 0
                    y.SetID("dt_id", x.GetID("dt_id"))
                    break
            if found == False:
                print "Could not find an associated DT stack for DT ID - " + str(x.GetID("dt_id")) 
                discards.append(x)

        idsCopied = {}

        for x in stacks["tf_id"]:
            found = False
            for y in stacks["dstime_id"]:
                if x.CompareTFToDT(y):
                    found = True
                    assert y.GetID("tf_id") == 0
                    idsCopied[y.GetID("dstime_id")] = True
                    y.SetID("ls_id", x.GetID("ls_id"))
                    y.SetID("fi_id", x.GetID("fi_id"))                    
                    y.SetID("tf_id", x.GetID("tf_id"))
                    final.append(y)
                    break
            if found == False:
                print "Could not find tf_id in transfer log (synchronization only) " + str(x.GetID("tf_id")) 
                final.append(x)

        for x in stacks["dstime_id"]:
            if x.GetID("dstime_id") not in idsCopied:
                assert x.GetID("tf_id") == 0
                final.append(x)
        GetLineInfo()
        gloId = 1
        for x in final:
            x.GetLineInfo()
            x._globalID = gloId
            gloId += 1

        self.DumpStack(final, "combined_stacks")
        proc = ProcessTimeFile(final)
        final = proc.Process()

        proc = ProcessLSTrace(final)
        final = proc.Process()

        proc = ProcessFITrace(final)
        final = proc.Process()

        proc = ProcessDSTime(final)
        final = proc.Process()

        proc = ProcessTransCollisions(final)
        final = proc.Process()
        self.DumpStack(final, "combined_stacks")






n = StackContainer()
n.ReadStackFiles({"tf_id": "TF_timekey.txt", "ls_id" : "LS_stackkey.txt", "dstime_id" : "DSTIME_stacks.bin", "fi_id" : "FI_stackkey.txt", "dt_id" : "DT_stacks.bin"})

