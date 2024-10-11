#include "rndobj/EventTrigger.h"
#include "rndobj/Draw.h"
#include "synth/Sequence.h"
#include "rndobj/PartLauncher.h"
#include "rndobj/AnimFilter.h"
#include "obj/DataFunc.h"
#include "obj/MsgSource.h"
#include "utl/Symbols.h"

INIT_REVS(EventTrigger)

DataArray* EventTrigger::SupportedEvents(){
    if(Type() == "endgame_action"){
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
                for(; rit != rEnd; ++rit){
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
                    iter2->mScale = filter->Property("scale", true)->Float();
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

void EventTrigger::Init(){
    Register();
    // DataRegisterFunc("cleanup_triggers", Cleanup);
}

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
    unkbc(this, kObjListNoNull), unkcc(this, kObjListNoNull), mTriggerOrder(0), mAnimTrigger(0), unkde(-1), unkdf(0), mEnabled(1), mEnabledAtStart(1) {
    RegisterEvents();
}

EventTrigger::HideDelay::HideDelay(Hmx::Object* o) : mHide(o, 0), mDelay(0.0f), mRate(0) {

}

void EventTrigger::RegisterEvents(){
    MsgSource* src = dynamic_cast<MsgSource*>(Dir());
    if(src){
        for(std::vector<Symbol>::iterator it = mTriggerEvents.begin(); it != mTriggerEvents.end(); ++it){
            src->AddSink(this, *it, trigger, MsgSource::kHandle);
        }
        for(std::vector<Symbol>::iterator it = mEnableEvents.begin(); it != mEnableEvents.end(); ++it){
            src->AddSink(this, *it, enable, MsgSource::kHandle);
        }
        for(std::vector<Symbol>::iterator it = mDisableEvents.begin(); it != mDisableEvents.end(); ++it){
            src->AddSink(this, *it, disable, MsgSource::kHandle);
        }
        for(std::vector<Symbol>::iterator it = mWaitForEvents.begin(); it != mWaitForEvents.end(); ++it){
            src->AddSink(this, *it, wait_for, MsgSource::kHandle);
        }
        mEnabledAtStart = false;
    }
}

void EventTrigger::UnregisterEvents(){
    MsgSource* src = dynamic_cast<MsgSource*>(Dir());
    if(src){
        for(std::vector<Symbol>::iterator it = mTriggerEvents.begin(); it != mTriggerEvents.end(); ++it){
            src->RemoveSink(this, *it);
        }
        for(std::vector<Symbol>::iterator it = mEnableEvents.begin(); it != mEnableEvents.end(); ++it){
            src->RemoveSink(this, *it);
        }
        for(std::vector<Symbol>::iterator it = mDisableEvents.begin(); it != mDisableEvents.end(); ++it){
            src->RemoveSink(this, *it);
        }
        for(std::vector<Symbol>::iterator it = mWaitForEvents.begin(); it != mWaitForEvents.end(); ++it){
            src->RemoveSink(this, *it);
        }
    }
}

#pragma push
#pragma dont_inline on
BEGIN_COPYS(EventTrigger)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndAnimatable)
    CREATE_COPY(EventTrigger)
    BEGIN_COPYING_MEMBERS
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
    END_COPYING_MEMBERS
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
    if(gRev > 0xE) LOAD_BITFIELD(bool, unkdf)
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

BEGIN_CUSTOM_PROPSYNC(EventTrigger::Anim)
    SYNC_PROP_MODIFY_ALT(anim, o.mAnim, ResetAnim(o))
    SYNC_PROP(blend, o.mBlend)
    SYNC_PROP(wait, o.mWait)
    SYNC_PROP(delay, o.mDelay)
    SYNC_PROP(enable, o.mEnable)
    SYNC_PROP(rate, (int&)o.mRate)
    SYNC_PROP(start, o.mStart)
    SYNC_PROP(end, o.mEnd)
    SYNC_PROP(scale, o.mScale)
    SYNC_PROP(period, o.mPeriod)
    SYNC_PROP(type, o.mType)
END_CUSTOM_PROPSYNC

BEGIN_CUSTOM_PROPSYNC(EventTrigger::ProxyCall)
    SYNC_PROP_MODIFY_ALT(proxy, o.mProxy, o.mCall = Symbol(""))
    SYNC_PROP(call, o.mCall)
    SYNC_PROP(event, o.mEvent)
END_CUSTOM_PROPSYNC

BEGIN_CUSTOM_PROPSYNC(EventTrigger::HideDelay)
    SYNC_PROP(hide, o.mHide)
    SYNC_PROP(delay, o.mDelay)
    SYNC_PROP(rate, o.mRate)
END_CUSTOM_PROPSYNC

#pragma push
#pragma pool_data off
BEGIN_PROPSYNCS(EventTrigger)
    {
        static Symbol _s("trigger_events");
        if(sym == _s){
            if(!(_op & (kPropSize|kPropGet))) UnregisterEvents();
            bool synced = PropSync(mTriggerEvents, _val, _prop, _i + 1, _op);
            if(synced){
                if(!(_op & (kPropSize|kPropGet))) RegisterEvents();
                return true;
            }
            else return false;
        }
    }
    SYNC_PROP_MODIFY_ALT(anims, mAnims, CheckAnims())
    SYNC_PROP(proxy_calls, mProxyCalls)
    SYNC_PROP(sounds, mSounds)
    SYNC_PROP(shows, mShows)
    SYNC_PROP(hide_delays, mHideDelays)
    SYNC_PROP(part_launchers, mPartLaunchers)
    {
        static Symbol _s("enable_events");
        if(sym == _s){
            if(!(_op & (kPropSize|kPropGet))) UnregisterEvents();
            bool synced = PropSync(mEnableEvents, _val, _prop, _i + 1, _op);
            if(synced){
                if(!(_op & (kPropSize|kPropGet))) RegisterEvents();
                return true;
            }
            else return false;
        }
    }
    {
        static Symbol _s("disable_events");
        if(sym == _s){
            if(!(_op & (kPropSize|kPropGet))) UnregisterEvents();
            bool synced = PropSync(mDisableEvents, _val, _prop, _i + 1, _op);
            if(synced){
                if(!(_op & (kPropSize|kPropGet))) RegisterEvents();
                return true;
            }
            else return false;
        }
    }
    SYNC_PROP_SET(enabled, mEnabled, mEnabled = _val.Int())
    SYNC_PROP_SET(enabled_at_start, mEnabledAtStart, mEnabledAtStart = _val.Int())
    {
        static Symbol _s("wait_for_events");
        if(sym == _s){
            if(!(_op & (kPropSize|kPropGet))) UnregisterEvents();
            bool synced = PropSync(mWaitForEvents, _val, _prop, _i + 1, _op);
            if(synced){
                if(!(_op & (kPropSize|kPropGet))) RegisterEvents();
                return true;
            }
            else return false;
        }
    }
    SYNC_PROP_SET(next_link, mNextLink, SetNextLink(_val.Obj<EventTrigger>()))
    SYNC_PROP(trigger_order, mTriggerOrder)
    SYNC_PROP(triggers_to_reset, mResetTriggers)
    SYNC_PROP(anim_trigger, mAnimTrigger)
    SYNC_PROP(anim_frame, mAnimFrame)
    SYNC_SUPERCLASS(RndAnimatable)
END_PROPSYNCS
#pragma pop
