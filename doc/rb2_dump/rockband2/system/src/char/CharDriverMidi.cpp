/*
    Compile unit: C:\rockband2\system\src\char\CharDriverMidi.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80352D34 -> 0x80353C54
*/
class DataArray * types; // size: 0x4, address: 0x80A50EB8
// Range: 0x80352D34 -> 0x80352DF4
void CharDriverMidi::Enter(class CharDriverMidi * const this /* r31 */) {
    // Local variables
    class MsgSource * midiParser; // r3

    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9MsgSource;
}

// Range: 0x80352DF4 -> 0x80352E74
void CharDriverMidi::Exit(class CharDriverMidi * const this /* r31 */) {
    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9MsgSource;
    // -> class ObjectDir * sMainDir;
}

// Range: 0x80352E74 -> 0x80352E78
void CharDriverMidi::Poll() {}

// Range: 0x80352E78 -> 0x80352E7C
void CharDriverMidi::PollDeps() {}

// Range: 0x80352E7C -> 0x80352EEC
void CharDriverMidi::Save(class CharDriverMidi * const this /* r30 */, class BinStream & d /* r31 */) {}

static int gRev; // size: 0x4, address: 0x80A50EC0
// Range: 0x80352EEC -> 0x80352F48
void CharDriverMidi::Load(class CharDriverMidi * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x80352F48 -> 0x80353060
void CharDriverMidi::PreLoad(class CharDriverMidi * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class list sRevs;
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x80353060 -> 0x803531D4
void CharDriverMidi::PostLoad(class CharDriverMidi * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    class ObjPtr inactiveClip; // r1+0x20
    class String msgSource; // r1+0x14

    // References
    // -> struct [anonymous] __vt__28ObjPtr<8CharClip,9ObjectDir>;
    // -> static int gRev;
    // -> class list sRevs;
}

// Range: 0x803531D4 -> 0x8035328C
void CharDriverMidi::Copy(class CharDriverMidi * const this /* r29 */, const class Object * o /* r30 */) {
    // Local variables
    const class CharDriverMidi * d; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__14CharDriverMidi;
}

static class Symbol _s; // size: 0x4, address: 0x80A50EC8
static class Symbol _s; // size: 0x4, address: 0x80A50ED0
// Range: 0x8035328C -> 0x803537FC
class DataNode CharDriverMidi::Handle(class CharDriverMidi * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode r; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x803537FC -> 0x80353938
class DataNode CharDriverMidi::OnSetInactiveClipName(class CharDriverMidi * const this /* r30 */, class DataArray * d /* r31 */) {
    // Local variables
    class CharClip * pClip; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80353938 -> 0x80353A70
class DataNode CharDriverMidi::OnMidiParser(class CharDriverMidi * const this /* r29 */, class DataArray * d /* r30 */) {
    // Local variables
    float blendWidth; // f31
}

static class Symbol _s; // size: 0x4, address: 0x80A50ED8
static class Symbol _s; // size: 0x4, address: 0x80A50EE0
// Range: 0x80353A70 -> 0x80353C54
unsigned char CharDriverMidi::SyncProperty(class CharDriverMidi * const this /* r28 */, class DataNode & _val /* r29 */, class DataArray * _prop /* r30 */, int _i /* r27 */, enum PropOp _op /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0xF8
} __vt__14CharDriverMidi; // size: 0xF8, address: 0x808D57F8
struct {
    // total size: 0x8
} __RTTI__14CharDriverMidi; // size: 0x8, address: 0x808D5940

