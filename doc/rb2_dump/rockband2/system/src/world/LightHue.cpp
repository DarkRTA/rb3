/*
    Compile unit: C:\rockband2\system\src\world\LightHue.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8043FB64 -> 0x80440DFC
*/
class DataArray * types; // size: 0x4, address: 0x80A524F0
class Symbol name; // size: 0x4, address: 0x80A524F8
// Range: 0x8043FB64 -> 0x8043FBDC
void * LightHue::LightHue(class LightHue * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__8FilePath;
    // -> struct [anonymous] __vt__8LightHue;
}

// Range: 0x8043FBDC -> 0x8043FCF8
void * LightHue::~LightHue(class LightHue * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__8LightHue;
}

// Range: 0x8043FCF8 -> 0x8043FD74
void LightHue::Copy(class LightHue * const this /* r30 */, const class Object * o /* r31 */) {
    // Local variables
    const class LightHue * t; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8LightHue;
}

static int REV; // size: 0x4, address: 0x80A524FC
// Range: 0x8043FD74 -> 0x8043FDB8
void LightHue::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8043FDB8 -> 0x8043FE14
void LightHue::Load(class LightHue * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x8043FE14 -> 0x8043FF28
void LightHue::PreLoad(class LightHue * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int rev; // r1+0x8

    // References
    // -> class LoadMgr TheLoadMgr;
    // -> class FilePath sRoot;
    // -> class Debug TheDebug;
    // -> static int REV;
}

// Range: 0x8043FF28 -> 0x8043FF44
void LightHue::PostLoad() {
    // References
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x8043FF44 -> 0x80440328
void LightHue::Sync(class LightHue * const this /* r29 */) {
    // Local variables
    int size; // r1+0x40
    char * buffer; // r31
    class RndBitmap bm; // r1+0xB4
    class BufStream b; // r1+0x90
    int i; // r30
    unsigned char r; // r1+0x33
    unsigned char g; // r1+0x32
    unsigned char b; // r1+0x31
    unsigned char a; // r1+0x30
    float hue; // r1+0x3C
    float sat; // r1+0x38
    float lit; // r1+0x34

    // References
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x80440328 -> 0x80440788
void LightHue::TranslateColor(class LightHue * const this /* r23 */, class Color & out /* r24 */) {
    // Local variables
    float intensity; // f30
    class Color c; // r1+0x30
    float hue; // r1+0x18
    float sat; // r1+0x14
    float lit; // r1+0x10
    class Vector3 frame; // r1+0x20
}

static class Symbol _s; // size: 0x4, address: 0x80A52504
// Range: 0x80440788 -> 0x80440B88
class DataNode LightHue::Handle(class LightHue * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x38
    class DataNode r; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x80440B88 -> 0x80440D00
class DataNode LightHue::OnSaveDefault(class DataArray * a /* r26 */) {
    // Local variables
    class RndBitmap bm; // r1+0x20
    int x; // r31
    class Color c; // r1+0x10
    unsigned char r; // r30
    unsigned char g; // r29
    unsigned char b; // r28
    int y; // r27
}

static class Symbol _s; // size: 0x4, address: 0x80A5250C
// Range: 0x80440D00 -> 0x80440DFC
unsigned char LightHue::SyncProperty(class LightHue * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
}

struct {
    // total size: 0x54
} __vt__8LightHue; // size: 0x54, address: 0x808ED8F8

