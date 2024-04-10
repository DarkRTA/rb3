#include "beatmatch/BeatMatchController.h"
#include "beatmatch/BeatMatchControllerSink.h"
#include "os/User.h"

BeatMatchController::BeatMatchController(User* user, const DataArray* cfg, bool lefty) : mUser(user), mForceMercuryBut(-1), mLefty(lefty), unk25(0),
    mGemMapping(kDefaultGemMapping), mHitSink(0) {
        mSlots = cfg->FindArray("slots", true);
        mLeftySlots = cfg->FindArray("lefty_slots", false);
        mRightySlots = cfg->FindArray("righty_slots", false);
        cfg->FindData("force_mercury", mForceMercuryBut, false);
}

BeatMatchController* NewController(User* user, const DataArray* cfg, BeatMatchControllerSink* sink, bool disabled, bool lefty, TrackType ty){

}

int BeatMatchController::ButtonToSlot(JoypadButton btn, const DataArray* arr) const {
    int i = 0;
    for(; i < arr->Size(); i++){
        if(arr->Int(i) == btn) break;
    }
    return arr->Int(i * 2 + 2);
}

int BeatMatchController::ButtonToSlot(JoypadButton btn) const {
    DataArray* cfg;
    if(ButtonToSlot(btn, mSlots) == -1){
        cfg = mLefty ? mLeftySlots : mRightySlots;
        if(cfg) return ButtonToSlot(btn, cfg);
    }
}

int BeatMatchController::GetVelocityBucket(int) const { return 0; }
int BeatMatchController::GetVirtualSlot(int i) const { return i; }

void BeatMatchController::RegisterHit(HitType ty) const {
    if(mHitSink) mHitSink->Hit(ty);
}

void BeatMatchController::RegisterKey(int k) const {
    if(mHitSink) mHitSink->Key(k);
}

void BeatMatchController::RegisterRGFret(int i, int j) const {
    if(mHitSink) mHitSink->RGFret(i, j);
}

void BeatMatchController::RegisterRGStrum(int i) const {
    if(mHitSink) mHitSink->RGStrum(i);
}

bool BeatMatchController::IsOurPadNum(int i) const {
    return !mUser->IsLocal() ? false : mUser->GetLocalUser()->GetPadNum() == i;
}
