#ifndef OS_JOYPAD_H
#define OS_JOYPAD_H
#include "utl/Symbol.h"
#include "obj/Msg.h"

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
    kJoypadXboxRoDrums = 10,
    kJoypadXboxStageKit = 11,
    kJoypadPs3HxGuitar = 12,
    kJoypadPs3HxGuitarRb2 = 13,
    kJoypadPs3HxDrums = 14,
    kJoypadPs3HxDrumsRb2 = 15,
    kJoypadPs3RoGuitar = 16,
    kJoypadPs3RoDrums = 17,
    kJoypadPs3KonamiDrums = 18,
    kJoypadWiiCore = 19,
    kJoypadWiiFS = 20,
    kJoypadWiiClassic = 21,
    kJoypadWiiGamecube = 22,
    kJoypadWiiGuitar = 23,
    kJoypadWiiDrums = 24,
    kJoypadWiiHxGuitar = 25,
    kJoypadWiiHxGuitarRb2 = 26,
    kJoypadWiiHxDrums = 27,
    kJoypadWiiHxDrumsRb2 = 28,
    kJoypadXboxCoreGuitar = 29,
    kJoypadXboxButtonGuitar = 30,
    kJoypadXboxRealGuitar22Fret = 31,
    kJoypadXboxMidiBoxKeyboard = 32,
    kJoypadXboxMidiBoxDrums = 33,
    kJoypadXboxKeytar = 34,
    kJoypadPs3CoreGuitar = 35,
    kJoypadPs3ButtonGuitar = 36,
    kJoypadPs3RealGuitar22Fret = 37,
    kJoypadPs3MidiBoxKeyboard = 38,
    kJoypadPs3MidiBoxDrums = 39,
    kJoypadPs3Keytar = 40,
    kJoypadWiiCoreGuitar = 41,
    kJoypadWiiButtonGuitar = 42,
    kJoypadWiiRealGuitar22Fret = 43,
    kJoypadWiiMidiBoxKeyboard = 44,
    kJoypadWiiMidiBoxDrums = 45,
    kJoypadWiiKeytar = 46,
    kJoypadNumTypes = 47
};

class JoypadData {
public:
    unsigned int mButtons;
    unsigned int mNewPressed;
    unsigned int mNewReleased;
    float mSticks[2][2]; // LX, LY, RX, RY
    float mTriggers[2]; // LT, RT
    float mSensors[3]; // SX, SY, SZ
    float mPressures[8];

    int unk50;
    bool unk54, unk55, unk56, unk57;
    int unk58, unk5c;

    class LocalUser* mUser;
    bool mConnected;
    bool mVibrateEnabled;

    bool unk66, unk67, unk68;

    bool mHasAnalogSticks;
    bool mTranslateSticks;
    int mIgnoreButtonMask;
    int mGreenCymbalMask;
    int mYellowCymbalMask;
    int mBlueCymbalMask;
    int mSecondaryPedalMask;
    int mCymbalMask;
    bool mIsDrum;
    JoypadType mType;
    Symbol mControllerType;
    float mDistFromRest;
    bool mHasGreenCymbal;
    bool mHasYellowCymbal;
    bool mHasBlueCymbal;
    
    int unk98;

    JoypadData();
    float GetAxis(Symbol) const;
    int FloatToBucket(float) const;
    int GetVelocityBucket(Symbol) const;
    int GetPressureBucket(JoypadButton) const;
};

class LocalUser; // forward dec

extern "C" bool JoypadIsCalbertGuitar(int);
extern "C" int ButtonToVelocityBucket(JoypadData*, JoypadButton);
extern "C" void JoypadInitCommon(class DataArray*);
extern "C" void AssociateUserAndPad(LocalUser*, int);
extern "C" void ResetAllUsersPads();
extern "C" int GetUsersPadNum(LocalUser*);
extern "C" LocalUser* JoypadGetUserFromPadNum(int);
extern "C" int JoypadGetUsersPadNum(LocalUser*);

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
JoypadAction ButtonToAction(JoypadButton, Symbol);

bool UserHasController(LocalUser*);
bool UserHasGHDrums(LocalUser*);
bool UserHas22FretGuitar(LocalUser*);
bool UserHasButtonGuitar(LocalUser*);

// forward dec
namespace Hmx { class Object; }

void JoypadSubscribe(Hmx::Object*);
void JoypadUnsubscribe(Hmx::Object*);
void JoypadPushThroughMsg(const Message&);

#endif
