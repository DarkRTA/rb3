#include "UIPanel.h"
#include "messages.hpp"

extern int lbl_80988298; // wonder if this lbl represents total panel count, and unk34 of a UIPanel is its unique panel id?

UIPanel::UIPanel() : 
    panel(0), unkc(0), focus(), mState(kUnloaded), loaded(0), paused(false), showing(true), forceExit(false), refCount(0), fpath() {
        unk34 = lbl_80988298++;
}

void UIPanel::CheckLoad(){
    if(++refCount != 1) return;
    Load();
}

void UIPanel::CheckUnload(){
    if(refCount >= 1){
        if(mState == kDown){
            DataNode handled = Handle(MsgExitComplete.GetArray(), false);
        }
        if(--refCount == 0){
            Unload();
        }
    }
}

bool UIPanel::IsLoaded(){
    if(mState != kUnloaded) return true;
}

void UIPanel::FinishLoad(){
    {
    DataNode handled = HandleType(MsgFinishLoad.GetArray());
    }
    mState = kDown;
}

UIPanel::~UIPanel(){
    Unload();
}
