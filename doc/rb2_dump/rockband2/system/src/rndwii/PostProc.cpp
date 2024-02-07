/*
    Compile unit: C:\rockband2\system\src\rndwii\PostProc.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805556FC -> 0x80557658
*/
class DataArray * types; // size: 0x4, address: 0x80A53FD8
class Symbol name; // size: 0x4, address: 0x80A53FE0
class RndTex * sWorkTex; // size: 0x4, address: 0x80A53FE4
class RndTex * sBloomTex; // size: 0x4, address: 0x80A53FE8
class RndTex * sGrayscaleTex; // size: 0x4, address: 0x80A53FEC
struct WiiHOTRing sHOTRings[25]; // size: 0x4B0, address: 0x80982280
class WiiPostProc : public RndPostProc {
    // total size: 0x1E0
    class RndTexRenderer * mHOTRenderer; // offset 0x1B0, size 0x4
    class Vector2 mNoisePos; // offset 0x1B4, size 0x8
    float mNoiseScale; // offset 0x1BC, size 0x4
    class Color mBaseHOTColor; // offset 0x1C0, size 0x10
    class Color mLastHOTColor; // offset 0x1D0, size 0x10
};
// Range: 0x805556FC -> 0x805559AC
void WiiPostProc::Init() {
    // Local variables
    int h; // r29

    // References
    // -> class Symbol name;
    // -> class RndTex * sGrayscaleTex;
    // -> class RndTex * sBloomTex;
    // -> class RndTex * sWorkTex;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndTex;
    // -> class Symbol name;
    // -> class WiiRnd TheWiiRnd;
}

// Range: 0x805559AC -> 0x80555A4C
void WiiPostProc::Terminate() {
    // References
    // -> class RndTex * sGrayscaleTex;
    // -> class RndTex * sBloomTex;
    // -> class RndTex * sWorkTex;
}

// Range: 0x80555A4C -> 0x80555AA0
void * WiiPostProc::WiiPostProc(class WiiPostProc * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__11WiiPostProc;
}

// Range: 0x80555AA0 -> 0x80555AFC
void * WiiPostProc::~WiiPostProc(class WiiPostProc * const this /* r30 */) {}

// Range: 0x80555AFC -> 0x80555C40
void WiiPostProc::Select(class WiiPostProc * const this /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__8RndLight;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__14RndTexRenderer;
    // -> class WorldDir * TheWorld;
}

static class Timer * _t; // size: 0x4, address: 0x80A53FF0
// Range: 0x80555C40 -> 0x80555D78
void WiiPostProc::BeginWorld(class WiiPostProc * const this /* r31 */) {
    // Local variables
    class AutoTimer _at; // r1+0xC

    // References
    // -> class WiiRnd TheWiiRnd;
    // -> static class Timer * _t;
}

static class Timer * _t; // size: 0x4, address: 0x80A53FF8
// Range: 0x80555D78 -> 0x80556160
void WiiPostProc::EndWorld(class WiiPostProc * const this /* r29 */) {
    // Local variables
    class AutoTimer _at; // r1+0x14
    class WiiOrthoProj _ortho; // r1+0x18
    unsigned char c; // r3
    struct _GXColor color; // r1+0x10

    // References
    // -> class RndTex * sBloomTex;
    // -> class RndTex * sWorkTex;
    // -> class Rnd & TheRnd;
    // -> class WiiRnd TheWiiRnd;
    // -> static class Timer * _t;
}

static class Timer * _t; // size: 0x4, address: 0x80A54000
// Range: 0x80556160 -> 0x80556300
void WiiPostProc::DoPost(class WiiPostProc * const this /* r31 */) {
    // Local variables
    class AutoTimer _at; // r1+0xC

    // References
    // -> class WiiRnd TheWiiRnd;
    // -> static class Timer * _t;
}

// Range: 0x80556300 -> 0x805567D0
void WiiPostProc::DoBloom(class WiiPostProc * const this /* r31 */) {
    // Local variables
    class WiiOrthoProj _ortho; // r1+0x28
    float texmtx[2][4]; // r1+0x8
    float size; // f31

    // References
    // -> class RndTex * sBloomTex;
    // -> class WiiRnd TheWiiRnd;
}

// Range: 0x805567D0 -> 0x80556B98
void WiiPostProc::DoNoise(class WiiPostProc * const this /* r31 */) {
    // Local variables
    class WiiOrthoProj _ortho; // r1+0x30
    float mod1[3][4]; // r1+0x80
    float mod2[3][4]; // r1+0x50
    class Color intense; // r1+0x20

    // References
    // -> class WiiRnd TheWiiRnd;
}

// Range: 0x80556B98 -> 0x80556D6C
void WiiPostProc::DoDesaturation(class WiiPostProc * const this /* r29 */) {
    // Local variables
    class WiiOrthoProj _ortho; // r1+0x10
    float factor; // f0
    struct _GXColor color; // r1+0xC

    // References
    // -> class RndTex * sGrayscaleTex;
    // -> class WiiRnd TheWiiRnd;
}

// Range: 0x80556D6C -> 0x805575A4
void WiiPostProc::DoHallOfTime(class WiiPostProc * const this /* r31 */) {
    // Local variables
    float distance; // f0
    int i; // r3
    float r; // f6
    float g; // f7
    float b; // f1
    float fade; // f4
    float r; // f5
    float g; // f6
    float b; // f1
    class WiiOrthoProj _ortho; // r1+0x40
    class Rect rect; // r1+0x30
    float adjust; // f4
    int i; // r29
    class Color color; // r1+0x20
    signed short tweak; // r30
    signed short tweak2; // r31

    // References
    // -> class Rnd & TheRnd;
    // -> unsigned char sCurrentZCompLoc;
    // -> struct WiiHOTRing sHOTRings[25];
    // -> class WiiRnd TheWiiRnd;
}

// Range: 0x805575A4 -> 0x80557638
void WiiPostProc::BeginHallOfTime(class WiiPostProc * const this /* r30 */) {
    // References
    // -> unsigned char sOverrideAlphaWrite;
    // -> class WiiRnd TheWiiRnd;
}

struct {
    // total size: 0x84
} __vt__11WiiPostProc; // size: 0x84, address: 0x80918814
struct {
    // total size: 0x8
} __RTTI__11WiiPostProc; // size: 0x8, address: 0x809188C8
// Range: 0x80557638 -> 0x80557658
static void __sinit_\PostProc_cpp() {
    // References
    // -> struct WiiHOTRing sHOTRings[25];
}

struct WiiHOTRing {
    // total size: 0x30
    unsigned short pos; // offset 0x0, size 0x2
    class Color baseColor; // offset 0x10, size 0x10
    class Color pulseColor; // offset 0x20, size 0x10
};

