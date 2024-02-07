/*
    Compile unit: C:\rockband2\band2\src\meta\SessionMgr.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8016165C -> 0x801665F4
*/
class Symbol t; // size: 0x4, address: 0x80A4C47C
class Symbol t; // size: 0x4, address: 0x80A4C484
class Symbol t; // size: 0x4, address: 0x80A4C48C
class SessionMgr * TheSessionMgr; // size: 0x4, address: 0x80A4C490
// Range: 0x8016165C -> 0x80161698
void SessionMgr::Init() {
    // References
    // -> class SessionMgr * TheSessionMgr;
}

// Range: 0x80161698 -> 0x80161814
void * SessionMgr::SessionMgr(class SessionMgr * const this /* r31 */) {
    // References
    // -> class NetSession * TheNetSession;
    // -> class ObjectDir * sMainDir;
    // -> struct [anonymous] __vt__10SessionMgr;
    // -> struct [anonymous] __vt__9MsgSource;
}

// Range: 0x80161814 -> 0x801619EC
void * SessionMgr::~SessionMgr(class SessionMgr * const this /* r30 */) {
    // References
    // -> class ObjectDir * sMainDir;
    // -> struct [anonymous] __vt__10SessionMgr;
}

// Range: 0x80161A84 -> 0x80161A8C
void SessionMgr::Poll() {}

