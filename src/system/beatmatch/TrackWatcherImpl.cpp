#include "beatmatch/TrackWatcherImpl.h"
#include "beatmatch/TrackWatcherParent.h"
#include "os/UserMgr.h"
#include "math/Rand.h"
#include "beatmatch/SongData.h"
#include "utl/TempoMap.h"
#include "math/MathFuncs.h"

TrackWatcherImpl::TrackWatcherImpl(int track, const UserGuid& u, int slot, SongData* data, GameGemList* gemlist, TrackWatcherParent* parent, DataArray* cfg, int gemsize) :
    mTrack(track), mUserGuid(u), mPlayerSlot(slot), mGemList(gemlist), mParent(parent), mSlop(100.0f), mLastGemHit(-1), mIsCurrentTrack(false), mGemsInProgress(),
    mSyncOffset(0.0f), mSucceeding(false), mEnabled(true), mSinks(), mSongData(data), mTrillSucceeding(false), mTrillNextSlot(-1), mTrillLastFretMs(0.0f), mTrillIntervalMs(500.0f),
    mRollIntervalsConfig(0), mLastGemPassed(-1), mLastGemSeen(-1), mLastMiss(-10000.0f), mCheating(false), mAutoplayCoda(true), mCheatError(0), mLastCheatCodaSwing(0.0f),
    mNextGemToAutoplay(0), mAutoplayAccuracy(1.0f), mLastPlayedHitFlags(kGemHitFlagNone), mPitchBendReady(true), mPitchBendRange(1), mPitchBendMsToFull(1000), mPitchBendMsHit(0.0f),
    mBiggestWhammy(-1.0f), mRollSlotsLastSwingMs(), mRollActiveSlots(0), mRollIntervalMs(0.0f), mRollEndTick(0), mTrillIntervalsConfig(0) {
    // code
    mIsLocalUser = TheUserMgr->GetUser(mUserGuid, true)->IsLocal();
    if(cfg){
        cfg->FindData("cheat_error", mCheatError, false);
        cfg->FindData("slop", mSlop, false);
        cfg->FindData("pitch_bend_range", mPitchBendRange, false);
        cfg->FindData("ms_to_full_pitch_bend", mPitchBendMsToFull, false);
        cfg->FindData("cymbal_autoplay_ms", mCymbalAutoplayMs, false);
        mRollIntervalsConfig = cfg->FindArray("roll_interval_ms", true);
        mTrillIntervalsConfig = cfg->FindArray("trill_interval_ms", true)->Array(1);
        DataArray* autoplayArr = cfg->FindArray("autoplay_accuracy", false);
        if(autoplayArr){
            mAutoplayAccuracy = autoplayArr->Float(1) / 100.0f;
        }
    }
    if(mParent->GetMaxSlots() < mRollSlotsLastSwingMs.size()){
        mRollSlotsLastSwingMs.push_back(0.0f);
    }
    MILO_ASSERT(mPitchBendMsToFull > 0, 0x66);
    mNextCheatError = (mCheatError == 0) ? 0 : RandomInt(-mCheatError, mCheatError);
    GemInProgress gem;
    gem.mInUse = 0;
    gem.mGemID = -1;
    gem.unk8 = 0.0f;
    if(gemsize < mGemsInProgress.size()){
        mGemsInProgress.push_back(gem);
    }
    EndAllSustainedNotes();
}

TrackWatcherImpl::~TrackWatcherImpl(){
    EndAllSustainedNotes();
}

void TrackWatcherImpl::Init(){
    HandleDifficultyChange();
}

void TrackWatcherImpl::RecalcGemList(){
    mGemList = mSongData->GetGemList(mTrack);
    HandleDifficultyChange();
}

void TrackWatcherImpl::HandleDifficultyChange(){
    EndAllSustainedNotes();
    MILO_ASSERT(mSongData, 0x84);
    // accesses one of SongData's vectors
    MILO_ASSERT(mTrillIntervalsConfig, 0x87);
}

