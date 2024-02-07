/*
    Compile unit: C:\rockband2\system\src\os\Joypad.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805B6454 -> 0x805BA124
*/
int kNonUser; // size: 0x4, address: 0x80A57DB0
static float kAnalogRestPos; // size: 0x4, address: 0x80A58AA8
static class DataArray * gControllersCfg; // size: 0x4, address: 0x80A549E0
static class DataArray * gButtonMeanings; // size: 0x4, address: 0x80A549E4
static class JoypadData gJoypadData[8]; // size: 0x340, address: 0x809854C0
static unsigned char gJoypadDisabled[8]; // size: 0x8, address: 0x80985800
static class MsgSource gJoypadMsgSource; // size: 0x48, address: 0x80985818
static unsigned char gJoypadLibInitialized; // size: 0x1, address: 0x80A549E8
static unsigned char gExportMsgs; // size: 0x1, address: 0x80A47818
static unsigned char gReservedUserNums[4]; // size: 0x4, address: 0x80A549EC
static unsigned int gNotifyMask; // size: 0x4, address: 0x80A4781C
static int gFakeUser1; // size: 0x4, address: 0x80A549F0
// Range: 0x805B6454 -> 0x805B64BC
static class DataNode SetFakeUser1(class DataArray * a /* r31 */) {
    // References
    // -> static int gFakeUser1;
    // -> static class JoypadData gJoypadData[8];
}

// Range: 0x805B64BC -> 0x805B64D0
static class DataNode FakeUser1() {
    // References
    // -> static int gFakeUser1;
}

// Range: 0x805B64D0 -> 0x805B6528
static class DataNode OnJoypadGetUsersPadNum(class DataArray * args /* r31 */) {}

// Range: 0x805B6528 -> 0x805B6580
static class DataNode OnJoypadGetUserFromPadNum(class DataArray * args /* r31 */) {}

// Range: 0x805B6580 -> 0x805B65DC
static class DataNode OnJoypadControllerType(class DataArray * args /* r31 */) {}

// Range: 0x805B65DC -> 0x805B6634
static class DataNode OnJoypadIsConnected(class DataArray * args /* r31 */) {}

// Range: 0x805B6634 -> 0x805B66F0
static class DataNode OnJoypadGetLX(class DataArray * args /* r31 */) {
    // Local variables
    int pad; // r0

    // References
    // -> static class JoypadData gJoypadData[8];
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805B66F0 -> 0x805B67AC
static class DataNode OnJoypadGetLY(class DataArray * args /* r31 */) {
    // Local variables
    int pad; // r0

    // References
    // -> static class JoypadData gJoypadData[8];
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805B67AC -> 0x805B6868
static class DataNode OnJoypadGetRX(class DataArray * args /* r31 */) {
    // Local variables
    int pad; // r0

    // References
    // -> static class JoypadData gJoypadData[8];
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805B6868 -> 0x805B6924
static class DataNode OnJoypadGetRY(class DataArray * args /* r31 */) {
    // Local variables
    int pad; // r0

    // References
    // -> static class JoypadData gJoypadData[8];
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805B6924 -> 0x805B69E0
static class DataNode OnJoypadGetTL(class DataArray * args /* r31 */) {
    // Local variables
    int pad; // r0

    // References
    // -> static class JoypadData gJoypadData[8];
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805B69E0 -> 0x805B6A9C
static class DataNode OnJoypadGetTR(class DataArray * args /* r31 */) {
    // Local variables
    int pad; // r0

    // References
    // -> static class JoypadData gJoypadData[8];
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805B6A9C -> 0x805B6B88
static class DataNode OnJoypadIsButtonDown(class DataArray * args /* r30 */) {
    // Local variables
    int pad; // r0

