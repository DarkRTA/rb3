#ifndef UTL_LOADER_H
#define UTL_LOADER_H
#include "FilePath.h"
#include "System.h"

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
    char list1[8];
    char list2[8];
    float mPeriod;
    char list3[8];
    char mTimer[0x30];
    int unk50;
    int unk54;
};

#endif
