#include "os/UsbMidiGuitar.h"
#include "os/CritSec.h"
#include "os/Joypad.h"
#include "os/Debug.h"
#include "os/UsbMidiGuitarMsgs.h"

CriticalSection gCritSection;
Queue gQueue(0x32);
Timer UsbMidiGuitar::mTimer;
UsbMidiGuitar *TheGuitar;
bool UsbMidiGuitar::mUsbMidiGuitarExists = false;
int UsbMidiGuitar::mMinVelocity = 5;

UsbMidiGuitar::UsbMidiGuitar() {
    mPadNum = 0;
    if (!mUsbMidiGuitarExists) {
        mUsbMidiGuitarExists = true;
        for (int i = 0; i < 4; i++) {
            mConnectedAccessories[i] = 0;
            mPitchBend[i] = 0;
            mMuting[i] = 0;
            mStompBox[i] = false;
            mProgramChange[i] = 0;
            for (int j = 0; j < 6; j++) {
                mStringStrummed[i][j] = false;
                mStringFret[i][j] = 0;
                mStringVelocity[i][j] = 0;
                mLastSixStringsStrummed[i][j] = 0;
            }
            for (int j = 0; j < 5; j++) {
                mFretDown[i][j] = false;
            }
            for (int j = 0; j < 3; j++) {
                mAccelerometer[i][j] = 0;
            }
        }
        mTimer.Init();
        mTimer.Start();
    }
}

UsbMidiGuitar::~UsbMidiGuitar() {
    CritSecTracker tracker(&gCritSection);
    mTimer.Stop();
}

void UsbMidiGuitar::Init() {
    MILO_ASSERT(TheGuitar == NULL, 0x64);
    TheGuitar = new UsbMidiGuitar();
    TheDebug.AddExitCallback(UsbMidiGuitar::Terminate);
}

void UsbMidiGuitar::Terminate() {
    MILO_ASSERT(TheGuitar != NULL, 0x6F);
    RELEASE(TheGuitar);
}

// matches in retail
void UsbMidiGuitar::Poll() {
    if (TheGuitar) {
        ProGuitarData *proData;
        for (int i = 0; i < 4; i++) {
            JoypadType ty = JoypadGetPadData(i)->mType;
            if (ty == kJoypadXboxButtonGuitar || ty == kJoypadPs3ButtonGuitar
                || ty == kJoypadWiiButtonGuitar || ty == kJoypadXboxRealGuitar22Fret
                || ty == kJoypadPs3RealGuitar22Fret || ty == kJoypadWiiRealGuitar22Fret) {
                proData = &JoypadGetPadData(i)->mProGuitarData;
                unsigned int uVar9 = 0;
                for (int j = 5; j >= 0; j--) {
                    int curFret, curVel;
                    switch (j) {
                    case 5:
                        curFret = proData->mString5Fret;
                        curVel = proData->mString5Velocity;
                        break;
                    case 4:
                        curFret = proData->mString4FretTopHalf * 8
                            + proData->mString4FretBottomHalf;
                        curVel = proData->mString4Velocity;
                        break;
                    case 3:
                        curFret = proData->mString3Fret;
                        curVel = proData->mString3Velocity;
                        break;
                    case 2:
                        curFret = proData->mString2Fret;
                        curVel = proData->mString2Velocity;
                        break;
                    case 1:
                        curFret = proData->mString1FretTopHalf * 8
                            + proData->mString1FretBottomHalf;
                        curVel = proData->mString1Velocity;
                        break;
                    default:
                        curFret = proData->mString0Fret;
                        curVel = proData->mString0Velocity;
                        break;
                    }
                    bool velUpdated = false;
                    if (curVel != TheGuitar->GetVelocity(i, j)) {
                        TheGuitar->SetVelocity(i, j, curVel);
                        velUpdated = true;
                    }
                    if (curFret != TheGuitar->GetFret(i, j) || velUpdated) {
                        TheGuitar->SetFret(i, j, curFret);
                        TheGuitar->SetVelocity(i, j, curVel);
                        StringStrummedMsg ssmsg(
                            j, curFret, curVel & -(velUpdated != 0), i
                        );
                        SendMessage(ssmsg);
                        TheGuitar->UpdateStringStrummed(i, j);
                        if ((curVel > UsbMidiGuitar::mMinVelocity) && velUpdated) {
                            uVar9 |= 1 << (5 - j);
                        }
                    }
                }
                volatile bool someCharArr[8]; // volatile for usb?
                bool RGFretBool = proData->unk3upper;
                for (int k = 0; k < 5; k++) {
                    bool padDataFretDown = proData->mStringInfos[k].mDown;
                    someCharArr[k] = padDataFretDown;
                    if (padDataFretDown != TheGuitar->GetFretDown(i, k)) {
                        if (padDataFretDown) {
                            TheGuitar->SetFretDown(i, k, true);
                            SendMessage(RGFretButtonDownMsg(k, i, RGFretBool));
                        } else {
                            TheGuitar->SetFretDown(i, k, false);
                            SendMessage(RGFretButtonUpMsg(k, i, RGFretBool));
                        }
                    }
                }
                if (uVar9 != 0) {
                    SendMessage(RGSwingMsg(uVar9, i));
                }
                int axisVal11 = proData->unkachar;
                int axisVal12 = proData->unkbchar;
                int axisVal10 = proData->unkcchar;
                if (axisVal11 != TheGuitar->CurrentAccelAxisVal(i, 0)
                    || axisVal12 != TheGuitar->CurrentAccelAxisVal(i, 1)
                    || axisVal10 != TheGuitar->CurrentAccelAxisVal(i, 2)) {
                    TheGuitar->SetAccelerometer(i, axisVal11, axisVal12, axisVal10);
                    SendMessage(RGAccelerometerMsg(axisVal11, axisVal12, axisVal10, i));
                }
                int connAcc = proData->unkdchar;
                if (connAcc != TheGuitar->GetConnectedAccessory(i)) {
                    TheGuitar->SetConnectedAccessories(i, connAcc);
                    SendMessage(RGConnectedAccessoriesMsg(connAcc, i));
                }
                int pitchBend = proData->unkdchar;
                if (pitchBend != TheGuitar->GetPitchBend(i)) {
                    TheGuitar->SetPitchBend(i, pitchBend);
                    SendMessage(RGPitchBendMsg(pitchBend, i));
                }
                int muting = proData->mMuting;
                if (muting != TheGuitar->GetMuting(i)) {
                    TheGuitar->SetMuting(i, muting);
                    SendMessage(RGMutingMsg(muting, i));
                }
                bool stompBox = proData->mStompBox;
                if (stompBox != TheGuitar->GetStompBox(i)) {
                    TheGuitar->SetStompBox(i, stompBox);
                    SendMessage(RGStompBoxMsg(stompBox, i));
                }
                int programChange = proData->unkabool + (proData->unkbbool << 1)
                    + (proData->unkcbool << 2);
                if (programChange != TheGuitar->GetProgramChange(i)) {
                    TheGuitar->SetProgramChange(i, programChange);
                    SendMessage(RGProgramChangeMsg(programChange, i));
                }
            }
        }
    }
}

