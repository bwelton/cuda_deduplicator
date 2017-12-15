import os

for i in range(0,16):
	outstr = "template<"
	for x in range(0, i):
		outstr+= "typename T"+ str(x) + ","
	if outstr[-1] == ',':
		outstr = outstr[:-1]
	outstr += ">\nstd::tuple<"
	for x in range(0, i):
		outstr+= "T"+ str(x) + ","
	if outstr[-1] == ',':
		outstr = outstr[:-1]	
	outstr += "> GetParams()\n{\n\treturn std::make_tuple("
	for x in range(0, i):
		outstr+= "(T"+ str(x) + ")(values[" +str(x) +"]),"
	if outstr[-1] == ',':
		outstr = outstr[:-1]	
	outstr += ");\n}\n"	
	print outstr