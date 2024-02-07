/*
    Compile unit: C:\rockband2\band2\src\meta\CharCreatorPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800D0EF0 -> 0x800D30E8
*/
class DataArray * types; // size: 0x4, address: 0x80A4AB40
class Symbol name; // size: 0x4, address: 0x80A4AB48
class CharCreatorPanel * TheCharCreatorPanel; // size: 0x4, address: 0x80A4AB4C
// Range: 0x800D0EF0 -> 0x800D0FC8
void * CharCreatorPanel::CharCreatorPanel(class CharCreatorPanel * const this /* r31 */) {
    // References
    // -> class CharCreatorPanel * TheCharCreatorPanel;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__16CharCreatorPanel;
    // -> struct [anonymous] __vt__10OutfitChar;
}

// Range: 0x800D1064 -> 0x800D10F4
void CharCreatorPanel::Enter(class CharCreatorPanel * const this /* r31 */) {
    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> const char * gNullStr;
    // -> class Symbol t;
}

// Range: 0x800D10F4 -> 0x800D1178
void CharCreatorPanel::Exit(class CharCreatorPanel * const this /* r31 */) {
    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> class Symbol t;
}

static class Symbol tour; // size: 0x4, address: 0x80A4AB54
static class Symbol char_names; // size: 0x4, address: 0x80A4AB5C
// Range: 0x800D1178 -> 0x800D13D0
void CharCreatorPanel::Load(class CharCreatorPanel * const this /* r31 */) {
    // Local variables
    class DataArray * names; // r30
    const char * path; // r28

    // References
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> static class Symbol char_names;
    // -> static class Symbol tour;
    // -> class CharCache * TheCharCache;
    // -> class InputMgr * TheInputMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800D13D0 -> 0x800D1458
unsigned char CharCreatorPanel::IsLoaded(class CharCreatorPanel * const this /* r29 */) {}

// Range: 0x800D1458 -> 0x800D1500
void CharCreatorPanel::FinishLoad(class CharCreatorPanel * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800D1500 -> 0x800D1570
void CharCreatorPanel::Unload(class CharCreatorPanel * const this /* r31 */) {}

// Range: 0x800D1570 -> 0x800D1800
void CharCreatorPanel::Poll(class CharCreatorPanel * const this /* r27 */) {
    // Local variables
    class CompositeCharacter * dude; // r27

    // References
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7UIPanel;
    // -> class ObjectDir * sMainDir;
    // -> class CharCache * TheCharCache;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800D1800 -> 0x800D1810
unsigned char CharCreatorPanel::IsCharLoaded() {}

// Range: 0x800D1810 -> 0x800D1874
class TourCharLocal * CharCreatorPanel::GetTourChar(class CharCreatorPanel * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800D1874 -> 0x800D1928
class CompositeCharacter * CharCreatorPanel::GetChar(class CharCreatorPanel * const this /* r30 */) {
    // References
    // -> class CharCache * TheCharCache;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800D1928 -> 0x800D1A54
char * CharCreatorPanel::RandomCharName(class CharCreatorPanel * const this /* r28 */) {
    // Local variables
    class BandUser * pOwnerUser; // r4
    class Profile * profile; // r30
    class TourCharLocal * tc; // r0
    class DataArray * n; // r29
    int i; // r28

    // References
    // -> class Debug TheDebug;
    // -> class ProfileMgr TheProfileMgr;
}

// Range: 0x800D1A54 -> 0x800D1B0C
class DataArray * CharCreatorPanel::NextPrefab(class CharCreatorPanel * const this /* r29 */, unsigned char advance /* r30 */) {
    // Local variables
    const class DataArray * character_list; // r31
}

// Range: 0x800D1B0C -> 0x800D1C60
void CharCreatorPanel::Request(class CharCreatorPanel * const this /* r29 */, class Symbol & gender /* r30 */) {
    // Local variables
    const class DataArray * character; // r31

    // References
    // -> class CharCache * TheCharCache;
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800D1C60 -> 0x800D1CF8
void CharCreatorPanel::Free(class CharCreatorPanel * const this /* r31 */) {
    // References
    // -> class CharCache * TheCharCache;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800D1CF8 -> 0x800D1D18
unsigned char CharCreatorPanel::IsCharNameUnique() {
    // Local variables
    class BandUser * pOwnerUser; // r4

    // References
    // -> class ProfileMgr TheProfileMgr;
}

static class Symbol outfit; // size: 0x4, address: 0x80A4AB64
struct Outfit {
    // total size: 0x10
    class Symbol mOutfit; // offset 0x0, size 0x4
    class Symbol mLocaleToken; // offset 0x4, size 0x4
    unsigned char mCanAfford; // offset 0x8, size 0x1
    int mCost; // offset 0xC, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct Outfit * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct Outfit * _M_start; // offset 0x0, size 0x4
    struct Outfit * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class OutfitProvider : public ListProvider, public Object {
    // total size: 0x48
    class Symbol mGender; // offset 0x2C, size 0x4
    class Symbol mCategoryName; // offset 0x30, size 0x4
    class DataArray * mCategory; // offset 0x34, size 0x4
    unsigned char mShowText; // offset 0x38, size 0x1
    class vector mOutfits; // offset 0x3C, size 0xC
};
// Range: 0x800D1D18 -> 0x800D2050
void CharCreatorPanel::AddCharToProfile(class CharCreatorPanel * const this /* r30 */) {
    // Local variables
    class BandUser * pOwnerUser; // r28
    class Profile * profile; // r31
    class Symbol gender; // r1+0x54
    class DataArrayPtr character; // r1+0x58
    class DataArray * outfits; // r28
    int i; // r27
    class Symbol cat; // r1+0x50
    class OutfitProvider * p; // r29
    class Symbol none; // r1+0x4C
    class Symbol current; // r1+0x48

    // References
    // -> const char * gNullStr;
    // -> class Shop * TheShop;
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> static class Symbol outfit;
    // -> class ProfileMgr TheProfileMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol sign_out; // size: 0x4, address: 0x80A4AB6C
static class Symbol on_owner_user_signed_out; // size: 0x4, address: 0x80A4AB74
static class Message msg; // size: 0x8, address: 0x80978070
// Range: 0x800D2050 -> 0x800D2270
class DataNode CharCreatorPanel::OnMsg(class CharCreatorPanel * const this /* r31 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> static class Symbol on_owner_user_signed_out;
    // -> class BandUI * TheBandUI;
    // -> static class Symbol sign_out;
}

// Range: 0x800D2270 -> 0x800D22A8
unsigned char CharCreatorPanel::IsCharFullyLoaded() {
    // References
    // -> class CharCache * TheCharCache;
}

// Range: 0x800D22A8 -> 0x800D22BC
unsigned char CharCreatorPanel::HasCharLoadStarted() {}

static class Symbol _s; // size: 0x4, address: 0x80A4AB7C
static class Symbol _s; // size: 0x4, address: 0x80A4AB84
static class Symbol _s; // size: 0x4, address: 0x80A4AB8C
static class Symbol _s; // size: 0x4, address: 0x80A4AB94
static class Symbol _s; // size: 0x4, address: 0x80A4AB9C
static class Symbol _s; // size: 0x4, address: 0x80A4ABA4
static class Symbol _s; // size: 0x4, address: 0x80A4ABAC
static class Symbol _s; // size: 0x4, address: 0x80A4ABB4
static class Symbol _s; // size: 0x4, address: 0x80A4ABBC
// Range: 0x800D22BC -> 0x800D2F60
class DataNode CharCreatorPanel::Handle(class CharCreatorPanel * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x54
    class MessageTimer _mt; // r1+0x70
    class DataNode r; // r1+0x68
    class DataNode _n; // r1+0x60

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__16SigninChangedMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
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

static class Symbol _s; // size: 0x4, address: 0x80A4ABC4
// Range: 0x800D2F60 -> 0x800D30E8
unsigned char CharCreatorPanel::SyncProperty(class CharCreatorPanel * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8BandUser;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

struct {
    // total size: 0xC0
} __vt__16CharCreatorPanel; // size: 0xC0, address: 0x80882390
struct {
    // total size: 0x8
} __RTTI__16CharCreatorPanel; // size: 0x8, address: 0x80882488
struct {
    // total size: 0x8
} __RTTI__10OutfitChar; // size: 0x8, address: 0x808824F0
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class Shop : public Object {
    // total size: 0x30
    class list mProviders; // offset 0x28, size 0x8
};

