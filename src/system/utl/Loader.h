#ifndef UTL_LOADER_H
#define UTL_LOADER_H
#include "utl/FilePath.h"
#include "os/System.h"
// #include <list>

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

class LoadMgr {
public:
    char mLoaders[8];
    Platform mPlatform;
    bool mCacheMode;
    bool mEditMode;

    // // total size: 0x60
    // class list mLoaders; // offset 0x0, size 0x8
    // enum Platform mPlatform; // offset 0x8, size 0x4
    // unsigned char mCacheMode; // offset 0xC, size 0x1
    // unsigned char mEditMode; // offset 0xD, size 0x1
    // class list mFactories; // offset 0x10, size 0x8
    // float mPeriod; // offset 0x18, size 0x4
    // class list mLoading; // offset 0x1C, size 0x8
    // class Timer mTimer; // offset 0x28, size 0x38
};

#endif
