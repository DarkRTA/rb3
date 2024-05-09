#include "Bitmap.h"
#include "os/Debug.h"
#include "utl/BinStream.h"
#include "utl/ChunkStream.h"
#include "utl/MemMgr.h"
#include "utl/Symbols4.h"

unsigned char BITMAP_REV = 1;

BinStream& RndBitmap::LoadHeader(BinStream& bs, u8& test) {
    u8 ver, h;
    u8 pad[0x13];
    bs >> ver;
    bs >> mBpp;
    if (ver != 0) bs >> mOrder;
    else {bs >> h; mOrder = h;}
    bs >> test;
    bs >> mWidth;
    bs >> mHeight;
    bs >> mRowBytes;
    test = 0;
    bs.Read(pad, ver != 0 ? 0x13 : 6);
    return bs;
}

BinStream& RndBitmap::SaveHeader(BinStream& bs) const {
    static u8 pad[0x13];
    bs << BITMAP_REV << mBpp << (unsigned int)mOrder << (unsigned char)NumMips() << mWidth << mHeight;
    bs << mRowBytes;
    bs.Write(pad, 0x13);
    return bs;
}

BinStream& operator>>(BinStream& bs, tagBITMAPFILEHEADER& bmfh) {
    bs >> bmfh.bfSize;
    bs >> bmfh.bfReserved1;
    bs >> bmfh.bfReserved2;
    bs >> bmfh.bfOffBits;
    return bs;
}

BinStream& operator<<(BinStream& bs, const tagBITMAPFILEHEADER &bmfh) {
    bs << bmfh.bfSize << bmfh.bfReserved1 << bmfh.bfReserved2 << bmfh.bfOffBits;
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


BinStream& operator<<(BinStream& bs, const tagBITMAPINFOHEADER& bmih){
    bs << bmih.biSize << bmih.biWidth << bmih.biHeight << bmih.biPlanes << bmih.biBitCount <<
        bmih.biCompression << bmih.biSizeImage << bmih.biXPelsPerMeter << bmih.biYPelsPerMeter << bmih.biClrUsed << bmih.biClrImportant;
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

void RndBitmap::Create(const RndBitmap& bm, int a, int b, void* c) {
    int test = 0;
    Create(bm.mWidth, bm.mHeight, 0, a, b, c, NULL, NULL);
    if (!mPalette || !c) {
        MILO_ASSERT(bm.Palette(), 392);

    }
}

void RndBitmap::AllocateBuffer() {
    int paletteBytes;
    if (mPalette) paletteBytes = 0; else paletteBytes = PaletteBytes();

    /*if (mPalette) {
        int x = paletteBytes + mWidth * mHeight;
        _MemAlloc(x, 0x20);
    }*/
    int test = mRowBytes * mHeight + paletteBytes;
    if (mPalette) mBuffer = (u8*)_MemAlloc(test, 0x20);
    if (paletteBytes) mPalette = mBuffer;
    mPixels = mBuffer + paletteBytes;
    MILO_ASSERT(!paletteBytes, 439);
    MILO_ASSERT(!((int)mPixels & 31), 441);
}

void RndBitmap::Create(int width, int height, int rowlen, int bpp, int order, void* palette, void* pixels, void* buf) {
    MILO_ASSERT(width >= 0 && height >= 0, 454);
    MILO_ASSERT(bpp == 4 || bpp == 8 || bpp == 16 || bpp == 24 || bpp == 32, 455);
    mWidth = width;
    mHeight = height;
    mRowBytes = rowlen;
    mBpp = bpp;
    mOrder = order;
    mPixels = (u8*)pixels;
    MILO_ASSERT(!((int)mPixels & 31), 465);
    mPalette = (u8*)palette;
    delete mMip;
    mMip = 0;
    if (mRowBytes) {}
    // TODO bpp magic, someone else pls do it
    if (mPalette) {
        _MemFree(mPalette);
        mPalette = 0;
    }
    else if (!buf) AllocateBuffer();
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

void RndBitmap::Blt(const RndBitmap& bm, int dX, int dY, int sX, int sY, int width, int height) {
    MILO_ASSERT(dX + width <= mWidth, 1728);
    MILO_ASSERT(dY + height <= mHeight, 1729);
    MILO_ASSERT(sX + width <= bm.Width(), 1730);
    MILO_ASSERT(sY + height <= bm.Height(), 1731);
    if (!SamePixelFormat(bm)) {

    }
}

bool RndBitmap::SamePixelFormat(const RndBitmap& bm) const {
    if (mBpp != bm.Bpp() || mOrder != bm.Order()) return false;
    if (mPalette && bm.Palette()) {
        return SamePaletteColors(bm);
    } else return true;
}

bool RndBitmap::ColumnNonTransparent(int x, int y, int h, int* d) {
    for (int i; i < h; i++) {
        u8 r, g, b, a;
        PixelColor(x, y, r, g, b, a);
        if (a != 0) return false;
        else *d = y;
    }
    return false;
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
    if (mBuffer) {_MemFree(mBuffer); mBuffer = 0;}
    mPalette = 0;
    AllocateBuffer();
    if (mPalette) bs.Read(mPalette, PaletteBytes());
    ReadChunks(bs, mPixels, mRowBytes * mHeight, 0x8000);

    delete mMip;
    mMip = 0;
    RndBitmap* workingMip = this;
    int working_w = mWidth;
    int working_h = mHeight;
    while (mipCt--) {
        RndBitmap* newMip = new RndBitmap;
        /*if (newMip) {
            newMip->mBuffer = 0;
            newMip->mMip = 0;
            newMip->Reset();
        }*/
        workingMip->mMip = newMip;
        workingMip = newMip;
        working_w = working_w >> 1;
        working_h = working_h >> 1;
        newMip->Create(working_w, working_h, 0, mBpp, mOrder, mPalette, 0, 0);
        ReadChunks(bs, newMip->mPixels, newMip->mRowBytes * newMip->mHeight, 0x8000);
    }
}

bool RndBitmap::LoadSafely(BinStream& bs, int a, int b) {
    u8 test;
    int mips; LoadHeader(bs, test);
    if (mWidth > a || mHeight > b) {
        MILO_WARN("Something is wrong with the bitmap you're loading from %s, w = %d, h = %d", bs.Name(), mWidth, mHeight);
        Create(8,8,0,0x20,0,NULL,NULL,NULL);
        return true;
    } else if (mBpp * mWidth / 8 != mRowBytes) {
        MILO_WARN("Something is wrong with the bitmap you're loading from %s, w = %d, bpp = %d, row bytes: %d", bs.Name(), mWidth, mBpp, mRowBytes);
        Create(8,8,0,0x20,0,NULL,NULL,NULL);
        return false;
    }
    if (mBuffer) {_MemFree(mBuffer); mBuffer = NULL;}
    mPalette = NULL;
    AllocateBuffer();
    if (mPalette) bs.Read(mPalette, PaletteBytes());
    ReadChunks(bs, mPixels, mRowBytes * mHeight, 0x8000);
    if (mBuffer) {
        Reset();
        _MemFree(mBuffer);
    }
    mBuffer = NULL;
    u16 lw = mWidth, lh = mHeight;
    RndBitmap* mp, *prev_mip = this;
    while (mips-- != 0) {
        mp = new RndBitmap;
        prev_mip->mMip = mp;
        lw /= 2;
        lh /= 2;
        mp->Create(lw, lh, 0, mBpp, mOrder, mPalette, NULL, NULL);
        ReadChunks(bs, mp->mPixels, mp->mRowBytes * mp->mHeight, 0x8000);
    }
    return true;
}
