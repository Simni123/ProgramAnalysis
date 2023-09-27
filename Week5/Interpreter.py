#Finding all the json files
from pathlib import Path
import json

folder = Path("course-02242-examples-main/course-02242-examples-main/src/executables/java/eu/bogoe/dtu/exceptional")
jsons = {}
for f in folder.glob("**/*.json"):
    source = open(f,"r")
    newKey = {f.name : json.load(source)}
    jsons.update(newKey)

#Finding all case methods
mehtods = {}
for jfile in jsons.values():
    if jfile["name"] != "eu/bogoe/dtu/exceptional/Arithmetics": #working with only arithmatic
        continue
    for method in jfile["methods"]:
        if method["name"] != "<init>" and method["name"] != "<clinit>":
            newKey = {method["name"] : method}
            mehtods.update(newKey)
        
#Simple bytecode printer
def find_method(caseName):
    assert mehtods[caseName] is not None
    return mehtods[caseName]

def print_bytecode(caseName):
    method = find_method(caseName)
    for codePices in method["code"]["bytecode"]:
        print(codePices)

#Building method program
class Interpreter:
    def __init__(self, log, casename):
        self.states = {}
        self.log = log
        self.casename = casename
    
    def run(self, param, k, abstract):
        self.abstract = abstract
        mstack={}
        mstack[0] = (sign_astraction(param,self.log),[],(self.casename,0))
        self.states[0] = mstack
        step = 0
        while k-step > 0:
            self.step(abstract, step)
            step += 1
        return

    def step(self, abstract, step):
        stepStates = self.states[step]
        self.states[step+1] = {}
        stackIndex = 0
        for index in stepStates:
            self.log("->", stepStates[index], end="")
            (localVars, opStack, (cn_,i)) = stepStates[index]
            byte = find_method(self.casename)["code"]["bytecode"][i]
            if byte["opr"] == "push":
                self.log("  push")
                for l in range(2):
                    self.states[step+1][stackIndex] = (localVars, opStack + [1], (cn_,i+1))
                    stackIndex += 1
            else:
                self.log("  fail    ", byte)
                return
    
    #def push(self, abstract, value):
    #    if abstract == "sign":

    #    else:
    #        self.log("push: sabstract type not supported", abstract)

'''
def interp(caseName, log, param):
    state = {}
    abs_param = sign_astraction(param, log)
    print(abs_param)
    state[0] = (abs_param, [])
    
    mstack = [(param,[],(caseName, 0))]
    while True:
        log("->", mstack, end="")
        (localsVars, opStack, (cn_, i)) = mstack[-1]
        byte = find_method(caseName)["code"]["bytecode"][i]
        log(" fail", byte)
        return None
        
    return None
'''
    
def sign_astraction(param, log):
    abstract_param = []
    for p in param:
        if type(param[p]) == int:
            if param[p] < 0:
                abstract_param[p] = {'-'}
            elif param[p] > 0:
                abstract_param[p] = {'+'}
            else:
                abstract_param[p] = {'0'}
        else:
            log("Abstract type not yet supported", param[p], type(param[p]))
            return None
    return abstract_param

#setting arguments (need to be a list - make a list of a long length)
#memory = [5,-3]
#memory[0] = 5
#memory[1] = -3
#Running the interpurator
interpret = Interpreter(print, "alwaysThrows1")
interpret.run([], 3, "sign")

#print_bytecode("alwaysThrows1")
#print(s)
