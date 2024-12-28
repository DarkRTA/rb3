#pragma once
#include "os/Timer.h"
#include "midi/Midi.h"
#include "os/Joypad.h"

class UsbMidiGuitar {
public:
    UsbMidiGuitar();
    ~UsbMidiGuitar();

    static bool mUsbMidiGuitarExists;
    static Timer mTimer;
    static int mMinVelocity;

    static void Init();
    static void Terminate();
    static void Poll();
    static void SendMessage(const Message& msg){ JoypadPushThroughMsg(msg); }

    static int E3CheatGetMinVelocity();
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
    void UpdateStringStrummed(int, int);

    int GetFret(int pad, int str) const {
        return mStringFret[pad][str];
    }

    int GetVelocity(int pad, int str) const {
        return mStringVelocity[pad][str];
    }

    int GetConnectedAccessory(int i) const {
        return mConnectedAccessories[i];
    }

    int GetPitchBend(int i) const {
        return mPitchBend[i];
    }

    int GetMuting(int i) const {
        return mMuting[i];
    }

    bool GetStompBox(int i) const {
        return mStompBox[i];
    }

    int GetProgramChange(int i) const {
        return mProgramChange[i];
    }

    bool GetFretDown(int i, int j) const {
        return mFretDown[i][j];
    }

    bool mStringStrummed[4][6]; // 0x0
    int mStringFret[4][6]; // 0x18
    int mStringVelocity[4][6]; // 0x78
    bool mFretDown[4][5]; // 0xd8 - could be wrong?
    int mAccelerometer[4][3]; // 0xec
    int mConnectedAccessories[4]; // 0x11c
    int mPitchBend[4]; // 0x12c
    int mMuting[4]; // 0x13c
    bool mStompBox[4]; // 0x14c
    int mProgramChange[4]; // 0x150
    int mLastSixStringsStrummed[4][6]; // 0x160 - take another look at this and mPadNum maybe?
    int mPadNum; // 0x1c0

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
