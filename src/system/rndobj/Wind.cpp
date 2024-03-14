#include "rndobj/Wind.h"

RndWind::RndWind() : mPrevailing(0.0f, 0.0f, 0.0f), mRandom(0.0f, 0.0f, 0.0f), mTimeLoop(100.0f), mSpaceLoop(100.0f), mWindOwner(this, this) {
    SyncLoops();
}

RndWind::~RndWind(){
    
}

void RndWind::SetWindOwner(RndWind* wind){
    // RndWind* toSet = (wind) ? wind : this;
    mWindOwner = (wind) ? wind : this;
}

void RndWind::Zero(){
    mRandom.Set(0.0f, 0.0f, 0.0f);
    mPrevailing.Set(0.0f, 0.0f, 0.0f);
}

void RndWind::SetDefaults(){
    mPrevailing.Set(0.0f, 0.0f, 0.0f);
    mRandom.Set(17.0f, 17.0f, 0.0f);
    mTimeLoop = 100.0f;
    mSpaceLoop = 100.0f;
}

SAVE_OBJ(RndWind, 0x96)

BEGIN_COPYS(RndWind)
    COPY_SUPERCLASS(Hmx::Object)
    GET_COPY(RndWind)
    BEGIN_COPY_CHECKED
        COPY_MEMBER(mWindOwner)
    END_COPY_CHECKED
END_COPYS
