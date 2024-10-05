#pragma once

#include "rndobj/Tex.h"
#include "utl/PoolAlloc.h"

class WiiTex : public RndTex {
public:
    WiiTex();
    virtual ~WiiTex();
    OBJ_CLASSNAME(WiiTex)
    OBJ_SET_TYPE(WiiTex)
    NEW_OBJ(WiiTex)

    void PresyncBitmap();
    void DeleteSurface();
    void MovieSwapFrames();
    void CopyFromFB(int, int, int, int, bool, bool);
    void CreateScreenShot();

    u8 pad[32];
    void* mImageData; // 0x84
    GXTexFmt mFormat; // 0x88

    static bool bComposingOutfitTexture;

    void* operator new(unsigned long i) { return _PoolAlloc(i, i, FastPool); }
    void operator delete(void* obj) { _PoolFree(0xd0, FastPool, obj); }
};
