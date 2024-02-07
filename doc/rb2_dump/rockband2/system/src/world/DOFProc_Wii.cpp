/*
    Compile unit: C:\rockband2\system\src\world\DOFProc_Wii.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80469A30 -> 0x8046A638
*/
class DataArray * types; // size: 0x4, address: 0x80A528A0
// Range: 0x80469A30 -> 0x80469C08
void * WiiDOFProc::WiiDOFProc(class WiiDOFProc * const this /* r31 */) {
    // Local variables
    int height; // r30

    // References
    // -> class WiiRnd TheWiiRnd;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndTex;
    // -> class Symbol name;
    // -> class Rnd & TheRnd;
    // -> struct [anonymous] __vt__10WiiDOFProc;
}

// Range: 0x80469C08 -> 0x80469CE4
void * WiiDOFProc::~WiiDOFProc(class WiiDOFProc * const this /* r30 */) {
    // References
    // -> class Rnd & TheRnd;
    // -> struct [anonymous] __vt__10WiiDOFProc;
}

// Range: 0x80469CE4 -> 0x80469D04
void WiiDOFProc::Set() {}

// Range: 0x80469D04 -> 0x80469D10
void WiiDOFProc::UnSet() {}

static class Timer * _t; // size: 0x4, address: 0x80A528A8
// Range: 0x80469D10 -> 0x8046A634
void WiiDOFProc::EndWorld(class WiiDOFProc * const this /* r30 */) {
    // Local variables
    class AutoTimer _at; // r1+0x18
    float q; // f1
    float farz; // f31
    class WiiOrthoProj _ortho; // r1+0x40
    unsigned char c; // r3
    struct _GXColor white; // r1+0x14
    float texmtx[2][4]; // r1+0x20

    // References
    // -> class WiiRnd TheWiiRnd;
    // -> static class Timer * _t;
}

// Range: 0x8046A634 -> 0x8046A638
void WiiDOFProc::DoPost() {}

struct {
    // total size: 0x98
} __vt__10WiiDOFProc; // size: 0x98, address: 0x808F1008
struct {
    // total size: 0x8
} __RTTI__10WiiDOFProc; // size: 0x8, address: 0x808F10D0
class WiiSplitPostProc : public PostProcessor {
    // total size: 0x18
    class RndTex * mWorldColorTex; // offset 0x4, size 0x4
    class RndTex * mWorldDepthTex; // offset 0x8, size 0x4
    class RndTex * mFinalTex; // offset 0xC, size 0x4
    unsigned char mWorldDrawn; // offset 0x10, size 0x1
    unsigned char mFinalDrawn; // offset 0x11, size 0x1
    void * mDummyTex; // offset 0x14, size 0x4
};

