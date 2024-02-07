/*
    Compile unit: C:\rockband2\system\src\os\Joypad_Wii.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805BA310 -> 0x805BC13C
*/
static int kWiiRemoteButton[16]; // size: 0x40, address: 0x8084E6E8
static int kWiiClassicButton[16]; // size: 0x40, address: 0x8084E728
static int kWiiGuitarButton[16]; // size: 0x40, address: 0x8084E768
static int kWiiUSBButton[24]; // size: 0x60, address: 0x8084E7A8
static long op[4]; // size: 0x10, address: 0x8084E808
static unsigned char gDisabled; // size: 0x1, address: 0x80A54AE0
static float gDeadzone; // size: 0x4, address: 0x80A54AE4
static unsigned char gWiiJoypadCommonInitialized; // size: 0x1, address: 0x80A54AE8
static unsigned char gWiiJoypadUseHeapMemory; // size: 0x1, address: 0x80A54AE9
static class UsbWii * gUSBWii; // size: 0x4, address: 0x80A54AEC
static class WiiJoypad * gWiiJoypads[8]; // size: 0x20, address: 0x809858C0
// Range: 0x805BA310 -> 0x805BA360
void * WiiJoypadWPADAlloc(unsigned long size /* r1+0x8 */) {
    // References
    // -> static unsigned char gWiiJoypadUseHeapMemory;
}

// Range: 0x805BA360 -> 0x805BA39C
unsigned char WiiJoypadWPADFree() {
    // References
    // -> static unsigned char gWiiJoypadUseHeapMemory;
}

// Range: 0x805BA39C -> 0x805BA5F4
void JoypadInit() {
    // Local variables
    class DataArray * joypad_config; // r30

    // References
    // -> static class UsbWii * gUSBWii;
    // -> static class WiiJoypad * gWiiJoypads[8];
    // -> static float gDeadzone;
    // -> static unsigned char gDisabled;
}

// Range: 0x805BA5F4 -> 0x805BA640
void WiiJoypadInitCommon() {
    // References
    // -> static unsigned char gWiiJoypadUseHeapMemory;
    // -> static unsigned char gWiiJoypadCommonInitialized;
}

// Range: 0x805BA640 -> 0x805BA6D4
void JoypadReset() {
    // Local variables
    int i; // r31

    // References
    // -> static class WiiJoypad * gWiiJoypads[8];
    // -> int kNonUser;
}

// Range: 0x805BA6D4 -> 0x805BA764
void JoypadTerminate() {
    // Local variables
    int i; // r29

    // References
    // -> static class UsbWii * gUSBWii;
    // -> static class WiiJoypad * gWiiJoypads[8];
    // -> static unsigned char gDisabled;
}

// Range: 0x805BA764 -> 0x805BA7C0
void JoypadPoll() {
    // References
    // -> static class UsbWii * gUSBWii;
    // -> class PlatformMgr ThePlatformMgr;
    // -> static unsigned char gDisabled;
}

// Range: 0x805BA7C0 -> 0x805BAA2C
int ReadSingleJoypad(int iPadNum /* r22 */, unsigned int * iButtons /* r23 */, char * iLeftStickX /* r24 */, char * iLeftStickY /* r25 */, char * iRightStickX /* r26 */, char * iRightStickY /* r27 */, char * iLeftTrigger /* r28 */, char * iRightTrigger /* r29 */, float * iPressures /* r30 */) {
    // Local variables
    class WiiJoypad * wiiJoypad; // r31
    enum JoypadType newJoypadType; // r1+0x10
    unsigned int pressures[4]; // r1+0x18
    enum JoypadType type; // r3

    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> static unsigned char gDisabled;
}

