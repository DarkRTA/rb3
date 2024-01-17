# Import labels from a dtk symbols.txt
#@author Dark
#@category Import
#@menupath Tools.Import From dtk Symbols File

import re
from ghidra.program.model.symbol.SourceType import *
from ghidra.program.model.symbol import SymbolUtilities
import string
import subprocess

def demangle(sym):
    try:
        # TODO: port the demangler to python as calling cwdemangle is SLOW
        demangler_output = subprocess.check_output(['cwdemangle', sym])
        return SymbolUtilities.replaceInvalidChars(str(demangler_output).split("(")[0], False)
    except:
        return sym

f = askFile("Symbols File", "OK")

# cleanup existing syms
for sym in currentProgram.getSymbolTable().getSymbolIterator():
    if sym.getSource() == USER_DEFINED:
        continue
    if sym.isPrimary():
        continue
    sym.delete()

for l in file(f.absolutePath):
    tokens = l.split(" ")
    addr_matches = re.search(r'0x........', tokens[2])
    if addr_matches == None:
        raise Exception("invalid symbols file")

    address = toAddr(addr_matches.group(0))
    name = tokens[0]
    demangled_name = demangle(name)
    print("Created label {} at address {}".format(demangled_name, address))

    sym = getSymbolAt(address)

    if sym == None:
        createLabel(address, name, False, IMPORTED)
        createLabel(address, demangled_name, True, ANALYSIS)
    else:
        createLabel(address, name, False, IMPORTED)
        createLabel(address, demangled_name, sym.getSource() != USER_DEFINED, ANALYSIS)
