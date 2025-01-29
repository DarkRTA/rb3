#include "beatmatch/RealGuitarTrackWatcherImpl.h"
#include "beatmatch/RGChords.h"
#include "beatmatch/RGState.h"
#include "beatmatch/SongData.h"
#include "beatmatch/Output.h"
#include "beatmatch/TrackWatcherParent.h"

RealGuitarTrackWatcherImpl::RealGuitarTrackWatcherImpl(int track, const UserGuid& u, int slot, SongData* data, GameGemList* gemlist, TrackWatcherParent* parent, DataArray* cfg) :
    BaseGuitarTrackWatcherImpl(track, u, slot, data, gemlist, parent, cfg), unk1f0(0), mMissWindowMs(0), mIs22Fret(0) {
    mSlop = 125.0f;
    mFretSlop = 100.0f;
    if(cfg) cfg->FindData("real_guitar_miss_window_ms", mMissWindowMs, false);
    mIs22Fret = data->TrackTypeAt(track) == kTrackRealGuitar22Fret || data->TrackTypeAt(track) == kTrackRealBass22Fret;
}

RealGuitarTrackWatcherImpl::~RealGuitarTrackWatcherImpl(){

}

void RealGuitarTrackWatcherImpl::JumpHook(float f){
    BaseGuitarTrackWatcherImpl::JumpHook(f);
    unk1f0 = 0;
}

void RealGuitarTrackWatcherImpl::PollHook(float f){
    BaseGuitarTrackWatcherImpl::PollHook(f);
    if(!IsCheating()){
        bool b2 = false;
        for(std::vector<GemInProgress>::iterator it = mGemsInProgress.begin(); !b2 && it != mGemsInProgress.end(); ++it){
            if(it->mInUse){
                GameGem& curGem = mGemList->GetGem(it->mGemID);
                float curGemMs = curGem.mMs;
                if(!InSlopWindow(curGemMs, mParent->GetNow())){
                    float curGemMs2 = curGem.mMs;
                    if(!mMatcher.FretMatch(curGem, mSlop, curGemMs2, mSyncOffset, mParent->GetNow(), false, true, (RGMatchType)0)){
                        KillSustain(it->mGemID);
                        b2 = true;
                    }
                }
            }
        }
    }
}

bool RealGuitarTrackWatcherImpl::Swing(int i1, bool b2, bool b3, GemHitFlags flags){
    bool ret = false;
    mMatcher.Swing(i1, mParent->GetNow());
    int tick = mSongData->GetTempoMap()->TimeToTick(mSyncOffset + mParent->GetNow());
    if(mParent->InCodaFreestyle(tick, true)){
        for(int i = 0; i < 6; i++){
            if(i1 & (1 << i)){
                CodaSwing(tick, i);
            }
        }
    }
    else {
        ret = BaseGuitarTrackWatcherImpl::Swing(i1, b2, b3, flags);
        float now = mParent->GetNow();
        int idx = mGemList->ClosestMarkerIdx(now + mSyncOffset);
        float timeAt = mGemList->TimeAt(idx);
        if(!InSlopWindow(timeAt, now)){
            if(StrumOK(idx)) return false;
            GemHitFlags u7 = kGemHitFlagNone;
            if(now - unk1f0 < mMissWindowMs) u7 = (GemHitFlags)(u7|kGemHitFlagNoPenalize);
            else unk1f0 = now;
            for(int i = 0; i < 6; i++){
                if(i1 & (1 << i)){
                    OnMiss(now, i, idx, i1, u7);
                }
            }
            if(TheBeatMatchOutput.IsActive()){
                TheBeatMatchOutput.Print(MakeString("(%2d%10.1f MISS\t%d)\n", 0, timeAt, idx));
            }
        }
    }
    NoteSwing(i1, tick);
    return ret;
}

void RealGuitarTrackWatcherImpl::NonStrumSwing(int i1, bool b2, bool b3){
    float now = mParent->GetNow();
    GameGem& gem = mGemList->GetGem(ClosestUnplayedGem(now, i1));
    CheckForTrills(now, gem.GetTick(), i1);
    if(!IsTrillActive()){
        TryToHopo(now, i1, b2, b3);
    }
}

void RealGuitarTrackWatcherImpl::FretButtonUp(int i){
    mMatcher.FretUp(i, mParent->GetNow());
    BaseGuitarTrackWatcherImpl::TryToFinishSwing(mParent->GetNow(), -1);
}

void RealGuitarTrackWatcherImpl::RGFretButtonDown(int i){
    RecordFretButtonDown(i);
}

void RealGuitarTrackWatcherImpl::RecordFretButtonDown(int i){
    mMatcher.FretDown(i, mParent->GetNow());
}

void RealGuitarTrackWatcherImpl::RecordFretButtonUp(int i){
    mMatcher.FretUp(i, mParent->GetNow());
}

