#include "rndobj/Wind.h"
#include "math/Rand.h"
#include "obj/ObjMacros.h"
#include "utl/Symbols.h"

INIT_REVS(RndWind)
float sWindField[0x401] = {0}, sWhiteField[0x400] = {0};
Rand* sRand;
Vector3 sOffset(0.0f, 0.3384f, 0.66843998f);

void SetWind(int, int, float, float, float) {

}

void RndWind::Init() {
    Register();
    sRand = new Rand(0x7FEF8A);
    SetWind(0, 0x400, 0, 0, 0.5f);
    sWindField[0x400] = sWindField[0];
    int i = 0;
    do {
        sWhiteField[i] = RandomFloat(0,1);
        i++;
    } while (i < 0x400);
    delete sRand;
    sRand = 0;
}

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
    CREATE_COPY(RndWind)
    BEGIN_COPYING_MEMBERS
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
    END_COPYING_MEMBERS
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
    SYNC_PROP_SET(wind_owner, mWindOwner, SetWindOwner(_val.Obj<RndWind>()))
    SYNC_PROP_MODIFY(time_loop, mTimeLoop, SyncLoops())
    SYNC_PROP_MODIFY(space_loop, mSpaceLoop, SyncLoops())
END_PROPSYNCS
