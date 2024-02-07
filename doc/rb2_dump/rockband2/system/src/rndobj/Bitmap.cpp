/*
    Compile unit: C:\rockband2\system\src\rndobj\Bitmap.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8046EFE8 -> 0x8047289C
*/
// Range: 0x8046EFE8 -> 0x8046F110
class BinStream & RndBitmap::LoadHeader(class RndBitmap * const this /* r29 */, class BinStream & d /* r30 */, unsigned char & numMips /* r31 */) {
    // Local variables
    unsigned char rev; // r1+0x9
    unsigned char order; // r1+0x8
    unsigned char pad[19]; // r1+0x20
    unsigned char pad[19]; // r1+0xC
}

// Range: 0x8046F110 -> 0x8046F180
class BinStream & __rs(class BinStream & d /* r30 */, struct tagBITMAPFILEHEADER & header /* r31 */) {}

// Range: 0x8046F180 -> 0x8046F208
class BinStream & __ls(class BinStream & d /* r31 */) {}

// Range: 0x8046F208 -> 0x8046F2E8
class BinStream & __rs(class BinStream & d /* r30 */, struct tagBITMAPINFOHEADER & info /* r31 */) {}

// Range: 0x8046F2E8 -> 0x8046F418
class BinStream & __ls(class BinStream & d /* r31 */) {}

// Range: 0x8046F418 -> 0x8046F438
int RndBitmap::NumMips() {
    // Local variables
    const class RndBitmap * bm; // r3
    int num; // r4
}

// Range: 0x8046F438 -> 0x8046F448
int RndBitmap::PixelBytes() {}

// Range: 0x8046F448 -> 0x8046F484
int RndBitmap::PaletteBytes() {}

// Range: 0x8046F484 -> 0x8046F564
unsigned char RndBitmap::NearestColor(const class RndBitmap * const this /* r25 */, unsigned char r /* r26 */, unsigned char g /* r27 */, unsigned char b /* r28 */, unsigned char a /* r29 */) {
    // Local variables
    int ir; // r0
    int ig; // r0
    int ib; // r0
    int ia; // r0
    int nearI; // r31
    int nearDiff; // r30
    int i; // r21
    unsigned char pr; // r1+0xB
    unsigned char pg; // r1+0xA
    unsigned char pb; // r1+0x9
    unsigned char pa; // r1+0x8
    int diff; // r0
}

// Range: 0x8046F564 -> 0x8046F74C
void RndBitmap::ConvertColor(const class RndBitmap * const this /* r27 */, unsigned char & r /* r29 */, unsigned char & g /* r30 */, unsigned char & b /* r31 */, unsigned char & a /* r28 */) {
    // Local variables
    unsigned short p; // r0
}

// Range: 0x8046F74C -> 0x8046F884
void RndBitmap::ConvertColor(unsigned char * color /* r31 */) {
    // Local variables
    unsigned short * p; // r0
}

// Range: 0x8046F884 -> 0x8046F93C
void RndBitmap::Reset(class RndBitmap * const this /* r30 */) {}

