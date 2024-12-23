#include "beatmatch/JoypadTrackWatcherImpl.h"
#include "beatmatch/GameGemList.h"
#include "beatmatch/TrackWatcherParent.h"
#include "beatmatch/SongData.h"
#include "utl/TempoMap.h"
#include "beatmatch/BeatMatchUtl.h"

JoypadTrackWatcherImpl::JoypadTrackWatcherImpl(int track, const UserGuid& u, int slot, SongData* data, GameGemList* gemlist, TrackWatcherParent* parent, DataArray* cfg, int size) :
    TrackWatcherImpl(track, u, slot, data, gemlist, parent, cfg, size), mChordSlop(50.0f), mChordGemInProgress(-1), mChordSlotsInProgress(0), mChordLastSlot(0) {

}

JoypadTrackWatcherImpl::~JoypadTrackWatcherImpl(){

}

// fn_804672B8 - swing
bool JoypadTrackWatcherImpl::Swing(int i1, bool b1, bool b2, GemHitFlags flags){
    KillSustainForSlot(i1);
    float now = mParent->GetNow();
    int idk = ClosestUnplayedGem(now, i1);
    float timeat = mGemList->TimeAt(idk);
    float timeatnext = mGemList->TimeAtNext(idk);
    bool inslopwindow = InSlopWindow(timeat, now);
    GameGem& gem = mGemList->GetGem(idk);
    GameGem& gem2 = mGemList->GetGem(idk);
    int tick = gem2.mTick;
    if(gem.NumSlots() == 1){
        NoteSwing(1 << i1, tick);
    }
    else {
        NoteSwing(mChordSlotsInProgress | 1 << i1, tick);
    }

    bool somebool = false;
    if(AllowAllInputInRolls()){
        int tick = mSongData->GetTempoMap()->TimeToTick(now + mSyncOffset);
        int locInt = 0;
        int loopTick = mSongData->GetTempoMap()->GetLoopTick(tick, locInt);
        if(mSongData->GetRollingSlotsAtTick(mTrack, loopTick)){
            unsigned int roll1;
            int roll2;
            mSongData->GetNextRoll(mTrack, loopTick, roll1, roll2);
            float rollInterval = GetRollIntervalMs(mRollIntervalsConfig, mSongData->mTrackInfos[mTrack]->mType, mSongData->mTrackDifficulties[mTrack], false);
        }
        mSongData->TrackTypeAt(0);
    }

    if(mChordGemInProgress != -1){
        if(mChordGemInProgress == idk){
            TryToCompleteChord(now, i1);
            return false;
        }
        OnMiss(now, mChordLastSlot, idk, 0, kGemHitFlagNone);
        ResetChordInProgress();
    }
    if(!inslopwindow){
        if(!somebool){
            OnMiss(now, i1, idk, 0, kGemHitFlagNone);
        }
    }
    else if(!gem2.GetPlayed() || !Playable(idk)){
        OnMiss(now, mChordLastSlot, idk, 0, kGemHitFlagNone);
    }
    else {

    }
    return true;
}

bool JoypadTrackWatcherImpl::AllowAllInputInRolls() const { return false; }

void JoypadTrackWatcherImpl::TryToCompleteChord(float f, int i){
    GameGem& gem = mGemList->GetGem(mChordGemInProgress);
    int slots = gem.mSlots;
    if(1 << i & slots){
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
void JoypadTrackWatcherImpl::JumpHook(float f){ ResetChordInProgress(); }
void JoypadTrackWatcherImpl::PollHook(float f){ CheckForChordTimeout(f); }

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