#include "meta_band/UIEvent.h"
#include "UIEventMgr.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/Msg.h"
#include "os/Debug.h"
#include "ui/UI.h"
#include "ui/UIMessages.h"
#include "ui/UIScreen.h"
#include "utl/Messages2.h"
#include "utl/Symbols4.h"

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

TransitionEvent::TransitionEvent(DataArray* a1, DataArray* a2) : UIEvent(a1, a2) {

}

DestructiveTransitionEvent::DestructiveTransitionEvent(NetSync* sync, DataArray* a1, DataArray* a2) : TransitionEvent(a1, a2), mNetSync(sync) {

}

void DestructiveTransitionEvent::OnActivate(){

}

void DestructiveTransitionEvent::SetTransitionAndDestination(){
    mTransitionScreen = ObjectDir::Main()->Find<UIScreen>(mEventDef->FindStr(next_screen), true);
    mDestinationScreen = ObjectDir::Main()->Find<UIScreen>(mTransitionScreen->Property(next_screen, true)->Str(), true);
}

bool DestructiveTransitionEvent::IsDestination(const std::vector<UIScreen*>& screens) const {
    return screens.size() == 1 && screens[0] == mDestinationScreen;
}

bool DestructiveTransitionEvent::IsTransitionAllowed(UIScreen* screen) const {
    return screen == mTransitionScreen || screen == mDestinationScreen;
}

NonDestructiveTransitionEvent::NonDestructiveTransitionEvent(NetSync* sync, const std::vector<UIScreen*>& screens) : TransitionEvent(0, 0), mNetSync(sync) {
    mDestState = screens;
    MILO_ASSERT(!mDestState.empty(), 0xAA);
    MILO_ASSERT(mDestState.size() <= 2, 0xAB);
}

Symbol NonDestructiveTransitionEvent::Type() const { return non_destructive_transition; }

void NonDestructiveTransitionEvent::Poll(){
    if(TheUI->GetTransitionState() == kTransitionNone) AttemptNextTransition();
}

bool NonDestructiveTransitionEvent::IsDestination(const std::vector<UIScreen*>& screens) const {
    bool samesizes = mDestState.size() == screens.size();
    if(samesizes){
        std::vector<UIScreen*>::const_iterator sit = mDestState.begin();
        for(std::vector<UIScreen*>::const_iterator it = screens.begin(); it != screens.end(); ++it, ++sit){
            if(*it != *sit) return false;
        }
        return true;
    }
    return samesizes;
}

bool NonDestructiveTransitionEvent::IsTransitionAllowed(UIScreen* screen) const {
    for(int i = 0; i < mDestState.size(); i++){
        if(mDestState[i] == screen) return true;
    }
    return false;
}

void NonDestructiveTransitionEvent::OnActivate(){ AttemptNextTransition(); }

void NonDestructiveTransitionEvent::AttemptNextTransition(){
    
}