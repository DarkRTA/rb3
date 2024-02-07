/*
    Compile unit: C:\rockband2\system\src\rndobj\Text.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80504BC8 -> 0x8050A798
*/
class DataArray * types; // size: 0x4, address: 0x80A53A20
static float gSuperscriptScale; // size: 0x4, address: 0x80A47428
class WrapPoint {
    // total size: 0x60
public:
    int mOffset; // offset 0x0, size 0x4
    int mCost; // offset 0x4, size 0x4
    int mBackLink; // offset 0x8, size 0x4
    int mFwdLink; // offset 0xC, size 0x4
    float mLineWidth; // offset 0x10, size 0x4
    class Style mStyle; // offset 0x20, size 0x30
    unsigned char mBreakOnHyphen; // offset 0x50, size 0x1
    unsigned char mIsHead; // offset 0x51, size 0x1
    unsigned char mIsHardBreak; // offset 0x52, size 0x1
};
static class WrapPoint * gWrapPoints; // size: 0x4, address: 0x80A53A28
// Range: 0x80504BC8 -> 0x80504C80
void RndText::Init() {
    // References
    // -> static class WrapPoint * gWrapPoints;
    // -> static float gSuperscriptScale;
    // -> class Symbol name;
}

// Range: 0x80504C80 -> 0x80504C88
void RndText::Terminate() {
    // References
    // -> static class WrapPoint * gWrapPoints;
}

// Range: 0x80504C88 -> 0x80504D90
void RndText::Mats(class RndText * const this /* r31 */, class list & mats /* r30 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std20_List_node<P6RndMat>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80504D90 -> 0x80504DE0
class RndDrawable * RndText::CollideShowing(class RndText * const this /* r31 */) {}

// Range: 0x80504DE0 -> 0x80504DF4
int RndText::CollidePlane() {}

// Range: 0x80504DF4 -> 0x80504EB0
void RndText::Replace(class RndText * const this /* r29 */, class Object * from /* r30 */, class Object * to /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndFont;
}

static int TEXT_REV; // size: 0x4, address: 0x80A47430
// Range: 0x80504EB0 -> 0x80504EF4
void RndText::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80504EF4 -> 0x80505250
void RndText::Load(class RndText * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int rev; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> static int TEXT_REV;
}

// Range: 0x80505250 -> 0x805052A4
void RndText::UpdateText(class RndText * const this /* r30 */, unsigned char update_mesh /* r31 */) {}

// Range: 0x805052A4 -> 0x805052D4
void RndText::SetWrapWidth() {}

// Range: 0x805052D4 -> 0x80505348
void RndText::SetFixedLength(class RndText * const this /* r30 */, unsigned char * update /* r31 */) {}

// Range: 0x80505348 -> 0x80505378
void RndText::SetSize() {}