// Range: 0x8046F93C -> 0x8046FADC
void RndBitmap::Create(class RndBitmap * const this /* r27 */, const class RndBitmap & bm /* r28 */, int bpp /* r29 */, int order /* r30 */, void * palette /* r31 */) {
    // Local variables
    int i; // r31
    unsigned char r; // r1+0x13
    unsigned char g; // r1+0x12
    unsigned char b; // r1+0x11
    unsigned char a; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8046FADC -> 0x8046FB68
void RndBitmap::AllocateBuffer(class RndBitmap * const this /* r30 */) {
    // Local variables
    int bufferBytes; // r3
}

// Range: 0x8046FB68 -> 0x8046FDB8
void RndBitmap::Create(class RndBitmap * const this /* r23 */, int width /* r24 */, int height /* r25 */, int rowBytes /* r26 */, int bpp /* r27 */, int order /* r28 */, void * palette /* r29 */, void * pixels /* r30 */, void * buffer /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8046FDB8 -> 0x8047001C
void RndBitmap::Create(class RndBitmap * const this /* r30 */, void * buffer /* r25 */) {
    // Local variables
    unsigned char numMips; // r1+0x10
    class BufStream stream; // r1+0x14
    unsigned char * buf; // r31
    int bytes; // r28
    class RndBitmap * to; // r27
    int width; // r26
    int height; // r25

    // References
    // -> class Debug TheDebug;
}

static unsigned char bytes02[4][16]; // size: 0x40, address: 0x808F1AE0
static unsigned char bytes13[4][16]; // size: 0x40, address: 0x808F1B20
static unsigned char hbytes02[4][32]; // size: 0x80, address: 0x808F1B60
static unsigned char hbytes13[4][32]; // size: 0x80, address: 0x808F1BE0
// Range: 0x8047001C -> 0x8047037C
int RndBitmap::PixelOffset() {
    // Local variables
    int rb; // r0
    int addr; // r3
    int offset; // r4
    int col; // r9
    int x2; // r10
    int y2; // r11
    int rb; // r0
    int addr; // r3
    int offset; // r5
    int kTexelsPerTile; // r31
    unsigned int offset; // r30
    int x_; // r7
    int y_; // r0

    // References
    // -> static unsigned char hbytes02[4][32];
    // -> static unsigned char hbytes13[4][32];
    // -> static unsigned char bytes02[4][16];
    // -> static unsigned char bytes13[4][16];
}

// Range: 0x8047037C -> 0x804703E4
unsigned char RndBitmap::PixelIndex(const class RndBitmap * const this /* r31 */) {
    // Local variables
    unsigned char half; // r1+0x8
    unsigned char * color; // r0
}

// Range: 0x804703E4 -> 0x80470468
void RndBitmap::SetPixelIndex(class RndBitmap * const this /* r30 */, unsigned char i /* r31 */) {
    // Local variables
    unsigned char half; // r1+0x8
    unsigned char * color; // r0
}

// Range: 0x80470468 -> 0x80470514
int RndBitmap::HighestIndex(const class RndBitmap * const this /* r28 */) {
    // Local variables
    int highest; // r31
    int y; // r30
    int x; // r29
    int i; // r0
}

// Range: 0x80470514 -> 0x804706A4
void RndBitmap::ConvertTo8Bpp(class RndBitmap * const this /* r29 */) {
    // Local variables
    class RndBitmap bm; // r1+0x10
    int y; // r31
    int x; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804706A4 -> 0x8047075C
void RndBitmap::ConvertToAlpha(class RndBitmap * const this /* r30 */) {
    // Local variables
    class RndBitmap bm; // r1+0x8
}

// Range: 0x8047075C -> 0x80470A10
unsigned char RndBitmap::SetAlpha(class RndBitmap * const this /* r30 */, const class RndBitmap & bm /* r31 */) {
    // Local variables
    int y; // r29
    int x; // r28
    unsigned char r; // r1+0x11
    unsigned char g; // r1+0x10
    unsigned char b; // r1+0xF
    unsigned char a; // r1+0xE
    unsigned char foo; // r1+0xD
    int highest; // r28
    int alphaHighest; // r29
    int i; // r27
    unsigned char r; // r1+0xC
    unsigned char g; // r1+0xB
    unsigned char b; // r1+0xA
    unsigned char a; // r1+0x9
    unsigned char foo; // r1+0x8
    int j; // r26
    int y; // r26
    int x; // r27
    int i; // r29
    int ai; // r0

    // References
    // -> class Debug TheDebug;
}

// Range: 0x80470A10 -> 0x80470C14
void RndBitmap::SetAlpha(class RndBitmap * const this /* r30 */, enum AlphaFlag ext /* r31 */) {
    // Local variables
    int i; // r29
    unsigned char r; // r1+0xF
    unsigned char g; // r1+0xE
    unsigned char b; // r1+0xD
    unsigned char a; // r1+0xC
    int y; // r29
    int x; // r28
    unsigned char r; // r1+0xB
    unsigned char g; // r1+0xA
    unsigned char b; // r1+0x9
    unsigned char a; // r1+0x8
}

// Range: 0x80470C14 -> 0x80470CB4
static void PreMultiplyAlpha() {
    // Local variables
    float alpha; // f1
}

// Range: 0x80470CB4 -> 0x80470E5C
void RndBitmap::SetPreMultipliedAlpha(class RndBitmap * const this /* r31 */) {
    // Local variables
    int i; // r30
    unsigned char r; // r1+0xF
    unsigned char g; // r1+0xE
    unsigned char b; // r1+0xD
    unsigned char a; // r1+0xC
    int y; // r30
    int x; // r29
    unsigned char r; // r1+0xB
    unsigned char g; // r1+0xA
    unsigned char b; // r1+0x9
    unsigned char a; // r1+0x8

    // References
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x80470E5C -> 0x80470FB0
void RndBitmap::SelfMip(class RndBitmap * const this /* r29 */) {
    // Local variables
    int offset; // r31
    int pixelBytes; // r30
    int levels; // r27
    class RndBitmap * bm; // r26
    int i; // r25
}

// Range: 0x80470FB0 -> 0x80471204
void RndBitmap::GenerateMips(class RndBitmap * const this /* r22 */) {
    // Local variables
    int y; // r28
    int x; // r27
    int rt; // r26
    int gt; // r25
    int bt; // r24
    int at; // r23
    unsigned char r; // r1+0x13
    unsigned char g; // r1+0x12
    unsigned char b; // r1+0x11
    unsigned char a; // r1+0x10
}

struct tagBITMAPFILEHEADER {
    // total size: 0xC
    unsigned int bfSize; // offset 0x0, size 0x4
    unsigned short bfReserved1; // offset 0x4, size 0x2
    unsigned short bfReserved2; // offset 0x6, size 0x2
    unsigned int bfOffBits; // offset 0x8, size 0x4
};
// Range: 0x80471204 -> 0x804712AC
unsigned char RndBitmap::LoadBmp(class RndBitmap * const this /* r30 */, class BinStream * file /* r31 */) {
    // Local variables
    unsigned short type; // r1+0x8
    struct tagBITMAPFILEHEADER header; // r1+0xC

    // References
    // -> class Debug TheDebug;
}

struct tagBITMAPINFOHEADER {
    // total size: 0x28
    unsigned int biSize; // offset 0x0, size 0x4
    int biWidth; // offset 0x4, size 0x4
    int biHeight; // offset 0x8, size 0x4
    unsigned short biPlanes; // offset 0xC, size 0x2
    unsigned short biBitCount; // offset 0xE, size 0x2
    unsigned int biCompression; // offset 0x10, size 0x4
    unsigned int biSizeImage; // offset 0x14, size 0x4
    int biXPelsPerMeter; // offset 0x18, size 0x4
    int biYPelsPerMeter; // offset 0x1C, size 0x4
    unsigned int biClrUsed; // offset 0x20, size 0x4
    unsigned int biClrImportant; // offset 0x24, size 0x4
};
// Range: 0x804712AC -> 0x8047157C
unsigned char RndBitmap::LoadDIB(class RndBitmap * const this /* r23 */, class BinStream * file /* r24 */, unsigned int bfOffBits /* r25 */) {
    // Local variables
    struct tagBITMAPINFOHEADER info; // r1+0x10
    int palLen; // r30
    int rowBytes; // r29
    int pixelLen; // r28
    unsigned char * buffer; // r31
    unsigned char * pal; // r27
    unsigned char * pixels; // r26
    int y; // r25
    unsigned char * p; // r4

    // References
    // -> class Debug TheDebug;
}

// Range: 0x8047157C -> 0x80471828
unsigned char RndBitmap::LoadBmp(class RndBitmap * const this /* r26 */, const char * path /* r27 */, unsigned char addAlpha /* r28 */, unsigned char wantMips /* r29 */) {
    // Local variables
    char base[512]; // r1+0x230
    char str[512]; // r1+0x30
    class RndBitmap bm; // r1+0x8
}

// Range: 0x80471828 -> 0x804718C8
void RndBitmap::SaveBmp(const class RndBitmap * const this /* r29 */, const char * path /* r30 */) {}

// Range: 0x804718C8 -> 0x80471AAC
void RndBitmap::SaveBmp(const class RndBitmap * const this /* r30 */, class BinStream * file /* r31 */) {
    // Local variables
    struct tagBITMAPFILEHEADER header; // r1+0xC
    struct tagBITMAPINFOHEADER info; // r1+0x18
    int y; // r28
    unsigned char * pixels; // r29
    unsigned char * p; // r27
    unsigned char c; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80471AAC -> 0x80471B60
unsigned char RndBitmap::IsTranslucent(const class RndBitmap * const this /* r29 */) {
    // Local variables
    int y; // r31
    int x; // r30
    unsigned char r; // r1+0xB
    unsigned char g; // r1+0xA
    unsigned char b; // r1+0x9
    unsigned char a; // r1+0x8
}

// Range: 0x80471B60 -> 0x80471BC4
void RndBitmap::SetAlphaDxt(class RndBitmap * const this /* r29 */, class RndBitmap * bm /* r30 */) {}

// Range: 0x80471BC4 -> 0x80471C98
unsigned char RndBitmap::SamePaletteColors(const class RndBitmap * const this /* r28 */, const class RndBitmap & bm /* r29 */) {
    // Local variables
    int i; // r31
    unsigned int a; // r1+0xC
    unsigned int b; // r1+0x8
    unsigned char * pa; // r5
    unsigned char * pb; // r30
}

// Range: 0x80471C98 -> 0x80471CE4
unsigned char RndBitmap::SamePixelFormat() {}

// Range: 0x80471CE4 -> 0x80472088
void RndBitmap::Blt(class RndBitmap * const this /* r23 */, const class RndBitmap & bm /* r24 */, int dX /* r25 */, int dY /* r26 */, int sX /* r27 */, int sY /* r28 */, int width /* r29 */, int height /* r30 */) {
    // Local variables
    int len; // r31
    unsigned char map[256]; // r1+0x10
    int i; // r31
    unsigned char r; // r1+0xF
    unsigned char g; // r1+0xE
    unsigned char b; // r1+0xD
    unsigned char a; // r1+0xC
    int dX0; // r31
    int sX0; // r22
    int width0; // r21
    int dX0; // r21
    int sX0; // r22
    int width0; // r31
    unsigned char r; // r1+0xB
    unsigned char g; // r1+0xA
    unsigned char b; // r1+0x9
    unsigned char a; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80472088 -> 0x80472134
void RndBitmap::PixelColor(const class RndBitmap * const this /* r27 */, unsigned char & r /* r28 */, unsigned char & g /* r29 */, unsigned char & b /* r30 */, unsigned char & a /* r31 */) {
    // Local variables
    unsigned char half; // r1+0x8
    unsigned char * color; // r0
}

// Range: 0x80472134 -> 0x804721E0
void RndBitmap::SetPixelColor(class RndBitmap * const this /* r25 */, int x /* r26 */, int y /* r27 */, unsigned char r /* r28 */, unsigned char g /* r29 */, unsigned char b /* r30 */, unsigned char a /* r31 */) {
    // Local variables
    unsigned char half; // r1+0x8
    unsigned char * color; // r0
}

// Range: 0x804721E0 -> 0x80472368
static void DecodeDxtColor(int x /* r0 */) {
    // Local variables
    unsigned short c0; // r31
    unsigned short c1; // r30
    int i; // r3
    unsigned char r0; // r29
    unsigned char r1; // r28
    unsigned char g0; // r0
    unsigned char g1; // r4
    unsigned char b0; // r5
    unsigned char b1; // r11
    unsigned int u; // r6
    unsigned int v; // r3
}

// Range: 0x80472368 -> 0x8047256C
void RndBitmap::DxtColor(const class RndBitmap * const this /* r22 */, int x /* r23 */, int y /* r24 */, unsigned char & r /* r25 */, unsigned char & g /* r26 */, unsigned char & b /* r27 */, unsigned char & a /* r28 */) {
    // Local variables
    int dxt; // r30
    int W; // r0
    int X; // r3
    int Y; // r4
    int tile_offs; // r29
    int XWiiTile; // r8
    int YWiiTile; // r9
    int iWiiTileOffset; // r30
    unsigned char unused; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8047256C -> 0x804725AC
int RndBitmap::PaletteOffset() {}

// Range: 0x804725AC -> 0x80472614
void RndBitmap::PaletteColor(const class RndBitmap * const this /* r27 */, unsigned char & r /* r28 */, unsigned char & g /* r29 */, unsigned char & b /* r30 */, unsigned char & a /* r31 */) {}

// Range: 0x80472614 -> 0x8047267C
void RndBitmap::SetPaletteColor(class RndBitmap * const this /* r27 */, unsigned char r /* r28 */, unsigned char g /* r29 */, unsigned char b /* r30 */, unsigned char a /* r31 */) {}

// Range: 0x8047267C -> 0x8047289C
void RndBitmap::Load(class RndBitmap * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    unsigned char numMips; // r1+0x10
    class RndBitmap * to; // r27
    int width; // r26
    int height; // r25
}


