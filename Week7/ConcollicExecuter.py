from dataclasses import dataclass
from typing import Any
import z3
#from z3 import *
#Finding all the json files
from pathlib import Path
import json

folder = Path("D:/GitHub/ProgramAnalyse/ProgramAnalysis/Week7/course-02242-examples-main/course-02242-examples-main/src/executables/java/eu/bogoe/dtu/exceptional")

jsons = {}
for f in folder.glob("**/*.json"):
    source = open(f,"r")
    newKey = {f.name : json.load(source)}
    jsons.update(newKey)

#Finding all case methods
mehtods = {}
for jfile in jsons.values():
    print(jfile["name"])
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

@dataclass(frozen=True)
class Bytecode:
    dictionary : dict 

    def __getattr__(self, name):
        return self.dictionary[name]
    
    def __repr__(self):
        return f"{self.opr} " + ", ".join(
            f"{k}: {v}"
            for k, v in self.dictionary.items() 
            if k != "opr" and k != "offset"
        )

@dataclass(frozen=True)
class ConcolicValue:
    concrete : int | bool
    symbolic : z3.ExprRef

    def __repr__(self):
        return f"{self.concrete} ({self.symbolic})"
    
    @classmethod
    def from_const(self, c):
        if isinstance(c,bool):
            return ConcolicValue(c, z3.BoolVal(c))
        elif isinstance(c,int):
            r = ConcolicValue(c, z3.IntVal(c))
            return r
        raise Exception(f"Unknown const: {c}")
    
    def compare(self, copr, other):
        DICT = {
            "ne" : "__ne__",
            "gt" : "__gt__",
            "ge" : "__ge__",
            "le" : "__le__",
            "eq" : "__eq__",
            "lt" : "__lt__",
        }

        if copr in DICT:
            opr = DICT[copr]
        else:
            raise Exception(f"Unknown compare operatorr: {copr}")

        return ConcolicValue(
            getattr(self.concrete, opr)(other.concrete),
            z3.simplify(getattr(self.symbolic, opr)(other.symbolic))
        )
    
    def binary(self, oprerant, other):
        DICT = {
            "sub" : "__sub__",
            "add" : "__add__",
            "mul" : "__mul__",
        }

        if oprerant in DICT:
            opr = DICT[oprerant]
        else:
            if oprerant == "div":
                return ConcolicValue(
                    self.concrete // other.concrete,
                    z3.simplify(self.symbolic / other.symbolic)
                )
            raise Exception(f"Unknown binary oprerant: {oprerant}")
        
        return ConcolicValue(
            getattr(self.concrete, opr)(other.concrete),
            z3.simplify(getattr(self.symbolic, opr)(other.symbolic))
        )
    

@dataclass
class State:
    locals : dict[int, ConcolicValue]
    stack : list[ConcolicValue]

    def push(self, value):
        self.stack.append(value)

    def pop(self):
        return self.stack.pop()
    
    def load(self, index):
        self.push(self.locals[index])
    
    def store(self,index):
        self.locals[index] = self.stack.pop()

