/*
    Compile unit: C:\rockband2\system\src\rndobj\Flare.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80499FF4 -> 0x8049B928
*/
class DataArray * types; // size: 0x4, address: 0x80A52EA8
static int FLARE_REV; // size: 0x4, address: 0x80A471D8
// Range: 0x80499FF4 -> 0x8049A038
void RndFlare::Save() {
    // References
    // -> class Debug TheDebug;
}

static int gRev; // size: 0x4, address: 0x80A52EB0
// Range: 0x8049A038 -> 0x8049A200
void RndFlare::Load(class RndFlare * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int FLARE_REV;
    // -> static int gRev;
}

// Range: 0x8049A200 -> 0x8049A368
void * RndFlare::RndFlare(class RndFlare * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
    // -> struct [anonymous] __vt__8RndFlare;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x8049A368 -> 0x8049A4B4
void * RndFlare::~RndFlare(class RndFlare * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
    // -> class Rnd & TheRnd;
    // -> struct [anonymous] __vt__8RndFlare;
}

// Range: 0x8049A4B4 -> 0x8049A518
void RndFlare::SetPointTest(class RndFlare * const this /* r30 */, unsigned char b /* r31 */) {
    // References
    // -> class Rnd & TheRnd;
}

// Range: 0x8049A518 -> 0x8049AA70
void RndFlare::DrawShowing(class RndFlare * const this /* r31 */) {
    // Local variables
    class Vector2 v; // r1+0x10
    float dist; // f0
    class Rect area; // r1+0x50
    unsigned char offscreen; // r0
    unsigned char transition; // r30
    float fade; // f3
    class Color c; // r1+0x40
    class Transform t; // r1+0x60
    class Rect r; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class RndEnviron * sCurrent;
    // -> class RndCam * sCurrent;
    // -> class Rnd & TheRnd;
}

// Range: 0x8049AA70 -> 0x8049AC04
class Rect & RndFlare::CalcRect(class RndFlare * const this /* r27 */, class Vector2 & v /* r28 */) {
    // Local variables
    float size; // f2
    float dot; // f2

    // References
    // -> class Rnd & TheRnd;
    // -> class RndCam * sCurrent;
}

// Range: 0x8049AC04 -> 0x8049ACA8
unsigned char RndFlare::RectOffscreen() {
    // References
    // -> class Rnd & TheRnd;
}

// Range: 0x8049ACA8 -> 0x8049AD60
void RndFlare::Mats(class RndFlare * const this /* r31 */, class list & mats /* r30 */) {
    // Local variables
    struct MatShaderOptions opts; // r1+0xC

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std20_List_node<P6RndMat>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x8049AD60 -> 0x8049ADC8
void RndFlare::SetMat(class RndFlare * const this /* r30 */, class RndMat * m /* r31 */) {}

// Range: 0x8049ADC8 -> 0x8049AE60
void RndFlare::SetSteps(int s /* r1+0x8 */) {}

static class Symbol _s; // size: 0x4, address: 0x80A52EB8
static class Symbol _s; // size: 0x4, address: 0x80A52EC0
// Range: 0x8049AE60 -> 0x8049B578
class DataNode RndFlare::Handle(class RndFlare * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x30
    class MessageTimer _mt; // r1+0x50
    class DataNode _n; // r1+0x48
    class DataNode _n; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A52EC8
static class Symbol _s; // size: 0x4, address: 0x80A52ED0
static class Symbol _s; // size: 0x4, address: 0x80A52ED8
static class Symbol _s; // size: 0x4, address: 0x80A52EE0
static class Symbol _s; // size: 0x4, address: 0x80A52EE8
// Range: 0x8049B578 -> 0x8049B928
unsigned char RndFlare::SyncProperty(class RndFlare * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> class Rnd & TheRnd;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0xF8
} __vt__8RndFlare; // size: 0xF8, address: 0x808F6EB8

