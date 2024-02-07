/*
    Compile unit: C:\rockband2\band2\src\meta\PassiveMessenger.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8013B76C -> 0x8013C4FC
*/
class ReadyForTourMsg : public NetMessage {
    // total size: 0x14
    enum NetUIState mReadyState; // offset 0x4, size 0x4
    class String mName; // offset 0x8, size 0xC
};
// Range: 0x8013B76C -> 0x8013B7BC
static class NetMessage * ReadyForTourMsg::NewNetMessage() {
    // References
    // -> static struct [anonymous] __vt__Q230@unnamed@PassiveMessenger_cpp@15ReadyForTourMsg;
}

// Range: 0x8013B7BC -> 0x8013B814
static void ReadyForTourMsg::Save(const class ReadyForTourMsg * const this /* r30 */, class BinStream & dest /* r31 */) {}

// Range: 0x8013B814 -> 0x8013B86C
static void ReadyForTourMsg::Load(class ReadyForTourMsg * const this /* r30 */, class BinStream & src /* r31 */) {
    // Local variables
    int ready; // r1+0x8
}

static class Symbol passive_message_ready_world_tour; // size: 0x4, address: 0x80A4BEFC
static class Symbol passive_message_ready_set_challenges; // size: 0x4, address: 0x80A4BF04
static class Symbol passive_message_ready_battle_of_the_bands; // size: 0x4, address: 0x80A4BF0C
// Range: 0x8013B86C -> 0x8013BA08
static void ReadyForTourMsg::Dispatch(class ReadyForTourMsg * const this /* r31 */) {
    // Local variables
    const char * waiting_screen; // r29
    class Symbol token; // r1+0xC
    const char * msg; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
    // -> static class Symbol passive_message_ready_battle_of_the_bands;
    // -> static class Symbol passive_message_ready_set_challenges;
    // -> static class Symbol passive_message_ready_world_tour;
    // -> class UIManager TheUI;
}

static class Symbol is_h2h_arrangement; // size: 0x4, address: 0x80A4BF14
// Range: 0x8013BA08 -> 0x8013BB10
static unsigned char ShouldDisplaySessionMessages() {
    // References
    // -> class GameMode * TheGameMode;
    // -> static class Symbol is_h2h_arrangement;
    // -> struct [anonymous] __RTTI__8UIScreen;
    // -> struct [anonymous] __RTTI__17MatchmakingScreen;
    // -> class UIManager TheUI;
    // -> class NetSession * TheNetSession;
}

class PassiveMessenger * ThePassiveMessenger; // size: 0x4, address: 0x80A4BF18
// Range: 0x8013BB10 -> 0x8013BBCC
void * PassiveMessenger::PassiveMessenger(class PassiveMessenger * const this /* r30 */) {
    // References
    // -> class NetMessageFactory TheNetMessageFactory;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class PassiveMessenger * ThePassiveMessenger;
    // -> struct [anonymous] __vt__16PassiveMessenger;
}

// Range: 0x8013BBCC -> 0x8013BC74
void * PassiveMessenger::~PassiveMessenger(class PassiveMessenger * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class PassiveMessenger * ThePassiveMessenger;
    // -> struct [anonymous] __vt__16PassiveMessenger;
}

// Range: 0x8013BC74 -> 0x8013BDA4
void PassiveMessenger::Poll(class PassiveMessenger * const this /* r31 */) {
    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
}

// Range: 0x8013BDA4 -> 0x8013BE78
void PassiveMessenger::BroadcastReadyForTourMsg(class PassiveMessenger * const this /* r29 */) {
    // Local variables
    enum NetUIState state; // r30
    class ReadyForTourMsg msg; // r1+0x8

    // References
    // -> class NetSession * TheNetSession;
    // -> class Debug TheDebug;
    // -> class NetSync * TheNetSync;
}

static class Symbol passive_message_member_join_failed; // size: 0x4, address: 0x80A4BF20
// Range: 0x8013BED8 -> 0x8013BF44
void PassiveMessenger::TriggerMemberJoinFailedMsg() {
    // Local variables
    const char * msg; // r31

    // References
    // -> static class Symbol passive_message_member_join_failed;
}

static class Symbol passive_message_auto_join_failed; // size: 0x4, address: 0x80A4BF28
// Range: 0x8013BF44 -> 0x8013BFB0
void PassiveMessenger::TriggerAutoJoinFailedMsg() {
    // Local variables
    const char * msg; // r31

    // References
    // -> static class Symbol passive_message_auto_join_failed;
}

// Range: 0x8013BFB0 -> 0x8013C024
void PassiveMessenger::ProcessNewRemotePlayerMsg(class PassiveMessenger * const this /* r30 */, const class NewRemotePlayerMsg & msg /* r31 */) {
    // Local variables
    class BandUser * user; // r0

    // References
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x8013C024 -> 0x8013C098
void PassiveMessenger::ProcessRemotePlayerLeftMsg(class PassiveMessenger * const this /* r30 */, const class RemotePlayerLeftMsg & msg /* r31 */) {
    // Local variables
    class BandUser * user; // r0

    // References
    // -> class BandUserMgr * TheBandUserMgr;
}

static class Symbol passive_message_new_remote_user; // size: 0x4, address: 0x80A4BF30
// Range: 0x8013C098 -> 0x8013C114
void PassiveMessenger::TriggerNewRemoteUserMsg(const char * userName /* r31 */) {
    // Local variables
    class Symbol token; // r1+0xC
    const char * msg; // r31

    // References
    // -> static class Symbol passive_message_new_remote_user;
}

static class Symbol passive_message_remote_user_left; // size: 0x4, address: 0x80A4BF38
// Range: 0x8013C114 -> 0x8013C190
void PassiveMessenger::TriggerRemoteUserLeftMsg(const char * userName /* r31 */) {
    // Local variables
    class Symbol token; // r1+0xC
    const char * msg; // r31

    // References
    // -> static class Symbol passive_message_remote_user_left;
}

static class Symbol passive_message_game_invite_received; // size: 0x4, address: 0x80A4BF40
// Range: 0x8013C190 -> 0x8013C1FC
void PassiveMessenger::TriggerGameInviteReceivedMsg() {
    // References
    // -> static class Symbol passive_message_game_invite_received;
}

static class Symbol _s; // size: 0x4, address: 0x80A4BF48
// Range: 0x8013C1FC -> 0x8013C46C
class DataNode PassiveMessenger::Handle(class PassiveMessenger * const this /* r29 */, class DataArray * _msg /* r31 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x20
    class MessageTimer _mt; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x8013C46C -> 0x8013C4A0
static char * ReadyForTourMsg::Name() {}

// Range: 0x8013C4A0 -> 0x8013C4FC
static unsigned char ReadyForTourMsg::ByteCode() {
    // References
    // -> class NetMessageFactory TheNetMessageFactory;
}

static struct {
    // total size: 0x28
} __vt__Q230@unnamed@PassiveMessenger_cpp@15ReadyForTourMsg; // size: 0x28, address: 0x80892488
struct {
    // total size: 0x8
} __RTTI__Q230@unnamed@PassiveMessenger_cpp@15ReadyForTourMsg; // size: 0x8, address: 0x808924F0
struct {
    // total size: 0x54
} __vt__16PassiveMessenger; // size: 0x54, address: 0x80892680
struct {
    // total size: 0x8
} __RTTI__16PassiveMessenger; // size: 0x8, address: 0x80892700