unsigned int RealGuitarTrackWatcherImpl::GetFretButtonsDown() const {
    unsigned int ret = 0;
    for(int i = 0; i < 6; i++){
        if((int)mMatcher.GetState()->GetFret(i) != -1){
            ret |= (1 << i);
        }
    }
    return ret;
}

bool RealGuitarTrackWatcherImpl::HandleHitsAndMisses(int i1, int i2, float f3, bool b4, bool b5, bool b6, GemHitFlags flags){
    GameGem& gem = mGemList->GetGem(i1);
    if(gem.GetPlayed()) return true;
    else {
        if(FretMatch(i1, false, false)){
            if(!b4) flags = (GemHitFlags)(flags|kGemHitFlagSolo);
            OnHit(f3, i2, i1, gem.GetSlots(), flags);
            ResetGemNotFretted();
            return true;
        }
        else {
            if(mGemNotFretted == -1){
                if(StrumOK(i1)) return false;
                mGemNotFretted = i1;
                mFretWaitTimeout = f3 + mFretSlop;
            }
            return false;
        }
    }
}

bool RealGuitarTrackWatcherImpl::StrumOK(int i) const {
    if(i == 0) return false;
    else {
        GameGem& thisGem = mGemList->GetGem(i);
        GameGem& prevGem = mGemList->GetGem(i - 1);
        float prevMs = prevGem.mMs;
        float prevAbs = Abs<float>(prevMs - (mSyncOffset + mParent->GetNow()));
        float thisMs = thisGem.mMs;
        float thisAbs = Abs<float>(thisMs - (mSyncOffset + mParent->GetNow()));
        if(prevAbs < mSlop || thisAbs < mSlop) return true;
        else return false;
    }
}

bool RealGuitarTrackWatcherImpl::FretMatch(int i1, bool b2, bool b3) const {
    GameGem& gem = mGemList->GetGem(i1);
    return mMatcher.FretMatch(gem, mSlop, mGemList->TimeAt(i1), mSyncOffset, mParent->GetNow(), b2, b3, (RGMatchType)1);
}

bool RealGuitarTrackWatcherImpl::IsChordSubset(int) const { return true; }
bool RealGuitarTrackWatcherImpl::HarmlessFretDown(int, int) const { return true; }
bool RealGuitarTrackWatcherImpl::IsCoreGuitar() const { return false; }

bool RealGuitarTrackWatcherImpl::IsHighestFret(int i) const {
    int x, y;
    UnpackRGData(i, x, y);
    return mMatcher.GetState()->GetFret(x) == y;
}

bool RealGuitarTrackWatcherImpl::InGem(int i, const GameGem& gem) const {
    int x, y;
    UnpackRGData(i, x, y);
    return gem.GetFret(x) == y;
}

bool RealGuitarTrackWatcherImpl::AreSlotsInRoll(unsigned int i1, int i2) const {
    int tick = mSongData->GetTempoMap()->GetLoopTick(i2);
    RGRollChord chord = mSongData->GetRGRollingSlotsAtTick(Track(), tick);
    const RGState* state = mMatcher.GetState();
    unsigned int mask = 1;
    bool ret = false;
    for(int i = 0; i < 6; i++, mask <<= 1){
        if((i1 & mask) && chord.unk0[i] != -1){
            if(chord.unk0[i] != (int)state->GetFret(i)){
                return false;
            }
            ret = true;
        }
    }
    return ret;
}

bool RealGuitarTrackWatcherImpl::IsSwingInRoll(int, unsigned int){ return false; }

bool RealGuitarTrackWatcherImpl::GetNextRoll(int i1, unsigned int& uiRef, int& endTick) const {
    int tick = mSongData->GetTempoMap()->GetLoopTick(i1);
    RGRollChord chord;
    if(mSongData->GetNextRGRoll(Track(), tick, chord, endTick)){
        uiRef = 0;
        for(int i = 0; i < 6; i++){
            if(chord.unk0[i] != -1){
                uiRef |= 1 << i;
            }
        }
        return true;
    }
    else return false;
}

void RealGuitarTrackWatcherImpl::CheckForTrills(float fff, int iii, unsigned int ui){
    RGTrill trill;
    int track = Track();
    int tick = mSongData->GetTempoMap()->GetLoopTick(iii);
    int x, y;
    if(mSongData->GetRGTrillAtTick(track, tick, trill)){
        UnpackRGData(ui, x, y);
        if(fff - mTrillLastFretMs < mTrillIntervalMs){
            if(y == mTrillNextSlot){
                mTrillNextSlot = GetNextTrillSlot(y, trill);
                mTrillSucceeding = true;
            }
            else mTrillSucceeding = false;
        }
        else {
            
            mTrillNextSlot = GetNextTrillSlot(y, trill);
            mTrillSucceeding = false;
        }
        mTrillLastFretMs = fff;
    }
}

bool RealGuitarTrackWatcherImpl::InTrill(int i) const {
    RGTrill trill;
    int track = Track();
    int tick = mSongData->GetTempoMap()->GetLoopTick(i);
    return mSongData->GetRGTrillAtTick(track, tick, trill);
}