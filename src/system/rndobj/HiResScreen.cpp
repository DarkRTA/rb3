#include "rndobj/HiResScreen.h"
#include "rndobj/Rnd.h"
#include "os/Debug.h"

HiResScreen gHiResScreen;
HiResScreen* TheHiResScreen;

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
    for (uint i = 0; i < mTotalNumCacheLines; i++){
        mFileNames[i] = MakeString("_hires_cache_%.2d.dat", i);
    }
    mBuffer = (unsigned char*)_MemAlloc(mByteSize, 0);
    mCurrLoadedIndex = ui2;
    DeleteCache();
}

HiResScreen::BmpCache::~BmpCache(){
    DeleteCache();
}

HiResScreen::HiResScreen() : mActive(0), mTiling(3), mFileBase("urhigh"), mAccumWidth(0), mAccumHeight(0), 
    mCurrTile(0), mEvenOddDisabled(0), mShrinkToSafe(1), mConsoleShowing(0), mCache(NULL) { }

HiResScreen::~HiResScreen(){

}

void HiResScreen::TakeShot(const char* c, int i) {
    mFileBase = c;
    mTiling = i;
    mActive = 1;
    int x = i * 270;
    mCurrTile = 0;
    mAccumWidth = i * (TheRnd->mWidth - 480);
    mAccumHeight = TheRnd->mHeight * i;
    mAccumHeight -= x;
    mCache = new BmpCache(mAccumWidth, mAccumHeight);
    
    mEvenOddDisabled = TheRnd->GetEvenOddDisabled();
    mShrinkToSafe = TheRnd->ShrinkToSafeArea();
    mConsoleShowing = TheRnd->ConsoleShowing();
    TheRnd->SetEvenOddDisabled(true);
    TheRnd->SetShrinkToSafeArea(false);
    TheRnd->ShowConsole(false);
}

int HiResScreen::GetPaddingX() const { return 480; }
int HiResScreen::GetPaddingY() const { return 270; }

Hmx::Rect HiResScreen::ScreenRect() const {
    Hmx::Rect r = RndCam::sCurrent->mScreenRect;
    return ScreenRect(RndCam::sCurrent, r);
}

Hmx::Rect HiResScreen::ScreenRect(const RndCam* cam, const Hmx::Rect& r) const {
    int a, b, c, d;
    Hmx::Rect x, y, ret = r;
    if ((cam->mTargetTex != NULL && !mOverride) || !mActive || mCurrTile < mTiling * mTiling) {
        CurrentTileRect(x, y, ret);
        int tile_nonsense = mCurrTile / mTiling;
        GetBorderForTile(tile_nonsense * mTiling - mCurrTile, tile_nonsense, a, c, b, d);
        return ret;
    } else return r;
}