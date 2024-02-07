/*
    Compile unit: C:\rockband2\system\src\utl\TempoMap.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80624220 -> 0x80624268
*/
class SimpleTempoMap : public TempoMap {
    // total size: 0x8
    float mTempo; // offset 0x4, size 0x4
};
static class SimpleTempoMap gDefaultTempoMap; // size: 0x8, address: 0x8098A500
class TempoMap * TheTempoMap; // size: 0x4, address: 0x80A47BC8
// Range: 0x80624220 -> 0x80624228
void SetTheTempoMap() {
    // References
    // -> class TempoMap * TheTempoMap;
}

// Range: 0x80624228 -> 0x80624238
void ResetTheTempoMap() {
    // References
    // -> class TempoMap * TheTempoMap;
    // -> static class SimpleTempoMap gDefaultTempoMap;
}

struct {
    // total size: 0x28
} __vt__14SimpleTempoMap; // size: 0x28, address: 0x8092F460
struct {
    // total size: 0x8
} __RTTI__14SimpleTempoMap; // size: 0x8, address: 0x8092F4A8
// Range: 0x80624238 -> 0x80624268
static void __sinit_\TempoMap_cpp() {
    // References
    // -> struct [anonymous] __vt__14SimpleTempoMap;
    // -> static class SimpleTempoMap gDefaultTempoMap;
}


