import os 
from string import Template

f = open("cudaFunctionProtos.txt", "r")
protos = f.readlines()
f.close()

f = open("WrapperTemplate.txt","r")
funcTemplate = f.read()
f.close()

outStr = ""
for x in protos:
	variables = {"RETURN_TYPE" : None, "CALL_NAME" : None, "PARAMETERS_NAMES" : None,
				"PARAMETERS_FULL" : None}
	tmp = x.split(",")
	if "CUresult" in tmp[0]:
		variables["RETURN_TYPE"] = "int"
	else:
		continue
	variables["CALL_NAME"] = tmp[1]
	variables["PARAMETERS_FULL"] = ""
	variables["PARAMETERS_NAMES"] = ""
	tmp[-1] = tmp[-1][:-1]
	for y in tmp[2:]:
		pnames = y.split("$")
		variables["PARAMETERS_FULL"] += pnames[0] + " " + pnames[1] + ", "
		variables["PARAMETERS_NAMES"] += pnames[1] + ","
	variables["PARAMETERS_FULL"] = variables["PARAMETERS_FULL"][:-1]
	variables["PARAMETERS_NAMES"] = variables["PARAMETERS_NAMES"][:-1]
	outStr += Template(funcTemplate).substitute(variables)

print outStr