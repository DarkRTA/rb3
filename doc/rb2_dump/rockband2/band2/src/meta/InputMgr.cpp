/*
    Compile unit: C:\rockband2\band2\src\meta\InputMgr.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800F7230 -> 0x800FA9D4
*/
class Symbol t; // size: 0x4, address: 0x80A4B1CC
class Symbol t; // size: 0x4, address: 0x80A4B1D4
class InputMgr * TheInputMgr; // size: 0x4, address: 0x80A4B1D8
// Range: 0x800F7230 -> 0x800F7314
void InputMgr::Init() {
    // References
    // -> class BandUI * TheBandUI;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class InputMgr * TheInputMgr;
}

// Range: 0x800F7314 -> 0x800F735C
void InputMgr::Terminate() {
    // References
    // -> class InputMgr * TheInputMgr;
}

static class Symbol session_busy; // size: 0x4, address: 0x80A4B1E0
// Range: 0x800F735C -> 0x800F7538
void * InputMgr::InputMgr(class InputMgr * const this /* r29 */, class BandUserMgr & bum /* r30 */, class BandUI * bu /* r31 */) {
    // Local variables
    int i; // r4

    // References
    // -> class NetSession * TheNetSession;
    // -> const char * gNullStr;
    // -> static class Symbol session_busy;
    // -> class ObjectDir * sMainDir;
    // -> struct [anonymous] __vt__8InputMgr;
    // -> struct [anonymous] __vt__9MsgSource;
}

static class Symbol session_busy; // size: 0x4, address: 0x80A4B1E8
// Range: 0x800F7538 -> 0x800F7624
void * InputMgr::~InputMgr(class InputMgr * const this /* r29 */) {
    // References
    // -> class NetSession * TheNetSession;
    // -> static class Symbol session_busy;
    // -> struct [anonymous] __vt__8InputMgr;
}

