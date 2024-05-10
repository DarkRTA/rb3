#ifndef RNDOBJ_SIVIDEO_H
#define RNDOBJ_SIVIDEO_H
#include "utl/BinStream.h"

class SIVideo {
public:
    void Reset();
    void Load(BinStream&, bool);
    int Bpp() const;
    int Bpp() { return mBpp == 8 ? 4 : 8;}
    int FrameSize() const;
    char* Frame(int);

    unsigned int mMagic;
    unsigned int mWidth;
    unsigned int mHeight;
    unsigned int mBpp;
    char* mData;
};

#endif
