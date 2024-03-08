#include "Bitmap.h"
#include "os/Debug.h"
#include "utl/BinStream.h"
#include "utl/ChunkStream.h"
#include "utl/MemMgr.h"

void RndBitmap::SaveHeader(BinStream& bs) const {
    static u8 pad[0x13];
    u16 h = mHeight;
    u16 w = mWidth;
    u8 mipCt = NumMips();
    u8 rb = mRowBytes;
    u32 ord = mOrder;
    u16 rev = BITMAP_REV;
    bs << BITMAP_REV;
    bs << rb;
    bs << (int)ord;
    bs << mipCt;
    bs << w;
    bs << h;
    bs.Write(pad, 0x13);
}

BinStream& operator>>(BinStream& bs, tagBITMAPFILEHEADER& bmfh) {
    bs >> bmfh.bfSize;
    bs >> bmfh.bfReserved1;
    bs >> bmfh.bfReserved2;
    bs >> bmfh.bfOffBits;
    return bs;
}

BinStream& operator<<(BinStream& bs, const tagBITMAPFILEHEADER &bmfh) {
    // bs << (int)bmfh.bfSize;
    // bs << bmfh.bfReserved1;
    // bs << bmfh.bfReserved2;
    // bs << (int)bmfh.bfOffBits;
    return bs;
}

BinStream& operator>>(BinStream& bs, tagBITMAPINFOHEADER& bmih) {
    bs >> bmih.biSize;
    bs >> bmih.biWidth;
    bs >> bmih.biHeight;
    bs >> bmih.biPlanes;
    bs >> bmih.biBitCount;
    bs >> bmih.biCompression;
    bs >> bmih.biSizeImage;
    bs >> bmih.biXPelsPerMeter;
    bs >> bmih.biYPelsPerMeter;
    bs >> bmih.biClrUsed;
    bs >> bmih.biClrImportant;
    return bs;
}

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

void RndBitmap::Reset() {
    mRowBytes = 0;
    mHeight = 0;
    mWidth = 0;
    mBpp = 0x20;
    mOrder = 1;
    mPalette = NULL;
    mPixels = NULL;
    if (mBuffer) {
        _MemFree(mBuffer);
        mBuffer = NULL;
    }
    if (mMip) {
        RndBitmap* m = mMip;
        m->Reset();
        _MemFree(m);
    }
    mMip = 0;
}

void RndBitmap::AllocateBuffer() {
    int palette_bytes;
    if (mPalette) {
        palette_bytes = PaletteBytes();
    } else palette_bytes = 0;

    if (mPalette) {
        int x = palette_bytes + mWidth * mHeight;
        _MemAlloc(x, 0x20);
    }
}

void PreMultiplyAlpha(u8&, u8&, u8&, u8) {

}

RndBitmap* RndBitmap::DetachMip() {
    RndBitmap* m = mMip;
    mMip = NULL;
    return m;
}

void RndBitmap::SetMip(RndBitmap* bm) {
    RndBitmap* mip = mMip;
    delete mip;
    mMip = 0;
    if (bm) {
        MILO_ASSERT(mWidth / 2 == bm->Width(), 1101);
        MILO_ASSERT(mHeight / 2 == bm->Height(), 1102);
        MILO_ASSERT(mOrder == bm->Order(), 1103);
        MILO_ASSERT(mBpp == bm->Bpp(), 1104);
        mMip = bm;
    }
}

void RndBitmap::Save(BinStream& bs) const {
    SaveHeader(bs);
    if (mPalette) {
        bs.Write(mPalette, PaletteBytes());
    }
    const RndBitmap* m = this;
    while (m) {
        WriteChunks(bs, m->mPixels, m->mRowBytes * m->mHeight, 0x8000);
        m = m->mMip;
    }
}

void RndBitmap::Load(BinStream& bs) {
    u8 mipCt;
    LoadHeader(bs, mipCt);
    if (mBuffer) {delete mBuffer; mBuffer = 0;}
    mPalette = 0;
    AllocateBuffer();
    if (mPalette) bs.Read(mPalette, PaletteBytes());
    ReadChunks(bs, mPixels, PixelBytes(), 0x8000);
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
        ReadChunks(bs, newMip->mPixels, newMip->PaletteBytes(), 0x8000);
        workingMip = newMip;
    }
}
