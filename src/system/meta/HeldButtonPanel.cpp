#include "meta/HeldButtonPanel.h"
#include "ui/UI.h"
#include "utl/Symbols.h"

HeldButtonPanel::HeldButtonPanel() : mHolder(new ButtonHolder(this, 0)), mHandling(0) {

}

HeldButtonPanel::~HeldButtonPanel(){
    delete mHolder;
}

void HeldButtonPanel::Enter(){
    std::vector<ActionRec> recs;
    DataArray* heldButtonsArr = TypeDef()->FindArray(held_buttons, false);
    if(heldButtonsArr){
        for(int i = 1; i < heldButtonsArr->Size(); i++){
            DataArray* el = heldButtonsArr->Array(i);
            MILO_ASSERT(el, 0x27);
            float innerFloat = el->Float(1);
            if(innerFloat > 0){
                recs.push_back(ActionRec((JoypadAction)el->Int(0), innerFloat, TheUserMgr));
            }
        }
    }
    mHolder->SetHoldActions(recs);
    UIPanel::Enter();
}

void HeldButtonPanel::Exit(){
    std::vector<ActionRec> recs;
    mHolder->SetHoldActions(recs);
    UIPanel::Exit();
}

void HeldButtonPanel::Poll(){
    if(TheUI->FocusPanel() == this) mHolder->Poll();
    else mHolder->ClearHeldButtons();
    UIPanel::Poll();
}

#pragma push
#pragma pool_data off
DataNode HeldButtonPanel::OnMsg(const ProcessedButtonDownMsg& msg){
    if(msg.IsHeldDown()){
        static Message msgButtonHeld(on_button_held, DataNode(0), DataNode(0), DataNode(0), DataNode(0));
        msgButtonHeld->Node(2) = DataNode(msg.GetUser());
        msgButtonHeld->Node(3) = DataNode(msg.GetButton());
        msgButtonHeld->Node(4) = DataNode(msg.GetAction());
        msgButtonHeld->Node(5) = DataNode(msg.GetPadNum());
        Handle(msgButtonHeld, false);
    }
    else {
        static ButtonDownMsg msgButtonDown(0, kPad_L2, kAction_None, 0);
        msgButtonDown->Node(2) = DataNode(msg.GetUser());
        msgButtonDown->Node(3) = DataNode(msg.GetButton());
        msgButtonDown->Node(4) = DataNode(msg.GetAction());
        msgButtonDown->Node(5) = DataNode(msg.GetPadNum());
        mHandling = true;
        Handle(msgButtonDown, false);
        mHandling = false;
    }
    return 1;
}
#pragma pop

BEGIN_HANDLERS(HeldButtonPanel)
    HANDLE_MESSAGE(ProcessedButtonDownMsg)
    if(!mHandling) HANDLE_MEMBER_PTR(mHolder)
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0x7E)
END_HANDLERS