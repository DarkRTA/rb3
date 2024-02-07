/*
    Compile unit: C:\rockband2\system\src\rndwii\SplitPostProc.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8055B9D0 -> 0x8055CB30
*/
// Range: 0x8055B9D0 -> 0x8055BAD8
void * WiiSplitPostProc::~WiiSplitPostProc(class WiiSplitPostProc * const this /* r29 */) {
    // References
    // -> class Rnd & TheRnd;
    // -> struct [anonymous] __vt__16WiiSplitPostProc;
}

static class Timer * _t; // size: 0x4, address: 0x80A540A0
// Range: 0x8055BAD8 -> 0x8055BBEC
void WiiSplitPostProc::BeginWorld(class WiiSplitPostProc * const this /* r31 */) {
    // Local variables
    class AutoTimer _at; // r1+0xC

    // References
    // -> class WiiRnd TheWiiRnd;
    // -> static class Timer * _t;
}

static class Timer * _t; // size: 0x4, address: 0x80A540A8
// Range: 0x8055BBEC -> 0x8055BCA4
void WiiSplitPostProc::EndWorld() {
    // Local variables
    class AutoTimer _at; // r1+0xC

    // References
    // -> static class Timer * _t;
}

static class Timer * _t; // size: 0x4, address: 0x80A540B0
// Range: 0x8055BCA4 -> 0x8055BE80
void WiiSplitPostProc::DoPost(class WiiSplitPostProc * const this /* r31 */) {
    // Local variables
    class AutoTimer _at; // r1+0xC

    // References
    // -> class WiiRnd TheWiiRnd;
    // -> static class Timer * _t;
}

// Range: 0x8055BE80 -> 0x8055C0D0
void WiiSplitPostProc::DrawWorldTex(class WiiSplitPostProc * const this /* r31 */) {
    // Local variables
    class WiiOrthoProj _ortho; // r1+0x8
    class WiiTex * tex; // r0

    // References
    // -> class WiiRnd TheWiiRnd;
    // -> unsigned char sCurrentZCompLoc;
    // -> class RndCam * sCurrent;
}

// Range: 0x8055C0D0 -> 0x8055C8BC
void WiiSplitPostProc::DrawFinalTex(class WiiSplitPostProc * const this /* r30 */) {
    // Local variables
    class WiiOrthoProj _ortho; // r1+0x70
    class RndPostProc * pp; // r29
    class Transform colorxfm; // r1+0x90
    float currMod; // f0
    class Color hmxoverflow; // r1+0x60
    class Color hmxscale; // r1+0x50
    struct _GXColor offset; // r1+0x44
    unsigned char subtract; // r31
    enum _GXTevStageID next; // r28

    // References
    // -> class WiiRnd TheWiiRnd;
    // -> class RndCam * sCurrent;
}

// Range: 0x8055C8BC -> 0x8055C9CC
void WiiSplitPostProc::ClearAlpha(class WiiSplitPostProc * const this /* r31 */) {
    // References
    // -> class WiiRnd TheWiiRnd;
    // -> class Rnd & TheRnd;
}

// Range: 0x8055C9CC -> 0x8055CB30
void WiiSplitPostProc::DrawWorldColorTex(class WiiSplitPostProc * const this /* r31 */) {
    // Local variables
    class WiiOrthoProj _ortho; // r1+0x8

    // References
    // -> class WiiRnd TheWiiRnd;
    // -> class RndCam * sCurrent;
}

struct {
    // total size: 0x18
} __vt__16WiiSplitPostProc; // size: 0x18, address: 0x80919250
struct {
    // total size: 0x8
} __RTTI__16WiiSplitPostProc; // size: 0x8, address: 0x80919288

