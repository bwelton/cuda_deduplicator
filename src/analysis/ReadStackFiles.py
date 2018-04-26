class StackEntry:
    def __init__(self, libname = "", offset = 0):
        self._libname = libname
        self._offset = offset

    def __str__(self):
        return str(self._libname) + "@" + str(self._offset) 

class Stack:
    def __init__(self, i):
        self._stack = []
        self._ident = i
    def AddEntry(self, libname, offset):
        self._stack.append(StackEntry(libname, offset))

    def __str__(self):
        ret = "\tStack " + str(self._ident)  + "\n"
        for i in self._stack:
            ret += "\t\t" + str(i) + "\n"
        return ret

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
