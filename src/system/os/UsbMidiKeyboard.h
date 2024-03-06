#ifndef OS_USBMIDIKEYBOARD_H
#define OS_USBMIDIKEYBOARD_H

class UsbMidiKeyboard {
public:
    UsbMidiKeyboard();
    ~UsbMidiKeyboard();

    bool mKeyPressed[8][128];
    int mKeyVelocity[8][128];
    int mModVal[8];
    int mExpressionPedal[8];
    int mConnectedAccessories[8];
    bool mSustain[8];
    bool mStompPedal[8];
    int mAccelerometer[8][3];
    int mLowHandPlacement[8];
    int mHighHandPlacement[8];
    int mPadNum;

};

#endif