static class Symbol session_ready; // size: 0x4, address: 0x80A4C498
static class Symbol wii_roguitar; // size: 0x4, address: 0x80A4C4A0
static class Symbol wii_rodrums; // size: 0x4, address: 0x80A4C4A8
static class Symbol is_tour; // size: 0x4, address: 0x80A4C4B0
static class Symbol wii_roguitar; // size: 0x4, address: 0x80A4C4B8
static class Symbol wii_rodrums; // size: 0x4, address: 0x80A4C4C0
// Range: 0x80161A8C -> 0x80161FEC
void SessionMgr::AddLocalUser(class SessionMgr * const this /* r29 */, class BandUser * pUser /* r30 */) {
    // Local variables
    class Message msg; // r1+0x60

    // References
    // -> class GameConfig * TheGameConfig;
    // -> class Symbol t;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> static class Symbol wii_rodrums;
    // -> static class Symbol wii_roguitar;
    // -> struct [anonymous] __vt__7Message;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol is_tour;
    // -> class Rnd & TheRnd;
    // -> static class Symbol wii_rodrums;
    // -> static class Symbol wii_roguitar;
    // -> class PlatformMgr ThePlatformMgr;
    // -> const char * gNullStr;
    // -> class Symbol t;
    // -> static class Symbol session_ready;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol session_ready; // size: 0x4, address: 0x80A4C4C8
static class Symbol is_tour; // size: 0x4, address: 0x80A4C4D0
static class Symbol guest_not_first; // size: 0x4, address: 0x80A4C4D8
// Range: 0x80161FEC -> 0x80162878
void SessionMgr::RemoveLocalPlayer(class SessionMgr * const this /* r23 */, int playerNum /* r24 */) {
    // Local variables
    unsigned char isTour; // r0
    int leaderNum; // r0
    unsigned char isLocalHost; // r30
    unsigned char isLastLocalPlayer; // r31
    class list users; // r1+0x78
    class BandUser * pUser; // r0
    int guestCount; // r31
    struct _List_iterator it; // r1+0x64
    class BandUser * pUserCur; // r24
    struct SavePlayer sp; // r1+0x80
    unsigned char isGuestNotFirst; // r0
    struct SavePlayer * it; // r24
    unsigned char isAnyoneLeftToSave; // r0
    unsigned char useLeaderAsNewHost; // r5
    struct SavePlayer * it; // r6
    class BandUser * pUserNewLeader; // r25
    struct SavePlayer * it; // r24
    struct SavePlayer * spIt; // r24

    // References
    // -> class GameConfig * TheGameConfig;
    // -> const char * gNullStr;
    // -> class Symbol t;
    // -> class CharCache * TheCharCache;
    // -> static class Symbol guest_not_first;
    // -> class PlatformMgr ThePlatformMgr;
    // -> struct [anonymous] __RTTI__4User;
    // -> struct [anonymous] __RTTI__8BandUser;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class BandUI * TheBandUI;
    // -> class Rnd & TheRnd;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol is_tour;
    // -> static class Symbol session_ready;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol is_tour; // size: 0x4, address: 0x80A4C4E0
static class Symbol choose_leader_from_band; // size: 0x4, address: 0x80A4C4E8
// Range: 0x80162878 -> 0x801629E0
void SessionMgr::UpdateBandLeader(class SessionMgr * const this /* r29 */) {
    // Local variables
    int localHost; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol choose_leader_from_band;
    // -> static class Symbol is_tour;
}

// Range: 0x801629E0 -> 0x801629E8
int SessionMgr::GetLeaderNum() {}

// Range: 0x801629E8 -> 0x801629F8
class BandUser * SessionMgr::GetLeaderUser(class SessionMgr * const this /* r4 */) {
    // References
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x801629F8 -> 0x80162A00
void SessionMgr::ClearLeaderNum() {}

class LocalLeaderChangedMsg : public Message {
    // total size: 0x8
};
static class LocalLeaderChangedMsg msg; // size: 0x8, address: 0x80979CA0
// Range: 0x80162A00 -> 0x80162CBC
void SessionMgr::SetLeaderNum(class SessionMgr * const this /* r29 */, int leaderNum /* r30 */) {
    // References
    // -> struct [anonymous] __vt__21LocalLeaderChangedMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class LocalLeaderChangedMsg msg;
}

static class Message completeMsg; // size: 0x8, address: 0x80979CB8
static class Symbol session_ready; // size: 0x4, address: 0x80A4C4F0
static class AddLocalUserResultMsg msgResultMsg; // size: 0x8, address: 0x80979CD0
static class Symbol is_tour; // size: 0x4, address: 0x80A4C4F8
// Range: 0x80162D40 -> 0x801636F0
class DataNode SessionMgr::OnMsg(class SessionMgr * const this /* r27 */, const class SessionReadyMsg & msg /* r28 */) {
    // Local variables
    class BandUser * user; // r25
    class BandUser * user; // r25
    struct SavePlayer * it; // r25
    class BandUser * user; // r28

    // References
    // -> class UIManager TheUI;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__17MatchmakingScreen;
    // -> class ObjectDir * sMainDir;
    // -> class GameConfig * TheGameConfig;
    // -> class GameMode * TheGameMode;
    // -> class Rnd & TheRnd;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol is_tour;
    // -> struct [anonymous] __vt__21AddLocalUserResultMsg;
    // -> class Symbol t;
    // -> static class AddLocalUserResultMsg msgResultMsg;
    // -> static class Symbol session_ready;
    // -> static class Message completeMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class PlatformMgr ThePlatformMgr;
    // -> class Symbol t;
}

static class AddLocalUserResultMsg msgAddLocalResult; // size: 0x8, address: 0x80979CE8
// Range: 0x801636F0 -> 0x80163B54
class DataNode SessionMgr::OnMsg(class SessionMgr * const this /* r29 */, const class AddPlayerResultMsg & msg /* r30 */) {
    // References
    // -> struct [anonymous] __vt__21AddLocalUserResultMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class AddLocalUserResultMsg msgAddLocalResult;
    // -> class PlatformMgr ThePlatformMgr;
    // -> class Symbol t;
    // -> class Symbol t;
}

// Range: 0x80163B54 -> 0x80163DAC
class DataNode SessionMgr::OnMsg(class SessionMgr * const this /* r29 */) {
    // Local variables
    struct SavePlayer * spIt; // r30

    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> class Symbol t;
}

// Range: 0x80163DAC -> 0x80163DB4
void SessionMgr::SetPossibleAutoJoinPads() {}

// Range: 0x80163DB4 -> 0x80163DD0
unsigned char SessionMgr::HasPossibleAutoJoinPads() {}

// Range: 0x80163DD0 -> 0x80163DE0
void SessionMgr::GetPossibleAutoJoinPads(const class SessionMgr * const this /* r5 */) {}

// Range: 0x80163DE0 -> 0x80163E4C
void SessionMgr::ClearPossibleAutoJoinPads(class SessionMgr * const this /* r30 */) {}

static class Symbol _s; // size: 0x4, address: 0x80A4C500
static class Symbol _s; // size: 0x4, address: 0x80A4C508
static class Symbol _s; // size: 0x4, address: 0x80A4C510
static class Symbol _s; // size: 0x4, address: 0x80A4C518
static class Symbol _s; // size: 0x4, address: 0x80A4C520
static class Symbol _s; // size: 0x4, address: 0x80A4C528
// Range: 0x80163E4C -> 0x80164CD0
class DataNode SessionMgr::Handle(class SessionMgr * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x54
    class MessageTimer _mt; // r1+0x98
    class DataNode r; // r1+0x90
    class DataNode r; // r1+0x88
    class DataNode r; // r1+0x80
    class DataNode _n; // r1+0x78
    class DataNode _n; // r1+0x70

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__16SigninChangedMsg;
    // -> class Symbol t;
    // -> struct [anonymous] __vt__18AddPlayerResultMsg;
    // -> class Symbol t;
    // -> struct [anonymous] __vt__15SessionReadyMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8BandUser;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

class Symbol disband; // size: 0x4, address: 0x80A4C530
class Message init; // size: 0x8, address: 0x80979D00
class KickPlayerMsg : public NetMessage {
    // total size: 0x4
};
// Range: 0x80164CD0 -> 0x80164D08
static class NetMessage * KickPlayerMsg::NewNetMessage() {
    // References
    // -> static struct [anonymous] __vt__Q224@unnamed@SessionMgr_cpp@13KickPlayerMsg;
}

// Range: 0x80164D08 -> 0x80164DC8
void * RemotePlayersProvider::RemotePlayersProvider(class RemotePlayersProvider * const this /* r31 */) {
    // References
    // -> class NetMessageFactory TheNetMessageFactory;
    // -> class ObjectDir * sMainDir;
    // -> struct [anonymous] __vt__21RemotePlayersProvider;
    // -> struct [anonymous] __vt__12ListProvider;
}

// Range: 0x80164DC8 -> 0x80164E40
void RemotePlayersProvider::Cleanup(class RemotePlayersProvider * const this /* r30 */) {}

// Range: 0x80164E40 -> 0x80164F00
void RemotePlayersProvider::KickPlayer(class RemotePlayersProvider * const this /* r30 */, int selected /* r31 */) {
    // Local variables
    class KickPlayerMsg msg; // r1+0x8

    // References
    // -> class NetSession * TheNetSession;
    // -> static struct [anonymous] __vt__Q224@unnamed@SessionMgr_cpp@13KickPlayerMsg;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80164F40 -> 0x80164F44
void RemotePlayersProvider::ToggleMuteStatus() {}

// Range: 0x80164F44 -> 0x80164F4C
unsigned char RemotePlayersProvider::IsMuted() {}

// Range: 0x80164F4C -> 0x80164F54
void RemotePlayersProvider::SetShowMuteStatus() {}

// Range: 0x80164F54 -> 0x801650E0
void RemotePlayersProvider::InitData(class RemotePlayersProvider * const this /* r28 */, class RndDir * dir /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndMat;
}

// Range: 0x801650E0 -> 0x80165244
void RemotePlayersProvider::RefreshUserList(class RemotePlayersProvider * const this /* r28 */) {
    // Local variables
    class vector & users; // r0
    class BandUser * * it; // r29
    class BandUser * pUser; // r30

    // References
    // -> class Net TheNet;
    // -> class NetSession * TheNetSession;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
}

static class Symbol name; // size: 0x4, address: 0x80A4C538
// Range: 0x80165244 -> 0x80165350
char * RemotePlayersProvider::Text(const class RemotePlayersProvider * const this /* r28 */, int data /* r29 */, class Symbol & slot /* r30 */) {
    // References
    // -> static class Symbol name;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol check; // size: 0x4, address: 0x80A4C540
// Range: 0x80165350 -> 0x80165480
class RndMat * RemotePlayersProvider::Mat(const class RemotePlayersProvider * const this /* r28 */, int data /* r29 */, class Symbol & slot /* r30 */) {
    // References
    // -> static class Symbol check;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80165480 -> 0x80165498
int RemotePlayersProvider::NumData() {}

static class Symbol _s; // size: 0x4, address: 0x80A4C548
static class Symbol _s; // size: 0x4, address: 0x80A4C550
static class Symbol _s; // size: 0x4, address: 0x80A4C558
static class Symbol _s; // size: 0x4, address: 0x80A4C560
static class Symbol _s; // size: 0x4, address: 0x80A4C568
static class Symbol _s; // size: 0x4, address: 0x80A4C570
// Range: 0x80165498 -> 0x80165BC0
class DataNode RemotePlayersProvider::Handle(class RemotePlayersProvider * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x34
    class MessageTimer _mt; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x80165BC0 -> 0x80165C44
void * SessionPlayersProvider::SessionPlayersProvider(class SessionPlayersProvider * const this /* r31 */) {
    // References
    // -> class ObjectDir * sMainDir;
    // -> struct [anonymous] __vt__22SessionPlayersProvider;
    // -> struct [anonymous] __vt__12ListProvider;
}

// Range: 0x80165C44 -> 0x80165CB0
void SessionPlayersProvider::Cleanup(class SessionPlayersProvider * const this /* r30 */) {}

// Range: 0x80165CB0 -> 0x80165D30
enum ShowGamercardResult SessionPlayersProvider::ShowGamercard() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80165D30 -> 0x80165D34
void SessionPlayersProvider::InitData() {}

// Range: 0x80165D34 -> 0x80165EA0
void SessionPlayersProvider::RefreshUserList(class SessionPlayersProvider * const this /* r28 */) {
    // Local variables
    class NetSession * session; // r30
    class vector & users; // r0
    class BandUser * * it; // r29
    class BandUser * pUser; // r1+0x18

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class Net TheNet;
}

// Range: 0x80165EA0 -> 0x80165F44
char * SessionPlayersProvider::Text(const class SessionPlayersProvider * const this /* r30 */, int data /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80165F44 -> 0x80165F4C
class RndMat * SessionPlayersProvider::Mat() {}

// Range: 0x80165F4C -> 0x80165F64
int SessionPlayersProvider::NumData() {}

static class Symbol _s; // size: 0x4, address: 0x80A4C578
static class Symbol _s; // size: 0x4, address: 0x80A4C580
static class Symbol _s; // size: 0x4, address: 0x80A4C588
// Range: 0x80165F64 -> 0x801663CC
class DataNode SessionPlayersProvider::Handle(class SessionPlayersProvider * const this /* r29 */, class DataArray * _msg /* r26 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x801663CC -> 0x8016655C
static void KickPlayerMsg::Dispatch() {
    // References
    // -> class BandUI * TheBandUI;
    // -> class Message init;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol disband;
}

// Range: 0x8016655C -> 0x80166560
static void KickPlayerMsg::Load() {}

// Range: 0x80166560 -> 0x80166564
static void KickPlayerMsg::Save() {}

// Range: 0x80166564 -> 0x80166598
static char * KickPlayerMsg::Name() {}

// Range: 0x80166598 -> 0x801665F4
static unsigned char KickPlayerMsg::ByteCode() {
    // References
    // -> class NetMessageFactory TheNetMessageFactory;
}

static struct {
    // total size: 0x28
} __vt__Q224@unnamed@SessionMgr_cpp@13KickPlayerMsg; // size: 0x28, address: 0x808977D0
struct {
    // total size: 0x8
} __RTTI__Q224@unnamed@SessionMgr_cpp@13KickPlayerMsg; // size: 0x8, address: 0x80897830
struct {
    // total size: 0x9C
} __vt__22SessionPlayersProvider; // size: 0x9C, address: 0x808978F0
struct {
    // total size: 0x8
} __RTTI__22SessionPlayersProvider; // size: 0x8, address: 0x808979C0
struct {
    // total size: 0x9C
} __vt__21RemotePlayersProvider; // size: 0x9C, address: 0x808979C8
struct {
    // total size: 0x8
} __RTTI__21RemotePlayersProvider; // size: 0x8, address: 0x80897A98
struct {
    // total size: 0x6C
} __vt__10SessionMgr; // size: 0x6C, address: 0x80897AA0
struct {
    // total size: 0x8
} __RTTI__10SessionMgr; // size: 0x8, address: 0x80897B38
struct {
    // total size: 0xC
} __vt__21LocalLeaderChangedMsg; // size: 0xC, address: 0x80897B40
struct {
    // total size: 0x8
} __RTTI__21LocalLeaderChangedMsg; // size: 0x8, address: 0x80897B70
struct {
    // total size: 0xC
} __vt__18AddPlayerResultMsg; // size: 0xC, address: 0x80897C48
struct {
    // total size: 0x8
} __RTTI__18AddPlayerResultMsg; // size: 0x8, address: 0x80897C78
struct {
    // total size: 0xC
} __vt__15SessionReadyMsg; // size: 0xC, address: 0x80897C80
struct {
    // total size: 0x8
} __RTTI__15SessionReadyMsg; // size: 0x8, address: 0x80897CB0
struct {
    // total size: 0x8
} __RTTI__P10SavePlayer; // size: 0x8, address: 0x80897DE0
struct {
    // total size: 0x8
} __RTTI__PP4User; // size: 0x8, address: 0x80897DF0

