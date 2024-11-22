#include "Bitmap.h"
#include "decomp.h"
#include "os/Debug.h"
#include "os/Endian.h"
#include "utl/BinStream.h"
#include "utl/BufStream.h"
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

DECOMP_FORCEFUNC(Bitmap, RndBitmap, PixelBytes())

#pragma push
#pragma force_active on
inline int RndBitmap::PixelBytes() const { return mRowBytes * mHeight; }
#pragma pop

int RndBitmap::PaletteBytes() const {
    if (mBpp <= 8) {
        if ((mOrder & 0x38) == 0 && (mOrder & 0x80) == 0) {
            return (1 << mBpp) * 4;
        }
    }
    return 0;
}

unsigned char RndBitmap::NearestColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) const {
    int i = 1 << mBpp;
    int i3 = 0x40000;
    int u4 = -1;
    unsigned char pr, pg, pb, pa;
    while(--i >= 0){
        PaletteColor(i, pr, pg, pb, pa);
        int diff = (pr - r) * (pr - r) + (pg - g) * (pg - g) +  (pb - b) * (pb - b) + (pa - a) * (pa - a);
        if(diff < i3){
            i3 = diff;
            u4 = i;
        }
    }
    return u4;
}

void RndBitmap::ConvertColor(const unsigned char* uc, unsigned char& r, unsigned char& g, unsigned char& b, unsigned char& a) const {
    if(mBpp == 0x20 || mPalette){
        if(mOrder & 1){
            a = uc[3];
            b = uc[2];
            g = uc[1];
            r = uc[0];
        }
        else if(mOrder & 0x40){
            a = uc[0];
            r = uc[1];
            g = uc[0x20];
            b = uc[0x21];     
        }
        else {
            a = uc[3];
            r = uc[2];
            g = uc[1];
            b = uc[0];
        }

        if(mOrder & 2){
            a = ((a * 256) - a) >> 7;
        }
    }
    else if(mBpp == 0x10){
        unsigned short swapped = SwapBytes(*(unsigned short*)uc);
        if(mOrder & 1){
            a = -(swapped >> 0xF & 1);
            b = swapped >> 7 & 0xF8;
            g = swapped >> 2 & 0xF8;
            r = swapped << 3;
        }
        else {
            a = -(swapped >> 0xF & 1);
            r = swapped >> 7 & 0xF8;
            g = swapped >> 2 & 0xF8;
            b = swapped << 3;
        }
    }
    else if((mOrder & 0x80) && (mOrder & 0x40)){
        r = 255;
        g = 255;
        b = 255;
        a = *uc;
    }
    else {
        a = 255;
        if(mOrder & 1){
            b = uc[2];
            g = uc[1];
            r = uc[0];
        }
        else {
            r = uc[2];
            g = uc[1];
            b = uc[0];
        }
    }
}

void RndBitmap::ConvertColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a, unsigned char* uc) const {
    if(mBpp == 0x20 || mPalette){
        if(mOrder & 2){
            a = (a + 1) >> 1;
        }
        if(mOrder & 1){
            uc[3] = a;
            uc[2] = b;
            uc[1] = g;
            uc[0] = r;
        }
        else if(mOrder & 0x40){
            uc[0] = a;
            uc[1] = r;
            uc[0x20] = g;
            uc[0x21] = b;

        }
        else {
            uc[3] = a;
            uc[2] = r;
            uc[1] = g;
            uc[0] = b;
        }
        return;
    }
    if(mBpp == 0x10){
        unsigned short* twobytes = (unsigned short*)uc;
        if(mOrder & 1){
            *twobytes = r >> 3 | (g & 0xF8) << 2 | (a & 0x80) << 8 | (b & 0xF8) << 7;
        }
        else {
            *twobytes = b >> 3 | (g & 0xF8) << 2 | (a & 0x80) << 8 | (r & 0xF8) << 7;
        }        
        *twobytes = EndianSwap(*twobytes);
        return;
    }
    if((mOrder & 0x80) && (mOrder & 0x40)){
        uc[0] = a;
        return;
    }
    if(mOrder & 1){
        uc[2] = b;
        uc[1] = g;
        uc[0] = r;
    }
    else {
        uc[2] = r;
        uc[1] = g;
        uc[0] = b;
    }
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
    RELEASE(mMip);
}

