#include "rndobj/PropAnim.h"

RndPropAnim::RndPropAnim() : mLastFrame(0.0f), mInSetFrame(0), mLoop(0) {

}

RndPropAnim::~RndPropAnim(){
    RemoveKeys();
}

SAVE_OBJ(RndPropAnim, 0x43);

void RndPropAnim::RemoveKeys(){
    for(std::vector<PropKeys*>::iterator it = mPropKeys.begin(); it != mPropKeys.end(); it++){
        delete *it;
    }
    mPropKeys.clear();
}
