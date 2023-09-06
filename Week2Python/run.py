import os
import fnmatch
import graphviz
import re

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
    
class ClassDeclaration(SyntaxFold):
    def default(self, node, results):
        return set().union(*results)
    def method_declaration(self, node, results):
        return {node.text}
    
def extract_class_names(node):
    if node.type == 'class_declaration':
        # Find the identifier inside the class_declaration node
        for child_node in node.children:
            if child_node.type == 'identifier':
                return child_node.text
    # Recursively check child nodes
    for child_node in node.children:
        class_name = extract_class_names(child_node)
        if class_name:
            return class_name
    return None

def extract_field_names(node):
    if node.type == 'field_declaration':
        # Find the identifier inside the class_declaration node
        for child_node in node.children:
            if child_node.type == 'identifier':
                return child_node.text
    # Recursively check child nodes
    for child_node in node.children:
        class_name = extract_class_names(child_node)
        if class_name:
            return class_name
    return None

def is_java_file(filename):
    return fnmatch.fnmatch(filename, '*.java')

def main():
    directory = './deps'
    max_depth = 10
    graph = graphviz.Digraph()
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
            allTrees.append(parser.parse(f.read()))

    for tree in allTrees:
        print(extract_field_names(tree.root_node))
        dependencies = TypeIdentifiers().visit(tree.root_node)
        pattern = rb"b'([^']+)'"
        cleaned_class = re.sub(pattern, r'\1', extract_class_names(tree.root_node)).decode('utf-8')
        cleaned_dependencies = [re.sub(pattern, r'\1', s).decode('utf-8') for s in dependencies]
        if not cleaned_class in graph.body:
            graph.node(cleaned_class, cleaned_class)
        for dep in cleaned_dependencies:
            if dep in graph.body:
                graph.edge(cleaned_class, dep, '')
            else:
                graph.node(dep,dep)
                graph.edge(cleaned_class, dep, '')
    
    #graph.render('depGraph')

    
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

    