void TrackWatcherImpl::LoadState(TrackWatcherState& state){
    mLastGemHit = state.mLastGemHit;
    mAutoplayCoda = state.mAutoplayCoda;
    mIsCurrentTrack = state.mIsCurrentTrack;
    mGemsInProgress = state.mGemsInProgress;
    mSyncOffset = state.mSyncOffset;
    mTrack = state.mTrack;
    mEnabled = state.mEnabled;
    mLastGemPassed = state.mLastGemPassed;
    mLastGemSeen = state.mLastGemSeen;
    mLastMiss = state.mLastMiss;
    mCheating = state.mCheating;
    mCheatError = state.mCheatError;
    mNextCheatError = state.mNextCheatError;
    mNextGemToAutoplay = state.mNextGemToAutoplay;
    mPitchBendReady = state.mPitchBendReady;
    mPitchBendRange = state.mPitchBendRange;
    mPitchBendMsToFull = state.mPitchBendMsToFull;
    mPitchBendMsHit = state.mPitchBendMsHit;
    mBiggestWhammy = state.mBiggestWhammy;
    mCymbalAutoplayMs = state.mCymbalAutoplayMs;
    mSucceeding = state.mSucceeding;
}

void TrackWatcherImpl::SaveState(TrackWatcherState& state){
    state.mLastGemHit = mLastGemHit;
    state.mAutoplayCoda = mAutoplayCoda;
    state.mIsCurrentTrack = mIsCurrentTrack;
    state.mGemsInProgress = mGemsInProgress;
    state.mSyncOffset = mSyncOffset;
    state.mTrack = mTrack;
    state.mEnabled = mEnabled;
    state.mLastGemPassed = mLastGemPassed;
    state.mLastGemSeen = mLastGemSeen;
    state.mLastMiss = mLastMiss;
    state.mCheating = mCheating;
    state.mCheatError = mCheatError;
    state.mNextCheatError = mNextCheatError;
    state.mNextGemToAutoplay = mNextGemToAutoplay;
    state.mPitchBendReady = mPitchBendReady;
    state.mPitchBendRange = mPitchBendRange;
    state.mPitchBendMsToFull = mPitchBendMsToFull;
    state.mPitchBendMsHit = mPitchBendMsHit;
    state.mBiggestWhammy = mBiggestWhammy;
    state.mCymbalAutoplayMs = mCymbalAutoplayMs;
    state.mSucceeding = mSucceeding;
}

void TrackWatcherImpl::AddSink(BeatMatchSink* sink){
    mSinks.push_back(sink);
}

void TrackWatcherImpl::SetIsCurrentTrack(bool b){ mIsCurrentTrack = b; }

void TrackWatcherImpl::Poll(float time){
    if(mIsCurrentTrack){
        int tick = mSongData->GetTempoMap()->TimeToTick(time);
        CheckForSustainedNoteTimeout(time);
        CheckForRolls(time, tick);
        CheckForTrillTimeout(time);
        CheckForAutoplay(time);
        CheckForPasses(time);
        CheckForGemsSeen(time);
        CheckForPitchBend(time);
        CheckForCodaLanes(tick);
        PollHook(time);
    }
}

void TrackWatcherImpl::PollHook(float){}

void TrackWatcherImpl::Jump(float f){
    SetAllGemsUnplayed();
    EndAllSustainedNotes();
    int marker = mGemList->ClosestMarkerIdxAtOrAfter(f + mSyncOffset);
    if(marker == -1) marker = mGemList->mGems.size();
    mLastGemPassed = marker - 1;
    mLastGemHit = -1;
    mLastGemSeen = marker - 1;
    mLastMiss = -10000.0f;
    mNextGemToAutoplay = marker;
    mLastCheatCodaSwing = 0.0f;
    // vector stuff
    mRollActiveSlots = 0;
    mRollIntervalMs = 0.0f;
    mRollEndTick = 0;
    mTrillLastFretMs = 0.0f;
    JumpHook(f);
}

void TrackWatcherImpl::JumpHook(float){}
void TrackWatcherImpl::Restart(){}
void TrackWatcherImpl::Enable(bool b){ mEnabled = b; }
bool TrackWatcherImpl::IsCheating() const { return mCheating; }
void TrackWatcherImpl::SetCheating(bool b){ mCheating = b; }
void TrackWatcherImpl::SetAutoplayError(int i){ mCheatError = i; }
void TrackWatcherImpl::SetAutoplayCoda(bool b){ mAutoplayCoda = b; }

float TrackWatcherImpl::CycleAutoplayAccuracy(){
    mAutoplayAccuracy -= 0.1f;
    if(mAutoplayAccuracy < 0.01f) mAutoplayAccuracy = 1.0f;
    return mAutoplayAccuracy;
}

void TrackWatcherImpl::SetAutoplayAccuracy(float f){
    mAutoplayAccuracy = Clamp(0.0f, 1.0f, f);
}

void TrackWatcherImpl::SetSyncOffset(float f){ mSyncOffset = f; }

bool TrackWatcherImpl::IsTrillActive() const { return mTrillSucceeding; }

