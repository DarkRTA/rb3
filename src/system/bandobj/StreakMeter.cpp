#include "bandobj/StreakMeter.h"
#include "utl/Symbols.h"

StreakMeter::StreakMeter() : mStreakMultiplier(1), mBandMultiplier(1), mMaxMultiplier(4), mShowBandMult(0), mNewStreakTrig(this, 0), mEndStreakTrig(this, 0), mPeakStateTrig(this, 0),
    mBreakOverdriveTrig(this, 0), mMultiMeterAnim(this, 0), mMultiplierLabel(this, 0), mXLabel(this, 0), mMeterWipeAnim(this, 0), mStarDeployTrig(this, 0), mEndOverdriveTrig(this, 0),
    mStarDeployStopTrig(this, 0), mStarDeployPauseTrig(this, 0), mResetTrig(this, 0), mHideMultiplierTrig(this, 0), unk248(this, 0), unk254(this, 0), unk260(0), mPartBarsGroup(this, 0),
    mPartColorAnims(this), mPartFadeAnims(this), mPartWipeAnims(this), mPartWipeResidualAnims(this), mResidueFadeTrig(this, 0), mNumPartsAnim(this, 0), mPartSparksLaunchers(this),
    unk2c8(1), unk2d0(-1) {

}

#pragma push
#pragma dont_inline on
void StreakMeter::SyncObjects(){
    bool audible = true;
    Hmx::Object* gamemodeObj = FindObject("gamemode", true);
    if(gamemodeObj) audible = gamemodeObj->Property("play_streak_sfx", true)->Int(0);
    if(audible) mNewStreakTrig = Find<EventTrigger>("new_streak.trig", true);
    else mNewStreakTrig = Find<EventTrigger>("new_streak_silent.trig", true);
    mEndStreakTrig = Find<EventTrigger>("end_streak.trig", true);
    mPeakStateTrig = Find<EventTrigger>("peak_state.trig", true);
    mBreakOverdriveTrig = Find<EventTrigger>("break_overdrive.trig", true);
    mMultiMeterAnim = Find<RndTransAnim>("multi-meter_anim.tnm", true);
    mMultiplierLabel = Find<BandLabel>("multiplier.lbl", true);
    mXLabel = Find<BandLabel>("x.lbl", true);
    mMeterWipeAnim = Find<RndPropAnim>("meter_wipe.anim", true);
    mStarDeployTrig = Find<EventTrigger>("star_deploy.trig", true);
    mEndOverdriveTrig = Find<EventTrigger>("end_overdrive.trig", true);
    mStarDeployStopTrig = Find<EventTrigger>("star_deploy_stop.trig", true);
    mStarDeployPauseTrig = Find<EventTrigger>("star_deploy_pause.trig", false);
    mResetTrig = Find<EventTrigger>("reset.trig", true);
    mHideMultiplierTrig = Find<EventTrigger>("hide_multiplier.trig", true);
    mPartBarsGroup = Find<RndGroup>("part_bars.grp", false);
    if(mPartBarsGroup){
        unk260 = true;
        mPartColorAnims.clear();
        mPartFadeAnims.clear();
        mPartWipeAnims.clear();
        mPartWipeResidualAnims.clear();
        for(int i = 0; i < 3; i++){
            mPartColorAnims.push_back(ObjPtr<RndPropAnim, ObjectDir>(this, Find<RndPropAnim>(MakeString("part_color%d.anim", i + 1), true)));
            mPartFadeAnims.push_back(ObjPtr<RndPropAnim, ObjectDir>(this, Find<RndPropAnim>(MakeString("part_fade%d.anim", i + 1), true)));
            mPartWipeAnims.push_back(ObjPtr<RndPropAnim, ObjectDir>(this, Find<RndPropAnim>(MakeString("part_wipe%d.anim", i + 1), true)));
            mPartWipeResidualAnims.push_back(ObjPtr<RndPropAnim, ObjectDir>(this, Find<RndPropAnim>(MakeString("part_wipe%d_residual.anim", i + 1), true)));
            mPartSparksLaunchers.push_back(ObjPtr<RndPartLauncher, ObjectDir>(this, Find<RndPartLauncher>(MakeString("part_sparks%d.ml", i + 1), true)));
        }
        mResidueFadeTrig = Find<EventTrigger>("residue_fade.trig", true);
        mNumPartsAnim = Find<RndPropAnim>("num_parts.anim", true);
    }
    RndDir::SyncObjects();
}
#pragma pop

