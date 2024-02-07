/*
    Compile unit: C:\rockband2\band2\src\meta\NetSync.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x801265FC -> 0x8012AC54
*/
class NetPushScreenMsg : public StartTransitionMsg {
    // total size: 0x10
};
class NetPopScreenMsg : public StartTransitionMsg {
    // total size: 0x10
};
class NetResetScreenMsg : public StartTransitionMsg {
    // total size: 0x10
};
class NetForceResetScreenMsg : public StartTransitionMsg {
    // total size: 0x10
};
class NetSync * TheNetSync; // size: 0x4, address: 0x80A4BBA0
// Range: 0x801265FC -> 0x80126840
static void RegisterNetMessages() {
    // References
    // -> class NetMessageFactory TheNetMessageFactory;
}

// Range: 0x80126840 -> 0x801268D0
void NetSync::Init() {
    // References
    // -> class ObjectDir * sMainDir;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class NetSync * TheNetSync;
}

// Range: 0x801268D0 -> 0x80126950
void NetSync::Terminate() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class NetSync * TheNetSync;
}

static class Symbol session_disabled; // size: 0x4, address: 0x80A4BBA8
static class Symbol session_busy; // size: 0x4, address: 0x80A4BBB0
// Range: 0x80126950 -> 0x80126AA0
void * NetSync::NetSync(class NetSync * const this /* r31 */) {
    // Local variables
    int i; // r5

    // References
    // -> static class Symbol session_busy;
    // -> class Net TheNet;
    // -> const char * gNullStr;
    // -> static class Symbol session_disabled;
    // -> struct [anonymous] __vt__7NetSync;
}

// Range: 0x80126AA0 -> 0x80126B54
void * NetSync::~NetSync(class NetSync * const this /* r30 */) {
    // References
    // -> class Net TheNet;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__7NetSync;
}

// Range: 0x80126B54 -> 0x80126B5C
unsigned char NetSync::IsForcedTransitionActive() {}

// Range: 0x80126B5C -> 0x80126B94
unsigned char NetSync::IsBlockingTransition() {
    // Local variables
    int i; // r5
}

static class Message msg; // size: 0x8, address: 0x80979188
static class Message msg; // size: 0x8, address: 0x809791A0
class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class UIPanel * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x80126B94 -> 0x80127498
unsigned char NetSync::IsBlockingEvent(class Symbol & event /* r30 */) {
    // Local variables
    class DataNode ret; // r1+0x80
    class ObjDirItr p; // r1+0x88
    class DataNode ret; // r1+0x78

    // References
    // -> static class Message msg;
    // -> class UIManager TheUI;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7UIPanel;
    // -> class ObjectDir * sMainDir;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> const char * gNullStr;
}

// Range: 0x80127498 -> 0x801274C8
unsigned char NetSync::IsEnabled() {}

// Range: 0x801274C8 -> 0x80127594
enum NetUIState NetSync::GetUIState() {
    // Local variables
    class vector & users; // r0
    class BandUser * * it; // r28
    class BandUser * pUser; // r27

