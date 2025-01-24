#include "rndobj/EventTrigger.h"
#include "decomp.h"
#include "math/Rand.h"
#include "math/Utl.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/ObjMacros.h"
#include "obj/ObjPtr_p.h"
#include "obj/Object.h"
#include "obj/Task.h"
#include "obj/Utl.h"
#include "os/Debug.h"
#include "os/File.h"
#include "rndobj/Anim.h"
#include "rndobj/Draw.h"
#include "synth/Sequence.h"
#include "rndobj/PartLauncher.h"
#include "rndobj/AnimFilter.h"
#include "obj/DataFunc.h"
#include "obj/Msg.h"
#include "utl/Loader.h"
#include "utl/Messages.h"
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
                    if((*rit)->RefOwner() && (*rit)->RefOwner() != iter){
                        break;
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
    for(std::list<EventTrigger*>::iterator iter = trigList.begin(); iter != trigList.end(); ++iter){
        EventTrigger* curTrig = *iter;
        for(std::list<EventTrigger*>::iterator iter2 = iter; iter2 != trigList.end(); ){
            EventTrigger* curTrig2 = *iter2;
            if(curTrig != curTrig2 &&
                curTrig2->mTriggerEvents == curTrig->mTriggerEvents &&
                curTrig2->mEnableEvents == curTrig->mEnableEvents &&
                curTrig2->mDisableEvents == curTrig->mDisableEvents &&
                curTrig2->mWaitForEvents == curTrig->mWaitForEvents){
                MILO_WARN("Combining %s with %s", curTrig2->Name(), curTrig->Name());
                while(!curTrig2->mAnims.empty()){
                    curTrig->mAnims.push_back(curTrig2->mAnims.back());
                    curTrig2->mAnims.pop_back();
                }
                while(!curTrig2->mSounds.empty()){
                    curTrig->mSounds.push_back(curTrig2->mSounds.back());
                    curTrig2->mSounds.pop_back();
                }
                while(!curTrig2->mShows.empty()){
                    curTrig->mShows.push_back(curTrig2->mShows.back());
                    curTrig2->mShows.pop_back();
                }
                while(!curTrig2->mHideDelays.empty()){
                    curTrig->mHideDelays.push_back(curTrig2->mHideDelays.back());
                    curTrig2->mHideDelays.pop_back();
                }
                while(!curTrig2->mProxyCalls.empty()){
                    curTrig->mProxyCalls.push_back(curTrig2->mProxyCalls.back());
                    curTrig2->mProxyCalls.pop_back();
                }
                const std::vector<ObjRef*>& refs = curTrig2->Refs();
                while(!refs.empty()){
                    refs.back()->Replace(curTrig2, curTrig);
                }
                delete curTrig2;
                iter2 = trigList.erase(iter2);
            }
            else ++iter2;
        }
    }
    return 0;
}
#pragma pop

