#include "os/VirtualKeyboard.h"
#include "os/File.h"

File* gKeyboardFontFile = 0;
void* gKeyboardFont = 0;

void VirtualKeyboard::PlatformTerminate(){}

bool VirtualKeyboard::IsKeyboardShowing(){
    return gKeyboardFontFile != 0;
}

void VirtualKeyboard::RegisterCallback(Callback* cb){
    mCallbacks.push_back(cb);
}

void VirtualKeyboard::NotifyCallbacksOpen(){
    for(std::list<Callback*>::iterator it = mCallbacks.begin(); it != mCallbacks.end(); it++){
        (*it)->KeyboardOpen();
    }
}

void VirtualKeyboard::NotifyCallbacksClose(){
    for(std::list<Callback*>::iterator it = mCallbacks.begin(); it != mCallbacks.end(); it++){
        (*it)->KeyboardClose();
    }
}