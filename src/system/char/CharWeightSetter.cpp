#include "char/CharWeightSetter.h"

CharWeightSetter::CharWeightSetter() : mBase(this, 0), mDriver(this, 0), mMinWeights(this, kObjListNoNull), mMaxWeights(this, kObjListNoNull),
    mFlags(0), mOffset(0.0f), mScale(1.0f), mBaseWeight(0.0f), mBeatsPerWeight(0.0f) {

}

void CharWeightSetter::SetWeight(float weight){
    mBaseWeight = weight;
    mWeight = weight;
}