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

class Interpreter:
    def __init__(self, log, casename):
        self.states = {}
        self.log = log
        self.casename = casename
    
    def run(self, param, k, abstract):
        self.abstract = abstract
        mstack={}   #contains all posible bastract states in step x 
        mstack[0] = (abstract(param,self.log),[],(self.casename,0))
        self.states[0] = mstack     #contains all steps 0->k wil mstacks
        step = 0
        while k-step > 0:   #calculating and adding all new states from step->step+1
            if abstract == sign_astraction:
                message = self.sign_step(step)
            if message == "return":
                break
            if message != "noProp":
                return message
            step += 1
        return "noProp"

    def sign_step(self, step):
        stepStates = self.states[step]
        self.states[step+1] = {}
        stackIndex = 0
        for index in stepStates:    #loop throug each posivle state in current step
            self.log("({0},{1})".format(step,index), end="")
            self.log("->", stepStates[index], end="")
            (localVars, opStack, (cn_,i)) = stepStates[index]   #fething posible state
            byte = find_method(self.casename)["code"]["bytecode"][i]    #feching bytecode for this step with this state
            if byte["opr"] == "push":   #push opr
                numb = byte["value"]["value"]
                self.log("  push    ", numb)
                value = sign_astraction(numb, self.log)
                self.states[step+1][stackIndex] = (localVars, opStack + [value], (cn_,i+1))    
                stackIndex += 1
            elif byte["opr"] == "binary":   #binary
                self.log("  binary", end="")
                if byte["operant"] == "div":    #div
                    self.log("  div", end="")
                    self.log("  sign")
                    dividend = opStack.pop()
                    quotient = opStack.pop()
                    value = set()
                    if "0" in dividend:
                        return "div by 0 error"
                    elif "+" in quotient and "+" in dividend:
                        value.add("+")
                    elif "+" in quotient and "-" in dividend:
                        value.add("-")
                    elif "0" in quotient:
                        value.add("0")
                    elif "-" in quotient and "+" in dividend:
                        value.add("-")
                    elif "-" in quotient and "-" in dividend:
                        value.add("-")
                    else:       #div combi missing
                        self.log("  div combination missing  ", byte)
                        return "not yet implemented error"
                    self.states[step+1][stackIndex] = (localVars, opStack + [value], (cn_,i+1))
                    stackIndex += 1
                elif byte["operant"] == "sub":
                    self.log("  sub", end="")
                    self.log("  sign")
                    val1 = opStack.pop()
                    val2 = opStack.pop()
                    value = set()
                    if "+" in val1 and "+" in val2:
                        value.add("+")
                        value.add("0")
                        value.add("-")
                        self.states[step+1][stackIndex] = (localVars, opStack + [value], (cn_,i+1))
                        stackIndex += 1
                    else:
                        self.log("sub with these params not yet implemented", byte)
                        return "not yet implemented error"
                else:
                    self.log("  binary type not yet implemented", byte)
            elif byte["opr"] == "store":
                idx = byte["index"]
                self.log("  store   ", idx)
                localVars[idx] = opStack.pop()
                self.states[step+1][stackIndex] = (localVars, opStack, (cn_,i+1))
                stackIndex += 1
            elif byte["opr"] == "load":
                idx = byte["index"]
                self.log("  load    ", idx)
                value = localVars[idx]
                self.states[step+1][stackIndex] = (localVars, opStack + [value], (cn_,i+1))
                stackIndex += 1
            elif byte["opr"] == "return":
                self.log("  return")
                return "return"
            elif byte["opr"] == "ifz":  #ifx        (Question: how to hande new regulation of local variable??? those dosent change)
                self.log("  ifz", end="")
                target = byte["target"]
                cond = opStack.pop()
                if byte["condition"] == "le":   #le
                    self.log("  le")
                    if "0" in cond or "-" in cond:
                        value = set()
                        value.add("0")
                        value.add("-")
                        self.states[step+1][stackIndex] = (localVars, opStack + [value], (cn_,target))
                        stackIndex += 1
                    if "+" in cond:
                        value = set()
                        value.add("+")
                        self.states[step+1][stackIndex] = (localVars, opStack + [value], (cn_,i+1))
                        stackIndex += 1
                elif byte["condition"] == "lt":
                    self.log("  lt")
                    if "-" in cond:
                        value = set()
                        value.add("-")
                        self.states[step+1][stackIndex] = (localVars, opStack + [value], (cn_,target))
                        stackIndex += 1
                    if "0" in cond or "-" in cond:
                        value = set()
                        value.add("0")
                        value.add("-")
                        self.states[step+1][stackIndex] = (localVars, opStack + [value], (cn_,i+1))
                        stackIndex += 1
                else:
                    self.log(" ifz condition not implemented yet ", byte)
                    return "not yet implemented error"
            elif byte["opr"] == "goto":     #goto
                target = byte["target"]
                self.log("  goto ", target)
                self.states[step+1][stackIndex] = (localVars, opStack, (cn_,target))
                stackIndex += 1
            elif byte["opr"] == "negate":   #negate
                self.log("  negate")
                cond = opStack.pop()
                value = set()
                if "+" in cond:
                    value.add("-")
                if "0" in cond:
                    value.add("0")
                if "-" in cond:
                    value.add("+")
                self.states[step+1][stackIndex] = (localVars, opStack + [value], (cn_,i+1))
                stackIndex += 1
            elif byte["opr"] == "incr":     #incr
                idx = byte["index"]
                amount = byte["amount"]
                self.log("  incr    idx: {0}  with: {1}".format(idx, amount))
                old = localVars[idx]
                new = set()
                if "+" in old and amount > 0:
                    new.add("+")
                if "+" in old and amount < 0:
                    new.add("+")
                    new.add("0")
                    new.add("-")
                if "0" in old and amount > 0:
                    new.add("+")
                if "0" in old and amount < 0:
                    new.add("-")
                if "-" in old and amount > 0:
                    new.add("+")
                    new.add("0")
                    new.add("-")
                if "-" in old and amount < 0:
                    new.add("-")
                localVars[idx] = new
                self.states[step+1][stackIndex] = (localVars, opStack, (cn_,i+1))
                stackIndex += 1
            else:
                self.log("  fail    ", byte)
                return "not yet implemented error"
        return "noProp"
        
