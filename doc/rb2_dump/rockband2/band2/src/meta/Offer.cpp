/*
    Compile unit: C:\rockband2\band2\src\meta\Offer.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8012BA90 -> 0x8012C3F4
*/
class Symbol song; // size: 0x4, address: 0x80A4BCAC
// Range: 0x8012BA90 -> 0x8012BADC
void * Offer::Offer(class Offer * const this /* r30 */, const class DataArray * data /* r31 */) {
    // References
    // -> struct [anonymous] __vt__5Offer;
}

// Range: 0x8012BADC -> 0x8012BB6C
class DataNode & Offer::GetData(class DataArray * fields /* r29 */) {
    // Local variables
    const class DataArray * a; // r31
    int i; // r30
}

// Range: 0x8012BB6C -> 0x8012BBAC
unsigned char Offer::HasData() {}

// Range: 0x8012BBAC -> 0x8012BCAC
class DataNode Offer::ExecuteScript(class DataArray * script /* r31 */) {
    // Local variables
    class DataArrayPtr offer; // r1+0x10

    // References
    // -> struct [anonymous] __vt__12DataArrayPtr;
}

static class Symbol store_nonalpha_group; // size: 0x4, address: 0x80A4BCB4
// Range: 0x8012BCAC -> 0x8012BDE0
class Symbol Offer::FirstChar(unsigned char skip_the /* r30 */) {
    // Local variables
    char buf[256]; // r1+0x20
    class String strResult; // r1+0x14

    // References
    // -> static class Symbol store_nonalpha_group;
    // -> struct __locale _current_locale;
}

static class Symbol _s; // size: 0x4, address: 0x80A4BCBC
static class Symbol _s; // size: 0x4, address: 0x80A4BCC4
static class Symbol _s; // size: 0x4, address: 0x80A4BCCC
// Range: 0x8012BDE0 -> 0x8012C3A8
class DataNode Offer::Handle(class Offer * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x40
    class MessageTimer _mt; // r1+0x50
    class DataNode _n; // r1+0x48

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x8012C3A8 -> 0x8012C3F4
unsigned char __eq(class Symbol & rhs /* r31 */) {}

struct {
    // total size: 0x68
} __vt__5Offer; // size: 0x68, address: 0x8088FCF8
struct {
    // total size: 0x8
} __RTTI__5Offer; // size: 0x8, address: 0x8088FD80

