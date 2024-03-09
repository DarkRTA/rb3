#include "os/HolmesKeyboard.h"

HolmesInput::HolmesInput(CWnd* cwnd){
    mJoypadBuffer = new MemStream(true);
    mKeyboardBuffer = new MemStream(true);
    mOwner = cwnd;
}

HolmesInput::~HolmesInput(){
    delete mKeyboardBuffer;
    mKeyboardBuffer = 0;
    delete mJoypadBuffer;
    mJoypadBuffer = 0;
}
