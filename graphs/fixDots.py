import os
f = open("cuMemcpyDtoHAsync_v2.dot","rb")
d = f.readlines()
f.close()

diagram = {}
for x in d:
	if x.find("->") != -1:
		tmp = x.split("->")
		if tmp[0] not in diagram:
			diagram[tmp[0]] = {}
		diagram[tmp[0]][tmp[1]] = 1
ret = ""
for x in diagram:
	for y in diagram[x]:
		ret += x + " -> " + y

print ret

