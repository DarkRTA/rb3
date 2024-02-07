/*
    Compile unit: C:\rockband2\band2\src\meta\OutfitGroupPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8012FCE0 -> 0x801308C8
*/
class DataArray * types; // size: 0x4, address: 0x80A4BD20
// Range: 0x8012FCE0 -> 0x8012FD90
void * OutfitGroupPanel::OutfitGroupPanel(class OutfitGroupPanel * const this /* r30 */) {
    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__16OutfitGroupPanel;
    // -> struct [anonymous] __vt__12ListProvider;
}

struct AlphaCmp {
    // total size: 0x1
};
// Range: 0x8012FD90 -> 0x8012FDC8
char * OutfitGroupPanel::Text() {}

// Range: 0x8012FDC8 -> 0x8012FDE0
int OutfitGroupPanel::NumData() {}

// Range: 0x8012FDE0 -> 0x8012FDF0
class Symbol OutfitGroupPanel::DataSymbol() {}

// Range: 0x8012FDF0 -> 0x8012FE70
class DataNode OutfitGroupPanel::OnMsg(class OutfitGroupPanel * const this /* r30 */) {}

// Range: 0x8012FE70 -> 0x8012FF14
void OutfitGroupPanel::SelectOutfit(class OutfitGroupPanel * const this /* r30 */, class Symbol & outfit /* r29 */) {
    // Local variables
    class Symbol category; // r1+0x1C
    class CompositeCharacter * cc; // r31
    class TourCharLocal * tc; // r30
}

static class Symbol _s; // size: 0x4, address: 0x80A4BD28
static class Symbol _s; // size: 0x4, address: 0x80A4BD30
// Range: 0x8012FF14 -> 0x80130720
class DataNode OutfitGroupPanel::Handle(class OutfitGroupPanel * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x38
    class MessageTimer _mt; // r1+0x68
    class DataNode r; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode _n; // r1+0x50

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__13ButtonDownMsg;
    // -> class Symbol t;
    // -> struct [anonymous] __vt__20UIComponentScrollMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11OutfitPanel;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A4BD38
// Range: 0x80130720 -> 0x801308C8
unsigned char OutfitGroupPanel::SyncProperty(class OutfitGroupPanel * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11OutfitPanel;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x104
} __vt__16OutfitGroupPanel; // size: 0x104, address: 0x808909B0
struct {
    // total size: 0x8
} __RTTI__16OutfitGroupPanel; // size: 0x8, address: 0x80890AF0

