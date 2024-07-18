#include "char/CharWeightSetter.h"
#include "obj/Task.h"
#include "utl/Symbols.h"

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
    std::vector<ObjRef*>::const_reverse_iterator it = Refs().rbegin();
    std::vector<ObjRef*>::const_reverse_iterator itEnd = Refs().rend();
    for(; it != itEnd; ++it){
        CharWeightable* weightowner = dynamic_cast<CharWeightable*>((*it)->RefOwner());
        if(weightowner && weightowner->mWeightOwner == this) change.push_back(weightowner);
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

BEGIN_COPYS(CharWeightSetter)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(CharWeightable)
    CREATE_COPY(CharWeightSetter)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mDriver)
        COPY_MEMBER(mFlags)
        COPY_MEMBER(mBase)
        COPY_MEMBER(mOffset)
        COPY_MEMBER(mScale)
        COPY_MEMBER(mBaseWeight)
        COPY_MEMBER(mBeatsPerWeight)
        COPY_MEMBER(mMinWeights)
        COPY_MEMBER(mMaxWeights)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(CharWeightSetter)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xF4)
END_HANDLERS

BEGIN_PROPSYNCS(CharWeightSetter)
    SYNC_PROP(driver, mDriver)
    SYNC_PROP(flags, mFlags)
    SYNC_PROP(base, mBase)
    SYNC_PROP(offset, mOffset)
    SYNC_PROP(scale, mScale)
    SYNC_PROP(base_weight, mBaseWeight)
    SYNC_PROP(beats_per_weight, mBeatsPerWeight)
    SYNC_PROP(min_weights, mMinWeights)
    SYNC_PROP(max_weights, mMaxWeights)
    SYNC_SUPERCLASS(CharWeightable)
END_PROPSYNCS

DECOMP_FORCEFUNC(CharWeightSetter, CharWeightSetter, SetType)
DECOMP_FORCEFUNC_TEMPL(CharWeightSetter, ObjPtrList, Replace(0, 0), CharWeightable, ObjectDir)
DECOMP_FORCEFUNC_TEMPL(CharWeightSetter, ObjPtrList, RefOwner(), CharWeightable, ObjectDir)
DECOMP_FORCEFUNC_TEMPL(CharWeightSetter, ObjPtrList, Replace(0, 0), CharWeightSetter, ObjectDir)
DECOMP_FORCEFUNC_TEMPL(CharWeightSetter, ObjPtrList, RefOwner(), CharWeightSetter, ObjectDir)
DECOMP_FORCEDTOR(CharWeightSetter, CharWeightSetter)