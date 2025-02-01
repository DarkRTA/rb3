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

BinStream &operator>>(BinStream &, tagBITMAPFILEHEADER &);
BinStream &operator<<(BinStream &, const tagBITMAPFILEHEADER &);

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

BinStream &operator>>(BinStream &, tagBITMAPINFOHEADER &);
BinStream &operator<<(BinStream &, const tagBITMAPINFOHEADER &);

class RndBitmap { // 0x1c
public:
    enum AlphaFlag {
        kGrayscaleAlpha = 0,
        kGrayscaleWhite = 1,
        kTransparentBlack = 2,
    };

    // mOrder notes:
    // mOrder & 0x38 indicates DXT usage
    // mOrder & 1 would indicate RGBA, as opposed to BGRA
    // mOrder being 0 also seems to be RGBA?
    // mOrder & 0x40 or mOrder & 0x80 would mean white (R=G=B=255)
    enum Order {
        kDXT1 = 8
    };

    /** The bitmap's width in pixels. */
    u16 mWidth; // 0x0
    /** The bitmap's height in pixels. */
    u16 mHeight; // 0x2
    /** The number of bytes in memory that make up one row of the image. */
    u16 mRowBytes; // 0x4
    /** The number of bits per pixel, aka color depth. */
    u8 mBpp; // 0x6
    /** The ordering of the color bytes in this bitmap (e.g. RGBA, BGRA) - determined with
     * masking */
    unsigned int mOrder; // 0x8
    /** The pixels that makes up this image. */
    u8 *mPixels; // 0xc
    /** The colors of this image's color palette. */
    u8 *mPalette; // 0x10
    /** The contiguous series of bytes that make up the bitmap's palette and pixels */
    u8 *mBuffer; // 0x14
    /** The next mip after this one, used to create a mipmap. */
    RndBitmap *mMip; // 0x18

    RndBitmap() : mBuffer(0), mMip(0) { Reset(); }
    ~RndBitmap() { Reset(); }

