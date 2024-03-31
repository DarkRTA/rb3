#ifndef OS_USBMIDIGUITAR_H
#define OS_USBMIDIGUITAR_H
#include "os/Timer.h"
#include "midi/Midi.h"

class UsbMidiGuitar {
public:
    UsbMidiGuitar();
    ~UsbMidiGuitar();

    static bool mUsbMidiGuitarExists;
    static Timer mTimer;
    static int mMinVelocity;

    static void Init();
    static void Terminate();

    int E3CheatGetMinVelocity();
    static void E3CheatSetMinVelocity(int);
    int CurrentAccelAxisVal(int, int);
    void SetFret(int, int, int);
    void SetVelocity(int, int, int);
    void SetAccelerometer(int, int, int, int);
    void SetConnectedAccessories(int, int);
    void SetPitchBend(int, int);
    void SetMuting(int, int);
    void SetStompBox(int, bool);
    void SetProgramChange(int, int);
    void SetFretDown(int, int, bool);

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

class Queue {
public:
    Queue(int);
    ~Queue();
    void Initialize(int);

    MidiMessage* mArrayStart;
    MidiMessage* mArrayEnd;
    MidiMessage* mQueueStart;
    MidiMessage* mQueueEnd;
    int mUsurpedFret[6];
    // int mUsurpedTime[6];
};

#endif
