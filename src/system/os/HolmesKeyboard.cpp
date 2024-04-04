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

void HolmesInput::LoadKeyboard(BinStream& bs){
    int asdf;
    mKeyboardBuffer->Seek(0, BinStream::kSeekEnd);
    bs >> asdf;
    if(0 < asdf){
        mKeyboardBuffer->WriteStream(bs, asdf);
    }
}

void HolmesInput::LoadJoypad(BinStream& bs){
    int asdf;
    mKeyboardBuffer->Seek(0, BinStream::kSeekEnd);
    bs >> asdf;
    if(0 < asdf){
        mJoypadBuffer->WriteStream(bs, asdf);
    }
}
