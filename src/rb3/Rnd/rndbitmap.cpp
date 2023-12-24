#include "rndbitmap.hpp"

extern void MemFree(void*);

/* oops! these are weak!
RndBitmap::RndBitmap() {
    allData = NULL;
    nextMipmap = NULL;
    Reset();
}

RndBitmap::~RndBitmap() {
    Reset();
} */

void RndBitmap::Reset() {
    bytesperline = 0;
    h = 0;
    w = 0;
    bpp = 0x20;
    enc = ARGB;
    paletteData = NULL;
    imageData = NULL;
    if (allData) {
        MemFree(allData);
        allData = NULL;
    }
    delete nextMipmap;
    nextMipmap = NULL;
}

u32 RndBitmap::PixelBytes() const {
    return bytesperline * h;
}

u32 RndBitmap::PaletteBytes() const {
    if (bpp <= 8) {
        if (((enc & 0x38) == 0) && ((enc & 0x80) == 0)) {
            return (1 << bpp) << 2;
        }
    }
    return 0;
}