def sign_astraction(param, log):
    if type(param) == int:
        return single_sign_abtraction(param, log)
    elif type(param) == set:
        return param
    elif type(param) == dict:
        abstract_param = {}
        for p in param:
            abstract_param[p] = single_sign_abtraction(param[p],log)
        return abstract_param
    else:
        log("sign abstraction type not supported", param, type(param))
        return None

def single_sign_abtraction(param, log):
    if type(param) == int:
        if param < 0:
            return {"-"}
        elif param > 0:
            return {"+"}
        else:
            return {"0"}
    elif type(param) == set:
        return param
    else:
        log("Single sing abstraction type not yet supported", param, type(param))
        return None

def noLog(str, st2="", end=None):
    dummy = 0

#Automatic test
#alwaysThrows1
memory = {}
interpret = Interpreter(noLog, "alwaysThrows1")
s = interpret.run(memory, 10, sign_astraction)
assert s == "div by 0 error"
#alwaysThrows2
memory[0] = 1
interpret = Interpreter(noLog, "alwaysThrows2")
s = interpret.run(memory, 10, sign_astraction)
assert s == "div by 0 error"
memory[0] = 0
interpret = Interpreter(noLog, "alwaysThrows2")
s = interpret.run(memory, 10, sign_astraction)
assert s == "div by 0 error"
memory[0] = -1
interpret = Interpreter(noLog, "alwaysThrows2")
s = interpret.run(memory, 10, sign_astraction)
assert s == "div by 0 error"
#alwaysThrows3
memory[0] = 1
memory[1] = 1
interpret = Interpreter(noLog, "alwaysThrows3")
s = interpret.run(memory, 10, sign_astraction)
assert s == "noProp"
memory[0] = 1
memory[1] = 0
interpret = Interpreter(noLog, "alwaysThrows3")
s = interpret.run(memory, 10, sign_astraction)
assert s == "div by 0 error"
memory[0] = 1
memory[1] = -1
interpret = Interpreter(noLog, "alwaysThrows3")
s = interpret.run(memory, 10, sign_astraction)
assert s == "noProp"
memory[0] = 0
memory[1] = 1
interpret = Interpreter(noLog, "alwaysThrows3")
s = interpret.run(memory, 10, sign_astraction)
assert s == "noProp"
memory[0] = 0
memory[1] = 0
interpret = Interpreter(noLog, "alwaysThrows3")
s = interpret.run(memory, 10, sign_astraction)
assert s == "div by 0 error"
memory[0] = 0
memory[1] = -1
interpret = Interpreter(noLog, "alwaysThrows3")
s = interpret.run(memory, 10, sign_astraction)
assert s == "noProp"
memory[0] = -1
memory[1] = 1
interpret = Interpreter(noLog, "alwaysThrows3")
s = interpret.run(memory, 10, sign_astraction)
assert s == "noProp"
memory[0] = -1
memory[1] = 0
interpret = Interpreter(noLog, "alwaysThrows3")
s = interpret.run(memory, 10, sign_astraction)
assert s == "div by 0 error"
memory[0] = -1
memory[1] = -1
interpret = Interpreter(noLog, "alwaysThrows3")
s = interpret.run(memory, 10, sign_astraction)
assert s == "noProp"
#alwaysThrows5
memory[0] = 1
memory[1] = 1
interpret = Interpreter(noLog, "alwaysThrows5")
s = interpret.run(memory, 10, sign_astraction)
assert s == "noProp"
memory[0] = 1
memory[1] = 0
interpret = Interpreter(noLog, "alwaysThrows5")
s = interpret.run(memory, 10, sign_astraction)
assert s == "noProp"
memory[0] = 1
memory[1] = -1
interpret = Interpreter(noLog, "alwaysThrows5")
s = interpret.run(memory, 10, sign_astraction)
assert s == "noProp"
memory[0] = 0
memory[1] = 1
interpret = Interpreter(noLog, "alwaysThrows5")
s = interpret.run(memory, 10, sign_astraction)
assert s == "div by 0 error"
memory[0] = 0
memory[1] = 0
interpret = Interpreter(noLog, "alwaysThrows5")
s = interpret.run(memory, 10, sign_astraction)
assert s == "div by 0 error"
memory[0] = 0
memory[1] = -1
interpret = Interpreter(noLog, "alwaysThrows5")
s = interpret.run(memory, 10, sign_astraction)
assert s == "div by 0 error"
memory[0] = -1
memory[1] = 1
interpret = Interpreter(noLog, "alwaysThrows5")
s = interpret.run(memory, 10, sign_astraction)
assert s == "noProp"
memory[0] = -1
memory[1] = 0
interpret = Interpreter(noLog, "alwaysThrows5")
s = interpret.run(memory, 10, sign_astraction)
assert s == "noProp"
memory[0] = -1
memory[1] = -1
interpret = Interpreter(noLog, "alwaysThrows5")
s = interpret.run(memory, 10, sign_astraction)
assert s == "noProp"