int UsbMidiGuitar::E3CheatGetMinVelocity() { return mMinVelocity; }

void UsbMidiGuitar::E3CheatSetMinVelocity(int vel) { mMinVelocity = vel; }

// axes are presumably X, Y, Z
int UsbMidiGuitar::CurrentAccelAxisVal(int pad, int axis) {
    if (0 <= axis && (unsigned int)axis < 4)
        return mAccelerometer[pad][axis];
    else
        return 0;
}

void UsbMidiGuitar::SetFret(int pad, int str, int fret) { mStringFret[pad][str] = fret; }

void UsbMidiGuitar::SetVelocity(int pad, int str, int vel) {
    mStringVelocity[pad][str] = vel;
}

void UsbMidiGuitar::SetAccelerometer(int pad, int a1, int a2, int a3) {
    mAccelerometer[pad][0] = a1;
    mAccelerometer[pad][1] = a2;
    mAccelerometer[pad][2] = a3;
}

void UsbMidiGuitar::SetConnectedAccessories(int pad, int accs) {
    mConnectedAccessories[pad] = accs;
}

void UsbMidiGuitar::SetPitchBend(int pad, int pb) { mPitchBend[pad] = pb; }

void UsbMidiGuitar::SetMuting(int pad, int mute) { mMuting[pad] = mute; }

void UsbMidiGuitar::SetStompBox(int pad, bool stomp) { mStompBox[pad] = stomp; }

void UsbMidiGuitar::SetProgramChange(int pad, int pc) { mProgramChange[pad] = pc; }

void UsbMidiGuitar::SetFretDown(int pad, int str, bool down) {
    mFretDown[pad][str] = down;
}

void UsbMidiGuitar::UpdateStringStrummed(int pad, int str) {
    for (int i = 6; i > 0; i--) {
        mLastSixStringsStrummed[pad][i] = mLastSixStringsStrummed[pad][i - 1];
    }
    mLastSixStringsStrummed[pad][0] = str;
}

Queue::Queue(int i) : mArrayStart(0) { Initialize(i); }

Queue::~Queue() {
    CritSecTracker tracker(&gCritSection);
    delete mArrayStart;
}

void Queue::Initialize(int i) {
    CritSecTracker tracker(&gCritSection);
    delete mArrayStart;
    mArrayStart = new MidiMessage[i + 1];
    mArrayEnd = &mArrayStart[i] + 1;
    mUsurpedFret[0] = mUsurpedFret[1] = mUsurpedFret[2] = mUsurpedFret[3] =
        mUsurpedFret[4] = mUsurpedFret[5] = -1;
    mQueueStart = mArrayStart;
    mQueueEnd = mArrayStart;
}

DECOMP_FORCEACTIVE(UsbMidiGuitar, "queue full\n", "queue empty\n")