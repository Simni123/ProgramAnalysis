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
    def __init__(self, log):
        self.states = {}
        self.log = log
    
    def run(self, caseName, param, k):
        mstack={}
        mstack[0] = (param,[],(caseName,0))
        #mstack[1] = (param,[1],(caseName,0))
        self.states[0] = mstack
        step = 0
        while k-step >= 0:
            stepStates = self.states[step]
            mstack={}
            stackIndex = 0
            for index in stepStates:
                self.log("->", stepStates[index], end="")
                (localVars, opStack, (cn_,i)) = stepStates[index]
                byte = find_method(caseName)["code"]["bytecode"][i]
                
                self.log("  fail    ", byte)
                stackIndex += 1
            step += 1
            return

    def step(self):
        (localVars, opStack, pc) = self.stack[-1]

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
interpret = Interpreter(print)
interpret.run("alwaysThrows1", [], 1)

#print_bytecode("alwaysThrows1")
#print(s)
