#include "Tex.h"
#include "os/Debug.h"
#include "revolution/gx/GXFrameBuf.h"
#include "revolution/gx/GXPixel.h"
#include "rndobj/Rnd.h"
#include "rndobj/Tex.h"
#include "rndwii/Rnd.h"
#include <set>

std::set<WiiTex*> gRenderTextureSet;

bool WiiTex::bComposingOutfitTexture = false;

WiiTex::WiiTex() : mImageData(NULL), mFormat(   ) { }

WiiTex::~WiiTex() { DeleteSurface(); }

void WiiTex::PresyncBitmap() { DeleteSurface(); }

void WiiTex::DeleteSurface() {

}

u32 OrderFromFormat(unsigned int ui) {
    switch (ui) {
        case 4:
            return 0;
        case 14:
            return 72;
        case 6:
            return 64;
        case 1:
            return 192;
        default:
            MILO_FAIL("Currently unsupported format %d for OrderFromFormat.\n", ui);
            return 0;
    }
}

void WiiTex::MovieSwapFrames() {

}

void WiiTex::CopyFromFB(int src_x, int src_y, int src_w, int src_h, bool copy_bool, bool is_mip) {
    MILO_ASSERT(mImageData, 711);
    MILO_ASSERT(mType & kRendered, 712);
    if (copy_bool) GXSetZMode(TRUE, GX_ALWAYS, TRUE);
    GXSetAlphaUpdate(TRUE);
    // TODO add PSVEC copy
    GXSetCopyClear(*(GXColor*)&TheRnd->mClearColor,0x00FFFFFF);
    GXSetTexCopySrc(src_x, src_y, src_w, src_h);
    GXSetTexCopyDst(mWidth, mHeight, mFormat, is_mip);
    GXGetTexBufferSize(mWidth, mHeight, mFormat, 0, 0);

    GXSetCopyClamp(GX_CLAMP_ALL);
    GXCopyTex(mImageData, u8(copy_bool));
    if (bComposingOutfitTexture || !TheRnd->mInGame) RndGxDrawDone();
}

bool ConvertAndStoreYUV2BMP(void*, int, int, void*);

void WiiTex::CreateScreenShot() {
    DeleteSurface();
    if (!ConvertAndStoreYUV2BMP(WiiRnd::GetCurrXFB(), mWidth, mHeight, mImageData)) {
        MILO_WARN("[WiiTex::CreateScreenShot] Failed to covert XFB to BMP!\n"); // BUG: covert
        DeleteSurface();
    }
}

bool ConvertAndStoreYUV2BMP(void*, int, int, void*) {

}