    // References
    // -> class Net TheNet;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x80127594 -> 0x80127664
unsigned char NetSync::AllUsersReady() {
    // Local variables
    class vector & users; // r0
    class BandUser * * it; // r30
    class BandUser * pUser; // r29
    enum NetUIState state; // r0

    // References
    // -> class NetSession * TheNetSession;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x80127664 -> 0x80127678
unsigned char NetSync::HasDestinationScreen() {}

// Range: 0x80127678 -> 0x801277CC
void NetSync::Poll(class NetSync * const this /* r27 */) {
    // Local variables
    class vector & users; // r0
    class BandUser * * it; // r28
    class BandUser * pUser; // r29

    // References
    // -> class Net TheNet;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class UIManager TheUI;
}

static class Symbol max_block_mode; // size: 0x4, address: 0x80A4BBB8
// Range: 0x801277CC -> 0x80127A14
unsigned char NetSync::AttemptTransition(class NetSync * const this /* r31 */, class UIScreen * destination /* r26 */, int destination_depth /* r27 */) {
    // References
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7UIPanel;
    // -> class ObjectDir * sMainDir;
    // -> class RockCentralGateway RockCentral;
    // -> class BandUI * TheBandUI;
    // -> class UIManager TheUI;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol max_block_mode;
}

// Range: 0x80127A14 -> 0x80127A1C
void NetSync::Enable() {}

// Range: 0x80127A1C -> 0x80127A24
void NetSync::Disable() {}

// Range: 0x80127A24 -> 0x80127AF8
void NetSync::SetUIState(enum NetUIState s /* r26 */) {
    // Local variables
    class vector & users; // r0
    class BandUser * * it; // r28
    class BandUser * pUser; // r27

    // References
    // -> class InputMgr * TheInputMgr;
    // -> class Net TheNet;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x80127AF8 -> 0x80127B90
void NetSync::SetWaiting(class NetSync * const this /* r29 */, int player /* r30 */, enum WaitType w /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80127B90 -> 0x80127C4C
void NetSync::SendNetFocus(class NetSync * const this /* r29 */, int player /* r30 */, class UIComponent * c /* r31 */) {
    // Local variables
    class ComponentFocusNetMsg msg; // r1+0x8

    // References
    // -> class Net TheNet;
    // -> class NetSession * TheNetSession;
}

// Range: 0x80127C4C -> 0x80127D94
void NetSync::StartNetWaiting(class NetSync * const this /* r26 */, enum WaitType w /* r27 */, unsigned char waitForAll /* r28 */) {
    // Local variables
    class vector & users; // r0
    class BandUser * * it; // r29
    class BandUser * pUser; // r25

    // References
    // -> class Net TheNet;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80127D94 -> 0x8012808C
void NetSync::SendNetTransitionComplete(class NetSync * const this /* r27 */) {
    // Local variables
    class vector localPlayers; // r1+0x50
    class vector & users; // r0
    class BandUser * * it; // r28
    class BandUser * pUser; // r29
    int i; // r1+0x2C
    int leaderNum; // r31
    class AllTransitionCompleteMsg msg; // r1+0x28
    class LocalTransitionCompleteMsg msg; // r1+0x40

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__Pi;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __vt__24AllTransitionCompleteMsg;
    // -> class SessionMgr * TheSessionMgr;
    // -> class Net TheNet;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x801280CC -> 0x80128124
void NetSync::CheckNetAllComplete() {
    // Local variables
    class AllTransitionCompleteMsg msg; // r1+0x8

    // References
    // -> class UIManager TheUI;
    // -> class Net TheNet;
    // -> struct [anonymous] __vt__24AllTransitionCompleteMsg;
}

// Range: 0x80128124 -> 0x801281C8
void NetSync::SyncScreen(class NetSync * const this /* r29 */, class DataArray * a /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8UIScreen;
}

// Range: 0x801281C8 -> 0x80128238
void NetSync::ForceResetScreen(class DataArray * a /* r31 */) {
    // References
    // -> class UIManager TheUI;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8UIScreen;
}

// Range: 0x80128238 -> 0x801282B8
unsigned char NetSync::DisableAndGoto(class NetSync * const this /* r30 */, class UIScreen * destination /* r31 */) {
    // Local variables
    int i; // r6
}

static class Symbol sync_screen; // size: 0x4, address: 0x80A4BBC0
static class Symbol force_reset_screen; // size: 0x4, address: 0x80A4BBC8
static class Symbol ui; // size: 0x4, address: 0x80A4BBD0
static class Symbol goto_screen; // size: 0x4, address: 0x80A4BBD8
static class Symbol push_screen; // size: 0x4, address: 0x80A4BBE0
static class Symbol pop_screen; // size: 0x4, address: 0x80A4BBE8
static class Symbol reset_screen; // size: 0x4, address: 0x80A4BBF0
static class Symbol force_reset_screen; // size: 0x4, address: 0x80A4BBF8
// Range: 0x801282B8 -> 0x80128A88
class DataNode NetSync::OnTransition(class NetSync * const this /* r27 */, class DataArray * msg /* r28 */) {
    // Local variables
    unsigned char blocking_event; // r0
    class Symbol type; // r1+0x18
    const class DataNode & n; // r0
    int leader; // r25
    enum WaitType t; // r29
    unsigned char force; // r31
    unsigned char back; // r24
    class NetGotoScreenMsg gotoScreen; // r1+0x7C
    class NetPushScreenMsg pushScreen; // r1+0x58
    class UIScreen * screen; // r24
    class NetPopScreenMsg popScreen; // r1+0x48
    class NetResetScreenMsg resetScreen; // r1+0x38
    class NetForceResetScreenMsg forceScreen; // r1+0x28
    class NetSyncScreenMsg syncScreen; // r1+0x68

    // References
    // -> struct [anonymous] __vt__22NetForceResetScreenMsg;
    // -> struct [anonymous] __vt__17NetResetScreenMsg;
    // -> struct [anonymous] __vt__15NetPopScreenMsg;
    // -> struct [anonymous] __vt__16NetPushScreenMsg;
    // -> static class Symbol force_reset_screen;
    // -> static class Symbol reset_screen;
    // -> static class Symbol pop_screen;
    // -> static class Symbol push_screen;
    // -> static class Symbol goto_screen;
    // -> static class Symbol ui;
    // -> class UIManager TheUI;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Net TheNet;
    // -> class SessionMgr * TheSessionMgr;
    // -> static class Symbol force_reset_screen;
    // -> static class Symbol sync_screen;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8UIScreen;
    // -> class BandUI * TheBandUI;
}

// Range: 0x80128A88 -> 0x80128AD0
void NetSync::SendTransitionMsg(class NetTransitionMsg & msg /* r31 */) {
    // References
    // -> class Net TheNet;
    // -> class SyncStore * TheSyncStore;
}

// Range: 0x80128AD0 -> 0x80128BF0
class DataNode NetSync::OnMsg(class NetSync * const this /* r27 */) {
    // Local variables
    class vector & users; // r0
    class BandUser * * it; // r28
    class BandUser * pUser; // r29

    // References
    // -> class Net TheNet;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x80128BF0 -> 0x80128D38
class DataNode NetSync::OnMsg(class NetSync * const this /* r28 */, const class UIComponentFocusChangeMsg & msg /* r29 */) {
    // Local variables
    class MultiFocusScreen * screen; // r0
    int leaderNum; // r30

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11UIComponent;
    // -> class Net TheNet;
    // -> class SessionMgr * TheSessionMgr;
    // -> struct [anonymous] __RTTI__8UIScreen;
    // -> struct [anonymous] __RTTI__16MultiFocusScreen;
    // -> class UIManager TheUI;
    // -> class BandUI * TheBandUI;
}

// Range: 0x80128D38 -> 0x80128ED0
class DataNode NetSync::OnMsg(class NetSync * const this /* r26 */, const class UIComponentSelectMsg & msg /* r25 */) {
    // Local variables
    class ComponentSelectNetMsg selectMsg; // r1+0x10

    // References
    // -> class Net TheNet;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11UIComponent;
    // -> class UIManager TheUI;
    // -> class BandUI * TheBandUI;
}

static class Message msg; // size: 0x8, address: 0x809791B8
// Range: 0x80128ED0 -> 0x801291EC
class DataNode NetSync::OnMsg(const class UIComponentScrollMsg & msg /* r31 */) {
    // Local variables
    class DataNode n; // r1+0x20
    class ComponentScrollNetMsg remoteScroll; // r1+0x28

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11UIComponent;
    // -> class Net TheNet;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class UIManager TheUI;
}

// Range: 0x801291EC -> 0x80129320
class DataNode NetSync::OnMsg(class NetSync * const this /* r28 */) {
    // Local variables
    class vector players; // r1+0xC
    int n; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80129320 -> 0x801293EC
class DataNode NetSync::OnMsg(class NetSync * const this /* r31 */) {
    // Local variables
    int leaderNum; // r4
    int i; // r5

    // References
    // -> class UIManager TheUI;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Net TheNet;
    // -> class SessionMgr * TheSessionMgr;
}

// Range: 0x801293EC -> 0x80129724
void NetSync::HandleNetTransitionMsg(class NetSync * const this /* r31 */, class NetTransitionMsg * msg /* r25 */) {
    // Local variables
    int byteCode; // r26
    class StartTransitionMsg * transitionMsg; // r26
    int leader; // r4
    enum WaitType t; // r26

    // References
    // -> class Net TheNet;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class SessionMgr * TheSessionMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__18StartTransitionMsg;
    // -> struct [anonymous] __RTTI__24AllTransitionCompleteMsg;
    // -> struct [anonymous] __RTTI__16NetTransitionMsg;
    // -> struct [anonymous] __RTTI__26LocalTransitionCompleteMsg;
    // -> class NetMessageFactory TheNetMessageFactory;
}

static class Symbol reset_screen; // size: 0x4, address: 0x80A4BC00
static class Message resetScreen; // size: 0x8, address: 0x809791D0
static class Symbol sync_screen; // size: 0x4, address: 0x80A4BC08
static class Message syncScreen; // size: 0x8, address: 0x809791E8
// Range: 0x80129724 -> 0x80129EA4
enum WaitType NetSync::StartNetTransition(class NetSync * const this /* r25 */, class StartTransitionMsg * msg /* r26 */) {
    // Local variables
    enum WaitType t; // r27
    class NetGotoScreenMsg * gotoMsg; // r0
    class UIScreen * s; // r24
    class NetSyncScreenMsg * syncMsg; // r30

    // References
    // -> static class Message syncScreen;
    // -> static class Symbol sync_screen;
    // -> struct [anonymous] __RTTI__16NetSyncScreenMsg;
    // -> static class Message resetScreen;
    // -> struct [anonymous] __vt__7Message;
    // -> static class Symbol reset_screen;
    // -> class UIManager TheUI;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__18StartTransitionMsg;
    // -> struct [anonymous] __RTTI__16NetGotoScreenMsg;
    // -> class NetMessageFactory TheNetMessageFactory;
}

// Range: 0x80129EA4 -> 0x80129EDC
class DataNode NetSync::OnSessionDisabled() {
    // Local variables
    int i; // r7
}

// Range: 0x80129EDC -> 0x80129EFC
class DataNode NetSync::OnMsg() {
    // References
    // -> class NetSession * TheNetSession;
}

static class Symbol _s; // size: 0x4, address: 0x80A4BC10
static class Symbol _s; // size: 0x4, address: 0x80A4BC18
static class Symbol _s; // size: 0x4, address: 0x80A4BC20
static class Symbol _s; // size: 0x4, address: 0x80A4BC28
static class Symbol _s; // size: 0x4, address: 0x80A4BC30
static class Symbol _s; // size: 0x4, address: 0x80A4BC38
static class Symbol _s; // size: 0x4, address: 0x80A4BC40
static class Symbol _s; // size: 0x4, address: 0x80A4BC48
static class Symbol _s; // size: 0x4, address: 0x80A4BC50
static class Symbol _s; // size: 0x4, address: 0x80A4BC58
static class Symbol _s; // size: 0x4, address: 0x80A4BC60
static class Symbol _s; // size: 0x4, address: 0x80A4BC68
static class Symbol _s; // size: 0x4, address: 0x80A4BC70
static class Symbol _s; // size: 0x4, address: 0x80A4BC78
static class Symbol _s; // size: 0x4, address: 0x80A4BC80
static class Symbol _s; // size: 0x4, address: 0x80A4BC88
static class Symbol _s; // size: 0x4, address: 0x80A4BC90
// Range: 0x80129EFC -> 0x8012AAC8
class DataNode NetSync::Handle(class NetSync * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0xC0
    class DataNode r; // r1+0xB8
    class DataNode r; // r1+0xB0
    class DataNode r; // r1+0xA8
    class DataNode r; // r1+0xA0
    class DataNode r; // r1+0x98
    class DataNode r; // r1+0x90
    class DataNode r; // r1+0x88
    class DataNode r; // r1+0x80
    class DataNode r; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode r; // r1+0x68
    class DataNode r; // r1+0x60
    class DataNode _n; // r1+0x58

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

static class Symbol _s; // size: 0x4, address: 0x80A4BC98
// Range: 0x8012AAC8 -> 0x8012AC54
unsigned char NetSync::SyncProperty(class NetSync * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x28
} __vt__22NetForceResetScreenMsg; // size: 0x28, address: 0x8088F400
struct {
    // total size: 0x8
} __RTTI__22NetForceResetScreenMsg; // size: 0x8, address: 0x8088F460
struct {
    // total size: 0x28
} __vt__17NetResetScreenMsg; // size: 0x28, address: 0x8088F468
struct {
    // total size: 0x8
} __RTTI__17NetResetScreenMsg; // size: 0x8, address: 0x8088F4C0
struct {
    // total size: 0x28
} __vt__15NetPopScreenMsg; // size: 0x28, address: 0x8088F4C8
struct {
    // total size: 0x8
} __RTTI__15NetPopScreenMsg; // size: 0x8, address: 0x8088F520
struct {
    // total size: 0x28
} __vt__16NetPushScreenMsg; // size: 0x28, address: 0x8088F528
struct {
    // total size: 0x8
} __RTTI__16NetPushScreenMsg; // size: 0x8, address: 0x8088F580
struct {
    // total size: 0x28
} __vt__24AllTransitionCompleteMsg; // size: 0x28, address: 0x8088F5F0
struct {
    // total size: 0x8
} __RTTI__24AllTransitionCompleteMsg; // size: 0x8, address: 0x8088F648
struct {
    // total size: 0x54
} __vt__7NetSync; // size: 0x54, address: 0x8088F7D0
struct {
    // total size: 0x8
} __RTTI__7NetSync; // size: 0x8, address: 0x8088F848

