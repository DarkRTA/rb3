#include "os/UsbMidiGuitar.h"
#include "os/CritSec.h"
#include "os/Joypad.h"
#include "os/Debug.h"
#include "os/UsbMidiGuitarMsgs.h"

CriticalSection gCritSection;
Queue gQueue(0x32);
Timer UsbMidiGuitar::mTimer;
UsbMidiGuitar* TheGuitar;
bool UsbMidiGuitar::mUsbMidiGuitarExists = false;
int UsbMidiGuitar::mMinVelocity = 5;

UsbMidiGuitar::UsbMidiGuitar(){
    mPadNum = 0;
    if(!mUsbMidiGuitarExists){
        mUsbMidiGuitarExists = true;
        for(int inc = 0; inc < 4; inc++){
            mConnectedAccessories[inc] = 0;
            mPitchBend[inc] = 0;
            mMuting[inc] = 0;
            mStompBox[inc] = false;
            mProgramChange[inc] = 0;
            
            mStringStrummed[inc][0] = false;
            mStringFret[inc][0] = 0;
            mStringVelocity[inc][0] = 0;
            mLastSixStringsStrummed[inc][0] = 0;
            
            mStringStrummed[inc][1] = false;
            mStringFret[inc][1] = 0;
            mStringVelocity[inc][1] = 0;
            mLastSixStringsStrummed[inc][1] = 0;

            mStringStrummed[inc][2] = false;
            mStringFret[inc][2] = 0;
            mStringVelocity[inc][2] = 0;
            mLastSixStringsStrummed[inc][2] = 0;

            mStringStrummed[inc][3] = false;
            mStringFret[inc][3] = 0;
            mStringVelocity[inc][3] = 0;
            mLastSixStringsStrummed[inc][3] = 0;

            mStringStrummed[inc][4] = false;
            mStringFret[inc][4] = 0;
            mStringVelocity[inc][4] = 0;
            mLastSixStringsStrummed[inc][4] = 0;

            mStringStrummed[inc][5] = false;
            mStringFret[inc][5] = 0;
            mStringVelocity[inc][5] = 0;
            mLastSixStringsStrummed[inc][5] = 0;

            mFretDown[inc][0] = false;
            mFretDown[inc][1] = false;
            mFretDown[inc][2] = false;
            mFretDown[inc][3] = false;
            mFretDown[inc][4] = false;

            mAccelerometer[inc][0] = 0;
            mAccelerometer[inc][1] = 0;
            mAccelerometer[inc][2] = 0;
        }
        mTimer.Init();
        mTimer.Start();
    }
}

UsbMidiGuitar::~UsbMidiGuitar(){
    CritSecTracker tracker(&gCritSection);
}

void UsbMidiGuitar::Init(){
    MILO_ASSERT(TheGuitar == NULL, 0x64);
    TheGuitar = new UsbMidiGuitar();
}

void UsbMidiGuitar::Terminate(){
    MILO_ASSERT(TheGuitar != NULL, 0x6F);
    delete TheGuitar;
    TheGuitar = 0;
}

