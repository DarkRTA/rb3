/*
    Compile unit: C:\rockband2\system\src\char\CharCuff.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80348364 -> 0x8034AF24
*/
class DataArray * types; // size: 0x4, address: 0x80A50D80
// Range: 0x80348364 -> 0x803484F8
void * CharCuff::CharCuff(class CharCuff * const this /* r31 */) {
    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__31ObjPtrList<7RndMesh,9ObjectDir>;
    // -> struct [anonymous] __vt__8CharCuff;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x803484F8 -> 0x80348740
void * CharCuff::~CharCuff(class CharCuff * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__31ObjPtrList<7RndMesh,9ObjectDir>;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
}

// Range: 0x80348740 -> 0x80348790
float CharCuff::Eccentricity() {
    // Local variables
    float s; // f2
    float y2; // f3
    float x2; // f0
}

// Range: 0x80348790 -> 0x80348CDC
void CharCuff::Highlight(class CharCuff * const this /* r28 */) {
    // Local variables
    class Color col; // r1+0x60
    int i; // r30
    int j; // r29
    float heading; // f31
    class Vector3 la; // r1+0x50
    class Vector3 lb; // r1+0x40
    class Vector3 wa; // r1+0x30
    class Vector3 wb; // r1+0x20
    float h2; // f28
    class Vector3 la; // r1+0x10
    float h2; // f28

    // References
    // -> class Rnd & TheRnd;
}

// Range: 0x80348CDC -> 0x80348DB4
static int BoneMask(class list & bones /* r28 */, class RndMesh * mesh /* r29 */) {
    // Local variables
    int mask; // r31
    int i; // r30
}

class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class CharCuff * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x80348DB4 -> 0x803490C4
void CharCuff::DeformAll(class SyncMeshCB * cb /* r31 */) {
    // Local variables
    class ObjDirItr cuff; // r1+0x18

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8CharCuff;
}

static int gRev; // size: 0x4, address: 0x80A50D88
// Range: 0x803490C4 -> 0x803491F8
void CharCuff::Save(class CharCuff * const this /* r28 */, class BinStream & d /* r29 */) {
    // Local variables
    int i; // r30
}

// Range: 0x803491F8 -> 0x803492D4
class BinStream & __ls(class BinStream & d /* r30 */, const class ObjPtrList & c /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803492D4 -> 0x803495BC
void CharCuff::Load(class CharCuff * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    int i; // r27

    // References
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x803495BC -> 0x803499C0
void CharCuff::Copy(class CharCuff * const this /* r29 */, const class Object * o /* r28 */, enum CopyType type /* r27 */) {
    // Local variables
    const class CharCuff * c; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8CharCuff;
}

// Range: 0x803499C0 -> 0x80349DB8
class DataNode CharCuff::Handle(class CharCuff * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
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

static class Symbol _s; // size: 0x4, address: 0x80A50D90
static class Symbol _s; // size: 0x4, address: 0x80A50D98
static class Symbol _s; // size: 0x4, address: 0x80A50DA0
static class Symbol _s; // size: 0x4, address: 0x80A50DA8
static class Symbol _s; // size: 0x4, address: 0x80A50DB0
static class Symbol _s; // size: 0x4, address: 0x80A50DB8
static class Symbol _s; // size: 0x4, address: 0x80A50DC0
static class Symbol _s; // size: 0x4, address: 0x80A50DC8
static class Symbol _s; // size: 0x4, address: 0x80A50DD0
static class Symbol _s; // size: 0x4, address: 0x80A50DD8
static class Symbol _s; // size: 0x4, address: 0x80A50DE0
static class Symbol _s; // size: 0x4, address: 0x80A50DE8
// Range: 0x80349DB8 -> 0x8034A86C
unsigned char CharCuff::SyncProperty(class CharCuff * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

// Range: 0x8034A86C -> 0x8034AF24
unsigned char PropSync(class ObjPtrList & l /* r26 */, class DataNode & n /* r27 */, class DataArray * prop /* r28 */, int i /* r29 */, enum PropOp op /* r30 */) {
    // Local variables
    class iterator it; // r1+0x1C
    int which; // r3
    class RndMesh * obj; // r31
    class RndMesh * obj; // r31

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x9C
} __vt__8CharCuff; // size: 0x9C, address: 0x808D45AC
struct {
    // total size: 0x8
} __RTTI__8CharCuff; // size: 0x8, address: 0x808D4678

