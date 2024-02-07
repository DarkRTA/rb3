/*
    Compile unit: C:\rockband2\system\src\beatmatch\JoypadController.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802E36D0 -> 0x802E4448
*/
class JoypadController : public BeatMatchController {
    // total size: 0x54
    unsigned char mDisabled; // offset 0x3C, size 0x1
    unsigned char mUseDpad; // offset 0x3D, size 0x1
    unsigned char mAlternateMapping; // offset 0x3E, size 0x1
    unsigned int mFretMask; // offset 0x40, size 0x4
    class BeatMatchControllerSink * mSink; // offset 0x44, size 0x4
    class JoypadClient * mClient; // offset 0x48, size 0x4
    class DataArray * mVelocityAxes; // offset 0x4C, size 0x4
    class DataArray * mVelocityPressures; // offset 0x50, size 0x4
};
// Range: 0x802E36D0 -> 0x802E3768
void * JoypadController::~JoypadController(class JoypadController * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__16JoypadController;
}

// Range: 0x802E3768 -> 0x802E37B0
int JoypadController::MapSlot() {}

// Range: 0x802E37B0 -> 0x802E37FC
int JoypadController::ButtonToSlot(class JoypadController * const this /* r31 */) {
    // Local variables
    int slot; // r4
}

// Range: 0x802E37FC -> 0x802E3834
int JoypadController::SlotToButton(class JoypadController * const this /* r31 */) {}

// Range: 0x802E3834 -> 0x802E38C0
void JoypadController::Disable(class JoypadController * const this /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x802E38C0 -> 0x802E3930
float JoypadController::GetWhammyBar(const class JoypadController * const this /* r31 */) {
    // Local variables
    class JoypadData * joy; // r0
}

// Range: 0x802E3930 -> 0x802E3A44
int JoypadController::GetVelocityBucket(const class JoypadController * const this /* r29 */, int slot /* r30 */) {
    // Local variables
    class JoypadData * data; // r31
    class DataArray * pair; // r30
    class Symbol axis; // r1+0x14
    class DataArray * pair; // r30
}

// Range: 0x802E3A44 -> 0x802E3BCC
int JoypadController::GetVirtualSlot(const class JoypadController * const this /* r30 */, int slot /* r31 */) {
    // Local variables
    class JoypadData * data; // r0
    int val; // [invalid]

    // References
    // -> class Debug TheDebug;
}

// Range: 0x802E3BCC -> 0x802E3D4C
unsigned char JoypadController::OnMsg(class JoypadController * const this /* r30 */, const class ButtonDownMsg & msg /* r31 */) {
    // Local variables
    enum JoypadButton but; // r4
    int slot; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802E3D4C -> 0x802E3E60
unsigned char JoypadController::OnMsg(class JoypadController * const this /* r30 */, const class ButtonUpMsg & msg /* r31 */) {
    // Local variables
    enum JoypadButton but; // r31
    int slot; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802E3E60 -> 0x802E3F60
void JoypadController::ReconcileFretState(class JoypadController * const this /* r25 */) {
    // Local variables
    class JoypadData * joyData; // r0
    int new_fret_mask; // r27
    int slot; // r26
    unsigned char was_on; // r0
}

// Range: 0x802E3F60 -> 0x802E4448
class DataNode JoypadController::Handle(class JoypadController * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x2C
    class MessageTimer _mt; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode r; // r1+0x40

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__11ButtonUpMsg;
    // -> class Symbol t;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __vt__13ButtonDownMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x88
} __vt__16JoypadController; // size: 0x88, address: 0x808CB830
struct {
    // total size: 0x8
} __RTTI__16JoypadController; // size: 0x8, address: 0x808CB8E8

