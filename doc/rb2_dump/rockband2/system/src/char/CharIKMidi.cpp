/*
    Compile unit: C:\rockband2\system\src\char\CharIKMidi.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80378794 -> 0x80379E54
*/
class DataArray * types; // size: 0x4, address: 0x80A51120
// Range: 0x80378794 -> 0x80378970
void * CharIKMidi::CharIKMidi(class CharIKMidi * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__35ObjPtr<14CharWeightable,9ObjectDir>;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__10CharIKMidi;
    // -> struct [anonymous] __vt__12CharPollable;
    // -> struct [anonymous] __vt__11RndPollable;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x80378970 -> 0x80378AD4
void * CharIKMidi::~CharIKMidi(class CharIKMidi * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__35ObjPtr<14CharWeightable,9ObjectDir>;
}

// Range: 0x80378AD4 -> 0x80378BDC
void CharIKMidi::Enter(class CharIKMidi * const this /* r31 */) {}

// Range: 0x80378BDC -> 0x80378BEC
void CharIKMidi::Highlight() {}

// Range: 0x80378BEC -> 0x80378CD4
void CharIKMidi::NewSpot(class CharIKMidi * const this /* r30 */, class RndTransformable * spot /* r31 */, float delta /* f31 */) {}

// Range: 0x80378CD4 -> 0x803790D8
void CharIKMidi::Poll(class CharIKMidi * const this /* r31 */) {
    // Local variables
    class Transform t; // r1+0x70
    float frac; // f31
    class Quat q; // r1+0x20
    class Transform t; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x803790D8 -> 0x80379234
void CharIKMidi::PollDeps(class CharIKMidi * const this /* r29 */, class list & changedBy /* r30 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<PQ23Hmx6Object>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x80379234 -> 0x803792BC
void CharIKMidi::Save(class CharIKMidi * const this /* r30 */, class BinStream & d /* r31 */) {}

static int gRev; // size: 0x4, address: 0x80A51128
class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
// Range: 0x803792BC -> 0x803794B4
void CharIKMidi::Load(class CharIKMidi * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    class ObjVector spots; // r1+0x30
    class String msgSource; // r1+0x20

    // References
    // -> class Debug TheDebug;
    // -> static int gRev;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class ObjPtr * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class ObjPtr * _M_start; // offset 0x0, size 0x4
    class ObjPtr * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x803794B4 -> 0x803795AC
void CharIKMidi::Copy(class CharIKMidi * const this /* r29 */, const class Object * o /* r30 */) {
    // Local variables
    const class CharIKMidi * i; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10CharIKMidi;
}

static class Symbol _s; // size: 0x4, address: 0x80A51130
// Range: 0x803795AC -> 0x80379A1C
class DataNode CharIKMidi::Handle(class CharIKMidi * const this /* r30 */, class DataArray * _msg /* r26 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A51138
static class Symbol _s; // size: 0x4, address: 0x80A51140
static class Symbol _s; // size: 0x4, address: 0x80A51148
static class Symbol _s; // size: 0x4, address: 0x80A51150
// Range: 0x80379A1C -> 0x80379CF8
unsigned char CharIKMidi::SyncProperty(class CharIKMidi * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x80379CF8 -> 0x80379E54
unsigned char PropSync(class ObjPtr & p /* r29 */, class DataNode & n /* r30 */, enum PropOp op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__14CharWeightable;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0xB8
} __vt__10CharIKMidi; // size: 0xB8, address: 0x808D8570
struct {
    // total size: 0x18
} __vt__35ObjPtr<14CharWeightable,9ObjectDir>; // size: 0x18, address: 0x808D8668
struct {
    // total size: 0x8
} __RTTI__35ObjPtr<14CharWeightable,9ObjectDir>; // size: 0x8, address: 0x808D86B0
struct {
    // total size: 0x8
} __RTTI__P37ObjPtr<16RndTransformable,9ObjectDir>; // size: 0x8, address: 0x808D8958

