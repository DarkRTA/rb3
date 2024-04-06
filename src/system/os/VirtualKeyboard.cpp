#include "os/VirtualKeyboard.h"
#include "obj/Dir.h"
#include "utl/Symbols.h"

VirtualKeyboard TheVirtualKeyboard;

VirtualKeyboard::VirtualKeyboard() : mPobjKeyboardCallback(0), mCallbackReady(0), mMsgOk(0), mCallbackMsg() {

}

VirtualKeyboard::~VirtualKeyboard(){

}

void VirtualKeyboard::Init(){
    SetName("virtual_keyboard", ObjectDir::Main());
}

void VirtualKeyboard::Poll(){
    PlatformPoll();
    if(mCallbackReady){
        VirtualKeyboardResultMsg msg(mMsgOk, mCallbackMsg.c_str());
        if(mPobjKeyboardCallback){
            mPobjKeyboardCallback->Handle(msg, true);
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

DataNode VirtualKeyboard::OnShowKeyboardUI(const DataArray* array){
    LocalUser* u = array->Obj<LocalUser>(2);
    int i3 = array->Int(3);
    class String s4(array->Str(4));
    class String s5(array->Str(5));
    class String s6(array->Str(6));
    mPobjKeyboardCallback = array->GetObj(7);
    int i8 = 0;
    int i9 = 0;
    if(array->Size() >= 9) i8 = array->Int(8);
    if(array->Size() >= 10) i9 = array->Int(9);
    return ShowKeyboardUI(u, i3, s4, s5, s6, i8, i9);
}

void VirtualKeyboard::ClearKeyboardCallback(){
    mPobjKeyboardCallback = 0;
}

BEGIN_HANDLERS(VirtualKeyboard)
    HANDLE(show_keyboard, OnShowKeyboardUI);
    HANDLE_ACTION(clear_callback, ClearKeyboardCallback());
    HANDLE_SUPERCLASS(Hmx::Object);
    HANDLE_CHECK(0x8B);
END_HANDLERS;
