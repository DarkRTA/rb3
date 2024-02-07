/*
    Compile unit: C:\rockband2\band2\src\meta\HelpBarPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800F2550 -> 0x800F6E54
*/
class Symbol t; // size: 0x4, address: 0x80A4B0EC
class DataArray * types; // size: 0x4, address: 0x80A4B0F0
class Symbol name; // size: 0x4, address: 0x80A4B0F8
static int gAnimSpeed; // size: 0x4, address: 0x80A4B0FC
static int gSwitchFrames; // size: 0x4, address: 0x80A4B100
// Range: 0x800F2550 -> 0x800F25EC
void * HelpBarWidget::HelpBarWidget(class HelpBarWidget * const this /* r30 */) {
    // References
    // -> const char * gNullStr;
}

// Range: 0x800F25EC -> 0x800F2740
void * HelpBarWidget::HelpBarWidget(class HelpBarWidget * const this /* r28 */, class UILabel * icon1 /* r29 */, class UILabel * icon2 /* r30 */, class UILabel * icon3 /* r31 */) {
    // References
    // -> const char * gNullStr;
}

// Range: 0x800F2740 -> 0x800F2884
void HelpBarWidget::RefreshAnim(class HelpBarWidget * const this /* r31 */) {
    // Local variables
    float curInFrame; // f1
    float alpha; // f0
}

static class Symbol symNullStr; // size: 0x4, address: 0x80A4B108
// Range: 0x800F2884 -> 0x800F2A48
void HelpBarWidget::UpdateAnim(class HelpBarWidget * const this /* r31 */) {
    // Local variables
    int desInFrame; // r4

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static int gAnimSpeed;
    // -> static class Symbol symNullStr;
}

// Range: 0x800F2A48 -> 0x800F2BE0
void HelpBarWidget::Update(class HelpBarWidget * const this /* r28 */, class Symbol & text /* r29 */, unsigned char cacheState /* r30 */, class Symbol & altText /* r31 */) {
    // References
    // -> static int gSwitchFrames;
    // -> const char * gNullStr;
    // -> class BandUI * TheBandUI;
}

class HelpBarPanel * sInstance; // size: 0x4, address: 0x80A4B10C
// Range: 0x800F2BE0 -> 0x800F2F08
void * HelpBarPanel::HelpBarPanel(class HelpBarPanel * const this /* r30 */) {
    // Local variables
    const class DataArray * config; // r28

    // References
    // -> static int gSwitchFrames;
    // -> static int gAnimSpeed;
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUI * TheBandUI;
    // -> class HelpBarPanel * sInstance;
    // -> struct [anonymous] __vt__12HelpBarPanel;
}

// Range: 0x800F2F08 -> 0x800F2FDC
void * HelpBarPanel::~HelpBarPanel(class HelpBarPanel * const this /* r29 */) {
    // References
    // -> class BandUI * TheBandUI;
    // -> const char * gNullStr;
    // -> class HelpBarPanel * sInstance;
    // -> struct [anonymous] __vt__12HelpBarPanel;
}

// Range: 0x800F2FDC -> 0x800F3210
void HelpBarPanel::FinishLoad(class HelpBarPanel * const this /* r24 */) {
    // Local variables
    class Symbol types[3]; // r1+0x1C
    int i; // r25
    class String cancel_str; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7UILabel;
    // -> class PlatformMgr ThePlatformMgr;
}

static class Symbol input_status_changed; // size: 0x4, address: 0x80A4B114
// Range: 0x800F3210 -> 0x800F44C4
void HelpBarPanel::Enter(class HelpBarPanel * const this /* r25 */) {
    // Local variables
    class ObjectDir * dir; // r26

    // References
    // -> const char * gNullStr;
    // -> const char * kAssertStr;
    // -> class InputMgr * TheInputMgr;
    // -> static class Symbol input_status_changed;
    // -> struct [anonymous] __RTTI__13RndAnimatable;
    // -> struct [anonymous] __RTTI__7UILabel;
    // -> class Rnd & TheRnd;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
}

// Range: 0x800F44C4 -> 0x800F4538
void HelpBarPanel::SetTypeDef(class DataArray * data /* r31 */) {
    // References
    // -> static int gSwitchFrames;
    // -> static int gAnimSpeed;
}

// Range: 0x800F4538 -> 0x800F458C
void HelpBarPanel::Exit(class HelpBarPanel * const this /* r31 */) {
    // References
    // -> class InputMgr * TheInputMgr;
    // -> const char * gNullStr;
}

// Range: 0x800F458C -> 0x800F4618
void HelpBarPanel::FadeOut(class HelpBarPanel * const this /* r29 */) {
    // Local variables
    int i; // r30

    // References
    // -> const char * gNullStr;
}

// Range: 0x800F4618 -> 0x800F4624
void HelpBarPanel::FadeIn() {}

// Range: 0x800F4624 -> 0x800F4650
void HelpBarPanel::Draw() {}

// Range: 0x800F4650 -> 0x800F4940
void HelpBarPanel::Poll(class HelpBarPanel * const this /* r31 */) {
    // Local variables
    int i; // r5
    int i; // r30
}

// Range: 0x800F4940 -> 0x800F4948
int HelpBarPanel::GetHeightFrame() {}

// Range: 0x800F4948 -> 0x800F4954
void HelpBarPanel::SetConfig() {}

// Range: 0x800F4954 -> 0x800F495C
void HelpBarPanel::BandEventStartHelpbar() {}