void UsbMidiGuitar::Poll(){
    unsigned int uVar9;
    char someCharArr[8];
    if(TheGuitar){
        for(int i = 0; i < 4; i++){
            JoypadData* thePadData = JoypadGetPadData(i);
            JoypadType ty = thePadData->mType;
            if(ty == kJoypadXboxButtonGuitar || ty == kJoypadPs3ButtonGuitar || ty == kJoypadWiiButtonGuitar ||
                ty == kJoypadXboxRealGuitar22Fret || ty == kJoypadPs3RealGuitar22Fret || ty == kJoypadWiiRealGuitar22Fret){
                    JoypadData* padData = JoypadGetPadData(i);
                    int curunk50 = padData->unk50;
                    // this loop sets frets and velocities
                    for(int j = 5; j >= 0; j--){
                        int curFret, curVel;
                        switch(j){
                            case 5:
                                curFret = curunk50 & 0x1F;
                                curVel = padData->unk54 & 0x7F;
                                break;
                            case 4:
                                curFret = (curunk50 >> 5) + ((padData->unk50 + 1) & 3) * 8;
                                curVel = padData->unk55 & 0x7F;
                                break;
                            case 3:
                                curFret = (padData->unk50 + 1) >> 2 & 0x1F;
                                curVel = padData->unk56 & 0x7F;
                                break;
                            case 2:
                                curFret = (padData->unk50 + 2) & 0x1F;
                                curVel = padData->unk57 & 0x7F;
                                break;
                            case 1:
                                curFret = ((padData->unk50 + 2) >> 5) + (((padData->unk50 + 3) & 3) * 8);
                                curVel = padData->unk58 & 0x7F;
                                break;
                            default:
                                curFret = (padData->unk50 + 3) >> 2 & 0x1F;
                                curVel = padData->unk58 + 1 & 0x7F;
                                break;
                        }
                        bool mustUpdateVel = (curVel) != TheGuitar->mStringVelocity[i][j];
                        if(mustUpdateVel) TheGuitar->SetVelocity(i, j, curVel);
                        if(curFret != TheGuitar->mStringFret[i][j] && mustUpdateVel){
                            TheGuitar->SetFret(i, j, curFret);
                            TheGuitar->SetVelocity(i, j, curVel);
                            StringStrummedMsg ssmsg(j, curFret, mustUpdateVel != 0, i);
                            JoypadPushThroughMsg(ssmsg);
                            TheGuitar->UpdateStringStrummed(i, j);
                            if((UsbMidiGuitar::mMinVelocity < curVel) && mustUpdateVel){
                                uVar9 = uVar9 | 1 << 5 - j;
                            }
                        }
                    }
                    // this loop sets whether frets are up or down
                    bool RGFretBool = (padData->unk50 + 3) >> 7;
                    for(int k = 0; k < 5; k++){
                        bool padDataFretDown = (padData->unk50 + i + 4) >> 7;
                        bool isTheGuitarFretDown = TheGuitar->mFretDown[i][k];
                        if(padDataFretDown != isTheGuitarFretDown){
                            if(padDataFretDown){
                                TheGuitar->SetFretDown(i, k, true);
                                JoypadPushThroughMsg(RGFretButtonDownMsg(i, k, RGFretBool));
                            }
                            else {
                                TheGuitar->SetFretDown(i, k, false);
                                JoypadPushThroughMsg(RGFretButtonUpMsg(i, k, RGFretBool));
                            }
                        }
                    }
                    if(uVar9 != 0){
                        JoypadPushThroughMsg(RGSwingMsg(uVar9, i));
                    }
                    int axisVal11 = (padData->unk58 + 2) & 0x7F;
                    int axisVal12 = (padData->unk58 + 3) & 0x7F;
                    int axisVal10 = (padData->unk5c) & 0x7F;
                    if(axisVal11 != TheGuitar->CurrentAccelAxisVal(i, 0) ||
                        axisVal12 != TheGuitar->CurrentAccelAxisVal(i, 1) ||
                        axisVal10 != TheGuitar->CurrentAccelAxisVal(i, 2)){
                            TheGuitar->SetAccelerometer(i, axisVal11, axisVal12, axisVal10);
                            JoypadPushThroughMsg(RGAccelerometerMsg(axisVal11, axisVal12, axisVal10, i));
                        }
                    int connAcc = (padData->unk5c + 1) & 0x7F;
                    if(connAcc != TheGuitar->mConnectedAccessories[i]){
                        TheGuitar->SetConnectedAccessories(i, connAcc);
                        JoypadPushThroughMsg(RGConnectedAccessoriesMsg(connAcc, i));
                    }
                    int pitchBend = (padData->unk5c + 1) & 0x7F;
                    if(pitchBend != TheGuitar->mPitchBend[i]){
                        JoypadPushThroughMsg(RGPitchBendMsg(pitchBend, i));
                    }
                    int muting = (padData->unk5c + 2) & 0x7F;
                    if(muting != TheGuitar->mMuting[i]){
                        TheGuitar->SetMuting(i, muting);
                        JoypadPushThroughMsg(RGMutingMsg(muting, i));
                    }
                    bool stompBox = (padData->unk5c + 1) >> 7;
                    if(stompBox != TheGuitar->mStompBox[i]){
                        TheGuitar->SetStompBox(i, stompBox);
                        JoypadPushThroughMsg(RGStompBoxMsg(stompBox, i));
                    }
                    int programChange = ((padData->unk58 + 3) >> 6 & 2) + (padData->unk5c >> 5 & 4) + ((padData->unk58 + 2) >> 7);
                    if(programChange != TheGuitar->mProgramChange[i]){
                        TheGuitar->SetProgramChange(i, programChange);
                        JoypadPushThroughMsg(RGProgramChangeMsg(i, programChange));
                    }
            }
        }
    }
}

int UsbMidiGuitar::E3CheatGetMinVelocity(){
    return mMinVelocity;
}

void UsbMidiGuitar::E3CheatSetMinVelocity(int vel){
    mMinVelocity = vel;
}

int UsbMidiGuitar::CurrentAccelAxisVal(int pad, int str){
    if(0 <= str && (unsigned int)str < 4) return mAccelerometer[pad][str];
    else return 0;
}

void UsbMidiGuitar::SetFret(int pad, int str, int fret){
    mStringFret[pad][str] = fret;
}

void UsbMidiGuitar::SetVelocity(int pad, int str, int vel){
    mStringVelocity[pad][str] = vel;
}

void UsbMidiGuitar::SetAccelerometer(int pad, int a1, int a2, int a3){
    mAccelerometer[pad][0] = a1;
    mAccelerometer[pad][1] = a2;
    mAccelerometer[pad][2] = a3;
}

void UsbMidiGuitar::SetConnectedAccessories(int pad, int accs){
    mConnectedAccessories[pad] = accs;
}

void UsbMidiGuitar::SetPitchBend(int pad, int pb){
    mPitchBend[pad] = pb;
}

void UsbMidiGuitar::SetMuting(int pad, int mute){
    mMuting[pad] = mute;
}

void UsbMidiGuitar::SetStompBox(int pad, bool stomp){
    mStompBox[pad] = stomp;
}

void UsbMidiGuitar::SetProgramChange(int pad, int pc){
    mProgramChange[pad] = pc;
}

void UsbMidiGuitar::SetFretDown(int pad, int str, bool down){
    mFretDown[pad][str] = down;
}

Queue::Queue(int i) : mArrayStart(0) {
    Initialize(i);
}

Queue::~Queue(){
    CritSecTracker tracker(&gCritSection);
    delete mArrayStart;
}

void Queue::Initialize(int i){
    CritSecTracker tracker(&gCritSection);
    delete mArrayStart;
    mArrayStart = new MidiMessage[i + 1];
    mArrayEnd = &mArrayStart[i] + 1;
    mUsurpedFret[0] = mUsurpedFret[1] = mUsurpedFret[2] = mUsurpedFret[3] = mUsurpedFret[4] = mUsurpedFret[5] = -1;
    mQueueStart = mArrayStart;
    mQueueEnd = mArrayStart;
}
