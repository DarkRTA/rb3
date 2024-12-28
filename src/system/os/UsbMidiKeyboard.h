#pragma once
#include "os/CritSec.h"
#include "os/Joypad.h"

class UsbMidiKeyboard {
public:
    UsbMidiKeyboard();
    ~UsbMidiKeyboard();

    static bool mUsbMidiKeyboardExists;
    static void Init();
    static void Terminate();
    static void Poll();
    static void SendMessage(const Message& msg){ JoypadPushThroughMsg(msg); }

    int GetSlottedKeyVelocityFromExtended(int, unsigned char*);
    int GetAccelAxisVal(int, int);
    bool GetKeyPressed(int, int);
    int GetKeyVelocity(int, int);
    void SetAccelerometer(int, int, int, int);
    void SetSustain(int, bool);
    void SetStompPedal(int, bool);
    void SetModVal(int, int);
    void SetExpressionPedal(int, int);
    void SetConnectedAccessories(int, int);
    void SetLowHandPlacement(int, int);
    void SetHighHandPlacement(int, int);
    void SetKeyPressed(int, int, bool);
    void SetKeyVelocity(int, int, int);

    bool GetSustain(int i) const { return mSustain[i]; }
    bool GetStompPedal(int i) const { return mStompPedal[i]; }
    int GetModVal(int i) const { return mModVal[i]; }
    int GetExpressionPedal(int i) const { return mExpressionPedal[i]; }
    int GetConnectedAccessory(int i) const { return mConnectedAccessories[i]; }
    int GetLowHandPlacement(int i) const { return mLowHandPlacement[i]; }
    int GetHighHandPlacement(int i) const { return mHighHandPlacement[i]; }

    bool mKeyPressed[4][128]; // 0x0
    int mKeyVelocity[4][128]; // 0x200
    int mModVal[4]; // 0xa00
    int mExpressionPedal[4]; // 0xa10
    int mConnectedAccessories[4]; // 0xa20
    bool mSustain[4]; // 0xa30
    bool mStompPedal[4]; // 0xa34
    int mAccelerometer[4][3]; // 0xa38
    int mLowHandPlacement[4]; // 0xa68
    int mHighHandPlacement[4]; // 0xa78
    int mPadNum; // 0xa88
};

class StaticCriticalSection : public CriticalSection {
public:
    StaticCriticalSection();
    ~StaticCriticalSection();
    static StaticCriticalSection* Instance();
};