void TrackWatcherImpl::E3CheatIncSlop(){
    mSlop += 10.0f;
    MILO_WARN("Slop = %f ms", mSlop);
}

void TrackWatcherImpl::E3CheatDecSlop(){
    mSlop -= 10.0f;
    if(mSlop < 0.0f) mSlop = 0.0f;
    MILO_WARN("Slop = %f ms", mSlop);
}

bool TrackWatcherImpl::InTrill(int i) const {
    int tick = mSongData->GetTempoMap()->GetLoopTick(i);
    std::pair<int, int> thePair;
    return mSongData->GetTrillSlotsAtTick(mTrack, tick, thePair);
}

bool TrackWatcherImpl::ShouldAutoplayGem(float f, int i){
    GameGem& gem = mGemList->GetGem(i);
    if(!InTrill(gem.mTick)) return false;
    else return mTrillSucceeding;
}

int TrackWatcherImpl::NextGemAfter(int i, bool b){
    int ret = i + 1;
    if(ret < (int)mGemList->mGems.size()) return ret;
    else return -1;
}

int TrackWatcherImpl::ClosestUnplayedGem(float f, int i){
    int idx = mGemList->ClosestMarkerIdxAtOrAfter(f + mSyncOffset);
    GameGem& gem = mGemList->GetGem(idx);
    if(gem.PlayableBy(mPlayerSlot)){
        GameGem& gemgem = mGemList->GetGem(idx);
        if(!gemgem.GetPlayed()) goto oh;
    }
    if(idx + 1 < (int)mGemList->mGems.size()) return idx + 1;
oh:
    return idx;
}

bool TrackWatcherImpl::InSlopWindow(float f1, float f2) const {
    return fabs_f(f2 + mSyncOffset) - f1 <= mSlop;
}

void TrackWatcherImpl::SetGemsPlayedUntil(int thresh){
    for(int x = mLastGemPassed + 1; x < thresh; x++){
        GameGem& gem = mGemList->GetGem(x);
        gem.mPlayed = true;
    }
}

void TrackWatcherImpl::SetAllGemsUnplayed(){ mGemList->Reset(); }

void TrackWatcherImpl::FakeHitGem(float f, int i, GemHitFlags flags){
    GameGem& gem = mGemList->GetGem(i);
    HitGem(f, i, gem.mSlots, flags);
}

GemInProgress* TrackWatcherImpl::GetUnusedGemInProgress(float f){
    for(std::vector<GemInProgress>::iterator iter = mGemsInProgress.begin(); iter != mGemsInProgress.end(); iter++){
        if(!iter->mInUse) return iter;
        if(iter->unk8 < f){
            iter->mInUse = 0;
            iter->mGemID = -1;
            iter->unk8 = 0.0f;
            return iter;
        }
    }
    MILO_FAIL("Couldn't find unused gem in progress!");
    return mGemsInProgress.begin();
}

GemInProgress* TrackWatcherImpl::GetGemInProgressWithSlot(int slot){
    for(std::vector<GemInProgress>::iterator iter = mGemsInProgress.begin(); iter != mGemsInProgress.end(); iter++){
        if(iter->mInUse){
            MILO_ASSERT(iter->mGemID != -1, 0x3FD);
            GameGem& gem = mGemList->GetGem(iter->mGemID);
            if(1 << slot & gem.mSlots) return iter;
        }
    }
    return 0;
}

GemInProgress* TrackWatcherImpl::GetGemInProgressWithID(int id){
    for(std::vector<GemInProgress>::iterator it = mGemsInProgress.begin(); it != mGemsInProgress.end(); it++){
        if(it->mInUse && it->mGemID == id) return it;
    }
    return 0;
}

bool TrackWatcherImpl::HasAnyGemInProgress() const {
    for(std::vector<GemInProgress>::const_iterator it = mGemsInProgress.begin(); it != mGemsInProgress.end(); it++){
        if(it->mInUse) return true;
    }
    return false;
}

bool TrackWatcherImpl::Playable(int i){
    return mGemList->GetGem(i).PlayableBy(mPlayerSlot);
}

void TrackWatcherImpl::EndSustainedNote(GemInProgress& gem){
    mParent->ResetPitchBend(mTrack);
    mPitchBendReady = false;
    gem.mInUse = 0;
    gem.mGemID = -1;
    gem.unk8 = 0.0f;
}

void TrackWatcherImpl::EndAllSustainedNotes(){
    for(std::vector<GemInProgress>::iterator it = mGemsInProgress.begin(); it != mGemsInProgress.end(); it++){
        EndSustainedNote(*it);
    }
}