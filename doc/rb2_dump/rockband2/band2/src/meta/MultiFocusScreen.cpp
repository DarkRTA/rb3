/*
    Compile unit: C:\rockband2\band2\src\meta\MultiFocusScreen.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80121720 -> 0x80124F00
*/
class DataArray * types; // size: 0x4, address: 0x80A4BB48
static class Message ready; // size: 0x8, address: 0x80979008
// Range: 0x80121720 -> 0x801219A4
unsigned char MultiFocusScreen::AllReady(class MultiFocusScreen * const this /* r31 */) {
    // Local variables
    class PanelDir * * it; // r28
    class DataNode n; // r1+0x28

    // References
    // -> const char * gNullStr;
    // -> static class Message ready;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x801219A4 -> 0x80121A0C
void MultiFocusScreen::SetTypeDef(class MultiFocusScreen * const this /* r30 */, class DataArray * data /* r31 */) {}

static class Message enter; // size: 0x8, address: 0x80979020
// Range: 0x80121A0C -> 0x80121F80
void MultiFocusScreen::Enter(class MultiFocusScreen * const this /* r24 */, class UIScreen * from /* r25 */) {
    // Local variables
    class DataArray * pp; // r29
    class UIPanel * main; // r0
    class DataArray * panel_dir_type; // r28
    class DataArray * slots; // r29
    int numSlots; // r27
    int i; // r26
    const char * dir_name; // r21
    class PanelDir * p; // r1+0x48

    // References
    // -> class NetSession * TheNetSession;
    // -> const char * gNullStr;
    // -> struct [anonymous] __RTTI__8PanelDir;
    // -> const char * kAssertStr;
    // -> static class Message enter;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7UIPanel;
    // -> class ObjectDir * sMainDir;
}

static class Message exit; // size: 0x8, address: 0x80979038
// Range: 0x80121F80 -> 0x801220C0
void MultiFocusScreen::Exit(class MultiFocusScreen * const this /* r30 */, class UIScreen * to /* r31 */) {
    // References
    // -> static class Message exit;
    // -> struct [anonymous] __vt__7Message;
    // -> class NetSession * TheNetSession;
    // -> const char * gNullStr;
}

// Range: 0x801220C0 -> 0x80122134
void MultiFocusScreen::UnloadPanels(class MultiFocusScreen * const this /* r30 */) {}

static class Message poll; // size: 0x8, address: 0x80979050
// Range: 0x80122134 -> 0x80122244
void MultiFocusScreen::Poll(class MultiFocusScreen * const this /* r31 */) {
    // References
    // -> static class Message poll;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x80122244 -> 0x801222DC
class DataNode MultiFocusScreen::OnMsg(class MultiFocusScreen * const this /* r29 */, const class ButtonDownMsg & msg /* r30 */) {
    // References
    // -> class BandUI * TheBandUI;
}

// Range: 0x801222DC -> 0x80122374
class DataNode MultiFocusScreen::OnMsg(class MultiFocusScreen * const this /* r29 */, const class UIComponentScrollMsg & msg /* r30 */) {
    // References
    // -> class BandUI * TheBandUI;
}

// Range: 0x80122374 -> 0x8012240C
class DataNode MultiFocusScreen::OnMsg(class MultiFocusScreen * const this /* r29 */, const class UIComponentSelectMsg & msg /* r30 */) {
    // References
    // -> class BandUI * TheBandUI;
}

// Range: 0x8012240C -> 0x801224A4
class DataNode MultiFocusScreen::OnMsg(class MultiFocusScreen * const this /* r29 */, const class UIComponentSelectDoneMsg & msg /* r30 */) {
    // References
    // -> class BandUI * TheBandUI;
}

// Range: 0x801224A4 -> 0x8012256C
class DataNode MultiFocusScreen::OnMsg(class MultiFocusScreen * const this /* r29 */, const class UIComponentFocusChangeMsg & msg /* r30 */) {
    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8PanelDir;
    // -> class BandUI * TheBandUI;
}

// Range: 0x8012256C -> 0x801226AC
class DataNode MultiFocusScreen::OnMsg(class MultiFocusScreen * const this /* r29 */, const class NetComponentFocusMsg & msg /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__4User;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Message playerNum; // size: 0x8, address: 0x80979068
// Range: 0x801226AC -> 0x80122914
class DataNode MultiFocusScreen::OnMsg(class MultiFocusScreen * const this /* r28 */, const class NetComponentSelectMsg & msg /* r29 */) {
    // Local variables
    class PanelDir * * it; // r30
    class UIComponent * c; // r0

    // References
    // -> static class Message playerNum;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__4User;
}

static class Message playerNum; // size: 0x8, address: 0x80979080
// Range: 0x80122914 -> 0x80122C34
class DataNode MultiFocusScreen::OnMsg(class MultiFocusScreen * const this /* r28 */, const class NetComponentScrollMsg & msg /* r29 */) {
    // Local variables
    class User * u; // r0
    class PanelDir * * it; // r30
    class UIComponent * c; // r26
    class UIList * list; // r31
    class UISlider * slider; // r28

    // References
    // -> struct [anonymous] __RTTI__8UISlider;
    // -> struct [anonymous] __RTTI__11UIComponent;
    // -> struct [anonymous] __RTTI__6UIList;
    // -> static class Message playerNum;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__4User;
}

static class Symbol update; // size: 0x4, address: 0x80A4BB54
static class Message updateMsg; // size: 0x8, address: 0x80979098
// Range: 0x80122C34 -> 0x80122DB8
class DataNode MultiFocusScreen::OnMsg(class MultiFocusScreen * const this /* r31 */) {
    // References
    // -> static class Message updateMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> static class Symbol update;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol update; // size: 0x4, address: 0x80A4BB5C
static class Message updateMsg; // size: 0x8, address: 0x809790B0
// Range: 0x80122DB8 -> 0x80122F3C
class DataNode MultiFocusScreen::OnMsg(class MultiFocusScreen * const this /* r31 */) {
    // References
    // -> static class Message updateMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> static class Symbol update;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80122F3C -> 0x80122FDC
class DataNode MultiFocusScreen::OnUpdate(class MultiFocusScreen * const this /* r31 */) {
    // Local variables
    const class DataNode & n; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8PanelDir;
}

static class Message playerNum; // size: 0x8, address: 0x809790C8
// Range: 0x80122FDC -> 0x801231CC
class DataNode MultiFocusScreen::Update(class MultiFocusScreen * const this /* r28 */, int player_num /* r29 */) {
    // Local variables
    class PanelDir * p; // r31
    class PanelDir * * it; // r30

    // References
    // -> static class Message playerNum;
    // -> struct [anonymous] __vt__7Message;
}

static class Message current_option; // size: 0x8, address: 0x809790E0
static class Message init; // size: 0x8, address: 0x809790F8
static class Message update; // size: 0x8, address: 0x80979110
// Range: 0x801231CC -> 0x801235F8
class DataNode MultiFocusScreen::Update(class MultiFocusScreen * const this /* r28 */, class PanelDir * p /* r29 */) {
    // Local variables
    class Symbol newOpt; // r1+0x3C

    // References
    // -> static class Message update;
    // -> const char * gNullStr;
    // -> static class Message init;
    // -> static class Message current_option;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801235F8 -> 0x80123798
class DataNode MultiFocusScreen::OnExportAll(class MultiFocusScreen * const this /* r29 */, class DataArray * a /* r30 */) {
    // Local variables
    class DataNode & n; // r0

    // References
    // -> struct [anonymous] __vt__7Message;
}

static class Symbol update; // size: 0x4, address: 0x80A4BB68
// Range: 0x80123798 -> 0x801238DC
void MultiFocusScreen::ExportAll(class MultiFocusScreen * const this /* r29 */, const class Message & msg /* r30 */) {
    // Local variables
    class PanelDir * * it; // r31

    // References
    // -> const char * gNullStr;
    // -> static class Symbol update;
}

static class Message playerNum; // size: 0x8, address: 0x80979128
static class Message playerNum; // size: 0x8, address: 0x80979140
static class Message msg; // size: 0x8, address: 0x80979158
// Range: 0x801238DC -> 0x80123F6C
class DataNode MultiFocusScreen::ExportButtonDown(class MultiFocusScreen * const this /* r25 */, const class Message & msg /* r26 */, int player /* r27 */) {
    // Local variables
    class DataNode result; // r1+0x70
    class PanelDir * pPanelDir; // r29
    class PanelDir * * it; // r28
    class PanelDir * * it; // r28
    class DataNode n; // r1+0x68
    class UIComponent * c; // r0

    // References
    // -> const char * gNullStr;
    // -> static class Message msg;
    // -> static class Message playerNum;
    // -> static class Message playerNum;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class UIManager TheUI;
}

// Range: 0x80123F6C -> 0x80124048
class DataNode MultiFocusScreen::ExportToPlayer(class MultiFocusScreen * const this /* r28 */, const class Message & msg /* r29 */, int player /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class UIManager TheUI;
}

static class Message playerNum; // size: 0x8, address: 0x80979170
// Range: 0x80124048 -> 0x8012426C
class DataNode MultiFocusScreen::DoExportToPlayer(class DataNode * result /* r26 */, class MultiFocusScreen * const this /* r27 */, const class Message & msg /* r28 */, int player /* r29 */) {
    // Local variables
    class PanelDir * pPanelDir; // r31
    class PanelDir * * it; // r30

    // References
    // -> const char * gNullStr;
    // -> static class Message playerNum;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x8012426C -> 0x80124490
class DataNode MultiFocusScreen::OptionHandle(class DataNode * ret /* r29 */, class MultiFocusScreen * const this /* r26 */, class PanelDir * p /* r30 */, const class Message & msg /* r31 */, class Symbol & opt /* r27 */) {
    // Local variables
    class DataArray * h; // r4

    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80124490 -> 0x80124638
class DataNode MultiFocusScreen::OnShowChar(class MultiFocusScreen * const this /* r28 */, class DataArray * a /* r29 */) {
    // References
    // -> struct [anonymous] __vt__7Message;
    // -> class GameConfig * TheGameConfig;
}

static class Symbol _s; // size: 0x4, address: 0x80A4BB74
static class Symbol _s; // size: 0x4, address: 0x80A4BB7C
static class Symbol _s; // size: 0x4, address: 0x80A4BB84
static class Symbol _s; // size: 0x4, address: 0x80A4BB8C
// Range: 0x80124638 -> 0x80124F00
class DataNode MultiFocusScreen::Handle(class MultiFocusScreen * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x3C
    class MessageTimer _mt; // r1+0x100
    class DataNode r; // r1+0xF8
    class DataNode r; // r1+0xF0
    class DataNode r; // r1+0xE8
    class DataNode r; // r1+0xE0
    class DataNode r; // r1+0xD8
    class DataNode r; // r1+0xD0
    class DataNode r; // r1+0xC8
    class DataNode r; // r1+0xC0
    class DataNode r; // r1+0xB8
    class DataNode r; // r1+0xB0
    class DataNode r; // r1+0xA8
    class DataNode r; // r1+0xA0
    class DataNode r; // r1+0x98
    class DataNode _n; // r1+0x90

    // References
    // -> class DebugNotifier TheDebugNotifier;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x80
} __vt__16MultiFocusScreen; // size: 0x80, address: 0x8088E9D0
struct {
    // total size: 0x8
} __RTTI__16MultiFocusScreen; // size: 0x8, address: 0x8088EA88
struct {
    // total size: 0x8
} __RTTI__PP8PanelDir; // size: 0x8, address: 0x8088EB98

