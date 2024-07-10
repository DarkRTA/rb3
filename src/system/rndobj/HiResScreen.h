#ifndef RNDOBJ_HIRESSCREEN_H
#define RNDOBJ_HIRESSCREEN_H
#include "math/Geo.h"
#include "rndobj/Cam.h"
#include "utl/Str.h"

class HiResScreen {
public:

    class BmpCache {
    public:
        BmpCache(unsigned int, unsigned int);
        virtual ~BmpCache();

        void DeleteCache();
        void GetLoadedRange(uint&, uint&) const;
        void LoadCache(uint);
        void FlushCache();

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
    void TakeShot(const char*, int);
    void GetBorderForTile(int, int, int&, int&, int&, int&) const;
    void Accumulate();
    void Finish();
    int GetPaddingX() const; int GetPaddingY() const;
    Hmx::Rect CurrentTileRect(const Hmx::Rect&, Hmx::Rect&, Hmx::Rect&) const;
    Hmx::Rect ScreenRect(const RndCam*, const Hmx::Rect&) const; Hmx::Rect ScreenRect() const;
    void InvScreenRect() const;
    bool IsActive() const { return mActive; }

    bool mActive; // 0x4
    int mTiling; // 0x8
    String mFileBase; // 0xC
    unsigned int mAccumWidth; // 0x18
    unsigned int mAccumHeight; // 0x1C
    int mCurrTile; // 0x20
    bool mOverride; // 0x24
    bool mEvenOddDisabled; // 0x25
    bool mShrinkToSafe; // 0x26
    bool mConsoleShowing; // 0x27
    BmpCache* mCache; // 0x28
};

extern HiResScreen* TheHiResScreen;

#endif
