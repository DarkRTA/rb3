/*
    Compile unit: C:\rockband2\system\src\char\CharLipSync.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8037E2FC -> 0x8037F1FC
*/
class DataArray * types; // size: 0x4, address: 0x80A511E8
// Range: 0x8037E2FC -> 0x8037E324
void * PlayBack::PlayBack() {}

// Range: 0x8037E324 -> 0x8037E530
void PlayBack::Set(class PlayBack * const this /* r31 */) {
    // Local variables
    int i; // r25

    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8CharClip;
}

// Range: 0x8037E530 -> 0x8037E584
void PlayBack::Reset() {
    // Local variables
    int i; // r5
}

// Range: 0x8037E584 -> 0x8037E774
void PlayBack::Poll(class PlayBack * const this /* r29 */) {
    // Local variables
    float fFrame; // f31
    int iFrame; // r30
    float frac; // f31
    class vector & data; // r0
    int count; // r6
    int old; // r4
    int count; // r5
    int index; // r0
}

// Range: 0x8037E774 -> 0x8037E7D0
void * CharLipSync::CharLipSync(class CharLipSync * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__11CharLipSync;
}

// Range: 0x8037E7D0 -> 0x8037E904
void * CharLipSync::~CharLipSync(class CharLipSync * const this /* r30 */) {}

static int gRev; // size: 0x4, address: 0x80A511F0
// Range: 0x8037E904 -> 0x8037E98C
void CharLipSync::Save(class CharLipSync * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x8037E98C -> 0x8037EA04
void CharLipSync::Load(class CharLipSync * const this /* r30 */, class BinStream & d /* r31 */) {
    // References
    // -> static int gRev;
}

// Range: 0x8037EA04 -> 0x8037EA88
void CharLipSync::Copy(class CharLipSync * const this /* r30 */, const class Object * o /* r31 */) {
    // Local variables
    const class CharLipSync * c; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11CharLipSync;
}

static class Symbol _s; // size: 0x4, address: 0x80A511F8
static class Symbol _s; // size: 0x4, address: 0x80A51200
static class Symbol _s; // size: 0x4, address: 0x80A51208
// Range: 0x8037EA88 -> 0x8037ED08
unsigned char CharLipSync::SyncProperty(class CharLipSync * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

// Range: 0x8037ED08 -> 0x8037EF54
unsigned char PropSync(class vector & v /* r30 */, class DataNode & n /* r31 */, class DataArray * prop /* r26 */, int i /* r27 */, enum PropOp op /* r29 */) {
    // Local variables
    class String * it; // r28
    class String tmp; // r1+0x20

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8037EF54 -> 0x8037F1FC
class DataNode CharLipSync::Handle(class CharLipSync * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
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

struct {
    // total size: 0x54
} __vt__11CharLipSync; // size: 0x54, address: 0x808D9750
struct {
    // total size: 0x8
} __RTTI__11CharLipSync; // size: 0x8, address: 0x808D97C8
struct {
    // total size: 0x8
} __RTTI__PQ311CharLipSync9Generator6Weight; // size: 0x8, address: 0x808D9880
struct {
    // total size: 0x8
} __RTTI__PQ311CharLipSync8PlayBack6Weight; // size: 0x8, address: 0x808D98A8

