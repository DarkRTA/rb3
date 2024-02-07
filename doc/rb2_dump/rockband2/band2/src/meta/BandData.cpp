/*
    Compile unit: C:\rockband2\band2\src\meta\BandData.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800B2800 -> 0x800B3DAC
*/
// Range: 0x800B2800 -> 0x800B2840
void * BandMember::BandMember(struct BandMember * const this /* r31 */) {}

// Range: 0x800B2840 -> 0x800B28BC
class BinStream & __ls(class BinStream & s /* r30 */, const struct BandMember & bm /* r31 */) {}

// Range: 0x800B28BC -> 0x800B2978
class BinStream & __rs(class BinStream & s /* r30 */, struct BandMember & bm /* r31 */) {
    // Local variables
    int ver; // r1+0xC
    class String ignoreName; // r1+0x10
}

class String sDefaultLogo; // size: 0xC, address: 0x80977BE4
// Range: 0x800B2978 -> 0x800B2998
void BandData::Init() {
    // References
    // -> class String sDefaultLogo;
}

// Range: 0x800B2998 -> 0x800B299C
void BandData::Terminate() {}

// Range: 0x800B299C -> 0x800B2B40
unsigned char BandData::IsMember(const class HxGuid & charGuid /* r29 */) {
    // Local variables
    class vector roster; // r1+0x30
    int i; // r30
}

static class Symbol band_profile_creation_info; // size: 0x4, address: 0x80A4A554
static class Symbol band_profile_creation_info_offline; // size: 0x4, address: 0x80A4A55C
// Range: 0x800B2B40 -> 0x800B2D44
char * BandData::GetCreationInfo(const class BandData * const this /* r30 */) {
    // Local variables
    class String date; // r1+0x38

    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> class Net TheNet;
    // -> static class Symbol band_profile_creation_info_offline;
    // -> static class Symbol band_profile_creation_info;
}

// Range: 0x800B2D44 -> 0x800B2E2C
int BandData::RosterSize() {
    // Local variables
    class vector r; // r1+0x1C
}

// Range: 0x800B2E2C -> 0x800B2E64
class Symbol BandData::StarRatingFormatted() {
    // References
    // -> class Scoring * TheScoring;
}

static class Symbol _s; // size: 0x4, address: 0x80A4A564
static class Symbol _s; // size: 0x4, address: 0x80A4A56C
static class Symbol _s; // size: 0x4, address: 0x80A4A574
static class Symbol _s; // size: 0x4, address: 0x80A4A57C
static class Symbol _s; // size: 0x4, address: 0x80A4A584
static class Symbol _s; // size: 0x4, address: 0x80A4A58C
static class Symbol _s; // size: 0x4, address: 0x80A4A594
static class Symbol _s; // size: 0x4, address: 0x80A4A59C
static class Symbol _s; // size: 0x4, address: 0x80A4A5A4
static class Symbol _s; // size: 0x4, address: 0x80A4A5AC
static class Symbol _s; // size: 0x4, address: 0x80A4A5B4
static class Symbol _s; // size: 0x4, address: 0x80A4A5BC
static class Symbol _s; // size: 0x4, address: 0x80A4A5C4
// Range: 0x800B2E64 -> 0x800B3D38
class DataNode BandData::Handle(class BandData * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x58
    class MessageTimer _mt; // r1+0x80
    class DataNode _n; // r1+0x60

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
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
    // total size: 0xB8
} __vt__8BandData; // size: 0xB8, address: 0x8087E2A0
struct {
    // total size: 0x8
} __RTTI__8BandData; // size: 0x8, address: 0x8087E378
// Range: 0x800B3D38 -> 0x800B3D84
static void __sinit_\BandData_cpp() {
    // References
    // -> class String sDefaultLogo;
}


