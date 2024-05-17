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
# Be sure to update macros.h if this list changes!
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
parser.add_argument(
    "--non-matching",
    dest="non_matching",
    action="store_true",
    help="builds equivalent (but not matching) files",
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
config.non_matching = args.non_matching

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
objects_path = config_dir / "objects.json"
config.config_path = config_dir / "config.yml"
config.check_sha_path = config_dir / "build.sha1"
config.reconfig_deps = [
    flags_path,
    objects_path,
]

# Build flags
flags = json.load(open(flags_path, "r", encoding="utf-8"))

config.asflags = [
    "-mgekko",
    "--strip-local-absolute",
    f"-I build/{config.version}/include",
]
config.ldflags = flags["ldflags"]

cflags: dict[str, dict] = flags["cflags"]

def get_flags(name: str) -> list[str]:
    return cflags[name]["flags"]
def add_flags(name: str, flags: list[str]):
    cflags[name]["flags"] = [*flags, *cflags[name]["flags"]]

def get_flags_base(name: str) -> str:
    return cflags[name]["base"]

def are_flags_inherited(name: str) -> bool:
    return "inherited" in cflags[name]
def set_flags_inherited(name: str):
    cflags[name]["inherited"] = True

# Additional base flags
base_flags = get_flags("base")
base_flags.append(f"-d GAME_VERSION={version_num}")
if config.debug:
    base_flags.append("-sym dwarf-2,full")

# Apply cflag inheritance
def apply_base_flags(key: str):
    if are_flags_inherited(key):
        return

    base = get_flags_base(key)
    if base is None:
        add_flags(key, cflags_includes)
    else:
        apply_base_flags(base)
        add_flags(key, get_flags(base))

    set_flags_inherited(key)

for key in cflags.keys():
    apply_base_flags(key)

config.linker_version = "Wii/1.3"

config.shift_jis = False
config.progress_all = False

# Object files
Matching = True
Equivalent = config.non_matching
NonMatching = False

config.warn_missing_config = False
config.warn_missing_source = False

def get_object_completed(status: str) -> bool:
    if status == "Matching":
        return Matching
    elif status == "NonMatching":
        return NonMatching
    elif status == "Equivalent":
        return Equivalent
    elif status == "LinkIssues":
        return NonMatching

    assert False, f"Invalid object status {status}"

libs: list[dict] = []
objects: dict[str, dict] = json.load(open(objects_path, "r", encoding="utf-8"))
for (lib, lib_config) in objects.items():
    lib_mw_version: str = lib_config["mw_version"]

    # config_cflags: str | list[str]
    config_cflags: list[str] = lib_config["cflags"]
    lib_cflags = get_flags(config_cflags) if type(config_cflags) is str else config_cflags

    lib_objects: list[Object] = []
    # config_objects: dict[str, str | dict]
    config_objects: dict[str, dict] = lib_config["objects"]
    if len(config_objects) < 1:
        continue

    for (path, obj_config) in config_objects.items():
        if type(obj_config) is str:
            completed = get_object_completed(obj_config)
            lib_objects.append(Object(completed, path))
        else:
            completed = get_object_completed(obj_config["status"])

            if "cflags" in obj_config:
                object_cflags = obj_config["cflags"]
                if type(object_cflags) is str:
                    obj_config["cflags"] = get_flags(object_cflags)

            lib_objects.append(Object(completed, path, **obj_config))
        pass

    libs.append({
        "lib": lib,
        "mw_version": lib_mw_version,
        "cflags": lib_cflags,
        "host": False,
        "objects": lib_objects,
    })

config.libs = libs

if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
elif args.mode == "progress":
    # Print progress and write progress.json
    config.progress_each_module = args.verbose
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
