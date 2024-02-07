/*
    Compile unit: C:\rockband2\band2\src\meta\CharData.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800D3410 -> 0x800D5684
*/
class DataArray * sTrackIcons; // size: 0x4, address: 0x80A4ABC8
// Range: 0x800D3410 -> 0x800D3464
void CharData::Init() {
    // References
    // -> class DataArray * sTrackIcons;
}

// Range: 0x800D3464 -> 0x800D3514
void * CharData::CharData(class CharData * const this /* r30 */, class DataArray * char_data /* r31 */) {
    // Local variables
    int i; // r5

    // References
    // -> struct [anonymous] __vt__8CharData;
}

// Range: 0x800D3514 -> 0x800D359C
void * CharData::~CharData(class CharData * const this /* r29 */) {}

// Range: 0x800D359C -> 0x800D35C8
char * CharData::InstrumentIcon() {}

// Range: 0x800D35C8 -> 0x800D3668
char * CharData::TrackIcon(const class CharData * const this /* r30 */, class Symbol & track /* r31 */) {
    // Local variables
    enum TrackType tt; // r0
    enum ControllerType ct; // r0

    // References
    // -> class DataArray * sTrackIcons;
}

// Range: 0x800D3668 -> 0x800D36F4
enum Difficulty CharData::TourWinDiff(const class CharData * const this /* r30 */, enum ControllerType ct /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol drum; // size: 0x4, address: 0x80A4ABD0
static class Symbol none; // size: 0x4, address: 0x80A4ABD8
class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class OutfitLoader * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x800D36F4 -> 0x800D3A4C
void CharData::ConfigureChar(class CompositeCharacter * cc /* r30 */) {
    // Local variables
    class ObjDirItr ol; // r1+0x1C

    // References
    // -> struct [anonymous] __RTTI__6RndTex;
    // -> class Tour * TheTour;
    // -> struct [anonymous] __RTTI__6RndMat;
    // -> static class Symbol none;
    // -> static class Symbol drum;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12OutfitLoader;
    // -> class CharCache * TheCharCache;
}

static class Symbol _s; // size: 0x4, address: 0x80A4ABE0
static class Symbol _s; // size: 0x4, address: 0x80A4ABE8
static class Symbol _s; // size: 0x4, address: 0x80A4ABF0
static class Symbol _s; // size: 0x4, address: 0x80A4ABF8
// Range: 0x800D3A4C -> 0x800D40EC
class DataNode CharData::Handle(class CharData * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x44
    class MessageTimer _mt; // r1+0x50
    class DataNode _n; // r1+0x48

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

// Range: 0x800D40EC -> 0x800D4150
class PrefabChar * PrefabChar::Create(class DataArray * char_data /* r30 */) {}

// Range: 0x800D4150 -> 0x800D41DC
void * PrefabChar::PrefabChar(class PrefabChar * const this /* r30 */, class DataArray * char_data /* r31 */) {
    // References
    // -> struct [anonymous] __vt__10PrefabChar;
}

// Range: 0x800D41DC -> 0x800D425C
void * PrefabChar::PrefabChar(class PrefabChar * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__10PrefabChar;
}

// Range: 0x800D425C -> 0x800D42E4
void * PrefabChar::~PrefabChar(class PrefabChar * const this /* r29 */) {}

// Range: 0x800D42E4 -> 0x800D46D0
class DataNode PrefabChar::Handle(class PrefabChar * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x38
    class DataNode _n; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> unsigned char sActive;
}

class vector sPrefabs; // size: 0xC, address: 0x80978084
static class Rand sRand; // size: 0x410, address: 0x80978090
static int sNextRand[4]; // size: 0x10, address: 0x809784A0
// Range: 0x800D46D0 -> 0x800D481C
static class DataNode OnAvailablePrefab(class DataArray * a /* r29 */) {
    // Local variables
    class Symbol gender; // r1+0x18
    unsigned char only_selectable; // r30
    class vector users; // r1+0x1C

    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> const char * gNullStr;
}

// Range: 0x800D481C -> 0x800D488C
static class DataNode OnFindPrefab(class DataArray * a /* r31 */) {}

// Range: 0x800D488C -> 0x800D4A58
void PrefabChar::Init() {
    // Local variables
    class DataArray * prefabs; // r31
    int i; // r28

    // References
    // -> class vector sPrefabs;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std17_List_node<PFv_v>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Debug TheDebug;
}

// Range: 0x800D4A58 -> 0x800D4ADC
void PrefabChar::Terminate() {
    // References
    // -> class vector sPrefabs;
}

// Range: 0x800D4ADC -> 0x800D4B3C
unsigned char __eq(class Symbol & rhs /* r30 */) {}

// Range: 0x800D4B3C -> 0x800D4BC0
class PrefabChar * PrefabChar::Find() {
    // Local variables
    class PrefabChar * * c; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class vector sPrefabs;
}

// Range: 0x800D4BC0 -> 0x800D4C30
class PrefabChar * PrefabChar::Get(int idx /* r31 */) {
    // References
    // -> class vector sPrefabs;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800D4C30 -> 0x800D4DEC
unsigned char PrefabChar::IsValid(const class PrefabChar * p /* r1+0x8 */, class Symbol & gender /* r26 */, class DataArray * group /* r31 */, class vector & users /* r27 */, class list * exclude /* r29 */, unsigned char only_selectable /* r28 */) {
    // Local variables
    unsigned char found; // r29
    int j; // r28

    // References
    // -> class ProfileMgr TheProfileMgr;
    // -> const char * gNullStr;
}

// Range: 0x800D4DEC -> 0x800D52A0
class PrefabChar * PrefabChar::Available(int user_num /* r22 */, class Symbol & gender /* r23 */, class DataArray * group /* r24 */, class vector & users /* r25 */, class list * exclude /* r26 */, unsigned char peek /* r27 */, unsigned char only_selectable /* r28 */) {
    // Local variables
    unsigned char * check; // r29
    int i; // r4
    class PrefabChar * * c; // r20
    class PrefabChar * cd; // r19
    int i; // r18
    int i; // r18
    class vector candidates; // r1+0x44
    class PrefabChar * * c; // r29
    class PrefabChar * cd; // r1+0x40
    class PrefabChar * * c; // r18
    class PrefabChar * cd; // r1+0x3C
    int which; // r18

    // References
    // -> static class Rand sRand;
    // -> static int sNextRand[4];
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> class vector sPrefabs;
}

static class Symbol selectable; // size: 0x4, address: 0x80A4AC00
// Range: 0x800D52A0 -> 0x800D5334
unsigned char PrefabChar::IsSelectable(const class PrefabChar * const this /* r31 */) {
    // Local variables
    class DataArray * pData; // r31

    // References
    // -> static class Symbol selectable;
}

// Range: 0x800D5334 -> 0x800D54EC
class PrefabChar * PrefabChar::GetRandomSelectablePrefab() {
    // Local variables
    class vector users; // r1+0x28
    class vector candidates; // r1+0x1C
    class PrefabChar * * it; // r31
    class PrefabChar * pPrefab; // r1+0x18
    int iPrefab; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
    // -> class vector sPrefabs;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x800D54EC -> 0x800D550C
int PrefabChar::Num() {
    // References
    // -> class vector sPrefabs;
}

// Range: 0x800D550C -> 0x800D5570
void PrefabChar::SetRandomSeed() {
    // Local variables
    int i; // r31

    // References
    // -> static int sNextRand[4];
    // -> static class Rand sRand;
}

// Range: 0x800D5570 -> 0x800D55D8
char * PrefabChar::CharName() {}

struct {
    // total size: 0x8
} __RTTI__12OutfitLoader; // size: 0x8, address: 0x80882AA0
struct {
    // total size: 0x8
} __RTTI__11MergeFilter; // size: 0x8, address: 0x80882AB8
struct {
    // total size: 0x8
} __RTTI__Q29DirLoader8Callback; // size: 0x8, address: 0x80882B00
struct {
    // total size: 0x90
} __vt__10PrefabChar; // size: 0x90, address: 0x80882B08
struct {
    // total size: 0x90
} __vt__8CharData; // size: 0x90, address: 0x80882BD0
struct {
    // total size: 0x8
} __RTTI__PP10PrefabChar; // size: 0x8, address: 0x80882CF8
struct _OKToMemCpy {
    // total size: 0x1
};
// Range: 0x800D55D8 -> 0x800D5634
static void __sinit_\CharData_cpp() {
    // References
    // -> static class Rand sRand;
    // -> class vector sPrefabs;
}


