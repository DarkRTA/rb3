#include "world/EventAnim.h"
#include "utl/Symbols.h"

EventAnim* gEventAnimOwner;

INIT_REVS(EventAnim)

EventAnim::EventAnim() : mStart(this), mEnd(this), mKeys(this), mResetStart(1), mLastFrame(-1e+30f) {
    
}

EventAnim::EventCall::EventCall(Hmx::Object* o) : mDir(o, 0), mEvent(o, 0) {}
EventAnim::KeyFrame::KeyFrame(Hmx::Object* o) : mTime(0), mCalls(o) {}

void EventAnim::StartAnim(){
    mLastFrame = -1e+30f;
    TriggerEvents(mStart);
}

void EventAnim::EndAnim(){
    TriggerEvents(mEnd);
    if(mResetStart){
        ResetEvents(mStart);
        for(ObjList<KeyFrame>::iterator it = mKeys.begin(); it != mKeys.end(); it++){
            ResetEvents(it->mCalls);
        }
    }
}

float EventAnim::EndFrame(){
    if(mKeys.size() == 0) return 0;
    else return mKeys.back().mTime;
}

void EventAnim::SetFrame(float frame, float blend){
    RndAnimatable::SetFrame(frame, blend);
    for(ObjList<KeyFrame>::iterator it = mKeys.begin(); it != mKeys.end(); ++it){
        if(it->mTime > frame) break;
        if(it->mTime >= mLastFrame){
            TriggerEvents(it->mCalls);
        }
    }
    mLastFrame = frame;
}

void EventAnim::TriggerEvents(ObjList<EventAnim::EventCall>& calls){
    for(ObjList<EventCall>::iterator it = calls.begin(); it != calls.end(); ++it){
        if((*it).mEvent){
            (*it).mEvent->Trigger();
        }
    }
}

void EventAnim::ResetEvents(ObjList<EventAnim::EventCall>& calls){
    for(ObjList<EventCall>::iterator it = calls.begin(); it != calls.end(); ++it){
        if((*it).mDir && (*it).mEvent){
            (*it).mEvent->BasicReset();
        }
    }
}

BEGIN_COPYS(EventAnim)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndAnimatable)
    CREATE_COPY(EventAnim)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mKeys)
        COPY_MEMBER(mStart)
        COPY_MEMBER(mEnd)
        COPY_MEMBER(mResetStart)
    END_COPYING_MEMBERS
END_COPYS

SAVE_OBJ(EventAnim, 0x7F)

BEGIN_LOADS(EventAnim)
    LOAD_REVS(bs)
    ASSERT_REVS(1, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(RndAnimatable)
    bs >> mKeys;
    if(gRev != 0){
        bs >> mStart;
        bs >> mResetStart;
        bs >> mEnd;
    }
END_LOADS

BinStream& operator>>(BinStream& bs, EventAnim::KeyFrame& k){
    bs >> k.mTime;
    bs >> k.mCalls;
    return bs;
}

BinStream& operator>>(BinStream& bs, EventAnim::EventCall& e){
    bs >> e.mDir;
    e.mEvent.Load(bs, true, e.mDir);
    return bs;
}

BEGIN_HANDLERS(EventAnim)
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xCC)
END_HANDLERS

BEGIN_CUSTOM_PROPSYNC(EventAnim::EventCall)
    SYNC_PROP(dir, o.mDir)
    SYNC_PROP(event, o.mEvent)
END_CUSTOM_PROPSYNC

BEGIN_CUSTOM_PROPSYNC(EventAnim::KeyFrame)
    SYNC_PROP_MODIFY(time, o.mTime, gEventAnimOwner->RefreshKeys())
    SYNC_PROP(events, o.mCalls)
END_CUSTOM_PROPSYNC

BEGIN_PROPSYNCS(EventAnim)
    gEventAnimOwner = this;
    SYNC_PROP(start, mStart)
    SYNC_PROP(end, mEnd)
    SYNC_PROP(reset_on_end, mResetStart)
    SYNC_PROP(keys, mKeys)
    SYNC_SUPERCLASS(RndAnimatable)
END_PROPSYNCS