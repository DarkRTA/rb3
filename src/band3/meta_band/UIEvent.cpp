#include "meta_band/UIEvent.h"
#include "UIEventMgr.h"
#include "obj/Data.h"
#include "obj/Msg.h"
#include "os/Debug.h"
#include "ui/UIMessages.h"
#include "utl/Messages2.h"

UIEvent::UIEvent(DataArray* a1, DataArray* a2) : mEventDef(a1), mActive(0) {
    if(a2) mEventInit = a2->Clone(true, true, 0);
}

UIEvent::~UIEvent(){

}

Symbol UIEvent::Type() const {
    MILO_ASSERT(mEventDef, 0x20);
    return mEventDef->Sym(0);
}

void UIEvent::Activate(){
    mActive = true;
    OnActivate();
}

void UIEvent::Dismiss(){
    mActive = false;
    OnDismiss();
    if(mEventDef){
        DataArray* dismissArr = mEventDef->FindArray("on_dismiss", false);
        if(dismissArr) dismissArr->ExecuteScript(1, nullptr, mEventInit, 2);
    }
}

DialogEvent::DialogEvent(DataArray* a1, DataArray* a2) : UIEvent(a1, a2) {

}

void DialogEvent::OnActivate(){
    static EventDialogStartMsg msg(mEventDef, init_msg);
    msg[0] = DataNode(mEventDef, kDataArray);
    if(mEventInit->Size() == 0){
        mEventInit = init_msg;
    }
    msg[1] = mEventInit;
    TheUIEventMgr->Export(msg, true);
}

void DialogEvent::OnDismiss(){
    static EventDialogDismissMsg dismiss;
    TheUIEventMgr->Export(dismiss, true);
}

bool DialogEvent::AllowsOverride() const {
    MILO_ASSERT(mEventDef, 0x5A);
    DataArray* overrideArr = mEventDef->FindArray("allows_override", false);
    if(overrideArr) return overrideArr->Int(1);
    else return true;
}