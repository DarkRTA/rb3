#ifndef UTL_LOADER_H
#define UTL_LOADER_H
#include "utl/FilePath.h"

enum LoaderPos {
    kLoadFront = 0,
    kLoadBack = 1,
    kLoadFrontStayBack = 2,
    kLoadStayBack = 3,
};

class Loader {
public:
    LoaderPos mPos;
    FilePath mFile;
};

#endif
