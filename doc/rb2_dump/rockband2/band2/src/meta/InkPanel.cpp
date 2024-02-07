/*
    Compile unit: C:\rockband2\band2\src\meta\InkPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800FAAA8 -> 0x800FAF8C
*/
class DataArray * types; // size: 0x4, address: 0x80A4B270
class Symbol name; // size: 0x4, address: 0x80A4B278
class InkProvider : public ListProvider, public Object {
    // total size: 0x30
    class DataArray * mInkList; // offset 0x2C, size 0x4
};
class InkPanel : public UIPanel {
    // total size: 0x90
    class InkProvider mInkProvider; // offset 0x30, size 0x30
    class Symbol mGender; // offset 0x60, size 0x4
};
// Range: 0x800FAAA8 -> 0x800FAADC
void InkPanel::Enter(class InkPanel * const this /* r31 */) {}

// Range: 0x800FAADC -> 0x800FAAE0
void InkPanel::Exit() {}

// Range: 0x800FAAE0 -> 0x800FAAEC
void InkPanel::SetGender() {}

static class Symbol _s; // size: 0x4, address: 0x80A4B280
static class Symbol _s; // size: 0x4, address: 0x80A4B288
// Range: 0x800FAAEC -> 0x800FAF8C
class DataNode InkPanel::Handle(class InkPanel * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x30
    class MessageTimer _mt; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0xAC
} __vt__8InkPanel; // size: 0xAC, address: 0x80888734
struct {
    // total size: 0x8
} __RTTI__8InkPanel; // size: 0x8, address: 0x80888808
struct {
    // total size: 0x8
} __RTTI__8BandList; // size: 0x8, address: 0x80888898
struct {
    // total size: 0x8
} __RTTI__9BandLabel; // size: 0x8, address: 0x80888988
struct {
    // total size: 0x8
} __RTTI__12BandTextComp; // size: 0x8, address: 0x808889F0