// Range: 0x800F495C -> 0x800F4A44
void HelpBarPanel::ShowIcon(const char * icon /* r30 */, unsigned char val /* r31 */, float xpos /* f31 */) {
    // Local variables
    class Vector3 v; // r1+0x10

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7UILabel;
}

// Range: 0x800F4A44 -> 0x800F5064
void HelpBarPanel::UpdateIcons(class HelpBarPanel * const this /* r27 */) {
    // Local variables
    unsigned char showGuitar; // r30
    unsigned char showDrum; // r29
    unsigned char showVocals; // r28
    float xpos; // f31
    unsigned char hasIcons; // r5
    int i; // r6

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7UILabel;
    // -> class InputMgr * TheInputMgr;
}

static class Symbol cancel; // size: 0x4, address: 0x80A4B11C
static class Symbol endgame_hb_leave_session; // size: 0x4, address: 0x80A4B124
static class Symbol waiting; // size: 0x4, address: 0x80A4B12C
static class Symbol helpbar_waiting_for; // size: 0x4, address: 0x80A4B134
// Range: 0x800F5064 -> 0x800F56F8
void HelpBarPanel::UpdateConfig(class HelpBarPanel * const this /* r28 */, class DataArray * elements /* r27 */, unsigned char cacheState /* r29 */) {
    // Local variables
    class DataArray * cfg; // r30
    class DataArray * c; // r0
    class BandUser * u; // r27
    class Symbol waiting_for; // r1+0x30
    class DataArray * w; // r27

    // References
    // -> static class Symbol helpbar_waiting_for;
    // -> static class Symbol waiting;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class SessionMgr * TheSessionMgr;
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> static class Symbol endgame_hb_leave_session;
    // -> static class Symbol cancel;
    // -> class InputMgr * TheInputMgr;
}

static class Message msg; // size: 0x8, address: 0x80978B60
// Range: 0x800F56F8 -> 0x800F5FA0
void HelpBarPanel::DoUpdateConfig(class HelpBarPanel * const this /* r26 */, class DataArray * elements /* r27 */, unsigned char cacheState /* r28 */) {
    // Local variables
    unsigned char updated[9]; // r1+0xC0
    int i; // r6
    int i; // r29
    int i; // r24

    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800F5FA0 -> 0x800F5FF0
class DataNode HelpBarPanel::OnMsg() {
    // References
    // -> class UIManager TheUI;
}

static class Symbol helpbar; // size: 0x4, address: 0x80A4B13C
// Range: 0x800F5FF0 -> 0x800F60D0
class DataNode HelpBarPanel::OnMsg(class HelpBarPanel * const this /* r30 */) {
    // Local variables
    class DataArray * cfg; // r31

    // References
    // -> class UIManager TheUI;
    // -> static class Symbol helpbar;
}

// Range: 0x800F60D0 -> 0x800F6168
class DataNode HelpBarPanel::OnMsg(class HelpBarPanel * const this /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x800F6168 -> 0x800F6424
void HelpBarPanel::OnUpdateWidget(class HelpBarPanel * const this /* r29 */, enum WidgetId widget /* r30 */, class DataArray * msg /* r28 */) {
    // Local variables
    class Symbol token; // r1+0x2C
    unsigned char cacheState; // r31
    class Symbol altToken; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A4B144
static class Symbol _s; // size: 0x4, address: 0x80A4B14C
static class Symbol _s; // size: 0x4, address: 0x80A4B154
static class Symbol _s; // size: 0x4, address: 0x80A4B15C
static class Symbol _s; // size: 0x4, address: 0x80A4B164
static class Symbol _s; // size: 0x4, address: 0x80A4B16C
static class Symbol _s; // size: 0x4, address: 0x80A4B174
static class Symbol _s; // size: 0x4, address: 0x80A4B17C
static class Symbol _s; // size: 0x4, address: 0x80A4B184
static class Symbol _s; // size: 0x4, address: 0x80A4B18C
static class Symbol _s; // size: 0x4, address: 0x80A4B194
static class Symbol _s; // size: 0x4, address: 0x80A4B19C
static class Symbol _s; // size: 0x4, address: 0x80A4B1A4
static class Symbol _s; // size: 0x4, address: 0x80A4B1AC
static class Symbol _s; // size: 0x4, address: 0x80A4B1B4
static class Symbol _s; // size: 0x4, address: 0x80A4B1BC
static class Symbol _s; // size: 0x4, address: 0x80A4B1C4
// Range: 0x800F6424 -> 0x800F6DD4
class DataNode HelpBarPanel::Handle(class HelpBarPanel * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x20
    class MessageTimer _mt; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode r; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode _n; // r1+0x40

    // References
    // -> class DebugNotifier TheDebugNotifier;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x800F6DD4 -> 0x800F6E54
unsigned char HelpBarPanel::SyncProperty(class HelpBarPanel * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {}

struct {
    // total size: 0xB0
} __vt__12HelpBarPanel; // size: 0xB0, address: 0x80887E10
struct {
    // total size: 0x8
} __RTTI__12HelpBarPanel; // size: 0x8, address: 0x80887EF0
struct {
    // total size: 0xC
} __vt__21InputStatusChangedMsg; // size: 0xC, address: 0x80887EF8
struct {
    // total size: 0x8
} __RTTI__21InputStatusChangedMsg; // size: 0x8, address: 0x80887F28

