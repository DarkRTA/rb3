# Import labels from a dtk symbols.txt
#@author Dark
#@category Import
#@menupath Tools.Import From dtk Symbols File

import re
from ghidra.program.model.symbol.SourceType import *
from ghidra.program.model.symbol import SymbolUtilities;
import string
import subprocess

functionManager = currentProgram.getFunctionManager()
symutils = SymbolUtilities();

def demangle(sym):
    try:
        # TODO: port the demangler to python as calling cwdemangle is SLOW
        demangler_output = subprocess.check_output(['cwdemangle', name])
        return SymbolUtilities.replaceInvalidChars(str(demangler_output), False)
    except:
        return sym


f = askFile("Symbols File", "OK")

for l in file(f.absolutePath):
    tokens = l.split(" ")
    addr_matches = re.search(r'0x........', tokens[2])
    if addr_matches == None:
        raise Exception("invalid symbols file")

    address = toAddr(addr_matches.group(0))
    name = tokens[0]
    #demangled_name = demangle(name)

    print("Created label {} at address {}".format(name, address))
    createLabel(address, name, False, IMPORTED)
    #createLabel(address, demangled_name, True, ANALYSIS)
