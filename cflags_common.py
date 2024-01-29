cflags_includes = [
    "-i src/libs/stlport/stlport",
    "-i src/sdk/MSL_C/MSL_Common",
    "-i src/sdk/MSL_C/MSL_Common_Embedded",
    "-i src/sdk/MSL_C/MSL_Common_Embedded/Math",
    "-i src/sdk/MetroTRK",
    # "-i src/tainted/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Include",
    "-i src/libs/bt/gki/common",
    "-i src/libs/bt/bta/include",
    "-i src/libs/bt/utils/include",
    "-i src/libs/bt/stack/l2cap",
    "-i src/libs/bt/stack/btm",
    "-i src/libs/bt/include",
    "-i src/libs/bt/stack/include",
    "-i src/libs/libogg/include",
    "-i src/libs/speex/include",
    "-i src/libs/speex",
    "-i src/sdk/RVL_SDK",
    "-i src/sdk/MSL_C++",
    "-i src/rb3",
    "-i src/rb3/data",
    "-i src/rb3/world",
    "-i src/libs",
    "-i src",
]

cflags_defines = [
    "-d NDEBUG",
]
