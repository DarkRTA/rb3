#include "rndobj/SIVideo.h"
#include "utl/MemMgr.h"

void SIVideo::Reset(){
    mWidth = mHeight = mNumFrames = mOrder = 0;
    if(mData){
        _MemFree(mData);
        mData = 0;
    }
}

// unsigned int mWidth;
//     unsigned int mHeight;
//     unsigned int mNumFrames;
//     unsigned int mOrder;
//     char* mData;
