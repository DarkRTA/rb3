#include "beatmatch/BeatMatchController.h"
#include "beatmatch/BeatMatchControllerSink.h"
#include "os/User.h"
#include "beatmatch/GuitarController.h"
#include "beatmatch/JoypadController.h"
#include "beatmatch/JoypadGuitarController.h"
#include "beatmatch/ButtonGuitarController.h"
#include "beatmatch/RealGuitarController.h"
#include "beatmatch/KeyboardController.h"
#include "beatmatch/JoypadMidiController.h"

BeatMatchController::BeatMatchController(User* user, const DataArray* cfg, bool lefty) : mUser(user), mForceMercuryBut(-1), mLefty(lefty), unk25(0),
    mGemMapping(kDefaultGemMapping), mHitSink(0) {
        mSlots = cfg->FindArray("slots", true);
        mLeftySlots = cfg->FindArray("lefty_slots", false);
        mRightySlots = cfg->FindArray("righty_slots", false);
        cfg->FindData("force_mercury", mForceMercuryBut, false);
}

BeatMatchController* NewController(User* user, const DataArray* cfg, BeatMatchControllerSink* sink, bool disabled, bool lefty, TrackType ty){
    DataArray* ctrl_cfg = SystemConfig("beatmatcher", "controllers", "beatmatch_controller_mapping");
    Symbol instr = ctrl_cfg->FindArray(cfg->Sym(0), true)->Sym(1);
    BeatMatchController* controller = 0;
    if(instr == "guitar"){
        controller = new GuitarController(user, cfg, sink, disabled, lefty);
    }
    else if(instr == "joypad"){
        controller = new JoypadController(user, cfg, sink, disabled, lefty);
    }
    else if(instr == "joypad_guitar"){
        controller = new JoypadGuitarController(user, cfg, sink, disabled, lefty);
    }
    else if(instr == "real_guitar"){
        if(ty - 1 <= 1U){
            controller = new ButtonGuitarController(user, cfg, sink, disabled, lefty);
        }
        else controller = new RealGuitarController(user, cfg, sink, disabled, lefty);
    }
    else if(instr == "keys"){
        if(ty == 5){
            controller = new KeyboardController(user, cfg, sink, disabled);
        }
        else controller = new JoypadMidiController(user, cfg, sink, disabled);
    }
    else MILO_FAIL("NewController: Bad controller type %s, %s", cfg->Sym(0), instr.Str());
    sink->SetController(controller);
    return controller;
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
