#include "beatmatch/JoypadTrackWatcherImpl.h"
#include "beatmatch/GameGemList.h"

JoypadTrackWatcherImpl::JoypadTrackWatcherImpl(int track, const UserGuid& u, int slot, SongData* data, GameGemList* gemlist, TrackWatcherParent* parent, DataArray* cfg, int size) :
    TrackWatcherImpl(track, u, slot, data, gemlist, parent, cfg, size), mChordSlop(50.0f), mChordGemInProgress(-1), mChordSlotsInProgress(0), mChordLastSlot(0) {

}

JoypadTrackWatcherImpl::~JoypadTrackWatcherImpl(){

}

// fn_804672B8 - swing
bool JoypadTrackWatcherImpl::Swing(int, bool, bool, GemHitFlags){

}

bool JoypadTrackWatcherImpl::AllowAllInputInRolls() const { return false; }

void JoypadTrackWatcherImpl::TryToCompleteChord(float f, int i){
    GameGem* gem = mGemList->GetGem(mChordGemInProgress);
    int slots = gem->mSlots;
    if(slots & 1 << i){
        mChordSlotsInProgress |= 1 << i;
        if(mChordSlotsInProgress == slots){
            OnHit(f, i, mChordGemInProgress, mChordSlotsInProgress, kGemHitFlagNone);
        }
    }
    else {
        OnMiss(f, i, mChordGemInProgress, mChordSlotsInProgress, kGemHitFlagNone);
        ResetChordInProgress();        
    }
}

void JoypadTrackWatcherImpl::FretButtonUp(int i){ KillSustainForSlot(i); }
float JoypadTrackWatcherImpl::HitGemHook(float, int, GemHitFlags){ ResetChordInProgress(); }
float JoypadTrackWatcherImpl::JumpHook(float f){ ResetChordInProgress(); }
float JoypadTrackWatcherImpl::PollHook(float f){ CheckForChordTimeout(f); }

void JoypadTrackWatcherImpl::CheckForChordTimeout(float f){
    if(mChordGemInProgress != -1 && mChordTimeout < f){
        OnMiss(f, mChordLastSlot, mChordGemInProgress, mChordSlotsInProgress, kGemHitFlagNone);
        ResetChordInProgress();
    }
}

void JoypadTrackWatcherImpl::ResetChordInProgress(){
    mChordGemInProgress = -1;
    mChordSlotsInProgress = 0;
    mChordLastSlot = -1;
    mChordTimeout = 0.0f;
}