// Range: 0x80505378 -> 0x80505548
void RndText::SetColor(class RndText * const this /* r28 */, const class Color & c /* r29 */, unsigned char * update /* r30 */) {
    // Local variables
    class VertVector & verts; // r0
    class Vert * v; // r5

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80505548 -> 0x8050576C
void RndText::SetData(class RndText * const this /* r25 */, const char * text /* r26 */, class RndFont * font /* r27 */, float leading /* f28 */, float wrapWidth /* f29 */, float size /* f30 */, float italics /* f31 */, const class Color & color /* r28 */, unsigned char markup /* r29 */, int fixedLength /* r30 */, unsigned char * update /* r31 */) {
    // Local variables
    unsigned char textChanged; // r1+0x8
}

// Range: 0x8050576C -> 0x805058DC
void RndText::Copy(class RndText * const this /* r29 */, const class Object * o /* r31 */, enum CopyType type /* r30 */) {
    // Local variables
    const class RndText * t; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndText;
}

// Range: 0x805058DC -> 0x80505A6C
void RndText::Print(class RndText * const this /* r27 */) {
    // Local variables
    class TextStream & d; // r28

    // References
    // -> class Debug TheDebug;
}

// Range: 0x80505A6C -> 0x80505A84
int RndText::GetMinHyphenationWordLength() {
    // References
    // -> class Hyphenator TheHyphenator;
}

// Range: 0x80505A84 -> 0x80505AA0
int RndText::GetMinHyphenationPrefix() {
    // References
    // -> class Hyphenator TheHyphenator;
}

// Range: 0x80505AA0 -> 0x80505ABC
int RndText::GetMinHyphenationSuffix() {
    // References
    // -> class Hyphenator TheHyphenator;
}

// Range: 0x80505ABC -> 0x80505AEC
void RndText::SetUseAutoHyphenation() {}

// Range: 0x80505AEC -> 0x80505B1C
void RndText::SetMinHyphenationWordLength() {}

// Range: 0x80505B1C -> 0x80505B4C
void RndText::SetMinHyphenationPrefix() {}

// Range: 0x80505B4C -> 0x80505B7C
void RndText::SetMinHyphenationSuffix() {}

// Range: 0x80505B7C -> 0x80505E50
void * RndText::RndText(class RndText * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
    // -> class Symbol name;
    // -> struct [anonymous] __vt__32ObjOwnerPtr<7RndFont,9ObjectDir>;
    // -> struct [anonymous] __vt__7RndText;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x80505E50 -> 0x80506068
void * RndText::~RndText(class RndText * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__32ObjOwnerPtr<7RndFont,9ObjectDir>;
    // -> struct [anonymous] __vt__7RndText;
}

// Range: 0x80506068 -> 0x80506134
void RndText::SetFont(class RndText * const this /* r29 */, class RndFont * font /* r30 */, unsigned char * update /* r31 */) {}

// Range: 0x80506134 -> 0x80506164
void RndText::SetAlignment() {}

// Range: 0x80506164 -> 0x805063D0
char * RndText::ParseMarkup(const class RndText * const this /* r27 */, const char * c /* r30 */, class Style * style /* r31 */, float size /* f31 */) {
    // Local variables
    unsigned char stop; // r28
    int r; // r1+0x14
    int g; // r1+0x10
    int b; // r1+0xC
    int a; // r1+0x8

    // References
    // -> static float gSuperscriptScale;
}

// Range: 0x805063D0 -> 0x80506500
unsigned char canBreak() {
    // Local variables
    char c; // r0
}

// Range: 0x80506500 -> 0x80506544
float segmentLength() {
    // Local variables
    float lineLen; // f1
    int j; // r3
}

// Range: 0x80506544 -> 0x80506998
void RndText::ComputeCharWidths(class RndText * const this /* r21 */, float * charWidths /* r22 */, const char * in /* r23 */, int len /* r24 */, class Style & style /* r25 */) {
    // Local variables
    const char * cur; // r30
    unsigned char badCharNotify; // r29
    unsigned char negCharNotify; // r28
    float stopSize; // f31
    char lastChar; // r27
    int i; // r26
    class String n; // r1+0x14
    int i; // r20
    class String n; // r1+0x8
    int i; // r20

    // References
    // -> unsigned int npos;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80506998 -> 0x80507C78
void RndText::WrapText(class RndText * const this /* r16 */, const char * in /* r17 */, const class Style & style /* r15 */, class vector & lines /* f3 */) {
    // Local variables
    int len; // r28
    int * pHypPoints; // r31+0x58
    float * charWidths; // r27
    class WrapPoint * pWrapPoints; // r26
    unsigned char hyphenationOk; // r0
    float hyphenWidth; // f0
    class Style curStyle; // r31+0xA0
    const char * cur; // r25
    int numWp; // r24
    float maxWidth[5]; // r31+0x5C
    unsigned char doBreak; // r14
    int offset; // r23
    int prevOffset; // r18
    unsigned char isHyphenBreak; // r31+0x54
    int bestWp; // r22
    int bestWpCost; // r21
    float bestLineLen; // f30
    unsigned char scanDone; // r20
    int i; // r19
    float lineLen; // f29
    int cost; // r18
    float lastLineLen; // f0
    float err; // f1
    int totalCost; // r0
    class WrapPoint & wp; // r5
    int bestWp; // r22
    int bestWpCost; // r29
    float bestLineLen; // f29
    unsigned char scanDone; // f14
    int i; // r19
    int offset; // r20
    float lineLen; // f30
    int cost; // r21
    float lastLineLen; // f0
    float err; // f1
    int totalCost; // r0
    class WrapPoint & wp; // r5
    int wpIdx; // r4
    int prevWp; // r5
    class WrapPoint & wp; // r14
    class WrapPoint & nwp; // r4
    class Line curLine; // r31+0x1C0
    class Line curLine; // r31+0x170
    float z; // f29
    float vSize; // f4
    int i; // r5

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class WrapPoint * gWrapPoints;
}

// Range: 0x80507C78 -> 0x80507E98
void RndText::SetText(class RndText * const this /* r30 */, const char * text /* r29 */, unsigned char * update /* r31 */) {
    // Local variables
    class String tmp; // r1+0x8
    char * c; // r3
    char * c; // r3

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * sIgnoreMissingText;
}

// Range: 0x80507E98 -> 0x80508074
float RndText::GetStringWidth(const class RndText * const this /* r25 */, const char * text /* r26 */, const char * end /* r27 */, unsigned char trailingKerning /* r28 */, class Style * style /* r29 */) {
    // Local variables
    float width; // f31
    char lastChar; // r31
    class Style s; // r1+0x10
    float size; // f30
    const char * cur; // [invalid]
    char c; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80508074 -> 0x8050828C
void RndText::ResetFaces(class RndText * const this /* r31 */, int numFaces /* r29 */) {
    // Local variables
    class Face * f; // r29
    int i; // r4

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8050828C -> 0x805085EC
void RndText::UpdateMesh(class RndText * const this /* r30 */) {
    // Local variables
    int sync; // r31
    int num_faces; // r0
    int num_verts; // r28

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805085EC -> 0x805088D0
void SetupCharVerts(char c /* r28 */, class Vert * & v /* r30 */, float x /* f27 */, float h /* f28 */, float z /* f29 */, float it /* f30 */, class Style & style /* r31 */, class RndFont * font /* r29 */) {
    // Local variables
    float w; // f31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805088D0 -> 0x80508D34
void RndText::CreateLines(class RndText * const this /* r28 */) {
    // Local variables
    class Vert * v; // r1+0x10
    class Style style; // r1+0x20
    float it; // f31
    float h; // f30
    float size; // f29
    int i; // r30
    class Line & line; // r0
    float z; // f28
    float x; // f27
    char lastChar; // r26
    const char * c; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80508D34 -> 0x80508D3C
void RndText::ReserveLines() {}

// Range: 0x80508D3C -> 0x80508E60
class Vector3 RndText::GetCharPos() {
    // Local variables
    const char * c; // r5
    int i; // r8
    class Style s; // r1+0x10
    float x; // f0
}

// Range: 0x80508E60 -> 0x80508EA4
void RndText::GetVerticalBounds() {}

// Range: 0x80508EA4 -> 0x80508EFC
float RndText::MaxLineWidth() {
    // Local variables
    float maxWidth; // f1
    int i; // r6
}

// Range: 0x80508EFC -> 0x8050915C
void RndText::GetStringDimensions(class RndText * const this /* r28 */, float & width /* r29 */, float & height /* r30 */, class vector & lines /* r31 */) {
    // Local variables
    class Style style; // r1+0x20
    class Line * i; // r3

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8050915C -> 0x80509170
void RndText::DrawShowing() {}

// Range: 0x80509170 -> 0x80509248
unsigned char RndText::MakeWorldSphere(class RndText * const this /* r30 */, class Sphere & s /* r31 */) {}

// Range: 0x80509248 -> 0x805092B0
void RndText::UpdateSphere(class RndText * const this /* r31 */) {}

static class Symbol _s; // size: 0x4, address: 0x80A53A30
static class Symbol _s; // size: 0x4, address: 0x80A53A38
static class Symbol _s; // size: 0x4, address: 0x80A53A40
static class Symbol _s; // size: 0x4, address: 0x80A53A48
static class Symbol _s; // size: 0x4, address: 0x80A53A50
static class Symbol _s; // size: 0x4, address: 0x80A53A58
static class Symbol _s; // size: 0x4, address: 0x80A53A60
static class Symbol _s; // size: 0x4, address: 0x80A53A68
static class Symbol _s; // size: 0x4, address: 0x80A53A70
// Range: 0x805092B0 -> 0x8050A320
class DataNode RndText::Handle(class RndText * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x50
    class MessageTimer _mt; // r1+0xA8
    class DataNode r; // r1+0xA0
    class DataNode r; // r1+0x98
    class DataNode r; // r1+0x90
    class DataNode r; // r1+0x88
    class DataNode r; // r1+0x80
    class DataNode r; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode _n; // r1+0x68
    class DataNode _n; // r1+0x60
    class DataNode _n; // r1+0x58

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

// Range: 0x8050A320 -> 0x8050A390
class DataNode RndText::OnSetFixedLength(class RndText * const this /* r30 */, class DataArray * a /* r31 */) {}

// Range: 0x8050A390 -> 0x8050A41C
class DataNode RndText::OnSetFont(class RndText * const this /* r30 */, class DataArray * a /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndFont;
}

// Range: 0x8050A41C -> 0x8050A48C
class DataNode RndText::OnSetAlign(class RndText * const this /* r30 */, class DataArray * a /* r31 */) {}

// Range: 0x8050A48C -> 0x8050A4FC
class DataNode RndText::OnSetText(class RndText * const this /* r30 */, class DataArray * a /* r31 */) {}

// Range: 0x8050A4FC -> 0x8050A568
class DataNode RndText::OnSetWrapWidth(class RndText * const this /* r30 */, class DataArray * a /* r31 */) {}

// Range: 0x8050A568 -> 0x8050A5D4
class DataNode RndText::OnSetSize(class RndText * const this /* r30 */, class DataArray * a /* r31 */) {}

// Range: 0x8050A5D4 -> 0x8050A6C4
class DataNode RndText::OnSetColor(class RndText * const this /* r30 */, class DataArray * a /* r31 */) {}

// Range: 0x8050A6C4 -> 0x8050A76C
unsigned char RndText::SyncProperty(class RndText * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {}

struct {
    // total size: 0xFC
} __vt__7RndText; // size: 0xFC, address: 0x80902780
// Range: 0x8050A76C -> 0x8050A798
void _Vector_base::_M_throw_length_error() {}

struct {
    // total size: 0x8
} __RTTI__PQ27RndText4Line; // size: 0x8, address: 0x80902A98
class HyphenatorException {
    // total size: 0x10
public:
    class Symbol mString; // offset 0x0, size 0x4
    signed char mHyphens[10]; // offset 0x4, size 0xA
};
class HyphenatorPattern {
    // total size: 0x14
public:
    char mString[10]; // offset 0x0, size 0xA
    signed char mThresh[10]; // offset 0xA, size 0xA
};
struct HyphenationState {
    // total size: 0x1C
    int mMinLength; // offset 0x0, size 0x4
    int mMinPrefix; // offset 0x4, size 0x4
    int mMinSuffix; // offset 0x8, size 0x4
    int mMaxHyphens; // offset 0xC, size 0x4
    int * mOutputPoints; // offset 0x10, size 0x4
    int mOutputIdx; // offset 0x14, size 0x4
    const char * mText; // offset 0x18, size 0x4
};
class Hyphenator {
    // total size: 0x20
    int mMinLength; // offset 0x0, size 0x4
    int mMinPrefix; // offset 0x4, size 0x4
    int mMinSuffix; // offset 0x8, size 0x4
    int mNumExceptions; // offset 0xC, size 0x4
    int mNumPatterns; // offset 0x10, size 0x4
    class HyphenatorException * mExceptions; // offset 0x14, size 0x4
    class HyphenatorPattern * mPatterns; // offset 0x18, size 0x4
    unsigned char mInitted; // offset 0x1C, size 0x1
};

