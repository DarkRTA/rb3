/*
    Compile unit: C:\rockband2\system\src\movie\Bink_WiiTextures.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803BFD70 -> 0x803C1488
*/
// Range: 0x803BFD70 -> 0x803BFDB0
void Free_Bink_textures(struct BINKTEXTURESET * set_textures /* r31 */) {}

// Range: 0x803BFDB0 -> 0x803BFDC4
static unsigned int nextpow2() {}

// Range: 0x803BFDC4 -> 0x803BFE38
static void fill_offset_buffer() {
    // Local variables
    unsigned int finalwidth; // r6
    int srcx; // r7
    int srcy; // r8
    int x; // r9
    int y; // r10
    unsigned int texoffset; // r11
}

// Range: 0x803BFE38 -> 0x803BFED8
static void swizzle_offsets() {
    // Local variables
    unsigned int tilex; // r6
    unsigned int tiley; // r7
    unsigned int pitch; // r8
    unsigned int tilesw; // r9
    unsigned int tilesh; // r10
    unsigned int swizzoffset; // r11
    unsigned int row; // r12
    unsigned int sourceoffset; // r31
    unsigned int * dest; // r30
    unsigned int * src; // r5
}

enum _GXTexFmt {
    GX_TF_I4 = 0,
    GX_TF_I8 = 1,
    GX_TF_IA4 = 2,
    GX_TF_IA8 = 3,
    GX_TF_RGB565 = 4,
    GX_TF_RGB5A3 = 5,
    GX_TF_RGBA8 = 6,
    GX_TF_CMPR = 14,
    GX_CTF_R4 = 32,
    GX_CTF_RA4 = 34,
    GX_CTF_RA8 = 35,
    GX_CTF_YUVA8 = 38,
    GX_CTF_A8 = 39,
    GX_CTF_R8 = 40,
    GX_CTF_G8 = 41,
    GX_CTF_B8 = 42,
    GX_CTF_RG8 = 43,
    GX_CTF_GB8 = 44,
    GX_TF_Z8 = 17,
    GX_TF_Z16 = 19,
    GX_TF_Z24X8 = 22,
    GX_CTF_Z4 = 48,
    GX_CTF_Z8M = 57,
    GX_CTF_Z8L = 58,
    GX_CTF_Z16L = 60,
    GX_TF_A8 = 39,
};
// Range: 0x803BFED8 -> 0x803BFF5C
static int make_texture(unsigned int pitch /* r11 */, unsigned int height /* r10 */, enum _GXTexFmt format /* r0 */, struct _GXTexObj * texture /* r31 */) {}

// Range: 0x803BFF5C -> 0x803BFF68
static unsigned int divisible128() {}

// Range: 0x803BFF68 -> 0x803BFF88
static unsigned int swizz_div() {
    // Local variables
    unsigned int offwidth; // r3
}

// Range: 0x803BFF88 -> 0x803C0040
static unsigned int make_swizzler(void * data /* r26 */, struct _GXTexObj * obj /* r27 */, unsigned int * out_swidth /* r28 */, unsigned int * out_sheight /* r30 */, unsigned int sourcewidth /* r29 */) {
    // Local variables
    unsigned int offwidth; // r31
    unsigned int offsize; // r30
    unsigned char buffer[2048]; // r1+0x8
}

// Range: 0x803C0040 -> 0x803C00A4
static void do_deswizzlers(struct BINKTEXTURESET * set_textures /* r30 */, unsigned char * data /* r31 */) {}

// Range: 0x803C00A4 -> 0x803C01BC
static void calc_layout(struct BINKFRAMEBUFFERS * buffers /* r21 */, unsigned int * cRoffset /* r22 */, unsigned int * cBoffset /* r23 */, unsigned int * Aoffset /* r24 */, unsigned int * framesize /* r25 */, unsigned int * swizzlesize /* r26 */, unsigned int * YApitch /* r27 */, unsigned int * cRcBpitch /* r28 */) {
    // Local variables
    unsigned int yaheight; // r18
    unsigned int crcbheight; // r19
    unsigned int ysize; // r0
    unsigned int asize; // r0
    unsigned int crcbsize; // r0
}

