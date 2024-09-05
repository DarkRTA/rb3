#include "bandobj/BandTrack.h"

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

void BandTrack::Init(Hmx::Object* o){
    if(o) mParent = dynamic_cast<TrackInterface*>(o);
    Reset();
}