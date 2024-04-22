#include "GemSmasher.h"
#include "os/Debug.h"
#include "rndobj/EventTrigger.h"
#include "utl/Messages.h"

GemSmasher::GemSmasher(int slot, RndDir* dir, bool keys) : mSlot(slot), mDir(dir), mHitSmashTrig(NULL),
    mHitDrumsTrig(NULL), mHitDrumsBonus(NULL), mHitCymsTrig(NULL), mHitCymsBonus(NULL), mHitChordTrig(NULL), 
    mHitChordBonus(NULL), mHitBonus(NULL), mBREHitTrig(NULL), mBREHitChord(NULL), mMissTrig(NULL), 
    mBurnTrig(NULL), mBurnBonusTrig(NULL), mBurnChordTrig(NULL), mBREBurnTrig(NULL), mBREBurnChord(NULL),
    mStopBurnTrig(NULL), mPressTrig(NULL), mReleaseTrig(NULL), mMissAfterRelease(NULL), mGemSmasherGlow(NULL),
    mGlowing(false), mBurning(false), unk_0x6A(keys) {
    if (mDir) {
        mHitSmashTrig = mDir->Find<EventTrigger>("hit.trig", false);
        if (mHitSmashTrig == NULL) mHitSmashTrig = mDir->Find<EventTrigger>("smash.trig", false);
        mHitDrumsTrig = mDir->Find<EventTrigger>("hit_drums.trig", false);
        mHitDrumsBonus = mDir->Find<EventTrigger>("hit_drums_bonus.trig", false);
        mHitCymsTrig = mDir->Find<EventTrigger>("hit_cymbals.trig", false);
        mHitCymsBonus = mDir->Find<EventTrigger>("hit_cymbals_bonus.trig", false);
        mHitChordTrig = mDir->Find<EventTrigger>("hit_chord.trig", false);
        mHitChordBonus = mDir->Find<EventTrigger>("hit_chord_bonus.trig", false);
        mHitBonus = mDir->Find<EventTrigger>("hit_bonus.trig", false);
        mBREHitTrig = mDir->Find<EventTrigger>("big_rock_hit.trig", false);
        mBREHitChord = mDir->Find<EventTrigger>("big_rock_hit_chord.trig", false);
        mMissTrig = mDir->Find<EventTrigger>("miss.trig", false);
        mBurnTrig = mDir->Find<EventTrigger>("burn.trig", false);
        mBurnBonusTrig = mDir->Find<EventTrigger>("burn_bonus.trig", false);
        mBurnChordTrig = mDir->Find<EventTrigger>("burn_chord.trig", false);
        mBREBurnTrig = mDir->Find<EventTrigger>("big_rock_burn.trig", false);
        mBREBurnChord = mDir->Find<EventTrigger>("big_rock_burn_chord.trig", false);
        mStopBurnTrig = mDir->Find<EventTrigger>("stop_burn.trig", false);
        mGemSmasherGlow = mDir->Find<RndMesh>("gem_smasher_glow.mesh", false);
        mPressTrig = mDir->Find<EventTrigger>("press.trig", false);
        mReleaseTrig = mDir->Find<EventTrigger>("release.trig", false);
        mMissAfterRelease = mDir->Find<EventTrigger>("miss_after_release.trig", false);
        mHitFillTrig = mDir->Find<EventTrigger>("hit_fill.trig", false);
        EventTrigger* hitFillLight = mDir->Find<EventTrigger>("hit_fill_light.trig", false);
        if (hitFillLight) {
            EventTrigger* hitFillMediumTrig, *hitFillHardTrig;
            hitFillMediumTrig = (EventTrigger*)mDir->Find<EventTrigger>("hit_fill_medium.trig", false);
            hitFillHardTrig = (EventTrigger*)mDir->Find<EventTrigger>("hit_fill_hard.trig", false);
            MILO_ASSERT(hitFillMediumTrig, 87);
            MILO_ASSERT(hitFillHardTrig, 88);
            mMoreTriggers.push_back(mHitFillTrig);
            mMoreTriggers.push_back(hitFillLight);
            mMoreTriggers.push_back(hitFillLight);
            mMoreTriggers.push_back(hitFillMediumTrig);
            mMoreTriggers.push_back(hitFillMediumTrig);
            mMoreTriggers.push_back(hitFillHardTrig);
            mMoreTriggers.push_back(hitFillHardTrig);
        }
    }
}

