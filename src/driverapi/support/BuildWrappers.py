import os
import sys 
from string import Template

f = open("cudaFunctionProtos.txt", "r")
protos = f.readlines()
f.close()

f = open("WrapperTemplate.txt","r")
funcTemplate = f.read()
f.close()

f = open("HeaderTemplate.txt", "r")
headerTemplate =  f.read()
f.close()

f = open("DefinitionHeader.txt","r")
defTemplate = f.read()
f.close()
count = 0
## Build Header for Wrappers
alreadyWritten = {}
charVector = "static const std::vector<const char *> CallVector = {"
outStr = '#include "'+ "DriverAPIHeader.h" +'"\n#include <tuple>\n#include "DriverWrapperBase.h"\n#include "DriverWrapperFactory.h"\n#include "cuda.h"\nstd::shared_ptr<DriverWrapperFactory> DriverFactory;\nextern "C" {'
for x in protos:
	variables = {"RETURN_TYPE" : None, "CALL_NAME" : None, "PARAMETERS_NAMES" : None,
				"PARAMETERS_FULL" : None}
	tmp = x.split(",")
	if "CUresult" in tmp[0]:
		variables["RETURN_TYPE"] = "int"
	else:
		continue
	variables["CALL_NAME"] = tmp[1]
	if tmp[1] in alreadyWritten:
		continue
	alreadyWritten[tmp[1]] = 1
	variables["PARAMETERS_FULL"] = ""
	variables["PARAMETERS_NAMES"] = ""
	variables["PARAMETER_TYPES"] = "int,"
	tmp[-1] = tmp[-1][:-1]
	for y in tmp[2:]:
		pnames = y.split("$")
		variables["PARAMETER_TYPES"] += pnames[0] + ","
		variables["PARAMETERS_FULL"] += pnames[0] + " " + pnames[1] + ", "
		variables["PARAMETERS_NAMES"] += pnames[1] + ","
	variables["PARAMETERS_FULL"] = variables["PARAMETERS_FULL"][:-2]	
	variables["PARAMETERS_NAMES"] = variables["PARAMETERS_NAMES"][:-1]
	variables["PARAMETER_TYPES"] = variables["PARAMETER_TYPES"][:-1]
	if len(variables["PARAMETERS_NAMES"]) == 0:
		variables["PARAMETERS_NAMES"] = ""
		variables["PARAMETER_TYPES"] = "int"
	else:
		variables["PARAMETERS_NAMES"] = "," + variables["PARAMETERS_NAMES"]
	variables["CALL_ID"] = str(count)
	count+= 1
	charVector += '"' + tmp[1] + '",'
	outStr += Template(funcTemplate).substitute(variables)

outStr += "\n}"
charVector = charVector[:-1] + "};\n"
outStr += charVector + "\n"

## Create The Header File
hdr = '#pragma once\n#include "cuda.h"\n#include "DriverWrapperBase.h"\n#include <vector>\nextern "C"{\n'
charVector = "extern static const std::vector<const char *> CallVector;"
alreadyWritten = {}
defFile = ""
count = 0
for x in protos:
	variables = {"RETURN_TYPE" : None, "CALL_NAME" : None, "PARAMETERS_NAMES" : None,
				"PARAMETERS_FULL" : None}
	tmp = x.split(",")
	if "CUresult" in tmp[0]:
		variables["RETURN_TYPE"] = "int"
	else:
		continue
	variables["CALL_NAME"] = tmp[1]
	if tmp[1] in alreadyWritten:
		continue
	alreadyWritten[tmp[1]] = 1
	variables["PARAMETERS_FULL"] = ""
	variables["PARAMETERS_NAMES"] = ""
	variables["PARAMETER_TYPES"] = "int,"
	tmp[-1] = tmp[-1][:-1]	
	for y in tmp[2:]:
		pnames = y.split("$")
		variables["PARAMETER_TYPES"] += pnames[0] + ","
		variables["PARAMETERS_FULL"] += pnames[0] + " " + pnames[1] + ", "
		variables["PARAMETERS_NAMES"] += pnames[1] + ","
	variables["PARAMETERS_FULL"] = variables["PARAMETERS_FULL"][:-2]	
	variables["PARAMETERS_NAMES"] = variables["PARAMETERS_NAMES"][:-1]	
	variables["PARAMETER_TYPES"] = variables["PARAMETER_TYPES"][:-1]
	if len(variables["PARAMETERS_NAMES"]) == 0:
		variables["PARAMETERS_NAMES"] = ""
	else:
		variables["PARAMETERS_NAMES"] = "," + variables["PARAMETERS_NAMES"]
	variables["CALL_ID"] = str(count)
	count += 1

	hdr += Template(headerTemplate).substitute(variables)
	defFile += Template(defTemplate).substitute(variables) + "\n"

hdr += "\n}\n" + charVector
f = open(sys.argv[3], "w")
f.write(defFile)
f.close()

f = open(sys.argv[2], "w")
f.write(hdr)
f.close()

f = open(sys.argv[1],"w")
f.write(outStr)
f.close()

