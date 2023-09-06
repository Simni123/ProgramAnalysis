import os
import fnmatch

from tree_sitter import Language, Parser
FILE = "./languages.so" # the ./ is important
Language.build_library(FILE, ["tree-sitter-java"])
JAVA_LANGUAGE = Language(FILE, "java")

parser = Parser()
parser.set_language(JAVA_LANGUAGE)

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
    
    print(javaFiles)

    allTrees = []
    for file in javaFiles:
        with open("Test.java", "rb") as f:
            allTrees.append(parser.parse(f.read()))
    
    
    print(allTrees[0].root_node.get)




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

    