static int _x; // size: 0x4, address: 0x80A51788
// Range: 0x803C01BC -> 0x803C0448
int Create_Bink_textures(struct BINKTEXTURESET * set_textures /* r28 */) {
    // Local variables
    int i; // r30
    unsigned int cRoffset; // r1+0x20
    unsigned int cBoffset; // r1+0x1C
    unsigned int Aoffset; // r1+0x18
    unsigned int framesize; // r1+0x14
    unsigned int swizzlesize; // r1+0x10
    unsigned int YApitch; // r1+0xC
    unsigned int cRcBpitch; // r1+0x8
    unsigned char * data; // r29

    // References
    // -> static int _x;
}

struct _GXColorS10 {
    // total size: 0x8
    signed short r; // offset 0x0, size 0x2
    signed short g; // offset 0x2, size 0x2
    signed short b; // offset 0x4, size 0x2
    signed short a; // offset 0x6, size 0x2
};
static struct _GXColorS10 reg0color; // size: 0x8, address: 0x80848DA0
struct _GXColor {
    // total size: 0x4
    unsigned char r; // offset 0x0, size 0x1
    unsigned char g; // offset 0x1, size 0x1
    unsigned char b; // offset 0x2, size 0x1
    unsigned char a; // offset 0x3, size 0x1
};
static struct _GXColor color0; // size: 0x4, address: 0x80A570C4
static struct _GXColor color1; // size: 0x4, address: 0x80A570C8
static struct _GXColor color2; // size: 0x4, address: 0x80A570CC
static struct _GXColor color3; // size: 0x4, address: 0x80A570D0
static float indMtx[2][3]; // size: 0x18, address: 0x80848DA8
static float id_texmtx[2][4]; // size: 0x20, address: 0x80848DC0
static float yswiz_texmtx[2][4]; // size: 0x20, address: 0x8097E100
static float crcbswiz_texmtx[2][4]; // size: 0x20, address: 0x8097E120
// Range: 0x803C0448 -> 0x803C0C1C
void Select_Bink_textures(struct BINKTEXTURESET * set_textures /* r30 */) {
    // Local variables
    float yaswizzletexU; // f3
    float yaSwizzletexV; // f4
    float crcbswizzletexU; // f5
    float crcbswizzletexV; // f0

    // References
    // -> static float id_texmtx[2][4];
    // -> static float crcbswiz_texmtx[2][4];
    // -> static float yswiz_texmtx[2][4];
    // -> static float indMtx[2][3];
    // -> static struct _GXColor color3;
    // -> static struct _GXColor color2;
    // -> static struct _GXColor color1;
    // -> static struct _GXColor color0;
    // -> static struct _GXColorS10 reg0color;
}

// Range: 0x803C0C1C -> 0x803C11A8
void Select_Bink_textures_grayscale(struct BINKTEXTURESET * set_textures /* r30 */) {
    // Local variables
    float yaswizzletexU; // f3
    float yaSwizzletexV; // f4
    float crcbswizzletexU; // f5
    float crcbswizzletexV; // f0

    // References
    // -> static float id_texmtx[2][4];
    // -> static float crcbswiz_texmtx[2][4];
    // -> static float yswiz_texmtx[2][4];
    // -> static float indMtx[2][3];
    // -> static struct _GXColor color3;
    // -> static struct _GXColor color2;
    // -> static struct _GXColor color1;
    // -> static struct _GXColor color0;
    // -> static struct _GXColorS10 reg0color;
}

// Range: 0x803C11A8 -> 0x803C1380
void JustDraw_Bink_textures(signed short x_offset /* r28 */, signed short y_offset /* r29 */) {
    // Local variables
    signed short x2; // r31
    signed short y2; // r30
}

// Range: 0x803C1380 -> 0x803C1408
void Deselect_Bink_textures() {
    // Local variables
    int i; // r31
}

// Range: 0x803C1408 -> 0x803C1488
void Draw_Bink_textures(struct BINKTEXTURESET * set_textures /* r27 */, signed short width /* r28 */, signed short height /* r29 */, signed short x_offset /* r30 */, signed short y_offset /* r31 */) {}


