/*
    Compile unit: C:\rockband2\band2\src\meta\BandDataProvider.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800B3E94 -> 0x800B68E8
*/
class BandDataProvider * TheBandDataProvider; // size: 0x4, address: 0x80A4A5C8
class CharRemoveProvider * TheCharRemoveProvider; // size: 0x4, address: 0x80A4A5CC
class BandQuitProvider * TheBandQuitProvider; // size: 0x4, address: 0x80A4A5D0
char lhsName[256]; // size: 0x100, address: 0x80977BF0
char rhsName[256]; // size: 0x100, address: 0x80977CF0
class BandDataProvider : public ListProvider, public Object {
    // total size: 0x3C
    class vector mBands; // offset 0x2C, size 0xC
    class Profile * mProfile; // offset 0x38, size 0x4
};
// Range: 0x800B3E94 -> 0x800B3F1C
void * BandDataProvider::BandDataProvider(class BandDataProvider * const this /* r31 */) {
    // References
    // -> class ObjectDir * sMainDir;
    // -> struct [anonymous] __vt__16BandDataProvider;
    // -> struct [anonymous] __vt__12ListProvider;
}

// Range: 0x800B3F1C -> 0x800B3FB4
void * BandDataProvider::~BandDataProvider(class BandDataProvider * const this /* r30 */) {}

// Range: 0x800B3FB4 -> 0x800B4000
void BandDataProvider::Init() {
    // References
    // -> class CharRemoveProvider * TheCharRemoveProvider;
    // -> class BandDataProvider * TheBandDataProvider;
}

// Range: 0x800B4000 -> 0x800B4004
void BandDataProvider::InitData() {}

static class Symbol name; // size: 0x4, address: 0x80A4A5D8
// Range: 0x800B4004 -> 0x800B40FC
char * BandDataProvider::Text(const class BandDataProvider * const this /* r28 */, int data /* r29 */, class Symbol & slot /* r30 */) {
    // Local variables
    class BandData * band; // r30

    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol name;
}

// Range: 0x800B40FC -> 0x800B4148
class RndMat * BandDataProvider::Mat() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800B4148 -> 0x800B414C
int BandDataProvider::NumData() {}

// Range: 0x800B414C -> 0x800B4154
unsigned char BandDataProvider::IsActive() {}

