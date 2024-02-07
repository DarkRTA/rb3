/*
    Compile unit: C:\rockband2\band2\src\meta\SigninScreen.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80168494 -> 0x80169974
*/
class Symbol t; // size: 0x4, address: 0x80A4C5DC
class DataArray * types; // size: 0x4, address: 0x80A4C5E0
// Range: 0x80168494 -> 0x801684EC
void * SigninScreen::SigninScreen(class SigninScreen * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__12SigninScreen;
}

// Range: 0x801684EC -> 0x80168564
void * SigninScreen::~SigninScreen(class SigninScreen * const this /* r30 */) {}

// Range: 0x80168564 -> 0x80168568
void SigninScreen::Poll() {}

static class Symbol limit_user_signin; // size: 0x4, address: 0x80A4C5E8
static class Symbol must_not_be_a_guest; // size: 0x4, address: 0x80A4C5F0
static class Symbol must_be_online; // size: 0x4, address: 0x80A4C5F8
static class Symbol must_be_multiplayer_capable; // size: 0x4, address: 0x80A4C600
static class Symbol handle_sign_outs; // size: 0x4, address: 0x80A4C608
// Range: 0x80168568 -> 0x801687D4
void SigninScreen::Enter(class SigninScreen * const this /* r30 */) {
    // Local variables
    class BandUser * pUser; // r0

    // References
    // -> static class Symbol handle_sign_outs;
    // -> static class Symbol must_be_multiplayer_capable;
    // -> static class Symbol must_be_online;
    // -> static class Symbol must_not_be_a_guest;
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
    // -> class InputMgr * TheInputMgr;
    // -> static class Symbol limit_user_signin;
    // -> class PlatformMgr ThePlatformMgr;
    // -> const char * gNullStr;
}

// Range: 0x801687D4 -> 0x80168834
void SigninScreen::Exit(class SigninScreen * const this /* r30 */, class UIScreen * to /* r31 */) {
    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> const char * gNullStr;
}

static class Message msg; // size: 0x8, address: 0x80979D18
// Range: 0x80168834 -> 0x80168A80
void SigninScreen::ReEvaluateState(class SigninScreen * const this /* r31 */) {
    // Local variables
    class BandUser * pUser; // r29
    unsigned char triggerSignedIn; // r28

    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class PlatformMgr ThePlatformMgr;
    // -> class InputMgr * TheInputMgr;
}

static class Message msg; // size: 0x8, address: 0x80979D30
static class Message msg; // size: 0x8, address: 0x80979D48
static class Message msg; // size: 0x8, address: 0x80979D60
static class Message msg; // size: 0x8, address: 0x80979D78
// Range: 0x80168A80 -> 0x80169194
class DataNode SigninScreen::OnMsg(class SigninScreen * const this /* r25 */, const class SigninChangedMsg & msg /* r26 */) {
    // Local variables
    int bestState; // r1+0x28
    const class vector & users; // r0
    class BandUser * const * it; // r28
    const class BandUser * pUser; // r27
    unsigned long userMask; // r22
    unsigned char isSignedIn; // r0

    // References
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class PlatformMgr ThePlatformMgr;
    // -> class InputMgr * TheInputMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
}

static class Message msg; // size: 0x8, address: 0x80979D90
// Range: 0x80169194 -> 0x80169374
class DataNode SigninScreen::OnMsg(class SigninScreen * const this /* r31 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class PlatformMgr ThePlatformMgr;
    // -> class InputMgr * TheInputMgr;
}

// Range: 0x80169374 -> 0x80169974
class DataNode SigninScreen::Handle(class SigninScreen * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x30
    class MessageTimer _mt; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode r; // r1+0x50
    class DataNode _n; // r1+0x48

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__12UIChangedMsg;
    // -> class Symbol t;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __vt__16SigninChangedMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x80
} __vt__12SigninScreen; // size: 0x80, address: 0x80898448
struct {
    // total size: 0x8
} __RTTI__12SigninScreen; // size: 0x8, address: 0x80898500
struct {
    // total size: 0xC
} __vt__12UIChangedMsg; // size: 0xC, address: 0x80898538
struct {
    // total size: 0x8
} __RTTI__12UIChangedMsg; // size: 0x8, address: 0x80898560

