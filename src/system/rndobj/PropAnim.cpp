#include "rndobj/PropAnim.h"

RndPropAnim::RndPropAnim() : mLastFrame(0.0f), mInSetFrame(0), mLoop(0) {

}

RndPropAnim::~RndPropAnim(){
    RemoveKeys();
}

SAVE_OBJ(RndPropAnim, 0x43);
