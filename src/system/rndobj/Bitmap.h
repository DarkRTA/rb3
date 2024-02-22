#ifndef RNDOBJ_BITMAP_H
#define RNDOBJ_BITMAP_H

#include "utl/BinStream.h"
typedef unsigned char u8;

class RndBitmap { // 0x1c
    enum AlphaFlag {
        kGrayscaleAlpha = 0,
        kGrayscaleWhite = 1,
        kTransparentBlack = 2,
    };
    unsigned short mWidth; // 0x0
    unsigned short mHeight; // 0x2
    unsigned short mRowBytes; // 0x4
    u8 mBpp; // 0x6
    int mOrder; // 0x8
    void* mPixels; // 0xc
    void* mPalette; // 0x10
    void* mBuffer; // 0x14
    RndBitmap* mMip; // 0x18

    RndBitmap() : mBuffer(0), mMip(0) {Reset();}
    ~RndBitmap() {Reset();}
    void LoadHeader(BinStream&, u8&);
    void SaveHeader(BinStream&) const;
    int NumMips() const;
    int PixelBytes() const;
    int PaletteBytes() const;
    int NearestColor(u8, u8, u8, u8) const;
    int ConvertColor(const u8*, u8&, u8&, u8&, u8&) const;
    int ConvertColor(u8, u8, u8, u8, u8*) const;
    void Reset();
    void Create(const RndBitmap&, int, int, void*);
    void AllocateBuffer();
    void Create(int, int, int, int, int, void*, void*, void*);
    void Create(void*);
    int PixelOffset(int, int, bool&) const;
    int PixelIndex(int, int) const;
    void SetPixelIndex(int, int, unsigned char);
    void ConvertToAlpha();
    void SetAlpha(AlphaFlag);
    void SetPreMultipliedAlpha();
    void SelfMip();
    void GenerateMips();

    void Save(BinStream&) const;
    void Load(BinStream&);
};

#endif // RNDOBJ_BITMAP_H
