#include "os/UsbMidiGuitar.h"
#include "os/CritSec.h"
#include "os/Debug.h"

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
