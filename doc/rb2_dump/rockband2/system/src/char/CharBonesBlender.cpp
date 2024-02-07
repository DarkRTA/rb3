/*
    Compile unit: C:\rockband2\system\src\char\CharBonesBlender.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80326910 -> 0x80327488
*/
class DataArray * types; // size: 0x4, address: 0x80A50A88
// Range: 0x80326910 -> 0x80326A60
void * CharBonesBlender::CharBonesBlender(class CharBonesBlender * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__36ObjPtr<15CharBonesObject,9ObjectDir>;
    // -> struct [anonymous] __vt__16CharBonesBlender;
    // -> struct [anonymous] __vt__14CharBonesAlloc;
    // -> struct [anonymous] __vt__15CharBonesObject;
    // -> struct [anonymous] __vt__12CharPollable;
    // -> struct [anonymous] __vt__11RndPollable;
}

// Range: 0x80326A60 -> 0x80326B38
void * CharBonesBlender::~CharBonesBlender(class CharBonesBlender * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__36ObjPtr<15CharBonesObject,9ObjectDir>;
}

// Range: 0x80326B38 -> 0x80326B74
void CharBonesBlender::Enter(class CharBonesBlender * const this /* r31 */) {}

// Range: 0x80326B74 -> 0x80326BD8
void CharBonesBlender::Poll(class CharBonesBlender * const this /* r31 */) {}

// Range: 0x80326BD8 -> 0x80326C64
void CharBonesBlender::SetDest(class CharBonesBlender * const this /* r30 */, class CharBonesObject * dest /* r31 */) {}

// Range: 0x80326C64 -> 0x80326CBC
void CharBonesBlender::ReallocateInternal(class CharBonesBlender * const this /* r31 */) {}

// Range: 0x80326CBC -> 0x80326D3C
void CharBonesBlender::PollDeps() {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<PQ23Hmx6Object>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x80326D3C -> 0x80326DA0
void CharBonesBlender::Save(class CharBonesBlender * const this /* r30 */, class BinStream & d /* r31 */) {}

static int gRev; // size: 0x4, address: 0x80A50A90
// Range: 0x80326DA0 -> 0x80326ECC
void CharBonesBlender::Load(class CharBonesBlender * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    class ObjPtr dest; // r1+0xC

    // References
    // -> struct [anonymous] __vt__36ObjPtr<15CharBonesObject,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x80326ECC -> 0x80326F40
void CharBonesBlender::Copy(class CharBonesBlender * const this /* r30 */, const class Object * o /* r31 */) {
    // Local variables
    const class CharBonesBlender * c; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16CharBonesBlender;
}

// Range: 0x80326F40 -> 0x8032732C
class DataNode CharBonesBlender::Handle(class CharBonesBlender * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
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

static class Symbol _s; // size: 0x4, address: 0x80A50A98
// Range: 0x8032732C -> 0x80327488
unsigned char CharBonesBlender::SyncProperty(class CharBonesBlender * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__15CharBonesObject;
    // -> static class Symbol _s;
}

struct {
    // total size: 0xBC
} __vt__16CharBonesBlender; // size: 0xBC, address: 0x808D11D0
struct {
    // total size: 0x8
} __RTTI__16CharBonesBlender; // size: 0x8, address: 0x808D12E0
struct {
    // total size: 0x18
} __vt__36ObjPtr<15CharBonesObject,9ObjectDir>; // size: 0x18, address: 0x808D12E8
struct {
    // total size: 0x8
} __RTTI__36ObjPtr<15CharBonesObject,9ObjectDir>; // size: 0x8, address: 0x808D1330

