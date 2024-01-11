#include "rndbitmap.hpp"
#include "common.hpp"
#include "rb3/bufstream.hpp"

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
    if (paletteData == 0) {
        palSize = PaletteBytes();
    } else palSize = 0;
    u32 imgSize = PixelBytes();
    if (palSize + imgSize != 0) {
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
//    if ((enc & 4) && ((((bVar1 = this->bpp, bVar1 == 8 && (w < 0x10 || h < 0x10)) ||
//        ((bVar1 == 4 && (w < 0x20 || h < 0x10)))) || (8 < bVar1))))
//        enc &= ~4u; // all this... to clear 4?
    if (allData) {
        MemFree(allData);
        allData = NULL;
    }
    if (nuData == 0) {
        if (nuImgData == 0) AllocateBuffer();
    } else allData = nuData;
}

void RndBitmap::Create(void* inData) {
    if (inData) {
        char mips;
        BufStream strm(inData, 0x20, true);
        Load(strm, mips); // mips gets overwritten with 0, so it doesn't... do anything?
        if (allData) {
            MemFree(allData);
            allData = 0;
        }
        allData = inData;
        size_t len = strm.Tell();
        void* workingPtr = (void*)((int)allData + len);
        len = PaletteBytes();
        void* palette = workingPtr;
        if (len == 0) {
            palette = 0;
        }
        paletteData = palette;
        workingPtr = (void*)((int)workingPtr + len);
        len = PixelBytes();
        imageData = workingPtr;
        workingPtr = (void*)((int)workingPtr + len);
        delete nextMipmap;
        nextMipmap = 0;
        u16 mipW = w;
        u16 mipH = h;
        RndBitmap* recursy_the_ptr = this;
        for (; mips != 0; mips--) {
            RndBitmap* recursy2 = new RndBitmap;
            recursy_the_ptr->nextMipmap = recursy2;
            mipW /= 2;
            mipH /= 2;
            len /= 4; // len makes a reappearance here to be used as a mipmap size tracker. neat trick
            recursy2->Create(mipW, mipH, 0, bpp, enc, paletteData, workingPtr, NULL);
            workingPtr = (void*)((int)workingPtr + len);
            recursy_the_ptr = recursy2;
        }
    }
}

void RndBitmap::GenerateMips(void) {
    u8 curR, curG, curB, curA;
    u16 totalR, totalG, totalB, totalA;

    if ((Minimum((uint)w,(uint)h) & 0xFFFFU) > 16) {
        delete nextMipmap;
        nextMipmap = 0;
        nextMipmap = new RndBitmap;
        nextMipmap->Create(w >> 1, h >> 1, 0, bpp, enc, paletteData, NULL, NULL);
        for (int localY = 0, mipY = 0; mipY < nextMipmap->h; mipY++, localY += 2) {
            for (int localX = 0, mipX = 0; mipX < nextMipmap->w; mipX++, localX += 2) {
                PixelColor(localX, localY, curR, curG, curB, curA);
                totalR += curR; totalG += curG; totalB += curB; totalA += curA;
                PixelColor(localX, localY, curR, curG, curB, curA);
                totalR += curR; totalG += curG; totalB += curB; totalA += curA;
                PixelColor(localX, localY, curR, curG, curB, curA);
                totalR += curR; totalG += curG; totalB += curB; totalA += curA;
                PixelColor(localX, localY, curR, curG, curB, curA);
                totalR += curR; totalG += curG; totalB += curB; totalA += curA;
                nextMipmap->SetPixelColor(mipX, mipY, (totalR >> 2), (totalG >> 2), (totalB >> 2), (totalA >> 2));
            }
        }
        nextMipmap->GenerateMips();
    }
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
