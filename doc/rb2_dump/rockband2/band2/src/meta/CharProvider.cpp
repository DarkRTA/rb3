/*
    Compile unit: C:\rockband2\band2\src\meta\CharProvider.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800DA6F0 -> 0x800DCA70
*/
class CharProvider : public ListProvider, public Object {
    // total size: 0x54
    class vector mCharList; // offset 0x2C, size 0xC
    int mSlotNum; // offset 0x38, size 0x4
    class Profile * mProfile; // offset 0x3C, size 0x4
    class vector mSavedList; // offset 0x40, size 0xC
    class PrefabChar * mPrefabRandom; // offset 0x4C, size 0x4
    int mLastPos; // offset 0x50, size 0x4
};
// Range: 0x800DA6F0 -> 0x800DA784
void * CharProvider::CharProvider(class CharProvider * const this /* r30 */, int slotNum /* r31 */) {
    // References
    // -> struct [anonymous] __vt__12CharProvider;
    // -> struct [anonymous] __vt__12ListProvider;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct CharEntry * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct CharEntry * _M_start; // offset 0x0, size 0x4
    struct CharEntry * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x800DA784 -> 0x800DA924
void * CharProvider::~CharProvider(class CharProvider * const this /* r30 */) {}

// Range: 0x800DA924 -> 0x800DA928
void CharProvider::Reload() {}

// Range: 0x800DA928 -> 0x800DA94C
unsigned char CharProvider::IsCreateNew() {}

// Range: 0x800DA94C -> 0x800DA988
unsigned char CharProvider::IsChar() {}

enum EntryType {
    kT_Heading = 0,
    kT_Character = 1,
    kT_Prefab = 2,
    kT_Create = 3,
    kT_RandomPrefab = 4,
};
static class Symbol is_tour; // size: 0x4, address: 0x80A4ACDC
// Range: 0x800DA988 -> 0x800DAA78
int CharProvider::FindPosFromChar(const class CharProvider * const this /* r31 */) {
    // Local variables
    int cEntry; // r7
    int iEntry; // r3
    unsigned char isTour; // r0

    // References
    // -> class GameMode * TheGameMode;
    // -> static class Symbol is_tour;
}

// Range: 0x800DAA78 -> 0x800DAD38
void CharProvider::SaveRelativePos(class CharProvider * const this /* r29 */, int pos /* r30 */) {
    // Local variables
    int cEntry; // r3
    int iEntry; // r5
}

// Range: 0x800DAD38 -> 0x800DADAC
unsigned char __eq() {}

static class Symbol is_tour; // size: 0x4, address: 0x80A4ACE4
// Range: 0x800DADAC -> 0x800DAEBC
int CharProvider::GetRelativePos(const class CharProvider * const this /* r31 */) {
    // Local variables
    int cEntry; // r30
    const struct CharEntry * itSaved; // [invalid]
    const struct CharEntry & entrySaved; // r29
    int iEntry; // r28
    unsigned char isTour; // r0

    // References
    // -> class GameMode * TheGameMode;
    // -> static class Symbol is_tour;
}

// Range: 0x800DAEBC -> 0x800DAEC0
void CharProvider::InitData() {}

static class Symbol character; // size: 0x4, address: 0x80A4ACEC
static class Symbol option; // size: 0x4, address: 0x80A4ACF4
static class Symbol heading; // size: 0x4, address: 0x80A4ACFC
// Range: 0x800DAEC0 -> 0x800DB06C
char * CharProvider::Text(const class CharProvider * const this /* r28 */, int data /* r29 */, class Symbol & slot /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static class Symbol heading;
    // -> static class Symbol option;
    // -> static class Symbol character;
}

// Range: 0x800DB06C -> 0x800DB0B8
class RndMat * CharProvider::Mat() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800DB0B8 -> 0x800DB0E0
int CharProvider::NumData() {}

// Range: 0x800DB0E0 -> 0x800DB100
unsigned char CharProvider::IsActive() {
    // Local variables
    enum EntryType t; // r3
}

// Range: 0x800DB100 -> 0x800DB168
unsigned char CharNameCmp(const class TourCharLocal * lhs /* r30 */) {}

// Range: 0x800DB168 -> 0x800DB1D0
unsigned char CharEntryNameCmp(const struct CharEntry & lhs /* r30 */) {}

struct CharEntry {
    // total size: 0x14
    class String mStr; // offset 0x0, size 0xC
    class CharData * mChar; // offset 0xC, size 0x4
    enum EntryType mType; // offset 0x10, size 0x4
};
// Range: 0x800DB1D0 -> 0x800DB3B8
void CharProvider::AddToCharList(class CharProvider * const this /* r30 */, const char * strHeading /* r28 */, const class vector & chars /* r31 */) {
    // Local variables
    struct CharEntry entry; // r1+0x18
    class TourCharLocal * const * it; // r28
    class TourCharLocal * pChar; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800DB3B8 -> 0x800DB4A4
void CharProvider::AddToCharList(class CharProvider * const this /* r29 */, const class vector & chars /* r30 */) {
    // Local variables
    const struct CharEntry * it; // r31
}

static class Symbol is_tour; // size: 0x4, address: 0x80A4AD04
static class Symbol char_provider_create_new; // size: 0x4, address: 0x80A4AD0C
static class Symbol char_provider_my_members; // size: 0x4, address: 0x80A4AD14
static class Symbol char_provider_my_chars; // size: 0x4, address: 0x80A4AD1C
static class Symbol char_provider_profile_possessive; // size: 0x4, address: 0x80A4AD24
static class Symbol char_provider_profile_members; // size: 0x4, address: 0x80A4AD2C
static class Symbol char_provider_profile_chars; // size: 0x4, address: 0x80A4AD34
static class Symbol char_provider_prefabs; // size: 0x4, address: 0x80A4AD3C
static class Symbol char_provider_prefab_random; // size: 0x4, address: 0x80A4AD44
// Range: 0x800DB4A4 -> 0x800DC3D0
void CharProvider::GenerateCharEntryList(class CharProvider * const this /* r26 */) {
    // Local variables
    class BandUser * pUser; // r29
    struct CharEntry entry; // r1+0x140
    unsigned char isTour; // r0
    class vector users; // r1+0x134
    class Profile * pProfile; // r29
    class vector memberChars; // r1+0x128
    class TourBand * pBand; // r25
    class vector roster; // r1+0x11C
    struct BandMember * it; // r25
    class TourCharLocal * pChar; // r1+0xDC
    const char * strHeading; // r0
    class vector chars; // r1+0x110
    class TourCharLocal * * itMember; // r25
    class TourCharLocal * pCharMember; // r27
    class TourCharLocal * * it; // r28
    class TourCharLocal * pChar; // r29
    const char * strHeading; // r0
    class BandUser * * it; // r28
    class BandUser * pUserOther; // r25
    class Profile * pProfileOther; // r27
    class vector chars; // r1+0x104
    const char * strHeadingFmt; // r24
    const char * strHeading; // r0
    class vector memberChars; // r1+0xF8
    class TourBand * pBand; // r24
    class vector roster; // r1+0xEC
    struct BandMember * it; // r24
    class TourCharLocal * pChar; // r1+0xD8
    const char * strHeading; // r0
    class TourCharLocal * * itMember; // r24
    class TourCharLocal * pCharMember; // r25
    class TourCharLocal * * it; // r27
    class TourCharLocal * pChar; // r23
    const char * strHeading; // r0
    class vector prefabs; // r1+0xE0
    int cChar; // r0
    int iChar; // r23
    class PrefabChar * pPrefab; // r24

    // References
    // -> const char * gNullStr;
    // -> static class Symbol char_provider_prefab_random;
    // -> static class Symbol char_provider_prefabs;
    // -> static class Symbol char_provider_profile_chars;
    // -> static class Symbol char_provider_profile_members;
    // -> class PlatformMgr ThePlatformMgr;
    // -> static class Symbol char_provider_profile_possessive;
    // -> static class Symbol char_provider_my_chars;
    // -> static class Symbol char_provider_my_members;
    // -> class Tour * TheTour;
    // -> class ProfileMgr TheProfileMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol char_provider_create_new;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol is_tour;
    // -> class BandUserMgr * TheBandUserMgr;
}

struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
// Range: 0x800DC3D0 -> 0x800DC3DC
void CharProvider::ClearRandomPrefab() {}

static class Symbol _s; // size: 0x4, address: 0x80A4AD4C
static class Symbol _s; // size: 0x4, address: 0x80A4AD54
static class Symbol _s; // size: 0x4, address: 0x80A4AD5C
static class Symbol _s; // size: 0x4, address: 0x80A4AD64
// Range: 0x800DC3DC -> 0x800DCA70
class DataNode CharProvider::Handle(class CharProvider * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x30
    class MessageTimer _mt; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class Debug TheDebug;
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
} __vt__12CharProvider; // size: 0x9C, address: 0x80883B6C
struct {
    // total size: 0x8
} __RTTI__12CharProvider; // size: 0x8, address: 0x80883C38
struct {
    // total size: 0x8
} __RTTI__PQ212CharProvider9CharEntry; // size: 0x8, address: 0x80883CB0

