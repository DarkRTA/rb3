#include "bandobj/BandTrack.h"

INIT_REVS(BandTrack);

BandTrack::BandTrack(Hmx::Object* o) : mDisabled(0), mSimulatedNet(0), mInstrument(""), unk14(4), unk18(0), unk19(0), unk1a(0), unk1b(0), unk1c(0), mInUse(0), unk1e(0), unk1f(0),
    mPlayerIntro(o, 0), mStarPowerMeter(o, 0), mStreakMeter(o, 0), mPopupObject(o, 0), mPlayerFeedback(o, 0), mFailedFeedback(o, 0), unk68(o, 0), unk74(""), unk78(0),
    mEndgameFeedback(o, 0), unk88(0), unk8c(0), mParent(o, 0), mRetractTrig(o, 0), mResetTrig(o, 0), mDeployTrig(o, 0), mStopDeployTrig(o, 0), mIntroTrig(o, 0), unkd8(o, 0),
    unke4(o, 0), unkf0(o, 0), unkfc(this, 0), unk108(1), unk109(1), unk10c(-1) {

}

BEGIN_COPYS(BandTrack)
END_COPYS

BEGIN_LOADS(BandTrack)
END_LOADS

void BandTrack::Save(BinStream&){}

void BandTrack::LoadTrack(BinStream& bs, bool b1, bool b2, bool b3){
    LOAD_REVS(bs);
    ASSERT_REVS(3, 0);
    if(b2){
        Symbol s;
        bool bbb;
        bs >> bbb;
        bs >> s;
    }
    else {
        bs >> mSimulatedNet;
        bs >> mInstrument;
    }
    if(gRev >= 1 && !b1){
        bs >> mStarPowerMeter;
        bs >> mStreakMeter;
    }
    bool finalbool;
    if(gRev < 3){
        finalbool = false;
        if(!b3 || !b1) finalbool = true;
    }
    else finalbool = !b1;
    if(finalbool){
        bs >> mPlayerIntro;
        if(gRev < 1){
            bs >> mStarPowerMeter;
            bs >> mStreakMeter;
        }
        bs >> mPopupObject;
        bs >> mPlayerFeedback;
        bs >> mFailedFeedback;
        if(gRev >= 2) bs >> mEndgameFeedback;
    }
    if(!b1){
        bs >> mRetractTrig;
        bs >> mResetTrig;
        bs >> mDeployTrig;
        bs >> mStopDeployTrig;
        bs >> mIntroTrig;
    }
}

void BandTrack::CopyTrack(const BandTrack* c){
    COPY_MEMBER(mDisabled)
    COPY_MEMBER(mSimulatedNet)
    COPY_MEMBER(mInstrument)
    COPY_MEMBER(mPlayerIntro)
    COPY_MEMBER(mStarPowerMeter)
    COPY_MEMBER(mStreakMeter)
    COPY_MEMBER(mPopupObject)
    COPY_MEMBER(mPlayerFeedback)
    COPY_MEMBER(mFailedFeedback)
    COPY_MEMBER(mEndgameFeedback)
    COPY_MEMBER(mRetractTrig)
    COPY_MEMBER(mResetTrig)
    COPY_MEMBER(mDeployTrig)
    COPY_MEMBER(mStopDeployTrig)
    COPY_MEMBER(mIntroTrig)
}

void BandTrack::Init(Hmx::Object* o){
    if(o) mParent = dynamic_cast<TrackInterface*>(o);
    Reset();
}

void BandTrack::ResetStreakMeter(){
    if(mStreakMeter){
        mStreakMeter->Reset();
        if(mParent && mParent->HasPlayer()){
            mStreakMeter->SetShowing(true);
        }
        SetStreak(0, 1, 1, true);
    }
}