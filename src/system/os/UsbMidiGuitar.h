#ifndef OS_USBMIDIGUITAR_H
#define OS_USBMIDIGUITAR_H
#include "os/Timer.h"

class UsbMidiGuitar {
public:
    UsbMidiGuitar();
    ~UsbMidiGuitar();

    static bool mUsbMidiGuitarExists;
    static Timer mTimer;

    bool mStringStrummed[4][6];
    int mStringFret[4][6];
    int mStringVelocity[4][6];
    bool mFretDown[4][5]; // could be wrong?
    int mAccelerometer[4][3];
    int mConnectedAccessories[4];
    int mPitchBend[4];
    int mMuting[4];
    bool mStompBox[4];
    int mProgramChange[4];
    int mLastSixStringsStrummed[4][6]; // take another look at this and mPadNum maybe?
    int mPadNum;

};

#endif
