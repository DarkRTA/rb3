#include "beatmatch/BaseGuitarTrackWatcherImpl.h"
#include "beatmatch/TrackWatcherParent.h"
#include "beatmatch/GameGemList.h"
#include "beatmatch/GameGem.h"
#include "utl/TempoMap.h"
#include "beatmatch/SongData.h"

BaseGuitarTrackWatcherImpl::BaseGuitarTrackWatcherImpl(int track, const UserGuid& u, int slot, SongData* data, GameGemList* gemlist, TrackWatcherParent* parent, DataArray* cfg) :
    TrackWatcherImpl(track, u, slot, data, gemlist, parent, cfg, 2), mLastLateGemHit(-1.0f), mLastNoStrumGemHit(-1), mLastNoStrumGemSwung(-1),
    mMostRecentHit(-1000.0f), mGemNotFretted(-1), mFretWhenStrummed(-1), mFretWaitTimeout(0.0f), mFretSlop(60.0f) {

}

BaseGuitarTrackWatcherImpl::~BaseGuitarTrackWatcherImpl(){

}

void BaseGuitarTrackWatcherImpl::PollHook(float f){
    CheckForFretTimeout(f);
    CheckForHopoTimeout(f);
}

void BaseGuitarTrackWatcherImpl::JumpHook(float f){
    ResetGemNotFretted();
    mLastNoStrumGemHit = -1;
    mLastNoStrumGemSwung = -1;
    mLastLateGemHit = -1.0f;
}

void BaseGuitarTrackWatcherImpl::HandleDifficultyChange(){
    TrackWatcherImpl::HandleDifficultyChange();
}

bool BaseGuitarTrackWatcherImpl::Swing(int, bool, bool, GemHitFlags){
    MILO_ASSERT(mParent, 0x47);
    MILO_ASSERT(mGemList, 0x48);
}

void BaseGuitarTrackWatcherImpl::NonStrumSwing(int i, bool b1, bool b2){
    float now = mParent->GetNow();
    int uu = ClosestUnplayedGem(now, i);
    GameGem* gem = mGemList->GetGem(uu);
    int tick = gem->mTick;
    unsigned int btns = GetFretButtonsDown();
    CheckForTrills(now, tick, btns);
    if(!IsTrillActive()) TryToHopo(now, i, b1, b2);
}

void BaseGuitarTrackWatcherImpl::FretButtonDown(int i){
    RecordFretButtonDown(i);
    float now = mParent->GetNow();
    int gem = SustainedGemToKill(i);
    if(gem != -1 && IsCoreGuitar()){
        KillSustain(gem);
    }
    TryToFinishSwing(mParent->GetNow(), i);
}

void BaseGuitarTrackWatcherImpl::FretButtonUp(int i){
    RecordFretButtonUp(i);
    GemInProgress* gem = GetGemInProgressWithSlot(i);
    if(gem){
        int id = gem->mGemID;
        if(!FretMatch(id, false, true)) KillSustain(id);
    }
    TryToFinishSwing(mParent->GetNow(), -1);
}

void BaseGuitarTrackWatcherImpl::AutoCaptureHook(){
    ResetGemNotFretted();
}

float BaseGuitarTrackWatcherImpl::HitGemHook(float f, int i, GemHitFlags flags){
    if(flags & kGemHitFlagHopo){
        SetLastNoStrumGem(f, i);
    }
    mMostRecentHit = f;
    ResetGemNotFretted();
}

bool BaseGuitarTrackWatcherImpl::GemCanBePassed(int i){ return i != mGemNotFretted; }

float BaseGuitarTrackWatcherImpl::Slop(int i){
    float theSlop;
    if(CanHopo(i)){
        theSlop = mSlop + mFretSlop;
    }
    else theSlop = mSlop;
    return theSlop - mSyncOffset;
}

void BaseGuitarTrackWatcherImpl::ResetGemNotFretted(){
    mGemNotFretted = -1;
    mFretWhenStrummed = -1;
    mFretWaitTimeout = 0.0f;
    mHarmlessSwing = false;
}

void BaseGuitarTrackWatcherImpl::TryToFinishSwing(float f, int i){
    if(mEnabled && mGemNotFretted != -1 && f < mFretWaitTimeout){
        GameGem* gem = mGemList->GetGem(mGemNotFretted);
        MILO_ASSERT(!gem->unk10b7, 0x142); // fix this member name
        if(FretMatch(mGemNotFretted, false, false)){
            OnHit(f, i, mGemNotFretted, gem->mSlots, kGemHitFlagNone);
            if(gem->unk10b6){
                SendSwingAtHopo(f, mGemNotFretted);
            }
            mLastLateGemHit = f;
        }
        else {
            if(!IsChordSubset(mGemNotFretted) && IsCoreGuitar()){
                unsigned int btns = GetFretButtonsDown();
                OnMiss(f, mFretWhenStrummed, mGemNotFretted, btns, kGemHitFlagNone);
                ResetGemNotFretted();
            }
        }
    }
}

int BaseGuitarTrackWatcherImpl::SustainedGemToKill(int i){
    for(std::vector<GemInProgress>::iterator it = mGemsInProgress.begin(); it != mGemsInProgress.end(); it++){
        if(it->mInUse){
            int id = it->mGemID;
            if(!FretMatch(id, false, true)) return id;
        }
    }
    return -1;
}

void BaseGuitarTrackWatcherImpl::TryToHopo(float f, int i, bool b1, bool b2){
    MILO_ASSERT(mGemList, 0x17B);
    if(f != mMostRecentHit){
        int closestgem = ClosestUnplayedGem(f, i);
        GameGem* gem = mGemList->GetGem(closestgem);
        if(CanHopo(closestgem)){
            float timeat = mGemList->TimeAt(closestgem);
            float timeatnext = mGemList->TimeAtNext(closestgem);
            float f2 = mSlop;
            float f1 = f + mSyncOffset - timeat;
            if((-f2 <= f1) && (f1 - mFretSlop <= f2) && (!gem->unk10b7) && Playable(closestgem) && (closestgem != mLastNoStrumGemSwung)){
                if(FretMatch(closestgem, true, false)){
                    int flags = mBaseGuitarFlags | kGemHitFlagHopo;
                    if(b2) flags = flags | kGemHitFlagSolo;
                    OnHit(f, i, closestgem, gem->mSlots, (GemHitFlags)flags);
                }
                else {
                    int tick = mSongData->GetTempoMap()->TimeToTick(f);
                    if(mParent->InFill(tick, true)){
                        FillSwing(tick, i, -1, false);
                    }
                    else {
                        if(b1 && IsHighestFret(i) && !InGem(i, *gem) && IsCoreGuitar()){
                            mLastNoStrumGemSwung = closestgem;
                        }
                    }
                }
            }
        }
    }
}