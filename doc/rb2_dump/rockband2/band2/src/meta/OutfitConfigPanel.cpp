/*
    Compile unit: C:\rockband2\band2\src\meta\OutfitConfigPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8012D9CC -> 0x8012F468
*/
class DataArray * types; // size: 0x4, address: 0x80A4BCF8
// Range: 0x8012D9CC -> 0x8012DA90
void * OutfitConfigPanel::OutfitConfigPanel(class OutfitConfigPanel * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__17OutfitConfigPanel;
}

// Range: 0x8012DA90 -> 0x8012DB14
void OutfitConfigPanel::Unload(class OutfitConfigPanel * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8012DB14 -> 0x8012DB54
int OutfitConfigPanel::NumColors() {}

// Range: 0x8012DB54 -> 0x8012DC70
class DataNode OutfitConfigPanel::OnMsg(class OutfitConfigPanel * const this /* r30 */, const class UIComponentScrollMsg & msg /* r31 */) {
    // Local variables
    class UIList * l; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__6UIList;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11UIComponent;
    // -> class UIManager TheUI;
}

// Range: 0x8012DC70 -> 0x8012E020
class DataNode OutfitConfigPanel::OnMsg(class OutfitConfigPanel * const this /* r31 */) {
    // Local variables
    class OutfitConfig * oc; // r26
    class TourCharLocal * tc; // r25
    class Symbol category; // r1+0x44
    class Symbol charCategory; // r1+0x40
    class Symbol selected; // r1+0x3C
    unsigned char hasOutfit; // r0
    unsigned char change; // r24
    int i; // r23

    // References
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8UIScreen;
    // -> class ObjectDir * sMainDir;
    // -> class UIManager TheUI;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8012E020 -> 0x8012E0A4
void OutfitConfigPanel::Confirm(class OutfitConfigPanel * const this /* r30 */) {
    // References
    // -> class UIManager TheUI;
}

static class Message on_color_select; // size: 0x8, address: 0x80979200
// Range: 0x8012E0A4 -> 0x8012E4D8
void OutfitConfigPanel::SetColor(class OutfitConfigPanel * const this /* r30 */, int color /* r31 */) {
    // Local variables
    class TourCharLocal * tc; // r29
    class CompositeCharacter * cc; // r28
    class Symbol category; // r1+0x34
    class Symbol selected; // r1+0x30

    // References
    // -> static class Message on_color_select;
    // -> struct [anonymous] __vt__7Message;
    // -> const char * gNullStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12OutfitConfig;
}

static class Message on_pop; // size: 0x8, address: 0x80979218
// Range: 0x8012E4D8 -> 0x8012E7DC
class DataNode OutfitConfigPanel::OnMsg(class OutfitConfigPanel * const this /* r31 */) {
    // Local variables
    class TourCharLocal * tc; // r28
    class Symbol category; // r1+0x24

    // References
    // -> static class Message on_pop;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8UIScreen;
    // -> class ObjectDir * sMainDir;
    // -> class UIManager TheUI;
}

static class Symbol _s; // size: 0x4, address: 0x80A4BD00
static class Symbol _s; // size: 0x4, address: 0x80A4BD08
// Range: 0x8012E7DC -> 0x8012F1C8
class DataNode OutfitConfigPanel::Handle(class OutfitConfigPanel * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x4C
    class MessageTimer _mt; // r1+0x88
    class DataNode r; // r1+0x80
    class DataNode r; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode _n; // r1+0x68

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__13ButtonDownMsg;
    // -> class Symbol t;
    // -> struct [anonymous] __vt__20UIComponentSelectMsg;
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

static class Symbol _s; // size: 0x4, address: 0x80A4BD10
static class Symbol _s; // size: 0x4, address: 0x80A4BD18
// Range: 0x8012F1C8 -> 0x8012F468
unsigned char OutfitConfigPanel::SyncProperty(class OutfitConfigPanel * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11OutfitPanel;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x8
} __RTTI__12OutfitConfig; // size: 0x8, address: 0x808902A0
struct {
    // total size: 0x8
} __RTTI__10BandSwatch; // size: 0x8, address: 0x80890308
struct {
    // total size: 0x8
} __RTTI__11OutfitPanel; // size: 0x8, address: 0x808903C8
struct {
    // total size: 0xB0
} __vt__17OutfitConfigPanel; // size: 0xB0, address: 0x808903D0
struct {
    // total size: 0x8
} __RTTI__17OutfitConfigPanel; // size: 0x8, address: 0x808904B0

