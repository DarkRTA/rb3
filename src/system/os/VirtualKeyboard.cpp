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

void VirtualKeyboard::Terminate(){
    PlatformTerminate();
}

void VirtualKeyboard::ClearKeyboardCallback(){
    mCallbackMsg.erase();
}

BEGIN_HANDLERS(VirtualKeyboard)
    HANDLE(show_keyboard, OnShowKeyboardUI);
    HANDLE_ACTION(clear_callback, ClearKeyboardCallback);
    HANDLE_SUPERCLASS(Hmx::Object);
    HANDLE_CHECK(0x8B);
END_HANDLERS;
