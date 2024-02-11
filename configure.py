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
            # managers folder
            Object(NonMatching, "rb3/mgrs/tambourinemanager.cpp"),
            Object(NonMatching, "rb3/mgrs/gamemicmanager.cpp"),
            Object(NonMatching, "rb3/mgrs/trainingmgr.cpp"),
            Object(NonMatching, "rb3/mgrs/bandusermgr.cpp"),
            Object(NonMatching, "rb3/mgrs/closetmgr.cpp"),
            Object(NonMatching, "rb3/mgrs/profilemgr.cpp"),
            Object(NonMatching, "rb3/mgrs/inputmgr.cpp"),
            Object(NonMatching, "rb3/mgrs/interstitialmgr.cpp"),
            Object(NonMatching, "rb3/mgrs/lessonmgr.cpp"),
            Object(NonMatching, "rb3/mgrs/usermgr.cpp"),
            Object(NonMatching, "rb3/mgrs/modifiermgr.cpp"),
            Object(NonMatching, "rb3/mgrs/sessionmgr.cpp"),
            Object(NonMatching, "rb3/mgrs/songstatusmgr.cpp"),
            Object(NonMatching, "rb3/mgrs/bandmachinemgr.cpp"),
            Object(NonMatching, "rb3/mgrs/bandsongmgr.cpp"),
            Object(NonMatching, "rb3/mgrs/saveloadmanager.cpp"),

            # messages folder
            Object(Matching, "rb3/messages/stringstrummedmsg.cpp"),
            Object(NonMatching, "rb3/messages/stringstoppedmsg.cpp"),
            Object(Matching, "rb3/messages/rg_messages.cpp"),
            Object(Matching, "rb3/messages/key_messages.cpp"),

            # panels folder
            Object(NonMatching, "rb3/panels/trainingpanel.cpp"),
            Object(NonMatching, "rb3/panels/ugcpurchasepanel.cpp"),
            Object(NonMatching, "rb3/panels/overshellpanel.cpp"),
            Object(NonMatching, "rb3/panels/chordbookpanel.cpp"),
            Object(NonMatching, "rb3/panels/gamepanel.cpp"),
            Object(NonMatching, "rb3/panels/charactercreatorpanel.cpp"),
            Object(NonMatching, "rb3/panels/campaignsonginfopanel.cpp"),
            Object(NonMatching, "rb3/panels/choosecolorpanel.cpp"),
            Object(NonMatching, "rb3/panels/retryaudiopanel.cpp"),
            Object(NonMatching, "rb3/panels/saveloadstatuspanel.cpp"),
            Object(NonMatching, "rb3/panels/selectdifficultypanel.cpp"),
            Object(NonMatching, "rb3/panels/parentalcontrolpanel.cpp"),
            Object(NonMatching, "rb3/panels/passivemessagespanel.cpp"),
            Object(NonMatching, "rb3/panels/closetpanel.cpp"),
            Object(NonMatching, "rb3/panels/contentdeletepanel.cpp"),
            Object(NonMatching, "rb3/panels/fadepanel.cpp"),
            Object(NonMatching, "rb3/panels/freestylepanel.cpp"),
            Object(NonMatching, "rb3/panels/editsetlistpanel.cpp"),
            Object(NonMatching, "rb3/panels/eventdialogpanel.cpp"),
            Object(NonMatching, "rb3/panels/customizepanel.cpp"),
            Object(NonMatching, "rb3/panels/gametimepanel.cpp"),
            Object(NonMatching, "rb3/panels/interstitialpanel.cpp"),
            Object(NonMatching, "rb3/panels/joininvitepanel.cpp"),
            Object(NonMatching, "rb3/panels/metapanel.cpp"),
            Object(NonMatching, "rb3/panels/trainerpanel.cpp"),
            Object(NonMatching, "rb3/panels/heldbuttonpanel.cpp"),
            Object(NonMatching, "rb3/panels/preloadpanel.cpp"),
            Object(NonMatching, "rb3/panels/multiselectlistpanel.cpp"),
            Object(NonMatching, "rb3/panels/tokenredemptionpanel.cpp"),
            Object(NonMatching, "rb3/panels/texloadpanel.cpp"),
            Object(NonMatching, "rb3/panels/setlistmergepanel.cpp"),
            Object(NonMatching, "rb3/panels/storerootpanel.cpp"),
            Object(NonMatching, "rb3/panels/storemenupanel.cpp"),
            Object(NonMatching, "rb3/panels/storemainpanel.cpp"),
            Object(NonMatching, "rb3/panels/storeinfopanel.cpp"),
            Object(NonMatching, "rb3/panels/bandpreloadpanel.cpp"),
            Object(NonMatching, "rb3/panels/managebandpanel.cpp"),
            Object(NonMatching, "rb3/panels/mainhubpanel.cpp"),
            Object(NonMatching, "rb3/panels/calibrationpanel.cpp"),
            Object(NonMatching, "rb3/panels/calibrationwelcomepanel.cpp"),
            Object(NonMatching, "rb3/panels/campaigncareerleaderboardpanel.cpp"),
            Object(NonMatching, "rb3/panels/campaigngoalsleaderboardchoicepanel.cpp"),
            Object(NonMatching, "rb3/panels/voiceoverpanel.cpp"),
            Object(NonMatching, "rb3/panels/storeartloaderpanel.cpp"),
            Object(NonMatching, "rb3/panels/bandstorepanel.cpp"),
            Object(NonMatching, "rb3/panels/bandstoreuipanel.cpp"),
            Object(NonMatching, "rb3/panels/storepanel.cpp"),
            Object(NonMatching, "rb3/panels/practicepanel.cpp"),

            # providers folder
            Object(NonMatching, "rb3/providers/currentoutfitprovider.cpp"),
            Object(NonMatching, "rb3/providers/cymbalselectionprovider.cpp"),
            Object(NonMatching, "rb3/providers/eyebrowsprovider.cpp"),
            Object(NonMatching, "rb3/providers/facehairprovider.cpp"),
            Object(NonMatching, "rb3/providers/facetypeprovider.cpp"),
            Object(NonMatching, "rb3/providers/setlistscoresprovider.cpp"),
            Object(NonMatching, "rb3/providers/leaderboardshortcutprovider.cpp"),
            Object(NonMatching, "rb3/providers/instrumentfinishprovider.cpp"),
            Object(NonMatching, "rb3/providers/lessonprovider.cpp"),
            Object(NonMatching, "rb3/providers/sessionusersprovider.cpp"),
            Object(NonMatching, "rb3/providers/trainerprovider.cpp"),
            Object(NonMatching, "rb3/providers/storeofferprovider.cpp"),
            Object(NonMatching, "rb3/providers/storemenuprovider.cpp"),
            Object(NonMatching, "rb3/providers/standinprovider.cpp"),
            Object(NonMatching, "rb3/providers/outfitprovider.cpp"),
            Object(NonMatching, "rb3/providers/makeupprovider.cpp"),
            Object(NonMatching, "rb3/providers/mainhubmessageprovider.cpp"),
            Object(NonMatching, "rb3/providers/calibrationmodesprovider.cpp"),
            Object(NonMatching, "rb3/providers/practicesectionprovider.cpp"),

            # Rnd folder
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
            Object(NonMatching, "rb3/Rnd/rndset.cpp"),
            Object(NonMatching, "rb3/Rnd/rndambientocclusion.cpp"),
            Object(NonMatching, "rb3/Rnd/rndconsole.cpp"),
            Object(Matching, "rb3/Rnd/dofproc.cpp"),
            Object(Matching, "rb3/Rnd/shaderoptions.cpp"),

            # Wii-specific Rnd stuff
            Object(NonMatching, "rb3/Rnd/wii/wiirnd.cpp"),

            # stubs folder
            Object(Matching, "rb3/stubs/stubone.cpp"),
            Object(Matching, "rb3/stubs/stubonef.cpp"),
            Object(Matching, "rb3/stubs/stubzerof.cpp"),

            # symbols folder (for all those chonky global symbol and message sets)
            Object(Matching, "rb3/symbols/symbolset1.cpp"),
            Object(Matching, "rb3/symbols/symbolset2.cpp"),
            Object(Matching, "rb3/symbols/symbolset3.cpp"),
            Object(Matching, "rb3/symbols/symbolset4.cpp"),
            # These sinits match 100%, but won't link due to issues where the .bss labels don't pad properly
            Object(LinkIssues, "rb3/symbols/messageset1.cpp", extra_cflags=["-O4,p"]),
            Object(LinkIssues, "rb3/symbols/messageset2.cpp", extra_cflags=["-O4,p"]),
            Object(LinkIssues, "rb3/symbols/messageset3.cpp", extra_cflags=["-O4,p"]),
            Object(LinkIssues, "rb3/symbols/messageset4.cpp", extra_cflags=["-O4,p"]),

            # ui folder
            Object(NonMatching, "rb3/ui/uievent.cpp"),
            Object(NonMatching, "rb3/ui/uistats.cpp"),

            # miscellaneous loose files
            Object(NonMatching, "rb3/app.cpp"),
            Object(NonMatching, "rb3/fixedsizesaveable.cpp"),
            Object(NonMatching, "rb3/fixedsizesaveablestream.cpp"),
            Object(NonMatching, "rb3/musiclibrary.cpp"),
            Object(NonMatching, "rb3/dynamictex.cpp"),
            Object(NonMatching, "rb3/storesongsortnode.cpp"),
            Object(NonMatching, "rb3/bandprofile.cpp"),
            Object(NonMatching, "rb3/bandstoreoffer.cpp"),
            Object(NonMatching, "rb3/bandnetgamedata.cpp"),
            Object(NonMatching, "rb3/campaignlevel.cpp"),
            Object(NonMatching, "rb3/campaigngoalsleaderboard.cpp"),
            Object(NonMatching, "rb3/campaign.cpp"),
            Object(NonMatching, "rb3/playercampaigngoalleaderboard.cpp"),
            Object(NonMatching, "rb3/wiicommercemgr.cpp"),
            Object(NonMatching, "rb3/chordshapegenerator.cpp"),
            Object(NonMatching, "rb3/colorpalette.cpp"),
            Object(NonMatching, "rb3/player.cpp"),
            Object(NonMatching, "rb3/performer.cpp"),
            Object(NonMatching, "rb3/game.cpp"),
            Object(NonMatching, "rb3/storeoffer.cpp"),
            Object(NonMatching, "rb3/labelnumberticker.cpp"),
            Object(NonMatching, "rb3/labelshrinkwrapper.cpp"),
            Object(NonMatching, "rb3/netstream.cpp"),
            Object(NonMatching, "rb3/notetube.cpp"),
            Object(NonMatching, "rb3/wiinetworksocket.cpp"),
            Object(Matching, "rb3/stringtablelocks.cpp"),
            Object(Matching, "rb3/file_ops.cpp"),
            Object(Matching, "rb3/jsonobjects.cpp"),
            Object(Matching, "rb3/main.cpp"),

            # should link, but having issues with the ordering of the autogenned inherited methods
            Object(LinkIssues, "rb3/gamemode.cpp"),

            Object(NonMatching, "rb3/msgsource.cpp"),
            Object(NonMatching, "rb3/dirunloader.cpp"),
            Object(NonMatching, "rb3/songsectioncontroller.cpp"),
            Object(NonMatching, "rb3/unisonicon.cpp"),
            Object(NonMatching, "rb3/crowdmetericon.cpp"),
            Object(NonMatching, "rb3/crowdaudio.cpp"),
            Object(NonMatching, "rb3/overshelldir.cpp"),
            Object(NonMatching, "rb3/trackpaneldir.cpp"),
            Object(NonMatching, "rb3/midiparser.cpp"),
            Object(NonMatching, "rb3/objectdir.cpp"),
            Object(NonMatching, "rb3/micinputarrow.cpp"),
            Object(NonMatching, "rb3/minileaderboarddisplay.cpp"),
            Object(NonMatching, "rb3/streakmeter.cpp"),
            Object(NonMatching, "rb3/overdrivemeter.cpp"),
            Object(NonMatching, "rb3/gemtrackdir.cpp"),
            Object(NonMatching, "rb3/tasks.cpp"),
            Object(NonMatching, "rb3/criticaluserlistener.cpp"),
            Object(NonMatching, "rb3/gameplayoptions.cpp"),
            Object(NonMatching, "rb3/instarank.cpp"),
            Object(NonMatching, "rb3/leaderboard.cpp"),
            Object(NonMatching, "rb3/vocalplayer.cpp"),
            Object(NonMatching, "rb3/synchronizationevent.cpp"),
            Object(NonMatching, "rb3/virtualkeyboard.cpp"),
            Object(NonMatching, "rb3/profile.cpp"),
            Object(NonMatching, "rb3/metaperformer.cpp"),
            Object(NonMatching, "rb3/bandui.cpp"),
            Object(NonMatching, "rb3/bandmatchmaker.cpp"),
            Object(NonMatching, "rb3/matchmaker.cpp"),

            # unknowns
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
            Object(NonMatching, "rb3/unknown/801/unk_801FCC20.cpp"),

            Object(NonMatching, "rb3/unknown/802/unk_80252B98.cpp"),
            Object(NonMatching, "rb3/unknown/802/unk_802D4B74.cpp"),
            Object(NonMatching, "rb3/unknown/802/unk_802E0CA0.cpp"),
            Object(NonMatching, "rb3/unknown/802/unk_802E9040.cpp"),
            Object(NonMatching, "rb3/unknown/802/unk_802F02EC.cpp"),
            Object(NonMatching, "rb3/unknown/802/unk_802F844C.cpp"),
            Object(NonMatching, "rb3/unknown/802/unk_802F98DC.cpp"),
            Object(NonMatching, "rb3/unknown/802/unk_802FA994.cpp"),
            Object(NonMatching, "rb3/unknown/802/unk_802FB548.cpp"),
            Object(NonMatching, "rb3/unknown/802/unk_802663BC.cpp"),
            Object(NonMatching, "rb3/unknown/802/unk_802DDEA0.cpp"),
            Object(NonMatching, "rb3/unknown/802/unk_8022CD04.cpp"),
            Object(NonMatching, "rb3/unknown/802/unk_8028974C.cpp"),

            Object(NonMatching, "rb3/unknown/803/unk_8030A494.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_8033C8F0.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_803431F4.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_8034C91C.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_8034C9F8.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_80354A30.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_80357E10.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_8037A3D8.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_8037AD40.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_8030F4F0.cpp"),
            Object(NonMatching, "rb3/unknown/803/unk_8034DE50.cpp"),

            Object(NonMatching, "rb3/unknown/804/unk_80421240.cpp"),

            Object(NonMatching, "rb3/unknown/805/unk_8050FA30.cpp"),
            Object(NonMatching, "rb3/unknown/805/unk_805CE140.cpp"),
            Object(NonMatching, "rb3/unknown/805/unk_80567E84.cpp"),
            Object(NonMatching, "rb3/unknown/805/unk_8057464C.cpp"),
            Object(NonMatching, "rb3/unknown/805/unk_805CE140.cpp"),
            Object(NonMatching, "rb3/unknown/805/unk_8052A44C.cpp"),
            Object(NonMatching, "rb3/unknown/805/unk_80510944.cpp"),

            Object(NonMatching, "rb3/unknown/806/unk_80660D18.cpp"),
            Object(NonMatching, "rb3/unknown/806/unk_80671DCC.cpp")
        ],
    },
    {
        "lib": "system",
        "mw_version": "Wii/1.3",
        "cflags": cflags_rb3,
        "host": False,
        "objects": [       
            Object(NonMatching, "system/math/strips/Adjacency.cpp"),
            Object(Matching, "system/math/strips/CustomArray.cpp"),
            Object(NonMatching, "system/math/strips/RevisitedRadix.cpp"),
            Object(NonMatching, "system/math/strips/Striper.cpp"),
            Object(NonMatching, "system/math/Decibels.cpp"),
            Object(NonMatching, "system/math/FileChecksum.cpp"),
            # These functions match 100%, but won't link because the dtors aren't being merged properly
            Object(LinkIssues, "system/math/Interp.cpp"),
            Object(Matching, "system/math/Primes.cpp"),
            Object(Matching, "system/math/Rand.cpp"),
            Object(Matching, "system/math/Rand2.cpp"),
            Object(NonMatching, "system/math/Rot.cpp"),
            Object(NonMatching, "system/math/StreamChecksum.cpp"),
            Object(Matching, "system/math/Trig.cpp"),

            Object(NonMatching, "system/obj/DataArray.cpp"),
            Object(NonMatching, "system/obj/DataFile.cpp"),
            Object(NonMatching, "system/obj/DataFlex.c"),
            Object(NonMatching, "system/obj/DataFunc.cpp"),
            Object(NonMatching, "system/obj/DataNode.cpp"),
            Object(NonMatching, "system/obj/DataUtl.cpp"),
            Object(NonMatching, "system/obj/Object.cpp", mw_version="Wii/1.0a"),
            # should match, but link issues due to the weak symbols in the header, as well as the mystery function in the middle of the split
            Object(LinkIssues, "system/obj/PropSync.cpp", mw_version="Wii/1.0a"),
            # should match, but link issues due to...the superclasses just before the RTTI? idk
            Object(LinkIssues, "system/obj/TextFile.cpp"),
            Object(NonMatching, "system/obj/TypeProps.cpp"),
            Object(NonMatching, "system/obj/Utl.cpp"),
            
            Object(NonMatching, "system/os/AppChild.cpp"),
            Object(NonMatching, "system/os/Archive.cpp"),
            Object(NonMatching, "system/os/ArkFile.cpp"),
            Object(NonMatching, "system/os/AsyncFile.cpp"),
            Object(NonMatching, "system/os/AsyncFile_Wii.cpp"),
            Object(NonMatching, "system/os/AsyncFileCNT.cpp"),
            Object(NonMatching, "system/os/DateTime.cpp"),
            Object(NonMatching, "system/os/Debug.cpp"),
            Object(NonMatching, "system/os/Joypad.cpp"),
            Object(NonMatching, "system/os/System.cpp"),
            Object(NonMatching, "system/os/User.cpp"),

            Object(NonMatching, "system/synth/oggvorbis/VorbisMem.cpp"),
            Object(NonMatching, "system/synth/ADSR.cpp"),
            Object(NonMatching, "system/synth/BinkClip.cpp"),
            Object(NonMatching, "system/synth/BinkReader.cpp"),
            Object(NonMatching, "system/synth/ByteGrinder.cpp"),
            Object(NonMatching, "system/synth/Emitter.cpp"),
            Object(NonMatching, "system/synth/Faders.cpp"),
            Object(NonMatching, "system/synth/FxSend.cpp"),
            Object(NonMatching, "system/synth/FxSendChorus.cpp"),
            Object(NonMatching, "system/synth/FxSendFlanger.cpp"),
            Object(NonMatching, "system/synth/FxSendReverb.cpp"),
            Object(NonMatching, "system/synth/FxSendDelay.cpp"),
            Object(NonMatching, "system/synth/FxSendDistortion.cpp"),
            Object(NonMatching, "system/synth/FxSendCompress.cpp"),
            Object(NonMatching, "system/synth/FxSendEQ.cpp"),
            Object(NonMatching, "system/synth/FxSendMeterEffect.cpp"),
            Object(NonMatching, "system/synth/FxSendPitchShift.cpp"),
            Object(NonMatching, "system/synth/FxSendSynapse.cpp"),
            Object(NonMatching, "system/synth/FxSendWah.cpp"),
            Object(NonMatching, "system/synth/MetaMusic.cpp"),

            Object(NonMatching, "system/ui/PanelDir.cpp"),
            Object(NonMatching, "system/ui/Screenshot.cpp"),
            Object(NonMatching, "system/ui/UI.cpp"),
            Object(NonMatching, "system/ui/UIButton.cpp"),
            Object(NonMatching, "system/ui/UIColor.cpp"),
            Object(NonMatching, "system/ui/UIComponent.cpp"),
            Object(NonMatching, "system/ui/UIFontImporter.cpp"),
            Object(NonMatching, "system/ui/UILabel.cpp"),
            Object(NonMatching, "system/ui/UILabelDir.cpp"),
            Object(NonMatching, "system/ui/UIList.cpp"),
            Object(NonMatching, "system/ui/UIListArrow.cpp"),
            Object(NonMatching, "system/ui/UIListCustom.cpp"),
            Object(NonMatching, "system/ui/UIListDir.cpp"),
            Object(NonMatching, "system/ui/UIListHighlight.cpp"),
            Object(NonMatching, "system/ui/UIListLabel.cpp"),
            Object(NonMatching, "system/ui/UIListMesh.cpp"),
            Object(NonMatching, "system/ui/UIListWidget.cpp"),
            Object(NonMatching, "system/ui/UIPanel.cpp"),
            Object(NonMatching, "system/ui/UIPicture.cpp"),

            Object(NonMatching, "system/utl/BeatMap.cpp"),
            Object(NonMatching, "system/utl/BinkIntegration.cpp"),
            Object(Matching, "system/utl/BinStream.cpp"),
            Object(NonMatching, "system/utl/BufStream.cpp"),
            Object(NonMatching, "system/utl/BufStreamNAND.cpp"),
            Object(NonMatching, "system/utl/Cache.cpp"),
            Object(NonMatching, "system/utl/Cache_Wii.cpp"),
            Object(NonMatching, "system/utl/CacheMgr.cpp"),
            Object(NonMatching, "system/utl/CacheMgr_Wii.cpp"),
            Object(NonMatching, "system/utl/EncryptXTEA.cpp"),
            Object(NonMatching, "system/utl/FilePath.cpp"),
            Object(NonMatching, "system/utl/FileStream.cpp"),
            Object(NonMatching, "system/utl/HxGuid.cpp"),
            Object(Matching, "system/utl/IntPacker.cpp"),
            Object(NonMatching, "system/utl/Loader.cpp"),
            Object(NonMatching, "system/utl/Locale.cpp"),
            Object(Matching, "system/utl/LocaleOrdinal.cpp"),
            Object(NonMatching, "system/utl/LogFile.cpp"),
            Object(NonMatching, "system/utl/MakeString.cpp"),
            Object(NonMatching, "system/utl/MemStream.cpp"),
            Object(NonMatching, "system/utl/MultiTempoTempoMap.cpp"),
            Object(Matching, "system/utl/Option.cpp"),
            # when this gets matched, merge it with Option.cpp - that's how HMX did it
            Object(NonMatching, "system/utl/OptionTheRestLol.cpp"),
            Object(NonMatching, "system/utl/Str.cpp"),
            Object(NonMatching, "system/utl/StringTable.cpp"),
            Object(NonMatching, "system/utl/Symbol.cpp"),
            Object(Matching, "system/utl/TempoMap.cpp"),
            Object(Matching, "system/utl/TextFileStream.cpp"),
            Object(Matching, "system/utl/TextStream.cpp"),
            Object(NonMatching, "system/utl/UTF8.cpp"),
            
            Object(NonMatching, "system/world/Crowd.cpp"),
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