// Range: 0x800B4154 -> 0x800B43C4
void BandDataProvider::DeleteBand(class BandDataProvider * const this /* r31 */, int num /* r28 */) {
    // Local variables
    class BandData * band; // r29
    class HxGuid bandGuidCopy; // r1+0x28
    class vector roster; // r1+0x1C
    struct BandMember * rosterIter; // r29

    // References
    // -> class ProfileMgr TheProfileMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800B43C4 -> 0x800B4490
void BandDataProvider::Init(class BandDataProvider * const this /* r29 */) {
    // Local variables
    class User * pUser; // r30

    // References
    // -> class ProfileMgr TheProfileMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class UserMgr * TheUserMgr;
}

// Range: 0x800B4490 -> 0x800B455C
void BandDataProvider::GatherBands(class BandDataProvider * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct BandSorter {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
// Range: 0x800B455C -> 0x800B4574
int BandDataProvider::NumBands() {}

// Range: 0x800B4574 -> 0x800B4638
class String BandDataProvider::GetBandName(const class BandDataProvider * const this /* r30 */, int bandNum /* r31 */) {
    // Local variables
    class BandData * band; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800B4638 -> 0x800B4778
void BandDataProvider::SetBandName(class BandDataProvider * const this /* r27 */, int bandNum /* r28 */, class String & name /* r29 */) {
    // Local variables
    class BandData * band; // r30
    class TourBandLocal * pBand; // r30

    // References
    // -> struct [anonymous] __RTTI__8BandData;
    // -> struct [anonymous] __RTTI__13TourBandLocal;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800B4778 -> 0x800B4814
class BandData * BandDataProvider::GetBandData(class BandDataProvider * const this /* r30 */, int bandNum /* r31 */) {
    // Local variables
    class BandData * band; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800B4814 -> 0x800B48C8
unsigned char BandDataProvider::IsBandRemote(const class BandDataProvider * const this /* r30 */, int bandNum /* r31 */) {
    // Local variables
    class BandData * band; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A4A5E0
static class Symbol _s; // size: 0x4, address: 0x80A4A5E8
static class Symbol _s; // size: 0x4, address: 0x80A4A5F0
static class Symbol _s; // size: 0x4, address: 0x80A4A5F8
static class Symbol _s; // size: 0x4, address: 0x80A4A600
static class Symbol _s; // size: 0x4, address: 0x80A4A608
static class Symbol _s; // size: 0x4, address: 0x80A4A610
// Range: 0x800B48C8 -> 0x800B5280
class DataNode BandDataProvider::Handle(class BandDataProvider * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x3C
    class MessageTimer _mt; // r1+0x60
    class DataNode _n; // r1+0x40

    // References
    // -> class Debug TheDebug;
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

class CharRemoveProvider : public ListProvider, public Object {
    // total size: 0x40
    class BandData * mBand; // offset 0x2C, size 0x4
    class vector mChars; // offset 0x30, size 0xC
    class Profile * mProfile; // offset 0x3C, size 0x4
};
// Range: 0x800B5280 -> 0x800B530C
void * CharRemoveProvider::CharRemoveProvider(class CharRemoveProvider * const this /* r31 */) {
    // References
    // -> class ObjectDir * sMainDir;
    // -> struct [anonymous] __vt__18CharRemoveProvider;
    // -> struct [anonymous] __vt__12ListProvider;
}

// Range: 0x800B530C -> 0x800B5404
void * CharRemoveProvider::~CharRemoveProvider(class CharRemoveProvider * const this /* r30 */) {}

// Range: 0x800B5404 -> 0x800B5408
void CharRemoveProvider::InitData() {}

static class Symbol name; // size: 0x4, address: 0x80A4A618
// Range: 0x800B5408 -> 0x800B54B8
char * CharRemoveProvider::Text(const class CharRemoveProvider * const this /* r29 */, int data /* r30 */, class Symbol & slot /* r31 */) {
    // References
    // -> const char * gNullStr;
    // -> static class Symbol name;
}

// Range: 0x800B54B8 -> 0x800B5504
class RndMat * CharRemoveProvider::Mat() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800B5504 -> 0x800B551C
int CharRemoveProvider::NumData() {}

// Range: 0x800B551C -> 0x800B5524
unsigned char CharRemoveProvider::IsActive() {}

// Range: 0x800B5524 -> 0x800B5780
void CharRemoveProvider::RemoveCharacter(class CharRemoveProvider * const this /* r31 */, int num /* r28 */) {
    // Local variables
    class HxGuid remoteBandGuid; // r1+0x18

    // References
    // -> class ProfileMgr TheProfileMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800B5780 -> 0x800B5848
void CharRemoveProvider::Init(class CharRemoveProvider * const this /* r28 */, class Profile * profile /* r29 */, class BandData * band /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800B5848 -> 0x800B5860
int CharRemoveProvider::NumCharacters() {}

static class Symbol _s; // size: 0x4, address: 0x80A4A620
static class Symbol _s; // size: 0x4, address: 0x80A4A628
static class Symbol _s; // size: 0x4, address: 0x80A4A630
// Range: 0x800B5860 -> 0x800B5E3C
class DataNode CharRemoveProvider::Handle(class CharRemoveProvider * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x2C
    class MessageTimer _mt; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__7Profile;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8BandData;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

class BandQuitProvider : public ListProvider, public Object {
    // total size: 0x40
    class vector mBands; // offset 0x2C, size 0xC
    class TourCharLocal * mChar; // offset 0x38, size 0x4
    class Profile * mProfile; // offset 0x3C, size 0x4
};
// Range: 0x800B5E3C -> 0x800B5EC8
void * BandQuitProvider::BandQuitProvider(class BandQuitProvider * const this /* r31 */) {
    // References
    // -> class ObjectDir * sMainDir;
    // -> struct [anonymous] __vt__16BandQuitProvider;
    // -> struct [anonymous] __vt__12ListProvider;
}

// Range: 0x800B5EC8 -> 0x800B5F64
void * BandQuitProvider::~BandQuitProvider(class BandQuitProvider * const this /* r30 */) {}

// Range: 0x800B5F64 -> 0x800B5F98
void BandQuitProvider::Init() {
    // References
    // -> class BandQuitProvider * TheBandQuitProvider;
}

// Range: 0x800B5F98 -> 0x800B5F9C
void BandQuitProvider::InitData() {}

static class Symbol name; // size: 0x4, address: 0x80A4A638
// Range: 0x800B5F9C -> 0x800B6094
char * BandQuitProvider::Text(const class BandQuitProvider * const this /* r28 */, int data /* r29 */, class Symbol & slot /* r30 */) {
    // Local variables
    class BandData * band; // r30

    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol name;
}

// Range: 0x800B6094 -> 0x800B60E0
class RndMat * BandQuitProvider::Mat() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800B60E0 -> 0x800B60E4
int BandQuitProvider::NumData() {}

// Range: 0x800B60E4 -> 0x800B60EC
unsigned char BandQuitProvider::IsActive() {}

// Range: 0x800B60EC -> 0x800B61D8
void BandQuitProvider::Init(class BandQuitProvider * const this /* r29 */, class Profile * profile /* r31 */, class TourCharLocal * tourChar /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800B61D8 -> 0x800B62F4
void BandQuitProvider::Quit(class BandQuitProvider * const this /* r29 */, int bandNum /* r30 */) {
    // Local variables
    class BandData * band; // r31

    // References
    // -> class ProfileMgr TheProfileMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800B62F4 -> 0x800B630C
int BandQuitProvider::NumBands() {}

static class Symbol _s; // size: 0x4, address: 0x80A4A640
static class Symbol _s; // size: 0x4, address: 0x80A4A648
static class Symbol _s; // size: 0x4, address: 0x80A4A650
// Range: 0x800B630C -> 0x800B68E8
class DataNode BandQuitProvider::Handle(class BandQuitProvider * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x2C
    class MessageTimer _mt; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __RTTI__7Profile;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13TourCharLocal;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x8
} __RTTI__13TourBandLocal; // size: 0x8, address: 0x8087E5E0
struct {
    // total size: 0x9C
} __vt__16BandQuitProvider; // size: 0x9C, address: 0x8087E6B0
struct {
    // total size: 0x8
} __RTTI__16BandQuitProvider; // size: 0x8, address: 0x8087E780
struct {
    // total size: 0x9C
} __vt__18CharRemoveProvider; // size: 0x9C, address: 0x8087E788
struct {
    // total size: 0x8
} __RTTI__18CharRemoveProvider; // size: 0x8, address: 0x8087E858
struct {
    // total size: 0x9C
} __vt__16BandDataProvider; // size: 0x9C, address: 0x8087E860
struct {
    // total size: 0x8
} __RTTI__16BandDataProvider; // size: 0x8, address: 0x8087E930
struct {
    // total size: 0x8
} __RTTI__8TourBand; // size: 0x8, address: 0x8087E970
struct {
    // total size: 0x8
} __RTTI__7Profile; // size: 0x8, address: 0x8087EA18
struct _loc_coll_cmpt {
    // total size: 0x1C
    char CmptName[8]; // offset 0x0, size 0x8
    int char_start_value; // offset 0x8, size 0x4
    int char_coll_tab_size; // offset 0xC, size 0x4
    signed short char_spec_accents; // offset 0x10, size 0x2
    unsigned short * char_coll_table_ptr; // offset 0x14, size 0x4
    unsigned short * wchar_coll_seq_ptr; // offset 0x18, size 0x4
};
struct _loc_ctype_cmpt {
    // total size: 0x28
    char CmptName[8]; // offset 0x0, size 0x8
    const unsigned short * ctype_map_ptr; // offset 0x8, size 0x4
    const unsigned char * upper_map_ptr; // offset 0xC, size 0x4
    const unsigned char * lower_map_ptr; // offset 0x10, size 0x4
    const unsigned short * wctype_map_ptr; // offset 0x14, size 0x4
    const wchar_t * wupper_map_ptr; // offset 0x18, size 0x4
    const wchar_t * wlower_map_ptr; // offset 0x1C, size 0x4
    int (* decode_mb)(wchar_t *, char *, unsigned long); // offset 0x20, size 0x4
    int (* encode_wc)(char *, wchar_t); // offset 0x24, size 0x4
};
struct _loc_mon_cmpt {
    // total size: 0x34
    char CmptName[8]; // offset 0x0, size 0x8
    char * mon_decimal_point; // offset 0x8, size 0x4
    char * mon_thousands_sep; // offset 0xC, size 0x4
    char * mon_grouping; // offset 0x10, size 0x4
    char * positive_sign; // offset 0x14, size 0x4
    char * negative_sign; // offset 0x18, size 0x4
    char * currency_symbol; // offset 0x1C, size 0x4
    char frac_digits; // offset 0x20, size 0x1
    char p_cs_precedes; // offset 0x21, size 0x1
    char n_cs_precedes; // offset 0x22, size 0x1
    char p_sep_by_space; // offset 0x23, size 0x1
    char n_sep_by_space; // offset 0x24, size 0x1
    char p_sign_posn; // offset 0x25, size 0x1
    char n_sign_posn; // offset 0x26, size 0x1
    char * int_curr_symbol; // offset 0x28, size 0x4
    char int_frac_digits; // offset 0x2C, size 0x1
    char int_p_cs_precedes; // offset 0x2D, size 0x1
    char int_n_cs_precedes; // offset 0x2E, size 0x1
    char int_p_sep_by_space; // offset 0x2F, size 0x1
    char int_n_sep_by_space; // offset 0x30, size 0x1
    char int_p_sign_posn; // offset 0x31, size 0x1
    char int_n_sign_posn; // offset 0x32, size 0x1
};
struct _loc_num_cmpt {
    // total size: 0x14
    char CmptName[8]; // offset 0x0, size 0x8
    char * decimal_point; // offset 0x8, size 0x4
    char * thousands_sep; // offset 0xC, size 0x4
    char * grouping; // offset 0x10, size 0x4
};
struct _loc_time_cmpt {
    // total size: 0x28
    char CmptName[8]; // offset 0x0, size 0x8
    char * am_pm; // offset 0x8, size 0x4
    char * DateTime_Format; // offset 0xC, size 0x4
    char * Twelve_hr_format; // offset 0x10, size 0x4
    char * Date_Format; // offset 0x14, size 0x4
    char * Time_Format; // offset 0x18, size 0x4
    char * Day_Names; // offset 0x1C, size 0x4
    char * MonthNames; // offset 0x20, size 0x4
    char * TimeZone; // offset 0x24, size 0x4
};
struct __locale {
    // total size: 0x48
    struct __locale * next_locale; // offset 0x0, size 0x4
    char locale_name[48]; // offset 0x4, size 0x30
    struct _loc_coll_cmpt * coll_cmpt_ptr; // offset 0x34, size 0x4
    struct _loc_ctype_cmpt * ctype_cmpt_ptr; // offset 0x38, size 0x4
    struct _loc_mon_cmpt * mon_cmpt_ptr; // offset 0x3C, size 0x4
    struct _loc_num_cmpt * num_cmpt_ptr; // offset 0x40, size 0x4
    struct _loc_time_cmpt * time_cmpt_ptr; // offset 0x44, size 0x4
};
struct __locale _current_locale; // size: 0x48, address: 0x80930720

