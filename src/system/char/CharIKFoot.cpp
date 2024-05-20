#include "char/CharIKFoot.h"

CharIKFoot::CharIKFoot() : unk88(this, 0), unk94(0), mData(this, 0), mDataIndex(0), mMe(this, 0) {
    unk88 = Hmx::Object::New<RndTransformable>();
    unk88->mLocalXfm.Reset();
}

CharIKFoot::~CharIKFoot(){
    
}