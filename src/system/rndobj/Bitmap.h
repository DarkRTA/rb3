#pragma once
#include "utl/BinStream.h"
#include "obj/Object.h"
#include "utl/MemMgr.h"
#include "milo_types.h"
#include "types.h"

/** Info at the very start of a .bmp. */
struct tagBITMAPFILEHEADER {
    /** The .bmp file size in bytes */
    uint bfSize; // 0x0
    /** Reserved, if writing set this to 0 */
    ushort bfReserved1; // 0x4
    /** Reserved, if writing set this to 0 */
    ushort bfReserved2; // 0x6
    /** The start address of the byte where the bitmap image data is found. */
    uint bfOffBits; // 0x8
};

BinStream& operator>>(BinStream&, tagBITMAPFILEHEADER&);
BinStream& operator<<(BinStream&, const tagBITMAPFILEHEADER&);

/** Info about the bitmap's pixel array, comes after the file header. */
struct tagBITMAPINFOHEADER {
    /** This header's size in bytes (should be 40) */
    uint biSize; // 0x0
    /** The bitmap's width in pixels */
    int biWidth; // 0x4
    /** The bitmap's height in pixels */
    int biHeight; // 0x8
    /** The number of color planes (must be 1. why? idk lol) */
    ushort biPlanes; // 0xc
    /** The number of bits per pixel, aka the image's color depth. */
    ushort biBitCount; // 0xe
    /** The compression method being used. (usually 0) */
    uint biCompression; // 0x10
    /** The image size, aka the number of chars in the bitmap's pixel array. */
    uint biSizeImage; // 0x14
    /** The image's horizontal resolution (pixels per meter) */
    int biXPelsPerMeter; // 0x18
    /** The image's vertical resolution (pixels per meter) */
    int biYPelsPerMeter; // 0x1c
    /** The number of colors in the color palette */
    uint biClrUsed; // 0x20
    /** The number of important colors being used */
    uint biClrImportant; // 0x24
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

    /** The bitmap's width in pixels. */
    u16 mWidth; // 0x0
    /** The bitmap's height in pixels. */
    u16 mHeight; // 0x2
    /** The number of bytes in memory that make up one row of the image. */
    u16 mRowBytes; // 0x4
    /** The number of bits per pixel, aka color depth. */
    u8 mBpp; // 0x6
    /** The ordering of the color bytes in this bitmap (e.g. RGBA, BGRA) - determined with masking */
    u32 mOrder; // 0x8
    /** The pixels that makes up this image. */
    u8* mPixels; // 0xc
    /** The colors of this image's color palette. */
    u8* mPalette; // 0x10
    /** The contiguous series of bytes that make up the bitmap's palette and pixels */
    u8* mBuffer; // 0x14
    /** The next mip after this one, used to create a mipmap. */
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
    unsigned char PixelIndex(int, int) const;
    void SetPixelIndex(int, int, unsigned char);
    void ConvertToAlpha();
    void SetAlpha(AlphaFlag);
    void SetPreMultipliedAlpha();
    void SelfMip();
    void GenerateMips();
    RndBitmap* DetachMip();
    void SetMip(RndBitmap*);
    unsigned char ColumnNonTransparent(int, int, int, int*);
    bool LoadSafely(BinStream&, int, int);
    void Blt(const RndBitmap&, int, int, int, int, int, int);
    bool SamePixelFormat(const RndBitmap&) const;
    bool SamePaletteColors(const RndBitmap&) const;
    bool IsTranslucent() const;
    void SetPaletteColor(int, unsigned char, unsigned char, unsigned char, unsigned char);
    void SetPixelColor(int, int, unsigned char, unsigned char, unsigned char, unsigned char);
    bool LoadBmp(BinStream*);
    bool LoadDIB(BinStream*, unsigned int);
    bool LoadBmp(const char*, bool, bool);
    bool ProcessFlags(const char*, bool);
    bool SaveBmp(const char*) const;
    bool SaveBmp(BinStream*) const;
    void SaveBmpHeader(BinStream*) const;
    void SaveBmpPixels(BinStream*) const;
    void DxtColor(int, int, unsigned char&, unsigned char&, unsigned char&, unsigned char&) const;
    int PaletteOffset(int) const;
    unsigned char RowNonTransparent(int, int, int, int*);

    void Save(BinStream&) const;
    void Load(BinStream&);

    int Width() const { return mWidth; }
    int Height() const { return mHeight; }
    u32 Order() const { return mOrder; }
    int Bpp() const { return mBpp; }
    u8* Palette() const { return mPalette; }
    u8* Pixels() const { return mPixels; }
    RndBitmap* nextMip() const { return mMip; }

    NEW_OVERLOAD
    DELETE_OVERLOAD
};
