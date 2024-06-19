#include "ui/UITrigger.h"
#include "ui/UIComponent.h"
#include "obj/Task.h"
#include "ui/UIMessages.h"
#include "utl/Symbols.h"
// #include "utl/ClassSymbols.h"

INIT_REVS(UITrigger)

UITrigger::UITrigger() : mCallbackObject(this, 0), mEndTime(0.0f), unkfc(1), mBlockTransition(0) {

}

BEGIN_COPYS(UITrigger)
    COPY_SUPERCLASS(EventTrigger)
    CREATE_COPY(UITrigger)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mBlockTransition)
    END_COPYING_MEMBERS
END_COPYS

SAVE_OBJ(UITrigger, 0x2A)

BEGIN_LOADS(UITrigger)
    LOAD_REVS(bs)
    ASSERT_REVS(1, 0)
    if(gRev >= 1){
        UIComponent* uiCom = Hmx::Object::New<UIComponent>();
        uiCom->Load(bs);
        delete uiCom;
        Symbol sym;
        bs >> sym;
        UnregisterEvents();
        mTriggerEvents.clear();
        mTriggerEvents.push_back(sym);
        RegisterEvents();
        ObjPtr<RndAnimatable, ObjectDir> animPtr(this, 0);
        bs >> animPtr;
        mAnims.push_back(EventTrigger::Anim(this));
    }
    else LOAD_SUPERCLASS(EventTrigger);
    bs >> mBlockTransition;
END_LOADS

void UITrigger::Enter(){
    mStartTime = TheTaskMgr.UISeconds();
    mEndTime = 0.0f;
}

bool UITrigger::IsBlocking() const {
    if(TheTaskMgr.UISeconds() < mStartTime){
        const_cast<UITrigger*>(this)->mEndTime = 0.0f;
    }
    bool ret = false;
    bool b = false;
    if(mBlockTransition && mEndTime != 0.0f) b = true;
    if(b){
        if(TheTaskMgr.UISeconds() < mEndTime) ret = true;
    }
    return ret;
}

void UITrigger::StopAnimations(){
    for(ObjVector<EventTrigger::Anim>::iterator it = mAnims.begin(); it != mAnims.end(); it++){
        RndAnimatable* anim = (*it).mAnim;
        if(anim && anim->IsAnimating()) anim->StopAnimation();
    }
}

DataArray* UITrigger::SupportedEvents(){
    static DataArray* events = SystemConfig("objects", "UITrigger", "supported_events")->Array(1);
    return events;
}

void UITrigger::Poll(){
    if(!unkfc){
        if(mEndTime <= TheTaskMgr.UISeconds()){
            unkfc = true;
            if(mCallbackObject){
                mCallbackObject->Handle(UITriggerCompleteMsg(this), true);
            }
        }
    }
}

BEGIN_HANDLERS(UITrigger)
    HANDLE_EXPR(end_time, mEndTime)
    HANDLE_ACTION(play_start_of_anims, PlayStartOfAnims())
    HANDLE_ACTION(play_end_of_anims, PlayEndOfAnims())
    HANDLE_ACTION(stop_anims, StopAnimations())
    HANDLE_EXPR(is_done, mEndTime <= TheTaskMgr.UISeconds())
    HANDLE_EXPR(is_blocking, IsBlocking())
    HANDLE_SUPERCLASS(EventTrigger)
    HANDLE_CHECK(0x10C)
END_HANDLERS

BEGIN_PROPSYNCS(UITrigger)
    SYNC_PROP(block_transition, mBlockTransition)
    SYNC_PROP(callback_object, mCallbackObject)
    SYNC_SUPERCLASS(EventTrigger)
END_PROPSYNCS