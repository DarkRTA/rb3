#include "ui/Panel.h"
#include "messages.hpp"

extern int lbl_80988298; // wonder if this lbl represents total panel count, and unk34 of a UIPanel is its unique panel id?

UIPanel::UIPanel() : 
    panel(0), unkc(0), focus(), unk1c(0), loaded(0), paused(false), showing(true), forceExit(false), refCount(0), fpath() {
        unk34 = lbl_80988298++;
}

void UIPanel::CheckLoad(){
    if(++refCount != 1) return;
    Load();
}

void UIPanel::CheckUnload(){
    if(refCount >= 1){
        if(unk1c == 2){
            DataNode handled = Handle(MsgExitComplete.GetArray(), false);
        }
        if(--refCount == 0){
            Unload();
        }
    }
}

bool UIPanel::IsLoaded(){
    if(unk1c != 0) return true;
}

void UIPanel::FinishLoad(){
    {
    DataNode handled = HandleType(MsgFinishLoad.GetArray());
    }
    unk1c = 2;
}

UIPanel::~UIPanel(){
    Unload();
}
