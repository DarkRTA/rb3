/*
    Compile unit: C:\rockband2\band2\src\meta\BandUI.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800BD874 -> 0x800C172C
*/
class Symbol t; // size: 0x4, address: 0x80A4A7C4
class Symbol t; // size: 0x4, address: 0x80A4A7CC
class Symbol t; // size: 0x4, address: 0x80A4A7D4
class Symbol t; // size: 0x4, address: 0x80A4A7DC
class Symbol t; // size: 0x4, address: 0x80A4A7E4
class Symbol t; // size: 0x4, address: 0x80A4A7EC
class BandUI * TheBandUI; // size: 0x4, address: 0x80A4A7F0
// Range: 0x800BD874 -> 0x800BDBB0
void * BandUI::BandUI(class BandUI * const this /* r30 */) {
    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> class Net TheNet;
    // -> class ObjectDir * sMainDir;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__6BandUI;
    // -> struct [anonymous] __vt__9MsgSource;
    // -> struct [anonymous] __vt__6UISink;
}

// Range: 0x800BDBB0 -> 0x800BDD08
void * BandUI::~BandUI(class BandUI * const this /* r30 */) {
    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> class Net TheNet;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__6BandUI;
}

// Range: 0x800BDD08 -> 0x800BDE50
static class UIPanel * FindPanel(const char * name /* r28 */) {
    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7UIPanel;
    // -> class ObjectDir * sMainDir;
}

// Range: 0x800BDE50 -> 0x800BDEDC
void BandUI::InitPanels(class BandUI * const this /* r30 */) {}

static class Timer * _t; // size: 0x4, address: 0x80A4A7F4
// Range: 0x800BDEDC -> 0x800BE1C0
void BandUI::Draw(class BandUI * const this /* r31 */) {
    // Local variables
    class AutoTimer _at; // r1+0xC
    int heightFrame; // r0

    // References
    // -> class NetworkBusyPanel * sInstance;
    // -> class HelpBarPanel * sInstance;
    // -> class UIManager TheUI;
    // -> static class Timer * _t;
}

static class Timer * _t; // size: 0x4, address: 0x80A4A7FC
static class Symbol is_faded_in; // size: 0x4, address: 0x80A4A804
static class Message msg; // size: 0x8, address: 0x80977E48
// Range: 0x800BE1C0 -> 0x800BE520
void BandUI::Poll(class BandUI * const this /* r31 */) {
    // Local variables
    class AutoTimer _at; // r1+0x14
    unsigned char bFadedIn; // r0

    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> static class Symbol is_faded_in;
    // -> class UIManager TheUI;
    // -> static class Timer * _t;
}

// Range: 0x800BE520 -> 0x800BE52C
void BandUI::HideEvent() {}

static class Message msg; // size: 0x8, address: 0x80977E60
// Range: 0x800BE52C -> 0x800BE710
unsigned char BandUI::ShowEvent() {
    // Local variables
    class DataNode n; // r1+0x20

    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class UIManager TheUI;
}

// Range: 0x800BE710 -> 0x800BE718
unsigned char BandUI::IsBlockingTransition() {
    // References
    // -> class NetSync * TheNetSync;
}

static class Message init; // size: 0x8, address: 0x80977E78
static class Symbol data_error; // size: 0x4, address: 0x80A4A80C
// Range: 0x800BE718 -> 0x800BEA10
class DataNode BandUI::OnContentFileReadFailed(class BandUI * const this /* r29 */, class DataArray * msg /* r30 */) {
    // Local variables
    unsigned char corrupt; // r0

    // References
    // -> static class Symbol data_error;
    // -> const char * gNullStr;
    // -> static class Message init;
    // -> struct [anonymous] __vt__7Message;
}

static class Symbol disband; // size: 0x4, address: 0x80A4A814
static class Message init; // size: 0x8, address: 0x80977E90
// Range: 0x800BEA10 -> 0x800BEDF8
class DataNode BandUI::OnMsg(class BandUI * const this /* r29 */, const class RemotePlayerLeftMsg & msg /* r30 */) {
    // Local variables
    unsigned char in_transition; // r0
    int leaderNum; // r25

    // References
    // -> class GameMode * TheGameMode;
    // -> static class Message init;
    // -> struct [anonymous] __vt__7Message;
    // -> static class Symbol disband;
    // -> class SessionMgr * TheSessionMgr;
    // -> class Net TheNet;
    // -> class NetSync * TheNetSync;
}

