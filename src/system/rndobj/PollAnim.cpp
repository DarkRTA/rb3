#include "rndobj/PollAnim.h"
#include "utl/Symbols.h"

INIT_REVS(RndPollAnim)

RndPollAnim::RndPollAnim() : mAnims(this, kObjListNoNull) {
    
}

float RndPollAnim::EndFrame(){
    float frame = 0.0f;
    for(ObjPtrList<RndAnimatable, class ObjectDir>::iterator it = mAnims.begin(); it != mAnims.end(); ++it){
        float thisendframe = (*it)->EndFrame();
        if(frame < thisendframe) frame = thisendframe;
    }
    return frame;
}

void RndPollAnim::ListAnimChildren(std::list<RndAnimatable*>& children) const {
    ObjPtrList<RndAnimatable, class ObjectDir>::iterator it = mAnims.begin();
    ObjPtrList<RndAnimatable, class ObjectDir>::iterator itEnd = mAnims.end();
    for(; it != itEnd; ++it){
        children.push_back(*it);
    }
}

void RndPollAnim::Enter(){
    for(ObjPtrList<RndAnimatable, class ObjectDir>::iterator it = mAnims.begin(); it != mAnims.end(); ++it){
        (*it)->StartAnim();
    }
}

void RndPollAnim::Poll(){
    for(ObjPtrList<RndAnimatable, class ObjectDir>::iterator it = mAnims.begin(); it != mAnims.end(); ++it){
        RndAnimatable* thisAnim = *it;
        float f = 0.0f;
        switch(thisAnim->GetRate()){
            case k30_fps:
                f = 30.0f * TheTaskMgr.Seconds(TaskMgr::b);
                break;
            case k480_fpb:
                f = 480.0f * TheTaskMgr.Beat();
                break;
            case k30_fps_ui:
                f = 30.0f * TheTaskMgr.UISeconds();
                break;
            case k1_fpb:
                f = TheTaskMgr.Beat();
                break;
            case k30_fps_tutorial:
                f = 480.0f * TheTaskMgr.TutorialSeconds();
                break;
            default: break;
        }
        thisAnim->SetFrame(f, 1.0f);
    }
}

void RndPollAnim::Exit(){
    for(ObjPtrList<RndAnimatable, class ObjectDir>::iterator it = mAnims.begin(); it != mAnims.end(); ++it){
        (*it)->EndAnim();
    }
}

SAVE_OBJ(RndPollAnim, 0x66)

BEGIN_LOADS(RndPollAnim)
    LOAD_REVS(bs);
    ASSERT_REVS(0, 0);
    LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(RndAnimatable)
    LOAD_SUPERCLASS(RndPollable)
    bs >> mAnims;
END_LOADS

BEGIN_COPYS(RndPollAnim)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndAnimatable)
    COPY_SUPERCLASS(RndPollable)
    CREATE_COPY(RndPollAnim)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mAnims)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(RndPollAnim)
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_SUPERCLASS(RndPollable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x8B)
END_HANDLERS

BEGIN_PROPSYNCS(RndPollAnim)
    SYNC_PROP(anims, mAnims)
    bool super = RndAnimatable::SyncProperty(_val, _prop, _i, _op);
    if(super) return true;
    else return RndPollable::SyncProperty(_val, _prop, _i, _op);
END_PROPSYNCS