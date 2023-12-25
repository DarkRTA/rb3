#include "rndbitmap.hpp"

extern void MemFree(void*);
extern void* _MemAlloc(int, int);

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

void RndBitmap::Create(const RndBitmap& nuBmp, u8 nuBpp, BitmapEncoding enc, void* nuPalette) {
    Create(nuBmp.Width(), nuBmp.Height(), 0, nuBpp, enc, nuPalette, (void*)NULL, (void*)NULL);
    if (paletteData && nuPalette == NULL) {
        nuBmp.Palette();
        u8 r,g,b,a;
        for (int i = 0; i < NumPaletteColors(); i++) {
            nuBmp.PaletteColor(i,r,g,b,a);
            SetPaletteColor(i, r, g, b, a);
        }
    }
    Blt(nuBmp, 0, 0, 0, 0, w, h);
    if (nuBmp.nextMip()) {
        RndBitmap* next = new RndBitmap();
        nextMipmap = next;
        next = nuBmp.nextMip();
        nextMipmap->Create(*next, nuBpp, enc, paletteData);
    }
}

u32 RndBitmap::NumPaletteColors() const {
    if (paletteData) {
        return 1 << bpp;
    }
    return 0;
}

void RndBitmap::AllocateBuffer() {
    u32 palSize;
    if (!paletteData) {
        palSize = PaletteBytes();
    } else palSize = 0;
    u32 imgSize = PixelBytes();
    if (palSize + imgSize) {
        allData = _MemAlloc(imgSize+palSize, 0x20);
    }
    if (palSize) paletteData = allData;
    imageData = (void*)((int)allData + palSize);
}

void RndBitmap::Create(u16 nuW, u16 nuH, u16 nuByPL, u8 nuBPP, BitmapEncoding nuEnc, void* nuImgData, void* nuPalData, void* nuData) {
    w = nuW;
    h = nuH;
    bytesperline = nuByPL;
    bpp = nuBPP;
    enc = nuEnc;
    imageData = nuImgData;
    paletteData = nuPalData;
    delete nextMipmap;
    nextMipmap = NULL;
    if (bytesperline == 0) {
        if (bpp == 4) {
            if (w & 1) {
                bytesperline = ((w + 1) * 4) >> 3;
                goto test_lbl;
            }
        }
        bytesperline = (w * bpp) >> 3;
    }
    test_lbl:
    u8 bVar1;
    if ((enc & 4) && ((((bVar1 = this->bpp, bVar1 == 8 && (w < 0x10 || h < 0x10)) ||
       ((bVar1 == 4 && (w < 0x20 || h < 0x10)))) || (8 < bVar1))))
       enc &= ~4u; // all this... to clear 4?
    if (allData) {
        MemFree(allData);
        allData = NULL;
    }
    if (!nuData) {
        if (!nuImgData) AllocateBuffer();
    } else allData = nuData;
}
/* these two are outside of the convenient block of identified funcs
u32 RndBitmap::PixelBytes() const {
    return bytesperline * h; // if it was just the width, that wouldn't be specific enough
}

u32 RndBitmap::PaletteBytes() const {
    if (bpp <= 8) { // if the bpp is over 8, it's not palettized
        if (((enc & 0x38) == 0) && ((enc & 0x80) == 0)) { // check for compression
            return (1 << bpp) << 2; // palette size x 4
        }
    }
    return 0;
}*/

