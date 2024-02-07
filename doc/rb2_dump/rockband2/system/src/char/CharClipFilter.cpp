/*
    Compile unit: C:\rockband2\system\src\char\CharClipFilter.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8032C870 -> 0x8032CD74
*/
class DataArray * types; // size: 0x4, address: 0x80A50B90
// Range: 0x8032C870 -> 0x8032C8DC
void * CharClipFilter::CharClipFilter(class CharClipFilter * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__14CharClipFilter;
}

// Range: 0x8032C8DC -> 0x8032C8E4
void CharClipFilter::Save() {}

static class Message filterClips; // size: 0x8, address: 0x8097DE48
// Range: 0x8032C8E4 -> 0x8032CA54
void CharClipFilter::Load(class CharClipFilter * const this /* r31 */) {
    // References
    // -> static class Message filterClips;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x8032CA54 -> 0x8032CA5C
void CharClipFilter::Copy() {}

// Range: 0x8032CA5C -> 0x8032CD20
class DataNode CharClipFilter::Handle(class CharClipFilter * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
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

// Range: 0x8032CD20 -> 0x8032CD74
unsigned char CharClipFilter::SyncProperty(class DataArray * _prop /* r31 */) {}

struct {
    // total size: 0x7C
} __vt__14CharClipFilter; // size: 0x7C, address: 0x808D1B70
struct {
    // total size: 0x8
} __RTTI__14CharClipFilter; // size: 0x8, address: 0x808D1C10

