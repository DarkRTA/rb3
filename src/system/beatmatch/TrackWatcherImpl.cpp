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
    gem.unk0 = 0;
    gem.unk4 = -1;
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

float TrackWatcherImpl::PollHook(float){}

float TrackWatcherImpl::JumpHook(float){}
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