void RndBitmap::Create(const RndBitmap& bm, int bpp, int order, void* palette) {
    int test = 0;
    Create(bm.mWidth, bm.mHeight, 0, bpp, order, palette, NULL, NULL);
    if (mPalette && !palette) {
        MILO_ASSERT(bm.Palette(), 392);
        for(int i = 0; i < (bm.Palette() ? 1 << bm.Bpp() : 0); i++){
            unsigned char r, g, b, a;
            bm.PaletteColor(i, r, g, b, a);
            SetPaletteColor(i, r, g, b, a);
        }
    }
    Blt(bm, 0, 0, 0, 0, mWidth, mHeight);
    if(bm.mMip){
        mMip = new RndBitmap();
        mMip->Create(*bm.mMip, bpp, order, mPalette);
    }
}

void RndBitmap::Create(const RndBitmap& bmap, unsigned char uc, RndBitmap::BitmapEncoding enc, void* v){
    Create(bmap.Width(), bmap.Height(), 0, uc, (int)enc, v, 0, 0);
    if(mPalette && !v){
        bmap.Palette();
        for(int i = 0; i < bmap.NumPaletteColors(); i++){
            unsigned char r, g, b, a;
            bmap.PaletteColor(i, r, g, b, a);
            SetPaletteColor(i, r, g, b, a);
        }
    }
    Blt(bmap, 0, 0, 0, 0, mWidth, mHeight);
    if(bmap.nextMip()){
        mMip = new RndBitmap();
        mMip->Create(*bmap.nextMip(), uc, enc, mPalette);
    }
}

int RndBitmap::NumPaletteColors() const {
    if(mPalette) return 1 << mBpp;
    else return 0;
}

void RndBitmap::AllocateBuffer() {
    int paletteBytes;
    if (mPalette) paletteBytes = 0;
    else paletteBytes = PaletteBytes();
    int sum = paletteBytes + PixelBytes();
    if (sum) mBuffer = (u8*)_MemAlloc(sum, 0x20);
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
    RELEASE(mMip);
    if(mRowBytes == 0){
        if(mBpp == 4){
            if(mWidth & 1){
                mRowBytes = (mWidth + 1) * 4 >> 3;
                goto ok;
            }
        }
        mRowBytes = mWidth * mBpp >> 3;
    }
ok:
    if(mOrder & 4){
        unsigned char theBpp = mBpp;
        if((theBpp == 8 && (mWidth < 0x10 || mHeight < 0x10)) || (theBpp == 4 && (mWidth < 0x20 || mHeight < 0x10)) || theBpp > 8){
            mOrder &= 0xfffffffb;
        }
    }
    if(mBuffer){
        _MemFree(mBuffer);
        mBuffer = nullptr;
    }
    if(buf) mBuffer = (u8*)buf;
    else if(!pixels) AllocateBuffer();
}

void RndBitmap::Create(void* buffer){
    if(!buffer) MILO_WARN("Load buffer is empty");
    else {
        BufStream bs(buffer, 32, true);
        unsigned char buf;
        LoadHeader(bs, buf);
        if(mBuffer){
            _MemFree(mBuffer);
            mBuffer = nullptr;
        }
        mBuffer = (u8*)buffer;
        u8* i5 = mBuffer + bs.Tell();

        int pbytes = PaletteBytes();
        mPalette = pbytes ? i5 : 0;

        int pixbytes = PixelBytes();
        mPixels = i5 + pbytes;
        MILO_ASSERT(!((int)mPixels & 31), 0x21A);
        u8* pixels = i5 + pbytes + pixbytes;
        RELEASE(mMip);
        int width = mWidth;
        int height = mHeight;
        RndBitmap* cur = this;
        while(buf-- != 0){
            cur->mMip = new RndBitmap();
            cur = cur->mMip;
            width >>= 1;
            height >>= 1;
            pixbytes >>= 2;
            cur->Create(width, height, 0, mBpp, mOrder, mPalette, pixels, 0);
            pixels += pixbytes;
        }
    }
}

