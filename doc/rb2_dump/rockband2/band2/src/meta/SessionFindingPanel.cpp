/*
    Compile unit: C:\rockband2\band2\src\meta\SessionFindingPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8015E5E0 -> 0x80160F94
*/
class DataArray * types; // size: 0x4, address: 0x80A4C418
// Range: 0x8015E5E0 -> 0x8015E680
void * SessionFindingPanel::SessionFindingPanel(class SessionFindingPanel * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__19SessionFindingPanel;
}

// Range: 0x8015E680 -> 0x8015E68C
void SessionFindingPanel::SetJoiningPresence() {}

static class Symbol join_result; // size: 0x4, address: 0x80A4C420
static class Symbol processed_join_request; // size: 0x4, address: 0x80A4C428
static class Message check_disconnect; // size: 0x8, address: 0x80979B20
// Range: 0x8015E68C -> 0x8015E930
void SessionFindingPanel::Enter(class SessionFindingPanel * const this /* r30 */) {
    // References
    // -> class NetSync * TheNetSync;
    // -> static class Message check_disconnect;
    // -> struct [anonymous] __vt__7Message;
    // -> static class Symbol processed_join_request;
    // -> class NetSession * TheNetSession;
    // -> static class Symbol join_result;
    // -> class SessionMgr * TheSessionMgr;
    // -> const char * gNullStr;
    // -> class Symbol t;
}

static class Symbol join_result; // size: 0x4, address: 0x80A4C430
static class Symbol processed_join_request; // size: 0x4, address: 0x80A4C438
// Range: 0x8015E930 -> 0x8015EA8C
void SessionFindingPanel::Exit(class SessionFindingPanel * const this /* r30 */) {
    // References
    // -> static class Symbol processed_join_request;
    // -> class NetSession * TheNetSession;
    // -> static class Symbol join_result;
    // -> class Symbol t;
    // -> class SessionMgr * TheSessionMgr;
}

static class Message set_presence; // size: 0x8, address: 0x80979B38
// Range: 0x8015EA8C -> 0x8015EFC4
void SessionFindingPanel::SetPresenceInfo(class SessionFindingPanel * const this /* r28 */, enum PresenceInfo presence /* r29 */, const class JoinResultMsg * msg /* r30 */) {
    // Local variables
    class Symbol token; // r1+0x48

    // References
    // -> class GameMode * TheGameMode;
    // -> const char * gNullStr;
    // -> static class Message set_presence;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Message manual_retry; // size: 0x8, address: 0x80979B50
static class Message enable_retry; // size: 0x8, address: 0x80979B68
static class Message exit_due_to_error; // size: 0x8, address: 0x80979B80
// Range: 0x8015EFC4 -> 0x8015F4D8
void SessionFindingPanel::StartBuildingSession(class SessionFindingPanel * const this /* r27 */) {
    // Local variables
    unsigned char validController; // r28
    enum ControllerType controller; // r26

    // References
    // -> static class Message exit_due_to_error;
    // -> static class Message enable_retry;
    // -> static class Message manual_retry;
    // -> struct [anonymous] __vt__7Message;
    // -> class SessionMgr * TheSessionMgr;
    // -> class PlatformMgr ThePlatformMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class NetSession * TheNetSession;
}

static class Message save_user_settings; // size: 0x8, address: 0x80979B98
static class Message join_invited_session; // size: 0x8, address: 0x80979BB0
static class Message exit_due_to_error; // size: 0x8, address: 0x80979BC8
// Range: 0x8015F4D8 -> 0x8015F8E4
void SessionFindingPanel::OnSessionBuilt(class SessionFindingPanel * const this /* r29 */) {
    // References
    // -> static class Message exit_due_to_error;
    // -> static class Message join_invited_session;
    // -> static class Message save_user_settings;
    // -> struct [anonymous] __vt__7Message;
    // -> class BandUserMgr * TheBandUserMgr;
}

static class Message forceNonLeader; // size: 0x8, address: 0x80979BE0
// Range: 0x8015F8E4 -> 0x8015FA7C
void SessionFindingPanel::StartSearching(class SessionFindingPanel * const this /* r31 */) {
    // References
    // -> static class Message forceNonLeader;
    // -> struct [anonymous] __vt__7Message;
    // -> class SessionMgr * TheSessionMgr;
}

static class Message matchmaker_update; // size: 0x8, address: 0x80979BF8
// Range: 0x8015FA7C -> 0x8015FC00
void SessionFindingPanel::JoinInvite(class SessionFindingPanel * const this /* r31 */) {
    // References
    // -> static class Message matchmaker_update;
    // -> struct [anonymous] __vt__7Message;
    // -> class NetSession * TheNetSession;
    // -> class Net TheNet;
    // -> class SessionMgr * TheSessionMgr;
}

static class Message manual_retry; // size: 0x8, address: 0x80979C10
static class Message advance_when_joined; // size: 0x8, address: 0x80979C28
static class Message advance; // size: 0x8, address: 0x80979C40
static class Message enable_retry; // size: 0x8, address: 0x80979C58
// Range: 0x8015FC00 -> 0x80160120
class DataNode SessionFindingPanel::OnMsg(class SessionFindingPanel * const this /* r28 */, const class JoinResultMsg & msg /* r29 */) {
    // References
    // -> static class Message enable_retry;
    // -> static class Message advance;
    // -> static class Message advance_when_joined;
    // -> static class Message manual_retry;
    // -> struct [anonymous] __vt__7Message;
}

static class Message advance_when_joined; // size: 0x8, address: 0x80979C70
static class Message advance; // size: 0x8, address: 0x80979C88
// Range: 0x80160120 -> 0x801603F4
class DataNode SessionFindingPanel::OnMsg(class SessionFindingPanel * const this /* r29 */, const class ProcessedJoinRequestMsg & msg /* r30 */) {
    // References
    // -> static class Message advance;
    // -> static class Message advance_when_joined;
    // -> struct [anonymous] __vt__7Message;
}

static class Symbol _s; // size: 0x4, address: 0x80A4C44C
static class Symbol _s; // size: 0x4, address: 0x80A4C454
static class Symbol _s; // size: 0x4, address: 0x80A4C45C
static class Symbol _s; // size: 0x4, address: 0x80A4C464
static class Symbol _s; // size: 0x4, address: 0x80A4C46C
static class Symbol _s; // size: 0x4, address: 0x80A4C474
// Range: 0x801603F4 -> 0x80160F94
class DataNode SessionFindingPanel::Handle(class SessionFindingPanel * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x48
    class MessageTimer _mt; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode r; // r1+0x68
    class DataNode _n; // r1+0x60

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> struct [anonymous] __vt__23ProcessedJoinRequestMsg;
    // -> class Symbol t;
    // -> struct [anonymous] __vt__13JoinResultMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8BandUser;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0xAC
} __vt__19SessionFindingPanel; // size: 0xAC, address: 0x808971D0
struct {
    // total size: 0x8
} __RTTI__19SessionFindingPanel; // size: 0x8, address: 0x808972B0

