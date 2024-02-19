#!/usr/bin/env python3

###
# Generates build files for the project.
# This file also includes the project configuration,
# such as compiler flags and the object matching status.
#
# Usage:
#   python3 configure.py
#   ninja
#
# Append --help to see available options.
###

import sys
import argparse
import json

from pathlib import Path
from tools.project import (
    Object,
    ProjectConfig,
    calculate_progress,
    generate_build,
    is_windows,
)

from cflags_common import cflags_includes

# Game versions
DEFAULT_VERSION = 1
VERSIONS = [
    "SZBE69",    # 0
    "SZBE69_B8", # 1
]

if len(VERSIONS) > 1:
    versions_str = ", ".join(VERSIONS[:-1]) + f" or {VERSIONS[-1]}"
else:
    versions_str = VERSIONS[0]

parser = argparse.ArgumentParser()
parser.add_argument(
    "mode",
    default="configure",
    help="configure or progress (default: configure)",
    nargs="?",
)
parser.add_argument(
    "--version",
    dest="version",
    default=VERSIONS[DEFAULT_VERSION],
    help=f"version to build ({versions_str})",
)
parser.add_argument(
    "--build-dir",
    dest="build_dir",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--binutils",
    dest="binutils",
    type=Path,
    help="path to binutils (optional)",
)
parser.add_argument(
    "--compilers",
    dest="compilers",
    type=Path,
    help="path to compilers (optional)",
)
parser.add_argument(
    "--map",
    dest="map",
    action="store_true",
    help="generate map file(s)",
)
parser.add_argument(
    "--debug",
    dest="debug",
    action="store_true",
    help="build with debug info (non-matching)",
)
if not is_windows():
    parser.add_argument(
        "--wrapper",
        dest="wrapper",
        type=Path,
        help="path to wibo or wine (optional)",
    )
parser.add_argument(
    "--build-dtk",
    dest="build_dtk",
    type=Path,
    help="path to decomp-toolkit source (optional)",
)
parser.add_argument(
    "--sjiswrap",
    dest="sjiswrap",
    type=Path,
    help="path to sjiswrap.exe (optional)",
)
parser.add_argument(
    "--verbose",
    dest="verbose",
    action="store_true",
    help="print verbose output",
)
args = parser.parse_args()

config = ProjectConfig()
config.version = args.version.upper()
if config.version not in VERSIONS:
    sys.exit(f"Invalid version '{config.version}', expected {versions_str}")
version_num = VERSIONS.index(config.version)

# Apply arguments
config.build_dir = args.build_dir
config.build_dtk_path = args.build_dtk
config.binutils_path = args.binutils
config.compilers_path = args.compilers
config.debug = args.debug
config.generate_map = args.map
config.sjiswrap_path = args.sjiswrap
if not is_windows():
    config.wrapper = args.wrapper

# Tool versions
config.binutils_tag = "2.41-1"
config.compilers_tag = "20231018"
config.dtk_tag = "v0.7.2"
config.sjiswrap_tag = "v1.1.1"
config.wibo_tag = "0.6.11"

# Project
config_dir = Path("config") / config.version
flags_path = config_dir / "flags.json"
config.config_path = config_dir / "config.yml"
config.check_sha_path = config_dir / "build.sha1"

flags = json.load(open(flags_path, "r", encoding="utf-8"))

config.asflags = [
    "-mgekko",
    "--strip-local-absolute",
    f"-I build/{config.version}/include",
]
config.ldflags = flags["ldflags"]

cflags_runtime: list[str] = [] # Metrowerks library flags
cflags_base: list[str] = [] # Base flags for all other compile units
cflags_rb3: list[str] = []
cflags_sdk: list[str] = []

cflags = flags["cflags"]
cflags_runtime.extend(cflags["runtime"])
cflags_base.extend(cflags_includes)
cflags_base.extend(cflags["base"])

# Debug flags
if config.debug:
    cflags_base.append("-sym dwarf-2,full")
    cflags_runtime.append("-sym dwarf-2,full")

cflags_rb3.extend(cflags_base)
cflags_rb3.extend(cflags["rb3"])
cflags_sdk.extend(cflags_base)
cflags_sdk.extend(cflags["sdk"])

config.linker_version = "Wii/1.3"

config.shift_jis = False
config.progress_all = False

Matching = True
NonMatching = False

config.warn_missing_config = True
config.warn_missing_source = False
config.libs = [
    {
        "lib": "band3",
        "mw_version": "Wii/1.3",
        "cflags": cflags_rb3,
        "host": False,
        "objects": [

        ],
    },
    {
        "lib": "system",
        "mw_version": "Wii/1.3",
        "cflags": cflags_rb3,
        "host": False,
        "objects": [
            Object(Matching, "system/math/CustomArray.cpp"),
            Object(NonMatching, "system/math/Interp.cpp", extra_cflags=["-O4,s"]),
            Object(Matching, "system/math/Primes.cpp"),
            Object(Matching, "system/math/Rand2.cpp"),
            Object(Matching, "system/math/Vec.cpp"),

            Object(NonMatching, "system/obj/DataFlex.c"),
            Object(NonMatching, "system/obj/DataNode.cpp"),
            Object(NonMatching, "system/obj/Object.cpp"),
            Object(NonMatching, "system/obj/TypeProps.cpp"),

            Object(NonMatching, "system/utl/IntPacker.cpp"),
            Object(Matching, "system/utl/Symbols.cpp"),
            Object(Matching, "system/utl/Symbols2.cpp"),
            Object(Matching, "system/utl/Symbols3.cpp"),
            Object(Matching, "system/utl/Symbols4.cpp"),
            Object(NonMatching, "system/utl/SysTest.cpp"),
            Object(Matching, "system/utl/TempoMap.cpp"),
            Object(Matching, "system/utl/TextStream.cpp"),
        ],
    },
]

if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
elif args.mode == "progress":
    # Print progress and write progress.json
    config.progress_each_module = args.verbose
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
