#include "rndobj/SIVideo.h"
#include "os/Debug.h"
#include "utl/MemMgr.h"

void SIVideo::Reset(){
    mMagic = mWidth = mHeight = mBpp = 0;
    if(mData){
        _MemFree(mData);
        mData = 0;
    }
}

void SIVideo::Load(BinStream& bs, bool load_data) {
    int magic, dump;
    bs >> magic;
    if (magic != 'SIV_') {
        mMagic = magic;
        bs >> mWidth;
        bs >> mHeight;
        bs >> magic >> dump >> dump >> dump >> dump;
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
    if (mData) { _MemFree(mData); mData = NULL; }
    if (!load_data) {
        uint x = mMagic * mWidth;
        mData = (char*)_MemAlloc(mHeight * (x * (mBpp == 8 ? 4 : 8) >> 3), 0);
        uint y = mMagic * mWidth;
        bs.Read(mData, mHeight * (y * (mBpp == 8 ? 4 : 8) >> 3));
    }
}

int SIVideo::Bpp() const { return mBpp == 8 ? 4 : 8; }

int SIVideo::FrameSize() const {
    return (mMagic * mWidth * Bpp()) >> 3;
}

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