class BandEventDismissMsg : public Message {
    // total size: 0x8
};
static class BandEventDismissMsg dismiss_msg; // size: 0x8, address: 0x80977EA8
static class Message msg; // size: 0x8, address: 0x80977EC0
static class DataArrayPtr are_all_mics_connected; // size: 0x8, address: 0x80977ED8
static class Message on_mics_ok; // size: 0x8, address: 0x80977EF0
static class Symbol mic_lost; // size: 0x4, address: 0x80A4A820
static class Message on_controllers_ok; // size: 0x8, address: 0x80977F08
// Range: 0x800BEDF8 -> 0x800BF400
void BandUI::DismissEvent(class BandUI * const this /* r28 */) {
    // References
    // -> static class Message on_controllers_ok;
    // -> class InputMgr * TheInputMgr;
    // -> static class Symbol mic_lost;
    // -> static class Message on_mics_ok;
    // -> static class DataArrayPtr are_all_mics_connected;
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> class Game * TheGame;
    // -> class UIManager TheUI;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__19BandEventDismissMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class BandEventDismissMsg dismiss_msg;
}

static class Message msg; // size: 0x8, address: 0x80977F20
static class Symbol allow_override; // size: 0x4, address: 0x80A4A828
static class Symbol events; // size: 0x4, address: 0x80A4A830
static class Message init_msg; // size: 0x8, address: 0x80977F38
class BandEventStartMsg : public Message {
    // total size: 0x8
};
static class BandEventStartMsg msg; // size: 0x8, address: 0x80977F50
// Range: 0x800BF400 -> 0x800BFA90
void BandUI::TriggerEvent(class BandUI * const this /* r26 */, class Symbol & event /* r27 */, class DataArray * custom_init /* r28 */) {
    // Local variables
    class UIScreen * screen; // r29
    class DataNode n; // r1+0x78
    class DataArray * t; // r0

    // References
    // -> struct [anonymous] __vt__17BandEventStartMsg;
    // -> class Symbol t;
    // -> static class BandEventStartMsg msg;
    // -> static class Message init_msg;
    // -> static class Symbol events;
    // -> static class Symbol allow_override;
    // -> class NetSync * TheNetSync;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class UIManager TheUI;
}

// Range: 0x800BFA90 -> 0x800BFAA4
unsigned char BandUI::HasEvent() {}

// Range: 0x800BFAA4 -> 0x800BFB0C
class Symbol BandUI::CurrentEvent() {
    // References
    // -> const char * gNullStr;
}

// Range: 0x800BFB0C -> 0x800BFCA4
class DataNode BandUI::OnMsg(class BandUI * const this /* r28 */, const class UITransitionCompleteMsg & msg /* r29 */) {
    // Local variables
    const class DataNode * prop; // r0

    // References
    // -> class UIManager TheUI;
    // -> class HelpBarPanel * sInstance;
    // -> class PlatformMgr ThePlatformMgr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8UIScreen;
}

class VerifyBuildVersionMsg : public NetMessage {
    // total size: 0x10
    class String mVersion; // offset 0x4, size 0xC
};
// Range: 0x800BFCA4 -> 0x800BFD28
class DataNode BandUI::OnMsg() {
    // Local variables
    class VerifyBuildVersionMsg versionMsg; // r1+0x8

    // References
    // -> class NetSession * TheNetSession;
}

static class Message init; // size: 0x8, address: 0x80977F68
static class Symbol lost_connection; // size: 0x4, address: 0x80A4A838
// Range: 0x800BFD88 -> 0x800C00A4
class DataNode BandUI::OnMsg(class BandUI * const this /* r30 */) {
    // References
    // -> class RockCentralGateway RockCentral;
    // -> static class Symbol lost_connection;
    // -> class PlatformMgr ThePlatformMgr;
    // -> static class Message init;
    // -> struct [anonymous] __vt__7Message;
    // -> class GameMode * TheGameMode;
}

static class Symbol disk_error; // size: 0x4, address: 0x80A4A840
// Range: 0x800C00A4 -> 0x800C0184
class DataNode BandUI::OnMsg(class BandUI * const this /* r30 */) {
    // References
    // -> static class Symbol disk_error;
    // -> class GameMode * TheGameMode;
    // -> class Net TheNet;
}

static class Message init; // size: 0x8, address: 0x80977F80
static class Symbol invite_accepted; // size: 0x4, address: 0x80A4A848
// Range: 0x800C0184 -> 0x800C04C4
class DataNode BandUI::OnMsg(class BandUI * const this /* r30 */, const class InviteAcceptedMsg & msg /* r31 */) {
    // Local variables
    class Profile * profile; // r28

    // References
    // -> static class Symbol invite_accepted;
    // -> static class Message init;
    // -> struct [anonymous] __vt__7Message;
    // -> class ProfileMgr TheProfileMgr;
}

// Range: 0x800C04C4 -> 0x800C0570
class DataNode BandUI::OnTriggerEvent(class BandUI * const this /* r30 */, class DataArray * msg /* r31 */) {
    // Local variables
    class Symbol t; // r1+0x14
    class DataArray * init; // r5
}

