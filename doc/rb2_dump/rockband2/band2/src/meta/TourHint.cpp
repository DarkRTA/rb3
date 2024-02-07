/*
    Compile unit: C:\rockband2\band2\src\meta\TourHint.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x801D6CB4 -> 0x801D9A78
*/
// Range: 0x801D6CB4 -> 0x801D6CBC
class Symbol TourHint::HintName() {}

static class Symbol one_off; // size: 0x4, address: 0x80A4DE5C
// Range: 0x801D6CBC -> 0x801D6D54
unsigned char TourHint::IsOneOff(const class TourHint * const this /* r31 */) {
    // Local variables
    class DataArray * o; // r31

    // References
    // -> static class Symbol one_off;
}

// Range: 0x801D6D54 -> 0x801D6E18
int TourHint::Order(const class TourHint * const this /* r29 */) {
    // Local variables
    int i; // r30

    // References
    // -> class Debug TheDebug;
}

// Range: 0x801D6E18 -> 0x801D6E5C
unsigned char TourHint::IsEqual(const class TourHint * const this /* r31 */) {}

static class Symbol screen; // size: 0x4, address: 0x80A4DE64
// Range: 0x801D6E5C -> 0x801D6EE0
char * TourHint::Screen(const class TourHint * const this /* r31 */) {
    // References
    // -> static class Symbol screen;
}

// Range: 0x801D6EE0 -> 0x801D6EF0
void TourHint::Save(class TourHint * const this /* r5 */) {}

static class Symbol new_venue; // size: 0x4, address: 0x80A4DE6C
static class Symbol new_item; // size: 0x4, address: 0x80A4DE74
static class Symbol item_available; // size: 0x4, address: 0x80A4DE7C
static class Symbol new_staff; // size: 0x4, address: 0x80A4DE84
static class Symbol new_tier; // size: 0x4, address: 0x80A4DE8C
static class Symbol impossible; // size: 0x4, address: 0x80A4DE94
// Range: 0x801D6EF0 -> 0x801D7304
class TourHint * TourHint::Create(class BinStream & s /* r29 */, class DataArray * cfg /* r30 */) {
    // Local variables
    class Symbol hint_name; // r1+0x60
    class Symbol venue_token; // r1+0x5C
    class Symbol item; // r1+0x58
    class Symbol item; // r1+0x54
    class Symbol town; // r1+0x50
    class Symbol venue_token; // r1+0x4C
    class String event_display_name; // r1+0x70
    class vector staff; // r1+0x64
    unsigned char first; // r31
    unsigned char first_tier; // r31
    class Symbol tier_name; // r1+0x48
    class Symbol event_name; // r1+0x44

    // References
    // -> int sVer;
    // -> const char * gNullStr;
    // -> static class Symbol impossible;
    // -> static class Symbol new_tier;
    // -> static class Symbol new_staff;
    // -> static class Symbol item_available;
    // -> static class Symbol new_item;
    // -> static class Symbol new_venue;
}

// Range: 0x801D7304 -> 0x801D7338
class DataArray * TourHint::Data() {}

