#include "Bitmap.h"
#include "decomp.h"
#include "os/Debug.h"
#include "os/Endian.h"
#include "utl/BinStream.h"
#include "utl/BufStream.h"
#include "utl/ChunkStream.h"
#include "utl/FileStream.h"
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
    int u4 = -1;
    int i3 = 0x40000;
    unsigned char pr, pg, pb, pa;
    for(int i = (1 << mBpp) - 1; i >= 0; i--){
        PaletteColor(i, pr, pg, pb, pa);
        int diff = (pr - r) * (pr - r) + (pg - g) * (pg - g) + (pb - b) * (pb - b) + (pa - a) * (pa - a);
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
        int start;
        if(mPalette) start = 1 << mBpp;
        else start = 0;
        start--;
        int max = 255;
        int min = 0;
        for(int i = start; i >= 0; i--){
            unsigned char r, g, b, a;
            PaletteColor(i, r, g, b, a);
            switch(flag){
                case kTransparentBlack:
                    if(b == 0 && r == 0 && g == 0){
                        a = min;
                    }
                    break;
                case kGrayscaleWhite:
                    a = r;
                    b = max;
                    g = max;
                    r = max;
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
}

void PreMultiplyAlpha(u8& r, u8& g, u8& b, u8 a) {
    float new_alpha = (float)a / 255.0f;
    r *= new_alpha;
    g *= new_alpha;
    b *= new_alpha;
}

void RndBitmap::SetPreMultipliedAlpha(){
    ConvertToAlpha();
    if(mBpp <= 8){
        int start;
        if(mPalette) start = 1 << mBpp;
        else start = 0;
        start--;
        int max = 255;
        int min = 0;
        for(int i = start; i >= 0; i--){
            unsigned char r, g, b, a;
            PaletteColor(i, r, g, b, a);
            if(a != 255){
                PreMultiplyAlpha(r, g, b, a);
                SetPaletteColor(i, r, g, b, a);
            }
        }
    }
    else {
        for(int i = 0; i < mHeight; i++){
            for(int j = 0; j < mWidth; j++){
                unsigned char r, g, b, a;
                PixelColor(j, i, r, g, b, a);
                if(a != 255){
                    PreMultiplyAlpha(r, g, b, a);
                    SetPixelColor(j, i, r, g, b, a);
                }
            }
        }
    }
}

void RndBitmap::SelfMip(){
    int pixelBytes = PixelBytes();
    mWidth >>= 1;
    int rowOffset = mRowBytes >> 1;
    int dim = Min(mWidth, mHeight);

    int i4 = 0;
    int i3 = 0;
    while(dim > 1){
        if(dim & 1){
            i3 = 1;
        }
        dim >>= 1;
        i4++;
    }
    int count = i4 + i3 - 3;
    RELEASE(mMip);
    RndBitmap* cur = this;
    for(int i = 0; i < count; i++){
        cur->mMip = new RndBitmap();
        cur->mMip->Create(cur->mWidth >> 1, cur->mHeight >> 1, mRowBytes, mBpp, mOrder, mPalette, mPixels + rowOffset, 0);
        pixelBytes >>= 1;
        cur = cur->mMip;
        rowOffset += pixelBytes;
    }
}

void RndBitmap::GenerateMips(){
    int dim = Min(mWidth, mHeight);
    if(dim > 0x10U){
        RELEASE(mMip);
        mMip = new RndBitmap();
        mMip->Create(mWidth >> 1, mHeight >> 1, 0, mBpp, mOrder, mPalette, 0, 0);
        int i18 = 0;
        for(int i = 0; i < mMip->mHeight; i++){
            int i181 = i18 + 1;
            int i17 = 0;
            for(int j = 0; j < mMip->mWidth; j++){
                int i171 = i17 + 1;
                unsigned char r, g, b, a;
                PixelColor(i17, i18, r, g, b, a);
                unsigned short rsum = r;
                unsigned short gsum = g;
                unsigned short bsum = b;
                unsigned short asum = a;
                PixelColor(i171, i18, r, g, b, a);
                rsum += r;
                gsum += g;
                bsum += b;
                asum += a;
                PixelColor(i17, i181, r, g, b, a);
                rsum += r;
                gsum += g;
                bsum += b;
                asum += a;
                PixelColor(i171, i181, r, g, b, a);
                rsum += r;
                gsum += g;
                bsum += b;
                asum += a;
                mMip->SetPixelColor(j, i, rsum >> 2, gsum >> 2, bsum >> 2, asum >> 2);
                i17 += 2;
            }
            i18 += 2;
        }
        mMip->GenerateMips();
    }
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

bool RndBitmap::LoadBmp(BinStream* bs){
    unsigned short us;
    *bs >> us;
    if(us != 0x4D42){
        MILO_WARN("%s not BMP format", bs->Name());
        return false;
    }
    else {
        tagBITMAPFILEHEADER header;
        *bs >> header;
        return LoadDIB(bs, header.bfOffBits);
    }
}

bool RndBitmap::LoadDIB(BinStream* bs, unsigned int offbits){
    tagBITMAPINFOHEADER infoheader;
    *bs >> infoheader;
    if(infoheader.biBitCount < 4){
        MILO_WARN("%s: Unsupported bit depth %d", bs->Name(), infoheader.biBitCount);
        return false;
    }
    if(infoheader.biCompression != 0){
        MILO_WARN("%s: Unsupported compression %d", bs->Name(), infoheader.biCompression);
        return false;
    }
    // more...
    return true;
}

bool RndBitmap::LoadBmp(const char* filename, bool b1, bool b2){
    FileStream* stream = new FileStream(filename, FileStream::kRead, true);
    if(stream->Fail()){
        delete stream;
        return false;
    }
    else {
        if(!LoadBmp(stream)){
            delete stream;
            return false;
        }
        else {
            delete stream;
            if(!b2){
                ProcessFlags(filename, b1);
            }
            return true;
        }
    }
}

bool RndBitmap::ProcessFlags(const char* filename, bool bbb){
    bool contains_flag = false;
    if(strstr(filename, MakeString("%s.", "_tb")) || strstr(filename, MakeString("%s_", "_tb"))) contains_flag = true;
    if(contains_flag){
        SetAlpha(kTransparentBlack);
    }
    else {
        contains_flag = false;
        if(strstr(filename, MakeString("%s.", "_gw")) || strstr(filename, MakeString("%s_", "_gw"))) contains_flag = true;
        if(contains_flag) SetAlpha(kGrayscaleWhite);
        else {
            contains_flag = false;
            if(strstr(filename, MakeString("%s.", "_ga")) || strstr(filename, MakeString("%s_", "_ga"))) contains_flag = true;
            if(contains_flag) SetAlpha(kGrayscaleAlpha);

        }
    }
    
    if(strstr(filename, MakeString("%s.", "_pma")) || strstr(filename, MakeString("%s_", "_pma"))){
        SetPreMultipliedAlpha();
    }
    if(strstr(filename, MakeString("%s.", "_selfmip")) || strstr(filename, MakeString("%s_", "_selfmip"))){
        SelfMip();
    }
    if(bbb){
        if(strstr(filename, MakeString("%s.", "_nomip")) || strstr(filename, MakeString("%s_", "_nomip"))){
            GenerateMips();
        }
        else if(strstr(filename, MakeString("%s.", "_mip")) || strstr(filename, MakeString("%s_", "_mip"))){
            GenerateMips();
        }
    }
    return true;
}

bool RndBitmap::SaveBmp(const char*) const {
    MILO_ASSERT(0, 0x610);
    return false;
}

bool RndBitmap::SaveBmp(BinStream* file) const {
    MILO_ASSERT(file, 0x626);
    if(file->Fail()){
        return false;
    }
    else if(mOrder & 1){
        MILO_WARN("Order isn't kARGB");
        return false;
    }
    else {
        SaveBmpHeader(file);
        SaveBmpPixels(file);
        return true;
    }
}

void RndBitmap::SaveBmpHeader(BinStream* file) const {
    tagBITMAPFILEHEADER fileheader;
    tagBITMAPINFOHEADER infoheader;

    MILO_ASSERT(file, 0x63F);
    unsigned short us = 0x4D42;
    *file << us;
    fileheader.bfOffBits = PaletteBytes() + 0x36;
    fileheader.bfSize = fileheader.bfOffBits + PixelBytes();
    fileheader.bfReserved1 = 0;
    fileheader.bfReserved2 = 0;
    *file << fileheader;

    infoheader.biSize = 0x28;
    infoheader.biWidth = mWidth;
    infoheader.biHeight = mHeight;
    infoheader.biPlanes = 1;
    infoheader.biBitCount = mBpp;
    infoheader.biCompression = 0;
    infoheader.biSizeImage = 0;
    infoheader.biXPelsPerMeter = 0xb11;
    infoheader.biYPelsPerMeter = 0xb11;
    infoheader.biClrUsed = 0;
    infoheader.biClrImportant = 0;
    *file << infoheader;
    if(mPalette){
        file->Write(mPalette, (1 << mBpp) << 2);
    }
}

void RndBitmap::SaveBmpPixels(BinStream* file) const {
    for(int i = mHeight - 1; i >= 0; i--){
        u8* pixels = mPixels + mRowBytes * i;
        if(mBpp == 4){
            u8* pixelIt = pixels;
            for(; pixelIt != pixels + mRowBytes; pixelIt++){
                unsigned char pix = *pixelIt >> 4 | *pixelIt << 4;
                *file << pix;
            }
        }
        else {
            file->Write(pixels, mRowBytes);
        }
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