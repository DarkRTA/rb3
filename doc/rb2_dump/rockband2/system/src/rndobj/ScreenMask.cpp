/*
    Compile unit: C:\rockband2\system\src\rndobj\ScreenMask.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804FAF60 -> 0x804FBDEC
*/
class DataArray * types; // size: 0x4, address: 0x80A538D8
// Range: 0x804FAF60 -> 0x804FB094
void * RndScreenMask::RndScreenMask(class RndScreenMask * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
    // -> struct [anonymous] __vt__13RndScreenMask;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x804FB094 -> 0x804FB19C
void RndScreenMask::Copy(class RndScreenMask * const this /* r29 */, const class Object * o /* r31 */, enum CopyType type /* r30 */) {
    // Local variables
    const class RndScreenMask * f; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13RndScreenMask;
}

static int SCREENMASK_REV; // size: 0x4, address: 0x80A473B0
// Range: 0x804FB19C -> 0x804FB1E0
void RndScreenMask::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x804FB1E0 -> 0x804FB380
void RndScreenMask::Load(class RndScreenMask * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    int rev; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> static int SCREENMASK_REV;
}

static class DebugWarner _dw; // size: 0x100, address: 0x809805A8
// Range: 0x804FB380 -> 0x804FB690
void RndScreenMask::DrawShowing(class RndScreenMask * const this /* r31 */) {
    // Local variables
    float screenWidth; // f31
    float screenHeight; // f30
    class Rect camRect; // r1+0x48
    class Rect r; // r1+0x38
    class Rect camRect; // r1+0x28
    class Rect r; // r1+0x18

    // References
    // -> class Debug TheDebug;
    // -> static class DebugWarner _dw;
    // -> class RndCam * sCurrent;
    // -> class Rnd & TheRnd;
}

// Range: 0x804FB690 -> 0x804FBA88
class DataNode RndScreenMask::Handle(class RndScreenMask * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x38
    class DataNode _n; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A538E0
static class Symbol _s; // size: 0x4, address: 0x80A538E8
static class Symbol _s; // size: 0x4, address: 0x80A538F0
static class Symbol _s; // size: 0x4, address: 0x80A538F8
static class Symbol _s; // size: 0x4, address: 0x80A53900
// Range: 0x804FBA88 -> 0x804FBDEC
unsigned char RndScreenMask::SyncProperty(class RndScreenMask * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0xB8
} __vt__13RndScreenMask; // size: 0xB8, address: 0x80900498

