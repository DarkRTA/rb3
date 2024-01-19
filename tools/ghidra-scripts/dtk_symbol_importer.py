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

for sym in currentProgram.getSymbolTable().getSymbolIterator():
    if sym.getSource() == USER_DEFINED:
        continue
    if sym.isPrimary():
        continue
    sym.delete()

for l in demangler_output.splitlines():
    tokens = l.split("|||")
    address = toAddr(tokens[0])
    lbl = tokens[1]
    name = tokens[2] if len(tokens) > 2 else lbl

    name = SymbolUtilities.replaceInvalidChars(str(name).split("(")[0], False)

    print("Creating label {} at address {}".format(name, address))

    sym = getSymbolAt(address)
    if sym == None:
        createLabel(address, lbl, False, IMPORTED)
        createLabel(address, name, True, ANALYSIS)
    else:
        createLabel(address, lbl, False, IMPORTED)
        createLabel(address, name, sym.getSource() != USER_DEFINED, ANALYSIS)
