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

from pathlib import Path
from tools.project import (
    Object,
    ProjectConfig,
    calculate_progress,
    generate_build,
    is_windows,
)

# Game versions
DEFAULT_VERSION = 0
VERSIONS = [
    "SZBE69",  # 0
]

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
config.compilers_path = args.compilers
config.debug = args.debug
config.generate_map = args.map
config.sjiswrap_path = args.sjiswrap
if not is_windows():
    config.wrapper = args.wrapper

# Tool versions
config.compilers_tag = "1"
config.dtk_tag = "v0.5.5"
config.sjiswrap_tag = "v1.1.1"
config.wibo_tag = "0.6.3"

# Project
config.config_path = Path("config") / config.version / "config.yml"
config.check_sha_path = Path("orig") / f"{config.version}.sha1"
config.ldflags = [
    "-fp hardware",
    "-nodefaults",
    "-listclosure",
    "-code_merging all",
]

cflags_base = [
    "-i src/PowerPC_EABI_Support/MSL_C/MSL_Common",
    "-i src/PowerPC_EABI_Support/MSL_C/MSL_Common_Embedded",
    "-i src/PowerPC_EABI_Support/MSL_C/MSL_Common_Embedded/Math",
    "-i src/PowerPC_EABI_Support/MetroTRK",
    # "-i src/tainted/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Include",
    "-i src/libogg/include",
    "-i src/speex/include",
    "-i src/speex",
    "-i src/RVL_SDK",
    "-i src/std",
    "-i src",
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    "-Cpp_exceptions off",
    # "-W all",
    "-O4,s",
    "-inline auto",
    '-pragma "cats off"',
    '-pragma "warn_notinlined off"',
    "-maxerrors 1",
    "-nosyspath",
    "-fp_contract on",
    "-str reuse,pool",
    "-func_align 4",
    "-gccinc",
];
cflags_rb3 = [
    *cflags_base,
    "-sdata 2",
    "-sdata2 2",
    "-pragma \"merge_float_consts on\"",
    "-RTTI on",
]

cflags_zlib = [
    *cflags_base,
    *cflags_rb3,
    "-pool on"
]


# Metrowerks library flags
cflags_runtime = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-common off",
]

# Debug flags
if config.debug:
    cflags_rb3.extend(["-sym dwarf-2,full"])
    cflags_runtime.extend(["-sym dwarf-2,full"])

cflags_runtime.append("-inline auto")
config.linker_version = "Wii/1.3"

Matching = True
NonMatching = False

