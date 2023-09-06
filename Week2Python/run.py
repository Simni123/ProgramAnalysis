import os
import fnmatch

from tree_sitter import Language, Parser
FILE = "./languages.so" # the ./ is important
Language.build_library(FILE, ["tree-sitter-java"])
JAVA_LANGUAGE = Language(FILE, "java")

parser = Parser()
parser.set_language(JAVA_LANGUAGE)

class SyntaxFold:
    def visit(self, node):
        results = [ self.visit(n) for n in node.children ]
        if hasattr(self, node.type):
            return getattr(self, node.type)(node, results)
        else:
            return self.default(node, results)

    def default(self, node):
        print(node)

class Printer(SyntaxFold):
    def default(self, node, results):
        print(node)

class TypeIdentifiers(SyntaxFold):
    def default(self, node, results):
        return set().union(*results)
    def type_identifier(self, node, results):
        return {node.text}


def is_java_file(filename):
    return fnmatch.fnmatch(filename, '*.java')

def main():
    directory = './deps'
    max_depth = 10
    javaFiles = []

    for root, _, files in os.walk(directory):
        depth = root.count(os.path.sep) - directory.count(os.path.sep)
        if depth > max_depth:
            continue

        for filename in files:
            if is_java_file(filename):
                javaFiles.append(os.path.join(root, filename))

    allTrees = []
    for file in javaFiles:
        with open(file, "rb") as f:
            print(file)
            allTrees.append(parser.parse(f.read()))

    for tree in allTrees:
        print(TypeIdentifiers().visit(tree.root_node))
    

    
    #Printer().visit(allTrees[0].root_node)




def default(self, node, results):
    return set().union(*results)

def type_identifier(self, node, results):
    return {node.text}

#with open("Test.java", "rb") as f:
#    tree = parser.parse(f.read())

# the tree is now ready for analysing
#print(tree.root_node.sexp())
print("the program started")

main()

    