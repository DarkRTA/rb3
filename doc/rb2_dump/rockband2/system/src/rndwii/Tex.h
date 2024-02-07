/*
    Compile unit: C:\rockband2\system\src\rndwii\Tex.h
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8055D4B4 -> 0x8055E078
*/
// Range: 0x8055D4B4 -> 0x8055D52C
static int OrderFromFormat() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8055D52C -> 0x8055DD50
void WiiTex::SyncBitmap(class WiiTex * const this /* r27 */) {
    // Local variables
    unsigned char isRenderTarget; // r5
    unsigned char isScreenTexture; // r6
    unsigned char isMovieTexture; // r29
    unsigned char isRegular; // r28
    unsigned char isDepthTexture; // r0
    const struct _GXRenderModeObj & mode; // r0
    int numBytes; // r31
    int palBytes; // r26
    class RndBitmap * mip; // r29
    int i; // r25
    int size; // r0
    unsigned char * p; // r24
    int numAlphaBytes; // r28

    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
    // -> class WiiRnd TheWiiRnd;
}

// Range: 0x8055DD50 -> 0x8055DEBC
void WiiTex::LockBitmap(class WiiTex * const this /* r26 */, class RndBitmap & bm /* r27 */, int flags /* r28 */) {
    // Local variables
    unsigned char bWriting; // r3
    int order; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8055DEBC -> 0x8055E038
void WiiTex::SetType(class WiiTex * const this /* r29 */, class Symbol & WiiTex /* r30 */) {
    // Local variables
    class DataArray * def; // r4

    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
    // -> class DataArray * types;
    // -> class Symbol name;
}

// Range: 0x8055E038 -> 0x8055E078
class Symbol WiiTex::ClassName() {
    // References
    // -> class Symbol name;
}


