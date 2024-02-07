/*
    Compile unit: C:\rockband2\system\src\os\JoypadClient.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805BC220 -> 0x805BD8E0
*/
static float gDefaultHoldMs; // size: 0x4, address: 0x80A47850
static float gDefaultRepeatMs; // size: 0x4, address: 0x80A47854
class vector : protected _Vector_base {
    // total size: 0xC
};
static class vector gClients; // size: 0xC, address: 0x809858EC
// Range: 0x805BC220 -> 0x805BC240
static unsigned char IsLeftStick() {}

// Range: 0x805BC240 -> 0x805BC2D0
static enum JoypadButton LeftStickToDpad() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x805BC2D0 -> 0x805BC324
void * JoypadRepeat::JoypadRepeat(struct JoypadRepeat * const this /* r31 */) {}

// Range: 0x805BC324 -> 0x805BC3A8
void JoypadRepeat::Start(struct JoypadRepeat * const this /* r28 */, enum JoypadButton btn /* r29 */, enum JoypadAction action /* r30 */, int pad /* r31 */) {}

// Range: 0x805BC3A8 -> 0x805BC3EC
void JoypadRepeat::Reset(struct JoypadRepeat * const this /* r31 */) {}

// Range: 0x805BC3EC -> 0x805BC62C
void JoypadRepeat::Poll(struct JoypadRepeat * const this /* r29 */, float minHoldMs /* f30 */, float minRepeatMs /* f31 */, class Object * sink /* r30 */, int user /* r31 */) {
    // Local variables
    float delayMs; // f0
    float repeatMs; // f0

    // References
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
}

// Range: 0x805BC62C -> 0x805BC730
void JoypadRepeat::SendRepeat(struct JoypadRepeat * const this /* r29 */, class Object * sink /* r30 */, int user /* r31 */) {
    // References
    // -> struct [anonymous] __vt__7Message;
    // -> class UserMgr * TheUserMgr;
}

// Range: 0x805BC730 -> 0x805BC800
void * JoypadClient::JoypadClient(class JoypadClient * const this /* r29 */, int userNum /* r31 */, class Object * sink /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__12JoypadClient;
}

// Range: 0x805BC800 -> 0x805BC8D0
void * JoypadClient::JoypadClient(class JoypadClient * const this /* r29 */, class Object * sink /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__12JoypadClient;
}

// Range: 0x805BC8D0 -> 0x805BC9FC
void JoypadClient::Init(class JoypadClient * const this /* r1+0x8 */) {
    // References
    // -> static class vector gClients;
    // -> static float gDefaultRepeatMs;
    // -> static float gDefaultHoldMs;
}

// Range: 0x805BC9FC -> 0x805BCAD0
void * JoypadClient::~JoypadClient(class JoypadClient * const this /* r1+0x8 */) {
    // References
    // -> static class vector gClients;
    // -> struct [anonymous] __vt__12JoypadClient;
}

// Range: 0x805BCAD0 -> 0x805BCAD8
void JoypadClient::SetRepeatMask() {}

// Range: 0x805BCAD8 -> 0x805BCAE0
void JoypadClient::SetHoldMs() {}

// Range: 0x805BCAE0 -> 0x805BCAE8
void JoypadClient::SetRepeatMs() {}

// Range: 0x805BCAE8 -> 0x805BCAF0
void JoypadClient::SetVirtualDpad() {}

// Range: 0x805BCAF0 -> 0x805BCB54
void JoypadClient::Poll(class JoypadClient * const this /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x805BCB54 -> 0x805BCBB4
void JoypadClientPoll() {
    // Local variables
    int i; // r31

    // References
    // -> static class vector gClients;
}

// Range: 0x805BCBB4 -> 0x805BD38C
class DataNode JoypadClient::Handle(class JoypadClient * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x38
    class MessageTimer _mt; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode r; // r1+0x68
    class DataNode r; // r1+0x60
    class DataNode _n; // r1+0x58

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__17JoypadReassignMsg;
    // -> class Symbol t;
    // -> struct [anonymous] __vt__11ButtonUpMsg;
    // -> class Symbol t;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __vt__13ButtonDownMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> unsigned char sActive;
}

// Range: 0x805BD38C -> 0x805BD5F8
int JoypadClient::OnMsg(class JoypadClient * const this /* r28 */, const class ButtonDownMsg & msg /* r29 */) {
    // Local variables
    enum JoypadButton btn; // r30

    // References
    // -> struct [anonymous] __vt__7Message;
    // -> class UserMgr * TheUserMgr;
}

// Range: 0x805BD5F8 -> 0x805BD82C
int JoypadClient::OnMsg(class JoypadClient * const this /* r29 */, const class ButtonUpMsg & msg /* r25 */) {
    // Local variables
    enum JoypadButton btn; // r30

    // References
    // -> struct [anonymous] __vt__7Message;
    // -> class UserMgr * TheUserMgr;
}

// Range: 0x805BD82C -> 0x805BD8B4
int JoypadClient::OnMsg(class JoypadClient * const this /* r30 */) {}

struct {
    // total size: 0x54
} __vt__12JoypadClient; // size: 0x54, address: 0x809243E0
struct {
    // total size: 0x8
} __RTTI__12JoypadClient; // size: 0x8, address: 0x80924458
struct {
    // total size: 0x8
} __RTTI__PP12JoypadClient; // size: 0x8, address: 0x809244C0
// Range: 0x805BD8B4 -> 0x805BD8E0
static void __sinit_\JoypadClient_cpp() {
    // References
    // -> static class vector gClients;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class JoypadClient * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class JoypadClient * * _M_start; // offset 0x0, size 0x4
    class JoypadClient * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};

