/*
    Compile unit: C:\rockband2\system\src\beatmatch\GuitarController.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802E0E70 -> 0x802E211C
*/
enum ControllerStyle {
    kPS2 = 0,
    kPS3 = 1,
    kHxXbox = 2,
    kRoXbox = 3,
    kRoPS3 = 4,
    kHxWii = 5,
};
class GuitarController : public BeatMatchController {
    // total size: 0x60
    unsigned char mDisabled; // offset 0x3C, size 0x1
    unsigned int mFretMask; // offset 0x40, size 0x4
    unsigned int mShiftButtonMask; // offset 0x44, size 0x4
    class BeatMatchControllerSink * mSink; // offset 0x48, size 0x4
    enum ControllerStyle mControllerStyle; // offset 0x4C, size 0x4
    class vector mStrumBarButtons; // offset 0x50, size 0xC
    enum JoypadButton mMercuryButton; // offset 0x5C, size 0x4
};
// Range: 0x802E0E70 -> 0x802E1380
void * GuitarController::GuitarController(class GuitarController * const this /* r26 */, const class DataArray * cfg /* r27 */, class BeatMatchControllerSink * sink /* r30 */, unsigned char disabled /* r28 */, unsigned char lefty /* r29 */) {
    // Local variables
    class Symbol controller_style; // r1+0x30
    class DataArray * strum_buttons; // r28
    int i; // r29
    class DataArray * shift_button_cfg; // r27

    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__16GuitarController;
}

// Range: 0x802E1380 -> 0x802E1430
void * GuitarController::~GuitarController(class GuitarController * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__16GuitarController;
}

// Range: 0x802E1430 -> 0x802E14BC
void GuitarController::Disable(class GuitarController * const this /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x802E14BC -> 0x802E1588
float GuitarController::GetWhammyBar(const class GuitarController * const this /* r31 */) {
    // Local variables
    class JoypadData * joy; // r0
    float val; // r1+0x8
}

// Range: 0x802E1588 -> 0x802E1630
void GuitarController::Poll(class GuitarController * const this /* r31 */) {
    // Local variables
    class JoypadData * joy; // r0
}

// Range: 0x802E1630 -> 0x802E1884
unsigned char GuitarController::OnMsg(class GuitarController * const this /* r29 */, const class ButtonDownMsg & msg /* r30 */) {
    // Local variables
    enum JoypadButton but; // r1+0x8
    int * strum_it; // r0
    int slot; // r0
    int slot; // r30
    unsigned char real_swing; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802E1884 -> 0x802E1A34
unsigned char GuitarController::OnMsg(class GuitarController * const this /* r29 */, const class ButtonUpMsg & msg /* r30 */) {
    // Local variables
    enum JoypadButton but; // r1+0x8
    int * strum_it; // r0
    int slot; // r31
    int pull_off_slot; // r4
}

// Range: 0x802E1A34 -> 0x802E1BB4
void GuitarController::ReconcileFretState(class GuitarController * const this /* r30 */) {
    // Local variables
    class JoypadData * joyData; // r0
    int new_fret_mask; // r26
    int slot; // r25
    unsigned char was_on; // r0
}

// Range: 0x802E1BB4 -> 0x802E1BEC
int GuitarController::GetCurrentSlot() {
    // Local variables
    int slot; // r5
    int i; // r6
}

// Range: 0x802E1BEC -> 0x802E1C34
unsigned char GuitarController::IsShifted(const class GuitarController * const this /* r31 */) {}

// Range: 0x802E1C34 -> 0x802E211C
class DataNode GuitarController::Handle(class GuitarController * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
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
} __vt__16GuitarController; // size: 0x88, address: 0x808CB3A8
struct {
    // total size: 0x8
} __RTTI__16GuitarController; // size: 0x8, address: 0x808CB460