static class Symbol _s; // size: 0x4, address: 0x80A4DE9C
// Range: 0x801D7338 -> 0x801D76D0
class DataNode TourHint::Handle(class TourHint * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x801D76D0 -> 0x801D7710
unsigned char __eq(class Symbol & rhs /* r31 */) {}

// Range: 0x801D7710 -> 0x801D7768
unsigned char TourHintCmp::__cl(const class TourHint * lhs /* r30 */) {}

class TourHintNewItem : public TourHint {
    // total size: 0x34
    class Symbol mItem; // offset 0x30, size 0x4
};
// Range: 0x801D7768 -> 0x801D77E0
void * TourHintNewItem::TourHintNewItem(class TourHintNewItem * const this /* r29 */, class Symbol & item /* r30 */, class DataArray * cfg /* r31 */) {
    // References
    // -> struct [anonymous] __vt__15TourHintNewItem;
}

// Range: 0x801D77E0 -> 0x801D7890
unsigned char TourHintNewItem::IsEqual(const class TourHintNewItem * const this /* r30 */, const class TourHint * h /* r31 */) {
    // Local variables
    const class TourHintNewItem * hni; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__8TourHint;
    // -> struct [anonymous] __RTTI__15TourHintNewItem;
}

// Range: 0x801D7890 -> 0x801D78C4
char * TourHintNewItem::Screen() {}

// Range: 0x801D78C4 -> 0x801D7908
void TourHintNewItem::Save(class TourHintNewItem * const this /* r30 */, class BinStream & s /* r31 */) {}

static class Symbol _s; // size: 0x4, address: 0x80A4DEA4
// Range: 0x801D7908 -> 0x801D7C94
class DataNode TourHintNewItem::Handle(class TourHintNewItem * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

class TourHintItemAvailable : public TourHint {
    // total size: 0x48
    class Symbol mItem; // offset 0x30, size 0x4
    class Symbol mTown; // offset 0x34, size 0x4
    class Symbol mVenueToken; // offset 0x38, size 0x4
    class String mEventDisplayName; // offset 0x3C, size 0xC
};
// Range: 0x801D7C94 -> 0x801D7D2C
void * TourHintItemAvailable::TourHintItemAvailable(class TourHintItemAvailable * const this /* r26 */, class Symbol & item /* r27 */, class Symbol & town /* r28 */, class Symbol & venue_token /* r29 */, const char * event_display_name /* r30 */, class DataArray * cfg /* r31 */) {
    // References
    // -> struct [anonymous] __vt__21TourHintItemAvailable;
}

// Range: 0x801D7D2C -> 0x801D7DDC
unsigned char TourHintItemAvailable::IsEqual(const class TourHintItemAvailable * const this /* r30 */, const class TourHint * h /* r31 */) {
    // Local variables
    const class TourHintItemAvailable * hni; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__8TourHint;
    // -> struct [anonymous] __RTTI__21TourHintItemAvailable;
}

// Range: 0x801D7DDC -> 0x801D7E38
void TourHintItemAvailable::Save(class TourHintItemAvailable * const this /* r30 */, class BinStream & s /* r31 */) {}

static class Symbol _s; // size: 0x4, address: 0x80A4DEAC
static class Symbol _s; // size: 0x4, address: 0x80A4DEB4
static class Symbol _s; // size: 0x4, address: 0x80A4DEBC
static class Symbol _s; // size: 0x4, address: 0x80A4DEC4
// Range: 0x801D7E38 -> 0x801D845C
class DataNode TourHintItemAvailable::Handle(class TourHintItemAvailable * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x3C
    class MessageTimer _mt; // r1+0x48
    class DataNode _n; // r1+0x40

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

class TourHintNewVenue : public TourHint {
    // total size: 0x34
    class Symbol mVenueToken; // offset 0x30, size 0x4
};
// Range: 0x801D845C -> 0x801D84D4
void * TourHintNewVenue::TourHintNewVenue(class TourHintNewVenue * const this /* r29 */, class Symbol & venue_token /* r30 */, class DataArray * cfg /* r31 */) {
    // References
    // -> struct [anonymous] __vt__16TourHintNewVenue;
}

// Range: 0x801D84D4 -> 0x801D8518
void TourHintNewVenue::Save(class TourHintNewVenue * const this /* r30 */, class BinStream & s /* r31 */) {}

static class Symbol _s; // size: 0x4, address: 0x80A4DECC
// Range: 0x801D8518 -> 0x801D88A4
class DataNode TourHintNewVenue::Handle(class TourHintNewVenue * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

class TourHintNewStaff : public TourHint {
    // total size: 0x40
    unsigned char mFirst; // offset 0x30, size 0x1
    class vector mStaff; // offset 0x34, size 0xC
};
// Range: 0x801D88A4 -> 0x801D89C4
void * TourHintNewStaff::TourHintNewStaff(class TourHintNewStaff * const this /* r31 */, unsigned char first /* r28 */, const class vector & staff /* r29 */, class DataArray * cfg /* r30 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__P6Symbol;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __vt__16TourHintNewStaff;
}

// Range: 0x801D89C4 -> 0x801D89CC
unsigned char TourHintNewStaff::IsFirst() {}

// Range: 0x801D89CC -> 0x801D89E4
int TourHintNewStaff::NumStaff() {}

// Range: 0x801D89E4 -> 0x801D8A40
void TourHintNewStaff::Save(class TourHintNewStaff * const this /* r30 */, class BinStream & s /* r31 */) {}

static class Symbol _s; // size: 0x4, address: 0x80A4DED4
static class Symbol _s; // size: 0x4, address: 0x80A4DEDC
static class Symbol _s; // size: 0x4, address: 0x80A4DEE4
// Range: 0x801D8A40 -> 0x801D8F88
class DataNode TourHintNewStaff::Handle(class TourHintNewStaff * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x30
    class MessageTimer _mt; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

class TourHintNewTier : public TourHint {
    // total size: 0x38
    unsigned char mFirstTier; // offset 0x30, size 0x1
    class Symbol mTierName; // offset 0x34, size 0x4
};
// Range: 0x801D8F88 -> 0x801D9010
void * TourHintNewTier::TourHintNewTier(class TourHintNewTier * const this /* r28 */, unsigned char first /* r29 */, class Symbol & tier_name /* r30 */, class DataArray * cfg /* r31 */) {
    // References
    // -> struct [anonymous] __vt__15TourHintNewTier;
}

// Range: 0x801D9010 -> 0x801D90C0
unsigned char TourHintNewTier::IsEqual(const class TourHintNewTier * const this /* r30 */, const class TourHint * h /* r31 */) {
    // Local variables
    const class TourHintNewTier * t; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__8TourHint;
    // -> struct [anonymous] __RTTI__15TourHintNewTier;
}

// Range: 0x801D90C0 -> 0x801D911C
void TourHintNewTier::Save(class TourHintNewTier * const this /* r30 */, class BinStream & s /* r31 */) {}

static class Symbol _s; // size: 0x4, address: 0x80A4DEEC
static class Symbol _s; // size: 0x4, address: 0x80A4DEF4
// Range: 0x801D911C -> 0x801D9580
class DataNode TourHintNewTier::Handle(class TourHintNewTier * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x2C
    class MessageTimer _mt; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

class TourHintImpossible : public TourHint {
    // total size: 0x34
    class Symbol mEventName; // offset 0x30, size 0x4
};
// Range: 0x801D9580 -> 0x801D95F8
void * TourHintImpossible::TourHintImpossible(class TourHintImpossible * const this /* r29 */, class Symbol & event_name /* r30 */, class DataArray * cfg /* r31 */) {
    // References
    // -> struct [anonymous] __vt__18TourHintImpossible;
}

// Range: 0x801D95F8 -> 0x801D96A8
unsigned char TourHintImpossible::IsEqual(const class TourHintImpossible * const this /* r30 */, const class TourHint * h /* r31 */) {
    // Local variables
    const class TourHintImpossible * i; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__8TourHint;
    // -> struct [anonymous] __RTTI__18TourHintImpossible;
}

// Range: 0x801D96A8 -> 0x801D96EC
void TourHintImpossible::Save(class TourHintImpossible * const this /* r30 */, class BinStream & s /* r31 */) {}

static class Symbol _s; // size: 0x4, address: 0x80A4DEFC
// Range: 0x801D96EC -> 0x801D9A78
class DataNode TourHintImpossible::Handle(class TourHintImpossible * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x5C
} __vt__18TourHintImpossible; // size: 0x5C, address: 0x808A4EC0
struct {
    // total size: 0x8
} __RTTI__18TourHintImpossible; // size: 0x8, address: 0x808A4F50
struct {
    // total size: 0x5C
} __vt__15TourHintNewTier; // size: 0x5C, address: 0x808A4F58
struct {
    // total size: 0x8
} __RTTI__15TourHintNewTier; // size: 0x8, address: 0x808A4FE8
struct {
    // total size: 0x5C
} __vt__16TourHintNewStaff; // size: 0x5C, address: 0x808A4FF0
struct {
    // total size: 0x8
} __RTTI__16TourHintNewStaff; // size: 0x8, address: 0x808A5080
struct {
    // total size: 0x5C
} __vt__16TourHintNewVenue; // size: 0x5C, address: 0x808A5088
struct {
    // total size: 0x8
} __RTTI__16TourHintNewVenue; // size: 0x8, address: 0x808A5118
struct {
    // total size: 0x5C
} __vt__21TourHintItemAvailable; // size: 0x5C, address: 0x808A5120
struct {
    // total size: 0x8
} __RTTI__21TourHintItemAvailable; // size: 0x8, address: 0x808A51B0
struct {
    // total size: 0x5C
} __vt__15TourHintNewItem; // size: 0x5C, address: 0x808A51B8
struct {
    // total size: 0x8
} __RTTI__15TourHintNewItem; // size: 0x8, address: 0x808A5248
struct {
    // total size: 0x5C
} __vt__8TourHint; // size: 0x5C, address: 0x808A5250
struct {
    // total size: 0x8
} __RTTI__8TourHint; // size: 0x8, address: 0x808A52D0