struct DPDObject {
    // total size: 0x8
    signed short x; // offset 0x0, size 0x2
    signed short y; // offset 0x2, size 0x2
    unsigned short size; // offset 0x4, size 0x2
    unsigned char traceId; // offset 0x6, size 0x1
};
struct WPADCLStatus {
    // total size: 0x36
    unsigned short button; // offset 0x0, size 0x2
    signed short accX; // offset 0x2, size 0x2
    signed short accY; // offset 0x4, size 0x2
    signed short accZ; // offset 0x6, size 0x2
    struct DPDObject obj[4]; // offset 0x8, size 0x20
    unsigned char dev; // offset 0x28, size 0x1
    signed char err; // offset 0x29, size 0x1
    unsigned short clButton; // offset 0x2A, size 0x2
    signed short clLStickX; // offset 0x2C, size 0x2
    signed short clLStickY; // offset 0x2E, size 0x2
    signed short clRStickX; // offset 0x30, size 0x2
    signed short clRStickY; // offset 0x32, size 0x2
    unsigned char clTriggerL; // offset 0x34, size 0x1
    unsigned char clTriggerR; // offset 0x35, size 0x1
};
struct WPADStatus {
    // total size: 0x2A
    unsigned short button; // offset 0x0, size 0x2
    signed short accX; // offset 0x2, size 0x2
    signed short accY; // offset 0x4, size 0x2
    signed short accZ; // offset 0x6, size 0x2
    struct DPDObject obj[4]; // offset 0x8, size 0x20
    unsigned char dev; // offset 0x28, size 0x1
    signed char err; // offset 0x29, size 0x1
};
// Range: 0x805BAA2C -> 0x805BAE3C
enum JoypadType ReadWiiJoypad(class WiiJoypad * wiiJoypad /* r29 */, unsigned int * iButtons /* r30 */, char * iLeftStickX /* r24 */, char * iLeftStickY /* r25 */, char * iRightStickX /* r31 */, char * iRightStickY /* r26 */, unsigned int * pressures /* r27 */) {
    // Local variables
    unsigned int usbButtons; // r1+0x10
    enum JoypadType joypadType; // r31
    struct WPADCLStatus curCLStatus; // r1+0x78
    struct WPADStatus curStatus; // r1+0x4C
    struct WPADCLStatus curCLStatus; // r1+0x14

    // References
    // -> class Debug TheDebug;
    // -> static class UsbWii * gUSBWii;
}

// Range: 0x805BAE3C -> 0x805BAE40
void JoypadKeepAlive() {}

// Range: 0x805BAE40 -> 0x805BAED0
int JoypadPollWiiRemotes() {
    // Local variables
    int i; // r31
    struct WPADStatus curStatus; // r1+0xC
    unsigned int iButtons; // r1+0x8
}

// Range: 0x805BAED0 -> 0x805BB07C
unsigned char CheckForJoypadOverflow() {
    // Local variables
    int numberConnected; // r29
    unsigned int iButtons; // r1+0x1C
    char iLeftStickX; // r1+0x15
    char iLeftStickY; // r1+0x14
    char iRightStickX; // r1+0x13
    char iRightStickY; // r1+0x12
    char iLeftTrigger; // r1+0x11
    char iRightTrigger; // r1+0x10
    unsigned int pressures[4]; // r1+0x20
    enum JoypadType joypadType; // r0
    enum JoypadType newJoypadType; // r1+0x18
    int i; // r28

    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class WiiJoypad * gWiiJoypads[8];
}

// Range: 0x805BB07C -> 0x805BB140
class WiiJoypad * GetWiiJoypad(int joypadNum /* r28 */) {
    // Local variables
    int i; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class WiiJoypad * gWiiJoypads[8];
}

// Range: 0x805BB140 -> 0x805BB4FC
class WiiJoypad * AddWiiJoypad(int joypadNum /* r29 */) {
    // Local variables
    enum JoypadType joypadType; // r31
    class WiiJoypad * wiiJoypad; // r30
    unsigned long contType; // r1+0x8
    long result; // r0
    int i; // r26
    class WiiJoypad * existingWiiJoypad; // r27
    class JoypadData * existingJoypadData; // r0
    int requestedUserNum; // r0
    int j; // r25
    unsigned char foundLocked; // r4
    int k; // r25
    int i; // r25
    int j; // r26
    unsigned char foundLocked; // r4
    int k; // r26

    // References
    // -> static class WiiJoypad * gWiiJoypads[8];
    // -> static class UsbWii * gUSBWii;
}

// Range: 0x805BB4FC -> 0x805BB52C
void DisableWiiJoypad() {
    // Local variables
    class WiiJoypad * wiiJoypad; // r0
}

// Range: 0x805BB52C -> 0x805BB56C
void LockWiiJoypad(int joypadNum /* r31 */) {
    // Local variables
    class WiiJoypad * wiiJoypad; // r0
}

// Range: 0x805BB56C -> 0x805BB5A0
void UnlockWiiJoypad() {
    // Local variables
    class WiiJoypad * wiiJoypad; // r0
}

// Range: 0x805BB5A0 -> 0x805BB5F4
void UnlockAllWiiJoypads() {
    // Local variables
    int i; // r31

    // References
    // -> static class WiiJoypad * gWiiJoypads[8];
}

// Range: 0x805BB5F4 -> 0x805BB648
int GetAccelerationByUser() {
    // Local variables
    class WiiJoypad * wiiJoypad; // r0
}

// Range: 0x805BB648 -> 0x805BB6C4
enum JoypadType GetWiiType() {}

