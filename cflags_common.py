cflags_includes = [
    # STLport requires that it comes first in the include path list
    "-i src/system/stlport",

    "-i src/sdk",
    "-i src/sdk/RVL_SDK",

    # Libraries
    "-i src/libs",

    # Project source
    "-i src",
    "-i src/system",
    "-i src/rb3",
]
