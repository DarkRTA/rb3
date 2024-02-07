/*
    Compile unit: C:\rockband2\band2\src\meta\CharPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800D949C -> 0x800DA0E0
*/
class DataArray * types; // size: 0x4, address: 0x80A4ACA0
class Symbol name; // size: 0x4, address: 0x80A4ACA8
class CharPanel : public OutfitChar {
    // total size: 0x98
    class BandUser * mUser; // offset 0x40, size 0x4
    class CompositeCharacter * mChar; // offset 0x44, size 0x4
    class TourCharLocal * mTourChar; // offset 0x48, size 0x4
    class MemStream mSavedTourChar; // offset 0x4C, size 0x20
};
// Range: 0x800D949C -> 0x800D9560
void * CharPanel::CharPanel(class CharPanel * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__9CharPanel;
    // -> struct [anonymous] __vt__10OutfitChar;
}

static class Symbol outfit; // size: 0x4, address: 0x80A4ACB0
static class Symbol select_instrument; // size: 0x4, address: 0x80A4ACB8
// Range: 0x800D9560 -> 0x800D9A64
void CharPanel::Unload(class CharPanel * const this /* r28 */) {
    // Local variables
    unsigned char dirty_save; // r30
    unsigned char dirty_upload; // r29
    class Symbol instrument; // r1+0x24
    class ObjDirItr ol; // r1+0x50
    class Message instrument_msg; // r1+0x48

    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12OutfitLoader;
    // -> class CharCache * TheCharCache;
    // -> static class Symbol select_instrument;
    // -> static class Symbol outfit;
}

// Range: 0x800D9A64 -> 0x800D9B08
void CharPanel::Enter(class CharPanel * const this /* r31 */) {
    // References
    // -> class CharCache * TheCharCache;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800D9B08 -> 0x800D9B18
unsigned char CharPanel::IsCharLoaded() {}

// Range: 0x800D9B18 -> 0x800D9B20
class TourCharLocal * CharPanel::GetTourChar() {}

// Range: 0x800D9B20 -> 0x800D9B28
class CompositeCharacter * CharPanel::GetChar() {}

// Range: 0x800D9B28 -> 0x800D9B70
void CharPanel::Save(class CharPanel * const this /* r31 */) {}

static class Symbol _s; // size: 0x4, address: 0x80A4ACC0
static class Symbol _s; // size: 0x4, address: 0x80A4ACC8
// Range: 0x800D9B70 -> 0x800D9D30
unsigned char CharPanel::SyncProperty(class CharPanel * const this /* r27 */, class DataNode & _val /* r31 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

static class Symbol _s; // size: 0x4, address: 0x80A4ACD0
// Range: 0x800D9D30 -> 0x800DA0E0
class DataNode CharPanel::Handle(class CharPanel * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0xC0
} __vt__9CharPanel; // size: 0xC0, address: 0x80883588
struct {
    // total size: 0x8
} __RTTI__9CharPanel; // size: 0x8, address: 0x80883678

