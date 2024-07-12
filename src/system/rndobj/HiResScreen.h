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

        String* mFileNames; // 0x4
        unsigned char* mBuffer; // 0x8
        unsigned int mPixelsPerRow; // 0xc
        unsigned int mRowsPerCacheLine; // 0x10
        unsigned int mTotalNumCacheLines; // 0x14
        unsigned int mTotalRows; // 0x18
        unsigned int mCurrLoadedIndex; // 0x1c
        unsigned int mByteSize; // 0x20
        unsigned int mDirtyStart; // 0x24
        unsigned int mDirtyEnd; // 0x28
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
