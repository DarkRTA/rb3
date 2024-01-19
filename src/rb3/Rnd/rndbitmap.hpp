#ifndef RND_RNDBITMAP_HPP
#define RND_RNDBITMAP_HPP

#include "types.h"
#include "rb3/binstream.hpp"

/** Bitmap used for textures, normals, etc.
 * A custom bitmap format derived from Microsoft's DirectDraw Surface.
 * Used commonly for textures, can be found as .bmp_platform or .png_platform.
 */
class RndBitmap {
public:

    /** Encodings that bitmaps can use, non-zero chance that there might be more. */
    enum BitmapEncoding {
        /*
         * the way this *seems* to work is as follows;
         * 0b0000 0100 signifies NON-RGB, i.e. compressed/packed/what-have-you; in addition,
         * 0b0100 0100 signifies TPL, i.e. a wii texture
         * not sure what's up with ATI, but i'd leave it alone
         */
        ARGB = 0x1, /**< 32-bit ARGB, 8 bits per channel */
        RGBA = 0x3, /**< 32-bit RGBA, 8 bits per channel */
        DXT1_BC1 = 0x8, /**< DXT1, aka Block Compression 1 */
        DXT5_BC3 = 0x18, /**< DXT5, aka Block Compression 3 */
        ATI2_BC5 = 0x20, /**< ATI2, aka Block Compression 5 */
        TPL_CMP = 0x48, /**< Wii TPL, no alpha */
        TPL_CMP_ALPHA = 0x148 /**< Wii TPL with alpha */
    };

    RndBitmap();
    ~RndBitmap();
    void Load(BinStream&, char&);
    void Create(const RndBitmap&, u8, BitmapEncoding, void*);

    /** Sets the bitmap up via piecewise flags, in offset order. */
    void Create(u16, u16, u16, u8, BitmapEncoding, void*, void*, void*);
    void Create(void*);
    void AllocateBuffer();
    void Reset();
    void Blt(const RndBitmap&, int, int, int, int, int, int);

    /** Automatically generates mipmaps for as small as 16x16. */
    void GenerateMips();

    u32 PaletteBytes() const;

    /** Gets the amount of colors in the palette, given it exists. */
    u32 NumPaletteColors() const;
    u32 PixelBytes() const;
    u32 PaletteOffset(int) const; // ????
    u32 PixelOffset(int, int, bool&) const;

    /** Getter for `w`. */
    u16 Width() const;

    /** Getter for `h`. */
    u16 Height() const;

    /** Getter for `paletteData`. \note This function was code-merged with MemStream::Tell() */
    void* Palette() const {return paletteData;}

    /** Getter for `nextMipmap`. */
    RndBitmap* nextMip() const;

    /** Getter for the palette color @ `idx`.
     * @param [in] idx Index of color to get from the palette.
     * @param [out] r u8 to output the value of the R channel to.
     * @param [out] g u8 to output the value of the G channel to.
     * @param [out] b u8 to output the value of the B channel to.
     * @param [out] a u8 to output the value of the A channel to.
     */
    void PaletteColor(int idx, u8& r, u8& g, u8& b, u8& a) const;

    /** Setter for the palette color @ `idx`.
     * @param [in] idx Index of color to set inthe palette.
     * @param [in] r Value of the R channel to write to the index.
     * @param [in] g Value of the G channel to write to the index.
     * @param [in] b Value of the B channel to write to the index.
     * @param [in] a Value of the A channel to write to the index.
     */
    void SetPaletteColor(int idx, u8 r, u8 g, u8 b, u8 a);

    /** Gets the palette offset of (`x`, `y`).
     *  @return The offset into the palette data of (`x`, `y`).
     */
    u8 PixelIndex(int x, int y) const;
    u8 SetPixelIndex(int, int, u8);
    void PixelColor(int, int, u8&, u8&, u8&, u8&) const;
    void SetPixelColor(int, int, u8, u8, u8, u8);

    u16 w; /**< Width. Offset 0x0 */
    u16 h; /**< Height. Offset 0x2 */
    u16 bytesperline; /**< Bytes per line, used for size calculation. Offset 0x4 */
    u8 bpp; /**< Bits per pixel. Offset 0x6 */
    u8 pad; /**< padding byte. Offset 0x7 */
    BitmapEncoding enc; /**< Encoding format. Offset 0x8 */
    void *imageData; /**< Pointer to image data, in the format defined in `enc`. Offset 0xc */
    void *paletteData; /**< Pointer to palette data, almost always in RGBA. Offset 0x10 */
    void *allData; /**< Pointer to entire image data blob. Offset 0x14 */
    RndBitmap *nextMipmap; /**< Pointer to the next mipmap. Offset 0x18 */
};

#endif // RND_RNDBITMAP_HPP
