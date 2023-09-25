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

folder = Path("course-02242-examples-main/course-02242-examples-main/src/executables/java/eu/bogoe/dtu/exceptional")
jsons = {}
for f in folder.glob("**/*.json"):
    source = open(f,"r")
    newKey = {f.name : json.load(source)}
    jsons.update(newKey)

#Finding all case methods
mehtods = {}
for jfile in jsons.values():
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
def interp(caseName, log, param):
    state = {}
    mstack = [(param,[],(caseName, 0))]
    while True:
        log("->", mstack, end="")
        (localsVars, opStack, (cn_, i)) = mstack[-1]
        byte = find_method(caseName)["code"]["bytecode"][i]
        log(" fail", byte)
        return None

print_bytecode("alwaysThrows1")

#setting arguments
#memory = {}
#memory[0] = [5]
#Running the interpurator
#s = interp("firstSafe", print, memory)
#print(s)
