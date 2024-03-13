#ifndef RNDOBJ_SIVIDEO_H
#define RNDOBJ_SIVIDEO_H
#include "utl/BinStream.h"

class SIVideo {
public:
    void Reset();
    void Load(BinStream&, bool);
    int Bpp() const;
    int FrameSize() const;
    char* Frame(int);

    unsigned int mWidth;
    unsigned int mHeight;
    unsigned int mNumFrames;
    unsigned int mOrder;
    char* mData;
};

#endif
