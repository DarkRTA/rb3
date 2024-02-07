/*
    Compile unit: C:\rockband2\system\src\rndobj\CubeTex.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8047AFC8 -> 0x8047BE1C
*/
class DataArray * types; // size: 0x4, address: 0x80A52A70
class Symbol name; // size: 0x4, address: 0x80A52A78
class RndCubeTex : public Object {
    // total size: 0x154
protected:
    int mSize; // offset 0x28, size 0x4
    int mBpp; // offset 0x2C, size 0x4
    int mNumMips; // offset 0x30, size 0x4
    class FilePath mFile[6]; // offset 0x34, size 0x48
    class RndBitmap mBitmap[6]; // offset 0x7C, size 0xD8
};
// Range: 0x8047AFC8 -> 0x8047B058
void * RndCubeTex::RndCubeTex(class RndCubeTex * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__10RndCubeTex;
}

enum CubeFace {
    kCubeFaceRight = 0,
    kCubeFaceLeft = 1,
    kCubeFaceTop = 2,
    kCubeFaceBottom = 3,
    kCubeFaceFront = 4,
    kCubeFaceBack = 5,
    kNumCubeFaces = 6,
};
// Range: 0x8047B058 -> 0x8047B198
void RndCubeTex::Update(class RndCubeTex * const this /* r26 */) {
    // Local variables
    int bpp; // r0
    int size; // r0
    int order; // r29
    int numMips; // r28
    const char * err; // r0
    int i; // r27
    class RndBitmap & bm; // r3

    // References
    // -> class Debug TheDebug;
}

static int CUBETEX_REV; // size: 0x4, address: 0x80A47154
// Range: 0x8047B198 -> 0x8047B1DC
void RndCubeTex::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8047B1DC -> 0x8047B238
void RndCubeTex::Load(class RndCubeTex * const this /* r30 */, class BinStream & d /* r31 */) {}

static int gRev; // size: 0x4, address: 0x80A52A7C
// Range: 0x8047B238 -> 0x8047B37C
void RndCubeTex::PreLoad(class RndCubeTex * const this /* r28 */, class BinStream & d /* r29 */) {
    // Local variables
    int i; // r30

    // References
    // -> class LoadMgr TheLoadMgr;
    // -> class FilePath sRoot;
    // -> class Debug TheDebug;
    // -> static int CUBETEX_REV;
    // -> static int gRev;
}

// Range: 0x8047B37C -> 0x8047B438
void RndCubeTex::PostLoad(class RndCubeTex * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    int i; // r31

    // References
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x8047B438 -> 0x8047B514
void RndCubeTex::Copy(class RndCubeTex * const this /* r29 */, const class Object * o /* r30 */) {
    // Local variables
    const class RndCubeTex * t; // r0
    int i; // r30

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10RndCubeTex;
}

// Range: 0x8047B514 -> 0x8047B7BC
class DataNode RndCubeTex::Handle(class RndCubeTex * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
    // Local variables
    class Symbol _type; // r1+0x20
    class MessageTimer _mt; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A52A84
static class Symbol _s; // size: 0x4, address: 0x80A52A8C
static class Symbol _s; // size: 0x4, address: 0x80A52A94
static class Symbol _s; // size: 0x4, address: 0x80A52A9C
static class Symbol _s; // size: 0x4, address: 0x80A52AA4
static class Symbol _s; // size: 0x4, address: 0x80A52AAC
// Range: 0x8047B7BC -> 0x8047BE1C
unsigned char RndCubeTex::SyncProperty(class RndCubeTex * const this /* r28 */, class DataNode & _val /* r29 */, class DataArray * _prop /* r27 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x60
} __vt__10RndCubeTex; // size: 0x60, address: 0x808F34E0
struct {
    // total size: 0x8
} __RTTI__10RndCubeTex; // size: 0x8, address: 0x808F3560