    // References
    // -> static class JoypadData gJoypadData[8];
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805B6B88 -> 0x805B6BE0
static class DataNode OnJoypadIsCalbertGuitar(class DataArray * args /* r31 */) {
    // Local variables
    unsigned char isCalbert; // r0
}

static class Symbol type; // size: 0x4, address: 0x80A549F8
static class Symbol button; // size: 0x4, address: 0x80A54A00
static class Symbol stick; // size: 0x4, address: 0x80A54A08
static class Symbol trigger; // size: 0x4, address: 0x80A54A10
static class Symbol X; // size: 0x4, address: 0x80A54A18
static class Symbol Y; // size: 0x4, address: 0x80A54A20
// Range: 0x805B6BE0 -> 0x805B6EB4
static unsigned char IsJoypadDetectMatch(class DataArray * detect_cfg /* r28 */, const class JoypadData & data /* r29 */) {
    // Local variables
    int i; // r30
    int axis; // r25
    class Symbol axis_sym; // r1+0x1C

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol Y;
    // -> static class Symbol X;
    // -> static class Symbol trigger;
    // -> static class Symbol stick;
    // -> static class Symbol button;
    // -> static class Symbol type;
}

// Range: 0x805B6EB4 -> 0x805B6EEC
static class DataNode DataJoypadReset() {}

// Range: 0x805B6EEC -> 0x805B6F8C
void * JoypadData::JoypadData() {
    // Local variables
    int k; // r5
    int j; // r6
    int i; // r5

    // References
    // -> const char * gNullStr;
}

static class Symbol lx; // size: 0x4, address: 0x80A54A28
static class Symbol ly; // size: 0x4, address: 0x80A54A30
static class Symbol rx; // size: 0x4, address: 0x80A54A38
static class Symbol ry; // size: 0x4, address: 0x80A54A40
static class Symbol tl; // size: 0x4, address: 0x80A54A48
static class Symbol tr; // size: 0x4, address: 0x80A54A50
static class Symbol sx; // size: 0x4, address: 0x80A54A58
static class Symbol sy; // size: 0x4, address: 0x80A54A60
static class Symbol sz; // size: 0x4, address: 0x80A54A68
// Range: 0x805B6F8C -> 0x805B71C4
float JoypadData::GetAxis(const class JoypadData * const this /* r30 */, class Symbol & axis /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> static class Symbol sz;
    // -> static class Symbol sy;
    // -> static class Symbol sx;
    // -> static class Symbol tr;
    // -> static class Symbol tl;
    // -> static class Symbol ry;
    // -> static class Symbol rx;
    // -> static class Symbol ly;
    // -> static class Symbol lx;
}

// Range: 0x805B71C4 -> 0x805B7244
int JoypadData::FloatToBucket() {}

// Range: 0x805B7244 -> 0x805B7284
int JoypadData::GetVelocityBucket(const class JoypadData * const this /* r31 */) {
    // Local variables
    float val; // f0
}

// Range: 0x805B7284 -> 0x805B7300
int JoypadData::GetPressureBucket(const class JoypadData * const this /* r30 */, enum JoypadButton b /* r31 */) {
    // Local variables
    float val; // f1

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol LX; // size: 0x4, address: 0x80A54A70
static class Symbol LY; // size: 0x4, address: 0x80A54A78
static class Symbol RX; // size: 0x4, address: 0x80A54A80
static class Symbol RY; // size: 0x4, address: 0x80A54A88
// Range: 0x805B7300 -> 0x805B74C8
int ButtonToVelocityBucket(class JoypadData * data /* r31 */, enum JoypadButton b /* r30 */) {
    // References
    // -> static class Symbol RY;
    // -> static class Symbol RX;
    // -> static class Symbol LY;
    // -> static class Symbol LX;
}

// Range: 0x805B74C8 -> 0x805B77D0
void JoypadInitCommon(const class DataArray * joypad_config /* r27 */) {
    // Local variables
    float threshold; // r1+0x54
    int i; // r29
    const class DataArray * ignores; // r28

    // References
    // -> static unsigned char gJoypadLibInitialized;
    // -> static class DataArray * gButtonMeanings;
    // -> static class DataArray * gControllersCfg;
    // -> static unsigned char gReservedUserNums[4];
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static unsigned char gJoypadDisabled[8];
    // -> static class JoypadData gJoypadData[8];
}

class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x805B77D0 -> 0x805B7B14
unsigned int JoypadWaitForButton(unsigned char start_only /* r30 */) {
    // Local variables
    class vector active; // r1+0x50
    int i; // r31
    struct WaitInfo * i; // r4
    int mask; // r0
    int cur; // r31

    // References
    // -> static unsigned int gNotifyMask;
    // -> static unsigned char gExportMsgs;
    // -> static unsigned char gJoypadDisabled[8];
    // -> const char * gNullStr;
    // -> static class JoypadData gJoypadData[8];
    // -> static unsigned char gJoypadLibInitialized;
}

class StlNodeAlloc {
    // total size: 0x1
};
struct WaitInfo {
    // total size: 0x8
    int pad; // offset 0x0, size 0x4
    int old; // offset 0x4, size 0x4
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct WaitInfo * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct WaitInfo * _M_start; // offset 0x0, size 0x4
    struct WaitInfo * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
static class Symbol hx_kick_xbox; // size: 0x4, address: 0x80A54A90
static class Symbol translate_sticks; // size: 0x4, address: 0x80A54A98
static class Symbol unknown; // size: 0x4, address: 0x80A54AA0
static class Symbol ignore_buttons; // size: 0x4, address: 0x80A54AA8
enum AnalogStickID {
    kLeftAnalog = 0,
    kRightAnalog = 1,
    kNumAnalogSticks = 2,
};
struct ButtonVelocity {
    // total size: 0x8
    enum JoypadButton mButton; // offset 0x0, size 0x4
    int mBucket; // offset 0x4, size 0x4
};
// Range: 0x805B7B14 -> 0x805B8958
void JoypadPollCommon() {
    // Local variables
    int padType; // r0
    char sticks[2][2]; // r1+0x50
    char triggers[2]; // r1+0x14
    float sensors[3]; // r1+0xE8
    float pressures[8]; // r1+0x118
    unsigned int currButtons; // r1+0x4C
    int i; // r27
    enum AnalogStickID k; // r6
    int s; // r4
    int p; // r4
    unsigned char justDisconnected; // r26
    unsigned char justConnected; // r25
    enum AnalogStickID k; // r4
    int t; // r4
    int s; // r4
    int p; // r4
    class Symbol type; // r1+0x48
    unsigned char translate; // r1+0x10
    class DataArray * type_array; // r0
    class DataArray * ignores; // r19
    int i; // r20
    unsigned int newBtnDowns; // r24
    unsigned int newBtnUps; // r23
    unsigned char ignore_dup_and_down; // r22
    struct ButtonVelocity button_velocities[4]; // r1+0xF8
    int user; // r21
    int but; // [invalid]
    enum JoypadButton joybut; // [invalid]
    class ButtonUpMsg msg; // r1+0xE0
    enum JoypadButton joybut; // r20
    int bucket; // r0
    class ButtonDownMsg msg; // r1+0xD8
    int e; // r9
    int f; // r10
    int e; // r20
    enum JoypadButton joybut; // r19
    class ButtonDownMsg msg; // r1+0xD0
    class JoypadConnectionMsg msg; // r1+0xC8
    class JoypadConnectionMsg msg; // r1+0xC0

    // References
    // -> struct [anonymous] __vt__19JoypadConnectionMsg;
    // -> class Symbol t;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__7Message;
    // -> static class MsgSource gJoypadMsgSource;
    // -> static unsigned char gExportMsgs;
    // -> class UserMgr * TheUserMgr;
    // -> static class Symbol ignore_buttons;
    // -> static class Symbol unknown;
    // -> static class DataArray * gControllersCfg;
    // -> static class Symbol translate_sticks;
    // -> static float kAnalogRestPos;
    // -> static unsigned char gJoypadDisabled[8];
    // -> static class JoypadData gJoypadData[8];
    // -> static class Symbol hx_kick_xbox;
    // -> class Debug TheDebug;
    // -> static unsigned char gJoypadLibInitialized;
}

// Range: 0x805B8958 -> 0x805B8A2C
void TranslateSticksToButs() {
    // Local variables
    float distFromRest; // f3
    int i; // r8
    int offset; // r9

    // References
    // -> static float kAnalogRestPos;
}

// Range: 0x805B8A2C -> 0x805B8AAC
class JoypadData * JoypadGetData(int iUserNum /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805B8AAC -> 0x805B8B30
class JoypadData * JoypadGetPadData(int pad_num /* r31 */) {
    // References
    // -> static class JoypadData gJoypadData[8];
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805B8B30 -> 0x805B8B7C
void JoypadSubscribe() {
    // References
    // -> static class MsgSource gJoypadMsgSource;
    // -> const char * gNullStr;
}

// Range: 0x805B8B7C -> 0x805B8BCC
void JoypadSubscribe(class Object * iSink /* r5 */) {
    // References
    // -> static class MsgSource gJoypadMsgSource;
    // -> const char * gNullStr;
}

// Range: 0x805B8BCC -> 0x805B8C08
void JoypadUnsubscribe() {
    // References
    // -> static class MsgSource gJoypadMsgSource;
    // -> const char * gNullStr;
}

// Range: 0x805B8C08 -> 0x805B8C44
void JoypadUnsubscribe(class Object * iSink /* r5 */) {
    // References
    // -> static class MsgSource gJoypadMsgSource;
}

static class JoypadReassignMsg msg; // size: 0x8, address: 0x80985870
// Range: 0x805B8C44 -> 0x805B8F80
void AssociateUserAndPad(int iUserNum /* r28 */, int iPadNum /* r29 */) {
    // References
    // -> static class MsgSource gJoypadMsgSource;
    // -> static unsigned char gExportMsgs;
    // -> struct [anonymous] __vt__17JoypadReassignMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class JoypadReassignMsg msg;
    // -> static class JoypadData gJoypadData[8];
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805B8F80 -> 0x805B8F84
void JoypadAssociateUserAndPad() {}

// Range: 0x805B8F84 -> 0x805B8FD8
int GetUsersPadNum() {
    // Local variables
    int i; // r5

    // References
    // -> static class JoypadData gJoypadData[8];
    // -> static unsigned char gJoypadDisabled[8];
}

// Range: 0x805B8FD8 -> 0x805B9060
int JoypadGetUserFromPadNum(int iPadNum /* r31 */) {
    // References
    // -> static class JoypadData gJoypadData[8];
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805B9060 -> 0x805B9064
int JoypadGetUsersPadNum() {}

static class Symbol symDetect; // size: 0x4, address: 0x80A54AB0
static class Symbol symOr; // size: 0x4, address: 0x80A54AB8
// Range: 0x805B9064 -> 0x805B9238
unsigned char JoypadIsControllerTypePadNum(int padNum /* r28 */, class Symbol & controller_type /* r31 */) {
    // Local variables
    class JoypadData & data; // r29
    class DataArray * type_cfg; // r0
    class DataArray * detect_cfg; // r30
    class DataArray * options; // r28
    int i; // r30

    // References
    // -> static class DataArray * gControllersCfg;
    // -> static class JoypadData gJoypadData[8];
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol symOr;
    // -> static class Symbol symDetect;
}

static class Symbol none; // size: 0x4, address: 0x80A54AC0
static class Symbol unknown; // size: 0x4, address: 0x80A54AC8
// Range: 0x805B9238 -> 0x805B93A0
class Symbol JoypadControllerTypePadNum(int padNum /* r31 */) {
    // Local variables
    int i; // r29
    class Symbol type; // r1+0x14

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class DataArray * gControllersCfg;
    // -> static class JoypadData gJoypadData[8];
    // -> static unsigned char gJoypadDisabled[8];
    // -> static class Symbol unknown;
    // -> static class Symbol none;
}

// Range: 0x805B93A0 -> 0x805B93C4
class Symbol JoypadControllerType() {
    // Local variables
    int pad_num; // r0
}

// Range: 0x805B93C4 -> 0x805B9408
unsigned char JoypadIsConnected() {
    // Local variables
    int pad; // r0

    // References
    // -> static class JoypadData gJoypadData[8];
}

static class JoypadReassignMsg msg; // size: 0x8, address: 0x80985888
// Range: 0x805B9408 -> 0x805B9808
void JoypadSwapUsers(int p1 /* r28 */, int p2 /* r29 */) {
    // References
    // -> static class JoypadData gJoypadData[8];
    // -> static class MsgSource gJoypadMsgSource;
    // -> static unsigned char gExportMsgs;
    // -> struct [anonymous] __vt__17JoypadReassignMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class JoypadReassignMsg msg;
}

static class JoypadReassignMsg msg; // size: 0x8, address: 0x809858A0
// Range: 0x805B9808 -> 0x805B9C04
void JoypadSwapPads(int padNum1 /* r26 */, int padNum2 /* r27 */) {
    // Local variables
    int userNum1; // r29
    int userNum2; // r28

    // References
    // -> static class MsgSource gJoypadMsgSource;
    // -> static unsigned char gExportMsgs;
    // -> struct [anonymous] __vt__17JoypadReassignMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class JoypadReassignMsg msg;
    // -> static class JoypadData gJoypadData[8];
}

// Range: 0x805B9C04 -> 0x805B9CBC
void JoypadReserveUserNum() {
    // Local variables
    int pad_num; // r31
    int p; // r30
    int this_pad; // r29

    // References
    // -> static unsigned char gReservedUserNums[4];
}

// Range: 0x805B9CBC -> 0x805B9DB8
void JoypadFreeUserNum(int user /* r30 */) {
    // Local variables
    int first_unused_joypad; // r5
    int j; // r4

    // References
    // -> static class JoypadData gJoypadData[8];
    // -> static unsigned char gJoypadDisabled[8];
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static unsigned char gReservedUserNums[4];
}

// Range: 0x805B9DB8 -> 0x805B9DEC
unsigned char UserHasController() {}

static class Symbol lefty_flip; // size: 0x4, address: 0x80A54AD0
// Range: 0x805B9DEC -> 0x805B9E9C
unsigned char JoypadTypeHasLeftyFlip(class Symbol & type /* r30 */) {
    // Local variables
    class DataArray * a; // r30

    // References
    // -> static class DataArray * gControllersCfg;
    // -> static class Symbol lefty_flip;
}

static class Symbol none; // size: 0x4, address: 0x80A54AD8
// Range: 0x805B9E9C -> 0x805B9F68
enum JoypadAction ButtonToAction(enum JoypadButton button /* r29 */, class Symbol & controller_type /* r30 */) {
    // Local variables
    enum JoypadAction action; // r31
    class DataArray * meaning_set; // r0
    class DataArray * mapping; // r30

    // References
    // -> static class DataArray * gButtonMeanings;
    // -> static class Symbol none;
}

// Range: 0x805B9F68 -> 0x805BA048
enum JoypadButton JoypadActionToButton(enum JoypadAction action /* r28 */) {
    // Local variables
    int pad_num; // r0
    class Symbol controller_type; // r1+0xC
    class DataArray * meaning_set; // r30
    int i; // r29

    // References
    // -> static class DataArray * gButtonMeanings;
    // -> static class JoypadData gJoypadData[8];
}

struct {
    // total size: 0x8
} __RTTI__P8WaitInfo; // size: 0x8, address: 0x80924150
// Range: 0x805BA048 -> 0x805BA124
static void __sinit_\Joypad_cpp() {
    // References
    // -> struct [anonymous] __vt__9MsgSource;
    // -> static class MsgSource gJoypadMsgSource;
    // -> static class JoypadData gJoypadData[8];
}


