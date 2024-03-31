#include "os/UsbMidiGuitar.h"

UsbMidiGuitar* TheGuitar;
bool UsbMidiGuitar::mUsbMidiGuitarExists = false;

UsbMidiGuitar::UsbMidiGuitar(){
    mPadNum = 0;
    if(!mUsbMidiGuitarExists){
        mUsbMidiGuitarExists = true;
        int inc = 0;
        for(int i = 0; i < 4; i++){
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
            inc++;
        }
        mTimer.Init();
        mTimer.Start();
    }
}
