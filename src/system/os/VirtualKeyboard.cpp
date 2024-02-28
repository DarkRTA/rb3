#include "os/VirtualKeyboard.h"
#include "obj/Dir.h"
#include "utl/Symbols.h"

VirtualKeyboard TheVirtualKeyboard;

VirtualKeyboard::VirtualKeyboard() : mPobjKeyboardCallback(0), mCallbackReady(0), mMsgOk(0), mCallbackMsg() {

}

VirtualKeyboard::~VirtualKeyboard(){
    
}

void VirtualKeyboard::Init(){
    SetName("virtual_keyboard", ObjectDir::sMainDir);
}

void VirtualKeyboard::Poll(){
    PlatformPoll();
    if(mCallbackReady){
        VirtualKeyboardResultMsg msg(mMsgOk, mCallbackMsg.c_str());
        if(mPobjKeyboardCallback){
            mPobjKeyboardCallback->Handle(msg.Data(), true);
        }
        mPobjKeyboardCallback = 0;
        mCallbackMsg = gNullStr;
        mMsgOk = false;
        mCallbackReady = false;
    }   
}

void VirtualKeyboard::Terminate(){
    PlatformTerminate();
}

void VirtualKeyboard::ClearKeyboardCallback(){
    mPobjKeyboardCallback = 0;
}

BEGIN_HANDLERS(VirtualKeyboard)
    HANDLE(show_keyboard, OnShowKeyboardUI);
    HANDLE_ACTION(clear_callback, ClearKeyboardCallback);
    HANDLE_SUPERCLASS(Hmx::Object);
    HANDLE_CHECK(0x8B);
END_HANDLERS;
