/*
    Compile unit: C:\rockband2\band2\src\meta\TourCharLocal.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x801C9914 -> 0x801CF110
*/
// Range: 0x801C9914 -> 0x801C9944
unsigned char __eq() {}

// Range: 0x801C9944 -> 0x801C9974
unsigned char __eq() {}

static class Symbol outfit; // size: 0x4, address: 0x80A4DAF4
static class Symbol colors; // size: 0x4, address: 0x80A4DAFC
static class Symbol tour; // size: 0x4, address: 0x80A4DB04
static class Symbol default_hometown; // size: 0x4, address: 0x80A4DB0C
static class Symbol default_money; // size: 0x4, address: 0x80A4DB14
// Range: 0x801C9974 -> 0x801C9ECC
void * TourCharLocal::TourCharLocal(class TourCharLocal * const this /* r26 */, const class DataArray * char_data /* r23 */) {
    // Local variables
    class DataArray * outs; // r28
    int i; // r27
    class Symbol category; // r1+0x5C
    class DataArray * color_array; // r24
    struct OutfitPref pref; // r1+0x90
    int c; // r23
    int color_idx; // r25
    class DataArray * t; // r23

    // References
    // -> static class Symbol default_money;
    // -> static class Symbol default_hometown;
    // -> static class Symbol tour;
    // -> struct [anonymous] __RTTI__Pi;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std41_List_node<Q213TourCharLocal10OutfitPref>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol colors;
    // -> static class Symbol outfit;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__13TourCharLocal;
}