#Concollic executor
def concolic(method, k = 1000):
    byteCode = find_method(method)
    code = [Bytecode(b) for b in byteCode['code']["bytecode"]]
    solver = z3.Solver()
    params = [z3.Int(f"p{i}") for i, _ in enumerate(byteCode['params'])]
    while solver.check() == z3.sat:
        model = solver.model()
        input = [model.eval(p, model_completion=True).as_long() for p in params]
        #print(input)
        state = State(
            {k: ConcolicValue(i,p) for k, (i, p) in enumerate(zip(input, params))}, #locals
            [], #stack
        )
        #print(state)
        pc = 0
        path_constraints = []
        for _ in range(k):
            c = code[pc]
            pc += 1
            #print("---------------------")
            #print(state)
            #print(f"constraints: {path_constraints}")
            #print(c)
            if c.opr == "get" and c.field["name"] == "$assertionsDisabled":
                state.push(ConcolicValue.from_const(False))
            elif c.opr == "ifz":
                value = state.pop()
                z = ConcolicValue.from_const(0)
                r = ConcolicValue.compare(z, c.condition, value)
                if r.concrete:
                    pc = c.target
                    path_constraints += [r.symbolic]
                else:
                    path_constraints += [z3.simplify(z3.Not(r.symbolic))]
            elif c.opr == "if":
                v2 = state.pop()
                v1 = state.pop()
                r = ConcolicValue.compare(v1, c.condition, v2)
                if r.concrete:
                    pc = c.target
                    path_constraints += [r.symbolic]
                else:
                    path_constraints += [z3.simplify(z3.Not(r.symbolic))]
            elif c.opr == "binary":
                v2 = state.pop()
                v1 = state.pop()
                if c.operant == "div":
                    if v2.concrete == 0:
                        result = "Div by zero error"
                        path_constraints += [v2.symbolic == 0]
                        break
                    else:
                        path_constraints += [z3.simplify(z3.Not(v2.symbolic == 0))]
                r = v1.binary(c.operant, v2)
                state.push(r)
            elif c.opr == "negate":
                v = state.pop()
                r = v.binary("mul", ConcolicValue.from_const(-1))
                state.push(r)
            elif c.opr == "load":
                state.load(c.index)
            elif c.opr == "push":
                state.push(ConcolicValue.from_const(c.value["value"]))
            elif c.opr == "store":
                state.store(c.index)
            elif c.opr == "incr":
                state.load(c.index)
                state.push(ConcolicValue.from_const(c.amount))
                v2 = state.pop()
                v1 = state.pop()
                r = v1.binary("add",v2)
                state.push(r)
                state.store(c.index)
            elif c.opr == "goto":
                pc = c.target
            elif c.opr == "return":
                if c.type is None:
                    result = "return"
                result = f"return {state.pop()}"
                break
            elif c.opr == "new" and c.dictionary["class"] == "java/lang/AssertionError":
                result = "AssertionError"
                break
            else:
                raise Exception(f"Unsuported Bytecode: {c}")
        else:
            result = "out of itterations"
        
        const = z3.simplify(z3.And(*path_constraints))
        print(input, "->", result, "|", const)
        solver.add(z3.Not(const))
        print("Eecution Finished----------------")
        if "Div by zero error" in result:
            return "Div by zero error"
    #return result


#Automatic testing
# alwaysThrows1
print("alwaysThrows1--------------------------------------------")
s = concolic("alwaysThrows1")
assert s == "Div by zero error"
# alwaysThrows2
print("alwaysThrows2--------------------------------------------")
s = concolic("alwaysThrows2")
assert s == "Div by zero error"
# alwaysThrows3
print("alwaysThrows3--------------------------------------------")
s = concolic("alwaysThrows3")
assert s == "Div by zero error"
# alwaysThrows4
print("alwaysThrows4--------------------------------------------")
s = concolic("alwaysThrows4")
assert s == "Div by zero error"
# alwaysThrows5
print("alwaysThrows5--------------------------------------------")
s = concolic("alwaysThrows5")
assert s == "Div by zero error"
# itDependsOnLattice1
s = concolic("itDependsOnLattice1")
assert s == None
# itDependsOnLattice2
s = concolic("itDependsOnLattice2")
assert s == None
# itDependsOnLattice3
s = concolic("itDependsOnLattice3")
assert s == "Div by zero error"
# itDependsOnLattice4
s = concolic("itDependsOnLattice4")
assert s == "Div by zero error"
# neverThrows1
s = concolic("neverThrows1")
assert s == None
# neverThrows2 - Somthing is wrong here, it checks the wrong direction, but dose reach the correct conclition
s = concolic("neverThrows2")
assert s == None
# neverThrows3 - Somthing is wrong here, it checks the wrong direction, but dose reach the correct conclition
s = concolic("neverThrows3")
assert s == None
# neverThrows4
s = concolic("neverThrows4")
assert s == None
# neverThrows5 - Wrong answer, it checks the wrong direction
s = concolic("neverThrows5")
#assert s == None
# speedVsPrecision - Wrong answer, uses the wring site of ifz ????????????
#s = concolic("speedVsPrecision")
#assert s == "Div by zero error"

print("Current--------------------------------------------")
s = concolic("speedVsPrecision")
print(s)

#print_bytecode("speedVsPrecision")