static class Symbol error_abandoned; // size: 0x4, address: 0x80A4A850
// Range: 0x800C0570 -> 0x800C05C4
void BandUI::ResetDisband(class BandUI * const this /* r31 */) {
    // References
    // -> static class Symbol error_abandoned;
}

static class Symbol is_tour; // size: 0x4, address: 0x80A4A858
static class Symbol sign_out; // size: 0x4, address: 0x80A4A860
static class Message init; // size: 0x8, address: 0x80977F98
static class Symbol disband; // size: 0x4, address: 0x80A4A868
static class Message init; // size: 0x8, address: 0x80977FB0
// Range: 0x800C05C4 -> 0x800C0AA4
void BandUI::TriggerDisbandIfNecessary(unsigned char leaderLeft /* r29 */, unsigned char signout /* r27 */) {
    // Local variables
    unsigned char triggerDisband; // r28
    class TourBand * pBand; // r0

    // References
    // -> static class Message init;
    // -> static class Symbol disband;
    // -> class BandUI * TheBandUI;
    // -> static class Message init;
    // -> struct [anonymous] __vt__7Message;
    // -> static class Symbol sign_out;
    // -> class ProfileMgr TheProfileMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol is_tour;
    // -> class Tour * TheTour;
}

static class Symbol _s; // size: 0x4, address: 0x80A4A870
static class Symbol _s; // size: 0x4, address: 0x80A4A878
static class Symbol _s; // size: 0x4, address: 0x80A4A880
static class Symbol _s; // size: 0x4, address: 0x80A4A888
static class Symbol _s; // size: 0x4, address: 0x80A4A890
static class Symbol _s; // size: 0x4, address: 0x80A4A898
static class Symbol _s; // size: 0x4, address: 0x80A4A8A0
static class Symbol _s; // size: 0x4, address: 0x80A4A8A8
// Range: 0x800C0AA4 -> 0x800C1394
class DataNode BandUI::Handle(class BandUI * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x30
    class MessageTimer _mt; // r1+0xC0
    class DataNode r; // r1+0xB8
    class DataNode r; // r1+0xB0
    class DataNode r; // r1+0xA8
    class DataNode r; // r1+0xA0
    class DataNode r; // r1+0x98
    class DataNode r; // r1+0x90
    class DataNode r; // r1+0x88
    class DataNode r; // r1+0x80
    class DataNode _n; // r1+0x78
    class DataNode _n; // r1+0x70
    class DataNode _n; // r1+0x68

    // References
    // -> class DebugNotifier TheDebugNotifier;
    // -> class InputMgr * TheInputMgr;
    // -> class NetSync * TheNetSync;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

static class Symbol _s; // size: 0x4, address: 0x80A4A8B0
static class Symbol _s; // size: 0x4, address: 0x80A4A8B8
static class Symbol _s; // size: 0x4, address: 0x80A4A8C0
// Range: 0x800C1394 -> 0x800C172C
unsigned char BandUI::SyncProperty(class BandUI * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

struct {
    // total size: 0xC
} __vt__23ProcessedJoinRequestMsg; // size: 0xC, address: 0x8087FE98
struct {
    // total size: 0x8
} __RTTI__23ProcessedJoinRequestMsg; // size: 0x8, address: 0x8087FED0
struct {
    // total size: 0x84
} __vt__6BandUI; // size: 0x84, address: 0x8087FED8
struct {
    // total size: 0x8
} __RTTI__6BandUI; // size: 0x8, address: 0x8087FF88
struct {
    // total size: 0xC
} __vt__19BandEventDismissMsg; // size: 0xC, address: 0x8087FF90
struct {
    // total size: 0x8
} __RTTI__19BandEventDismissMsg; // size: 0x8, address: 0x8087FFC0
struct {
    // total size: 0xC
} __vt__17BandEventStartMsg; // size: 0xC, address: 0x8087FFC8
struct {
    // total size: 0x8
} __RTTI__17BandEventStartMsg; // size: 0x8, address: 0x8087FFF8
struct {
    // total size: 0xC
} __vt__26ConnectionStatusChangedMsg; // size: 0xC, address: 0x80880000
struct {
    // total size: 0x8
} __RTTI__26ConnectionStatusChangedMsg; // size: 0x8, address: 0x80880038
struct {
    // total size: 0xC
} __vt__17InviteAcceptedMsg; // size: 0xC, address: 0x80880040
struct {
    // total size: 0x8
} __RTTI__17InviteAcceptedMsg; // size: 0x8, address: 0x80880070
struct {
    // total size: 0xC
} __vt__12DiskErrorMsg; // size: 0xC, address: 0x80880078
struct {
    // total size: 0x8
} __RTTI__12DiskErrorMsg; // size: 0x8, address: 0x808800A0
struct {
    // total size: 0x64
} __vt__6UISink; // size: 0x64, address: 0x808800A8
struct {
    // total size: 0x8
} __RTTI__6UISink; // size: 0x8, address: 0x80880128
class NetworkBusyPanel : public UIPanel {
    // total size: 0xA8
    unsigned char mBusy; // offset 0x30, size 0x1
    class Timer mTimer; // offset 0x38, size 0x38
    int mMinDuration; // offset 0x70, size 0x4
    class RndGroup * mHeightGroup; // offset 0x74, size 0x4
};
class HelpBarWidget {
    // total size: 0x48
protected:
    class RndGroup * mGroup; // offset 0x0, size 0x4
    class UILabel * mText; // offset 0x4, size 0x4
    class UILabel * mIcons[3]; // offset 0x8, size 0xC
    class RndAnimatable * mInAnim; // offset 0x14, size 0x4
    class RndAnimatable * mUpdateAnim; // offset 0x18, size 0x4
    int mDesInFrame; // offset 0x1C, size 0x4
    int mCurInFrame; // offset 0x20, size 0x4
    int mDesUpFrame; // offset 0x24, size 0x4
    int mCurUpFrame; // offset 0x28, size 0x4
    unsigned char mShowing; // offset 0x2C, size 0x1
    class Symbol mCachedText; // offset 0x30, size 0x4
    class Symbol mCachedAlt; // offset 0x34, size 0x4
    class Symbol mUpdateText; // offset 0x38, size 0x4
    class Symbol mAltText; // offset 0x3C, size 0x4
    int mAltCountdown; // offset 0x40, size 0x4
    unsigned char mHasIcons; // offset 0x44, size 0x1
};
class InputStatusChangedMsg : public Message {
    // total size: 0x8
};
enum WidgetId {
    kHBPCancel = 0,
    kHBPStateConfirm = 1,
    kHBPConfirm = 2,
    kHBPFirstFatBarWidget = 3,
    kHBPViewModify = 3,
    kHBPOption = 4,
    kHBPOption1 = 5,
    kHBPOption2 = 6,
    kHBPFirstNonBarWidget = 7,
    kHBPWaiting = 7,
    kHBPStart = 8,
    kHBPNumWidgets = 9,
    kHBPMinHeight = 9,
    kHBPNoDrum = 10,
    kHBPNoVocal = 11,
    kHBPNoGuitar = 12,
};
class HelpBarPanel : public UIPanel {
    // total size: 0x34C
public:
    unsigned char mConfigWasSet; // offset 0x30, size 0x1
private:
    class HelpBarWidget mWidgets[9]; // offset 0x34, size 0x288
    float mWidgetXPos[9]; // offset 0x2BC, size 0x24
    class RndGroup * mHeightGroup; // offset 0x2E0, size 0x4
    int mDesiredHeightFrame; // offset 0x2E4, size 0x4
    int mHeightFrame; // offset 0x2E8, size 0x4
    unsigned char mConsiderHeight; // offset 0x2EC, size 0x1
    unsigned char mUpdateIcons; // offset 0x2ED, size 0x1
    int mMinHeight; // offset 0x2F0, size 0x4
    unsigned char mFirstUsed; // offset 0x2F4, size 0x1
    float mDesPanelAlpha; // offset 0x2F8, size 0x4
    float mCurPanelAlpha; // offset 0x2FC, size 0x4
    class RndAnimatable * mPanelAlphaAnim; // offset 0x300, size 0x4
    unsigned char mAllowDrumIcon; // offset 0x304, size 0x1
    unsigned char mAllowVocalIcon; // offset 0x305, size 0x1
    unsigned char mAllowGuitarIcon; // offset 0x306, size 0x1
    int mGuitarIconWidth; // offset 0x308, size 0x4
    int mDrumIconWidth; // offset 0x30C, size 0x4
    int mVocalIconWidth; // offset 0x310, size 0x4
    int mStartIconWidth; // offset 0x314, size 0x4
    int mOptionIconWidth; // offset 0x318, size 0x4
    int mLabelSpace; // offset 0x31C, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class NetSearchResult * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class NetSearchResult * * _M_start; // offset 0x0, size 0x4
    class NetSearchResult * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class SessionSearcher : public MsgSource {
    // total size: 0x60
protected:
    class NetSearchResult * mLastInviteResult; // offset 0x1C, size 0x4
private:
    unsigned char mSearching; // offset 0x20, size 0x1
    class vector mSearchList; // offset 0x24, size 0xC
    int mNextResult; // offset 0x30, size 0x4
};

