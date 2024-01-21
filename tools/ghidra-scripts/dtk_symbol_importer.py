# Import labels from a dtk symbols.txt
#@author Dark
#@category Import
#@menupath Tools.Import From dtk Symbols File

import re
from ghidra.program.model.symbol.SourceType import *
from ghidra.program.model.symbol import SymbolUtilities
import string
import subprocess

f = askFile("Symbols File", "OK")
demangler_output = subprocess.check_output(['rb3-batch-demangle', f.absolutePath])

symbolTable = currentProgram.getSymbolTable()
for sym in symbolTable.getSymbolIterator():
    if sym.getSource() == USER_DEFINED:
        continue
    if sym.isPrimary():
        continue
    sym.delete()

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
        namespaces = namespaces.split(" :: ")
        parent_namespace = None
        for namespace_lbl in namespaces:
            namespace_lbl = SymbolUtilities.replaceInvalidChars(namespace_lbl, True)
            namespace = createNamespace(parent_namespace, namespace_lbl)
            parent_namespace = namespace
    else:
        namespace = None

    sym = getSymbolAt(address)
    if sym == None:
        createLabel(address, lbl, namespace, False, IMPORTED)
        createLabel(address, name, namespace, True, ANALYSIS)
    else:
        createLabel(address, lbl, namespace, False, IMPORTED)
        createLabel(address, name, namespace, sym.getSource() != USER_DEFINED, ANALYSIS)
