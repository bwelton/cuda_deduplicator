
class StackEntry:
	def __init__(self):
		self._libname = ""
		self._offset = 0

	def __init__(self, libname, offset):
		self._libname = libname
		self._offset = offset

class Stack:
	def __init__(self, i):
		self._stack = []
		self._ident = i
	def AddEntry(self, libname, offset):
		self._stack.append(StackEntry(libname, offset))


def RemoveNewline(line):
	return line.replace("\n","")

class StackReader:
	def __init__(self, filename):
		f = open(filename, "rb")
		self._data = f.readlines()
		f.close()

	def GetStacks(self):
		self._stacks = {}
		for x in self._data:
			tmp = RemoveNewline(x).split("$")
			self._stacks[int(tmp[0])] = Stack(int(tmp[0]))
			for y in tmp[1:]:
				ms = y.split("@")
				self._stacks[int(tmp[0])].AddEntry(ms[0], int(ms[1]))

	
