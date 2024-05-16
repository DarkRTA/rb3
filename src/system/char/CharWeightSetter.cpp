#include "char/CharWeightSetter.h"

CharWeightSetter::CharWeightSetter() : mBase(this, 0), mDriver(this, 0), mMinWeights(this, kObjListNoNull), mMaxWeights(this, kObjListNoNull),
    mFlags(0), mOffset(0.0f), mScale(1.0f), mBaseWeight(0.0f), mBeatsPerWeight(0.0f) {

}

void CharWeightSetter::SetWeight(float weight){
    mBaseWeight = weight;
    mWeight = weight;
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