    /** Read the metadata (not the actual buffer contents) from the BinStream.
     * @param [out] numMips The number of mips this RndBitmap has in its mipmap.
     */
    BinStream &LoadHeader(BinStream &, u8 &numMips); // private
    /** Write the metadata (not the actual buffer contents) to the BinStream. */
    BinStream &SaveHeader(BinStream &) const; // private
    /** Allocate the byte buffer and mark where the pixels begin and the color palette
     * begins. */
    void AllocateBuffer(); // private
    /** Get the number of colors in this RndBitmap's color palette. */
    int NumPaletteColors() const;
    /** Get the number of mips this RndBitmap has in its mipmap. */
    int NumMips() const;
    /** Get the number of bytes in memory that make up the pixels of this RndBitmap. */
    int PixelBytes() const;
    /** Get the number of bytes in memory that make up this RndBitmap's color palette. */
    int PaletteBytes() const;
    /** Get the index of the color in the palette that most closely matches the supplied
     * RGBA values.
     * @param [in] r, g, b, a The input RGBA values.
     * @returns The index of the closest matching color in the color palette.
     */
    unsigned char
    NearestColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) const;
    /** Given the buffer of color bytes, get the appropriate RGBA color value based on the
     * current color order/format.
     * @param [in] buffer The buffer of color bytes (could be palette, pixels, or
     * otherwise)
     * @param [out] r, g, b, a The resulting RGBA color values.
     */
    void ConvertColor(
        const unsigned char *buffer,
        unsigned char &r,
        unsigned char &g,
        unsigned char &b,
        unsigned char &a
    ) const;
    /** Place a supplied RGBA value into the buffer of color bytes based on the current
     * color order/format.
     * @param [in] r, g, b, a The RGBA color value to place into the buffer.
     * @param [in] buffer The buffer of color bytes (could be palette, pixels, or
     * otherwise)
     */
    void ConvertColor(
        unsigned char r,
        unsigned char g,
        unsigned char b,
        unsigned char a,
        unsigned char *buffer
    ) const;
    /** Clear the buffer and reset metadata to default values. */
    void Reset();
    /** Create this RndBitmap using the supplied parameters.
     * @param [in] bm Another RndBitmap to copy the width and height from.
     * @param [in] bpp The bitmap's bpp.
     * @param [in] order The bitmap's format (e.g. RGBA).
     * @param [in] palette The bitmap's color palette bytes.
     */
    void Create(const RndBitmap &bm, int bpp, int order, void *palette);
    /** Create this RndBitmap using the supplied parameters.
     * @param [in] width The bitmap's width.
     * @param [in] height The bitmap's height.
     * @param [in] rowlen The length of one row of this bitmap.
     * @param [in] bpp The bitmap's bpp.
     * @param [in] order The bitmap's format (e.g. RGBA).
     * @param [in] palette The bitmap's color palette bytes.
     * @param [in] pixels The bitmap's pixel bytes.
     * @param [in] buf The bitmap's byte buffer.
     */
    void Create(
        int width,
        int height,
        int rowlen,
        int bpp,
        int order,
        void *palette,
        void *pixels,
        void *buf
    );
    /** Create this RndBitmap using the supplied parameters.
     * @param [in] buffer The bitmap's byte buffer.
     */
    void Create(void *buffer);
    /** Get the color of the pixel at the supplied coordinates.
     * @param [in] x, y The coordinates of the pixel in the image. (0, 0) is the top left.
     * @param [out] r, g, b, a The corresponding color's RGBA values.
     */
    void PixelColor(int x, int y, u8 &r, u8 &g, u8 &b, u8 &a) const;
    /** Get the supplied number color in the color palette.
     * @param [in] idx The zero-indexed number color of the palette to get.
     * @param [out] r, g, b, a The corresponding color's RGBA values.
     */
    void
    PaletteColor(int, unsigned char &, unsigned char &, unsigned char &, unsigned char &)
        const;
    int PixelOffset(int, int, bool &) const;
    unsigned char PixelIndex(int, int) const;
    void SetPixelIndex(int, int, unsigned char);
    void ConvertToAlpha();
    void SetAlpha(AlphaFlag);
    void SetPreMultipliedAlpha();
    void SelfMip();
    /** Generate a mipmap for this RndBitmap using its current member info. */
    void GenerateMips();
    /** Detach the next mip (and subsequent mips) from this RndBitmap.
     * @returns The detached mip.
     */
    RndBitmap *DetachMip();
    /** Set the mipmap to that of the supplied RndBitmap.
     * @param [in] bm The supplied RndBitmap.
     */
    void SetMip(RndBitmap *bm);
    unsigned char ColumnNonTransparent(int, int, int, int *);
    /** Load the RndBitmap from the supplied BinStream and check its metadata.
     * @param [in] bs The supplied BinStream.
     * @param [in] w The max width the loaded RndBitmap should be.
     * @param [in] h The max height the loaded RndBitmap should be.
     * @returns True if the RndBitmap was able to be loaded safely, false if not.
     */
    bool LoadSafely(BinStream &bs, int w, int h);
    void Blt(const RndBitmap &, int, int, int, int, int, int);
    /** Determine if this RndBitmap and the supplied RndBitmap have identical pixel
     * formats. */
    bool SamePixelFormat(const RndBitmap &) const;
    /** Determine if this RndBitmap and the supplied RndBitmap have identical color
     * palettes. */
    bool SamePaletteColors(const RndBitmap &) const;
    /** Determine if the image is translucent (i.e. alpha value of any pixel < 253) */
    bool IsTranslucent() const;
    /** Set the supplied number color in the color palette to the desired RGBA values.
     * @param [in] idx The zero-indexed number color of the palette to set.
     * @param [in] r, g, b, a The desired RGBA values.
     */
    void SetPaletteColor(
        int idx, unsigned char r, unsigned char g, unsigned char b, unsigned char a
    );
    /** Set the pixel at the supplied coordinates to the desired RGBA values.
     * @param [in] x, y The coordinates of the pixel in the image. (0, 0) is the top left.
     * @param [in] r, g, b, a The desired RGBA values.
     */
    void SetPixelColor(
        int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a
    );
    /** Load a raw .bmp contained in a BinStream into this RndBitmap.
     * @param [in] bs The BinStream.
     * @returns True if the .bmp was successfully loaded, false if not.
     */
    bool LoadBmp(BinStream *bs);
    /** Load a Device-Independent Bitmap contained in a BinStream, into this RndBitmap.
     * @param [in] bs The BinStream.
     * @param [in] offbits The offset in the BinStream where the actual bitmap image data
     * is found.
     * @returns True if the .bmp was successfully loaded, false if not.
     */
    bool LoadDIB(BinStream *bs, unsigned int offbits);
    /** Load a raw .bmp contained in a BinStream into this RndBitmap.
     * @param [in] filename The name of the bitmap.
     * @param [in] wantMips If true, unless "_nomip" is in the filename, generate a
     * mipmap.
     * @param [in] noAlpha If true, don't process any alpha flags.
     */
    bool LoadBmp(const char *filename, bool wantMips, bool noAlpha);
    /** Process AlphaFlags based on the bitmap's name.
     * @param [in] filename The name of the bitmap.
     * @param [in] wantMips If true, unless "_nomip" is in the filename, generate a
     * mipmap.
     */
    bool ProcessFlags(const char *filename, bool wantMips);
    /** Does nothing, fails and returns false.
     * Presumably this would save this RndBitmap to a raw .bmp file,
     * and the input param would be the desired filename.
     */
    bool SaveBmp(const char *) const;
    /** Saves this RndBitmap to a BinStream.
     * The bytes make up a raw .bmp file.
     */
    bool SaveBmp(BinStream *) const;
    /** Saves this RndBitmap to a BinStream.
     * The bytes make up the file and info header of a .bmp file.
     */
    void SaveBmpHeader(BinStream *) const;
    /** Saves this RndBitmap to a BinStream.
     * The bytes make up the actual pixels part of the .bmp file.
     */
    void SaveBmpPixels(BinStream *) const;
    void DxtColor(
        int x,
        int y,
        unsigned char &r,
        unsigned char &g,
        unsigned char &b,
        unsigned char &a
    ) const;
    /** Get the actual offset in memory corresponding to the index of the color palette.
     * @param [in] idx The zero-indexed number color of the palette to retrieve the memory
     * address of.
     */
    int PaletteOffset(int idx) const; // private
    unsigned char RowNonTransparent(int, int, int, int *);

    /** Saves this RndBitmap into a BinStream. */
    void Save(BinStream &) const;
    /** Loads this RndBitmap from a BinStream. */
    void Load(BinStream &);

    int Width() const { return mWidth; }
    int Height() const { return mHeight; }
    u32 Order() const { return mOrder; }
    int RowBytes() const { return mRowBytes; }
    int Bpp() const { return mBpp; }
    u8 *Palette() const { return mPalette; }
    u8 *Pixels() const { return mPixels; }
    RndBitmap *nextMip() const { return mMip; }

    NEW_OVERLOAD
    DELETE_OVERLOAD
};

inline BinStream &operator>>(BinStream &bs, RndBitmap &bm) {
    bm.Load(bs);
    return bs;
}