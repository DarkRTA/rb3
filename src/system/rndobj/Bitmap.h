#ifndef RNDOBJ_BITMAP_H
#define RNDOBJ_BITMAP_H
#include "utl/BinStream.h"
#include "obj/Object.h"
#include "utl/MemMgr.h"
#include "milo_types.h"
#include "types.h"

struct tagBITMAPFILEHEADER {
    uint bfSize;
    ushort bfReserved1;
    ushort bfReserved2;
    uint bfOffBits;
};

BinStream& operator>>(BinStream&, tagBITMAPFILEHEADER&);
BinStream& operator<<(BinStream&, const tagBITMAPFILEHEADER&);

struct tagBITMAPINFOHEADER {
    uint biSize;
    int biWidth;
    int biHeight;
    ushort biPlanes;
    ushort biBitCount;
    uint biCompression;
    uint biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    uint biClrUsed;
    uint biClrImportant;
};

BinStream& operator>>(BinStream&, tagBITMAPINFOHEADER&);
BinStream& operator<<(BinStream&, const tagBITMAPINFOHEADER&);

class RndBitmap { // 0x1c
public:
    enum AlphaFlag {
        kGrayscaleAlpha = 0,
        kGrayscaleWhite = 1,
        kTransparentBlack = 2,
    };

    enum BitmapEncoding {

    };

    u16 mWidth; // 0x0
    u16 mHeight; // 0x2
    u16 mRowBytes; // 0x4
    u8 mBpp; // 0x6
    u32 mOrder; // 0x8
    u8* mPixels; // 0xc
    u8* mPalette; // 0x10
    u8* mBuffer; // 0x14
    RndBitmap* mMip; // 0x18

    RndBitmap() : mBuffer(0), mMip(0) {Reset();}
    ~RndBitmap() {Reset();}
    BinStream& LoadHeader(BinStream&, u8&);
    BinStream& SaveHeader(BinStream&) const;
    int NumPaletteColors() const;
    int NumMips() const;
    int PixelBytes() const;
    int PaletteBytes() const;
    u8 NearestColor(u8, u8, u8, u8) const;
    void ConvertColor(const u8*, u8&, u8&, u8&, u8&) const;
    void ConvertColor(u8, u8, u8, u8, u8*) const;
    void Reset();
    void Create(const RndBitmap&, int, int, void*);
    void AllocateBuffer();
    void Create(int, int, int, int, int, void*, void*, void*);
    void Create(void*); 
    void PixelColor(int x, int y, u8& r, u8& g, u8& b, u8& a) const;
    void PaletteColor(int, unsigned char&, unsigned char&, unsigned char&, unsigned char&) const;
    int PixelOffset(int, int, bool&) const;
    int PixelIndex(int, int) const;
    void SetPixelIndex(int, int, unsigned char);
    void ConvertToAlpha();
    void SetAlpha(AlphaFlag);
    void SetPreMultipliedAlpha();
    void SelfMip();
    void GenerateMips();
    RndBitmap* DetachMip();
    void SetMip(RndBitmap*);
    int ColumnNonTransparent(int, int, int, int*);
    bool LoadSafely(BinStream&, int, int);
    void LoadBmp(const char*, bool, bool);
    void Blt(const RndBitmap&, int, int, int, int, int, int);
    bool SamePixelFormat(const RndBitmap&) const;
    bool SamePaletteColors(const RndBitmap&) const;
    void SaveBmp(BinStream*) const;
    bool IsTranslucent() const;
    void Create(const RndBitmap&, unsigned char, BitmapEncoding, void*);
    void SetPaletteColor(int, unsigned char, unsigned char, unsigned char, unsigned char);
    void SetPixelColor(int, int, unsigned char, unsigned char, unsigned char, unsigned char);
    RndBitmap* nextMip() const;

    void Save(BinStream&) const;
    void Load(BinStream&);

    int Width() const { return mWidth; }
    int Height() const { return mHeight; }
    u32 Order() const { return mOrder; }
    int Bpp() const { return mBpp; }
    u8* Palette() const { return mPalette; }
    u8* Pixels() const { return mPixels; }

    NEW_OVERLOAD
    DELETE_OVERLOAD
};

#endif // RNDOBJ_BITMAP_H
