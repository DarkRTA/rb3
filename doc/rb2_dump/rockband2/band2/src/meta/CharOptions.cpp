/*
    Compile unit: C:\rockband2\band2\src\meta\CharOptions.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800D8758 -> 0x800D944C
*/
// Range: 0x800D8758 -> 0x800D87E8
void * GameplayOptions::GameplayOptions(class GameplayOptions * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__15GameplayOptions;
}

// Range: 0x800D87E8 -> 0x800D8880
class GameplayOptions & GameplayOptions::__as(class GameplayOptions * const this /* r30 */, const class GameplayOptions & rhs /* r31 */) {}

// Range: 0x800D8880 -> 0x800D88EC
void GameplayOptions::SetMicGain(class GameplayOptions * const this /* r30 */, int ixVol /* r31 */) {
    // References
    // -> class ProfileMgr TheProfileMgr;
}

// Range: 0x800D88EC -> 0x800D8958
void GameplayOptions::SetVocalVolume(class GameplayOptions * const this /* r30 */, int ixVol /* r31 */) {
    // References
    // -> class ProfileMgr TheProfileMgr;
}

// Range: 0x800D8958 -> 0x800D8974
void GameplayOptions::SetLefty() {}

// Range: 0x800D8974 -> 0x800D8990
void GameplayOptions::SetVocalStyle() {}

// Range: 0x800D8990 -> 0x800D8A44
void GameplayOptions::Save(class GameplayOptions * const this /* r30 */, class BinStream & s /* r31 */) {}

// Range: 0x800D8A44 -> 0x800D8AF8
void GameplayOptions::Load(class GameplayOptions * const this /* r30 */, class BinStream & s /* r31 */) {
    // Local variables
    int ver; // r1+0x10
    int i; // r1+0xC
}

// Range: 0x800D8AF8 -> 0x800D8B00
int GameplayOptions::SaveSize() {}

static class Symbol _s; // size: 0x4, address: 0x80A4AC64
static class Symbol _s; // size: 0x4, address: 0x80A4AC6C
static class Symbol _s; // size: 0x4, address: 0x80A4AC74
static class Symbol _s; // size: 0x4, address: 0x80A4AC7C
static class Symbol _s; // size: 0x4, address: 0x80A4AC84
static class Symbol _s; // size: 0x4, address: 0x80A4AC8C
static class Symbol _s; // size: 0x4, address: 0x80A4AC94
static class Symbol _s; // size: 0x4, address: 0x80A4AC9C
// Range: 0x800D8B00 -> 0x800D944C
class DataNode GameplayOptions::Handle(class GameplayOptions * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x3C
    class MessageTimer _mt; // r1+0x40

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x8C
} __vt__15GameplayOptions; // size: 0x8C, address: 0x808831A0
struct {
    // total size: 0x8
} __RTTI__15GameplayOptions; // size: 0x8, address: 0x80883258

