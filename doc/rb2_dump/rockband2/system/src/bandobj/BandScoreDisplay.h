/*
    Compile unit: C:\rockband2\system\src\bandobj\BandScoreDisplay.h
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8025D10C -> 0x8025D824
*/
// Range: 0x8025D10C -> 0x8025D1DC
void BandScoreDisplay::SetDigitMat(class BandScoreDisplay * const this /* r29 */, int meshIdx /* r30 */, class RndMat * mat /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8025D1DC -> 0x8025D220
void BandScoreDisplay::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8025D220 -> 0x8025D384
void BandScoreDisplay::PreLoad(class BandScoreDisplay * const this /* r30 */, class BinStream & s /* r31 */) {
    // Local variables
    int rev; // r1+0x14
    int tmp; // r1+0x10
    int tmp; // r1+0xC

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class list sRevs;
    // -> unsigned char gLoadingProxyFromDisk;
    // -> class Debug TheDebug;
}

// Range: 0x8025D384 -> 0x8025D648
class DataNode BandScoreDisplay::Handle(class BandScoreDisplay * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
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

// Range: 0x8025D648 -> 0x8025D68C
class Symbol BandScoreDisplay::ClassName() {
    // References
    // -> class Symbol name;
}

// Range: 0x8025D68C -> 0x8025D820
void BandScoreDisplay::SetType(class BandScoreDisplay * const this /* r29 */, class Symbol & BandScoreDisplay /* r30 */) {
    // Local variables
    class DataArray * def; // r4

    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
    // -> class DataArray * types;
    // -> class Symbol name;
}

// Range: 0x8025D820 -> 0x8025D824
void BandScoreDisplay::SetFrame() {}


