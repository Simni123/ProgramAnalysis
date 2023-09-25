class Interpreter:
    def __init__(self):
        self.memory = {}
        self.stack = []
    
    def run(self, method):
        self.stack.append(method)
        while len(self.stack) != 0:
            self.step

    def step(self):
        (localVars, opStack, pc) = self.stack[-1]

#Finding all the json files
from pathlib import Path
import json

folder = Path("course-02242-examples-main/course-02242-examples-main/src/executables/java/dtu/compute/exec")
jsons = {}
for f in folder.glob("**/*.json"):
    source = open(f,"r")
    newKey = {f.name : json.load(source)}
    jsons.update(newKey)

#Finding all case methods
mehtods = {}
for jfile in jsons.values():
    for method in jfile["methods"]:
        for a in method["annotations"]:
            if a["type"] == "dtu/compute/exec/Case":
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
def interp(caseName, log, param):
    memory = {}
    mstack = [(param,[],(caseName, 0))]
    while True:
        log("->", mstack, end="")
        (localsVars, opStack, (cn_, i)) = mstack[-1]
        byte = find_method(caseName)["code"]["bytecode"][i]
        if byte["opr"] == "return":     #return
            if byte["type"] == None:
                log("   (return)")
                return None
            elif byte["type"] == "int":
                log("   (return)")
                return opStack[-1]
            else:
                log("Unsupported return type", byte)
                return None
        elif byte["opr"] == "push":     #push
            log("   (push)")
            value = byte["value"]["value"]
            _ = mstack.pop()
            mstack.append((localsVars, opStack + [value], (cn_, i + 1)))
        elif byte["opr"] == "load":     #load
            idx = byte["index"]
            log("   (load: {v})".format(v=idx))
            _ = mstack.pop()
            mstack.append((localsVars, opStack + [localsVars[idx]], (cn_, i + 1)))
        elif byte["opr"] == "binary":   #binary
            log("   (binary)", end="")
            if byte["operant"] == "add":    #add
                log("   (add)")
                sum = opStack.pop() + opStack.pop()
                _ = mstack.pop()
                mstack.append((localsVars, opStack + [sum], (cn_, i + 1)))
            elif byte["operant"] == "mul":  #mul
                log("   (mul)")
                mul = opStack.pop() * opStack.pop()
                _ = mstack.pop()
                mstack.append((localsVars, opStack + [mul], (cn_, i + 1)))
            elif byte["operant"] == "sub":  #sub
                log("   (sub)")
                v2 = opStack.pop()
                v1 = opStack.pop()
                sub = v1 - v2
                _ = mstack.pop()
                mstack.append((localsVars, opStack + [sub], (cn_, i + 1)))
            else:
                log("binary opperator not supported", byte)
                return None
        elif byte["opr"] == "if":   #if
            log("   (if)", end="")
            _ = mstack.pop()
            if byte["condition"] == "gt":   #gt
                log("   (gt)",end="")
                if opStack.pop() > opStack.pop():
                    log("   (->if)")
                    mstack.append((localsVars, opStack, (cn_, i + 1)))
                else:
                    log("   (->else)")
                    target = byte["target"]
                    mstack.append((localsVars, opStack, (cn_, target)))
            elif byte["condition"] == "ge": #ge
                log("   (ge)", end="")
                if opStack.pop() >= opStack.pop():
                    log("   (->if)")
                    mstack.append((localsVars, opStack, (cn_, i + 1)))
                else:
                    log("   (->else)")
                    target = byte["target"]
                    mstack.append((localsVars, opStack, (cn_, target)))
            else:
                log("if condition not supported", byte)
                return None
        elif byte["opr"] == "store":
            _ = mstack.pop()
            idx = byte["index"]
            log("   (store {v})".format(v=idx))
            localsVars[idx] = opStack.pop()
            mstack.append((localsVars, opStack, (cn_, i + 1)))
        elif byte["opr"] == "incr":  #incr
            _ = mstack.pop()
            idx = byte["index"]
            amount = byte["amount"]
            log("   (incr {v1} with {v2})".format(v1 = idx, v2 = amount))
            localsVars[idx] = localsVars[idx] + amount
            mstack.append((localsVars, opStack, (cn_, i + 1)))
        elif byte["opr"] == "ifz":  #ifz
            log("   (ifz)", end="")
            _ = mstack.pop()
            if byte["condition"] == "le":   #ifz le
                log("   (le)",end="")
                if opStack.pop() <= 0:
                    log("   (->if)")
                    target = byte["target"]
                    mstack.append((localsVars, opStack, (cn_, target)))
                else:
                    log("   (->else)")
                    mstack.append((localsVars, opStack, (cn_, i + 1)))
            else:
                log("   ifz condition not supported", byte)
                return None
        elif byte["opr"] == "goto": #goto
            log("   (goto)")
            _ = mstack.pop()
            target = byte["target"]
            mstack.append((localsVars, opStack, (cn_, target)))
        elif byte["opr"] == "array_load":
            log("   (array_load)")
            _ = mstack.pop()
            idx = opStack.pop()
            array = opStack.pop()
            val = array[idx]
            mstack.append((localsVars, opStack + [val], (cn_, i + 1)))
        elif byte["opr"] == "invoke":   #invoke
            log("   (invoke)")
            _ = mstack.pop()
            fun = byte["method"]["name"]
            args = byte["method"]["args"]
            newMem = {}
            for i in range (len(args)):
                newMem[i] = opStack.pop()
            val = interp(fun,log,newMem)
            print(val)
            mstack.append((localsVars, opStack + [val], (cn_, i + 1)))
        else:
            log(" fail", byte)
            return None

#setting arguments
memory = {}
memory[0] = [5]
#Running the interpurator
s = interp("firstSafe", print, memory)
print(s)




#Cases working
##Simple:
## noop
## zero
## hundredAndTwo
## identity
## add
## min
## factorial
##Calls:
## first    (unsure of represontation)
## firstSafe