config.warn_missing_config = True
config.warn_missing_source = False
config.libs = [
    {
        "lib": "rb3",
        "mw_version": "Wii/1.3",
        "cflags": cflags_rb3,
        "host": False,
        "objects": [
            Object(Matching, "rb3/datainittrigfuncs.cpp"),
            Object(Matching, "rb3/file_ops.cpp"),
            Object(Matching, "rb3/jsonobjects.cpp"),
            Object(Matching, "rb3/main.cpp"),
            Object(Matching, "rb3/optioninit.cpp"),
            Object(Matching, "rb3/rand.cpp"),
            Object(Matching, "rb3/rand2.cpp"),
            Object(Matching, "rb3/simpletempomap.cpp"),
            Object(Matching, "rb3/textfilestream.cpp"),
            Object(Matching, "rb3/textstream.cpp"),
            Object(Matching, "rb3/trigtable.cpp"),

            Object(NonMatching, "rb3/Rnd/rndbitmap.cpp"),
            Object(NonMatching, "rb3/Rnd/rnddrawable.cpp"),

            Object(NonMatching, "rb3/hmx/object.cpp"),
            Object(NonMatching, "rb3/app.cpp"),
            Object(NonMatching, "rb3/arkfile.cpp"),
            Object(NonMatching, "rb3/asyncfile.cpp"),
            Object(NonMatching, "rb3/asyncfilecnt.cpp"),
            Object(NonMatching, "rb3/asyncfilewii.cpp"),
            Object(NonMatching, "rb3/binstream.cpp"),
            Object(NonMatching, "rb3/bink.cpp"),
            Object(NonMatching, "rb3/formatstring.cpp"),
            Object(NonMatching, "rb3/interpolators.cpp"),
            Object(NonMatching, "rb3/joypad.cpp"),
            Object(NonMatching, "rb3/key_messages.cpp"),
            Object(NonMatching, "rb3/netstream.cpp"),
            Object(NonMatching, "rb3/notetube.cpp"),
            Object(NonMatching, "rb3/ogg_mem.cpp"),
            Object(NonMatching, "rb3/rg_messages.cpp"),
            Object(NonMatching, "rb3/string.cpp"),
            Object(NonMatching, "rb3/wiinetworksocket.cpp"),

            Object(NonMatching, "rb3/unknown/800/unk_8000D980.cpp"),
            Object(NonMatching, "rb3/unknown/800/unk_8000F9B0.cpp"),
            Object(NonMatching, "rb3/unknown/800/unk_800A673C.cpp"),
            Object(NonMatching, "rb3/unknown/800/unk_800AAE1C.cpp"),
            Object(NonMatching, "rb3/unknown/800/unk_800AB914.cpp"),
            Object(NonMatching, "rb3/unknown/800/unk_800AC804.cpp"),
            Object(NonMatching, "rb3/unknown/800/unk_800B4630.cpp"),
            Object(NonMatching, "rb3/unknown/800/unk_800BF1A8.cpp"),
            Object(NonMatching, "rb3/unknown/800/unk_800C9D04.cpp"),
            Object(NonMatching, "rb3/unknown/800/unk_800DB160.cpp"),
            Object(NonMatching, "rb3/unknown/800/unk_800F6DF8.cpp"),

            Object(NonMatching, "rb3/unknown/801/unk_8011AED8.cpp"),
            Object(NonMatching, "rb3/unknown/801/unk_801660DC.cpp"),
            Object(NonMatching, "rb3/unknown/801/unk_80188850.cpp"),

            Object(NonMatching, "rb3/unknown/802/unk_8022BE84.cpp"),
            Object(NonMatching, "rb3/unknown/802/unk_80252B98.cpp"),
            Object(NonMatching, "rb3/unknown/802/unk_802D4B74.cpp"),
            Object(NonMatching, "rb3/unknown/802/unk_802DDEA0.cpp"),
            Object(NonMatching, "rb3/unknown/802/unk_802E0CA0.cpp"),
            Object(NonMatching, "rb3/unknown/802/unk_802E9040.cpp"),
            Object(NonMatching, "rb3/unknown/802/unk_802F02EC.cpp"),
            Object(NonMatching, "rb3/unknown/802/unk_802F844C.cpp"),
            Object(NonMatching, "rb3/unknown/802/unk_802F98DC.cpp"),
            Object(NonMatching, "rb3/unknown/802/unk_802FA994.cpp"),
            Object(NonMatching, "rb3/unknown/802/unk_802FB548.cpp"),

            Object(NonMatching, "rb3/unknown/803/unk_8030A494.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_80313E98.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_8031B028.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_80322664.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_803242CC.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_8032443C.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_803431F4.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_8034C91C.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_8034C9F8.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_80354A30.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_80357E10.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_80362A50.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_8037A3D8.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_8037AD40.cpp"),

            Object(NonMatching, "rb3/unknown/804/unk_80421240.cpp"),

            Object(NonMatching, "rb3/unknown/805/unk_8050FA30.cpp"),
            Object(NonMatching, "rb3/unknown/805/unk_805CE140.cpp"),

            Object(NonMatching, "rb3/unknown/806/unk_80660D18.cpp"),
        ],
    },
    {
        "lib": "unknown",
        "mw_version": "Wii/1.3",
        "cflags": cflags_rb3,
        "host": False,
        "objects": [
        ],
    },
    {
        "lib": "quazal",
        "mw_version": "Wii/1.3",
        "cflags": cflags_rb3,
        "host": False,
        "objects": [
            Object(NonMatching, "quazal/datetime.cpp"),
            Object(NonMatching, "quazal/platform.cpp"),
            Object(NonMatching, "quazal/profilingunit.cpp"),
            Object(Matching, "quazal/qresult.cpp"),
            Object(Matching, "quazal/randomnumbergenerator.cpp"),
            Object(NonMatching, "quazal/refcountedobject.cpp"),
            Object(NonMatching, "quazal/rootobject.cpp"),
            Object(Matching, "quazal/stream.cpp"),
            Object(NonMatching, "quazal/string.cpp"),

            Object(NonMatching, "quazal/unknown/8001/unk_800135F0.cpp"),
            Object(NonMatching, "quazal/unknown/8001/unk_80018968.cpp"),
            Object(NonMatching, "quazal/unknown/8007/unk_8007BF84.cpp"),
            Object(NonMatching, "quazal/unknown/8007/unk_8007B998.cpp"),
            Object(NonMatching, "quazal/unknown/800A/unk_800A515C.cpp"),
        ],
    },
    {
        "lib": "json-c",
        "mw_version": "Wii/1.3",
        "cflags": cflags_rb3,
        "host": False,
        "objects": [
            Object(Matching, "json-c/arraylist.c"),
            Object(Matching, "json-c/json_object.c"),
            Object(Matching, "json-c/json_tokener.c"),
            Object(Matching, "json-c/linkhash.c"),
            Object(Matching, "json-c/printbuf.c")
        ]
    },
    {
        "lib": "zlib",
        "mw_version": "Wii/1.3",
        "cflags": cflags_zlib,
        "host": False,
        "objects": [
            Object(Matching, "zlib/adler32.c"),
            Object(Matching, "zlib/crc32.c"),
            Object(Matching, "zlib/deflate.c"),
            Object(Matching, "zlib/inflate.c"),
            Object(Matching, "zlib/inffast.c"),
            Object(Matching, "zlib/trees.c"),
            Object(Matching, "zlib/zutil.c")
        ]
    },
    {
        "lib": "zlib",
        "mw_version": "Wii/1.0",
        "cflags": cflags_zlib,
        "host": False,
        "objects": [
            Object(Matching, "zlib/inftrees.c")
        ]
    },
    {
        "lib": "libtomcrypt",
        "mw_version": "Wii/1.0",
        "cflags": cflags_zlib,
        "host": False,
        "objects": [
            Object(NonMatching, "libtomcrypt/aes.c"),
            Object(Matching, "libtomcrypt/crypt.c"),
            Object(NonMatching, "libtomcrypt/ctr.c")
        ],
    },
    {
        "lib": "speex",
        "mw_version": "Wii/1.3",
        "cflags": cflags_zlib,
        "host": False,
        "objects": [
            Object(Matching, "speex/libspeex/bits.c"),
            Object(Matching, "speex/libspeex/cb_search.c"),
            Object(NonMatching, "speex/libspeex/filters.c"),
            Object(Matching, "speex/libspeex/lpc.c"),
            Object(Matching, "speex/libspeex/lsp.c"),
            Object(Matching, "speex/libspeex/ltp.c"),
            Object(NonMatching, "speex/libspeex/nb_celp.c"),
            Object(NonMatching, "speex/libspeex/quant_lsp.c"),
            Object(NonMatching, "speex/libspeex/speex.c"),
            Object(Matching, "speex/libspeex/speex_callbacks.c"),
            Object(NonMatching, "speex/libspeex/vbr.c"),
            Object(Matching, "speex/libspeex/vq.c")
        ]
    },
    {
        "lib": "libogg",
        "mw_version": "Wii/1.3",
        "cflags": cflags_rb3,
        "host": False,
        "objects": [
            Object(Matching, "libogg/src/bitwise.c"),
            Object(Matching, "libogg/src/framing.c")
        ],
    },
    {
        "lib": "vorbis",
        "mw_version": "Wii/1.3",
        "cflags": cflags_rb3,
        "host": False,
        "objects": [
            Object(Matching, "vorbis/bitrate.c"),
            Object(Matching, "vorbis/block.c"),
            Object(NonMatching, "vorbis/codebook.c"),
            Object(Matching, "vorbis/envelope.c"),
            Object(NonMatching, "vorbis/floor0.c"),
            Object(NonMatching, "vorbis/floor1.c"),
            Object(Matching, "vorbis/info.c"),
            Object(Matching, "vorbis/lsp.c"),
            Object(NonMatching, "vorbis/mapping0.c"),
            Object(NonMatching, "vorbis/mdct.c"),
            Object(NonMatching, "vorbis/psy.c"),
            Object(NonMatching, "vorbis/res0.c"),
            Object(NonMatching, "vorbis/sharedbook.c"),
            Object(Matching, "vorbis/smallft.c"),
            Object(NonMatching, "vorbis/window.c")
        ],
    },
    # anything below this line does not need to be decompiled
    # you can attempt to match these if you want though
    {
        "lib": "MSL_C",
        "mw_version": "Wii/1.3",
        "cflags": cflags_runtime,
        "host": False,
        "objects": [
            Object(Matching, "MSL_C/text_1.c"),
            Object(Matching, "MSL_C/sdata_1.c"),
        ]
    },
    {
        "lib": "Runtime.PPCEABI.H",
        "mw_version": "Wii/1.3",
        "cflags": cflags_runtime,
        "host": False,
        "objects": [
            Object(Matching, "Runtime/global_destructor_chain.c"),
            Object(Matching, "Runtime/__init_cpp_exceptions.cpp"),
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
