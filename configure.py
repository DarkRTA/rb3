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

from cflags_common import cflags_includes, cflags_defines

# Game versions
DEFAULT_VERSION = 0
VERSIONS = [
    "SZBE69",  # 0
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
config.config_path = Path("config") / config.version / "config.yml"
config.check_sha_path = Path("config") / config.version / "build.sha1"
config.asflags = [
    "-mgekko",
    "--strip-local-absolute",
    f"-I build/{config.version}/include",
]
config.ldflags = [
    "-fp hardware",
    "-nodefaults",
    "-listclosure",
    "-code_merging safe,aggressive",
]
config.shift_jis = False
config.progress_all = False

cflags_base = [
    *cflags_includes,
    *cflags_defines,
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    "-Cpp_exceptions off",
    # "-W all",
    "-O4,s",
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
    "-inline off",
]

cflags_c = [
    *cflags_base,
    "-lang=c99",
    "-sdata 2",
    "-sdata2 2",
    "-pragma \"merge_float_consts on\"",
    "-inline auto",
]

cflags_sdk = [
    *cflags_base,
    "-func_align 16"
]

cflags_zlib = [
    *cflags_c,
    "-pool on"
]

cflags_bt = [
    *cflags_c,
    "-str reuse,nopool"
]


# Metrowerks library flags
cflags_runtime = [
    *cflags_c,
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

# For objects that are affected by code merging and such
# Periodically try setting this to True to see if anything's started matching
LinkIssues = False

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

            Object(NonMatching, "rb3/dofproc.cpp"),
            Object(NonMatching, "rb3/Rnd/rndanimatable.cpp"),
            Object(NonMatching, "rb3/Rnd/rndanimfilter.cpp"),
            Object(NonMatching, "rb3/Rnd/rndbitmap.cpp"),
            Object(NonMatching, "rb3/Rnd/rndcam.cpp"),
            Object(NonMatching, "rb3/Rnd/rnddrawable.cpp"),
            Object(NonMatching, "rb3/Rnd/rnddir.cpp"),
            Object(NonMatching, "rb3/Rnd/rndenviron.cpp"),
            Object(NonMatching, "rb3/Rnd/rndflare.cpp"),
            Object(NonMatching, "rb3/Rnd/rndfont.cpp"),
            Object(NonMatching, "rb3/Rnd/rndgenerator.cpp"),
            Object(NonMatching, "rb3/Rnd/rndgroup.cpp"),
            Object(NonMatching, "rb3/Rnd/rndlight.cpp"),
            Object(NonMatching, "rb3/Rnd/rndlightanim.cpp"),
            Object(NonMatching, "rb3/Rnd/rndmesh.cpp"),
            Object(NonMatching, "rb3/Rnd/rndmeshanim.cpp"),
            Object(NonMatching, "rb3/Rnd/rndmotionblur.cpp"),
            Object(NonMatching, "rb3/Rnd/rndmovie.cpp"),
            Object(NonMatching, "rb3/Rnd/rndmultimesh.cpp"),
            Object(NonMatching, "rb3/Rnd/rndmultimeshproxy.cpp"),
            Object(NonMatching, "rb3/Rnd/rndoverlay.cpp"),
            Object(NonMatching, "rb3/Rnd/rndparticlesys.cpp"),
            Object(NonMatching, "rb3/Rnd/rndparticlesysanim.cpp"),
            Object(NonMatching, "rb3/Rnd/rndpartlauncher.cpp"),
            Object(NonMatching, "rb3/Rnd/rnd.cpp"),
            Object(NonMatching, "rb3/Rnd/rndscreenmask.cpp"),
            Object(NonMatching, "rb3/Rnd/rndtex.cpp"),
            Object(NonMatching, "rb3/Rnd/rndtexblendcontroller.cpp"),
            Object(NonMatching, "rb3/Rnd/rndtexblender.cpp"),
            Object(NonMatching, "rb3/Rnd/rndtexrenderer.cpp"),
            Object(NonMatching, "rb3/Rnd/rndtext.cpp"),
            Object(NonMatching, "rb3/Rnd/rndtransformable.cpp"),
            Object(NonMatching, "rb3/Rnd/rndtransproxy.cpp"),
            Object(NonMatching, "rb3/Rnd/rndcubetex.cpp"),
            Object(NonMatching, "rb3/Rnd/rndfur.cpp"),
            Object(NonMatching, "rb3/Rnd/rndambientocclusion.cpp"),

            Object(NonMatching, "rb3/hmx/object.cpp"),
            Object(NonMatching, "rb3/app.cpp"),
            Object(NonMatching, "rb3/arkfile.cpp"),
            Object(NonMatching, "rb3/asyncfile.cpp"),
            Object(NonMatching, "rb3/asyncfilecnt.cpp"),
            Object(NonMatching, "rb3/asyncfilewii.cpp"),
            Object(Matching, "rb3/binstream.cpp"),
            Object(NonMatching, "rb3/bink.cpp"),
            Object(NonMatching, "rb3/debug.cpp"),
            Object(NonMatching, "rb3/formatstring.cpp"),

            # These functions match 100%, but won't link because the dtors aren't being merged properly
            Object(LinkIssues, "rb3/interpolators.cpp"),

            Object(NonMatching, "rb3/joypad.cpp"),
            Object(NonMatching, "rb3/netstream.cpp"),
            Object(NonMatching, "rb3/notetube.cpp"),
            Object(NonMatching, "rb3/ogg_mem.cpp"),
            Object(NonMatching, "rb3/string.cpp"),
            Object(NonMatching, "rb3/wiinetworksocket.cpp"),
            Object(NonMatching, "rb3/trainingmgr.cpp"),
            Object(NonMatching, "rb3/hxguid.cpp"),
            Object(NonMatching, "rb3/trainingpanel.cpp"),
            Object(NonMatching, "rb3/beatmap.cpp"),
            Object(NonMatching, "rb3/datetime.cpp"),

            Object(Matching, "rb3/stringtablelocks.cpp"),
            Object(Matching, "rb3/symbols/symbolset1.cpp"),
            Object(Matching, "rb3/symbols/symbolset2.cpp"),
            Object(Matching, "rb3/symbols/symbolset3.cpp"),
            Object(Matching, "rb3/symbols/symbolset4.cpp"),

            # These sinits match 100%, but won't link due to issues where the .bss labels don't pad properly
            Object(LinkIssues, "rb3/symbols/messageset1.cpp", extra_cflags=["-O4,p"]),
            Object(LinkIssues, "rb3/symbols/messageset2.cpp", extra_cflags=["-O4,p"]),
            Object(LinkIssues, "rb3/symbols/messageset3.cpp", extra_cflags=["-O4,p"]),
            Object(LinkIssues, "rb3/symbols/messageset4.cpp", extra_cflags=["-O4,p"]),

            Object(NonMatching, "rb3/dataarray.cpp"),
            Object(NonMatching, "rb3/datafunc.cpp"),
            Object(NonMatching, "rb3/datanode.cpp"),
            Object(NonMatching, "rb3/datautil.cpp"),

            Object(NonMatching, "rb3/textfile.cpp"),
            Object(NonMatching, "rb3/bytegrinder.cpp"),
            Object(NonMatching, "rb3/ugcpurchasepanel.cpp"),
            Object(NonMatching, "rb3/uistats.cpp"),
            Object(NonMatching, "rb3/uipanel.cpp"),

            Object(NonMatching, "rb3/hmx/object.cpp"),

            Object(NonMatching, "rb3/fx/fxsend.cpp"),
            Object(NonMatching, "rb3/fx/fxsendchorus.cpp"),
            Object(NonMatching, "rb3/fx/fxsendflanger.cpp"),
            Object(NonMatching, "rb3/fx/fxsendreverb.cpp"),
            Object(NonMatching, "rb3/fx/fxsenddelay.cpp"),
            Object(NonMatching, "rb3/fx/fxsenddistortion.cpp"),
            Object(NonMatching, "rb3/fx/fxsendcompress.cpp"),
            Object(NonMatching, "rb3/fx/fxsendeq.cpp"),
            Object(NonMatching, "rb3/fx/fxsendmetereffect.cpp"),
            Object(NonMatching, "rb3/fx/fxsendpitchshift.cpp"),
            Object(NonMatching, "rb3/fx/fxsendsynapse.cpp"),
            Object(NonMatching, "rb3/fx/fxsendwah.cpp"),

            Object(NonMatching, "rb3/messages/stringstrummedmsg.cpp"),
            Object(NonMatching, "rb3/messages/stringstoppedmsg.cpp"),

            Object(NonMatching, "rb3/messages/rg/rgaccelerometermsg.cpp"),
            Object(NonMatching, "rb3/messages/rg/rgconnectedaccessoriesmsg.cpp"),
            Object(NonMatching, "rb3/messages/rg/rgpitchbendmsg.cpp"),
            Object(NonMatching, "rb3/messages/rg/rgmutingmsg.cpp"),
            Object(NonMatching, "rb3/messages/rg/rgstompboxmsg.cpp"),
            Object(NonMatching, "rb3/messages/rg/rgprogramchangemsg.cpp"),
            Object(NonMatching, "rb3/messages/rg/rgswingmsg.cpp"),
            Object(NonMatching, "rb3/messages/rg/rgfretbuttondownmsg.cpp"),
            Object(NonMatching, "rb3/messages/rg/rgfretbuttonupmsg.cpp"),

            Object(NonMatching, "rb3/messages/keys/keyboardkeyreleasedmsg.cpp"),
            Object(NonMatching, "rb3/messages/keys/keyboardmodmsg.cpp"),
            Object(NonMatching, "rb3/messages/keys/keyboardexpressionpedalmsg.cpp"),
            Object(NonMatching, "rb3/messages/keys/keyboardconnectedaccessories.cpp"),
            Object(NonMatching, "rb3/messages/keys/keyboardsustainmsg.cpp"),
            Object(NonMatching, "rb3/messages/keys/keyboardstompbox.cpp"),
            Object(NonMatching, "rb3/messages/keys/keysaccelerometermsg.cpp"),
            Object(NonMatching, "rb3/messages/keys/keyboardlowhandplacementmsg.cpp"),
            Object(NonMatching, "rb3/messages/keys/keyboardhighhandplacementmsg.cpp"),

            Object(NonMatching, "rb3/overshellpanel.cpp"),
            Object(NonMatching, "rb3/chordbookpanel.cpp"),
            Object(NonMatching, "rb3/bandusermgr.cpp"),
            Object(NonMatching, "rb3/gamemicmanager.cpp"),
            Object(NonMatching, "rb3/gamemode.cpp"),
            Object(NonMatching, "rb3/gamepanel.cpp"),
            Object(NonMatching, "rb3/charactercreatorpanel.cpp"),
            Object(NonMatching, "rb3/campaignsonginfopanel.cpp"),
            Object(NonMatching, "rb3/choosecolorpanel.cpp"),
            Object(NonMatching, "rb3/closetmgr.cpp"),
            Object(NonMatching, "rb3/closetpanel.cpp"),
            Object(NonMatching, "rb3/contentdeletepanel.cpp"),
            Object(NonMatching, "rb3/msgsource.cpp"),
            Object(NonMatching, "rb3/dirunloader.cpp"),
            Object(NonMatching, "rb3/fadepanel.cpp"),
            Object(NonMatching, "rb3/freestylepanel.cpp"),
            Object(NonMatching, "rb3/songsectioncontroller.cpp"),
            Object(NonMatching, "rb3/unisonicon.cpp"),
            Object(NonMatching, "rb3/crowdaudio.cpp"),
            Object(NonMatching, "rb3/overshelldir.cpp"),

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
            Object(NonMatching, "rb3/unknown/802/unk_802960B0.cpp"),
            Object(NonMatching, "rb3/unknown/802/unk_802D4B74.cpp"),
            Object(NonMatching, "rb3/unknown/802/unk_802DDEA0.cpp"),
            Object(NonMatching, "rb3/unknown/802/unk_802E0CA0.cpp"),
            Object(NonMatching, "rb3/unknown/802/unk_802E9040.cpp"),
            Object(NonMatching, "rb3/unknown/802/unk_802F02EC.cpp"),
            Object(NonMatching, "rb3/unknown/802/unk_802F844C.cpp"),
            Object(NonMatching, "rb3/unknown/802/unk_802F98DC.cpp"),
            Object(NonMatching, "rb3/unknown/802/unk_802FA994.cpp"),
            Object(NonMatching, "rb3/unknown/802/unk_802FB548.cpp"),
            Object(NonMatching, "rb3/unknown/802/unk_802663BC.cpp"),

            Object(NonMatching, "rb3/unknown/803/unk_8030A494.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_8033C8F0.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_80324AFC.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_803431F4.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_8034C91C.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_8034C9F8.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_80354A30.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_80357E10.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_80362A50.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_8037A3D8.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_8037AD40.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_8031144C.cpp"),

            Object(NonMatching, "rb3/unknown/804/unk_80421240.cpp"),

            Object(NonMatching, "rb3/unknown/805/unk_8050FA30.cpp"),
            Object(NonMatching, "rb3/unknown/805/unk_805CE140.cpp"),
            Object(NonMatching, "rb3/unknown/805/unk_80567E84.cpp"),
            Object(NonMatching, "rb3/unknown/805/unk_8057464C.cpp"),
            Object(NonMatching, "rb3/unknown/805/unk_805CE140.cpp"),
            Object(NonMatching, "rb3/unknown/805/unk_8052A44C.cpp"),

            Object(NonMatching, "rb3/unknown/806/unk_8066E3FC.cpp"),
            Object(NonMatching, "rb3/unknown/806/unk_80660D18.cpp"),
            Object(NonMatching, "rb3/unknown/806/unk_80671DCC.cpp")
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
            Object(NonMatching, "libs/quazal/datetime.cpp"),
            Object(NonMatching, "libs/quazal/platform.cpp"),
            Object(NonMatching, "libs/quazal/profilingunit.cpp"),
            Object(Matching, "libs/quazal/qresult.cpp"),
            Object(Matching, "libs/quazal/randomnumbergenerator.cpp"),
            Object(NonMatching, "libs/quazal/refcountedobject.cpp"),
            Object(NonMatching, "libs/quazal/rootobject.cpp"),
            Object(Matching, "libs/quazal/stream.cpp"),
            Object(NonMatching, "libs/quazal/string.cpp"),

            Object(NonMatching, "libs/quazal/unknown/8001/unk_800135F0.cpp"),
            Object(NonMatching, "libs/quazal/unknown/8001/unk_80018968.cpp"),
            Object(NonMatching, "libs/quazal/unknown/8007/unk_8007BF84.cpp"),
            Object(NonMatching, "libs/quazal/unknown/8007/unk_8007B998.cpp"),
            Object(NonMatching, "libs/quazal/unknown/800A/unk_800A515C.cpp"),
        ],
    },
    {
        "lib": "json-c",
        "mw_version": "Wii/1.3",
        "cflags": cflags_c,
        "host": False,
        "objects": [
            Object(Matching, "libs/json-c/arraylist.c"),
            Object(Matching, "libs/json-c/json_object.c"),
            Object(Matching, "libs/json-c/json_tokener.c"),
            Object(Matching, "libs/json-c/linkhash.c"),
            Object(Matching, "libs/json-c/printbuf.c")
        ]
    },
    {
        "lib": "zlib",
        "mw_version": "Wii/1.3",
        "cflags": cflags_zlib,
        "host": False,
        "objects": [
            Object(Matching, "libs/zlib/adler32.c"),
            Object(Matching, "libs/zlib/crc32.c"),
            Object(Matching, "libs/zlib/deflate.c"),
            Object(Matching, "libs/zlib/trees.c"),
            Object(Matching, "libs/zlib/zutil.c"),
            Object(Matching, "libs/zlib/inflate.c"),
            Object(Matching, "libs/zlib/inftrees.c", mw_version="Wii/1.0a"),
            Object(Matching, "libs/zlib/inffast.c"),
        ]
    },
    {
        "lib": "libtomcrypt",
        "mw_version": "Wii/1.0",
        "cflags": cflags_zlib,
        "host": False,
        "objects": [
            Object(NonMatching, "libs/libtomcrypt/aes.c"),
            Object(Matching, "libs/libtomcrypt/crypt.c"),
            Object(NonMatching, "libs/libtomcrypt/ctr.c")
        ],
    },
    {
        "lib": "speex",
        "mw_version": "Wii/1.3",
        "cflags": cflags_zlib,
        "host": False,
        "objects": [
            Object(Matching, "libs/speex/libspeex/bits.c"),
            Object(Matching, "libs/speex/libspeex/cb_search.c"),
            Object(Matching, "libs/speex/libspeex/filters.c"),
            Object(Matching, "libs/speex/libspeex/lpc.c"),
            Object(Matching, "libs/speex/libspeex/lsp.c"),
            Object(Matching, "libs/speex/libspeex/ltp.c"),
            Object(NonMatching, "libs/speex/libspeex/nb_celp.c"),
            Object(Matching, "libs/speex/libspeex/quant_lsp.c"),
            Object(Matching, "libs/speex/libspeex/speex.c"),
            Object(Matching, "libs/speex/libspeex/speex_callbacks.c"),
            Object(NonMatching, "libs/speex/libspeex/vbr.c"),
            Object(Matching, "libs/speex/libspeex/vq.c")
        ]
    },
    {
        "lib": "libogg",
        "mw_version": "Wii/1.3",
        "cflags": cflags_c,
        "host": False,
        "objects": [
            Object(Matching, "libs/libogg/src/bitwise.c"),
            Object(Matching, "libs/libogg/src/framing.c")
        ],
    },
    # TODO: this object is actually part of RB3's dta parser
    # should move this to rb3 itself
    {
        "lib": "flex",
        "mw_version": "Wii/1.3",
        "cflags": cflags_c,
        "host": False,
        "objects": [
            Object(NonMatching, "rb3/yy.c")
        ],
    },
    {
        "lib": "vorbis",
        "mw_version": "Wii/1.3",
        "cflags": cflags_c,
        "host": False,
        "objects": [
            Object(Matching, "libs/vorbis/bitrate.c"),
            Object(Matching, "libs/vorbis/block.c"),
            Object(NonMatching, "libs/vorbis/codebook.c"),
            Object(Matching, "libs/vorbis/envelope.c"),
            Object(NonMatching, "libs/vorbis/floor0.c"),
            Object(NonMatching, "libs/vorbis/floor1.c"),
            Object(Matching, "libs/vorbis/info.c"),
            Object(Matching, "libs/vorbis/lsp.c"),
            Object(NonMatching, "libs/vorbis/mapping0.c"),
            Object(NonMatching, "libs/vorbis/mdct.c"),
            Object(NonMatching, "libs/vorbis/psy.c"),
            Object(NonMatching, "libs/vorbis/res0.c"),
            Object(NonMatching, "libs/vorbis/sharedbook.c"),
            Object(Matching, "libs/vorbis/smallft.c"),
            Object(NonMatching, "libs/vorbis/window.c")
        ],
    },
    {
        "lib": "bt",
        "mw_version": "Wii/1.3",
        "cflags": cflags_bt,
        "host": False,
        "objects": [
            Object(NonMatching, "libs/bt/stack/l2cap/l2c_utils.c"),
            Object(NonMatching, "libs/bt/stack/l2cap/l2c_main.c"),
            Object(NonMatching, "libs/bt/stack/l2cap/l2c_link.c"),
            Object(NonMatching, "libs/bt/stack/l2cap/l2c_csm.c"),
            Object(NonMatching, "libs/bt/stack/l2cap/l2c_api.c"),
            Object(NonMatching, "libs/bt/stack/hid/hidh_conn.c"),
            Object(NonMatching, "libs/bt/stack/hid/hidh_api.c"),
            Object(NonMatching, "libs/bt/stack/hcic/hcicmds.c"),
            Object(NonMatching, "libs/bt/stack/btu/btu_hcif.c"),
            Object(NonMatching, "libs/bt/stack/rfcomm/port_api.c")
        ]
    },
    # anything below this line does not need to be decompiled
    # you can attempt to match these if you want though
    {
        "lib": "MSL_C",
        "mw_version": "Wii/1.3",
        "cflags": cflags_runtime,
        "host": False,
        "objects": [
            Object(Matching, "sdk/MSL_C/text_1.c"),
            Object(Matching, "sdk/MSL_C/sdata_1.c"),
        ]
    },
    {
        "lib": "Runtime.PPCEABI.H",
        "mw_version": "Wii/1.3",
        "cflags": cflags_runtime,
        "host": False,
        "objects": [
            Object(Matching, "sdk/Runtime/global_destructor_chain.c"),
            Object(Matching, "sdk/Runtime/__init_cpp_exceptions.cpp"),
        ],
    },
    {
        "lib": "std_native",
        "mw_version": "Wii/1.3",
        "cflags": cflags_runtime,
        "host": False,
        "objects": [
            Object(Matching, "sdk/MSL_C++/src/new.cpp"),
        ]
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
