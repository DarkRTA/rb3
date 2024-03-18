#ifndef RNDOBJ_HIRESSCREEN_H
#define RNDOBJ_HIRESSCREEN_H
#include "utl/Str.h"

class HiResScreen {
public:

    class BmpCache {
    public:
        BmpCache(unsigned int, unsigned int);
        virtual ~BmpCache();

        void DeleteCache();

        String* mFileNames;
        unsigned char* mBuffer;
        unsigned int mPixelsPerRow;
        unsigned int mRowsPerCacheLine;
        unsigned int mTotalNumCacheLines;
        unsigned int mTotalRows;
        unsigned int mCurrLoadedIndex;
        unsigned int mByteSize;
        unsigned int mDirtyStart;
        unsigned int mDirtyEnd;
    };

    HiResScreen();
    virtual ~HiResScreen();
    bool mActive;
    int mTiling;
    String mFileBase;
    unsigned int mAccumWidth;
    unsigned int mAccumHeight;
    int mCurrTile;
    bool mOverride;
    bool mEvenOddDisabled;
    bool mShrinkToSafe;
    int mCache;
};

extern HiResScreen* TheHighResScreen;

#endif
