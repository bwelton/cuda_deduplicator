import os
from collections import deque
nodetofind = "targ35ac08"


def GetChildrenAndParents(data):
	global nodetofind
	diagram = {}
	parentNodes = {}
	for x in d:
		if x.find("->") != -1:
			tmp = x.split("->")
			tmp[1] = tmp[1][:-2].replace(' ','')
			tmp[0] = tmp[0].replace(' ', '')
			if tmp[0] not in diagram:
				diagram[tmp[0]] = {}
			diagram[tmp[0]][tmp[1]] = 1
			if tmp[1] not in parentNodes:
				parentNodes[tmp[1]] = {}
			parentNodes[tmp[1]][tmp[0]] = 1
	return [diagram, parentNodes]

def BuildOutputSet(startName, retTuple, outputSet = {}):
	outputNodes = {}
	diagram = retTuple[0]
	parentNodes = retTuple[1]
	q = deque()
	q.append(startName)
	while len(q) > 0:
		tmp = q.popleft()
		if tmp in outputNodes:
			continue
		if tmp not in diagram:
			continue
		outputNodes[tmp] = {}
		for x in diagram[tmp]:
			q.append(x)
			outputNodes[tmp][x] = 1
	print outputNodes	


	#for x in diagram[nodetofind]:
	#	q.append(x)

	#print parentNodes.keys()
	#while len(q) > 0:
	#	tmp = q.popleft()
	#	if tmp in outputNodes:
	#		continue
	#	if tmp not in parentNodes:
	#		continue
	#	outputNodes[tmp] = {}
	#	for x in parentNodes[tmp]:
	#		q.append(x)
	#		outputNodes[tmp][x] = 1
	#print outputNodes
	coloring = {}
	ret = ""
	for x in outputNodes:
		for y in outputNodes[x]:
			ret += x + ' -> ' + y + "\n"
			if y in outputSet:
				coloring[y] = 1
			if x in outputSet:
				coloring[x] = 1

	for x in coloring:
		ret += x + ' [shape=circle, style=filled, fillcolor=green]\n'

	return ret


f = open("cuCtxSynchronize.dot","rb")
d = f.readlines()
f.close()

ctxSyncParents = GetChildrenAndParents(d)
f = open("cuMemcpyDtoHAsync_v2.dot","rb")
d = f.readlines()
f.close()
cuMemcpy = GetChildrenAndParents(d)

outputSet = {}
for x in cuMemcpy[0]:
	if x in ctxSyncParents[0]:
		outputSet[x] = 1

write =  BuildOutputSet("cuCtxSynchronize", ctxSyncParents, outputSet)
write = "digraph outgraph {\n" + write + "\n}"
f = open("test.dot","wb")
f.write(write)
f.close()