#include "rndobj/Wind.h"
#include "utl/Symbols.h"

INIT_REVS(RndWind)
Vector3 sOffset(0.0f, 0.3384f, 0.66843998f);

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

void RndWind::SyncLoops(){
    float f1 = (mTimeLoop == 0.0f) ? 0.0f : 1.0f / mTimeLoop;
    mTimeRate.Set(f1, f1 * 0.773437f, f1 * 1.38484f);
    f1 = (mSpaceLoop == 0.0f) ? 0.0f : 1.0f / mSpaceLoop;
    mSpaceRate.Set(f1, f1 * 0.773437f, f1 * 1.38484f);
}

SAVE_OBJ(RndWind, 0x96)

BEGIN_LOADS(RndWind)
    LOAD_REVS(bs)
    ASSERT_REVS(2, 0);
    LOAD_SUPERCLASS(Hmx::Object)
    bs >> mPrevailing >> mRandom >> mTimeLoop >> mSpaceLoop;
    if(gRev > 1){
        bs >> mWindOwner;
        SetWindOwner(mWindOwner);
    }
    SyncLoops();
END_LOADS

BEGIN_COPYS(RndWind)
    COPY_SUPERCLASS(Hmx::Object)
    GET_COPY(RndWind)
    BEGIN_COPY_CHECKED
        if(ty == kCopyShallow) mWindOwner = c->mWindOwner;
        else {
            mWindOwner = this;
            COPY_MEMBER(mWindOwner)
            COPY_MEMBER(mPrevailing)
            COPY_MEMBER(mRandom)
            COPY_MEMBER(mTimeLoop)
            COPY_MEMBER(mSpaceLoop)
            SyncLoops();
        }
    END_COPY_CHECKED
END_COPYS

void RndWind::Replace(Hmx::Object* from, Hmx::Object* to){
    Hmx::Object::Replace(from, to);
    if(mWindOwner == from){
        SetWindOwner(dynamic_cast<RndWind*>(to));
    }
}

BEGIN_HANDLERS(RndWind)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_ACTION(set_defaults, SetDefaults())
    HANDLE_ACTION(set_zero, Zero())
    HANDLE_CHECK(0xDA)
END_HANDLERS

BEGIN_PROPSYNCS(RndWind)
    SYNC_PROP(prevailing, mPrevailing)
    SYNC_PROP(random, mRandom)
    SYNC_PROP_METHOD(wind_owner, mWindOwner, SetWindOwner(_val.Obj<RndWind>(0)))
    SYNC_PROP_MODIFY(time_loop, mTimeLoop, SyncLoops())
    SYNC_PROP_MODIFY(space_loop, mSpaceLoop, SyncLoops())
END_PROPSYNCS