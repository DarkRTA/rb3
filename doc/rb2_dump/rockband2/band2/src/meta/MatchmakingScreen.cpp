/*
    Compile unit: C:\rockband2\band2\src\meta\MatchmakingScreen.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80104C04 -> 0x8010AF7C
*/
class DataArray * types; // size: 0x4, address: 0x80A4B3B0
class Symbol name; // size: 0x4, address: 0x80A4B3B8
class Symbol t; // size: 0x4, address: 0x80A4B3C0
class Symbol t; // size: 0x4, address: 0x80A4B3C8
class Symbol t; // size: 0x4, address: 0x80A4B3D0
class MatchmakingScreen : public AutoloadScreen {
    // total size: 0x70
    class DataArray * mOptions; // offset 0x4C, size 0x4
    class vector mSlots; // offset 0x50, size 0xC
    class vector mAutoJoinPadNums; // offset 0x5C, size 0xC
    int mAutoJoinSlotNum; // offset 0x68, size 0x4
    unsigned char mTriggerAutoJoinFailMsg; // offset 0x6C, size 0x1
    unsigned char mPendingAbandonSession; // offset 0x6D, size 0x1
};
// Range: 0x80104C04 -> 0x80104C6C
void * MatchmakingScreen::MatchmakingScreen(class MatchmakingScreen * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__17MatchmakingScreen;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class MatchmakingSlot * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class MatchmakingSlot * * _M_start; // offset 0x0, size 0x4
    class MatchmakingSlot * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x80104C6C -> 0x80104D4C
void * MatchmakingScreen::~MatchmakingScreen(class MatchmakingScreen * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__17MatchmakingScreen;
}

static class Message ready; // size: 0x8, address: 0x80978CA8
static class Symbol is_tour; // size: 0x4, address: 0x80A4B3D8
struct FakeBandUser {
    // total size: 0x14
    class BandUser * mUser; // offset 0x0, size 0x4
    int mPadNum; // offset 0x4, size 0x4
    class String mStrName; // offset 0x8, size 0xC
};
enum JoinState {
    kMetaJoinNeedsOnline = 0,
    kMetaJoinGuestNotFirst = 1,
    kMetaJoinOK = 2,
};
struct UserJoinEntry {
    // total size: 0x18
    struct FakeBandUser mUser; // offset 0x0, size 0x14
    enum JoinState mState; // offset 0x14, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct UserJoinEntry * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct UserJoinEntry * _M_start; // offset 0x0, size 0x4
    struct UserJoinEntry * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct FakeBandUser * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct FakeBandUser * _M_start; // offset 0x0, size 0x4
    struct FakeBandUser * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class MatchmakingSlot : public Object {
    // total size: 0x100
    class Symbol mSymOption; // offset 0x28, size 0x4
    class MatchmakingScreen * mMMScreen; // offset 0x2C, size 0x4
    int mSlotNum; // offset 0x30, size 0x4
    class PanelDir * mPanelDir; // offset 0x34, size 0x4
    class CharProvider mCharProvider; // offset 0x38, size 0x54
    unsigned char mSendFocusMsg; // offset 0x8C, size 0x1
    class UserNameProvider * mUserNameProvider; // offset 0x90, size 0x4
    class vector mUserJoinList; // offset 0x94, size 0xC
    unsigned char mAllowedActions[16]; // offset 0xA0, size 0x10
    class CharData * mPrevChar; // offset 0xB0, size 0x4
    unsigned char mHasChars; // offset 0xB4, size 0x1
    int mLastButtonPadNum; // offset 0xB8, size 0x4
    int mLastButtonUserNum; // offset 0xBC, size 0x4
    enum JoypadButton mLastButtonRawButton; // offset 0xC0, size 0x4
    enum JoypadAction mLastButtonAction; // offset 0xC4, size 0x4
    class RndGroup * mSingleInstGrp; // offset 0xC8, size 0x4
    class RndGroup * mMultiInstGrp; // offset 0xCC, size 0x4
    class RndGroup * mTopGrp; // offset 0xD0, size 0x4
    class RndGroup * mBottomGrp; // offset 0xD4, size 0x4
    class RndGroup * mRemoteOnlyGrp; // offset 0xD8, size 0x4
    class RndGroup * mNoInstGrp; // offset 0xDC, size 0x4
    class RndGroup * mUserNameGrp; // offset 0xE0, size 0x4
    class RndGroup * mSignInGrp; // offset 0xE4, size 0x4
    class RndGroup * mGuestNotFirstGrp; // offset 0xE8, size 0x4
    class RndGroup * mJoinGrp; // offset 0xEC, size 0x4
    class RndGroup * mUserNameJoinedGrp; // offset 0xF0, size 0x4
    class RndGroup * mBottomChoosePartGrp; // offset 0xF4, size 0x4
    class RndGroup * mBottomChooseCharGrp; // offset 0xF8, size 0x4
    class RndGroup * mFindingGrp; // offset 0xFC, size 0x4
};
// Range: 0x80104D4C -> 0x80105088
unsigned char MatchmakingScreen::IsEveryoneReady(class MatchmakingScreen * const this /* r30 */) {
    // Local variables
    class MatchmakingSlot * * it; // r28
    class MatchmakingSlot * pSlot; // r29
    class DataNode n; // r1+0x28

    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Tour * TheTour;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol is_tour;
    // -> static class Message ready;
    // -> struct [anonymous] __vt__7Message;
}

static class Message msgIsReady; // size: 0x8, address: 0x80978CC0
static class Symbol ready; // size: 0x4, address: 0x80A4B3E0
// Range: 0x80105088 -> 0x8010527C
unsigned char MatchmakingScreen::IsEveryLocalSlotReady(class MatchmakingScreen * const this /* r30 */) {
    // Local variables
    class MatchmakingSlot * * it; // r27
    class MatchmakingSlot * pSlot; // r26
    int slotNum; // r0
    class BandUser * pUser; // r0

    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol ready;
    // -> static class Message msgIsReady;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x8010527C -> 0x80105288
unsigned char MatchmakingScreen::IsSessionBusy() {
    // References
    // -> class NetSession * TheNetSession;
}

// Range: 0x80105288 -> 0x80105294
unsigned char MatchmakingScreen::IsSearching() {
    // References
    // -> class SessionMgr * TheSessionMgr;
}

static class Symbol is_h2h_arrangement; // size: 0x4, address: 0x80A4B3E8
// Range: 0x80105294 -> 0x80105344
unsigned char MatchmakingScreen::IsFull() {
    // Local variables
    unsigned char isH2h; // r0
    int userCount; // r0

    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol is_h2h_arrangement;
}

// Range: 0x80105344 -> 0x801053F4
class MatchmakingSlot * MatchmakingScreen::GetSlotObj(class MatchmakingScreen * const this /* r28 */, int slotNum /* r29 */) {
    // Local variables
    class MatchmakingSlot * * it; // r31
    class MatchmakingSlot * pSlot; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Message msg; // size: 0x8, address: 0x80978CD8
static class Symbol back; // size: 0x4, address: 0x80A4B3F0
// Range: 0x801053F4 -> 0x8010561C
void MatchmakingScreen::GoBack(class MatchmakingScreen * const this /* r31 */) {
    // Local variables
    class vector users; // r1+0x28

    // References
    // -> class UIManager TheUI;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8UIScreen;
    // -> static class Symbol back;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class BandUserMgr * TheBandUserMgr;
}

static class Symbol is_h2h_arrangement; // size: 0x4, address: 0x80A4B3F8
static class Symbol slot; // size: 0x4, address: 0x80A4B400
// Range: 0x8010561C -> 0x801057B0
void MatchmakingScreen::UpdateH2hSlotNames(class MatchmakingScreen * const this /* r30 */, enum ControllerType ct /* r28 */) {
    // Local variables
    unsigned char isH2h; // r0
    class Symbol symCt; // r1+0x18
    class MatchmakingSlot * * it; // r29
    class MatchmakingSlot * pSlot; // r28

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol slot;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol is_h2h_arrangement;
}

static class Symbol update; // size: 0x4, address: 0x80A4B408
static class Message msgUpdate; // size: 0x8, address: 0x80978CF0
// Range: 0x801057B0 -> 0x80105974
void MatchmakingScreen::UpdateAll(class MatchmakingScreen * const this /* r31 */) {
    // Local variables
    class MatchmakingSlot * * it; // r30

    // References
    // -> static class Message msgUpdate;
    // -> struct [anonymous] __vt__7Message;
    // -> class SessionMgr * TheSessionMgr;
    // -> static class Symbol update;
}

static class Symbol update; // size: 0x4, address: 0x80A4B410
// Range: 0x80105974 -> 0x80105AC8
void MatchmakingScreen::ExportAll(class MatchmakingScreen * const this /* r27 */, const class Message & msg /* r28 */) {
    // Local variables
    class MatchmakingSlot * * it; // r30
    class MatchmakingSlot * pSlot; // r29

    // References
    // -> const char * gNullStr;
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
    // -> static class Symbol update;
}

static class Symbol slot; // size: 0x4, address: 0x80A4B418
static class Symbol is_tour; // size: 0x4, address: 0x80A4B420
static class Symbol cancel; // size: 0x4, address: 0x80A4B428
static class Symbol helpbar_back; // size: 0x4, address: 0x80A4B430
static class Symbol option1; // size: 0x4, address: 0x80A4B438
static class Symbol mm_hb_fmp_cancel; // size: 0x4, address: 0x80A4B440
static class Symbol mm_hb_fmp; // size: 0x4, address: 0x80A4B448
static class Symbol start; // size: 0x4, address: 0x80A4B450
static class Symbol matchmaking_pressstart; // size: 0x4, address: 0x80A4B458
static class Symbol option2; // size: 0x4, address: 0x80A4B460
static class Symbol mm_hb_net_options; // size: 0x4, address: 0x80A4B468
static class Symbol confirm; // size: 0x4, address: 0x80A4B470
static class Symbol helpbar_select; // size: 0x4, address: 0x80A4B478
static class Symbol no_guitar_icon; // size: 0x4, address: 0x80A4B480
static class Symbol no_drum_icon; // size: 0x4, address: 0x80A4B488
static class Symbol no_vocal_icon; // size: 0x4, address: 0x80A4B490
static class Symbol waiting; // size: 0x4, address: 0x80A4B498
static class Symbol helpbar_waiting_for; // size: 0x4, address: 0x80A4B4A0
// Range: 0x80105AC8 -> 0x80106E24
void MatchmakingScreen::UpdateHelpbar(class MatchmakingScreen * const this /* r18 */) {
    // Local variables
    class DataArrayPtr pDataHelpbar; // r1+0x188
    int i; // r28
    unsigned char hasCancel; // r27
    unsigned char hasConfirm; // r26
    unsigned char hasStart; // r25
    unsigned char hasOption1; // r24
    unsigned char hasOption2; // r23
    unsigned char hasGuitar; // r22
    unsigned char hasDrum; // r21
    unsigned char hasVocals; // r20
    unsigned char isEveryoneReady; // r0
    class MatchmakingSlot * * it; // r29
    class MatchmakingSlot * pSlot; // r19
    unsigned char anyButton; // r17
    enum ControllerType ctSlot; // r0
    unsigned char isLeaderLocal; // r19
    int leaderNum; // r0
    class BandUser * pUserLeader; // r0
    class BandUser * pUserLeader; // r17
    class Symbol waiting_for; // r1+0x5C

    // References
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12HelpBarPanel;
    // -> class ObjectDir * sMainDir;
    // -> static class Symbol helpbar_waiting_for;
    // -> static class Symbol waiting;
    // -> static class Symbol no_vocal_icon;
    // -> static class Symbol no_drum_icon;
    // -> static class Symbol no_guitar_icon;
    // -> static class Symbol helpbar_select;
    // -> static class Symbol confirm;
    // -> static class Symbol mm_hb_net_options;
    // -> static class Symbol option2;
    // -> static class Symbol matchmaking_pressstart;
    // -> static class Symbol start;
    // -> static class Symbol mm_hb_fmp;
    // -> static class Symbol mm_hb_fmp_cancel;
    // -> static class Symbol option1;
    // -> static class Symbol helpbar_back;
    // -> static class Symbol cancel;
    // -> class Tour * TheTour;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol is_tour;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class SessionMgr * TheSessionMgr;
    // -> static class Symbol slot;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> class UIManager TheUI;
}

// Range: 0x80106E24 -> 0x80106E8C
void MatchmakingScreen::SetTypeDef(class MatchmakingScreen * const this /* r30 */, class DataArray * data /* r31 */) {}

static class Symbol panel; // size: 0x4, address: 0x80A4B4A8
// Range: 0x80106E8C -> 0x80107368
void MatchmakingScreen::Enter(class MatchmakingScreen * const this /* r24 */, class UIScreen * from /* r25 */) {
    // Local variables
    class DataArray * pDataPanels; // r27
    class UIPanel * pPanelMain; // r0
    class DataArray * pDataType; // r28
    class DataArray * slots; // r27
    int numSlots; // r0
    int i; // r26
    const char * dir_name; // r21
    class MatchmakingSlot * pSlot; // r1+0x44

    // References
    // -> class BandUI * TheBandUI;
    // -> class InputMgr * TheInputMgr;
    // -> class SessionMgr * TheSessionMgr;
    // -> class NetSession * TheNetSession;
    // -> const char * gNullStr;
    // -> struct [anonymous] __RTTI__8PanelDir;
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7UIPanel;
    // -> class ObjectDir * sMainDir;
    // -> static class Symbol panel;
}

static class Message exit; // size: 0x8, address: 0x80978D08
static class Symbol matchmaking_pad_lost; // size: 0x4, address: 0x80A4B4B0
// Range: 0x80107368 -> 0x80107564
void MatchmakingScreen::Exit(class MatchmakingScreen * const this /* r30 */, class UIScreen * to /* r31 */) {
    // References
    // -> static class Symbol matchmaking_pad_lost;
    // -> class BandUI * TheBandUI;
    // -> static class Message exit;
    // -> struct [anonymous] __vt__7Message;
    // -> class SessionMgr * TheSessionMgr;
    // -> class NetSession * TheNetSession;
    // -> const char * gNullStr;
    // -> class InputMgr * TheInputMgr;
}

// Range: 0x80107564 -> 0x80107598
void MatchmakingScreen::UnloadPanels(class MatchmakingScreen * const this /* r31 */) {}

static class Message poll; // size: 0x8, address: 0x80978D20
// Range: 0x80107598 -> 0x801076A8
void MatchmakingScreen::Poll(class MatchmakingScreen * const this /* r31 */) {
    // References
    // -> static class Message poll;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x801076A8 -> 0x80107B44
class DataNode MatchmakingScreen::OnMsg(class MatchmakingScreen * const this /* r30 */, const class ButtonDownMsg & msg /* r31 */) {
    // Local variables
    class vector users; // r1+0x28
    int firstFreePadNum; // r25
    class ButtonDownMsg msgNew; // r1+0x20
    class BandUser * pUser; // r26
    unsigned char useExtendedOptions; // r28
    enum JoypadButton button; // r0
    int slotNum; // r4
    class MatchmakingSlot * pSlot; // r27
    enum JoypadButton option1; // r28
    enum JoypadButton option2; // r24
    class JoypadData * data; // r0
    class ButtonDownMsg msgExtended; // r1+0x18
    class ButtonDownMsg msgExtended; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__7Message;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class UIManager TheUI;
    // -> class BandUI * TheBandUI;
}

// Range: 0x80107B44 -> 0x80107BDC
class DataNode MatchmakingScreen::OnMsg(class MatchmakingScreen * const this /* r29 */, const class UIComponentScrollMsg & msg /* r30 */) {
    // References
    // -> class BandUI * TheBandUI;
}

// Range: 0x80107BDC -> 0x80107C74
class DataNode MatchmakingScreen::OnMsg(class MatchmakingScreen * const this /* r29 */, const class UIComponentSelectMsg & msg /* r30 */) {
    // References
    // -> class BandUI * TheBandUI;
}

// Range: 0x80107C74 -> 0x80107D0C
class DataNode MatchmakingScreen::OnMsg(class MatchmakingScreen * const this /* r29 */, const class UIComponentSelectDoneMsg & msg /* r30 */) {
    // References
    // -> class BandUI * TheBandUI;
}

// Range: 0x80107D0C -> 0x80107DD4
class DataNode MatchmakingScreen::OnMsg(class MatchmakingScreen * const this /* r29 */, const class UIComponentFocusChangeMsg & msg /* r30 */) {
    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8PanelDir;
    // -> class BandUI * TheBandUI;
}

// Range: 0x80107DD4 -> 0x80107EF8
class DataNode MatchmakingScreen::OnMsg(class MatchmakingScreen * const this /* r29 */) {
    // Local variables
    class MatchmakingSlot * * it; // r31
    class MatchmakingSlot * pSlot; // r30

    // References
    // -> class SessionMgr * TheSessionMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol join; // size: 0x4, address: 0x80A4B4B8
static class Symbol is_h2h_arrangement; // size: 0x4, address: 0x80A4B4C0
static class Symbol local_network; // size: 0x4, address: 0x80A4B4C8
// Range: 0x80107EF8 -> 0x8010827C
void MatchmakingScreen::AutoJoinProcessNext(class MatchmakingScreen * const this /* r27 */) {
    // Local variables
    unsigned char isFinding; // r0
    unsigned char isH2h; // r0
    unsigned char isLocal; // r0
    int padNum; // r29
    class MatchmakingSlot * * it; // r28
    class MatchmakingSlot * pSlot; // r25
    class BandUser * pUserForSlot; // r0
    int userNum; // r24
    class vector users; // r1+0x28
    int firstFreePadNum; // r0

    // References
    // -> class PassiveMessenger * ThePassiveMessenger;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol local_network;
    // -> static class Symbol is_h2h_arrangement;
    // -> static class Symbol join;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class SessionMgr * TheSessionMgr;
    // -> class NetSession * TheNetSession;
    // -> class UIManager TheUI;
}

// Range: 0x8010827C -> 0x801083BC
class DataNode MatchmakingScreen::OnMsg(class MatchmakingScreen * const this /* r29 */, const class NetComponentFocusMsg & msg /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__4User;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Message playerNum; // size: 0x8, address: 0x80978D38
// Range: 0x801083BC -> 0x8010865C
class DataNode MatchmakingScreen::OnMsg(class MatchmakingScreen * const this /* r26 */, const class NetComponentSelectMsg & msg /* r27 */) {
    // Local variables
    class MatchmakingSlot * * it; // r29
    class MatchmakingSlot * pSlot; // r28
    class UIComponent * c; // r0

    // References
    // -> static class Message playerNum;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__4User;
}

static class Message playerNum; // size: 0x8, address: 0x80978D50
// Range: 0x8010865C -> 0x801089B4
class DataNode MatchmakingScreen::OnMsg(class MatchmakingScreen * const this /* r26 */, const class NetComponentScrollMsg & msg /* r27 */) {
    // Local variables
    class User * u; // r0
    class MatchmakingSlot * * it; // r29
    class MatchmakingSlot * pSlot; // r28
    class UIComponent * c; // r24
    class UIList * list; // r29
    class UISlider * slider; // r26

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

static class Symbol ranked; // size: 0x4, address: 0x80A4B4D0
static class Symbol disband; // size: 0x4, address: 0x80A4B4D8
static class Message init; // size: 0x8, address: 0x80978D68
// Range: 0x801089B4 -> 0x80108CCC
class DataNode MatchmakingScreen::OnMsg(class MatchmakingScreen * const this /* r30 */, const class RemotePlayerLeftMsg & msg /* r28 */) {
    // Local variables
    unsigned char isRanked; // r0

    // References
    // -> class BandUI * TheBandUI;
    // -> static class Message init;
    // -> struct [anonymous] __vt__7Message;
    // -> static class Symbol disband;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol ranked;
    // -> class Tour * TheTour;
    // -> class SessionMgr * TheSessionMgr;
    // -> class NetSession * TheNetSession;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80108CCC -> 0x80108D54
class DataNode MatchmakingScreen::OnMsg(class MatchmakingScreen * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80108D54 -> 0x80109094
class DataNode MatchmakingScreen::OnMsg(class MatchmakingScreen * const this /* r31 */) {
    // Local variables
    class vector users; // r1+0x24
    class vector usersToRemove; // r1+0x18
    class BandUser * * it; // r27
    class BandUser * pUser; // r1+0x14
    unsigned char removeUser; // r26
    class BandUser * pUserOwner; // r4
    class BandUser * pUserLeader; // r26
    class BandUser * pUser; // r25
    class MatchmakingSlot * pSlot; // r25
    class MatchmakingSlot * pSlot; // r25

    // References
    // -> class NetSession * TheNetSession;
    // -> class ProfileMgr TheProfileMgr;
    // -> class PlatformMgr ThePlatformMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x80109094 -> 0x8010913C
class DataNode MatchmakingScreen::OnUpdate(class MatchmakingScreen * const this /* r31 */) {
    // Local variables
    const class DataNode & n; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__15MatchmakingSlot;
}

static class Message msgPlayerNum; // size: 0x8, address: 0x80978D80
// Range: 0x8010913C -> 0x8010931C
void MatchmakingScreen::Update(class MatchmakingScreen * const this /* r26 */, int userNum /* r27 */) {
    // Local variables
    class MatchmakingSlot * pSlot; // r30
    class MatchmakingSlot * * it; // r29
    class MatchmakingSlot * pSlotCur; // r28

    // References
    // -> static class Message msgPlayerNum;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8010931C -> 0x80109330
void MatchmakingScreen::Update() {}

// Range: 0x80109330 -> 0x801094D0
class DataNode MatchmakingScreen::OnExportAll(class MatchmakingScreen * const this /* r29 */, class DataArray * a /* r30 */) {
    // Local variables
    class DataNode & n; // r0

    // References
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x801094D0 -> 0x801097AC
class DataNode MatchmakingScreen::ExportButtonDown(class MatchmakingScreen * const this /* r29 */, const class Message & msg /* r30 */, class BandUser * pUser /* r31 */) {
    // Local variables
    class DataNode result; // r1+0x18
    class MatchmakingSlot * pSlot; // r25
    class MatchmakingSlot * * it; // r24
    class MatchmakingSlot * pSlotCur; // r23
    class MatchmakingSlot * * it; // r23
    class MatchmakingSlot * pSlotCur; // r24
    class UIComponent * c; // r0

    // References
    // -> const char * gNullStr;
    // -> class UIManager TheUI;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801097AC -> 0x80109888
class DataNode MatchmakingScreen::ExportToPlayer(class MatchmakingScreen * const this /* r28 */, const class Message & msg /* r29 */, int player /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class UIManager TheUI;
}

static class Message player_num; // size: 0x8, address: 0x80978D98
// Range: 0x80109888 -> 0x80109AE0
class DataNode MatchmakingScreen::DoExportToPlayer(class DataNode * result /* r24 */, class MatchmakingScreen * const this /* r25 */, const class Message & msg /* r26 */, int player /* r27 */) {
    // Local variables
    class MatchmakingSlot * pSlot; // r30
    class MatchmakingSlot * * it; // r29
    class MatchmakingSlot * pSlotCur; // r28

    // References
    // -> const char * gNullStr;
    // -> static class Message player_num;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80109AE0 -> 0x80109BB0
class DataNode MatchmakingScreen::OptionHandle(class MatchmakingScreen * const this /* r26 */, class PanelDir * pDir /* r27 */, const class Message & msg /* r28 */, class Symbol & opt /* r29 */) {
    // Local variables
    class MatchmakingSlot * * it; // r31
    class MatchmakingSlot * pSlot; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80109BB0 -> 0x80109DAC
class DataNode MatchmakingScreen::OptionHandle(class DataNode * ret /* r29 */, class MatchmakingScreen * const this /* r26 */, class MatchmakingSlot * pSlot /* r30 */, const class Message & msg /* r31 */, class Symbol & opt /* r27 */) {
    // Local variables
    class DataArray * h; // r4

    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80109DAC -> 0x80109F90
class DataNode MatchmakingScreen::OnShowChar(class MatchmakingScreen * const this /* r27 */, class DataArray * a /* r28 */) {
    // Local variables
    class BandUser * pUser; // r29

    // References
    // -> struct [anonymous] __vt__7Message;
    // -> class GameConfig * TheGameConfig;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x80109F90 -> 0x8010A080
class DataNode MatchmakingScreen::OnMsg(class MatchmakingScreen * const this /* r29 */, const class AddLocalUserResultMsg & msg /* r30 */) {
    // Local variables
    class MatchmakingSlot * pSlot; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8010A080 -> 0x8010A160
class DataNode MatchmakingScreen::OnSessionBusy(class MatchmakingScreen * const this /* r29 */) {
    // Local variables
    class MatchmakingSlot * * it; // r31
    class MatchmakingSlot * pSlot; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class NetSession * TheNetSession;
}

static class Symbol matchmaking_pad_lost; // size: 0x4, address: 0x80A4B4E0
static class Symbol disband; // size: 0x4, address: 0x80A4B4E8
// Range: 0x8010A160 -> 0x8010A300
void MatchmakingScreen::AbandonSession(class MatchmakingScreen * const this /* r27 */) {
    // Local variables
    class MatchmakingSlot * * it; // r30
    class MatchmakingSlot * pSlot; // r29
    class BandUser * pUser; // r28

    // References
    // -> class BandUI * TheBandUI;
    // -> static class Symbol disband;
    // -> static class Symbol matchmaking_pad_lost;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class NetSession * TheNetSession;
}

static class Symbol _s; // size: 0x4, address: 0x80A4B4F0
static class Symbol _s; // size: 0x4, address: 0x80A4B4F8
static class Symbol _s; // size: 0x4, address: 0x80A4B500
static class Symbol _s; // size: 0x4, address: 0x80A4B508
static class Symbol _s; // size: 0x4, address: 0x80A4B510
static class Symbol _s; // size: 0x4, address: 0x80A4B518
static class Symbol _s; // size: 0x4, address: 0x80A4B520
static class Symbol _s; // size: 0x4, address: 0x80A4B528
static class Symbol _s; // size: 0x4, address: 0x80A4B530
// Range: 0x8010A300 -> 0x8010AF7C
class DataNode MatchmakingScreen::Handle(class MatchmakingScreen * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x48
    class MessageTimer _mt; // r1+0x148
    class DataNode r; // r1+0x140
    class DataNode r; // r1+0x138
    class DataNode r; // r1+0x130
    class DataNode r; // r1+0x128
    class DataNode r; // r1+0x120
    class DataNode r; // r1+0x118
    class DataNode r; // r1+0x110
    class DataNode r; // r1+0x108
    class DataNode r; // r1+0x100
    class DataNode r; // r1+0xF8
    class DataNode r; // r1+0xF0
    class DataNode r; // r1+0xE8
    class DataNode r; // r1+0xE0
    class DataNode r; // r1+0xD8
    class DataNode r; // r1+0xD0
    class DataNode r; // r1+0xC8
    class DataNode r; // r1+0xC0
    class DataNode _n; // r1+0xB8

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
}

class RemotePlayerChangedMsg : public Message {
    // total size: 0x8
};
class AddLocalUserResultMsg : public Message {
    // total size: 0x8
};
struct {
    // total size: 0xC
} __vt__21AddLocalUserResultMsg; // size: 0xC, address: 0x8088AC20
struct {
    // total size: 0x8
} __RTTI__21AddLocalUserResultMsg; // size: 0x8, address: 0x8088AC50
struct {
    // total size: 0x8
} __RTTI__15MatchmakingSlot; // size: 0x8, address: 0x8088AD28
struct {
    // total size: 0xC
} __vt__22RemotePlayerChangedMsg; // size: 0xC, address: 0x8088AD60
struct {
    // total size: 0x8
} __RTTI__22RemotePlayerChangedMsg; // size: 0x8, address: 0x8088AD90
struct {
    // total size: 0xC
} __vt__20UIComponentScrollMsg; // size: 0xC, address: 0x8088AF38
struct {
    // total size: 0x8
} __RTTI__20UIComponentScrollMsg; // size: 0x8, address: 0x8088AF68
struct {
    // total size: 0x80
} __vt__17MatchmakingScreen; // size: 0x80, address: 0x8088B270
struct {
    // total size: 0x8
} __RTTI__PP15MatchmakingSlot; // size: 0x8, address: 0x8088B4D0
struct _OKToMemCpy {
    // total size: 0x1
};