void StreakMeter::CombineMultipliers(bool b){
    if(b != mShowBandMult){
        mShowBandMult = b;
        MultiplierChanged();
    }
}

void StreakMeter::SetBandMultiplier(int mult){
    if(mBandMultiplier != mult){
        mBandMultiplier = mult;
        if(mShowBandMult) mNewStreakTrig->Trigger();
        MultiplierChanged();
    }
}

bool StreakMeter::SetMultiplier(int mult){
    if(mult != mStreakMultiplier && mult <= mMaxMultiplier){
        mStreakMultiplier = mult;
        if(mult > 1) mNewStreakTrig->Trigger();
        MultiplierChanged();
        return true;
    }
    else return false;
}

int StreakMeter::GetMultiplierToShow() const {
    if(mShowBandMult) return mStreakMultiplier * mBandMultiplier;
    else return mStreakMultiplier;
}

void StreakMeter::MultiplierChanged(){
    int mult = GetMultiplierToShow();
    if(mult != unk2d4){
        if(mult > 1) UpdateMultiplierText(mult);
        else mHideMultiplierTrig->Trigger();
    }
    unk2d4 = mult;
}

void StreakMeter::UpdateMultiplierText(int mult){
    mMultiplierLabel->SetShowing(true);
    mMultiplierLabel->SetTokenFmt(streak_multiplier_fmt, mult);
    mXLabel->SetShowing(true);
}

void StreakMeter::BreakStreak(bool b){
    mStreakMultiplier = 1;
    if(b) mEndStreakTrig->Trigger();
    int mult = GetMultiplierToShow();
    if(mult != 1){
        mBreakOverdriveTrig->Trigger();
        UpdateMultiplierText(mult);
    }
    SetWipe(0);
}

void StreakMeter::SetPeakState(){
    mPeakStateTrig->Trigger();
}

void StreakMeter::Overdrive() const {
    mStarDeployTrig->Trigger();
}

void StreakMeter::EndOverdrive() const {
    mStarDeployStopTrig->Trigger();
}

void StreakMeter::Reset(){
    mResetTrig->Trigger();
    SetWipe(0);
    unk2cc = false;
    unk2cd = false;
    unk2ce = false;
    SetMultiplier(1);
    SetBandMultiplier(1);
    unk2d4 = 1;
    for(int i = 0; i < mPartWipeAnims.size(); i++){
        SetPartPct(i, 0, false);
    }
}

void StreakMeter::SetWipe(float f){
    mMeterWipeAnim->SetFrame(f, 1.0f);
}

void StreakMeter::SetPartColor(int i, VocalHUDColor col){
    if(col == kVocalColorInvalid) SetPartActive(i, false);
    else if(i < mPartColorAnims.size()){
        RndPropAnim* curanim = mPartColorAnims[i];
        if(curanim) curanim->SetFrame(col, 1.0f);
    }
}

void StreakMeter::SetNumParts(int num){
    if(unk260) mNumPartsAnim->SetFrame(num, 1.0f);
    unk2c8 = num;
}

// void __thiscall StreakMeter::SetNumParts(StreakMeter *this,int param_1)

// {
//   if (this[0x260] != (StreakMeter)0x0) {
//     (**(code **)(*(int *)(*(int *)(this + 0x2b8) + 4) + 0x34))((double)param_1,0x3ff0000000000000) ;
//   }
//   *(int *)(this + 0x2c8) = param_1;
//   return;
// }

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