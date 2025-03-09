#ifndef RNDOBJ_SIVIDEO_H
#define RNDOBJ_SIVIDEO_H
#include "utl/BinStream.h"

class SIVideo {
public:
    SIVideo() : mData(nullptr) { Reset(); }
    ~SIVideo() { Reset(); }
    void Reset();
    void Load(BinStream &, bool);
    int Bpp() const;
    int Bpp() { return mBpp == 8 ? 4 : 8; }
    int FrameSize() const;
    char *Frame(int);

    unsigned int mMagic; // 0x0
    unsigned int mWidth; // 0x4
    unsigned int mHeight; // 0x8
    unsigned int mBpp; // 0xc
    char *mData; // 0x10
};

#endif
