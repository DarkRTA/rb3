#include "beatmatch/TrackWatcherImpl.h"
#include "beatmatch/TrackWatcherParent.h"
#include "os/UserMgr.h"
#include "math/Rand.h"

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
    gem.mTick = 0;
    gem.mNoStrum = -1;
    gem.mPlayers = 0;
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