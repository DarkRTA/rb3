#include "bandobj/StreakMeter.h"
#include "utl/Symbols.h"

StreakMeter::StreakMeter() : mStreakMultiplier(1), mBandMultiplier(1), mMaxMultiplier(4), mShowBandMult(0), mNewStreakTrig(this, 0), mEndStreakTrig(this, 0), mPeakStateTrig(this, 0),
    mBreakOverdriveTrig(this, 0), mMultiMeterAnim(this, 0), mMultiplierLabel(this, 0), mXLabel(this, 0), mMeterWipeAnim(this, 0), mStarDeployTrig(this, 0), mEndOverdriveTrig(this, 0),
    mStarDeployStopTrig(this, 0), mStarDeployPauseTrig(this, 0), mResetTrig(this, 0), mHideMultiplierTrig(this, 0), unk248(this, 0), unk254(this, 0), unk260(0), mPartBarsGroup(this, 0),
    mPartColorAnims(this), mPartFadeAnims(this), mPartWipeAnims(this), mPartWipeResidualAnims(this), mResidueFadeTrig(this, 0), mNumPartsAnim(this, 0), mPartSparksLaunchers(this),
    unk2c8(1), unk2d0(-1) {

}

BEGIN_HANDLERS(StreakMeter)
    HANDLE_ACTION(set_multiplier, SetMultiplier(_msg->Int(2)))
    HANDLE_ACTION(set_band_multiplier, SetBandMultiplier(_msg->Int(2)))
    HANDLE_ACTION(break_streak, BreakStreak(true))
    HANDLE_ACTION(star_deploy, Overdrive())
    HANDLE_ACTION(star_deploy_stop, EndOverdrive())
    HANDLE_ACTION(reset, Reset())
    HANDLE_ACTION(set_wipe, SetWipe(_msg->Float(2)))
    HANDLE_ACTION(peak_state, SetPeakState())
    HANDLE_SUPERCLASS(RndDir)
    HANDLE_CHECK(0x184)
END_HANDLERS

BEGIN_PROPSYNCS(StreakMeter)
    SYNC_PROP(streak_multiplier, mStreakMultiplier)
    SYNC_PROP(band_multiplier, mBandMultiplier)
    SYNC_PROP(max_multiplier, mMaxMultiplier)
    SYNC_PROP(show_band_mult, mShowBandMult)
    SYNC_SUPERCLASS(RndDir)
END_PROPSYNCS