DECOMP_FORCEACTIVE(Bitmap, "mBpp == 4", "alpha pair doesn't match size or palettization", "alpha combination has too many colors")

void RndBitmap::ConvertToAlpha(){
    if(mBpp == 0x18){
        RndBitmap bmap;
        bmap.Create(*this, 32, mOrder, 0);
        if(mBuffer){
            _MemFree(mBuffer);
            mBuffer = nullptr;
        }
        mPalette = bmap.mPalette;
        mPixels = bmap.mPixels;
        MILO_ASSERT(!((int)mPixels & 31), 0x342);
        mBuffer = bmap.mBuffer;
        mBpp = bmap.mBpp;
        mRowBytes = bmap.mRowBytes;
        bmap.mBuffer = nullptr;
    }
}

void RndBitmap::SetAlpha(AlphaFlag flag){
    ConvertToAlpha();
    if(mBpp <= 8){
        int i = mPalette ? (1 << mBpp) : 0;
        while(--i >= 0){
            unsigned char r, g, b, a;
            PaletteColor(i, r, g, b, a);
            switch(flag){
                case kTransparentBlack:
                    if(b == 0 && r == 0 && g == 0){
                        a = 0;
                    }
                    break;
                case kGrayscaleWhite:
                    a = r;
                    b = 255;
                    g = 255;
                    r = 255;
                    break;
                case kGrayscaleAlpha:
                    a = r;
                    break;
                default:
                    break;
            }
            SetPaletteColor(i, r, g, b, a);
        }
    }
    else {
        for(int i = 0; i < mHeight; i++){
            for(int j = 0; j < mWidth; j++){
                unsigned char r, g, b, a;
                PixelColor(j, i, r, g, b, a);
                switch(flag){
                    case kTransparentBlack:
                        if(b == 0 && r == 0 && g == 0){
                            a = 0;
                        }
                        break;
                    case kGrayscaleWhite:
                        a = r;
                        b = 255;
                        g = 255;
                        r = 255;
                        break;
                    case kGrayscaleAlpha:
                        a = r;
                        break;
                    default:
                        break;
                }
                SetPixelColor(j, i, r, g, b, a);
            }
        }
    }

//   ConvertToAlpha(this);
//   if (this->mBpp < 9) {
//   }
//   else {
//     for (iVar1 = 0; iVar1 < this->mHeight; iVar1 = iVar1 + 1) {
//       for (iVar2 = 0; iVar2 < this->mWidth; iVar2 = iVar2 + 1) {
//         PixelColor(this,iVar2,iVar1,&local_25,&local_26,&local_27,&local_28);
//         if (param_1 == 2) {
//           if (((local_27 == '\0') && (local_25 == '\0')) && (local_26 == '\0')) {
//             local_28 = '\0';
//           }
//         }
//         else if (param_1 == 1) {
//           local_28 = local_25;
//           local_27 = 0xff;
//           local_26 = 0xff;
//           local_25 = 0xff;
//         }
//         else if (param_1 == 0) {
//           local_28 = local_25;
//         }
//         SetPixelColor(this,iVar2,iVar1,local_25,local_26,local_27,local_28);
//       }
//     }
//   }
//   return;
}

void PreMultiplyAlpha(u8& r, u8& g, u8& b, u8 a) {
    float new_alpha = (float)a / 255.0f;
    r *= new_alpha;
    g *= new_alpha;
    b *= new_alpha;
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

int RndBitmap::ColumnNonTransparent(int x, int y, int h, int* d) {
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
        return false;
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