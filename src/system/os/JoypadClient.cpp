#include "os/JoypadClient.h"
#include "os/Debug.h"

namespace {
    JoypadButton LeftStickToDpad(JoypadButton btn){
        JoypadButton ret;
        switch(btn){
            case kPad_LStickUp: return kPad_DUp;
            case kPad_LStickDown: return kPad_DDown;
            case kPad_LStickLeft: return kPad_DLeft;
            case kPad_LStickRight: return kPad_DRight;
            default:
                MILO_FAIL("illegal button");
                return kPad_NumButtons;
        }
    }
}

JoypadRepeat::JoypadRepeat() : mLastBtn(kPad_NumButtons), mLastAction(kAction_None), mLastPad(-1) {
    
}

void JoypadRepeat::Start(JoypadButton btn, JoypadAction act, int pad){
    mHoldTimer.Reset();
    mRepeatTimer.Reset();
    mHoldTimer.Start();
    mLastBtn = btn;
    mLastAction = act;
    mLastPad = pad;
}

void JoypadRepeat::Reset(JoypadButton btn){
    if(mLastBtn == btn){
        mHoldTimer.Reset();
        mRepeatTimer.Reset();
    }
}
