#include "char/CharWeightSetter.h"
#include "obj/Task.h"

INIT_REVS(CharWeightSetter)

CharWeightSetter::CharWeightSetter() : mBase(this, 0), mDriver(this, 0), mMinWeights(this, kObjListNoNull), mMaxWeights(this, kObjListNoNull),
    mFlags(0), mOffset(0.0f), mScale(1.0f), mBaseWeight(0.0f), mBeatsPerWeight(0.0f) {

}

void CharWeightSetter::SetWeight(float weight){
    mBaseWeight = weight;
    mWeight = weight;
}

// fn_804FD058 - poll
void CharWeightSetter::Poll(){
    if(mDriver){
        mBaseWeight = mScale * mDriver->EvaluateFlags(mFlags) + mOffset;
    }
    else if(mBase){
        mBaseWeight = mScale * mBase->Weight() + mOffset;
    }

    if(mMinWeights.size() > 0){
        float newminweight = mBaseWeight;
        for(ObjPtrList<CharWeightSetter, ObjectDir>::iterator it = mMinWeights.begin(); it != mMinWeights.end(); ++it){
            MinEq(newminweight, (*it)->Weight());
        }
        mBaseWeight = newminweight;
    }

    if(mMaxWeights.size() > 0){
        float newmaxweight = mBaseWeight;
        for(ObjPtrList<CharWeightSetter, ObjectDir>::iterator it = mMaxWeights.begin(); it != mMaxWeights.end(); ++it){
            MaxEq(newmaxweight, (*it)->Weight());
        }
        mBaseWeight = newmaxweight;
    }

    if(mBaseWeight != mWeight){
        if(mBeatsPerWeight <= 0.0f) mWeight = mBaseWeight;
        else {
            float secs = TheTaskMgr.DeltaBeat() / mBeatsPerWeight;
            if(secs > 0.0f){
                float clamped = Clamp(-secs, secs, mBaseWeight - mWeight);
                mWeight += clamped;
            }
        }
    }
}


void CharWeightSetter::PollDeps(std::list<Hmx::Object*>& changedBy, std::list<Hmx::Object*>& change){
    changedBy.push_back(mDriver);
    changedBy.push_back(mBase);
    for(ObjPtrList<CharWeightSetter, ObjectDir>::iterator it = mMinWeights.begin(); it != mMinWeights.end(); ++it){
        changedBy.push_back(*it);
    }
    for(ObjPtrList<CharWeightSetter, ObjectDir>::iterator it = mMaxWeights.begin(); it != mMaxWeights.end(); ++it){
        changedBy.push_back(*it);
    }
    for(std::vector<ObjRef*>::reverse_iterator it = mRefs.rbegin(); it != mRefs.rend(); it++){
        CharWeightable* weightowner = dynamic_cast<CharWeightable*>((*it)->RefOwner());
        if(weightowner) change.push_back(weightowner);
    }
}

SAVE_OBJ(CharWeightSetter, 0x73)

BEGIN_LOADS(CharWeightSetter)
    LOAD_REVS(bs)
    ASSERT_REVS(9, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    if(gRev > 1) LOAD_SUPERCLASS(CharWeightable)
    bs >> mDriver;
    bs >> mFlags;
    if(gRev < 3){
        mScale = 1.0f;
        mOffset = 0.0f;
    }
    else if(gRev < 4){
        bool b;
        bs >> b;
        if(b){
            mScale = -1.0f;
            mOffset = 1.0f;
        }
        else {
            mScale = 1.0f;
            mOffset = 0.0f;
        }
    }
    else bs >> mOffset >> mScale;
    if(gRev < 2){
        ObjPtrList<CharWeightable,ObjectDir> pList(this, kObjListNoNull);
        bs >> pList;
        for(ObjPtrList<CharWeightable,ObjectDir>::iterator it = pList.begin(); it != pList.end(); ++it){
            (*it)->SetWeightOwner(this);
        }
    }
    if(gRev > 4){
        bs >> mBaseWeight;
        bs >> mBeatsPerWeight;
    }
    else {
        mBaseWeight = mWeight;
        mBeatsPerWeight = 0.0f;
    }
    if(gRev > 5) bs >> mBase;
    if(gRev > 8){
        bs >> mMinWeights;
        bs >> mMaxWeights;
    }
    else {
        if(gRev > 6){
            ObjPtr<CharWeightSetter, ObjectDir> ptrWS(this, 0);
            bs >> ptrWS;
            if(ptrWS) mMinWeights.push_back(ptrWS);
        }
        if(gRev > 7){
            ObjPtr<CharWeightSetter, ObjectDir> ptrWS(this, 0);
            bs >> ptrWS;
            if(ptrWS) mMaxWeights.push_back(ptrWS);
        }
    }
    
END_LOADS
