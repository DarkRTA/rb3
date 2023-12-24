#ifndef RND_RNDBITMAP_HPP
#define RND_RNDBITMAP_HPP

#include "types.h"

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
    RndBitmap();
    ~RndBitmap();

    u32 PaletteBytes() const;
    u32 PixelBytes() const;

    u16 unk0; // 0x0
    u16 w; // 0x2
    u16 h; // 0x4
    u8 bpp; // 0x6
    u8 pad; // 0x7
    BitmapEncoding enc; // 0x8
    size_t size; // guess
    void *paletteData;
    void *data; // size: width * height * (bpp/8 (compiler might do >> 3))
    RndBitmap *nextMipmap;
};

#endif // RND_RNDBITMAP_HPP
