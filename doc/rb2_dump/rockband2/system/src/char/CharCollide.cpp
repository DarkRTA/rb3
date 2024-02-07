/*
    Compile unit: C:\rockband2\system\src\char\CharCollide.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80346F10 -> 0x80347F28
*/
class DataArray * types; // size: 0x4, address: 0x80A50D40
// Range: 0x80346F10 -> 0x80347004
void * CharCollide::CharCollide(class CharCollide * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__11CharCollide;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x80347004 -> 0x803470B4
void * CharCollide::~CharCollide(class CharCollide * const this /* r30 */) {}

static int gRev; // size: 0x4, address: 0x80A50D48
// Range: 0x803470B4 -> 0x803471AC
void CharCollide::Save(class CharCollide * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x803471AC -> 0x80347328
void CharCollide::Load(class CharCollide * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x80347328 -> 0x803473DC
void CharCollide::Copy(class CharCollide * const this /* r29 */, const class Object * o /* r30 */, enum CopyType type /* r31 */) {
    // Local variables
    const class CharCollide * c; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11CharCollide;
}

// Range: 0x803473DC -> 0x803474E8
void CharCollide::ComputeRadius(class CharCollide * const this /* r31 */) {
    // Local variables
    class Vector3 offset; // r1+0x10
}

// Range: 0x803474E8 -> 0x803474F4
void CharCollide::SyncRadius() {}

static class Symbol _s; // size: 0x4, address: 0x80A50D50
// Range: 0x803474F4 -> 0x803479CC
class DataNode CharCollide::Handle(class CharCollide * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x40
    class DataNode _n; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A50D58
static class Symbol _s; // size: 0x4, address: 0x80A50D60
static class Symbol _s; // size: 0x4, address: 0x80A50D68
static class Symbol _s; // size: 0x4, address: 0x80A50D70
static class Symbol _s; // size: 0x4, address: 0x80A50D78
// Range: 0x803479CC -> 0x80347F28
unsigned char CharCollide::SyncProperty(class CharCollide * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x9C
} __vt__11CharCollide; // size: 0x9C, address: 0x808D4040

