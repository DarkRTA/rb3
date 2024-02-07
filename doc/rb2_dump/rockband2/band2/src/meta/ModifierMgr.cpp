/*
    Compile unit: C:\rockband2\band2\src\meta\ModifierMgr.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8011D7C4 -> 0x8011FC68
*/
class ModifierMgr * TheModifierMgr; // size: 0x4, address: 0x80A4BA88
static class Symbol modifiers; // size: 0x4, address: 0x80A4BA90
static class Symbol features; // size: 0x4, address: 0x80A4BA98
// Range: 0x8011D7C4 -> 0x8011DC00
void * ModifierMgr::ModifierMgr(class ModifierMgr * const this /* r30 */) {
    // Local variables
    class DataArray * root; // r29
    class DataArray * featuresArray; // r28
    int i; // r27
    class Symbol feature; // r1+0x3C
    class DataArray * allModifiersArray; // r27
    int i; // r28
    class Modifier * pModifier; // r1+0x38
    const class DataArray * features; // r29
    int featureIndex; // r26
    class Symbol feature; // r1+0x34

    // References
    // -> class ObjectDir * sMainDir;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class ModifierMgr * TheModifierMgr;
    // -> static class Symbol features;
    // -> static class Symbol modifiers;
    // -> struct [anonymous] __vt__11ModifierMgr;
}

struct pair {
    // total size: 0x8
    class Symbol first; // offset 0x0, size 0x4
    int second; // offset 0x4, size 0x4
};
// Range: 0x8011DC00 -> 0x8011DDBC
void * ModifierMgr::~ModifierMgr(class ModifierMgr * const this /* r30 */) {
    // Local variables
    class Modifier * * iter; // r29
    class Modifier * pModifier; // r28

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__11ModifierMgr;
}

// Range: 0x8011DDBC -> 0x8011DE44
class Symbol ModifierMgr::DataSymbol(const class ModifierMgr * const this /* r31 */) {
    // Local variables
    class Modifier * pModifier; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

// Range: 0x8011DE44 -> 0x8011DE60
int ModifierMgr::NumData() {}

static class Symbol entermodifier; // size: 0x4, address: 0x80A4BAA0
static class Symbol name; // size: 0x4, address: 0x80A4BAA8
static class Symbol description; // size: 0x4, address: 0x80A4BAB0
static class Symbol active; // size: 0x4, address: 0x80A4BAB8
static class Symbol locked; // size: 0x4, address: 0x80A4BAC0
static class Symbol modifier_locked_name; // size: 0x4, address: 0x80A4BAC8
static class Symbol modifier_enter_entry_name; // size: 0x4, address: 0x80A4BAD0
// Range: 0x8011DE60 -> 0x8011E150
char * ModifierMgr::Text(const class ModifierMgr * const this /* r28 */, int data /* r29 */, class Symbol & slot /* r30 */) {
    // Local variables
    class Modifier * pModifier; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol modifier_enter_entry_name;
    // -> static class Symbol modifier_locked_name;
    // -> static class Symbol locked;
    // -> static class Symbol active;
    // -> static class Symbol description;
    // -> static class Symbol name;
    // -> static class Symbol entermodifier;
}

static class Symbol check_bg; // size: 0x4, address: 0x80A4BAD8
// Range: 0x8011E150 -> 0x8011E238
class RndMat * ModifierMgr::Mat(const class ModifierMgr * const this /* r28 */, int data /* r29 */, class Symbol & slot /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol check_bg;
}

// Range: 0x8011E238 -> 0x8011E2EC
unsigned char ModifierMgr::IsHidden(const class ModifierMgr * const this /* r30 */) {
    // Local variables
    class Modifier * pModifier; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8011E2EC -> 0x8011E41C
void ModifierMgr::InitData(class ModifierMgr * const this /* r27 */, class RndDir * dir /* r28 */) {
    // References
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndMat;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8011E41C -> 0x8011E4B4
void ModifierMgr::UnlockModifier(class Symbol & modifier /* r30 */) {
    // Local variables
    class BandUser * pUser; // r0
    class Profile * data; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class ProfileMgr TheProfileMgr;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x8011E4B4 -> 0x8011E63C
unsigned char ModifierMgr::IsModifierUnlocked(const class ModifierMgr * const this /* r28 */, class Symbol & modifier /* r29 */) {
    // Local variables
    class vector profiles; // r1+0x1C
    class Profile * const * iter; // r31
    class Profile * data; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class ProfileMgr TheProfileMgr;
    // -> unsigned char sUnlockAll;
}

// Range: 0x8011E63C -> 0x8011E66C
unsigned char ModifierMgr::IsModifierAlwaysUnlocked() {
    // Local variables
    const class Modifier * pModifier; // r0
}

// Range: 0x8011E66C -> 0x8011E748
void ModifierMgr::ActivateModifier(class ModifierMgr * const this /* r30 */, class Symbol & modifier /* r31 */) {
    // Local variables
    const class Modifier * pModifier; // r31
    const class DataArray * disabledFeatures; // r4

    // References
    // -> class Debug TheDebug;
}

// Range: 0x8011E748 -> 0x8011E86C
void ModifierMgr::DeactivateModifier(class ModifierMgr * const this /* r30 */, class Symbol & modifier /* r31 */) {
    // Local variables
    const class Modifier * pModifier; // r31
    const class DataArray * disabledFeatures; // r4
}

// Range: 0x8011E86C -> 0x8011E8E4
void ModifierMgr::ToggleModifierActive(class ModifierMgr * const this /* r30 */, class Symbol & modifier /* r31 */) {}

// Range: 0x8011E8E4 -> 0x8011E968
unsigned char ModifierMgr::IsModifierActive() {}

struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
    // total size: 0x4
};
// Range: 0x8011E968 -> 0x8011EA64
unsigned char ModifierMgr::IsFeatureEnabled(const class ModifierMgr * const this /* r30 */, class Symbol & feature /* r31 */) {
    // Local variables
    struct _Rb_tree_iterator iter; // r1+0x20

    // References
    // -> class Debug TheDebug;
}

// Range: 0x8011EA64 -> 0x8011EAA0
unsigned char ModifierMgr::DoesDisableFeatures() {
    // Local variables
    const class Modifier * pModifier; // r0
}

// Range: 0x8011EAA0 -> 0x8011EAD0
class DataArray * ModifierMgr::GetDisabledFeatures() {
    // Local variables
    const class Modifier * pModifier; // r0
}

struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
    // total size: 0x4
};
struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
    // total size: 0x4
};
// Range: 0x8011EAD0 -> 0x8011EB7C
class Modifier * ModifierMgr::GetModifier(const class ModifierMgr * const this /* r28 */, class Symbol & modifier /* r29 */) {
    // Local variables
    class Modifier * const * iter; // r31
    const class Modifier * pModifier; // r30

