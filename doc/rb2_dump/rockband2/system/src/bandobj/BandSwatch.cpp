/*
    Compile unit: C:\rockband2\system\src\bandobj\BandSwatch.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80264F08 -> 0x80265F20
*/
class DataArray * types; // size: 0x4, address: 0x80A4F308
class Symbol name; // size: 0x4, address: 0x80A4F310
class Symbol name; // size: 0x4, address: 0x80A4F318
class ColorPalette * sDummyPalette; // size: 0x4, address: 0x80A4F31C
class BandSwatch : public UIList {
    // total size: 0x2A0
    class ObjPtr mColorPalette; // offset 0x25C, size 0xC
};
// Range: 0x80264F08 -> 0x80265108
void BandSwatch::Init() {
    // Local variables
    int i; // r31

    // References
    // -> class LoadMgr TheLoadMgr;
    // -> class ColorPalette * sDummyPalette;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12ColorPalette;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class UIManager TheUI;
}

// Range: 0x80265108 -> 0x80265150
void BandSwatch::Terminate() {
    // References
    // -> class ColorPalette * sDummyPalette;
}

// Range: 0x80265224 -> 0x8026534C
void * BandSwatch::BandSwatch(class BandSwatch * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__33ObjPtr<12ColorPalette,9ObjectDir>;
    // -> struct [anonymous] __vt__10BandSwatch;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x8026534C -> 0x8026543C
void BandSwatch::Copy(class BandSwatch * const this /* r28 */, enum CopyType type /* r29 */) {
    // Local variables
    const class BandSwatch * s; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10BandSwatch;
}

static int REV; // size: 0x4, address: 0x80A46ACC
static int gRev; // size: 0x4, address: 0x80A4F320
// Range: 0x8026543C -> 0x80265480
void BandSwatch::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80265480 -> 0x802654DC
void BandSwatch::Load(class BandSwatch * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x802654DC -> 0x802655BC
void BandSwatch::PreLoad(class BandSwatch * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int REV;
    // -> static int gRev;
}

static class Symbol colors; // size: 0x4, address: 0x80A4F328
// Range: 0x802655BC -> 0x802656B0
void BandSwatch::DrawShowing(class BandSwatch * const this /* r29 */) {
    // Local variables
    class Color c; // r1+0x20

    // References
    // -> static class Symbol colors;
}

// Range: 0x802656B0 -> 0x802656FC
char * BandSwatch::Text() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802656FC -> 0x802657D8
class RndMat * BandSwatch::Mat() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndMat;
}

// Range: 0x802657D8 -> 0x8026580C
int BandSwatch::NumData() {}

// Range: 0x8026580C -> 0x80265890
void BandSwatch::GetColor(const class BandSwatch * const this /* r29 */, class Color & color /* r30 */, int data /* r31 */) {}

// Range: 0x80265890 -> 0x802658F8
void BandSwatch::SetColors(class BandSwatch * const this /* r30 */, class ColorPalette * cp /* r31 */) {}

// Range: 0x802658F8 -> 0x80265918
class vector & BandSwatch::Colors() {
    // References
    // -> class ColorPalette * sDummyPalette;
}

static class Symbol _s; // size: 0x4, address: 0x80A4F330
// Range: 0x80265918 -> 0x80265CF8
class DataNode BandSwatch::Handle(class BandSwatch * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12ColorPalette;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A4F338
// Range: 0x80265CF8 -> 0x80265DD0
unsigned char BandSwatch::SyncProperty(class BandSwatch * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
}

// Range: 0x80265DD0 -> 0x80265F20
unsigned char PropSync(class ObjPtr & p /* r29 */, class DataNode & n /* r30 */, enum PropOp op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12ColorPalette;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x8
} __RTTI__12ColorPalette; // size: 0x8, address: 0x808B7D80
struct {
    // total size: 0x1CC
} __vt__10BandSwatch; // size: 0x1CC, address: 0x808B7D88
struct {
    // total size: 0x18
} __vt__33ObjPtr<12ColorPalette,9ObjectDir>; // size: 0x18, address: 0x808B7F58
struct {
    // total size: 0x8
} __RTTI__33ObjPtr<12ColorPalette,9ObjectDir>; // size: 0x8, address: 0x808B7FA0

