/*
    Compile unit: C:\rockband2\band2\src\meta\MatchmakingSlot.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8010BADC -> 0x801148E0
*/
static class Symbol joypad; // size: 0x4, address: 0x80A4B53C
static class Symbol instrument_mapping; // size: 0x4, address: 0x80A4B544
// Range: 0x8010BADC -> 0x8010BC0C
enum ControllerType GetConnectedControllerType(int padNum /* r30 */) {
    // Local variables
    enum ControllerType ctOverride; // r0
    class Symbol controller; // r1+0x18
    class DataArray * cfg; // r0
    class DataArray * data; // r30
    enum ControllerType ct; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol instrument_mapping;
    // -> static class Symbol joypad;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x8010BC0C -> 0x8010BD40
void GetPadsWithoutUsers(class vector * pFakeUsers /* r29 */, enum ControllerType ct /* r30 */) {
    // Local variables
    int i; // r31
    class JoypadData * pData; // r0

    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> int kNonUser;
}

// Range: 0x8010BD40 -> 0x8010BD84
void * FakeBandUser::FakeBandUser(struct FakeBandUser * const this /* r31 */) {}

// Range: 0x8010BD84 -> 0x8010BDC4
void * FakeBandUser::FakeBandUser(struct FakeBandUser * const this /* r31 */) {}

// Range: 0x8010BDC4 -> 0x8010BE0C
void * FakeBandUser::FakeBandUser(struct FakeBandUser * const this /* r31 */, int pad /* r6 */) {}

// Range: 0x8010BE0C -> 0x8010BE28
int FakeBandUser::GetPadNum() {}

// Range: 0x8010BE28 -> 0x8010BE70
char * FakeBandUser::GetUserName() {
    // Local variables
    int padNum; // r0

    // References
    // -> class PlatformMgr ThePlatformMgr;
}

// Range: 0x8010BE70 -> 0x8010BE98
enum ControllerType FakeBandUser::ConnectedControllerType() {}

// Range: 0x8010BE98 -> 0x8010BEBC
unsigned char FakeBandUser::IsParticipating() {}

// Range: 0x8010BEBC -> 0x8010BEE0
unsigned char FakeBandUser::IsLocalPlayer() {}

// Range: 0x8010BEE0 -> 0x8010BF04
unsigned char FakeBandUser::IsJoypadConnected() {}

struct UserName {
    // total size: 0x10
    class String mUserName; // offset 0x0, size 0xC
    int mPadNum; // offset 0xC, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct UserName * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct UserName * _M_start; // offset 0x0, size 0x4
    struct UserName * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class UserNameProvider : public ListProvider, public Object {
    // total size: 0x3C
    class vector mUserNames; // offset 0x2C, size 0xC
    class MatchmakingSlot * mMMSlot; // offset 0x38, size 0x4
};
// Range: 0x8010BF04 -> 0x8010C020
void * MatchmakingSlot::MatchmakingSlot(class MatchmakingSlot * const this /* r28 */, class MatchmakingScreen * pMMScreen /* r29 */, int slotNum /* r30 */, class PanelDir * pDir /* r31 */) {
    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__15MatchmakingSlot;
}

// Range: 0x8010C020 -> 0x8010C170
void * MatchmakingSlot::~MatchmakingSlot(class MatchmakingSlot * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__15MatchmakingSlot;
}

// Range: 0x8010C170 -> 0x8010C178
class ObjectDir * MatchmakingSlot::DataDir() {}

static class Symbol is_h2h_arrangement; // size: 0x4, address: 0x80A4B54C
static class Symbol slot; // size: 0x4, address: 0x80A4B554
static class Message msgEnter; // size: 0x8, address: 0x80978DB0
// Range: 0x8010C178 -> 0x8010CE90
void MatchmakingSlot::Enter(class MatchmakingSlot * const this /* r30 */) {
    // Local variables
    class BandUser * pUser; // r27
    unsigned char isH2h; // r0

    // References
    // -> static class Message msgEnter;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
    // -> static class Symbol slot;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol is_h2h_arrangement;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x8010CE90 -> 0x8010CE98
int MatchmakingSlot::GetSlotNum() {}

// Range: 0x8010CE98 -> 0x8010CEA0
class PanelDir * MatchmakingSlot::GetPanelDir() {}

// Range: 0x8010CEA0 -> 0x8010CF1C
unsigned char MatchmakingSlot::IsReady(class MatchmakingSlot * const this /* r4 */) {
    // Local variables
    class BandUser * pUser; // r30

    // References
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x8010CF1C -> 0x8010CFB4
unsigned char MatchmakingSlot::IsLeader(const class MatchmakingSlot * const this /* r4 */) {
    // Local variables
    class BandUser * pUser; // r29

    // References
    // -> class SessionMgr * TheSessionMgr;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x8010CFB4 -> 0x8010D03C
unsigned char MatchmakingSlot::IsLocal(const class MatchmakingSlot * const this /* r4 */) {
    // Local variables
    class BandUser * pUser; // r30

    // References
    // -> class BandUserMgr * TheBandUserMgr;
}

static class Symbol is_h2h_arrangement; // size: 0x4, address: 0x80A4B55C
static class Symbol local_network; // size: 0x4, address: 0x80A4B564
static class Symbol slot; // size: 0x4, address: 0x80A4B56C
// Range: 0x8010D03C -> 0x8010D780
void MatchmakingSlot::PopulateUserNameList(class MatchmakingSlot * const this /* r26 */, class vector * pFakeUsers /* r27 */) {
    // Local variables
    unsigned char isH2h; // r0
    unsigned char isOnline; // r0
    class vector users; // r1+0x60
    enum ControllerType ctSlot; // r28
    class BandUser * * it; // r29
    class BandUser * * it; // r29
    class BandUser * pUserOther; // r0
    struct FakeBandUser * itHighestPad; // r28
    struct FakeBandUser * it; // r29
    struct FakeBandUser * it; // r28
    struct FakeBandUser userHighest; // r1+0x94

    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> const char * kAssertStr;
    // -> static class Symbol slot;
    // -> static class Symbol local_network;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol is_h2h_arrangement;
    // -> class Debug TheDebug;
}

static class Symbol online_play_required; // size: 0x4, address: 0x80A4B574
static class Symbol guest_not_first; // size: 0x4, address: 0x80A4B57C
// Range: 0x8010D780 -> 0x8010DB70
void MatchmakingSlot::PopulateUserJoinFromUserNames(class MatchmakingSlot * const this /* r24 */, class vector * pFakeUsers /* r25 */) {
    // Local variables
    unsigned char onlineRequired; // r0
    unsigned char guestNotFirst; // r0
    class vector usersLocalParticipants; // r1+0x2C
    unsigned char isFirst; // r26
    struct FakeBandUser * it; // r27
    struct UserJoinEntry entry; // r1+0x38
    int padNum; // r22
    unsigned char hasOnline; // r0
    unsigned char isGuest; // r0

    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> static class Symbol guest_not_first;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol online_play_required;
    // -> class Debug TheDebug;
}

// Range: 0x8010DB70 -> 0x8010DBB4
unsigned char MatchmakingSlot::LookupUserInJoinList() {
    // Local variables
    struct UserJoinEntry * it; // r6
}

// Range: 0x8010DBB4 -> 0x8010DC34
unsigned char MatchmakingSlot::CanPadJoin(class MatchmakingSlot * const this /* r29 */, int padNum /* r30 */) {
    // Local variables
    struct UserJoinEntry * it; // r31
}

static class Symbol local_network; // size: 0x4, address: 0x80A4B584
static class Symbol ready; // size: 0x4, address: 0x80A4B58C
static class Symbol is_tour; // size: 0x4, address: 0x80A4B594
static class Symbol ranked; // size: 0x4, address: 0x80A4B59C
// Range: 0x8010DC34 -> 0x8010DF28
void MatchmakingSlot::PopulateAllowableActionsList(class MatchmakingSlot * const this /* r25 */) {
    // Local variables
    class BandUser * pUser; // r0
    unsigned char enabled; // r0
    unsigned char isLocal; // r0
    unsigned char isOnline; // r0
    unsigned char isLeaderLocal; // r26
    int leaderNum; // r0
    class BandUser * pUserLeader; // r0
    unsigned char isRanked; // r0
    unsigned char isBrowsing; // r3
    unsigned char isFull; // r0

    // References
    // -> static class Symbol ranked;
    // -> class Tour * TheTour;
    // -> static class Symbol is_tour;
    // -> static class Symbol ready;
    // -> class SessionMgr * TheSessionMgr;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol local_network;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x8010DF28 -> 0x8010DF34
unsigned char MatchmakingSlot::IsAllowed() {}

// Range: 0x8010DF34 -> 0x8010DF3C
class Symbol MatchmakingSlot::GetOption() {}

static class Symbol ready; // size: 0x4, address: 0x80A4B5A4
static class Symbol choose_part; // size: 0x4, address: 0x80A4B5AC
static class Symbol choose_char; // size: 0x4, address: 0x80A4B5B4
static class Symbol is_h2h_arrangement; // size: 0x4, address: 0x80A4B5BC
static class Symbol local_network; // size: 0x4, address: 0x80A4B5C4
static class Symbol remote_only; // size: 0x4, address: 0x80A4B5CC
static class Symbol no_instrument; // size: 0x4, address: 0x80A4B5D4
static class Symbol join; // size: 0x4, address: 0x80A4B5DC
static class Symbol sign_in; // size: 0x4, address: 0x80A4B5E4
static class Symbol guest_not_first; // size: 0x4, address: 0x80A4B5EC
// Range: 0x8010DF3C -> 0x8010E5F4
class Symbol MatchmakingSlot::GenerateCurrentOption(class MatchmakingSlot * const this /* r30 */) {
    // Local variables
    class BandUser * pUser; // r28
    unsigned char isH2h; // r0
    unsigned char isOnline; // r0
    class vector fakeUsers; // r1+0x8C
    unsigned char anyUserNeedsOnline; // r3
    unsigned char anyUserGuestNotFirst; // r4
    struct UserJoinEntry * it; // r5

    // References
    // -> static class Symbol guest_not_first;
    // -> static class Symbol sign_in;
    // -> static class Symbol join;
    // -> static class Symbol no_instrument;
    // -> static class Symbol remote_only;
    // -> static class Symbol local_network;
    // -> static class Symbol is_h2h_arrangement;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol choose_char;
    // -> static class Symbol choose_part;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol ready;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x8010E5F4 -> 0x8010E6C8
void MatchmakingSlot::RemovePlayer(class MatchmakingSlot * const this /* r28 */) {
    // Local variables
    class BandUser * pUser; // r0
    int leaderNum; // r0

    // References
    // -> class SessionMgr * TheSessionMgr;
    // -> class Tour * TheTour;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
}

static class Symbol choose_part; // size: 0x4, address: 0x80A4B5F4
static class Symbol choose_char; // size: 0x4, address: 0x80A4B5FC
// Range: 0x8010E6C8 -> 0x8010E768
unsigned char MatchmakingSlot::UseButtonExtendedOptions(class MatchmakingSlot * const this /* r31 */) {
    // References
    // -> static class Symbol choose_char;
    // -> static class Symbol choose_part;
}

// Range: 0x8010E768 -> 0x8010E808
unsigned char MatchmakingSlot::AllowButtonMsg(class MatchmakingSlot * const this /* r30 */, class BandUser * pUser /* r31 */) {
    // Local variables
    class BandUser * pUserSlot; // r0
    struct UserJoinEntry * it; // r3

    // References
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x8010E808 -> 0x8010E9D0
void MatchmakingSlot::InitCharProvider(class MatchmakingSlot * const this /* r28 */) {
    // Local variables
    class BandUser * pUser; // r29
    int pos; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6UIList;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x8010E9D0 -> 0x8010EBB4
void MatchmakingSlot::UpdateCharProvider(class MatchmakingSlot * const this /* r28 */) {
    // Local variables
    class BandUser * pUser; // r29
    int pos; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6UIList;
    // -> class BandUserMgr * TheBandUserMgr;
}

static class Symbol slot; // size: 0x4, address: 0x80A4B604
static class Symbol is_h2h_arrangement; // size: 0x4, address: 0x80A4B60C
static class Symbol local_network; // size: 0x4, address: 0x80A4B614
// Range: 0x8010EBB4 -> 0x8010ED88
void MatchmakingSlot::UpdateUserNameProvider(class MatchmakingSlot * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6UIList;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol local_network;
    // -> static class Symbol is_h2h_arrangement;
    // -> static class Symbol slot;
}

// Range: 0x8010ED88 -> 0x8010EDA4
void MatchmakingSlot::PreserveLastButton(class MatchmakingSlot * const this /* r7 */) {}

// Range: 0x8010EDA4 -> 0x8010EE48
void MatchmakingSlot::LoadChar(class MatchmakingSlot * const this /* r5 */, const class CharData * pChar /* r29 */) {
    // Local variables
    class BandUser * pUser; // r30

    // References
    // -> class CharCache * TheCharCache;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x8010EE48 -> 0x8010EF90
void MatchmakingSlot::LoadCharFromList(class MatchmakingSlot * const this /* r27 */) {
    // Local variables
    int pos; // r28

    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6UIList;
}

// Range: 0x8010EF90 -> 0x8010F030
void MatchmakingSlot::ReleaseChar(class MatchmakingSlot * const this /* r30 */) {
    // Local variables
    class BandUser * pUser; // r31

    // References
    // -> class SessionMgr * TheSessionMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x8010F030 -> 0x8010F1D0
unsigned char MatchmakingSlot::ShowChar(class MatchmakingSlot * const this /* r27 */) {
    // Local variables
    class BandUser * pUser; // r0
    int cChar; // r0
    int iChar; // r4

    // References
    // -> const char * kAssertStr;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6UIList;
    // -> class Debug TheDebug;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x8010F1D0 -> 0x8010F22C
void MatchmakingSlot::VerifyControllerTypes() {}

static class Symbol choose_char; // size: 0x4, address: 0x80A4B61C
static class Message msg; // size: 0x8, address: 0x80978DC8
static class Symbol is_h2h_arrangement; // size: 0x4, address: 0x80A4B624
static class Symbol slot; // size: 0x4, address: 0x80A4B62C
static class Symbol remote_only; // size: 0x4, address: 0x80A4B634
static class Symbol no_instrument; // size: 0x4, address: 0x80A4B63C
static class Symbol sign_in; // size: 0x4, address: 0x80A4B644
static class Symbol guest_not_first; // size: 0x4, address: 0x80A4B64C
static class Symbol join; // size: 0x4, address: 0x80A4B654
static class Symbol choose_part; // size: 0x4, address: 0x80A4B65C
static class Symbol choose_char; // size: 0x4, address: 0x80A4B664
static class Symbol ready; // size: 0x4, address: 0x80A4B66C
static unsigned char map[11][13]; // size: 0x8F, address: 0x80848238
static class Symbol slot; // size: 0x4, address: 0x80A4B674
static class Message msg; // size: 0x8, address: 0x80978DE0
static class Message msg; // size: 0x8, address: 0x80978DF8
static class Message msgUpdate; // size: 0x8, address: 0x80978E10
static class Message msg; // size: 0x8, address: 0x80978E28
static class Message msgUpdate; // size: 0x8, address: 0x80978E40
static class Message msgUpdateNames; // size: 0x8, address: 0x80978E58
static class Message msgUpdateOnlineEnabled; // size: 0x8, address: 0x80978E70
// Range: 0x8010F22C -> 0x80111180
void MatchmakingSlot::Update(class MatchmakingSlot * const this /* r25 */) {
    // Local variables
    class Symbol symNewState; // r1+0x84
    unsigned char isH2h; // r0
    class BandUser * pUser0; // r24
    class BandUser * pUser1; // r3
    class BandUser * pUser; // r28
    unsigned char row[13]; // r1+0x240
    class Symbol symSlot; // r1+0x80
    enum ControllerType ctSlot; // r27
    class Symbol symIcon; // r1+0x7C
    unsigned char isGuitar; // r27
    unsigned char isDrum; // r31
    unsigned char isVocals; // r26
    struct UserJoinEntry * it; // r24
    enum ControllerType ct; // r0

    // References
    // -> static class Message msgUpdateOnlineEnabled;
    // -> const char * gNullStr;
    // -> class PlatformMgr ThePlatformMgr;
    // -> static class Message msgUpdateNames;
    // -> static class Message msgUpdate;
    // -> static class Message msg;
    // -> static class Message msgUpdate;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Symbol slot;
    // -> static unsigned char map[11][13];
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class SessionMgr * TheSessionMgr;
    // -> static class Symbol ready;
    // -> static class Symbol choose_char;
    // -> static class Symbol choose_part;
    // -> static class Symbol join;
    // -> static class Symbol guest_not_first;
    // -> static class Symbol sign_in;
    // -> static class Symbol no_instrument;
    // -> static class Symbol remote_only;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> static class Symbol slot;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol is_h2h_arrangement;
    // -> class NetSync * TheNetSync;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> static class Symbol choose_char;
}

static class Symbol is_h2h_arrangement; // size: 0x4, address: 0x80A4B680
static class Symbol ranked; // size: 0x4, address: 0x80A4B688
// Range: 0x80111180 -> 0x80111408
class DataNode MatchmakingSlot::OnMsg(class MatchmakingSlot * const this /* r30 */, const class AddLocalUserResultMsg & msg /* r27 */) {
    // Local variables
    unsigned char isH2h; // r0
    unsigned char isRanked; // r0
    enum ControllerType ct; // r0
    enum TrackType tt; // r4

    // References
    // -> class GameMode * TheGameMode;
    // -> static class Symbol ranked;
    // -> static class Symbol is_h2h_arrangement;
    // -> class GameConfig * TheGameConfig;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8BandUser;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class SessionMgr * TheSessionMgr;
    // -> class Symbol t;
}

static class Symbol wii_roguitar; // size: 0x4, address: 0x80A4B690
static class Symbol wii_rodrums; // size: 0x4, address: 0x80A4B698
static class Symbol joypad; // size: 0x4, address: 0x80A4B6A0
static class Symbol instrument_mapping; // size: 0x4, address: 0x80A4B6A8
static class Message init; // size: 0x8, address: 0x80978E88
static class Symbol matchmaking_pad_lost; // size: 0x4, address: 0x80A4B6B0
// Range: 0x80111408 -> 0x80111C7C
class DataNode MatchmakingSlot::OnVerifyControllerTypes(class MatchmakingSlot * const this /* r23 */) {
    // Local variables
    class BandUser * pUser; // r29
    enum ControllerType ctOld; // r28
    unsigned char swapped; // r27
    unsigned char hasRemotePlayers; // r26
    class vector & users; // r0
    class BandUser * * u; // r25
    class BandUser * newUser; // r24
    class Symbol controller; // r1+0x40
    class DataArray * cfg; // r0
    class DataArray * data; // r21
    enum ControllerType remoteControllerType; // r0
    int i; // r24
    class JoypadData * padData; // r0
    class Symbol controller; // r1+0x3C
    class DataArray * cfg; // r0
    class DataArray * data; // r21
    enum ControllerType unclaimedControllerType; // r0
    enum ControllerType ctNew; // r0
    int padNum; // r21

    // References
    // -> class BandUI * TheBandUI;
    // -> static class Symbol matchmaking_pad_lost;
    // -> class PlatformMgr ThePlatformMgr;
    // -> static class Message init;
    // -> struct [anonymous] __vt__7Message;
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol instrument_mapping;
    // -> static class Symbol joypad;
    // -> static class Symbol wii_rodrums;
    // -> static class Symbol wii_roguitar;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class NetSession * TheNetSession;
}

static class Symbol online_play_required; // size: 0x4, address: 0x80A4B6B8
// Range: 0x80111C7C -> 0x80111DB0
unsigned char MatchmakingSlot::WarnRemovePlayer(const class MatchmakingSlot * const this /* r28 */) {
    // Local variables
    unsigned char onlineRequired; // r0
    class BandUser * pUser; // r28

    // References
    // -> class NetSession * TheNetSession;
    // -> class SessionMgr * TheSessionMgr;
    // -> class Tour * TheTour;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol online_play_required;
}

// Range: 0x80111DB0 -> 0x80111E60
class DataNode MatchmakingSlot::OnMsg(const class UIComponentFocusChangeMsg & msg /* r31 */) {
    // Local variables
    class BandUser * pUser; // r0

    // References
    // -> class NetSync * TheNetSync;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11UIComponent;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x80111E60 -> 0x80111F84
class DataNode MatchmakingSlot::OnMsg(class MatchmakingSlot * const this /* r28 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11UIComponent;
}

static class Message msgButtonPulse; // size: 0x8, address: 0x80978EA0
static class Symbol remote_only; // size: 0x4, address: 0x80A4B6C0
static class Symbol no_instrument; // size: 0x4, address: 0x80A4B6C8
static class Symbol sign_in; // size: 0x4, address: 0x80A4B6D0
static class Symbol guest_not_first; // size: 0x4, address: 0x80A4B6D8
static class Symbol join; // size: 0x4, address: 0x80A4B6E0
static class Symbol choose_char; // size: 0x4, address: 0x80A4B6E8
static class Symbol choose_part; // size: 0x4, address: 0x80A4B6F0
static class Symbol ready; // size: 0x4, address: 0x80A4B6F8
static class Symbol ranked; // size: 0x4, address: 0x80A4B700
static class Symbol invite_accepted; // size: 0x4, address: 0x80A4B708
static class Symbol is_h2h_arrangement; // size: 0x4, address: 0x80A4B710
static class Symbol local_network; // size: 0x4, address: 0x80A4B718
static class Message msg; // size: 0x8, address: 0x80978EB8
static class Message msg; // size: 0x8, address: 0x80978ED0
static class Message msg; // size: 0x8, address: 0x80978EE8
static class Message msg; // size: 0x8, address: 0x80978F00
static class Message msg; // size: 0x8, address: 0x80978F18
static class Message msg; // size: 0x8, address: 0x80978F30
static class Symbol local_network; // size: 0x4, address: 0x80A4B724
static class Message msg; // size: 0x8, address: 0x80978F48
static class Symbol is_tour; // size: 0x4, address: 0x80A4B72C
static class Message msg; // size: 0x8, address: 0x80978F60
// Range: 0x80111F84 -> 0x80113528
class DataNode MatchmakingSlot::OnMsg(class MatchmakingSlot * const this /* r25 */, const class ButtonDownMsg & msgButtonDown /* r26 */) {
    // Local variables
    unsigned char isRanked; // r0
    class BandUser * pUser; // r27
    enum JoinState joinStateUser; // r1+0x74
    unsigned char isH2h; // r0
    unsigned char isLocal; // r0
    unsigned char isOnline; // r0
    unsigned char isOnline; // r0
    enum TourMode mode; // r0
    unsigned char isOnline; // r0

    // References
    // -> static class Message msg;
    // -> class Tour * TheTour;
    // -> static class Symbol is_tour;
    // -> static class Message msg;
    // -> static class Symbol local_network;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> class GameConfig * TheGameConfig;
    // -> static class Symbol local_network;
    // -> static class Symbol is_h2h_arrangement;
    // -> class BandUI * TheBandUI;
    // -> static class Symbol invite_accepted;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol ranked;
    // -> static class Symbol ready;
    // -> static class Symbol choose_part;
    // -> static class Symbol choose_char;
    // -> static class Symbol join;
    // -> static class Symbol guest_not_first;
    // -> static class Symbol sign_in;
    // -> static class Symbol no_instrument;
    // -> static class Symbol remote_only;
    // -> static class Message msgButtonPulse;
    // -> struct [anonymous] __vt__7Message;
    // -> class Synth * TheSynth;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class SessionMgr * TheSessionMgr;
}

static class Symbol choose_part; // size: 0x4, address: 0x80A4B734
static class Symbol choose_char; // size: 0x4, address: 0x80A4B73C
static class Message msg; // size: 0x8, address: 0x80978F78
static class Message msg; // size: 0x8, address: 0x80978F90
static class Message msg; // size: 0x8, address: 0x80978FA8
static class Message msg; // size: 0x8, address: 0x80978FC0
// Range: 0x80113528 -> 0x80113DE0
class DataNode MatchmakingSlot::OnMsg(class MatchmakingSlot * const this /* r28 */, const class UIComponentSelectMsg & msg /* r29 */) {
    // Local variables
    class BandUser * pUser; // r25
    enum TrackType track; // r24
    class UIList * pList; // r24
    int pos; // r24
    class BandUser * pUser; // r23
    class CharData * pChar; // r24

    // References
    // -> class SessionMgr * TheSessionMgr;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__7UIPanel;
    // -> class ObjectDir * sMainDir;
    // -> class ProfileMgr TheProfileMgr;
    // -> struct [anonymous] __RTTI__8BandUser;
    // -> struct [anonymous] __RTTI__4User;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__6UIList;
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11UIComponent;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> static class Symbol choose_char;
    // -> static class Symbol choose_part;
}

static class Symbol choose_part; // size: 0x4, address: 0x80A4B748
static class Symbol choose_char; // size: 0x4, address: 0x80A4B750
static class Symbol ready; // size: 0x4, address: 0x80A4B758
// Range: 0x80113DE0 -> 0x80113EB8
unsigned char MatchmakingSlot::IsUserState(class Symbol & symOpt /* r30 */) {
    // References
    // -> static class Symbol ready;
    // -> static class Symbol choose_char;
    // -> static class Symbol choose_part;
}

static class Symbol _s; // size: 0x4, address: 0x80A4B760
static class Symbol _s; // size: 0x4, address: 0x80A4B768
static class Symbol _s; // size: 0x4, address: 0x80A4B770
static class Symbol _s; // size: 0x4, address: 0x80A4B778
static class Symbol _s; // size: 0x4, address: 0x80A4B780
static class Symbol _s; // size: 0x4, address: 0x80A4B788
static class Symbol _s; // size: 0x4, address: 0x80A4B790
static class Symbol _s; // size: 0x4, address: 0x80A4B798
static class Symbol _s; // size: 0x4, address: 0x80A4B7A0
static class Symbol _s; // size: 0x4, address: 0x80A4B7A8
static class Symbol _s; // size: 0x4, address: 0x80A4B7B0
static class Symbol _s; // size: 0x4, address: 0x80A4B7B8
static class Symbol _s; // size: 0x4, address: 0x80A4B7C0
static class Symbol _s; // size: 0x4, address: 0x80A4B7C8
static class Symbol _s; // size: 0x4, address: 0x80A4B7D0
// Range: 0x80113EB8 -> 0x801148E0
class DataNode MatchmakingSlot::Handle(class MatchmakingSlot * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x2C
    class MessageTimer _mt; // r1+0x98
    class DataNode r; // r1+0x90
    class DataNode r; // r1+0x88
    class DataNode r; // r1+0x80
    class DataNode r; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode r; // r1+0x68
    class DataNode _n; // r1+0x60
    class DataNode _n; // r1+0x58

    // References
    // -> class DebugNotifier TheDebugNotifier;
    // -> static class Symbol _s;
    // -> class BandUserMgr * TheBandUserMgr;
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

struct {
    // total size: 0x54
} __vt__15MatchmakingSlot; // size: 0x54, address: 0x8088BE54
struct {
    // total size: 0x8
} __RTTI__P13UserJoinEntry; // size: 0x8, address: 0x8088C338
struct {
    // total size: 0x8
} __RTTI__P12FakeBandUser; // size: 0x8, address: 0x8088C350

