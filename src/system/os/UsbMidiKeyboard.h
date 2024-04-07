#ifndef OS_USBMIDIKEYBOARD_H
#define OS_USBMIDIKEYBOARD_H
#include "os/CritSec.h"

class UsbMidiKeyboard {
public:
    UsbMidiKeyboard();
    ~UsbMidiKeyboard();

    static bool mUsbMidiKeyboardExists;
    static void Init();
    static void Terminate();
    static void Poll();

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

    bool mKeyPressed[4][128];
    int mKeyVelocity[4][128];
    int mModVal[4];
    int mExpressionPedal[4];
    int mConnectedAccessories[4];
    bool mSustain[4];
    bool mStompPedal[4];
    int mAccelerometer[4][3];
    int mLowHandPlacement[4];
    int mHighHandPlacement[4];
    int mPadNum;

};

class StaticCriticalSection : public CriticalSection {
public:
    StaticCriticalSection();
    ~StaticCriticalSection();
    static StaticCriticalSection* Instance();
};

#endif
