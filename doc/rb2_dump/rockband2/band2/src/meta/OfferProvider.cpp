/*
    Compile unit: C:\rockband2\band2\src\meta\OfferProvider.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8012C50C -> 0x8012D5F8
*/
// Range: 0x8012C50C -> 0x8012C63C
void * OfferProvider::OfferProvider(class OfferProvider * const this /* r27 */, class DataArray * sorts /* r28 */) {
    // Local variables
    int i; // r29

    // References
    // -> struct [anonymous] __vt__9StoreSort;
    // -> struct [anonymous] __vt__13OfferProvider;
}

// Range: 0x8012C63C -> 0x8012C7B0
void * OfferProvider::~OfferProvider(class OfferProvider * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__13OfferProvider;
}

// Range: 0x8012C80C -> 0x8012C85C
class Symbol OfferProvider::CurrentSort() {}

// Range: 0x8012C85C -> 0x8012C898
void OfferProvider::OnNextSort() {}

// Range: 0x8012C898 -> 0x8012C954
void OfferProvider::SetSort(class OfferProvider * const this /* r28 */, class Symbol & sort /* r29 */) {
    // Local variables
    int i; // r30
}

static class Symbol shortcut_groups; // size: 0x4, address: 0x80A4BCD4
// Range: 0x8012C954 -> 0x8012CC98
void OfferProvider::GetShortcuts(const class OfferProvider * const this /* r29 */, class vector & all /* r30 */, class vector & active /* r31 */) {
    // Local variables
    class vector represented; // r1+0x5C
    class DataArray * g; // r28
    int i; // r27
    int i; // r27

    // References
    // -> static class Symbol shortcut_groups;
}

// Range: 0x8012CC98 -> 0x8012CDF0
void OfferProvider::GetSorts(const class OfferProvider * const this /* r30 */, class vector & all /* r31 */) {
    // Local variables
    int i; // r28
}

static class Symbol _s; // size: 0x4, address: 0x80A4BCDC
static class Symbol _s; // size: 0x4, address: 0x80A4BCE4
static class Symbol _s; // size: 0x4, address: 0x80A4BCEC
// Range: 0x8012CDF0 -> 0x8012D358
class DataNode OfferProvider::Handle(class OfferProvider * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x38
    class MessageTimer _mt; // r1+0x48
    class DataNode _n; // r1+0x40

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A4BCF4
// Range: 0x8012D358 -> 0x8012D5F8
class DataNode GroupProvider::Handle(class GroupProvider * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
    // Local variables
    class Symbol _type; // r1+0x20
    class MessageTimer _mt; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x9C
} __vt__13GroupProvider; // size: 0x9C, address: 0x8088FE8C
struct {
    // total size: 0x8
} __RTTI__13GroupProvider; // size: 0x8, address: 0x8088FF58
struct {
    // total size: 0xA8
} __vt__13OfferProvider; // size: 0xA8, address: 0x8088FF60
struct {
    // total size: 0x8
} __RTTI__13OfferProvider; // size: 0x8, address: 0x80890038
struct {
    // total size: 0x8
} __RTTI__PP9StoreSort; // size: 0x8, address: 0x80890098

