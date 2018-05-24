class StackEntry:
    def __init__(self, libname = "", offset = 0):
        self._libname = libname
        self._offset = offset


    def __eq__(self, other):
        if (str(self) == str(other)):
            return True
        return False

    def __str__(self):
        return str(self._libname) + "@" + str(self._offset) 

    def GetFilename(self):
        return self._libname.split("/")[-1]
class Stack:
    def __init__(self, i):
        self._stack = []
        self._ident = i
    def AddEntry(self, libname, offset):
        self._stack.append(StackEntry(libname, offset))

    def GetStack(self):
        return self._stack

    def FindFirstUserCall(self):
        startPos = 0
        for x in range(0,len(self._stack)):
            if "libcuda.so" in  self._stack[x]._libname:
                startPos = x
                break
        return self._stack[startPos-1]

    def FindFirstLibCuda(self):
        for x in self._stack:
            if "libcuda.so" in  x._libname:
                return x
    def __str__(self):
        ret = "\tStack " + str(self._ident)  + "\n"
        for i in self._stack:
            ret += "\t\t" + str(i) + "\n"
        return ret

    def InverseStack(self):
        tmp = []
        for x in range(len(self._stack) - 1, 0, -1):
            tmp.append(self._stack[x])
        self._stack = tmp

def RemoveNewline(line):
    return line.replace("\n","")

class StackReader:
    def __init__(self, filename):
        self._filename = filename
        f = open(filename, "rb")
        self._data = f.readlines()
        f.close()
        self.__GetStacks()

    def __GetStacks(self):
        self._stacks = {}
        for x in self._data:
            tmp = RemoveNewline(x).split("$")
            self._stacks[int(tmp[0])] = Stack(int(tmp[0]))
            for y in tmp[1:]:
                ms = y.split("@")
                self._stacks[int(tmp[0])].AddEntry(ms[0], int(ms[1]))

    def __str__(self):
        ret = "Stack records read for file - " + str(self._filename) + "\n"
        for x in self._stacks:
            ret += str(self._stacks[x]) + "\n"
        return ret
    def GetStackAtID(self, i):
        if i not in self._stacks:
            return None
        return self._stacks[i]

    def GetAllStacks(self):
        return self._stacks

    def InverseStacks(self):
        for x in self._stacks:
            self._stacks[x].InverseStack()