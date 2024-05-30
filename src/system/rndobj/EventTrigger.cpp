#include "EventTrigger.h"
#include "rndobj/Draw.h"
#include "synth/Sequence.h"
#include "rndobj/PartLauncher.h"
#include "rndobj/AnimFilter.h"
#include "obj/DirItr.h"
#include "utl/Symbols.h"

INIT_REVS(EventTrigger)

DataArray* EventTrigger::SupportedEvents(){
    Symbol sym;
    if(mTypeDef){
        sym = mTypeDef->Sym(0);
    }
    if(sym == "endgame_action"){
        return SystemConfig("objects", "EventTrigger", "types", "endgame_action", "supported_events")->Array(1);
    }
    else {
        return SystemConfig("objects", "EventTrigger", "supported_events")->Array(1);
    }
}

#pragma push
#pragma dont_inline on
DataNode EventTrigger::Cleanup(DataArray* arr){
    class ObjectDir* dir = arr->Obj<class ObjectDir>(1);
    std::list<EventTrigger*> trigList;
    for(ObjDirItr<EventTrigger> iter(dir, true); iter != 0; ++iter){
        trigList.push_back(iter);
        for(std::vector<Symbol>::iterator iter2 = iter->mTriggerEvents.begin(); iter2 != iter->mTriggerEvents.end(); iter2++){
            char buf[0x80];
            strcpy(buf, iter2->Str());
            FileNormalizePath(buf);
            *iter2 = buf;
        }
        for(ObjVector<Anim>::iterator iter2 = iter->mAnims.begin(); iter2 != iter->mAnims.end(); iter2++){
            RndAnimFilter* filter = dynamic_cast<RndAnimFilter*>(iter2->mAnim.Ptr());
            if(filter){
                std::vector<ObjRef*>::const_reverse_iterator rit = filter->Refs().rbegin();
                std::vector<ObjRef*>::const_reverse_iterator rEnd = filter->Refs().rend();
                for(; rit != rEnd; rit++){
                    if((*rit)->RefOwner()){
                        if((*rit)->RefOwner() != iter) break;
                    }
                }
                if(!(rit != rEnd) && filter->GetType() != RndAnimFilter::kShuttle){
                    iter2->mAnim = filter->Anim();
                    iter2->mEnable = 1;
                    iter2->mRate = filter->GetRate();
                    iter2->mStart = filter->Start();
                    iter2->mEnd = filter->End();
                    iter2->mPeriod = filter->Period();
                    iter2->mScale = filter->Property("scale", true)->Float(0);
                    if(filter->GetType() == RndAnimFilter::kLoop) iter2->mType = loop;
                    else iter2->mType = range;
                    delete filter;
                }
            }
        }
    }
    // after all the ObjDirs have been Itr'd through
    for(std::list<EventTrigger*>::iterator iter = trigList.begin(); iter != trigList.end(); iter++){
        std::list<EventTrigger*>::iterator iter2 = iter;
        EventTrigger* t1 = *iter;
        EventTrigger* t2 = *iter2;
        if(t1 == t2){
            if(t1->mTriggerEvents == t2->mTriggerEvents &&
                t1->mEnableEvents == t2->mEnableEvents &&
                t1->mDisableEvents == t2->mDisableEvents &&
                t1->mWaitForEvents == t2->mWaitForEvents){
                MILO_WARN("Combining %s with %s", t1->Name(), t2->Name());
                while(!t1->mAnims.empty()){
                    t2->mAnims.push_back(t1->mAnims.back());
                    t1->mAnims.pop_back();
                }
                while(!t1->mSounds.empty()){
                    t2->mSounds.push_back(t1->mSounds.back());
                    t1->mSounds.pop_back();
                }
                while(!t1->mShows.empty()){
                    t2->mShows.push_back(t1->mShows.back());
                    t2->mShows.pop_back();
                }
            }
        }
    }
    return DataNode(0);
}
#pragma pop

void EventTrigger::SetName(const char* cc, class ObjectDir* dir){
    UnregisterEvents();
    Hmx::Object::SetName(cc, dir);
    RegisterEvents();
}

void ResetAnim(EventTrigger::Anim& anim){
    if(anim.mAnim){
        anim.mRate = anim.mAnim->GetRate();
        anim.mStart = anim.mAnim->StartFrame();
        anim.mEnd = anim.mAnim->EndFrame();
        anim.mPeriod = 0.0f;
        anim.mScale = 1.0f;
        anim.mType = anim.mAnim->Loop() ? loop : range;
    }
}

BinStream& operator>>(BinStream& bs, EventTrigger::Anim& anim){
    bs >> anim.mAnim >> anim.mBlend >> anim.mWait >> anim.mDelay;
    if(EventTrigger::gRev > 9){
        bs >> anim.mEnable;
        int i;
        bs >> i;
        anim.mRate = i;
        bs >> anim.mStart >> anim.mEnd >> anim.mPeriod >> anim.mType;
        bs >> anim.mScale;
    }
    else ResetAnim(anim);
    return bs;
}