#Automatic testing with full range abstract variables
memory = {}
interpret = Interpreter(noLog, "alwaysThrows1")
s = interpret.run(memory, 10, sign_astraction)
assert s == "div by 0 error"
memory[0] = {"+","0","-"}
interpret = Interpreter(noLog, "alwaysThrows2")
s = interpret.run(memory, 10, sign_astraction)
assert s == "div by 0 error"
memory[0] = {"+","0","-"}
memory[1] = {"+","0","-"}
interpret = Interpreter(noLog, "alwaysThrows3")
s = interpret.run(memory, 10, sign_astraction)
assert s == "div by 0 error"
memory[0] = {"+","0","-"}
memory[1] = {"+","0","-"}
interpret = Interpreter(noLog, "alwaysThrows5")
s = interpret.run(memory, 10, sign_astraction)
assert s == "div by 0 error"
memory = {}
interpret = Interpreter(noLog, "itDependsOnLattice1")
s = interpret.run(memory, 10, sign_astraction)
assert s == "div by 0 error"

#setting arguments (need to be a list - make a list of a long length)
memory = {}
memory[0] = {"+","0","-"}
memory[1] = {"+","0","-"}
#Running the interpurator
interpret = Interpreter(print, "neverThrows5")  #This is wrong answer
s = interpret.run(memory, 10, sign_astraction)
print(s)
#print_bytecode("alwaysThrows4")

#Supports:
#Arithmetics:
#   alwaysThrows1
#   alwaysThrows2
#   alwaysThrows3
#   alwaysThrows4 (need range and assertion) (not done)
#   alwaysThrows5
#   itDependsOnLattice1 (sign = div 0, )
#   itDependsOnLattice2 (sign = div 0, )
#   itDependsOnLattice3 (need asserion)
#   itDependsOnLattice4 (sign = div 0, )
#   neverThrows1
#   neverThrows2 (need assertion)   (not done)
#   neverThrows3 (need assertion)   (not done)
#   neverThrows4 (need assetion)    (not done)
#   neverThrows5 (wrong)    (i suspect it is becouse the localVar dosent get limited in ifz statements but only stack dose)