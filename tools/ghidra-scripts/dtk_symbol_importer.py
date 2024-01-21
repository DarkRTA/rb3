# Import labels from a dtk symbols.txt
#@author Dark
#@category Import
#@menupath Tools.Import From dtk Symbols File

import subprocess

from ghidra.program.model.symbol import *

# Read/demangle symbols file
f = askFile("Symbols File", "OK")
demangler_output = subprocess.check_output(['rb3-batch-demangle', f.absolutePath])

# Delete non-primary/user existing symbols, as we'll be replacing them
symbolTable = currentProgram.getSymbolTable()
for sym in symbolTable.getSymbolIterator():
    if sym.getSource() == SourceType.USER_DEFINED:
        continue
    if sym.isPrimary():
        continue
    sym.delete()

# Apply demangled symbols to the program
created_namespaces = []
for l in demangler_output.splitlines():
    tokens = l.split("|||")

    address = toAddr(tokens[0])
    lbl = str(tokens[1])
    if len(tokens) > 3:
        demangled = str(tokens[2])
        namespaces = str(tokens[3])
        name = str(tokens[4])

        print("Creating label {} in namespace {} at address {}".format(name, namespaces.replace(" :: ", "::"), address))
    else:
        demangled = None
        namespaces = ""
        name = lbl

        print("Creating label {} in global namespace at address {}".format(name, address))

    name = SymbolUtilities.replaceInvalidChars(name, True)

    if namespaces != "":
        # Recursively create each namespace, Ghidra doesn't handle this for us
        namespaces = namespaces.split(" :: ")
        parent_namespace = None
        for namespace_lbl in namespaces:
            namespace_lbl = SymbolUtilities.replaceInvalidChars(namespace_lbl, True)
            namespace = createNamespace(parent_namespace, namespace_lbl)
            created_namespaces.append(namespace)
            parent_namespace = namespace
    else:
        namespace = None

    sym = getSymbolAt(address)
    if sym == None:
        createLabel(address, lbl, namespace, False, SourceType.IMPORTED)
        createLabel(address, name, namespace, True, SourceType.ANALYSIS)
    else:
        createLabel(address, lbl, namespace, False, SourceType.IMPORTED)
        createLabel(address, name, namespace, sym.getSource() != SourceType.USER_DEFINED, SourceType.ANALYSIS)

# Fix up class namespaces
class_symbols = ["__vt", "__vtable", "__RTTI", "__superclasses", "__classname"]
for namespace in created_namespaces:
    if namespace.getSymbol().getSymbolType() == SymbolType.CLASS:
        continue

    constructor_name = namespace.getName().split("<")[0]
    destructor_name = "~" + constructor_name
    for sym in symbolTable.getSymbols(namespace):
        sym_name = sym.getName()
        if sym_name in class_symbols or sym_name == constructor_name or sym_name == destructor_name:
            print("Converting namespace {} to class".format(namespace.getName()))
            symbolTable.convertNamespaceToClass(namespace)
            break
