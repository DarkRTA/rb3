/*
    Compile unit: C:\rockband2\system\src\char\CharWalk.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8039A70C -> 0x8039C0CC
*/
class DataArray * types; // size: 0x4, address: 0x80A51440
// Range: 0x8039A70C -> 0x8039A8C8
static float AngleBetween() {
    // Local variables
    class Vector3 ta; // r1+0x40
    class Vector3 tb; // r1+0x30
    class Vector3 tc; // r1+0x20
    float la; // r1+0x14
    float lb; // r1+0x10
    float l1; // f2
    float l2; // f0
}

// Range: 0x8039A8C8 -> 0x8039A9B0
void * CharWalk::CharWalk(class CharWalk * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__8CharWalk;
    // -> struct [anonymous] __vt__12CharPollable;
    // -> struct [anonymous] __vt__11RndPollable;
}

// Range: 0x8039A9B0 -> 0x8039AB48
void * CharWalk::~CharWalk(class CharWalk * const this /* r30 */) {}

// Range: 0x8039AB48 -> 0x8039ABB4
void CharWalk::SetTypeDef(class CharWalk * const this /* r30 */, class DataArray * d /* r31 */) {}

// Range: 0x8039ABB4 -> 0x8039AC10
void CharWalk::SetName(class CharWalk * const this /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__9Character;
}

// Range: 0x8039AC10 -> 0x8039ADB4
void CharWalk::Enter(class CharWalk * const this /* r31 */) {}

// Range: 0x8039ADB4 -> 0x8039AF6C
void CharWalk::Poll(class CharWalk * const this /* r31 */) {
    // Local variables
    class CharClipDriver * most; // r30
}

class StlNodeAlloc {
    // total size: 0x1
};
// Range: 0x8039AF6C -> 0x8039B0EC
void CharWalk::ForwardPredict(class CharWalk * const this /* r28 */, class ClipPredict & pred /* r29 */, float kLookAhead /* f30 */, int & dstNode /* r30 */, float & dstFrame /* r31 */) {
    // Local variables
    float frame; // f31
    float nextFrame; // f30
}

// Range: 0x8039B0EC -> 0x8039B290
void CharWalk::BackPredict(class CharWalk * const this /* r29 */, class Vector3 & backPos /* r30 */, int dstNode /* r31 */, float dstFrame /* f30 */) {
    // Local variables
    class ClipPredict backPred; // r1+0x10
    float end; // f31
    int i; // r27
}

// Range: 0x8039B290 -> 0x8039B930
void CharWalk::RegulateWalk(class CharWalk * const this /* r28 */) {
    // Local variables
    const class CharClipDriver * mostPlaying; // r0
    int curNode; // r29
    float kLookAhead; // f31
    class ClipPredict pred; // r1+0x80
    float dstFrame; // r1+0x20
    int dstNode; // r1+0x1C
    class Vector3 backPos; // r1+0x70
    class Vector3 delta; // r1+0x60
    class Vector3 backProj; // r1+0x50
    class Vector3 delta; // r1+0x40
    float l; // f0
    float deltaPosAng; // f0
    float posDang; // f31
    float estDist; // f5
    float realDist; // f6
    class Vector3 lastPos; // r1+0x30
    int i; // r4
    float delta; // f31
    float beatsLeft; // r1+0x18
    float l; // f0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x8039B930 -> 0x8039BA2C
float CharWalk::FindStartFrame(class ClipPredict & pred /* r30 */, float br /* f30 */) {
    // Local variables
    class CharClip * stopClip; // r0
    float startFrame; // f31

    // References
    // -> class Debug TheDebug;
}

// Range: 0x8039BA2C -> 0x8039BAF4
void CharWalk::SetWaypoint() {}

// Range: 0x8039BAF4 -> 0x8039BB4C
unsigned char CharWalk::IsWalkClip() {
    // Local variables
    int i; // r7
}

// Range: 0x8039BB4C -> 0x8039BC4C
void CharWalk::PollDeps(class CharWalk * const this /* r29 */, class list & change /* r30 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<PQ23Hmx6Object>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x8039BC4C -> 0x8039BCA4
void CharWalk::Save(class CharWalk * const this /* r30 */, class BinStream & d /* r31 */) {}

static int gRev; // size: 0x4, address: 0x80A51448
// Range: 0x8039BCA4 -> 0x8039BD64
void CharWalk::Load(class CharWalk * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x8039BD64 -> 0x8039BDB4
void CharWalk::Copy(const class Object * o /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8CharWalk;
}

// Range: 0x8039BDB4 -> 0x8039C078
class DataNode CharWalk::Handle(class CharWalk * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
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

// Range: 0x8039C078 -> 0x8039C0CC
unsigned char CharWalk::SyncProperty(class DataArray * _prop /* r31 */) {}

struct {
    // total size: 0x98
} __vt__8CharWalk; // size: 0x98, address: 0x808DCD68