GemSmasher::~GemSmasher() {}

bool GemSmasher::Null() const { return !mDir; }

void GemSmasher::Reset(bool b) {
    mDir->HandleType(reset_msg.mData);
    if (b) mDir->HandleType(reset_particles_msg.mData);
    mBurning = false;
    SetGlowing(false);
}

bool GemSmasher::Showing() const { if (mDir) return mDir->mShowing; else return 0; }
void GemSmasher::Hit() { if (mHitSmashTrig) mHitSmashTrig->Trigger(); }
void GemSmasher::HitDrum() { if (mHitDrumsTrig) mHitDrumsTrig->Trigger(); }
void GemSmasher::HitDrumBonus() { if (mHitDrumsBonus) mHitDrumsBonus->Trigger(); }
void GemSmasher::HitCymbal() { if (mHitCymsTrig) mHitCymsTrig->Trigger(); }
void GemSmasher::HitCymbalBonus() { if (mHitCymsBonus) mHitCymsBonus->Trigger(); }
void GemSmasher::HitChord() { if (mHitChordTrig) mHitChordTrig->Trigger(); }
void GemSmasher::HitChordBonus() { if (mHitChordBonus) mHitChordBonus->Trigger(); else HitBonus(); }
void GemSmasher::HitBonus() { if (mHitBonus) mHitBonus->Trigger(); else Hit(); }
void GemSmasher::CodaHit() { if (mBREHitTrig) mBREHitTrig->Trigger(); else Hit(); }
void GemSmasher::CodaHitChord() { if (mBREHitChord) mBREHitChord->Trigger(); else HitChord(); }

void GemSmasher::Miss() {
    if (unk_0x6A && !mGlowing) {
        if (mMissAfterRelease) mMissAfterRelease->Trigger();
    } else {
        if (mMissTrig) mMissTrig->Trigger();
    }
    StopBurn();
}

void GemSmasher::Burn() {
    if (mBurnTrig) { mBurnTrig->Trigger(); mBurning = true; }
}

void GemSmasher::BurnBonus() {
    if (mBurnBonusTrig) {mBurnBonusTrig->Trigger(); mBurning = true;} else Burn();
}

void GemSmasher::BurnChord() {
    if (mBurnChordTrig) { mBurnChordTrig->Trigger(); mBurning = true; }
}

void GemSmasher::CodaBurn() {
    if (mBREBurnTrig) {mBREBurnTrig->Trigger(); mBurning = true;} else Burn();
}

void GemSmasher::CodaBurnChord() {
    if (mBREBurnChord) {mBREBurnChord->Trigger(); mBurning = true;} else BurnChord();
}

void GemSmasher::StopBurn() {
    if (mBurning && mStopBurnTrig) {mStopBurnTrig->Trigger(); mBurning = false;}
}

void GemSmasher::FillHit(int i) {
    if (i == 0) i = mMoreTriggers.size();
    bool in_range = false;
    if (i < mMoreTriggers.size() && mMoreTriggers[i]) { mMoreTriggers[i]->Trigger(); in_range = true; }
    if (!in_range && mHitFillTrig) mHitFillTrig->Trigger();
}

void GemSmasher::SetGlowing(bool b) {
    if (unk_0x6A) {
        bool test;
        if (mDir) test = mDir->mShowing;
        else test = false;
        if (test) {
            if (b == mGlowing) return;
            mGlowing = b;
            EventTrigger* trig;
            if (b & 0xFF) trig = mPressTrig; else trig = mReleaseTrig;
            if (trig == NULL) return;
            trig->Trigger();
            return;
        }
        mGlowing = false;
        return;
    }
    if (mGemSmasherGlow) {
        mGemSmasherGlow->mShowing = b;
    }
    mGlowing = b;
}

bool GemSmasher::Glowing() const { return mGlowing; }