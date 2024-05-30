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

EventTrigger::EventTrigger() : mAnims(this), mSpawnedTasks(this, kObjListNoNull), mProxyCalls(this), mSounds(this, kObjListNoNull), mShows(this, kObjListNoNull),
    mResetTriggers(this, kObjListNoNull), mHideDelays(this), mNextLink(this, 0), mPartLaunchers(this, kObjListNoNull), mAnimFrame(0.0f),
    unkbc(this, kObjListNoNull), unkcc(this, kObjListNoNull), mTriggerOrder(0), mAnimTrigger(0), unkde(-1) {
    RegisterEvents();
}

SAVE_OBJ(EventTrigger, 406)