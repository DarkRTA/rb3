#include "Bitmap.h"

int RndBitmap::NumMips() const {
    const RndBitmap* x = this;
    int i;
    for (i = 0; x->mMip; i++) x = x->mMip;
    return i;
}

int RndBitmap::PixelBytes() const {return mRowBytes * mHeight;}

int RndBitmap::PaletteBytes() const {
    if (mBpp <= 8) {
        if ((mOrder & 0x38) == 0 && (mOrder & 0x80) == 0) {
            return (1 << mBpp) * 4;
        }
    }
    return 0;
}

void PreMultiplyAlpha(u8&, u8&, u8&, u8) {

}


void RndBitmap::Save(BinStream& b) const {

}

extern void ReadChunks(BinStream&, void*, int, int);

void RndBitmap::Load(BinStream& b) {
    u8 mipCt;
    LoadHeader(b, mipCt);
    if (mBuffer) {delete mBuffer; mBuffer = 0;}
    mPalette = 0;
    AllocateBuffer();
    if (mPalette) b.Read(mPalette, PaletteBytes());
    ReadChunks(b, mPixels, PixelBytes(), 0x8000);
    if (mMip) {
        delete mMip;
    }
    mMip = 0;
    int working_w = mWidth;
    int working_h = mHeight;
    RndBitmap* workingMip;
    while (mipCt--) {
        RndBitmap* newMip = new RndBitmap;
        if (newMip) {
            newMip->mBuffer = 0;
            newMip->mMip = 0;
            newMip->Reset();
        }
        workingMip->mMip = newMip;
        working_w = working_w >> 1;
        working_h = working_h >> 1;
        newMip->Create(working_w, working_h, 0, mBpp, mOrder, mPalette, 0, 0);
        ReadChunks(b, newMip->mPixels, newMip->PaletteBytes(), 0x8000);
        workingMip = newMip;
    }
}
