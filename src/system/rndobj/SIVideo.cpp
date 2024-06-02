#include "rndobj/SIVideo.h"
#include "decomp.h"
#include "os/Debug.h"
#include "utl/MemMgr.h"

void SIVideo::Reset(){
    mMagic = mWidth = mHeight = mBpp = 0;
    if(mData){
        _MemFree(mData);
        mData = 0;
    }
}

inline int SIVideo::Bpp() const { return mBpp == 8 ? 4 : 8; }
inline int SIVideo::FrameSize() const { return (mMagic * mWidth * Bpp()) >> 3; }

void SIVideo::Load(BinStream& bs, bool load_data) {
    int magic, dump, unused;
    bs >> magic;
    if (magic != 'SIV_') {
        mMagic = magic;
        bs >> mWidth;
        bs >> mHeight;
        bs >> dump;
        bs >> unused;
        bs >> unused;
        bs >> unused;
        bs >> unused;
        mBpp = 8;
    } else {
        uint x;
        bs >> x;
        if (x > 1) MILO_FAIL("Can't load new SIVideo.\n");
        bs >> mMagic;
        bs >> mWidth;
        bs >> mHeight;
        bs >> mBpp;
    }
    if (mData) {
        _MemFree(mData);
        mData = 0;
    }
    if (!load_data) {
        mData = (char*)_MemAlloc(mHeight * (mMagic * mWidth * Bpp() >> 3), 0);
        bs.Read(mData, mHeight * (mMagic * mWidth * Bpp() >> 3));
    }
}

#pragma push
#pragma dont_inline on
DECOMP_FORCEBLOCK(SIVideo, (const SIVideo* s), s->Bpp(); s->FrameSize();)
#pragma pop

char* SIVideo::Frame(int i) {
    if (mData) {
        return &mData[((mMagic * mWidth * Bpp()) >> 3) * i];
    }
    else return NULL;
}

// unsigned int mWidth;
//     unsigned int mHeight;
//     unsigned int mNumFrames;
//     unsigned int mOrder;
//     char* mData;
