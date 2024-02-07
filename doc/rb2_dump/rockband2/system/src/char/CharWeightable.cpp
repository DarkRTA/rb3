/*
    Compile unit: C:\rockband2\system\src\char\CharWeightable.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8039C36C -> 0x8039CCEC
*/
class DataArray * types; // size: 0x4, address: 0x80A51450
// Range: 0x8039C36C -> 0x8039C414
void * CharWeightable::CharWeightable(class CharWeightable * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__40ObjOwnerPtr<14CharWeightable,9ObjectDir>;
    // -> struct [anonymous] __vt__14CharWeightable;
}

// Range: 0x8039C414 -> 0x8039C4FC
void CharWeightable::Replace(class CharWeightable * const this /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__14CharWeightable;
}

// Range: 0x8039C4FC -> 0x8039C56C
void CharWeightable::Save(class CharWeightable * const this /* r30 */, class BinStream & d /* r31 */) {}

static int gRev; // size: 0x4, address: 0x80A51458
// Range: 0x8039C56C -> 0x8039C648
void CharWeightable::Load(class CharWeightable * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x8039C648 -> 0x8039C774
void CharWeightable::Copy(class CharWeightable * const this /* r29 */, enum CopyType type /* r30 */) {
    // Local variables
    const class CharWeightable * w; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__14CharWeightable;
}

// Range: 0x8039C774 -> 0x8039CA38
class DataNode CharWeightable::Handle(class CharWeightable * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
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

static class Symbol _s; // size: 0x4, address: 0x80A51460
static class Symbol _s; // size: 0x4, address: 0x80A51468
// Range: 0x8039CA38 -> 0x8039CBAC
unsigned char CharWeightable::SyncProperty(class CharWeightable * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x8039CBAC -> 0x8039CCEC
unsigned char PropSync(class ObjOwnerPtr & p /* r29 */, class DataNode & n /* r30 */, enum PropOp op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__14CharWeightable;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x84
} __vt__14CharWeightable; // size: 0x84, address: 0x808DCEC4

