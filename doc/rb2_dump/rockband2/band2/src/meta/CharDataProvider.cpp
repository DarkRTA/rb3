/*
    Compile unit: C:\rockband2\band2\src\meta\CharDataProvider.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800D5F7C -> 0x800D6ED8
*/
class CharDataProvider * TheCharDataProvider; // size: 0x4, address: 0x80A4AC08
char lhsName[256]; // size: 0x100, address: 0x809784B0
char rhsName[256]; // size: 0x100, address: 0x809785B0
class CharDataProvider : public ListProvider, public Object {
    // total size: 0x3C
    class Profile * mProfile; // offset 0x2C, size 0x4
    class vector mChars; // offset 0x30, size 0xC
};
// Range: 0x800D5F7C -> 0x800D6004
void * CharDataProvider::CharDataProvider(class CharDataProvider * const this /* r31 */) {
    // References
    // -> class ObjectDir * sMainDir;
    // -> struct [anonymous] __vt__16CharDataProvider;
    // -> struct [anonymous] __vt__12ListProvider;
}

// Range: 0x800D6004 -> 0x800D609C
void * CharDataProvider::~CharDataProvider(class CharDataProvider * const this /* r30 */) {}

// Range: 0x800D609C -> 0x800D60D0
void CharDataProvider::Init() {
    // References
    // -> class CharDataProvider * TheCharDataProvider;
}

// Range: 0x800D60D0 -> 0x800D60D4
void CharDataProvider::InitData() {}

static class Symbol name; // size: 0x4, address: 0x80A4AC10
static class Symbol instrument; // size: 0x4, address: 0x80A4AC18
// Range: 0x800D60D4 -> 0x800D61BC
char * CharDataProvider::Text(const class CharDataProvider * const this /* r28 */, int data /* r29 */, class Symbol & slot /* r30 */) {
    // Local variables
    class TourCharLocal * tc; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol instrument;
    // -> static class Symbol name;
}

// Range: 0x800D61BC -> 0x800D6208
class RndMat * CharDataProvider::Mat() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800D6208 -> 0x800D6220
int CharDataProvider::NumData() {}

// Range: 0x800D6220 -> 0x800D6228
unsigned char CharDataProvider::IsActive() {}

// Range: 0x800D6228 -> 0x800D6270
void CharDataProvider::DeleteCharacter(class CharDataProvider * const this /* r31 */) {
    // Local variables
    class TourCharLocal * tc; // r0

    // References
    // -> class ProfileMgr TheProfileMgr;
}

// Range: 0x800D6270 -> 0x800D62D8
void CharDataProvider::SetCharacterName(class CharDataProvider * const this /* r29 */, class String & Name /* r30 */) {
    // Local variables
    class TourCharLocal * tc; // r31

    // References
    // -> class ProfileMgr TheProfileMgr;
}

// Range: 0x800D62D8 -> 0x800D6328
class String CharDataProvider::GetCharacterName() {
    // Local variables
    class TourCharLocal * tc; // r0
}

// Range: 0x800D6328 -> 0x800D63F4
void CharDataProvider::Init(class CharDataProvider * const this /* r29 */) {
    // Local variables
    class User * pUser; // r30

    // References
    // -> class ProfileMgr TheProfileMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class UserMgr * TheUserMgr;
}

// Range: 0x800D63F4 -> 0x800D640C
int CharDataProvider::NumCharacters() {}

// Range: 0x800D640C -> 0x800D64A4
class TourCharLocal * CharDataProvider::GetTourChar(const class CharDataProvider * const this /* r30 */, int num /* r31 */) {
    // Local variables
    class TourCharLocal * tc; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800D64A4 -> 0x800D6614
void CharDataProvider::GatherCharacters(class CharDataProvider * const this /* r30 */) {
    // Local variables
    int i; // r31
    class TourCharLocal * tc; // r1+0x20

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct CharSorter {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
static class Symbol _s; // size: 0x4, address: 0x80A4AC20
static class Symbol _s; // size: 0x4, address: 0x80A4AC28
static class Symbol _s; // size: 0x4, address: 0x80A4AC30
static class Symbol _s; // size: 0x4, address: 0x80A4AC38
static class Symbol _s; // size: 0x4, address: 0x80A4AC40
static class Symbol _s; // size: 0x4, address: 0x80A4AC48
// Range: 0x800D6614 -> 0x800D6ED8
class DataNode CharDataProvider::Handle(class CharDataProvider * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x38
    class MessageTimer _mt; // r1+0x60
    class DataNode _n; // r1+0x40

    // References
    // -> class Debug TheDebug;
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
    // total size: 0x9C
} __vt__16CharDataProvider; // size: 0x9C, address: 0x80882E60
struct {
    // total size: 0x8
} __RTTI__16CharDataProvider; // size: 0x8, address: 0x80882F30
struct {
    // total size: 0x8
} __RTTI__PP13TourCharLocal; // size: 0x8, address: 0x80882FA0

