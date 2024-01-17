cflags_includes = [
    "-i src/stlport/stlport",
    "-i src/PowerPC_EABI_Support/MSL_C/MSL_Common",
    "-i src/PowerPC_EABI_Support/MSL_C/MSL_Common_Embedded",
    "-i src/PowerPC_EABI_Support/MSL_C/MSL_Common_Embedded/Math",
    "-i src/PowerPC_EABI_Support/MetroTRK",
    # "-i src/tainted/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Include",
    "-i src/bt/gki/common",
    "-i src/bt/bta/include",
    "-i src/bt/utils/include",
    "-i src/bt/stack/l2cap",
    "-i src/bt/stack/btm",
    "-i src/bt/include",
    "-i src/bt/stack/include",
    "-i src/libogg/include",
    "-i src/speex/include",
    "-i src/speex",
    "-i src/RVL_SDK",
    "-i src/std_native",
    "-i src/rb3",
    "-i src",
]

cflags_defines = [
    "-d NDEBUG",
]
