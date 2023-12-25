#ifndef RND_RNDBITMAP_HPP
#define RND_RNDBITMAP_HPP

#include "types.h"
#include "rb3/binstream.hpp"

typedef enum {
    /*
     * the way this *seems* to work is as follows;
     * 0b0000 0100 signifies NON-RGB, i.e. compressed/packed/what-have-you; in addition,
     * 0b0100 0100 signifies TPL, i.e. a wii texture
     * not sure what's up with ATI, but i'd leave it alone
     */
    ARGB = 0x1,
    RGBA = 0x3,
    DXT1_BC1 = 0x8,
    DXT5_BC3 = 0x18,
    ATI2_BC5 = 0x20,
    TPL_CMP = 0x48,
    TPL_CMP_ALPHA = 0x148
} BitmapEncoding;

class RndBitmap {
public:
    RndBitmap();
    ~RndBitmap();
    void Load(BinStream&, char&);
    void Create(const RndBitmap&, u8, BitmapEncoding, void*);
    void Create(u16, u16, u16, u8, BitmapEncoding, void*, void*, void*);
    void Create(void*);
    void AllocateBuffer();
    void Reset();
    void Blt(const RndBitmap&, int, int, int, int, int, int);
    void GenerateMips();

    u32 PaletteBytes() const;
    u32 NumPaletteColors() const;
    u32 PixelBytes() const;
    u32 PaletteOffset(int) const; // ????
    u32 PixelOffset(int, int, bool&) const;

    u16 Width() const;
    u16 Height() const;
    void* Palette() const; // merged with MemStream::Tell :despair:
    RndBitmap* nextMip() const;

    void PaletteColor(int, u8&, u8&, u8&, u8&) const;
    void SetPaletteColor(int, u8, u8, u8, u8);
    u8 PixelIndex(int, int) const;
    u8 SetPixelIndex(int, int, u8);
    void PixelColor(int, int, u8&, u8&, u8&, u8&) const;
    void SetPixelColor(int, int, u8, u8, u8, u8);

    u16 w; // 0x0
    u16 h; // 0x2
    u16 bytesperline; // 0x4
    u8 bpp; // 0x6
    u8 pad; // 0x7
    BitmapEncoding enc; // 0x8
    void *imageData; // 0xc
    void *paletteData; // 0x10
    void *allData; // 0x14
    RndBitmap *nextMipmap; // 0x18
};

#endif // RND_RNDBITMAP_HPP
