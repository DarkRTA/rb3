#ifndef OS_USBMIDIGUITAR_H
#define OS_USBMIDIGUITAR_H
#include "os/Timer.h"

class UsbMidiGuitar {
public:
    UsbMidiGuitar();
    ~UsbMidiGuitar();

    static bool mUsbMidiGuitarExists;
    static Timer mTimer;

    bool mStringStrummed[8][6];
    int mStringFret[8][6];
    int mStringVelocity[8][6];
    int mAccelerometer[8][3];
    int mConnectedAccessories[8];
    int mPitchBend[8];
    int mMuting[8];
    bool mStompBox[8];
    int mProgramChange[8];
    int mLastSixStringsStrummed[8][6];
    int mPadNum;

};

#endif