EventTrigger::Anim::Anim(Hmx::Object* o) : mAnim(o, 0), mBlend(0.0f), mDelay(0.0f), mWait(0), mEnable(0), mRate(0), mStart(0.0f), mEnd(0.0f), mPeriod(0.0f), mScale(1.0f) {
    mType = range;
}

BinStream& operator>>(BinStream& bs, EventTrigger::ProxyCall& pcall){
    bs >> pcall.mProxy;
    bs >> pcall.mCall;
    if(EventTrigger::gRev > 10) pcall.mEvent.Load(bs, true, pcall.mProxy);
    return bs;
}

EventTrigger::ProxyCall::ProxyCall(Hmx::Object* o) : mProxy(o, 0), mEvent(o, 0) {

}

EventTrigger::EventTrigger() : mAnims(this), mSpawnedTasks(this, kObjListNoNull), mProxyCalls(this), mSounds(this, kObjListNoNull), mShows(this, kObjListNoNull),
    mResetTriggers(this, kObjListNoNull), mHideDelays(this), mNextLink(this, 0), mPartLaunchers(this, kObjListNoNull), mAnimFrame(0.0f),
    unkbc(this, kObjListNoNull), unkcc(this, kObjListNoNull), mTriggerOrder(0), mAnimTrigger(0), unkde(-1) {
    RegisterEvents();
}

EventTrigger::HideDelay::HideDelay(Hmx::Object* o) : mHide(o, 0), mDelay(0.0f), unk10(0) {

}

#pragma push
#pragma dont_inline on
BEGIN_COPYS(EventTrigger)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndAnimatable)
    GET_COPY(EventTrigger)
    BEGIN_COPY_CHECKED
        UnregisterEvents();
        COPY_MEMBER(mTriggerEvents)
        COPY_MEMBER(mAnims)
        COPY_MEMBER(mSounds)
        COPY_MEMBER(mProxyCalls)
        COPY_MEMBER(mShows)
        COPY_MEMBER(mHideDelays)
        COPY_MEMBER(mEnableEvents)
        COPY_MEMBER(mDisableEvents)
        COPY_MEMBER(mWaitForEvents)
        COPY_MEMBER(mNextLink)
        COPY_MEMBER(mTriggerOrder)
        COPY_MEMBER(mResetTriggers)
        COPY_MEMBER(unkdf)
        COPY_MEMBER(mAnimTrigger)
        COPY_MEMBER(mAnimFrame)
        COPY_MEMBER(mPartLaunchers)
        RegisterEvents();
        CleanupHideShow();
    END_COPY_CHECKED
END_COPYS
#pragma pop


void RemoveNullEvents(std::vector<Symbol>& vec){
    std::vector<Symbol>::iterator it = vec.begin();
    while(it != vec.end()){
        if(it->Null()) it = vec.erase(it);
        else it++;
    }
}

SAVE_OBJ(EventTrigger, 406)

BEGIN_LOADS(EventTrigger)
    LOAD_REVS(bs)
    ASSERT_REVS(0x11, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    if(gRev > 0xF) LOAD_SUPERCLASS(RndAnimatable)
    UnregisterEvents();
    if(gRev > 9) bs >> mTriggerEvents;
    else if(gRev > 6){
        mTriggerEvents.clear();
        Symbol sym;
        bs >> sym;
        if(!sym.Null()) mTriggerEvents.push_back(sym);
    }
    if(gRev > 6) bs >> mAnims >> mSounds >> mShows;
    if(gRev > 0xC) bs >> mHideDelays;
    else {
        // gross
    }
    if(gRev > 2) bs >> mEnableEvents >> mDisableEvents;
    if(gRev > 5) bs >> mWaitForEvents;
    if(gRev > 6) bs >> mNextLink;
    if(gRev < 10){
        RemoveNullEvents(mEnableEvents);
        RemoveNullEvents(mDisableEvents);
        RemoveNullEvents(mWaitForEvents);
    }
    if(gRev < 7){
        // iterator jank
    }
    if(gRev > 7) bs >> mProxyCalls;
    if(gRev > 0xB){
        int i = 0;
        bs >> i;
        mTriggerOrder = i;
    }
    if(gRev > 0xD) bs >> mResetTriggers;
    if(gRev > 0xE) bs >> unkdf;
    if(gRev > 0xF){
        int i;
        bs >> i;
        mAnimTrigger = i;
        bs >> mAnimFrame;
    }
    if(gRev > 0x10) bs >> mPartLaunchers;
    CleanupEventCase(mTriggerEvents);
    CleanupEventCase(mEnableEvents);
    CleanupEventCase(mDisableEvents);
    CleanupEventCase(mWaitForEvents);
    RegisterEvents();
    CleanupHideShow();
    ConvertParticleTriggerType();
END_LOADS

BEGIN_HANDLERS(EventTrigger)
    HANDLE(trigger, OnTrigger)
    HANDLE_ACTION(enable, unkdf = true)
    HANDLE_ACTION(disable, unkdf = false)
    HANDLE_ACTION(wait_for, unkdf = true; Trigger();)
    HANDLE(proxy_calls, OnProxyCalls)
    if (sym == supported_events) return DataNode(SupportedEvents(), kDataArray);
    HANDLE_ACTION(basic_cleanup, BasicReset())
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x3AF)
END_HANDLERS