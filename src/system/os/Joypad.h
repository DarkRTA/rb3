#ifndef OS_JOYPAD_H
#define OS_JOYPAD_H
#include "utl/Symbol.h"

#define kNumJoypads 4
#define kNumPressureButtons 8

enum JoypadAction {
    kAction_None = 0,
    kAction_Confirm = 1,
    kAction_Cancel = 2,
    kAction_Option = 3,
    kAction_Start = 4,
    kAction_ViewModify = 5,
    kAction_Up = 6,
    kAction_Right = 7,
    kAction_Down = 8,
    kAction_Left = 9,
    kAction_PageUp = 10,
    kAction_PageDown = 11,
    kAction_ExtendedOption1 = 12,
    kAction_ExtendedOption2 = 13,
    kAction_WiiHomeMenu = 14,
    kAction_Option1 = 15,
    kAction_NumActions = 16,
};
enum JoypadButton {
    kPad_L2 = 0,
    kPad_R2 = 1,
    kPad_L1 = 2,
    kPad_R1 = 3,
    kPad_Tri = 4,
    kPad_Circle = 5,
    kPad_X = 6,
    kPad_Square = 7,
    kPad_Select = 8,
    kPad_L3 = 9,
    kPad_R3 = 10,
    kPad_Start = 11,
    kPad_DUp = 12,
    kPad_DRight = 13,
    kPad_DDown = 14,
    kPad_DLeft = 15,
    kPad_LStickUp = 16,
    kPad_LStickRight = 17,
    kPad_LStickDown = 18,
    kPad_LStickLeft = 19,
    kPad_RStickUp = 20,
    kPad_RStickRight = 21,
    kPad_RStickDown = 22,
    kPad_RStickLeft = 23,
    kPad_NumButtons = 24,
    kPad_Xbox_LT = 0,
    kPad_Xbox_RT = 1,
    kPad_Xbox_LB = 2,
    kPad_Xbox_RB = 3,
    kPad_Xbox_Y = 4,
    kPad_Xbox_B = 5,
    kPad_Xbox_A = 6,
    kPad_Xbox_X = 7,
    kPad_Xbox_LS = 9,
    kPad_Xbox_RS = 10,
};

// there might be more of these specifically for RB3, who knows
enum JoypadType {
    kJoypadNone = 0,
    kJoypadDigital = 1,
    kJoypadAnalog = 2,
    kJoypadDualShock = 3,
    kJoypadMidi = 4,
    kJoypadXboxHxGuitar = 5,
    kJoypadXboxHxGuitarRb2 = 6,
    kJoypadXboxRoGuitar = 7,
    kJoypadXboxDrums = 8,
    kJoypadXboxDrumsRb2 = 9,
    kJoypadXboxStageKit = 10,
    kJoypadPs3HxGuitar = 11,
    kJoypadPs3HxGuitarRb2 = 12,
    kJoypadPs3HxDrums = 13,
    kJoypadPs3HxDrumsRb2 = 14,
    kJoypadPs3RoGuitar = 15,
    kJoypadWiiCore = 16,
    kJoypadWiiFS = 17,
    kJoypadWiiClassic = 18,
    kJoypadWiiGamecube = 19,
    kJoypadWiiGuitar = 20,
    kJoypadWiiDrums = 21,
    kJoypadWiiHxGuitar = 22,
    kJoypadWiiHxGuitarRb2 = 23,
    kJoypadWiiHxDrums = 24,
    kJoypadWiiHxDrumsRb2 = 25,
};

class JoypadData {
public:
    // RB3's members differ - verify this!
    unsigned int mButtons;
    unsigned int mNewPressed;
    unsigned int mNewReleased;
    float mSticks[2][2]; // LX, LY, RX, RY
    float mTriggers[2]; // LT, RT
    float mSensors[3]; // SX, SY, SZ
    float mPressures[8];
    int mUserNum;
    bool mConnected;
    bool mForceFeedback;
    bool mCanForceFeedback;
    bool mWireless;
    int unk58, unk5c, unk60;
    bool unk64;
    bool mVibrateEnabled;
    char filler[0x20];

    JoypadType mType;
    Symbol mControllerType;
    float mDistFromRest;
    bool mHasGreenCymbal;
    bool mHasBlueCymbal;
    bool mHasYellowCymbal;
    
    int morefiller;

    JoypadData();
    float GetAxis(Symbol) const;
    int FloatToBucket(float) const;
    int GetVelocityBucket(Symbol) const;
    int GetPressureBucket(JoypadButton) const;
};

extern "C" bool JoypadIsCalbertGuitar(int);

void JoypadSetVibrate(int, bool);
Symbol JoypadControllerTypePadNum(int padNum);
bool JoypadIsConnectedPadNum(int);
class JoypadData* JoypadGetPadData(int);
void JoypadReset();
bool JoypadIsControllerTypePadNum(int, Symbol);
bool JoypadTypeHasLeftyFlip(Symbol);
int JoypadTypePadShiftButton(Symbol);
int JoypadTypeCymbalShiftButton(Symbol);
bool JoypadIsShiftButton(int, JoypadButton);

#endif
