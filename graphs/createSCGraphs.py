import os
from collections import deque
nodetofind = "targ35ac08"

f = open("cuCtxSynchronize","rb")
d = f.readlines()
f.close()

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





outputNodes = {}

q = deque()
q.append(nodetofind)

print parentNodes.keys()
while len(q) > 0:
	tmp = q.popleft()
	if tmp in outputNodes:
		continue
	if tmp not in parentNodes:
		continue
	outputNodes[tmp] = {}
	for x in parentNodes[tmp]:
		q.append(x)
		outputNodes[tmp][x] = 1
print outputNodes
ret = ""
for x in outputNodes:
	for y in outputNodes[x]:
		ret += y + ' -> ' + x + "\n"

print ret
