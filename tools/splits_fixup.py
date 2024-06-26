import os
import re

# Converts split paths from archive/object paths to source paths.
# Various fixups are applied to organize things to our liking.

# Finds .o/.obj files and splits off the file extension
obj_regex = re.compile(r"(.*)\.ob?j?")

# Replaces any variation of `/src/` with just `/`
src_regex = re.compile(r"[\\\/][Ss][Rr][Cc][\\\/]")

# Determines if an object is within an archive,
# and splits the archive name from the rest of the path
archive_regex = re.compile(r"(.*?)\.a[\\\/](.*)")

# Cleans up RB3 project paths
# Removes "hproj" and "wii_release" path components
band_regex = re.compile(r"hproj[\\\/]band3_wii[\\\/](.*)[\\\/]wii_release[\\\/](.*)")

# RVL SDK archives
# Most of these names are sourced from various other places in doldecomp
# Others are present in the RB3 debug map
rvl_names = [
    "ai", "ar", "aralt", "arc", "arq", "ax", "axfx",
    "base", "bte",
    "card", "cnt", "cx",
    "darch", "db", "dsp", "dvd", "dwc",
    "eart", "enc", "esp", "euart", "exi",
    "fs",
    "gba", "gd", "gf", "gx",
    "hbm", "hid",
    "ipc",
    "kbd", "kpad", "kpr",
    "mem", "mix", "mtx",
    "nand",
    "os",
    "pad",
    "rso", "rvl",
    "sc", "scutil", "sdi", "si", "socket",
    "thp", "tpl",
    "usb", "usbcmn", "usbmic",
    "vf", "vi",
    "wenc", "wpad", "wpaddrm", "wpadgtr", "wud",
]

# RevoEX archives
# https://discord.com/channels/727908905392275526/1050967074090004500/1208698417853890580
revo_ex_names = [
    "mp", "mpdl", "mpds",
    "ncd", "net", "nhttp", "ntr", "nwc24",
    "so", "ssl",
    "vf",
    "wd",
]

# DWC archives
# https://discord.com/channels/727908905392275526/1050967074090004500/1208699973156347955
dwc_names = [
    "dwc_common",
    "dwc_nonport",
    "dwcsec_auth",
    "dwcsec_nas",
    "dwcsec_prof",
    "dwcsec_svl",
]

# Other SDK libs
sdk_c_names = [
    "NdevExi2A",
    "mobiclip",
]
sdk_cpp_names = [
    "ec",
]

# Make sure this script still works if the working directory is the `tools` folder
base_path = os.curdir
if not os.path.exists(os.path.join(base_path, "src")):
    base_path = os.pardir

# Load original generated splits file
splits_path = os.path.join(base_path, "config", "SZBE69_B8", "splits.txt")
with open(splits_path, "r") as symbols_file:
    symbols_text = symbols_file.read()

# Search splits
new_symbols_text: list[str] = []
previous_match_end = 0
for obj_match in obj_regex.finditer(symbols_text):
    obj_path = src_regex.sub("/", obj_match.group(1))
    path_range = range(obj_match.start(), obj_match.end())

    # Check if the object is contained in an archive
    lib_match = archive_regex.match(obj_path)
    if lib_match is None:
        # Assume C++ if not, and place in top-level directory
        obj_path = obj_path + ".cpp"
    else:
        lib_name = lib_match.group(1)
        lib_path = lib_match.group(2)

        # Determine which library this is and how to organize it
        if lib_name == "lib":
            # RB3 code, determine folders and put them in top-level directory
            band_match = band_regex.match(lib_path)
            assert band_match is not None
            obj_path = band_match.group(1) + "/" + band_match.group(2) + ".cpp"
        elif lib_name == "MSL_C.PPCEABI.bare.H":
            # Results in sdk/PowerPC_EABI_Support/MSL_C/...
            obj_path = "sdk/" + lib_path.removeprefix("Products/Eppc/TempBuildMSL/") + ".c"
        elif lib_name == "MSL_C++.PPCEABI.bare.H":
            # Results in sdk/PowerPC_EABI_Support/MSL_C++/...
            obj_path = "sdk/" + lib_path.removeprefix("Products/Eppc/TempBuildMSL/") + ".cpp"
        elif lib_name == "Runtime.PPCEABI.H":
            obj_path = f"sdk/PowerPC_EABI_Support/Runtime/{lib_path}.cpp"
        elif lib_name == "TRK_Hollywood_Revolution":
            obj_path = f"sdk/PowerPC_EABI_Support/MetroTRK/" + lib_path.removeprefix("Data/wiiProj/metrotrk/metrotrk/") + ".c"
        elif lib_name in sdk_c_names:
            obj_path = f"sdk/{lib_name}/{lib_path}.c"
        elif lib_name in sdk_cpp_names:
            obj_path = f"sdk/{lib_name}/{lib_path}.cpp"
        else:
            # RVL SDK and related libs, check as lowercase
            lib_name_lower = lib_name.lower()
            if lib_name_lower in rvl_names:
                obj_path = f"sdk/RVL_SDK/{lib_name}/{lib_path}.c"
            elif lib_name_lower in revo_ex_names:
                obj_path = f"sdk/RevoEX/{lib_name}/{lib_path}.c"
            elif lib_name_lower in dwc_names:
                obj_path = f"sdk/DWC/{lib_name}/{lib_path}.c"
            # For documentation purposes; not necessary for us
            # elif lib_name_lower == "rfl":
            #   obj_path = f"sdk/RVLFaceLib/{lib_path}.c"

            # Undetermined source, place into lib/ directory
            else:
                obj_path = f"lib/{lib_name}/{lib_path}.c"

    # Modify splits to use the determined path
    new_symbols_text.append(symbols_text[previous_match_end:obj_match.start()])
    new_symbols_text.append(obj_path)
    previous_match_end = obj_match.end()

# Remaining file text
new_symbols_text.append(symbols_text[previous_match_end:])

# Write new splits file
with open(splits_path, "w") as symbols_file:
    for piece in new_symbols_text:
        symbols_file.write(piece)
