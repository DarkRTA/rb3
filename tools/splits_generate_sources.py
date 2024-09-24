import json
import os
import re

# Paths used for each library in objects.json
lib_paths = {
    "main": "",

    "band3": "band3",

    "lib/binkwii": "lib/binkwii",

    "network": "network",
    "network/json_c": "network/net/json-c",
    "network/Platform": "network/Platform",

    "sdk": "sdk",
    "sdk/DWC": "sdk/DWC",
    "sdk/ec": "sdk/ec",
    "sdk/NdevExi2A": "sdk/NdevExi2A",

    "sdk/PowerPC_EABI_Support": "sdk/PowerPC_EABI_Support",
    "sdk/MetroTRK": "sdk/PowerPC_EABI_Support/MetroTRK",
    "sdk/MSL": "sdk/PowerPC_EABI_Support/MSL",
    "sdk/MSL_C": "sdk/PowerPC_EABI_Support/MSL/MSL_C",
    "sdk/MSL_C/fdlibm": "sdk/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/Math",
    "sdk/MSL_C++": "sdk/PowerPC_EABI_Support/MSL/MSL_C++",
    "sdk/Runtime": "sdk/PowerPC_EABI_Support/Runtime",

    "sdk/RevoEX": "sdk/RevoEX",
    "sdk/RVL_SDK": "sdk/RVL_SDK",

    "system": "system",
    "system/flex": "system/system/obj/DataFlex.c",
    "system/speex": "system/speex",
    "system/soundtouch": "system/synthwii/soundtouch",
    "system/tomcrypt": "system/synth/tomcrypt",
    "system/vorbis": "system/oggvorbis",
    "system/zlib": "system/zlib",
}
default_lib = "main"

# Finds .c/.cpp files and splits off the file extension
obj_regex = re.compile(r"(.*\.cp?p?):")

# Make sure this script still works if the working directory is the `tools` folder
base_path = os.curdir
if not os.path.exists(os.path.join(base_path, "src")):
    base_path = os.pardir

# Load splits file
config_path = os.path.join(base_path, "config", "SZBE69_B8")
splits_path = os.path.join(config_path, "splits.txt")
with open(splits_path, "r") as symbols_file:
    symbols_text = symbols_file.read()

# Load objects.json
objects_path = os.path.join(config_path, "objects.json")
with open(objects_path, "r") as objects_file:
    existing_objects: dict[str, dict] = json.load(objects_file)

# Go through each object in the splits
missing_objects: dict[str, dict] = {}
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
    with open(src_path, "w") as dummy_file:
        dummy_file.write("\n")

    # Determine which library this split belongs to
    selected_lib = default_lib
    for (lib, glob) in lib_paths.items():
        if obj_path.startswith(glob) and len(glob) > len(lib_paths[selected_lib]):
            selected_lib = lib

    # Add to list of missing objects
    if selected_lib not in existing_objects or obj_path not in existing_objects[selected_lib]["objects"]:
        if selected_lib not in missing_objects:
            missing_objects[selected_lib] = {}
        missing_objects[selected_lib][obj_path] = "MISSING"

if len(missing_objects) > 0:
    missing_objects_path = os.path.join(config_path, "missing_objects.json")
    with open(missing_objects_path, "w") as missing_objects_file:
        json.dump(missing_objects, missing_objects_file, indent=4, sort_keys=True)