class _List_node : public _List_node_base {
    // total size: 0x20
public:
    struct OutfitPref _M_data; // offset 0x8, size 0x18
};
class _List_node : public _List_node_base {
    // total size: 0x10
public:
    struct ClosetOutfit _M_data; // offset 0x8, size 0x8
};
class _List_node : public _List_node_base {
    // total size: 0x1C
public:
    struct OutfitGroup _M_data; // offset 0x8, size 0x14
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std41_List_node<Q213TourCharLocal10OutfitPref>; // size: 0x8, address: 0x808A3660
static class Symbol outfit; // size: 0x4, address: 0x80A4DB1C
static class Symbol colors; // size: 0x4, address: 0x80A4DB24
// Range: 0x801C9ECC -> 0x801CA524
void TourCharLocal::InitOutfitGroups(class TourCharLocal * const this /* r22 */) {
    // Local variables
    class DataArray * outs; // r28
    const class DataArray * categories; // r27
    int i; // r26
    class Symbol category; // r1+0xD4
    class Symbol outfit; // r1+0xD0
    class DataArray * cat; // r25
    class DataArray * groups; // r24
    struct OutfitGroup * group; // r30
    struct OutfitGroup new_group; // r1+0x128
    int g; // r23
    class Symbol group_name; // r1+0xCC

    // References
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std44_List_node<Q211stlpmtx_std15pair<6Symbol,i>>;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std50_List_node<Q211stlpmtx_std21pair<6Symbol,6Symbol>>;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std42_List_node<Q213TourCharLocal11OutfitGroup>;
    // -> unsigned char gStlAllocNameLookup;
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol colors;
    // -> static class Symbol outfit;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
class _List_node : public _List_node_base {
    // total size: 0x10
public:
    struct pair _M_data; // offset 0x8, size 0x8
};
class _List_node : public _List_node_base {
    // total size: 0x10
public:
    struct pair _M_data; // offset 0x8, size 0x8
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std50_List_node<Q211stlpmtx_std21pair<6Symbol,6Symbol>>; // size: 0x8, address: 0x808A36E8
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std44_List_node<Q211stlpmtx_std15pair<6Symbol,i>>; // size: 0x8, address: 0x808A3730
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std42_List_node<Q213TourCharLocal11OutfitGroup>; // size: 0x8, address: 0x808A3770
// Range: 0x801CA524 -> 0x801CA65C
void * TourCharLocal::TourCharLocal(class TourCharLocal * const this /* r29 */, class BinStream & s /* r30 */) {
    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__13TourCharLocal;
}

// Range: 0x801CA65C -> 0x801CA778
void * TourCharLocal::~TourCharLocal(class TourCharLocal * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__13TourCharLocal;
}

// Range: 0x801CA778 -> 0x801CA780
class Symbol TourCharLocal::Hometown() {}

// Range: 0x801CA780 -> 0x801CA788
int TourCharLocal::Money() {}

// Range: 0x801CA788 -> 0x801CA790
int TourCharLocal::MoneySpentOnOutfits() {}

// Range: 0x801CA790 -> 0x801CA864
unsigned char TourCharLocal::HasOutfit(const class TourCharLocal * const this /* r29 */, class Symbol & category /* r30 */, class Symbol & outfit /* r31 */) {
    // Local variables
    struct ClosetOutfit search; // r1+0x38
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x801CA864 -> 0x801CA86C
char * TourCharLocal::CharName() {}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x801CA86C -> 0x801CAB6C
void TourCharLocal::UpdatePref(class TourCharLocal * const this /* r29 */, class CompositeCharacter * cc /* r30 */, class Symbol & category /* r31 */, class Symbol & outfit /* r27 */) {
    // Local variables
    struct OutfitPref s; // r1+0x58
    struct _List_iterator o; // r1+0x54
    class OutfitConfig * oc; // r27
    int i; // r28

    // References
    // -> struct [anonymous] __RTTI__Pi;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std41_List_node<Q213TourCharLocal10OutfitPref>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol tour; // size: 0x4, address: 0x80A4DB2C
static class Symbol max_money; // size: 0x4, address: 0x80A4DB34
// Range: 0x801CAB6C -> 0x801CAC18
int TourCharLocal::MaxMoney() {
    // References
    // -> static class Symbol max_money;
    // -> static class Symbol tour;
}

// Range: 0x801CAC18 -> 0x801CAC30
unsigned char __eq() {}

// Range: 0x801CAC30 -> 0x801CACCC
class Symbol TourCharLocal::SelectedOutfitGroup(const class TourCharLocal * const this /* r30 */, class Symbol & category /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801CACCC -> 0x801CADB0
unsigned char TourCharLocal::HasGroupSelection(const class TourCharLocal * const this /* r28 */, class Symbol & category /* r27 */, class Symbol & group /* r26 */) {
    // Local variables
    struct OutfitGroup * g; // r0
    class DataArray * outfits; // r29
    int num; // r28
    int i; // r27
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x801CADB0 -> 0x801CAE24
struct OutfitGroup * TourCharLocal::FindOutfitGroup(const class TourCharLocal * const this /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x24
}

// Range: 0x801CAE24 -> 0x801CAEC4
class Symbol TourCharLocal::GroupName(class Symbol & outfit /* r29 */) {
    // Local variables
    const char * group_name; // r0
    class String group_str; // r1+0x10
}

static class Symbol hair; // size: 0x4, address: 0x80A4DB3C
// Range: 0x801CAEC4 -> 0x801CAF84
void TourCharLocal::ConfigureChar(class TourCharLocal * const this /* r30 */, class CompositeCharacter * cc /* r31 */) {
    // Local variables
    class Symbol selected; // r1+0x18
    int hair_color; // r0

    // References
    // -> static class Symbol hair;
}

static class Symbol tour; // size: 0x4, address: 0x80A4DB44
static class Symbol update_char_appearance; // size: 0x4, address: 0x80A4DB4C
class DataArrayMsg : public NetMessage {
    // total size: 0x24
    class MemStream mBuffer; // offset 0x4, size 0x20
};
// Range: 0x801CAF84 -> 0x801CB280
void TourCharLocal::UpdateAppearance(class TourCharLocal * const this /* r30 */, int player_num /* r31 */) {
    // Local variables
    class DataArrayPtr data; // r1+0x40
    class DataArrayPtr msg; // r1+0x38
    class DataArrayMsg dataMsg; // r1+0x48

    // References
    // -> class Net TheNet;
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> static class Symbol update_char_appearance;
    // -> static class Symbol tour;
}

static class Symbol skin_color_index; // size: 0x4, address: 0x80A4DB54
// Range: 0x801CB280 -> 0x801CB3CC
void TourCharLocal::SetSkinColor(class TourCharLocal * const this /* r29 */, class CompositeCharacter * cc /* r30 */, int new_color_index /* r31 */) {
    // Local variables
    class DataNode & nodeSkinColorIndex; // r27

    // References
    // -> static class Symbol skin_color_index;
}

static class Symbol eye_color_index; // size: 0x4, address: 0x80A4DB5C
// Range: 0x801CB3CC -> 0x801CB514
void TourCharLocal::SetEyeColor(class TourCharLocal * const this /* r29 */, class CompositeCharacter * cc /* r30 */, int new_color_index /* r31 */) {
    // Local variables
    class DataNode & old_index; // r27

    // References
    // -> static class Symbol eye_color_index;
}

static class Symbol eyebrow_color_index; // size: 0x4, address: 0x80A4DB64
// Range: 0x801CB514 -> 0x801CB65C
void TourCharLocal::SetEyebrowColor(class TourCharLocal * const this /* r29 */, class CompositeCharacter * cc /* r30 */, int new_index /* r31 */) {
    // Local variables
    class DataNode & old_index; // r27

    // References
    // -> static class Symbol eyebrow_color_index;
}

static class Symbol tattoo_prefab; // size: 0x4, address: 0x80A4DB6C
// Range: 0x801CB65C -> 0x801CB7BC
void TourCharLocal::SetTattooPrefab(class TourCharLocal * const this /* r29 */, class CompositeCharacter * cc /* r30 */, class Symbol & tattoo_name /* r31 */) {
    // Local variables
    class DataArray * tattoo_data; // r0
    class DataNode & tattoo_old; // r27

    // References
    // -> static class Symbol tattoo_prefab;
}

// Range: 0x801CB7BC -> 0x801CB924
void TourCharLocal::SetOutfitColor(class TourCharLocal * const this /* r26 */, class CompositeCharacter * cc /* r27 */, class Symbol & category /* r28 */, int option_index /* r29 */, int color_index /* r30 */) {
    // Local variables
    struct OutfitPref & pref; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol weight; // size: 0x4, address: 0x80A4DB74
// Range: 0x801CB924 -> 0x801CBA6C
void TourCharLocal::SetWeight(class TourCharLocal * const this /* r30 */, class CompositeCharacter * cc /* r31 */, float new_weight /* f31 */) {
    // Local variables
    class DataNode & nodeWeight; // r27

    // References
    // -> static class Symbol weight;
}

static class Symbol height; // size: 0x4, address: 0x80A4DB7C
// Range: 0x801CBA6C -> 0x801CBBB4
void TourCharLocal::SetHeight(class TourCharLocal * const this /* r30 */, class CompositeCharacter * cc /* r31 */, float new_height /* f31 */) {
    // Local variables
    class DataNode & nodeHeight; // r27

    // References
    // -> static class Symbol height;
}

static class Symbol attitude; // size: 0x4, address: 0x80A4DB84
// Range: 0x801CBBB4 -> 0x801CBCFC
void TourCharLocal::SetAttitude(class TourCharLocal * const this /* r29 */, class CompositeCharacter * cc /* r30 */, int new_attitude /* r31 */) {
    // Local variables
    class DataNode & nodeAttitude; // r27

    // References
    // -> static class Symbol attitude;
}

// Range: 0x801CBCFC -> 0x801CBD80
void TourCharLocal::SetMoney(class TourCharLocal * const this /* r30 */, int money /* r31 */) {}

// Range: 0x801CBD80 -> 0x801CBF1C
void TourCharLocal::BuyOutfit(class TourCharLocal * const this /* r31 */, class Symbol & category /* r27 */, class Symbol & outfit /* r28 */, int amt /* r29 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std43_List_node<Q213TourCharLocal12ClosetOutfit>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std43_List_node<Q213TourCharLocal12ClosetOutfit>; // size: 0x8, address: 0x808A3928
// Range: 0x801CBF1C -> 0x801CBF88
void TourCharLocal::SetCharName(class TourCharLocal * const this /* r30 */, const char * name /* r31 */) {}

// Range: 0x801CBF88 -> 0x801CBFA0
unsigned char __eq() {}

// Range: 0x801CBFA0 -> 0x801CC0E8
void TourCharLocal::SetGroupOutfit(class TourCharLocal * const this /* r29 */, class Symbol & outfit /* r30 */) {
    // Local variables
    struct OutfitGroup * g; // r0
    struct _List_iterator v; // r1+0x24

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801CC0E8 -> 0x801CC0F0
void TourCharLocal::SetEyebrowsMatchHair() {}

// Range: 0x801CC0F0 -> 0x801CC0FC
void TourCharLocal::SetHometown() {}

// Range: 0x801CC0FC -> 0x801CC184
void TourCharLocal::AddMoney(class TourCharLocal * const this /* r30 */) {
    // Local variables
    int new_money; // r31
}

// Range: 0x801CC184 -> 0x801CC1F8
void TourCharLocal::SetDirty(class TourCharLocal * const this /* r29 */, unsigned char val /* r30 */, int flags /* r31 */) {
    // References
    // -> class ProfileMgr TheProfileMgr;
}

static int gVer; // size: 0x4, address: 0x80A4DB88
// Range: 0x801CC1F8 -> 0x801CC264
class BinStream & __ls(class BinStream & d /* r30 */, const struct OutfitPref & pref /* r31 */) {}

// Range: 0x801CC264 -> 0x801CC2C8
class BinStream & __rs(class BinStream & d /* r30 */, struct OutfitPref & pref /* r31 */) {}

// Range: 0x801CC2C8 -> 0x801CC310
class BinStream & __ls(class BinStream & d /* r30 */, const struct ClosetOutfit & co /* r31 */) {}

// Range: 0x801CC310 -> 0x801CC358
class BinStream & __rs(class BinStream & d /* r30 */, struct ClosetOutfit & co /* r31 */) {}

// Range: 0x801CC358 -> 0x801CC3AC
class BinStream & __ls(class BinStream & d /* r30 */, const struct OutfitGroup & g /* r31 */) {}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x801CC3AC -> 0x801CC400
class BinStream & __rs(class BinStream & d /* r30 */, struct OutfitGroup & g /* r31 */) {}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x801CC400 -> 0x801CC544
void TourCharLocal::Save(class TourCharLocal * const this /* r29 */, class BinStream & s /* r30 */) {
    // Local variables
    int i; // r31
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
static class Symbol outfit; // size: 0x4, address: 0x80A4DB90
class IntPacker {
    // total size: 0xC
    unsigned char * mBuffer; // offset 0x0, size 0x4
    unsigned int mPos; // offset 0x4, size 0x4
    unsigned int mSize; // offset 0x8, size 0x4
};
// Range: 0x801CC544 -> 0x801CCBF0
void TourCharLocal::SaveDb(class TourCharLocal * const this /* r25 */, class BinStream & s /* r26 */) {
    // Local variables
    char buffer[65536]; // r31+0xFFFF0008
    class IntPacker packer; // r31+0x40
    class DataArray * o; // r28
    int i; // r27
    class Symbol category; // r31+0x3C
    class Symbol selected; // r31+0x38
    unsigned int catIdx; // r24
    unsigned int selIdx; // r30
    struct OutfitPref & pref; // r0
    int i; // r23
    class DataArray * tat; // r23
    unsigned int tatIdx; // r0
    int i; // r23
    unsigned int size; // r23

    // References
    // -> static class Symbol outfit;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

static class Symbol outfit; // size: 0x4, address: 0x80A4DB98
// Range: 0x801CCBF0 -> 0x801CCFF4
void TourCharLocal::SaveRemote(class TourCharLocal * const this /* r28 */, class DataArray * dest /* r29 */) {
    // Local variables
    class MemStream m; // r1+0x88
    class String censored; // r1+0x78
    class DataArray * o; // r31
    int i; // r30
    class Symbol category; // r1+0x68
    class Symbol selected; // r1+0x64
    struct OutfitPref & pref; // r0
    int i; // r26
    class DataArray * tat; // r26
    int i; // r26

    // References
    // -> static class Symbol outfit;
}

static class Symbol gender; // size: 0x4, address: 0x80A4DBA0
static class Symbol attitude; // size: 0x4, address: 0x80A4DBA8
static class Symbol skin_color_index; // size: 0x4, address: 0x80A4DBB0
static class Symbol eye_color_index; // size: 0x4, address: 0x80A4DBB8
static class Symbol eyebrow_color_index; // size: 0x4, address: 0x80A4DBC0
static class Symbol height; // size: 0x4, address: 0x80A4DBC8
static class Symbol weight; // size: 0x4, address: 0x80A4DBD0
static class Symbol outfit; // size: 0x4, address: 0x80A4DBD8
static class Symbol colors; // size: 0x4, address: 0x80A4DBE0
// Range: 0x801CCFF4 -> 0x801CE134
void TourCharLocal::SavePrefab(class TourCharLocal * const this /* r23 */, class DataArray * dest /* r24 */) {
    // Local variables
    class DataArray * local_outfit; // r29
    class DataArray * remote_outfit; // r28
    int i; // r27
    class Symbol category; // r1+0x6C
    class Symbol selected; // r1+0x68
    struct OutfitPref & pref; // r0
    class DataArrayPtr remote; // r1+0x1A8
    class DataArray * c; // r26
    int i; // r25
    class DataArray * local_tat; // r23

    // References
    // -> static class Symbol colors;
    // -> static class Symbol outfit;
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> static class Symbol weight;
    // -> static class Symbol height;
    // -> static class Symbol eyebrow_color_index;
    // -> static class Symbol eye_color_index;
    // -> static class Symbol skin_color_index;
    // -> static class Symbol attitude;
    // -> static class Symbol gender;
}

static class Symbol kGenres[6]; // size: 0x18, address: 0x8097A090
// Range: 0x801CE134 -> 0x801CE33C
void TourCharLocal::CheatBuyAllOutfits(class TourCharLocal * const this /* r30 */) {
    // Local variables
    class list & providers; // r0
    struct _List_iterator providerIter; // r1+0x40
    class OutfitProvider * provider; // r28
    class Symbol category; // r1+0x3C
    int genreIndex; // r27
    class Symbol genre; // r1+0x38
    int outfitIndex; // r26
    class Symbol outfit; // r1+0x34

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Shop * TheShop;
    // -> static class Symbol kGenres[6];
    // -> const char * gNullStr;
}

// Range: 0x801CE33C -> 0x801CE4B8
void TourCharLocal::WriteConfig(class TourCharLocal * const this /* r31 */) {
    // Local variables
    class DataArrayPtr data; // r1+0x18
    class DataArray * a; // r31

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__12DataArrayPtr;
}

// Range: 0x801CE4B8 -> 0x801CE50C
void TourCharLocal::PrintGuid() {
    // Local variables
    const int * data; // r0

    // References
    // -> class Debug TheDebug;
}

static class Symbol _s; // size: 0x4, address: 0x80A4DBE8
static class Symbol _s; // size: 0x4, address: 0x80A4DBF0
static class Symbol _s; // size: 0x4, address: 0x80A4DBF8
static class Symbol _s; // size: 0x4, address: 0x80A4DC00
static class Symbol _s; // size: 0x4, address: 0x80A4DC08
static class Symbol _s; // size: 0x4, address: 0x80A4DC10
static class Symbol _s; // size: 0x4, address: 0x80A4DC18
static class Symbol _s; // size: 0x4, address: 0x80A4DC20
static class Symbol _s; // size: 0x4, address: 0x80A4DC28
static class Symbol _s; // size: 0x4, address: 0x80A4DC30
static class Symbol _s; // size: 0x4, address: 0x80A4DC38
static class Symbol _s; // size: 0x4, address: 0x80A4DC40
static class Symbol _s; // size: 0x4, address: 0x80A4DC48
static class Symbol _s; // size: 0x4, address: 0x80A4DC50
static class Symbol _s; // size: 0x4, address: 0x80A4DC58
static class Symbol _s; // size: 0x4, address: 0x80A4DC60
static class Symbol _s; // size: 0x4, address: 0x80A4DC68
static class Symbol _s; // size: 0x4, address: 0x80A4DC70
static class Symbol _s; // size: 0x4, address: 0x80A4DC78
static class Symbol _s; // size: 0x4, address: 0x80A4DC80
static class Symbol _s; // size: 0x4, address: 0x80A4DC88
static class Symbol _s; // size: 0x4, address: 0x80A4DC90
// Range: 0x801CE50C -> 0x801CF110
class DataNode TourCharLocal::Handle(class TourCharLocal * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x3C
    class MessageTimer _mt; // r1+0x58
    class DataNode _n; // r1+0x50
    class DataNode _n; // r1+0x48
    class DataNode _n; // r1+0x40

    // References
    // -> class DebugNotifier TheDebugNotifier;
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
}

struct {
    // total size: 0xC0
} __vt__13TourCharLocal; // size: 0xC0, address: 0x808A4148
class SessionMsg : public NetMessage {
    // total size: 0x4
};
class PlayerLeftMsg : public SessionMsg {
    // total size: 0x8
    int mPlayerID; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class MemStream * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class MemStream * _M_start; // offset 0x0, size 0x4
    class MemStream * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class JoinRequestMsg : public SessionMsg {
    // total size: 0x40
    int mGameMode; // offset 0x4, size 0x4
    class vector mPlayerIDs; // offset 0x8, size 0xC
    class vector mPlayerData; // offset 0x14, size 0xC
    class MemStream mAuthData; // offset 0x20, size 0x20
};
class JoinResponseMsg : public SessionMsg {
    // total size: 0x24
    enum JoinResponseError mError; // offset 0x4, size 0x4
    int mCustomError; // offset 0x8, size 0x4
    class vector mOldIDs; // offset 0xC, size 0xC
    class vector mNewIDs; // offset 0x18, size 0xC
};
class NewPlayerMsg : public SessionMsg {
    // total size: 0x28
    int mPlayerID; // offset 0x4, size 0x4
    class MemStream mPlayerData; // offset 0x8, size 0x20
};
class AddPlayerRequestMsg : public SessionMsg {
    // total size: 0x48
    int mPlayerID; // offset 0x4, size 0x4
    class MemStream mPlayerData; // offset 0x8, size 0x20
    class MemStream mAuthData; // offset 0x28, size 0x20
};
class AddPlayerResponseMsg : public SessionMsg {
    // total size: 0x10
    unsigned char mSuccess; // offset 0x4, size 0x1
    int mOldID; // offset 0x8, size 0x4
    int mNewID; // offset 0xC, size 0x4
};
class ChangePlayerMsg : public SessionMsg {
    // total size: 0x2C
    int mPlayerID; // offset 0x4, size 0x4
    unsigned int mDirtyMask; // offset 0x8, size 0x4
    class MemStream mPlayerData; // offset 0xC, size 0x20
};
class BeginLoadingMsg : public SessionMsg {
    // total size: 0x4
};
class FinishedLoadingMsg : public SessionMsg {
    // total size: 0x8
    unsigned int mMachineID; // offset 0x4, size 0x4
};
class StartGameOnTimeMsg : public SessionMsg {
    // total size: 0x10
    unsigned long long mStartTime; // offset 0x8, size 0x8
};
class EndGameMsg : public SessionMsg {
    // total size: 0xC
    int mResultCode; // offset 0x4, size 0x4
    unsigned char mReportStats; // offset 0x8, size 0x1
};
class VoiceDataMsg : public SessionMsg {
    // total size: 0x28
    int mPlayerID; // offset 0x4, size 0x4
    class MemStream mVoiceData; // offset 0x8, size 0x20
};

