cflags_includes = [
    # C/C++ stdlib
    # STLport requires that it comes first in the include path list
    "-i src/system/stlport",
    "-i src/sdk/PowerPC_EABI_Support/MSL/MSL_C",
    # Not included since it's all wrapped by stlport
    # "-i src/sdk/PowerPC_EABI_Support/MSL/MSL_C++",

    "-i src/system/speex/include",

    "-i src/sdk",
    "-i src/sdk/RVL_SDK",

    # Libraries
    "-i src/libs",

    # Project source
    "-i src",
    "-i src/network",
    "-i src/system",
    "-i src/band3",
]
