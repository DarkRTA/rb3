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
    mTimer.Stop();
}

void UsbMidiGuitar::Init(){
    MILO_ASSERT(TheGuitar == NULL, 0x64);
    TheGuitar = new UsbMidiGuitar();
    TheDebug.AddExitCallback(UsbMidiGuitar::Terminate);
}

void UsbMidiGuitar::Terminate(){
    MILO_ASSERT(TheGuitar != NULL, 0x6F);
    delete TheGuitar;
    TheGuitar = 0;
}

// https://decomp.me/scratch/Kfn0h
void UsbMidiGuitar::Poll(){
    char someCharArr[8];
    if(TheGuitar){
        for(int i = 0; i < 4; i++){
            JoypadData* thePadData = JoypadGetPadData(i);
            JoypadType ty = thePadData->mType;
            if(ty == kJoypadXboxButtonGuitar || ty == kJoypadPs3ButtonGuitar || ty == kJoypadWiiButtonGuitar ||
                ty == kJoypadXboxRealGuitar22Fret || ty == kJoypadPs3RealGuitar22Fret || ty == kJoypadWiiRealGuitar22Fret){
                    JoypadData* padData = JoypadGetPadData(i);
                    // here, assign a pointer to padData's struct for pro guitar data
                    ProGuitarData* proData = &padData->mProData.guitarData;
                    // this loop sets frets and velocities
                    unsigned int uVar9 = 0;
                    for(int j = 5; j >= 0; j--){
                        int curFret, curVel;
                        switch(j){
                            case 5:
                                curFret = proData->mString5Fret;
                                curVel = proData->mString5Velocity;
                                break;
                            case 4:
                                // concatenate 2 bit and 3 bit numbers to make one big 5 bit number
                                curFret = proData->mString4FretTopHalf * 8 + proData->mString4FretBottomHalf; 
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
                                curFret = proData->mString1FretTopHalf * 8 + proData->mString1FretBottomHalf;
                                curVel = proData->mString1Velocity;
                                break;
                            default:
                                curFret = proData->mString0Fret;
                                curVel = proData->mString0Velocity;
                                break;
                        }
                        bool velUpdated = false;
                        if(curVel != TheGuitar->mStringVelocity[i][j]){
                            TheGuitar->SetVelocity(i, j, curVel);
                            velUpdated = true;
                        }
                        if(curFret != TheGuitar->mStringFret[i][j] || velUpdated){
                            TheGuitar->SetFret(i, j, curFret);
                            TheGuitar->SetVelocity(i, j, curVel);
                            StringStrummedMsg ssmsg(j, curFret, curVel & velUpdated != 0, i);
                            JoypadPushThroughMsg(ssmsg);
                            TheGuitar->UpdateStringStrummed(i, j);
                            if((curVel > UsbMidiGuitar::mMinVelocity) && velUpdated){
                                uVar9 = uVar9 | 1 << 5 - j;
                            }
                        }
                    }
                    // this loop sets whether frets are up or down
                    bool RGFretBool = proData->unk3upper; // shifted?
                    for(int k = 0; k < 5; k++){
                        // this part needs work
                        // i assume judging by the fact there's a neg in the asm,
                        // there's either a char assignment or a branchless comparison being assigned to a bool
                        bool padDataFretDown = (proData + k + 4); // accesses the bool bitfield of proData with offset k + 4?
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
                    int axisVal11 = proData->unkachar;
                    int axisVal12 = proData->unkbchar;
                    int axisVal10 = proData->unkcchar;
                    if(axisVal11 != TheGuitar->CurrentAccelAxisVal(i, 0) ||
                        axisVal12 != TheGuitar->CurrentAccelAxisVal(i, 1) ||
                        axisVal10 != TheGuitar->CurrentAccelAxisVal(i, 2)){
                            TheGuitar->SetAccelerometer(i, axisVal11, axisVal12, axisVal10);
                            JoypadPushThroughMsg(RGAccelerometerMsg(axisVal11, axisVal12, axisVal10, i));
                        }
                    int connAcc = proData->unkdchar;
                    if(connAcc != TheGuitar->mConnectedAccessories[i]){
                        TheGuitar->SetConnectedAccessories(i, connAcc);
                        JoypadPushThroughMsg(RGConnectedAccessoriesMsg(connAcc, i));
                    }
                    int pitchBend = proData->unkdchar;
                    if(pitchBend != TheGuitar->mPitchBend[i]){
                        TheGuitar->SetPitchBend(i, pitchBend);
                        JoypadPushThroughMsg(RGPitchBendMsg(pitchBend, i));
                    }
                    int muting = proData->mMuting;
                    if(muting != TheGuitar->mMuting[i]){
                        TheGuitar->SetMuting(i, muting);
                        JoypadPushThroughMsg(RGMutingMsg(muting, i));
                    }
                    bool stompBox = proData->mStompBox;
                    if(stompBox != TheGuitar->mStompBox[i]){
                        TheGuitar->SetStompBox(i, stompBox);
                        JoypadPushThroughMsg(RGStompBoxMsg(stompBox, i));
                    }
                    // these bits could be combined together into one 3 bit value?
                    // from MSB to LSB: unkcbool, unkbbool, unkabool
                    int programChange = proData->unkcbool + proData->unkbbool + proData->unkabool;
                    if(programChange != TheGuitar->mProgramChange[i]){
                        TheGuitar->SetProgramChange(i, programChange);
                        JoypadPushThroughMsg(RGProgramChangeMsg(programChange, i));
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

// axes are presumably X, Y, Z
int UsbMidiGuitar::CurrentAccelAxisVal(int pad, int axis){
    if(0 <= axis && (unsigned int)axis < 4) return mAccelerometer[pad][axis];
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
