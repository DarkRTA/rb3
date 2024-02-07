/*
    Compile unit: C:\rockband2\system\src\synth\OggMap.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80580E2C -> 0x805811A8
*/
class OggMap {
    // total size: 0x14
public:
    void * __vptr$; // offset 0x0, size 0x4
private:
    int mGran; // offset 0x4, size 0x4
    class vector mLookup; // offset 0x8, size 0xC
};
// Range: 0x80580E2C -> 0x80580EE4
void * OggMap::OggMap(class OggMap * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__6OggMap;
}

// Range: 0x80580EE4 -> 0x80581030
void * OggMap::~OggMap(class OggMap * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__6OggMap;
}

// Range: 0x80581030 -> 0x805810C4
void OggMap::Read(class OggMap * const this /* r30 */, class BinStream & s /* r31 */) {
    // Local variables
    int version; // r1+0x8

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805810C4 -> 0x805811A8
void OggMap::GetSeekPos(class OggMap * const this /* r28 */, int sampTarget /* r29 */, int & seekPos /* r30 */, int & actSamp /* r31 */) {
    // Local variables
    int idx; // r5

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0xC
} __vt__6OggMap; // size: 0xC, address: 0x8091D9F4
struct {
    // total size: 0x8
} __RTTI__6OggMap; // size: 0x8, address: 0x8091DA08

