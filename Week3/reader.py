#NOTE: i have realized that a set of recursive functions would be way better than the hard coding below

import json

jSource = open("test.json", "r")
dataT = json.load(jSource)
pretty = json.dumps(dataT, indent = 4)

#Class data structure
#{name, methods, fields, {{inheritance}{realization}{aggregation}{composition}{dependency}}}
#name: string
#methods: dict-list
# name: Mehtod name
# access: list of access key words
# parameters: list of parameter tooples (type, name) 
# return: return type
#fields: dict-list
# name: field name
# access: list of access key words
# type: the type of the field

def getClassInfo(fileDir):
    source = open(fileDir,"r")
    data = json.load(source)
    #Initializing classinfo dict
    classInfo = {}
    
    #Adding the name to classInfo
    name = {"name" : data["name"]}
    classInfo.update(name)

    #Adding the all method info to classInfo
    methods = {"methods" : getMethods(data)}
    classInfo.update(methods)

    #Adding all fields to class info
    fields = {"fields" : getFields(data)}
    classInfo.update(fields)

    #Pringting all class info
    print(classInfo["name"])
    print("     Methods:")
    for m in classInfo["methods"]:
        print("     " + " ".join(m["access"]) + " " + m["name"] + "(" + ", ".join(m["parameters"]) + ")" +  ": " + "".join(m["return"]))
    print("     Fields:")
    for f in classInfo["fields"]:
        print("     " + " ".join(f["access"]) + " " + f["type"] + " " + f["name"])
    

#Method info helper functions
def getMethods(data):
    allMethods = []
    for method in data["methods"]:
        methodInfo = {}
        #Adding the method name
        name = {"name" : method["name"]}
        methodInfo.update(name)
        #Adding the method access key words
        access = {"access" : method["access"]}
        methodInfo.update(access)
        #Adding the parameter definitions
        parameters = {"parameters" : getMethodParameters(method)}
        methodInfo.update(parameters)
        #Adding return type
        returns = {"return" : getMethodReturntype(method["returns"])}
        methodInfo.update(returns)
        #Adding the method info to list of methods
        allMethods.append(methodInfo)
    return allMethods

#Returns the parameters of the method
def getMethodParameters(method):
    parameters = []
    for params in method["params"]: 
        parameters.append(recursiveMethodType(params["type"]))
    return parameters    

#Extracts the single type of a method parameter
def recursiveMethodType(type):
    try:
        if type["kind"] == 'array':
            return recursiveMethodType(type["type"]) + "[]"
        elif type["kind"] == 'class':
            return type["name"]
        else:
            print("A methodType with a not yet coverd kind was found: " + type["kind"])
            return "fail"
    except:
        return type["base"]

#Finds and returns the return type of a method
def getMethodReturntype(returns):
    try:
        if returns["kind"] == 'array':
            return getMethodReturntype(returns["type"]) + "[]"
        elif returns["kind"] == 'class':
            return returns["name"]
    except:
        try:
            return getMethodReturntype(returns["type"])
        except:
            if returns == None:
                return "void"
            elif type(returns) == dict:
                return returns["base"]
            else:
                print("Some branch of returntype is not coverd")
                print("return: " + returns)
                return "fail"

#Helper methods for finding fiels
def getFields(data):
    fields = []
    for field in data["fields"]:
        fieldInfo = {}
        #adding field name to fieldInfo
        name = {"name" : field["name"]}
        fieldInfo.update(name)
        
        #adding field access to fieldInfo
        access = {"access" : field["access"]}
        fieldInfo.update(access)

        #adding field type
        type = {"type" : getFieldType(field["type"])}
        fieldInfo.update(type)

        #adding the field into to fields list
        fields.append(fieldInfo)
    return fields

def getFieldType(type):
    try:
        if type["kind"] == 'array':
            return getFieldType(type["type"]) + "[]"
        elif type["kind"] == 'class':
            return type["name"]
    except:
        try:
            return type["base"]
        except:
            print("some branch of field type is not covered")
            print(type)
            return "fail"



testDir = "test.json"
primesDir = "deps/normal/primes.json"
simpleExampleDir = "deps\simple\example.json"
simpleOtherDir = "deps\simple\other.json"

getClassInfo(testDir)
#print(pretty)

#dict = {}
#test = {"hey": 5}
#dict.update(test)
#print(dict["hey"])
