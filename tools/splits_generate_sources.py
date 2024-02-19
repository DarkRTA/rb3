import os
import re
from pathlib import *

# Finds .c/.cpp files and splits off the file extension
obj_regex = re.compile(r"(.*\.cp?p?):")

# Make sure this script still works if the working directory is the `tools` folder
base_path = os.curdir
if not os.path.exists(os.path.join(base_path, "src")):
    base_path = os.pardir

# Load splits file
splits_path = os.path.join(base_path, "config", "SZBE69_B8", "splits.txt")
with open(splits_path, "r") as symbols_file:
    symbols_text = symbols_file.read()

# Find source file names
for obj_match in obj_regex.finditer(symbols_text):
    obj_path = obj_match.group(1)
    src_path = os.path.join(base_path, "src_todo", obj_path)

    # Check if this file exists in the real source directory
    if os.path.exists(os.path.join(base_path, "src", obj_path)):
        if os.path.exists(src_path):
            os.remove(src_path)
        continue

    # Generate file for this split
    os.makedirs(os.path.dirname(src_path), exist_ok = True)
    with open(src_path, "w") as symbols_file:
        symbols_file.write("\n")
