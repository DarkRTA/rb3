#include "bandobj/StreakMeter.h"

StreakMeter::StreakMeter() : mStreakMultiplier(1), mBandMultiplier(1), mMaxMultiplier(4), mShowBandMult(0), mNewStreakTrig(this, 0), mEndStreakTrig(this, 0), mPeakStateTrig(this, 0),
    mBreakOverdriveTrig(this, 0), mMultiMeterAnim(this, 0), mMultiplierLabel(this, 0), mXLabel(this, 0), mMeterWipeAnim(this, 0), mStarDeployTrig(this, 0), mEndOverdriveTrig(this, 0),
    mStarDeployStopTrig(this, 0), mStarDeployPauseTrig(this, 0), mResetTrig(this, 0), mHideMultiplierTrig(this, 0), unk248(this, 0), unk254(this, 0), unk260(0), mPartBarsGroup(this, 0),
    mPartColorAnims(this), mPartFadeAnims(this), mPartWipeAnims(this), mPartWipeResidualAnims(this), mResidueFadeTrig(this, 0), mNumPartsAnim(this, 0), mPartSparksLaunchers(this),
    unk2c8(1), unk2d0(-1) {

}