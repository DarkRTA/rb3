#include "rndobj/HiResScreen.h"
#include "os/Debug.h"

HiResScreen gHiResScreen;
HiResScreen* TheHiResScreen = &gHiResScreen;

HiResScreen::BmpCache::BmpCache(unsigned int ui1, unsigned int ui2){
    mRowsPerCacheLine = ui2 + 1;
    mPixelsPerRow = ui1;
    mTotalRows = ui2;
    mDirtyStart = 0;
    mDirtyEnd = 0;
    mByteSize = mTotalRows % mRowsPerCacheLine;
    MILO_ASSERT(mTotalRows % mRowsPerCacheLine == 0, 0x3B);
    mTotalNumCacheLines = mTotalRows / mRowsPerCacheLine;
    mFileNames = new String[mTotalNumCacheLines];
    for(int i = 0; i < mTotalNumCacheLines; i++){
        mFileNames[i] = MakeString("_hires_cache_%.2d.dat");
    }
    mBuffer = (unsigned char*)_MemAlloc(mByteSize, 0);
    mCurrLoadedIndex = ui2;
    DeleteCache();
}

HiResScreen::BmpCache::~BmpCache(){
    DeleteCache();
}

HiResScreen::HiResScreen() : mActive(0), mTiling(3), mFileBase("urhigh"), mAccumWidth(0), mAccumHeight(0), mCurrTile(0), mOverride(0), mEvenOddDisabled(1), mShrinkToSafe(0), mCache(0) {
    
}

HiResScreen::~HiResScreen(){

}
