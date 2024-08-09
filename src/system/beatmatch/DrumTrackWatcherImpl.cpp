#include "beatmatch/DrumTrackWatcherImpl.h"
#include "beatmatch/SongData.h"
#include "beatmatch/TrackWatcherParent.h"

DrumTrackWatcherImpl::DrumTrackWatcherImpl(int track, const UserGuid& u, int slot, SongData* song_data, GameGemList* gemlist, TrackWatcherParent* parent, DataArray* cfg) : 
    TrackWatcherImpl(track, u, slot, song_data, gemlist, parent, cfg, 2), mNextKickGemToAutoplay(0), mGameCymbalLanes(0) {
    MILO_ASSERT(song_data, 0x25);
    mGameCymbalLanes = song_data->GetGameCymbalLanes();
}

DrumTrackWatcherImpl::~DrumTrackWatcherImpl(){

}

void DrumTrackWatcherImpl::Restart(){
    MILO_ASSERT(mSongData, 0x2F);
    mGameCymbalLanes = mSongData->GetGameCymbalLanes();
}

// fn_8045ED64 - relevantgem
int DrumTrackWatcherImpl::RelevantGem(int i1, int i2, int i3){
    int count = 0;
    int closest_gem = i1;
    for(; closest_gem < i2; closest_gem++){
        GameGem& gem = mGemList->GetGem(closest_gem);
        int slot = gem.GetSlot();
        if(i3 == slot) return closest_gem;
        if(!gem.GetPlayed()) count++;
    }
    closest_gem = -1;
    count = 999;
    for(; i1 <= i2; i1++){
        GameGem& gem = mGemList->GetGem(i1);
        if(count != 0 || !gem.GetPlayed()){
            int absval = abs(i3 - gem.GetSlot());
            if(absval < count){
                closest_gem = i1;
                count = absval;
            }
        }
    }
    MILO_ASSERT(closest_gem != -1, 0x59);
    return closest_gem;
}

// fn_8045EE58 - swing
bool DrumTrackWatcherImpl::Swing(int slot, bool b1, bool b2, GemHitFlags flags){
    KillSustainForSlot(slot);
    float now = mParent->GetNow();
    int idx = mGemList->ClosestMarkerIdx(now + mSyncOffset);
    float timeat = mGemList->TimeAt(idx);
    float timeatplus20 = timeat + 20.0f;
    int i3 = idx;
    for(; mGemList->NumGems() >= i3 + 1 || timeatplus20 <= mGemList->TimeAt(i3 + 1); i3++);
    float timeatminus20 = timeat - 20.0f;
    for(; idx >= 0; idx--){
        if(mGemList->TimeAt(idx - 1) >= timeatminus20) break;
    }
    int relevant = RelevantGem(idx, i3, slot);
    bool inslop = InSlopWindow(mGemList->TimeAt(relevant), now);
    unsigned int mask = 1 << slot;
    NoteSwing(mask, mGemList->GetGem(relevant).GetTick());
    if(inslop){
        GameGem& gem = mGemList->GetGem(relevant);
        if(!gem.GetPlayed() || Playable(relevant)){
            MILO_ASSERT(gem.NumSlots() == 1, 0x8D);
            if(slot == gem.GetSlot()){
                if(CheckCymbal(gem, flags)) OnHit(now, slot, relevant, gem.GetSlots(), flags);
                else OnMiss(now, slot, relevant, mask, kGemHitFlagNone);
            }
            else {
                if(b2) return false;
                OnMiss(now, slot, relevant, mask, kGemHitFlagNone);
            }
        }
        else {
            if(b2) return false;
            OnMiss(now, slot, relevant, mask, kGemHitFlagNone);
        }
    }
    else {
        if(b2) return false;
        OnMiss(now, slot, relevant, mask, kGemHitFlagNone);
    }
    return true;
}

void DrumTrackWatcherImpl::PollHook(float f){
    CheckForKickAutoplay(f);
}

void DrumTrackWatcherImpl::JumpHook(float f){
    int idx = mGemList->ClosestMarkerIdxAtOrAfter(f + mSyncOffset);
    if(idx == -1) idx = mGemList->NumGems();
    mNextKickGemToAutoplay = idx;
}