#NOTE: i have realized that a set of recursive functions would be way better than the hard coding below

import json
import os
import subprocess

jSource = open("test.json", "r")
data = json.load(jSource)
pretty = json.dumps(data, indent = 4)

#print(pretty)
#print(data["methods"])

methods = []
fields = set()
dependencies = set()

#Finding all fields of the class (not made yet)
#print(data["fields"])
#for f in data["fields"]:
#    fields.add(f)

#Finding all functions of the file
for method in data["methods"]:
    #Finding all method information
    methodParts = []
    methodParts.append(method["name"])
    accesses = []
    for access in method["access"]: #'public, private, static,...'
        accesses.append(access)
        #print("     " + ac)
    methodParts.insert(0,accesses)
    paramTypes = []
    for parameters in method["params"]:
        #Finding atomic types
        try:
            paramTypes.append(parameters["type"]["base"])
        except:
            dummy = 0
        #Finding arrays
        try:
            paramTypes.append(parameters["type"]["type"]["name"] + " " + parameters["type"]["kind"])
        except:
            dummy = 0
        #Fidning classes passed as parameters
        try:
            if parameters["type"]["kind"] == "class":
                dependencies.add(parameters["type"]["name"])
        except:
            dummy = 0
        try:
            if parameters["type"]["kind"] == "array" and parameters["type"]["type"]["kind"] == "class":
                dependencies.add(parameters["type"]["type"]["name"])
        except:
            dummy = 0


    methodParts.append(paramTypes)
    methods.append(methodParts)

    #Finding fields in mehtods
    for code in method["code"]["bytecode"]:
        try:
            fields.add(code["class"])
        except:
            dummy = 0

#for f in fields:
#    dependencies.add(f)   

print("Method:")
for method in methods:
    print(method)

print("Fields:")
for field in fields:
    print(field)

print("Dependencies:")
for d in dependencies:
    print(d)

#print(pretty)
