#include "meta_band/UIEventMgr.h"
#include "NetSync.h"
#include "decomp.h"
#include "meta_band/UIEvent.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/Msg.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/System.h"
#include "utl/Std.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"

UIEventMgr* TheUIEventMgr;

UIEventQueue::UIEventQueue(){

}

UIEventQueue::~UIEventQueue(){
    DeleteAll(mEventQueue);
}

void UIEventQueue::Poll(){
    if(!mEventQueue.empty() && mEventQueue.front()->IsActive()){
        mEventQueue.front()->Poll();
    }
}

void UIEventQueue::DismissEvent(){
    MILO_ASSERT(!mEventQueue.empty(), 0x28);
    MILO_ASSERT(mEventQueue.front()->IsActive(), 0x29);
    UIEvent* event = mEventQueue.front();
    mEventQueue.erase(mEventQueue.begin());
    event->Dismiss();
    delete event;
    CheckActivateEvent();
}

void UIEventQueue::TriggerEvent(UIEvent* event){
    UIEvent* cur;
    while(!mEventQueue.empty() && (cur = mEventQueue.back())->AllowsOverride()) {
        if(mEventQueue.size() == 1 && cur->IsActive()) {
            DismissEvent();
        }
        else {
            delete cur;
            mEventQueue.pop_back();
        }
    }
    mEventQueue.push_back(event);
    CheckActivateEvent();
}

void UIEventQueue::CheckActivateEvent(){
    if(!mEventQueue.empty() && !mEventQueue.front()->IsActive()){
        mEventQueue.front()->Activate();
    }
}

UIEvent* UIEventQueue::CurrentEvent() const {
    if(!mEventQueue.empty()) return mEventQueue.front();
    else return nullptr;
}

bool UIEventQueue::HasEvent(Symbol s) const {
    for(int i = 0; i < mEventQueue.size(); i++){
        if(mEventQueue[i]->Type() == s) return true;
    }
    return false;
}

void UIEventMgr::Init(){
    MILO_ASSERT(!TheUIEventMgr, 0x83);
    TheUIEventMgr = new UIEventMgr();
    TheUIEventMgr->SetName("ui_event_mgr", ObjectDir::Main());
    TheUIEventMgr->SetTypeDef(SystemConfig("ui", "ui_event_mgr"));
}

void UIEventMgr::Terminate(){
    RELEASE(TheUIEventMgr);
}

UIEventMgr::~UIEventMgr(){

}

void UIEventMgr::Poll(){
    mTransitionEventQueue.Poll();
    mDialogEventQueue.Poll();
}

void UIEventMgr::DismissDialogEvent(){
    mDialogEventQueue.DismissEvent();
}

void UIEventMgr::DismissTransitionEvent(){
    mTransitionEventQueue.DismissEvent();
}

void UIEventMgr::TriggerEvent(Symbol s, DataArray* arr){
    DataArray* dialogArr = TypeDef()->FindArray(dialog_events, true);
    DataArray* sArr = dialogArr->FindArray(s, false);
    UIEvent* event;
    if(sArr){
        event = new DialogEvent(sArr, arr);
    }
    else {
        DataArray* dtorArr = TypeDef()->FindArray(destructive_transition_events, s);
        event = new DestructiveTransitionEvent(TheNetSync, dtorArr, arr);
    }
    TriggerEvent(event);
}

void UIEventMgr::TriggerEvent(UIEvent* event){
    if(event->IsDialogEvent()) mDialogEventQueue.TriggerEvent(event);
    else {
        MILO_ASSERT(event->IsTransitionEvent(), 0xBD);
        mTransitionEventQueue.TriggerEvent(event);
    }
}

bool UIEventMgr::HasActiveEvent() const {
    return mDialogEventQueue.CurrentEvent() || mTransitionEventQueue.CurrentEvent();
}

DECOMP_FORCEFUNC(UIEventMgr, UIEventMgr, HasActiveDialogEvent())
DECOMP_FORCEFUNC(UIEventMgr, UIEventMgr, HasActiveTransitionEvent())

#pragma push
#pragma force_active on
inline bool UIEventMgr::HasActiveDialogEvent() const {
    return mDialogEventQueue.CurrentEvent();
}

inline bool UIEventMgr::HasActiveTransitionEvent() const {
    return mTransitionEventQueue.CurrentEvent();
}
#pragma pop

bool UIEventMgr::HasActiveDestructiveEvent() const {
    UIEvent* transitionEvent = mTransitionEventQueue.CurrentEvent();
    if(transitionEvent && transitionEvent->IsDestructiveEvent()) return true;
    UIEvent* dialogEvent = mDialogEventQueue.CurrentEvent();
    if(dialogEvent && dialogEvent->IsDestructiveEvent()) return true;
    return false;
}

DECOMP_FORCEFUNC(UIEventMgr, UIEventMgr, HasTransitionEvent(Symbol()))
DECOMP_FORCEFUNC(UIEventMgr, UIEventMgr, HasDialogEvent(Symbol()))

#pragma push
#pragma force_active on
inline bool UIEventMgr::HasTransitionEvent(Symbol s) const {
    return mTransitionEventQueue.HasEvent(s);
}

inline bool UIEventMgr::HasDialogEvent(Symbol s) const {
    return mDialogEventQueue.HasEvent(s);
}
#pragma pop

Symbol UIEventMgr::CurrentDialogEvent() const {
    UIEvent* event = mDialogEventQueue.CurrentEvent();
    if(event) return event->Type();
    else return gNullStr;
}

Symbol UIEventMgr::CurrentTransitionEvent() const {
    UIEvent* event = mTransitionEventQueue.CurrentEvent();
    if(event) return event->Type();
    else return gNullStr;
}

bool UIEventMgr::IsTransitionEventFinished() const {
    MILO_ASSERT(HasActiveTransitionEvent(), 0xFD);
    TransitionEvent* event = dynamic_cast<TransitionEvent*>(mTransitionEventQueue.CurrentEvent());
}

DataNode UIEventMgr::OnTriggerEvent(DataArray* a){
    Symbol s = a->Sym(2);
    DataArray* eventArr = nullptr;
    if(a->Size() > 3){
        eventArr = a->Array(3);
    }
    TriggerEvent(s, eventArr);
    return 1;
}

BEGIN_HANDLERS(UIEventMgr)
    HANDLE(trigger_event, OnTriggerEvent)
    HANDLE_ACTION(dismiss_dialog_event, DismissDialogEvent())
    HANDLE_ACTION(dismiss_transition_event, DismissTransitionEvent())
    HANDLE_EXPR(has_active_transition_event, HasActiveTransitionEvent())
    HANDLE_EXPR(has_active_destructive_event, HasActiveDestructiveEvent())
    HANDLE_EXPR(has_active_dialog_event, HasActiveDialogEvent())
    HANDLE_EXPR(current_dialog_event, CurrentDialogEvent())
    HANDLE_EXPR(current_transition_event, CurrentTransitionEvent())
    HANDLE_EXPR(has_transition_event, HasTransitionEvent(_msg->Sym(2)))
    HANDLE_EXPR(has_dialog_event, HasDialogEvent(_msg->Sym(2)))
    HANDLE_SUPERCLASS(MsgSource)
    HANDLE_CHECK(0x141)
END_HANDLERS