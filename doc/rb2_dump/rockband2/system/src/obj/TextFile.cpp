/*
    Compile unit: C:\rockband2\system\src\obj\TextFile.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805FAF90 -> 0x805FB9DC
*/
class DataArray * types; // size: 0x4, address: 0x80A55330
// Range: 0x805FAF90 -> 0x805FAFE8
void TextFile::SetName(class TextFile * const this /* r31 */) {}

// Range: 0x805FAFE8 -> 0x805FB0E0
void TextFile::Print(class TextFile * const this /* r30 */, const char * str /* r31 */) {
    // Local variables
    char kCRLF[2]; // r1+0x8
    const char * ptr; // [invalid]

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A55338
static class Symbol _s; // size: 0x4, address: 0x80A55340
static class Symbol _s; // size: 0x4, address: 0x80A55348
// Range: 0x805FB0E0 -> 0x805FB788
class DataNode TextFile::Handle(class TextFile * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x2C
    class MessageTimer _mt; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode r; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x805FB788 -> 0x805FB81C
class DataNode TextFile::OnPrint(class TextFile * const this /* r29 */, class DataArray * array /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x805FB81C -> 0x805FB8F0
class DataNode TextFile::OnPrintf(class TextFile * const this /* r29 */, class DataArray * array /* r30 */) {
    // Local variables
    class FormatString f; // r1+0x8
    int i; // r31
}

// Range: 0x805FB8F0 -> 0x805FB9DC
class DataNode TextFile::OnReflect(class DataArray * a /* r29 */) {
    // Local variables
    int i; // r30

    // References
    // -> class Debug TheDebug;
}

struct {
    // total size: 0x68
} __vt__8TextFile; // size: 0x68, address: 0x8092A808
struct {
    // total size: 0x8
} __RTTI__8TextFile; // size: 0x8, address: 0x8092A898

