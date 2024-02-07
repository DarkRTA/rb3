/*
    Compile unit: C:\rockband2\system\src\char\CharClipGroup.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8032E7D8 -> 0x80330E44
*/
class DataArray * types; // size: 0x4, address: 0x80A50BC0
// Range: 0x8032E7D8 -> 0x8032E870
void * CharClipGroup::CharClipGroup(class CharClipGroup * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__13CharClipGroup;
}

// Range: 0x8032E870 -> 0x8032E8D8
class CharClip * CharClipGroup::GetClip() {}

// Range: 0x8032E8D8 -> 0x8032E9B4
class CharClip * CharClipGroup::GetClip() {
    // Local variables
    int size; // r8
    int i; // r9
    int i; // r8
}

// Range: 0x8032E9B4 -> 0x8032EC20
void CharClipGroup::Replace(class CharClipGroup * const this /* r28 */, class Object * from /* r29 */, class Object * t /* r30 */) {
    // Local variables
    int i; // r31
    int s; // r4

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8CharClip;
}

// Range: 0x8032EC20 -> 0x8032ED00
unsigned char CharClipGroup::FlagUnique(class CharClipGroup * const this /* r27 */, class CharClip * c /* r28 */, int mask /* r29 */) {
    // Local variables
    int f; // r31
    int i; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8032ED00 -> 0x8032EDE0
int CharClipGroup::NumFlagDuplicates(class CharClipGroup * const this /* r26 */, class CharClip * c /* r27 */, int mask /* r28 */) {
    // Local variables
    int ret; // r31
    int f; // r30
    int i; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8032EDE0 -> 0x8032EE58
void CharClipGroup::DeleteRemaining() {
    // Local variables
    class CharClip * deathRow[256]; // r1+0x8
    int i; // r8
}

// Range: 0x8032EE58 -> 0x8032F0B8
void CharClipGroup::AddClip(class CharClipGroup * const this /* r30 */, class CharClip * c /* r26 */) {
    // References
    // -> struct [anonymous] __vt__33ObjOwnerPtr<8CharClip,9ObjectDir>;
}

// Range: 0x8032F0B8 -> 0x8032F1D0
void CharClipGroup::RemoveClip(class CharClipGroup * const this /* r29 */, class CharClip * c /* r30 */) {
    // Local variables
    class ObjOwnerPtr * it; // r31
}

// Range: 0x8032F1D0 -> 0x8032F208
unsigned char CharClipGroup::HasClip() {
    // Local variables
    const class ObjOwnerPtr * it; // r6
}

// Range: 0x8032F208 -> 0x8032F2E8
class CharClip * CharClipGroup::FindClip(const class CharClipGroup * const this /* r29 */, const char * name /* r30 */) {
    // Local variables
    int i; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8032F2E8 -> 0x8032F434
void CharClipGroup::Randomize(class CharClipGroup * const this /* r30 */) {
    // Local variables
    int i; // r31
    int which; // r0

    // References
    // -> struct [anonymous] __vt__33ObjOwnerPtr<8CharClip,9ObjectDir>;
}

// Range: 0x8032F434 -> 0x8032F470
void CharClipGroup::Sort(class CharClipGroup * const this /* r4 */) {}

struct Alphabetically {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
// Range: 0x8032F470 -> 0x8032F570
void CharClipGroup::SetClipFlags(class CharClipGroup * const this /* r29 */, int flags /* r30 */) {
    // Local variables
    int i; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8032F570 -> 0x8032F730
void CharClipGroup::MakeMRU(class CharClipGroup * const this /* r31 */) {
    // Local variables
    int next; // r8
    int i; // r27
    int i; // r27
}

// Range: 0x8032F730 -> 0x8032F7D0
void CharClipGroup::MakeMRU() {
    // Local variables
    int i; // r7

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8032F7D0 -> 0x8032F864
void CharClipGroup::Save(class CharClipGroup * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x8032F864 -> 0x8032F92C
class BinStream & __ls(class BinStream & d /* r30 */, const class ObjOwnerPtr & f /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static int gRev; // size: 0x4, address: 0x80A50BC8
// Range: 0x8032F92C -> 0x8032FA30
void CharClipGroup::Load(class CharClipGroup * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x8032FA30 -> 0x8032FED0
void CharClipGroup::Copy(class CharClipGroup * const this /* r28 */, const class Object * o /* r25 */, enum CopyType type /* r24 */) {
    // Local variables
    const class CharClipGroup * g; // r0
    int i; // r29

    // References
    // -> struct [anonymous] __vt__33ObjOwnerPtr<8CharClip,9ObjectDir>;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13CharClipGroup;
}

static class Symbol _s; // size: 0x4, address: 0x80A50BD0
static class Symbol _s; // size: 0x4, address: 0x80A50BD8
static class Symbol _s; // size: 0x4, address: 0x80A50BE0
static class Symbol _s; // size: 0x4, address: 0x80A50BE8
static class Symbol _s; // size: 0x4, address: 0x80A50BF0
static class Symbol _s; // size: 0x4, address: 0x80A50BF8
static class Symbol _s; // size: 0x4, address: 0x80A50C00
// Range: 0x8032FED0 -> 0x80330888
class DataNode CharClipGroup::Handle(class CharClipGroup * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x3C
    class MessageTimer _mt; // r1+0x48
    class DataNode _n; // r1+0x40

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8CharClip;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A50C08
static class Symbol _s; // size: 0x4, address: 0x80A50C10
// Range: 0x80330888 -> 0x80330A44
unsigned char CharClipGroup::SyncProperty(class CharClipGroup * const this /* r28 */, class DataNode & _val /* r29 */, class DataArray * _prop /* r30 */, int _i /* r27 */, enum PropOp _op /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x80330A44 -> 0x80330D04
unsigned char PropSync(class ObjVector & v /* r29 */, class DataNode & n /* r30 */, class DataArray * prop /* r26 */, int i /* r28 */, enum PropOp op /* r27 */) {
    // Local variables
    class ObjOwnerPtr * it; // r31
    class ObjOwnerPtr tmp; // r1+0x20

    // References
    // -> struct [anonymous] __vt__33ObjOwnerPtr<8CharClip,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80330D04 -> 0x80330E44
unsigned char PropSync(class ObjOwnerPtr & p /* r29 */, class DataNode & n /* r30 */, enum PropOp op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8CharClip;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x80
} __vt__13CharClipGroup; // size: 0x80, address: 0x808D1ED0
struct {
    // total size: 0x8
} __RTTI__P33ObjOwnerPtr<8CharClip,9ObjectDir>; // size: 0x8, address: 0x808D2018

