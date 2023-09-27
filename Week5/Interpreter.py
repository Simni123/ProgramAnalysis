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
        mstack={}   #contains all posible bastract states in step x 
        mstack[0] = (sign_astraction(param,self.log),[],(self.casename,0))
        self.states[0] = mstack     #contains all steps 0->k wil mstacks
        step = 0
        while k-step > 0:   #calculating and adding all new states from step->step+1
            self.step(abstract, step)
            step += 1
        return

    def step(self, abstract, step):
        stepStates = self.states[step]
        self.states[step+1] = {}
        stackIndex = 0
        for index in stepStates:    #loop of 
            self.log("->", stepStates[index], end="")
            (localVars, opStack, (cn_,i)) = stepStates[index]
            byte = find_method(self.casename)["code"]["bytecode"][i]
            if byte["opr"] == "push":
                numb = byte["value"]["value"]
                self.log("  push    ", numb)
                value = abstract(numb, self.log)
                self.states[step+1][stackIndex] = (localVars, opStack + [value], (cn_,i+1))    
                stackIndex += 1
            else:
                self.log("  fail    ", byte)
                return
    
def sign_astraction(param, log):
    if type(param) == int:
        return single_sign_abtraction(param, log)
    elif type(param) == list:
        abstract_param = []
        for p in param:
            abstract_param[p] = single_sign_abtraction(p,log)
        return abstract_param
    else:
        log("sign abstraction type not supported", param, type(param))
        return None

def single_sign_abtraction(param, log):
    if type(param) == int:
        if param < 0:
            return "-"
        elif param > 0:
            return "+"
        else:
            return "0"
    else:
        log("Single sing abstraction type not yet supported", param, type(param))
        return None

#setting arguments (need to be a list - make a list of a long length)
#memory = [5,-3]
#memory[0] = 5
#memory[1] = -3
#Running the interpurator
interpret = Interpreter(print, "alwaysThrows1")
interpret.run([], 3, sign_astraction)

#print_bytecode("alwaysThrows1")
#print(s)
