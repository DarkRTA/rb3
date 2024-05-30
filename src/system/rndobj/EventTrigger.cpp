#include "EventTrigger.h"
#include "rndobj/Draw.h"
#include "synth/Sequence.h"
#include "rndobj/PartLauncher.h"
#include "rndobj/AnimFilter.h"
#include "obj/DirItr.h"
#include "utl/Symbols.h"

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
    for(std::list<EventTrigger*>::iterator trigItr = trigList.begin(); trigItr != trigList.end(); trigItr++){

    }
    return DataNode(0);
}
#pragma pop

// #pragma dont_inline on
// static void thisisheretotestobjptrlist(Hmx::Object* obj){
//     ObjPtrList<RndDrawable, ObjectDir> lol(obj, kObjListNoNull);
//     lol.pop_back();
//     lol.back();
//     lol.empty();
//     lol.push_back(0);
// }

// static void test2(ObjPtrList<EventTrigger, ObjectDir>* l1, ObjPtrList<EventTrigger, ObjectDir>* l2){
//     *l1 = *l2;
// }
// #pragma dont_inline reset

// SAVE_OBJ(EventTrigger, 406)

EventTrigger::EventTrigger() : mAnims(this), mSpawnedTasks(this, kObjListNoNull), mProxyCalls(this), mSounds(this, kObjListNoNull), mShows(this, kObjListNoNull),
    mResetTriggers(this, kObjListNoNull), mHideDelays(this), mNextLink(this, 0), mPartLaunchers(this, kObjListNoNull), mAnimFrame(0.0f),
    unkbc(this, kObjListNoNull), unkcc(this, kObjListNoNull), mTriggerOrder(0), mAnimTrigger(0), unkde(-1) {
    RegisterEvents();
}