// Range: 0x805BB6C4 -> 0x805BB780
void TranslateButtons() {
    // Local variables
    int buttonCount; // r7
    const int * lookupTable; // r8
    int i; // r9

    // References
    // -> static int kWiiGuitarButton[16];
    // -> static int kWiiUSBButton[24];
    // -> static int kWiiClassicButton[16];
    // -> static int kWiiRemoteButton[16];
}

// Range: 0x805BB780 -> 0x805BB790
void WiiJoypadSyncCallback() {}

// Range: 0x805BB790 -> 0x805BB848
void WiiJoypadConnectCallback(long chan /* r31 */) {
    // Local variables
    unsigned long contType; // r1+0x8
}

class WiiJoypad {
    // total size: 0x20
    int mJoypadNum; // offset 0x0, size 0x4
    int mWiiJoypadNum; // offset 0x4, size 0x4
    enum JoypadType mJoypadType; // offset 0x8, size 0x4
    int mAcceleration; // offset 0xC, size 0x4
    int mReadDelay; // offset 0x10, size 0x4
    unsigned char mEnabled; // offset 0x14, size 0x1
    unsigned char mDisabling; // offset 0x15, size 0x1
    int mLockedJoypadNum; // offset 0x18, size 0x4
    enum JoypadType mLockedJoypadType; // offset 0x1C, size 0x4
};
// Range: 0x805BB848 -> 0x805BB978
void * WiiJoypad::WiiJoypad(class WiiJoypad * const this /* r24 */, enum JoypadType joypadType /* r25 */, int wiiJoypadNum /* r26 */) {
    // Local variables
    int maxWiiJoypadNum; // r3
    unsigned char setJoypadNum; // r29
    unsigned char foundJoypad; // r28
    int i; // r27

    // References
    // -> static class WiiJoypad * gWiiJoypads[8];
}

// Range: 0x805BB978 -> 0x805BB9B8
void * WiiJoypad::~WiiJoypad(class WiiJoypad * const this /* r31 */) {}

// Range: 0x805BB9B8 -> 0x805BBA28
unsigned char WiiJoypad::SetJoypadNum(class WiiJoypad * const this /* r30 */, int joypadNum /* r31 */) {}

// Range: 0x805BBA28 -> 0x805BBA44
int WiiJoypad::JoypadNum() {}

// Range: 0x805BBA44 -> 0x805BBA6C
void WiiJoypad::SetJoypadType() {}

// Range: 0x805BBA6C -> 0x805BBA88
int WiiJoypad::WiiJoypadNum() {}

// Range: 0x805BBA88 -> 0x805BBAB0
void WiiJoypad::SetReadDelay() {}

// Range: 0x805BBAB0 -> 0x805BBAD4
void WiiJoypad::DecrementReadDelay() {}

// Range: 0x805BBAD4 -> 0x805BBAF8
unsigned char WiiJoypad::CanRead() {}

// Range: 0x805BBAF8 -> 0x805BBC3C
void WiiJoypad::Connect(class WiiJoypad * const this /* r30 */, int joypadNum /* r31 */) {
    // References
    // -> static class UsbWii * gUSBWii;
}

// Range: 0x805BBC3C -> 0x805BBC74
void WiiJoypad::Disconnect(class WiiJoypad * const this /* r31 */) {}

// Range: 0x805BBC74 -> 0x805BBDDC
unsigned char WiiJoypad::Connected(class WiiJoypad * const this /* r29 */, enum JoypadType & newJoypadType /* r30 */) {
    // Local variables
    enum JoypadType joypadType; // r31
    unsigned long contType; // r1+0x8
    long result; // r0

    // References
    // -> static class UsbWii * gUSBWii;
}

// Range: 0x805BBDDC -> 0x805BBE84
void WiiJoypad::SetEnabled() {
    // References
    // -> static class UsbWii * gUSBWii;
}

// Range: 0x805BBE84 -> 0x805BBF78
void WiiJoypad::SetLocked(class WiiJoypad * const this /* r27 */, int joypadNum /* r28 */, enum JoypadType joypadType /* r29 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x805BBF78 -> 0x805BC064
unsigned char WiiJoypad::IsEquivalentToLockedType() {}

// Range: 0x805BC064 -> 0x805BC0AC
unsigned char JoypadIsCalbertGuitar() {
    // Local variables
    class WiiJoypad * wiiJoypad; // r0
}

enum JoypadCalbertMode {
    kJoypadCalbertPhoto = 0,
    kJoypadCalbertAudio = 1,
    kJoypadCalbertOff = 2,
};
// Range: 0x805BC0AC -> 0x805BC13C
void JoypadSetCalbertMode(enum JoypadCalbertMode mode /* r31 */) {
    // Local variables
    class WiiJoypad * wiiJoypad; // r3

    // References
    // -> static class UsbWii * gUSBWii;
}


