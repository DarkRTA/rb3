#include "bandobj/BandStarDisplay.h"
#include "obj/ObjVersion.h"
#include "utl/Symbols.h"

INIT_REVS(BandStarDisplay);

BandStarDisplay::BandStarDisplay() : mNumStars(0), mStars(this), mStarSweepAnims(this), mStarFullTriggers(this), mStarGoldTriggers(this), mStarOffsetAnim(this, 0), mEarnStarSfx(this, 0), mEarnSpadeSfx(this, 0), mStarType("normal") {

}

BandStarDisplay::~BandStarDisplay(){

}

void BandStarDisplay::SetNumStars(float f, bool b){
    SetupStars();
    if(f > 0){
        float min = Min<float>(f, mStars.size() + 1);
        if(min < mNumStars) ResetStars();
        // more...
    }
}

void BandStarDisplay::SyncObjects(){
    RndDir::SyncObjects();
    Reset();
}

void BandStarDisplay::Reset(){ ResetStars(); }

void BandStarDisplay::SetupStars(){
    if(mStars.empty()){
        mStarSweepAnims.clear();
        mStarFullTriggers.clear();
        for(int i = 0; i < 5; i++){
            RndDir* stardir = Find<RndDir>(MakeString("star%d", i), true);
            mStars.push_back(ObjPtr<RndDir, ObjectDir>(this, stardir));

            RndAnimatable* anim = stardir->Find<RndAnimatable>("sweep.mnm", true);
            mStarSweepAnims.push_back(ObjPtr<RndAnimatable, ObjectDir>(this, anim));

            EventTrigger* fulltrig = stardir->Find<EventTrigger>("full.trig", true);
            mStarFullTriggers.push_back(ObjPtr<EventTrigger, ObjectDir>(this, fulltrig));

            EventTrigger* goldtrig = stardir->Find<EventTrigger>("gold.trig", true);
            mStarGoldTriggers.push_back(ObjPtr<EventTrigger, ObjectDir>(this, goldtrig));
        }
        mStarOffsetAnim = Find<RndAnimatable>("stars_offset.tnm", true);
        mEarnStarSfx = Find<Sequence>("achieve_star.cue", true);
        mEarnSpadeSfx = Find<Sequence>("achieve_spade.cue", true);
        SetStarType(mStarType, true);
    }
}

void BandStarDisplay::ResetStars(){
    SetupStars();
    for(int i = 0; i < mStars.size(); i++){
        RndDir* star = mStars[i];
        star->Find<EventTrigger>("reset.trig", true)->Trigger();
        if(i > 0) star->SetShowing(false);
    }
    mStarOffsetAnim->SetFrame(0, 1);
    mNumStars = 0;
}

void BandStarDisplay::SetStarType(Symbol s, bool b){
    if(s == mStarType && !b) return;
    float frame = -1.0f;
    if(s == normal) frame = 0;
    else if(s == tour) frame = 1;
    if(frame != -1.0f){
        mStarType = s;
        for(int i = 0; i < mStars.size(); i++){
            mStars[i]->Find<RndAnimatable>("config.anim", true)->SetFrame(frame, 1.0f);
        }
    }
}

SAVE_OBJ(BandStarDisplay, 0xDC)

BEGIN_COPYS(BandStarDisplay)
    CREATE_COPY_AS(BandStarDisplay, rhs)
    MILO_ASSERT(rhs, 0xE9);
    COPY_MEMBER_FROM(rhs, mStarType)
    COPY_SUPERCLASS(RndDir)
END_COPYS

void BandStarDisplay::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(2, 0);
    if(gRev == 1){
        if(IsProxy()) bs >> mStarType;
        else {
            Symbol s; bs >> s;
        }
    }
    if(gRev >= 2 && IsProxy()) bs >> mStarType;
    PushRev(packRevs(gAltRev, gRev), this);
    RndDir::PreLoad(bs);
}

void BandStarDisplay::PostLoad(BinStream& bs){
    RndDir::PostLoad(bs);
    int revs = PopRev(this);
    gRev = getHmxRev(revs);
    gAltRev = getAltRev(revs);
}

BEGIN_PROPSYNCS(BandStarDisplay)
    SYNC_PROP_SET(num_stars, mNumStars, SetNumStars(_val.Float(), true))
    SYNC_PROP_SET(star_type, mStarType, SetStarType(_val.Sym(), false))
    SYNC_SUPERCLASS(RndDir)
END_PROPSYNCS

BEGIN_HANDLERS(BandStarDisplay)
    HANDLE_ACTION(reset, Reset())
    HANDLE_SUPERCLASS(RndDir)
    HANDLE_CHECK(0x121)
END_HANDLERS
