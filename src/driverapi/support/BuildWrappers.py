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

f = open("ExternTemplate.txt","r")
externTemplate = f.read()
f.close()

count = 0
## Build Header for Wrappers
alreadyWritten = {}
charVector = "static const std::vector<const char *> CallVector = {"
outStr = '#include "'+ "DriverAPIHeader.h" +'"\n#include <tuple>\n#include "DriverWrapperBase.h"\n#include "DriverWrapperFactory.h"\n#include "cuda.h"\nstd::shared_ptr<DriverWrapperFactory> DriverFactory;\nextern "C" {'
outStr+= """\nvoid JustGenStackTrace() {
	BUILD_FACTORY
	FACTORY_PTR->PrintStack();
	return;
}

void CheckInit_DriverAPI() {
	
}\n"""
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
	variables["PARAMETERS_NAMES_VOID_CAST"] = ""
	tmp[-1] = tmp[-1][:-1]
	for y in tmp[2:]:
		pnames = y.split("$")
		variables["PARAMETER_TYPES"] += pnames[0] + ","
		variables["PARAMETERS_FULL"] += pnames[0] + " " + pnames[1] + ", "
		variables["PARAMETERS_NAMES"] += pnames[1] + ","
		variables["PARAMETERS_NAMES_VOID_CAST"] += "(void **)&" + pnames[1] + ","
	variables["PARAMETERS_FULL"] = variables["PARAMETERS_FULL"][:-2]	
	variables["PARAMETERS_NAMES"] = variables["PARAMETERS_NAMES"][:-1]
	variables["PARAMETER_TYPES"] = variables["PARAMETER_TYPES"][:-1]
	variables["PARAMETERS_NAMES_VOID_CAST"] = variables["PARAMETERS_NAMES_VOID_CAST"][:-1]
	if len(variables["PARAMETERS_NAMES"]) == 0:
		variables["PARAMETERS_NAMES"] = ""
		variables["PARAMETER_TYPES"] = "int"
		variables["PARAMETERS_NAMES_VOID_CAST"] = ""
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
hdr = '#pragma once\n#include "PluginCommon.h"\n#include <vector>\n#include "Parameters.h"\n#include "cuda.h"\n#include "DriverWrapperBase.h"\n#include <vector>\nextern "C"{\n'
charVector = ""
alreadyWritten = {}
defFile = ""
count = 0
structFile = '#pragma once\n#include <iostream>\n#include <functional>\n#include <memory>\n#include <map>\n#include <vector>\n#include "Parameters.h"\n#include "DriverWrapperBase.h"\n'
structFile += 'enum PluginReturn {\n\tNO_ACTION = 0,\n\tNOTIFY_ON_CHANGE,	// Notify when the parameter has changed\n\tDO_NOT_PERFORM,		// Instruct driver to not perform the action\n\tPERFORMED_ACTION,	// This plugin performed the action, do not perform again\n\tMODIFIED_PARAMS,	// This plugin modified the parameters\n\tFAILED			// This plugin has failed\n};\n\n'
structFile += "enum CallID {\n\t"
externTemplates = "\n#ifndef DEFINED_TEMPLATES\n#define EXTERN_FLAG extern\n#else\n#define EXTERN_FLAG \n#endif\n"
defineBinders = 'extern "C" void DefineBinders() {\n'
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
	variables["PARAMETER_TYPES_ORIG"] = ""
	variables["BINDER_PLACEHOLDERS"] = ""
	tmp[-1] = tmp[-1][:-1]	
	tr = 1
	for y in tmp[2:]:
		pnames = y.split("$")
		variables["PARAMETER_TYPES"] += pnames[0] + ","
		variables["PARAMETER_TYPES_ORIG"] += pnames[0] + ","
		variables["PARAMETERS_FULL"] += pnames[0] + " " + pnames[1] + ", "
		variables["PARAMETERS_NAMES"] += pnames[1] + ","
		variables["BINDER_PLACEHOLDERS"] += "std::placeholders::" + "_" + str(tr) +","
		tr += 1
	variables["BINDER_PLACEHOLDERS"] = variables["BINDER_PLACEHOLDERS"][:-1]
	variables["PARAMETERS_FULL"] = variables["PARAMETERS_FULL"][:-2]	
	variables["PARAMETERS_NAMES"] = variables["PARAMETERS_NAMES"][:-1]	
	variables["PARAMETER_TYPES"] = variables["PARAMETER_TYPES"][:-1]
	variables["PARAMETER_TYPES_ORIG"] = variables["PARAMETER_TYPES_ORIG"][:-1]
	if len(variables["PARAMETERS_NAMES"]) == 0:
		variables["PARAMETERS_NAMES"] = ""
	else:
		variables["PARAMETERS_NAMES"] = "," + variables["PARAMETERS_NAMES"]
	variables["CALL_ID"] = str(count)
	if count == 0:
		structFile += "ID_" + tmp[1].upper() + " = 0,\n\t"
	else:
		structFile += "ID_" + tmp[1].upper() + ",\n\t"
	count += 1
	
	hdr += Template(headerTemplate).substitute(variables)
	defFile += Template(defTemplate).substitute(variables) + "\n"
	externTemplates += Template(externTemplate).substitute(variables) + "\n"
	defineBinders += "\tBound_" + variables["CALL_NAME"] + " = std::bind(&ORIGINAL_" + variables["CALL_NAME"] + "," + variables["BINDER_PLACEHOLDERS"] + ");\n"
structFile = structFile[:-3] + "\n};\n" + externTemplates
hdr += "\n}\n" + charVector
outStr += "#define DEFINED_TEMPLATES 1" + externTemplates + "\n" + defineBinders + "\n}\n"

f = open(sys.argv[4],"w")
f.write(structFile)
f.close()

f = open(sys.argv[3], "w")
f.write(defFile)
f.close()

f = open(sys.argv[2], "w")
f.write(hdr)
f.close()

f = open(sys.argv[1],"w")
f.write(outStr)
f.close()