void EventTrigger::Init(){
    Register();
    DataRegisterFunc("cleanup_triggers", Cleanup);
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
    mResetTriggers(this, kObjListNoNull), mHideDelays(this), mNextLink(this), mPartLaunchers(this, kObjListNoNull), mAnimFrame(0.0f),
    mHidden(this, kObjListNoNull), mShown(this, kObjListNoNull), mTriggerOrder(0), mAnimTrigger(kTriggerAnimNone), mLastTriggerIndex(-1), unkdf(0), mEnabled(1), mEnabledAtStart(1), mWaiting(0), mTriggered(0) {
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
        mEnabled = mEnabledAtStart;
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
        COPY_MEMBER(mEnabledAtStart)
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

DECOMP_FORCEACTIVE(EventTrigger, "ObjPtr_p.h", "f.Owner()", "")

SAVE_OBJ(EventTrigger, 406)

void EventTrigger::LoadOldAnim(BinStream& bs, RndAnimatable* anim){
    Anim eventAnim(this);
    bs >> (int&)eventAnim.mRate;
    int i48;
    bs >> i48;
    bs >> eventAnim.mStart;
    bs >> eventAnim.mEnd;
    bs >> eventAnim.mPeriod;
    bs >> eventAnim.mBlend;
    bool b88;
    bs >> b88;
    bs >> eventAnim.mDelay;
    if(i48 == 0){
        eventAnim.mType = "range";
    }
    else if(b88){
        eventAnim.mType = "dest";
    }
    else {
        eventAnim.mType = "loop";
    }
    if(anim){
        eventAnim.mAnim = anim;
        mAnims.push_back(eventAnim);
    }
}

void EventTrigger::LoadOldEvent(BinStream& bs, Hmx::Object* obj, const char* trigName, ObjectDir* dir){
    mTriggerEvents.clear();
    Symbol s;
    bs >> s;
    if(!s.Null()){
        mTriggerEvents.push_back(s);
    }
    if(trigName){
        SetName(NextName(MakeString("%s_%s.trig", trigName, s), dir), dir);
    }
    RndAnimatable* anim = dynamic_cast<RndAnimatable*>(obj);
    if(gRev < 5){
        bool b58;
        bs >> b58;
        LoadOldAnim(bs, b58 ? anim : nullptr);
    }
    else {
        unsigned int count;
        bs >> count;
        EventTrigger* curTrig = this;
        while(count-- != 0){
            LoadOldAnim(bs, anim);
            if(count != 0){
                EventTrigger* newTrig = new EventTrigger();
                mNextLink = newTrig;
                curTrig = mNextLink;
                curTrig->SetName(MakeString("%s_%d.trig", FileGetBase(Name(), 0), count), dir);
            }
        }
    }
    int whichVec;
    bs >> whichVec;
    if(whichVec == 1){
        RndDrawable* draw = dynamic_cast<RndDrawable*>(obj);
        if(draw) mShows.push_back(draw);
    }
    else if(whichVec == 2){
        RndDrawable* draw = dynamic_cast<RndDrawable*>(obj);
        if(draw){
            mHideDelays.push_back();
            mHideDelays.back().mHide = draw;
        }
    }
    else if(whichVec == 3){
        MILO_WARN("%s: can't enable %s", Name(), obj ? obj->Name() : "''");
    }
    else if(whichVec == 4){
        MILO_WARN("%s: can't disable %s", Name(), obj ? obj->Name() : "''");
    }
    if(gRev > 1){
        float f50;
        bs >> f50;
        if(f50 != 0){
            for(ObjVector<Anim>::iterator it = mAnims.begin(); it != mAnims.end(); ++it){
                if(it->mAnim->Units() == 0){
                    it->mDelay += f50;
                }
                else {
                    MILO_WARN("%s: anim delay not in seconds");
                }
            }
        }
    }
    if(gRev > 3){
        String str;
        bs >> str;
        if(!str.empty()){
            MILO_WARN("%s: %s", Name(), str);
        }
    }
}

void EventTrigger::CleanupEventCase(std::vector<Symbol>& syms){
    for(std::vector<Symbol>::iterator it = syms.begin(); it != syms.end(); ++it){
        const char* lightStr = strstr(it->mStr, "lighting_");
        if(lightStr){
            String str(*it);
            str.ToLower();
            *it = str.c_str();
        }
    }
}

BEGIN_LOADS(EventTrigger)
    LOAD_REVS(bs)
    ASSERT_REVS(0x11, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    if(gRev > 0xF) LOAD_SUPERCLASS(RndAnimatable)
    UnregisterEvents();
    std::list<EventTrigger*> triggers;
    if(gRev > 9) bs >> mTriggerEvents;
    else if(gRev > 6){
        mTriggerEvents.clear();
        Symbol sym;
        bs >> sym;
        if(!sym.Null()) mTriggerEvents.push_back(sym);
    }
    if(gRev > 6) bs >> mAnims >> mSounds >> mShows;

    if(gRev > 0xC) bs >> mHideDelays;
    else if(gRev > 8) {
        mHideDelays.clear();
        int count;
        bs >> count;
        mHideDelays.resize(count);
        for(ObjVector<HideDelay>::iterator it = mHideDelays.begin(); it != mHideDelays.end(); ++it){
            bs >> it->mHide;
            bs >> it->mDelay;
        }
    }
    else if(gRev > 6){
        ObjPtrList<RndDrawable> drawList(this, kObjListNoNull);
        bs >> drawList;
        mHideDelays.clear();
        for(ObjPtrList<RndDrawable>::iterator it = drawList.begin(); it != drawList.end(); ++it){
            mHideDelays.push_back();
            mHideDelays.back().mHide = *it;
        }
    }
    else {
        ObjPtr<Hmx::Object> objPtr(this);
        bs >> objPtr;
        unsigned int count;
        bs >> count;
        String str(FileGetBase(Name(), 0));
        TheLoadMgr.SetEditMode(true);
        EventTrigger* curTrig = this;
        while(count-- != 0){
            curTrig->LoadOldEvent(bs, objPtr, count != 0 || curTrig != this ? str.c_str() : 0, Dir());
            if(count != 0){
                curTrig = new EventTrigger();
                triggers.push_back(curTrig);
            }
        }
        TheLoadMgr.SetEditMode(false);
    }
    if(gRev > 2){
        bs >> mEnableEvents;
        bs >> mDisableEvents;
    }
    if(gRev > 5) bs >> mWaitForEvents;
    if(gRev > 6) bs >> mNextLink;
    if(gRev < 10){
        RemoveNullEvents(mEnableEvents);
        RemoveNullEvents(mDisableEvents);
        RemoveNullEvents(mWaitForEvents);
    }
    if(gRev < 7){
        for(std::list<EventTrigger*>::const_iterator it = triggers.begin(); it != triggers.end(); ++it){
            (*it)->mEnableEvents = mEnableEvents;
            (*it)->mDisableEvents = mDisableEvents;
            (*it)->mWaitForEvents = mWaitForEvents;
        }
    }
    if(gRev > 7) bs >> mProxyCalls;
    if(gRev > 0xB){
        int i = 0;
        bs >> i;
        mTriggerOrder = i;
    }
    if(gRev > 0xD) bs >> mResetTriggers;
    if(gRev > 0xE) LOAD_BITFIELD(bool, mEnabledAtStart)
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

void EventTrigger::Trigger(){
    mWaiting = 0;
    if(!mNextLink) TriggerSelf();
    else {
        EventTrigger* it = this;
        int num = 1;
        while((it = it->mNextLink) != nullptr){
            num++;
        }
        MILO_ASSERT(num < 256, 0x2D6);
        switch(mTriggerOrder){
            case 0:
                num = RandomInt(0, num);
                break;
            case 1:
                num = (mLastTriggerIndex + 1) % num;
                break;
            default:
                MILO_WARN("Unknown trigger order for %s", Name());
                break;
        }
        mLastTriggerIndex = num;
        it = this;
        while(num-- != 0){
            it = it->mNextLink;
        }
        it->TriggerSelf();
    }
}

#pragma push
#pragma pool_data off
void EventTrigger::TriggerSelf(){
    for(ObjPtrList<EventTrigger>::iterator it = mResetTriggers.begin(); it != mResetTriggers.end(); ++it){
        (*it)->BasicReset();
    }
    for(ObjVector<ProxyCall>::iterator it = mProxyCalls.begin(); it != mProxyCalls.end(); ++it){
        if(it->mProxy){
            if(!it->mCall.Null()){
                static Message msg(0);
                msg.SetType(it->mCall);
                it->mProxy->Handle(msg, true);
            }
            if(it->mEvent){
                it->mEvent->Trigger();
            }
        }
    }
    for(ObjVector<Anim>::iterator it = mAnims.begin(); it != mAnims.end(); ++it){
        if(it->mAnim){
            if(it->mEnable){
                mSpawnedTasks.push_back(
                    it->mAnim->Animate(it->mBlend, it->mWait, it->mDelay, (RndAnimatable::Rate)it->mRate,
                    it->mStart, it->mEnd, it->mPeriod, it->mScale, it->mType)
                );
            }
            else {
                mSpawnedTasks.push_back(
                    it->mAnim->Animate(it->mBlend, it->mWait, it->mDelay)
                );
            }
        }
    }
    for(ObjPtrList<Sequence>::iterator it = mSounds.begin(); it != mSounds.end(); ++it){
        (*it)->Play(0, 0, 0);
    }
    for(ObjPtrList<RndDrawable>::iterator it = mShows.begin(); it != mShows.end(); ++it){
        if(!(*it)->Showing()){
            if(!mTriggered){
                mShown.push_back(*it);
            }
            (*it)->SetShowing(true);
        }
    }
    for(ObjVector<HideDelay>::iterator it = mHideDelays.begin(); it != mHideDelays.end(); ++it){
        if(it->mHide){
            if(it->mHide->Showing()){
                if(!mTriggered){
                    mHidden.push_back(it->mHide);
                }
                if(it->mDelay){
                    static Message msg("set_showing", 0);
                    MessageTask* msgtask = new MessageTask(it->mHide, msg);
                    TheTaskMgr.Start(msgtask, RndAnimatable::RateToTaskUnits((RndAnimatable::Rate)it->mRate), it->mDelay);
                    mSpawnedTasks.push_back(msgtask);
                }
                else {
                    it->mHide->SetShowing(false);
                }
            }
        }
    }

    for(ObjPtrList<RndPartLauncher>::iterator it = mPartLaunchers.begin(); it != mPartLaunchers.end(); ++it){
        (*it)->LaunchParticles();
    }
    if(TypeDef()){
        HandleType(trigger_msg);
    }
    mTriggered = true;
}
#pragma pop

void EventTrigger::BasicReset(){
    mSpawnedTasks.DeleteAll();
    for(ObjPtrList<RndDrawable>::iterator it = mShown.begin(); it != mShown.end(); ++it){
        (*it)->SetShowing(false);
    }
    for(ObjPtrList<RndDrawable>::iterator it = mHidden.begin(); it != mHidden.end(); ++it){
        (*it)->SetShowing(true);
    }
    CleanupHideShow();
    for(ObjVector<ProxyCall>::iterator it = mProxyCalls.begin(); it != mProxyCalls.end(); ++it){
        if(it->mProxy && it->mEvent){
            it->mEvent->BasicReset();
        }
    }
    for(ObjPtrList<Sequence>::iterator it = mSounds.begin(); it != mSounds.end(); ++it){
        (*it)->Stop(false);
    }
    if(TypeDef()){
        Hmx::Object::Handle(reset_msg, false);
    }
    if(mNextLink) mNextLink->BasicReset();
}

void EventTrigger::StartAnim(){
    mFrame = kHugeFloat;
    if(mAnimTrigger == kTriggerAnimStart){
        Trigger();
    }
}

void EventTrigger::EndAnim(){
    mFrame = kHugeFloat;
    if(mAnimTrigger == kTriggerAnimEnd){
        Trigger();
    }
    else if(mAnimTrigger == kTriggerAnimStart){
        BasicReset();
    }
}

void EventTrigger::SetFrame(float frame, float blend){
    float oldframe = mFrame;
    RndAnimatable::SetFrame(frame, blend);
    if(mAnimTrigger == kTriggerAnimFrame && oldframe < mAnimFrame && mFrame >= mAnimFrame){
        Trigger();
    }
}

BEGIN_HANDLERS(EventTrigger)
    HANDLE(trigger, OnTrigger)
    HANDLE_ACTION(enable, unkdf = true)
    HANDLE_ACTION(disable, unkdf = false)
    HANDLE_ACTION(wait_for, (unkdf = true, Trigger()))
    HANDLE(proxy_calls, OnProxyCalls)
    HANDLE_EXPR(supported_events, DataNode(SupportedEvents(), kDataArray))
    HANDLE_ACTION(basic_cleanup, BasicReset())
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x3AF)
END_HANDLERS

DataNode EventTrigger::OnTrigger(DataArray*){
    if(mEnabled){
        if(!mWaitForEvents.empty()){
            mWaiting = true;
        }
        else Trigger();
    }
    return 0;
}

DataNode EventTrigger::OnProxyCalls(DataArray*){
    DataNode& var = DataVariable("milo_prop_path");
    DataArray* miloArr = var.Array();
    DataNode node2 = miloArr->Node(2);
    miloArr->Node(2) = Symbol("proxy");
    Hmx::Object* propDir = Property(miloArr, true)->Obj<ObjectDir>();
    miloArr->Node(2) = node2;
    
    DataArrayPtr ptr(new DataArray(0x200));
    int idx = 0;
    ptr.Node(idx++) = Symbol();
    if(propDir){
        const DataArray* tdef = propDir->TypeDef();
        if(tdef){
            for(int i = 1; i < tdef->Size(); i++){
                DataArray* curArr = tdef->Array(i);
                if(curArr->Size() > 1 && curArr->Type(1) == kDataCommand){
                    ptr.Node(idx++) = curArr->Sym(0);
                }
            }
        }
    }
    ptr->Resize(idx);
    return ptr;
}

void EventTrigger::SetNextLink(EventTrigger* trig){
    for(EventTrigger* it = trig; it != nullptr; it = it->mNextLink){
        if(it == this){
            MILO_WARN("Setting next link causes infinite loop, setting next_link to NULL");
            mNextLink = nullptr;
            return;
        }
    }
    mNextLink = trig;
}

void EventTrigger::Replace(Hmx::Object* from, Hmx::Object* to){
    Hmx::Object::Replace(from, to);
    for(ObjVector<Anim>::iterator it = mAnims.begin(); it != mAnims.end(); ){
        it->mAnim;
        if(from == it->mAnim){
            if(!to){
                it = mAnims.erase(it);
            }
            else {
                it->mAnim = dynamic_cast<RndAnimatable*>(to);
                ++it;
            }
        }
        else ++it;
    }
    for(ObjVector<HideDelay>::iterator it = mHideDelays.begin(); it != mHideDelays.end(); ){
        if(from == it->mHide){
            if(!to){
                it = mHideDelays.erase(it);
            }
            else {
                it->mHide = dynamic_cast<RndDrawable*>(to);
                ++it;
            }
        }
        else ++it;
    }
    for(ObjVector<ProxyCall>::iterator it = mProxyCalls.begin(); it != mProxyCalls.end(); ){
        if(from == it->mEvent || from == it->mProxy){
            if(!to){
                it = mProxyCalls.erase(it);
            }
            else {
                if(from == it->mEvent){
                    it->mEvent = dynamic_cast<EventTrigger*>(to);
                }
                else {
                    it->mProxy = dynamic_cast<ObjectDir*>(to);
                }
                ++it;
            }
        }
        else ++it;
    }
}

void EventTrigger::CleanupHideShow(){
    mTriggered = false;
    mShown.clear();
    mHidden.clear();
}

void EventTrigger::ConvertParticleTriggerType(){
    if(!unkdf && Type() == "particle_trigger"){
        MILO_WARN("Converting particle trigger %s to standard EventTrigger; should re-save %s", Name(), Dir()->GetPathName());
        DataArray* systemsArr = Property("systems", true)->Array();
        for(int i = 0; i < systemsArr->Size(); i++){
            RndPartLauncher* launcher = systemsArr->Obj<RndPartLauncher>(i);
            if(launcher) mPartLaunchers.push_back(launcher);
        }
        SetTypeDef(nullptr);
    }
    unkdf = true;
}

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
    SYNC_PROP_SET(enabled_at_start, mEnabledAtStart, mEnabled = mEnabledAtStart = _val.Int())
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
