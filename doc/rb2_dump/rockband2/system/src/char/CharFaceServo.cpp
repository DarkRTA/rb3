/*
    Compile unit: C:\rockband2\system\src\char\CharFaceServo.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8035B2D4 -> 0x8035BF08
*/
class DataArray * types; // size: 0x4, address: 0x80A50F48
// Range: 0x8035B2D4 -> 0x8035B444
void * CharFaceServo::CharFaceServo(class CharFaceServo * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__28ObjPtr<8CharClip,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtr<11CharClipSet,9ObjectDir>;
    // -> struct [anonymous] __vt__13CharFaceServo;
    // -> struct [anonymous] __vt__12CharPollable;
    // -> struct [anonymous] __vt__11RndPollable;
}

// Range: 0x8035B444 -> 0x8035B56C
void * CharFaceServo::~CharFaceServo(class CharFaceServo * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__32ObjPtr<11CharClipSet,9ObjectDir>;
    // -> struct [anonymous] __vt__28ObjPtr<8CharClip,9ObjectDir>;
}

// Range: 0x8035B56C -> 0x8035B5A0
void CharFaceServo::Enter(class CharFaceServo * const this /* r31 */) {}

// Range: 0x8035B5A0 -> 0x8035B5A8
void CharFaceServo::ReallocateInternal() {}

static class Timer * _t; // size: 0x4, address: 0x80A50F50
// Range: 0x8035B5A8 -> 0x8035B6B0
void CharFaceServo::Poll(class CharFaceServo * const this /* r31 */) {
    // Local variables
    class AutoTimer _at; // r1+0xC

    // References
    // -> static class Timer * _t;
}

// Range: 0x8035B6B0 -> 0x8035B79C
void CharFaceServo::ScaleAdd(class CharFaceServo * const this /* r30 */, class CharClip * clip /* r31 */, float weight /* f29 */, float frame /* f30 */, float dframe /* f31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8035B79C -> 0x8035B7A0
void CharFaceServo::StuffBones() {}

// Range: 0x8035B7A0 -> 0x8035B7D8
void CharFaceServo::Reset(class CharFaceServo * const this /* r4 */) {}

// Range: 0x8035B7D8 -> 0x8035B7E4
void CharFaceServo::PollDeps() {}

// Range: 0x8035B7E4 -> 0x8035B848
void CharFaceServo::Save(class CharFaceServo * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x8035B848 -> 0x8035B8DC
class BinStream & __ls(class BinStream & d /* r30 */, const class ObjPtr & f /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static int gRev; // size: 0x4, address: 0x80A50F58
// Range: 0x8035B8DC -> 0x8035B9B4
void CharFaceServo::Load(class CharFaceServo * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x8035B9B4 -> 0x8035BAE8
void CharFaceServo::Copy(class CharFaceServo * const this /* r29 */, const class Object * o /* r30 */) {
    // Local variables
    const class CharFaceServo * b; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13CharFaceServo;
}

// Range: 0x8035BAE8 -> 0x8035BDAC
class DataNode CharFaceServo::Handle(class CharFaceServo * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
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

static class Symbol _s; // size: 0x4, address: 0x80A50F60
// Range: 0x8035BDAC -> 0x8035BF08
unsigned char CharFaceServo::SyncProperty(class CharFaceServo * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11CharClipSet;
    // -> static class Symbol _s;
}

struct {
    // total size: 0xC8
} __vt__13CharFaceServo; // size: 0xC8, address: 0x808D68B0

