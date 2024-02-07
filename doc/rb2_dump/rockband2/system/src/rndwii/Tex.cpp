/*
    Compile unit: C:\rockband2\system\src\rndwii\Tex.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8055CDD0 -> 0x8055D4B4
*/
class DataArray * types; // size: 0x4, address: 0x80A540B8
// Range: 0x8055CDD0 -> 0x8055CE44
void * WiiTex::WiiTex(class WiiTex * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__6WiiTex;
}

// Range: 0x8055CE44 -> 0x8055CEC0
void * WiiTex::~WiiTex(class WiiTex * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__6WiiTex;
}

// Range: 0x8055CEC0 -> 0x8055CEC4
void WiiTex::PresyncBitmap() {}

// Range: 0x8055CEC4 -> 0x8055CFA8
void WiiTex::DeleteSurface(class WiiTex * const this /* r30 */) {}

// Range: 0x8055CFA8 -> 0x8055D01C
void WiiTex::UnlockBitmap(class WiiTex * const this /* r31 */) {
    // Local variables
    int iNumBytes; // r0
}

// Range: 0x8055D01C -> 0x8055D030
void * WiiTex::GetMovieLoadingFramePtr() {}

// Range: 0x8055D030 -> 0x8055D0AC
void WiiTex::MovieSwapFrames(class WiiTex * const this /* r31 */) {
    // Local variables
    int numBytes; // r0
}

static enum _GXTexWrapMode op[4]; // size: 0x10, address: 0x809194E8
// Range: 0x8055D0AC -> 0x8055D150
void WiiTex::SetTexWrapMode(class WiiTex * const this /* r27 */, enum TexWrap wrap_s /* r28 */, enum TexWrap wrap_t /* r29 */) {
    // References
    // -> static enum _GXTexWrapMode op[4];
}

// Range: 0x8055D150 -> 0x8055D22C
void WiiTex::Select(class WiiTex * const this /* r30 */, enum _GXTexMapID id /* r31 */) {
    // Local variables
    const struct _GXRenderModeObj & mode; // r0
    unsigned long tlut; // r0

    // References
    // -> class WiiRnd TheWiiRnd;
}

// Range: 0x8055D22C -> 0x8055D25C
void WiiTex::CopyContent() {}

// Range: 0x8055D25C -> 0x8055D294
void WiiTex::CopyFullScreen() {
    // References
    // -> class WiiRnd TheWiiRnd;
}

// Range: 0x8055D294 -> 0x8055D4B4
void WiiTex::CopyFromFB(class WiiTex * const this /* r31 */, int srcX /* r24 */, int srcY /* r25 */, int srcWidth /* r26 */, int srcHeight /* r27 */, unsigned char clear /* r28 */, unsigned char mip /* r29 */) {
    // Local variables
    struct _GXRenderModeObj mode; // r1+0x10

    // References
    // -> class WiiRnd TheWiiRnd;
    // -> class Rnd & TheRnd;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x8C
} __vt__6WiiTex; // size: 0x8C, address: 0x80919518