// Range: 0x800F7624 -> 0x800F77E4
unsigned char InputMgr::IsActiveAndConnected(const class InputMgr * const this /* r25 */, enum ControllerType ct /* r26 */) {
    // Local variables
    unsigned char allow_remote_exit; // r0
    class vector & users; // r0
    class BandUser * * u; // r28
    class BandUser * user; // r27

    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800F77E4 -> 0x800F77EC
class BandUser * InputMgr::GetUser() {}

// Range: 0x800F77EC -> 0x800F77FC
void InputMgr::Reset() {}

// Range: 0x800F77FC -> 0x800F7804
void InputMgr::SetNetworkBusy() {}

// Range: 0x800F7804 -> 0x800F7824
class DataNode InputMgr::OnMsg() {
    // References
    // -> class NetSession * TheNetSession;
}

// Range: 0x800F7824 -> 0x800F78BC
void InputMgr::SetLimit(class InputMgr * const this /* r30 */, enum InputLimitType t /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800F78BC -> 0x800F78F8
void InputMgr::SetUser(class InputMgr * const this /* r31 */) {}

static class Symbol fake_controllers; // size: 0x4, address: 0x80A4B1F0
static class Symbol pad_lost; // size: 0x4, address: 0x80A4B1F8
static class Message init; // size: 0x8, address: 0x80978B78
// Range: 0x800F78F8 -> 0x800F7E2C
unsigned char InputMgr::CheckControllers(class InputMgr * const this /* r29 */, unsigned char tryReconnect /* r25 */) {
    // Local variables
    class vector & users; // r0
    class BandUser * * u; // r26
    class BandUser * user; // r30
    int padNum; // r26

    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> static class Message init;
    // -> struct [anonymous] __vt__7Message;
    // -> const char * gNullStr;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol pad_lost;
    // -> static class Symbol fake_controllers;
}

// Range: 0x800F7E2C -> 0x800F7E34
void InputMgr::SetInvalidMessageSink() {}

// Range: 0x800F7E34 -> 0x800F7E40
void InputMgr::ClearInvalidMessageSink() {}

// Range: 0x800F7E40 -> 0x800F7F50
unsigned char InputMgr::AllowRemoteExit(const class InputMgr * const this /* r28 */) {
    // References
    // -> class NetSync * TheNetSync;
    // -> const char * gNullStr;
}

// Range: 0x800F7F50 -> 0x800F7FA8
class DataNode InputMgr::OnMsg(class InputMgr * const this /* r31 */) {}

static class Message msg; // size: 0x8, address: 0x80978B90
static class Symbol remote_exit; // size: 0x4, address: 0x80A4B200
static class Message msg; // size: 0x8, address: 0x80978BA8
static class ButtonDownMsg new_msg; // size: 0x8, address: 0x80978BC0
// Range: 0x800F7FA8 -> 0x800F8840
class DataNode InputMgr::OnMsg(class InputMgr * const this /* r27 */, const class ButtonDownMsg & msg /* r28 */) {
    // Local variables
    class DataNode res; // r1+0x68
    class BandUser * bu; // r0
    class BandUser * user; // r25
    class DataNode ret; // r1+0x60
    enum JoypadAction filtered; // r0

    // References
    // -> static class ButtonDownMsg new_msg;
    // -> static class Message msg;
    // -> class BandUI * TheBandUI;
    // -> static class Symbol remote_exit;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class UIManager TheUI;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

static class ButtonUpMsg new_msg; // size: 0x8, address: 0x80978BD8
// Range: 0x800F8840 -> 0x800F8C24
class DataNode InputMgr::OnMsg(class InputMgr * const this /* r29 */, const class ButtonUpMsg & msg /* r30 */) {
    // Local variables
    enum JoypadAction filtered; // r0

    // References
    // -> class UIManager TheUI;
    // -> static class ButtonUpMsg new_msg;
}

// Range: 0x800F8C24 -> 0x800F8C2C
enum JoypadAction InputMgr::FilterAction() {}

// Range: 0x800F8C2C -> 0x800F8D90
unsigned char InputMgr::IsDoubleStrum(class InputMgr * const this /* r31 */, int user /* r27 */) {
    // Local variables
    float dt; // f31

    // References
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
}

class InputLimitChangedMsg : public Message {
    // total size: 0x8
};
static class InputLimitChangedMsg msg; // size: 0x8, address: 0x80978BF0
// Range: 0x800F8D90 -> 0x800F8EDC
void InputMgr::ExportLimitChangedMsg(class InputMgr * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__20InputLimitChangedMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class InputLimitChangedMsg msg;
}

static class InputStatusChangedMsg msg; // size: 0x8, address: 0x80978C08
// Range: 0x800F8F60 -> 0x800F90AC
void InputMgr::ExportStatusChangedMsg(class InputMgr * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__21InputStatusChangedMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class InputStatusChangedMsg msg;
}

static class Symbol wii_roguitar; // size: 0x4, address: 0x80A4B20C
static class Symbol wii_rodrums; // size: 0x4, address: 0x80A4B214
static class Symbol joypad; // size: 0x4, address: 0x80A4B21C
static class Symbol instrument_mapping; // size: 0x4, address: 0x80A4B224
// Range: 0x800F90AC -> 0x800F9614
unsigned char InputMgr::HasValidController(const class InputMgr * const this /* r25 */, class BandUser * user /* r23 */, enum ControllerType t /* r24 */, unsigned char tryReconnect /* r22 */) {
    // Local variables
    enum ControllerType user_type; // r0
    unsigned char swapped; // r28
    unsigned char hasRemotePlayers; // r27
    class vector & users; // r0
    class BandUser * * u; // r26
    class BandUser * newUser; // r25
    class Symbol controller; // r1+0x34
    class DataArray * cfg; // r0
    class DataArray * data; // r22
    enum ControllerType remoteControllerType; // r0
    int i; // r25
    class JoypadData * padData; // r0
    class Symbol controller; // r1+0x30
    class DataArray * cfg; // r0
    class DataArray * data; // r22
    enum ControllerType unclaimedControllerType; // r0

    // References
    // -> static class Symbol instrument_mapping;
    // -> static class Symbol joypad;
    // -> static class Symbol wii_rodrums;
    // -> static class Symbol wii_roguitar;
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800F9614 -> 0x800F9778
unsigned char InputMgr::AllowInput(const class InputMgr * const this /* r28 */, int user_num /* r29 */, unsigned char allow_invalid_user /* r30 */) {
    // Local variables
    class BandUser * user; // r4

    // References
    // -> class GameMode * TheGameMode;
    // -> const char * gNullStr;
}

// Range: 0x800F9778 -> 0x800F9840
unsigned char InputMgr::AllowInSession(const class InputMgr * const this /* r30 */, class BandUser * user /* r31 */) {
    // Local variables
    int leaderNum; // r4

    // References
    // -> class SessionMgr * TheSessionMgr;
}

static class Symbol _s; // size: 0x4, address: 0x80A4B22C
static class Symbol _s; // size: 0x4, address: 0x80A4B234
static class Symbol _s; // size: 0x4, address: 0x80A4B23C
static class Symbol _s; // size: 0x4, address: 0x80A4B244
static class Symbol _s; // size: 0x4, address: 0x80A4B24C
static class Symbol _s; // size: 0x4, address: 0x80A4B254
static class Symbol _s; // size: 0x4, address: 0x80A4B25C
static class Symbol _s; // size: 0x4, address: 0x80A4B264
static class Symbol _s; // size: 0x4, address: 0x80A4B26C
// Range: 0x800F9840 -> 0x800FA9D4
class DataNode InputMgr::Handle(class InputMgr * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x64
    class MessageTimer _mt; // r1+0xB0
    class DataNode r; // r1+0xA8
    class DataNode r; // r1+0xA0
    class DataNode r; // r1+0x98
    class DataNode r; // r1+0x90
    class DataNode _n; // r1+0x88

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8BandUser;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> struct [anonymous] __vt__14SessionBusyMsg;
    // -> class Symbol t;
    // -> struct [anonymous] __vt__11ButtonUpMsg;
    // -> class Symbol t;
    // -> struct [anonymous] __vt__13ButtonDownMsg;
    // -> class Symbol t;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __vt__19JoypadConnectionMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> unsigned char sActive;
}

struct {
    // total size: 0xC
} __vt__14SessionBusyMsg; // size: 0xC, address: 0x80888364
struct {
    // total size: 0x8
} __RTTI__14SessionBusyMsg; // size: 0x8, address: 0x80888390
struct {
    // total size: 0x6C
} __vt__8InputMgr; // size: 0x6C, address: 0x80888488
struct {
    // total size: 0x8
} __RTTI__8InputMgr; // size: 0x8, address: 0x80888520
struct {
    // total size: 0xC
} __vt__20InputLimitChangedMsg; // size: 0xC, address: 0x80888528
struct {
    // total size: 0x8
} __RTTI__20InputLimitChangedMsg; // size: 0x8, address: 0x80888558