    // References
    // -> class Debug TheDebug;
}

// Range: 0x8011EB7C -> 0x8011EC30
int ModifierMgr::UIListIndexToModifierIndex(const class ModifierMgr * const this /* r29 */, int uiindex /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8011EC30 -> 0x8011ECB4
unsigned char ModifierMgr::KnownFeature() {}

struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
    // total size: 0x4
};
// Range: 0x8011ECB4 -> 0x8011EE24
void ModifierMgr::AddDisabledFeatures(class ModifierMgr * const this /* r29 */, const class DataArray * pFeatures /* r30 */) {
    // Local variables
    int i; // r31
    class Symbol feature; // r1+0x24
    struct _Rb_tree_iterator entry; // r1+0x20

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8011EE24 -> 0x8011EFAC
void ModifierMgr::RemoveDisabledFeatures(class ModifierMgr * const this /* r29 */, const class DataArray * pFeatures /* r30 */) {
    // Local variables
    int i; // r31
    class Symbol feature; // r1+0x24
    struct _Rb_tree_iterator entry; // r1+0x20

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol modifier_online_feature; // size: 0x4, address: 0x80A4BAE0
static class Symbol modifier_saving_feature; // size: 0x4, address: 0x80A4BAE8
// Range: 0x8011EFAC -> 0x8011F054
void ModifierMgr::OnFeatureDisabled(class Symbol & feature /* r31 */) {
    // References
    // -> class ProfileMgr TheProfileMgr;
    // -> class RockCentralGateway RockCentral;
    // -> static class Symbol modifier_saving_feature;
    // -> static class Symbol modifier_online_feature;
}

static class Symbol modifier_saving_feature; // size: 0x4, address: 0x80A4BAF0
// Range: 0x8011F054 -> 0x8011F0BC
void ModifierMgr::OnFeatureEnabled(class Symbol & feature /* r31 */) {
    // References
    // -> class ProfileMgr TheProfileMgr;
    // -> static class Symbol modifier_saving_feature;
}

static class Symbol _s; // size: 0x4, address: 0x80A4BAF8
static class Symbol _s; // size: 0x4, address: 0x80A4BB00
static class Symbol _s; // size: 0x4, address: 0x80A4BB08
static class Symbol _s; // size: 0x4, address: 0x80A4BB10
static class Symbol _s; // size: 0x4, address: 0x80A4BB18
static class Symbol _s; // size: 0x4, address: 0x80A4BB20
static class Symbol _s; // size: 0x4, address: 0x80A4BB28
static class Symbol _s; // size: 0x4, address: 0x80A4BB30
static class Symbol _s; // size: 0x4, address: 0x80A4BB38
// Range: 0x8011F0BC -> 0x8011FC68
class DataNode ModifierMgr::Handle(class ModifierMgr * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x8C
    class MessageTimer _mt; // r1+0x98
    class DataNode _n; // r1+0x90

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
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0xB0
} __vt__11ModifierMgr; // size: 0xB0, address: 0x8088DE58
struct {
    // total size: 0x8
} __RTTI__11ModifierMgr; // size: 0x8, address: 0x8088DF30
struct pair {
    // total size: 0x8
    struct _Rb_tree_iterator first; // offset 0x0, size 0x4
    unsigned char second; // offset 0x4, size 0x1
};
struct pair {
    // total size: 0x8
    struct _Rb_tree_iterator first; // offset 0x0, size 0x4
    unsigned char second; // offset 0x4, size 0x1
};
struct {
    // total size: 0x8
} __RTTI__PP8Modifier; // size: 0x8, address: 0x8088DF98
struct _OKToMemCpy {
    // total size: 0x1
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std22_Rb_tree_node<6Symbol>; // size: 0x8, address: 0x8088DFE0
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std48_Rb_tree_node<Q211stlpmtx_std16pair<C6Symbol,i>>; // size: 0x8, address: 0x8088E030

