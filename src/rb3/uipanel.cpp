#include "uipanel.hpp"
#include "messages.hpp"

extern int lbl_80988298;

UIPanel::UIPanel() : 
    unk8(0), unkc(0), str(), unk1c(0), unk20(0), unk21(0), unk22(1), unk23(0), unk24(0), fpath() {
        unk34 = lbl_80988298++;
}

void UIPanel::CheckUnload(){
    if(unk24 >= 1){
        if(unk1c == 2){
            DataNode handled = Handle(MsgExitComplete.GetArray(), false);
        }
        if(--unk24 == 0){
            Unload();
        }
    }
}