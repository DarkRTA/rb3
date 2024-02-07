/*
    Compile unit: C:\rockband2\system\src\rndobj\Font.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8049BE9C -> 0x8049E314
*/
class DataArray * types; // size: 0x4, address: 0x80A52EF0
class Symbol name; // size: 0x4, address: 0x80A52EF8
static int FONT_REV; // size: 0x4, address: 0x80A471E8
static int gRev; // size: 0x4, address: 0x80A52EFC
// Range: 0x8049BE9C -> 0x8049BF28
static class BinStream & __rs(class BinStream & d /* r30 */, class KernInfo & v /* r31 */) {
    // Local variables
    char tmp; // r1+0x8

    // References
    // -> static int gRev;
}

// Range: 0x8049BF28 -> 0x8049BFD8
static int NonTransparentColumn(class RndBitmap & c /* r25 */, int x0 /* r26 */, int x1 /* r27 */, int y0 /* r28 */, int y1 /* r29 */) {
    // Local variables
    int x; // r31
    int y; // r30
    unsigned char r; // r1+0xB
    unsigned char g; // r1+0xA
    unsigned char b; // r1+0x9
    unsigned char a; // r1+0x8
}

class Entry {
    // total size: 0xC
public:
    class Entry * next; // offset 0x0, size 0x4
    int key; // offset 0x4, size 0x4
    float kerning; // offset 0x8, size 0x4
};
class KerningTable {
    // total size: 0x88
protected:
    int mNumEntries; // offset 0x0, size 0x4
    class Entry * mEntries; // offset 0x4, size 0x4
    class Entry * mTable[32]; // offset 0x8, size 0x80
};
// Range: 0x8049BFD8 -> 0x8049C0B8
void RndFont::GetTexCoords(const class RndFont * const this /* r28 */, char c /* r29 */, class Vector2 & topLeft /* r30 */, class Vector2 & bottomRight /* r31 */) {
    // Local variables
    const class CharInfo & info; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8049C0B8 -> 0x8049C0C0
void RndFont::SetBaseKerning() {}

// Range: 0x8049C0C0 -> 0x8049C2E0
void RndFont::SetCharInfo(class RndFont * const this /* r23 */, class CharInfo * info /* r29 */, class RndBitmap & a /* r30 */, const class Vector2 & pos /* r31 */) {
    // Local variables
    int x0; // r27
    int x1; // r26
    int y0; // r25
    int y1; // r24
    float left; // f31
    float width; // f1

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8049C2E0 -> 0x8049C410
float RndFont::Kerning(const class RndFont * const this /* r29 */, char a /* r30 */, char b /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8049C410 -> 0x8049C4D0
float RndFont::CharAdvance(const class RndFont * const this /* r29 */, char a /* r30 */, char b /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8049C4D0 -> 0x8049C578
unsigned char RndFont::CharDefined(const class RndFont * const this /* r30 */, char a /* r31 */) {
    // Local variables
    const class CharInfo & i; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8049C578 -> 0x8049C594
class RndTex * RndFont::ValidTexture() {}

// Range: 0x8049C594 -> 0x8049C62C
void RndFont::SetBitmapSize() {}

class BitmapLocker {
    // total size: 0x2C
protected:
    class RndTex * mTexture; // offset 0x0, size 0x4
    class RndBitmap * mPbm; // offset 0x4, size 0x4
    class RndBitmap mBm; // offset 0x8, size 0x24
};
// Range: 0x8049C62C -> 0x8049C9A0
void RndFont::UpdateChars(class RndFont * const this /* r30 */) {
    // Local variables
    class RndTex * tex; // r0
    class BitmapLocker locker; // r1+0x10
    class RndBitmap * b; // r31
    class Vector2 pos; // r1+0x8
    char * c; // r29

    // References
    // -> class Debug TheDebug;
}

// Range: 0x8049C9A0 -> 0x8049CB94
void RndFont::GetKerning(class vector & info /* r30 */) {}

// Range: 0x8049CB94 -> 0x8049CDCC
void RndFont::SetKerning(class RndFont * const this /* r27 */, const class vector & info /* r28 */) {}

// Range: 0x8049CDCC -> 0x8049CE10
void RndFont::Save() {
    // References
    // -> class Debug TheDebug;
}

class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x8049CE10 -> 0x8049D7EC
void RndFont::Load(class RndFont * const this /* r26 */, class BinStream & d /* r27 */) {
    // Local variables
    char shader[128]; // r1+0x98
    float rows; // r1+0x54
    float cols; // r1+0x50
    int irows; // r1+0x4C
    int icols; // r1+0x48
    class RndTex * t; // r24
    class RndBitmap a; // r1+0x70
    int width; // r1+0x44
    int height; // r1+0x40
    class RndTex * tex; // r0
    int i; // r24
    class CharInfo & info; // r25
    class vector info; // r1+0x64

    // References
    // -> class Debug TheDebug;
    // -> static int FONT_REV;
    // -> static int gRev;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class KernInfo * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class KernInfo * _M_start; // offset 0x0, size 0x4
    class KernInfo * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
// Range: 0x8049D7EC -> 0x8049DAB8
void RndFont::Copy(class RndFont * const this /* r28 */, const class Object * o /* r30 */, enum CopyType type /* r29 */) {
    // Local variables
    const class RndFont * f; // r0
    class vector info; // r1+0x1C

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndFont;
}

// Range: 0x8049DAB8 -> 0x8049DBC8
void RndFont::Print(class RndFont * const this /* r27 */) {
    // Local variables
    class TextStream & d; // r28

    // References
    // -> class Debug TheDebug;
}

// Range: 0x8049DBC8 -> 0x8049DC90
void * RndFont::RndFont(class RndFont * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__32ObjOwnerPtr<7RndFont,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
    // -> struct [anonymous] __vt__7RndFont;
}

// Range: 0x8049DC90 -> 0x8049DD68
void RndFont::Replace(class RndFont * const this /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndFont;
}

// Range: 0x8049DD68 -> 0x8049DE5C
void * RndFont::~RndFont(class RndFont * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjOwnerPtr<7RndFont,9ObjectDir>;
    // -> struct [anonymous] __vt__7RndFont;
}

static class Symbol _s; // size: 0x4, address: 0x80A52F04
static class Symbol _s; // size: 0x4, address: 0x80A52F0C
// Range: 0x8049DE5C -> 0x8049E2C0
class DataNode RndFont::Handle(class RndFont * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x28
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

// Range: 0x8049E2C0 -> 0x8049E314
unsigned char RndFont::SyncProperty(class DataArray * _prop /* r31 */) {}

struct {
    // total size: 0x54
} __vt__7RndFont; // size: 0x54, address: 0x808F7620
struct {
    // total size: 0x18
} __vt__32ObjOwnerPtr<7RndFont,9ObjectDir>; // size: 0x18, address: 0x808F76A0
struct {
    // total size: 0x8
} __RTTI__32ObjOwnerPtr<7RndFont,9ObjectDir>; // size: 0x8, address: 0x808F76E8
class KernInfo {
    // total size: 0x8
public:
    char a; // offset 0x0, size 0x1
    char b; // offset 0x1, size 0x1
    float kerning; // offset 0x4, size 0x4
};
struct {
    // total size: 0x8
} __RTTI__PQ27RndFont8KernInfo; // size: 0x8, address: 0x808F77C0

