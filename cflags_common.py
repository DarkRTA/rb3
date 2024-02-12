cflags_includes = [
    # STLport requires that it comes first in the include path list
    "-i src/libs/stlport/stlport",

    # SDK
    "-i src/sdk",
    "-i src/sdk/RVL_SDK",
    # "-i src/sdk/MSL_C++", # Handled by STLport

    # Libraries
    "-i src/libs",
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

    # Project source
    "-i src",
    "-i src/system",
    "-i src/rb3",
    "-i src/rb3/data",
    "-i src/rb3/mgrs",
    "-i src/rb3/world",
]

cflags_defines = [
    "-d NDEBUG",
]
