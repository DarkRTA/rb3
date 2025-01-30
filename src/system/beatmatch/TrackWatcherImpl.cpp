#include "beatmatch/TrackWatcherImpl.h"
#include "beatmatch/BeatMatchSink.h"
#include "beatmatch/BeatMatchUtl.h"
#include "beatmatch/FillInfo.h"
#include "beatmatch/GameGem.h"
#include "beatmatch/Output.h"
#include "beatmatch/TrackType.h"
#include "beatmatch/TrackWatcherParent.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "os/UserMgr.h"
#include "math/Rand.h"
#include "beatmatch/SongData.h"
#include "utl/MakeString.h"
#include "utl/TempoMap.h"
#include "math/Utl.h"

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
    mRollSlotsLastSwingMs.resize(mParent->GetMaxSlots());
    MILO_ASSERT(mPitchBendMsToFull > 0, 0x66);
    mNextCheatError = (mCheatError == 0) ? 0 : RandomInt(-mCheatError, mCheatError);
    mGemsInProgress.resize(gemsize);
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
    int diff = mSongData->TrackDiffAt(Track());
    MILO_ASSERT(mTrillIntervalsConfig, 0x87);
    mTrillIntervalMs = mTrillIntervalsConfig->Float(diff);
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
    if(marker == -1) marker = mGemList->NumGems();
    mLastGemPassed = marker - 1;
    mLastGemHit = -1;
    mLastGemSeen = marker - 1;
    mLastMiss = -10000.0f;
    mNextGemToAutoplay = marker;
    mLastCheatCodaSwing = 0.0f;
    mRollSlotsLastSwingMs.clear();
    mRollSlotsLastSwingMs.resize(mParent->GetMaxSlots());
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

void TrackWatcherImpl::NoteSwing(unsigned int ui, int x){
    float f6 = mParent->GetNow();
    unsigned int ui5 = 1;
    for(int i = 0; ui != 0; ui &= ~ui5, ui5 <<= 1, i++){
        if(ui & ui5){
            if(AreSlotsInRoll(ui5, x)){
                if(f6 < mRollIntervalMs + mRollSlotsLastSwingMs[i]){
                    mRollActiveSlots |= ui5;
                }
                else mRollActiveSlots &= ~ui5;
                mRollSlotsLastSwingMs[i] = f6;
            }
            else mRollActiveSlots &= ~ui5;
        }
    }
}

bool TrackWatcherImpl::IsSwingInRoll(int id, unsigned int ui){
    GameGem& gem = mGemList->GetGem(id);
    int tick = gem.GetTick();
    unsigned int slots = gem.GetSlots();
    if(!AreSlotsInRoll(slots, tick)) return false;
    else return (slots == (slots & mRollActiveSlots)) && ((ui & mRollActiveSlots) == ui);
}

bool TrackWatcherImpl::AreSlotsInRoll(unsigned int ui, int i) const {
    return (ui & mSongData->GetRollingSlotsAtTick(mTrack, mSongData->GetTempoMap()->GetLoopTick(i))) == ui;
}

void TrackWatcherImpl::CheckForTrills(float f, int i, unsigned int ui){
    int tick = mSongData->GetTempoMap()->GetLoopTick(i);
    std::pair<int, int> pair;
    if(mSongData->GetTrillSlotsAtTick(Track(), tick, pair)){
        int slot = GameGem::GetHighestSlot(ui);
        if(f - mTrillLastFretMs < mTrillIntervalMs){
            if(slot == mTrillNextSlot){
                mTrillNextSlot = GetOtherTrillSlot(slot, pair);
                mTrillSucceeding = true;
            }
            else mTrillSucceeding = false;
        }
        else {
            mTrillNextSlot = GetOtherTrillSlot(slot, pair);
            mTrillSucceeding = false;
        }
        mTrillLastFretMs = f;
    }
}

int TrackWatcherImpl::GetOtherTrillSlot(int x, const std::pair<int, int>& p) const {
    return x == p.first ? p.second : p.first;
}

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
    return mSongData->GetTrillSlotsAtTick(Track(), tick, thePair);
}

bool TrackWatcherImpl::ShouldAutoplayGem(float f, int i){
    GameGem& gem = mGemList->GetGem(i);
    return !InTrill(gem.GetTick()) ? false : mTrillSucceeding;
}

int TrackWatcherImpl::NextGemAfter(int i, bool b){
    int numGems = mGemList->NumGems();
    int ret = -1;
    if(i + 1 < numGems){
        ret = i + 1;
    }
    return ret;
}

int TrackWatcherImpl::ClosestUnplayedGem(float f, int i){
    int idx = mGemList->ClosestMarkerIdx(f + mSyncOffset);
    if(Playable(idx)){
        GameGem& gemgem = mGemList->GetGem(idx);
        if(!gemgem.GetPlayed()) goto oh;
    }
    if(idx + 1 < mGemList->NumGems()) return idx + 1;
oh:
    return idx;
}

bool TrackWatcherImpl::InSlopWindow(float f1, float f2) const {
    return std::fabs(f2 + mSyncOffset - f1) <= mSlop;
}

void TrackWatcherImpl::SetGemsPlayedUntil(int thresh){
    for(int x = mLastGemPassed + 1; x < thresh; x++){
        GameGem& gem = mGemList->GetGem(x);
        gem.SetPlayed(true);
    }
}

void TrackWatcherImpl::SetAllGemsUnplayed(){ mGemList->Reset(); }

void TrackWatcherImpl::FakeHitGem(float f, int i, GemHitFlags flags){
    GameGem& gem = mGemList->GetGem(i);
    HitGem(f, i, gem.GetSlots(), flags);
}

void TrackWatcherImpl::HitGem(float ms, int gemID, unsigned int slots, GemHitFlags flags){
    GameGem& gem = mGemList->GetGem(gemID);
    gem.SetPlayed(true);
    SendHit(ms, gemID, slots, flags);
    mLastGemHit = gemID;
    if(mCheating){
        mNextCheatError = mCheatError == 0 ? 0 : RandomInt(-mCheatError, mCheatError);
    }
    GemInProgress* gemInProgress = GetGemInProgressWithID(gemID);
    if(gemInProgress){
        EndSustainedNote(*gemInProgress);
    }
    if(!gem.IgnoreDuration()){
        GemInProgress* unused = GetUnusedGemInProgress(gem.mMs);
        unused->mInUse = true;
        unused->mGemID = gemID;
        unused->unk8 = gem.mMs + gem.DurationMs();
        mPitchBendMsHit = ms;
    }
    HitGemHook(ms, gemID, flags);
    mLastPlayedHitFlags = flags;
}

void TrackWatcherImpl::CheckForPasses(float ms){
    for(int i = mGemList->NumGems(); mLastGemPassed != i - 1; ){
        int i3 = mLastGemPassed + 1;
        if(!GemCanBePassed(i3)) break;
        float f5 = mGemList->TimeAt(i3);
        float f6 = f5 + Slop(i3);
        int next = NextGemAfter(i3, false);
        if(next != -1){
            f6 = Min<float>(f6, (f5 + mGemList->TimeAt(next)) / 2.0f - mSyncOffset);
        }
        if(!Playable(i3)) f6 = f5;
        if(f6 < ms){
            mLastGemPassed++;
            if(!mGemList->GetGem(mLastGemPassed).GetPlayed()){
                if(Playable(mLastGemPassed)){
                    if(mEnabled) OnPass(ms, mLastGemPassed);
                    else SendIgnore(ms, mLastGemPassed);
                }
                else if(mIsCurrentTrack){
                    SendIgnore(ms, mLastGemPassed);
                }
            }
        }
        else break;
    }
}

void TrackWatcherImpl::CheckForSustainedNoteTimeout(float f){
    for(std::vector<GemInProgress>::iterator iter = mGemsInProgress.begin(); iter != mGemsInProgress.end(); ++iter){
        if(iter->mInUse){
            MILO_ASSERT(iter->mGemID != -1, 0x2AC);
            if(iter->unk8 < f){
                EndSustainedNote(*iter);
            }
        }
    }
}

bool TrackWatcherImpl::GetNextRoll(int i, unsigned int& uiref, int& iref) const {
    return mSongData->GetNextRoll(mTrack, mSongData->GetTempoMap()->GetLoopTick(i), uiref, iref);
}

void TrackWatcherImpl::CheckForRolls(float ms, int tick){
    if(mRollEndTick == -1 || tick <= mRollEndTick){
        if(tick == mSongData->GetTempoMap()->GetLoopTick(tick)) goto ok;
    }
    MILO_ASSERT(mSongData, 0x2C5);
    unsigned int ui28;
    if(GetNextRoll(tick, ui28, mRollEndTick)){
        bool bits = GameGem::CountBitsInSlotType(ui28) > 1;
        int diff = mSongData->TrackDiffAt(Track());
        TrackType ty = mSongData->TrackTypeAt(Track());
        MILO_ASSERT(mRollIntervalsConfig, 0x2D0);
        mRollIntervalMs = GetRollIntervalMs(mRollIntervalsConfig, ty, diff, bits);
    }
    else {
        mRollEndTick = -1;
    }
ok:
    if(mRollActiveSlots != 0){
        for(int i = 0; i < mRollSlotsLastSwingMs.size(); i++){
            int mask = 1 << i;
            if((mask & mRollActiveSlots) && (ms > mRollIntervalMs + mRollSlotsLastSwingMs[i])){
                mRollActiveSlots &= ~mask;
            }
        }
    }
}

void TrackWatcherImpl::CheckForTrillTimeout(float ms){
    if(mTrillSucceeding && (ms > mTrillLastFretMs + mTrillIntervalMs)){
        mTrillSucceeding = false;
    }
}

void TrackWatcherImpl::CheckForAutoplay(float ms){
    if(mIsCurrentTrack){
        int tick = mSongData->GetTempoMap()->TimeToTick(ms);
        if(mParent->InCodaFreestyle(tick, true)){
            if(mCheating && mAutoplayCoda && mLastCheatCodaSwing + 80.0f < ms){
                CodaSwing(tick, 0);
                mLastCheatCodaSwing = ms;
            }
        }
        else {
            int i5 = mGemList->NumGems();
            int i4;
            while(i4 = mNextGemToAutoplay, i4 <= i5 - 1){
                if(mNextCheatError + ms + mSyncOffset > mGemList->TimeAt(i4)){
                    mNextGemToAutoplay++;
                    GameGem& gem = mGemList->GetGem(i4);
                    if(!gem.GetPlayed()){
                        unsigned int ui8 = gem.GetSlots();
                        int i2 = mRollActiveSlots;
                        bool autoPlay = ShouldAutoplayGem(ms, i4);
                        if(mCheating || ((ui8 & i2) == ui8) || autoPlay || gem.Unk10B1()){
                            if(mEnabled && Playable(i4)){
                                if(mIsLocalUser && GetFillLogic() == 0){
                                    if(mParent->InFill(mGemList->GetGem(i4).GetTick(), true)) goto ignore;
                                }
                                if(RandomFloat() < mAutoplayAccuracy){
                                    bool b1 = false;
                                    if(gem.GetForceStrum()){
                                        if(DataVariable("auto_hopos").Int()) b1 = true;
                                    }
                                    HitGem(ms, i4, gem.GetSlots(), (GemHitFlags)(mLastPlayedHitFlags | kGemHitFlagAutoplay));
                                    if(b1) SendHopo(ms, i4);
                                }
                            }
                            else {
                            ignore:
                                SendIgnore(ms, i4);
                            }
                        }
                    }
                }
                else return;
            }
        }
    }
}

void TrackWatcherImpl::CheckForGemsSeen(float ms){
    int numGems = mGemList->NumGems();
    while((mLastGemSeen != numGems - 1)){
        int next = mLastGemSeen + 1;
        if(mGemList->TimeAt(next) < ms){
            mLastGemSeen = next;
            if(Playable(next) && !mButtonMashingMode){
                SendSeen(ms, next);
            }
        }
        else break;
    }
}

void TrackWatcherImpl::CheckForPitchBend(float ms){
    float whammy = mParent->GetWhammyBar();
    if(whammy >= -0.34999999f){
        mPitchBendReady = true;
        mBiggestWhammy = Max(mBiggestWhammy, whammy);
    }
    if(HasAnyGemInProgress()){
        if(mPitchBendReady && mBiggestWhammy != -1.0f){
            float f3 = (whammy - mBiggestWhammy) / (mBiggestWhammy + 1.0f);
            SendWhammy(f3);
            float prod = f3 * Clamp<float>(0, 1, (ms - mPitchBendMsHit) / mPitchBendMsToFull);
            mParent->SetPitchBend(mTrack, (float)mPitchBendRange * prod, false);
        }
        else SendWhammy(0);
    }
    else {
        SendWhammy(0);
        mParent->SetPitchBend(mTrack, 0, false);
        mBiggestWhammy = -1.0f;
    }
}

void TrackWatcherImpl::CheckForCodaLanes(int tick){
    bool inCoda = mParent->InCodaFreestyle(tick, true);
    if(inCoda != mButtonMashingMode){
        mButtonMashingMode = inCoda;
        mParent->SetButtonMashingMode(inCoda);
    }
}

int TrackWatcherImpl::SustainedGemToKill(int iii){
    GemInProgress* gem = GetGemInProgressWithSlot(iii);
    if(gem){
        int i4 = gem->mGemID;
        int i1 = 0;
        GameGem& activeGem = mGemList->GetGem(i4);
        unsigned int slots = activeGem.GetSlots();
        for(int i = 8, j = 7; i != 0; i--, j--){
            if(slots & (1 << j)){
                if(j < iii || ++i1 >= 2) return i4;
            }
        }
    }
    return -1;
}

void TrackWatcherImpl::KillSustain(int iii){
    GameGem& gem = mGemList->GetGem(iii);
    if(!gem.LeftHandSlide()){
        float ms = gem.mMs + gem.DurationMs();
        float now = mParent->GetNow();
        SendReleaseGem(now, iii, ms - now);
        GemInProgress* gemInProgress = GetGemInProgressWithID(iii);
        if(gemInProgress) EndSustainedNote(*gemInProgress);
    }
}

void TrackWatcherImpl::KillSustainForSlot(int iii){
    GemInProgress* gemInProgress = GetGemInProgressWithSlot(iii);
    if(gemInProgress) KillSustain(gemInProgress->mGemID);
}

GemInProgress* TrackWatcherImpl::GetUnusedGemInProgress(float f){
    for(std::vector<GemInProgress>::iterator iter = mGemsInProgress.begin(); iter != mGemsInProgress.end(); iter++){
        if(!iter->mInUse) return iter;
        if(iter->unk8 < f){
            iter->Reset();
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
            if(1 << slot & gem.GetSlots()) return iter;
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

#pragma push
#pragma force_active on
inline bool TrackWatcherImpl::Playable(int gemID){
    return mGemList->GetGem(gemID).PlayableBy(mPlayerSlot);
}
#pragma pop

void TrackWatcherImpl::EndSustainedNote(GemInProgress& gem){
    mParent->ResetPitchBend(mTrack);
    mPitchBendReady = false;
    gem.Reset();
}

void TrackWatcherImpl::EndAllSustainedNotes(){
    for(std::vector<GemInProgress>::iterator it = mGemsInProgress.begin(); it != mGemsInProgress.end(); it++){
        EndSustainedNote(*it);
    }
}

void TrackWatcherImpl::MaybeAutoplayFutureCymbal(int gemID){
    GameGem& gem = mGemList->GetGem(gemID);
    float gemMs = gem.mMs + mCymbalAutoplayMs;
    int i3 = gem.GetSlot();
    while(++gemID < mGemList->NumGems()){
        GameGem& curGem = mGemList->GetGem(gemID);
        if(curGem.mMs > gemMs) break;
        if(i3 == curGem.GetSlot()){
            curGem.SetUnk10B1(true);
            return;
        }
    }
}

void TrackWatcherImpl::OnHit(float f1, int i2, int gemID, unsigned int slots, GemHitFlags flags){
    GameGem& gem = mGemList->GetGem(gemID);
    int tick = gem.GetTick();
    int i38 = 0;
    GetFillLogic();
    bool fillCompletion = IsFillCompletion(f1, tick, i38);
    if(gem.Unk10B4()){
        if(!(flags & kGemHitFlagAutoplay) && (flags & kGemHitFlagCymbal)){
            MaybeAutoplayFutureCymbal(gemID);
        }
    }
    if(mParent->InCodaFreestyle(tick, true)){
        CodaSwing(tick, i2);
    }
    else {
        if(i2 == 4 && fillCompletion){
            FillSwing(tick, i2, gemID, true);
            RegisterFill(i38);
        }
        else {
            if(!GetFillLogic() && mParent->InFill(tick, true)){
                FillSwing(tick, i2, gemID, fillCompletion);
            }
            else {
                FillStop();
                HitGem(f1, gemID, slots, flags);
            }
        }
    }
}

bool TrackWatcherImpl::IsFillCompletion(float fff, int iii, int& iref){
    if(!mParent->FillsEnabled(iii)) return false;
    else {
        FillExtent extent(0,0,0);
        int i38 = 0;
        int i1 = mSongData->GetTempoMap()->GetLoopTick(iii, i38);
        if(mSongData->GetFillInfo(mTrack)->FillExtentAtOrBefore(i1, extent)){
            float time = mSongData->GetTempoMap()->TickToTime(extent.end + i38);
            if(InSlopWindow(time, fff)){
                iref = mSongData->GetTempoMap()->TimeToTick(time);
                return true;
            }
        }
    }
    return false;
}

void TrackWatcherImpl::OnMiss(float f1, int i2, int i3, unsigned int ui, GemHitFlags flags){
    int tick = mSongData->GetTempoMap()->TimeToTick(f1 + mSyncOffset);
    int i48 = 0;
    bool noFillLogic = GetFillLogic() == 0;
    GameGem& gem = mGemList->GetGem(i3);
    if(mParent->InCodaFreestyle(tick, true)){
        CodaSwing(tick, i2);
    }
    else if(mParent->InCoda(tick)){
        SendMiss(f1, i2, i3, ui, flags);
    }
    else if(IsFillCompletion(f1, tick, i48)){
        if(i2 == 4){
            FillSwing(tick, i2, -1, true);
            RegisterFill(i48);
        }
        else if(noFillLogic){
            FillSwing(tick, i2, -1, true);
        }
        else {
            SendMiss(f1, i2, i3, ui, flags);
            ResetFill();
        }
    }
    else if(noFillLogic && mParent->InFill(tick, true)) {
        FillSwing(tick, i2, -1, false);
    }
    else if(noFillLogic && mParent->InFill(tick + 120, true)){
        FillSwing(tick + 120, i2, -1, false);
    }
    else if(!IsSwingInRoll(i3, ui) && !IsTrillActive()){
        if(gem.Unk10B1() && gem.GetPlayed() && i2 == gem.GetSlot()){
            gem.SetUnk10B1(false);
        }
        else {
            SendMiss(f1, i2, i3, ui, flags);
            ResetFill();
        }
    }
}

void TrackWatcherImpl::OnPass(float f, int i){
    int tick = mGemList->GetGem(i).GetTick();
    if(mParent->InFill(tick, true)){
        if(!GetFillLogic()){
            SendIgnore(f, i);
            return;
        }
        else {
            int iref;
            if(IsFillCompletion(mSongData->GetTempoMap()->TickToTime(tick), tick, iref)){
                SendImplicit(f, i);
                return;
            }
        }
    }
    SendPass(f, i);
    ResetFill();
}

void TrackWatcherImpl::CodaSwing(int i1, int i2){
    for(std::vector<BeatMatchSink*>::iterator it = mSinks.begin(); it != mSinks.end(); ++it){
        (*it)->FillSwing(mTrack, 0, i2, i1, true);
    }
}

void TrackWatcherImpl::SendHit(float ms, int gemID, unsigned int slots, GemHitFlags flags){
    mSucceeding = true;
    if(mIsCurrentTrack){
        bool isHopo = flags & kGemHitFlagHopo;
        if(TheBeatMatchOutput.IsActive()){
            TheBeatMatchOutput.Print(MakeString("(%2d%10.1f HIT\t%d %d)\n", 0, ms, gemID, isHopo));
        }
    }
    for(std::vector<BeatMatchSink*>::iterator it = mSinks.begin(); it != mSinks.end(); ++it){
        (*it)->Hit(mTrack, ms, gemID, slots, flags);
    }
}

void TrackWatcherImpl::SendMiss(float ms, int i2, int gemID, int i4, GemHitFlags flags){
    mSucceeding = false;
    if(mIsCurrentTrack && TheBeatMatchOutput.IsActive()){
        TheBeatMatchOutput.Print(MakeString("(%2d%10.1f MISS\t%d)\n", 0, ms, gemID));
    }
    GemInProgress* gemInProg = GetGemInProgressWithID(gemID);
    if(gemInProg) EndSustainedNote(*gemInProg);
    mLastMiss = ms;
    if(gemID != -1 && gemID == mLastGemPassed){
        gemID = NextGemAfter(gemID, true);
        i4 = 0;
    }
    if(gemID == -1){
        gemID = mGemList->NumGems() - 1;
    }
    for(std::vector<BeatMatchSink*>::iterator it = mSinks.begin(); it != mSinks.end(); ++it){
        (*it)->Miss(mTrack, i2, ms, gemID, i4, flags);
    }
}

void TrackWatcherImpl::SendSpuriousMiss(float f1, int i2, int i3){
    for(std::vector<BeatMatchSink*>::iterator it = mSinks.begin(); it != mSinks.end(); ++it){
        (*it)->SpuriousMiss(mTrack, i2, f1, i3);
    }
}

void TrackWatcherImpl::SendPass(float ms, int gemID){
    mSucceeding = false;
    if(mIsCurrentTrack && TheBeatMatchOutput.IsActive()){
        TheBeatMatchOutput.Print(MakeString("(%2d%10.1f PASS\t%d)\n", 0, ms, gemID));
    }
    GemInProgress* gemInProg = GetGemInProgressWithID(gemID);
    if(gemInProg) EndSustainedNote(*gemInProg);
    for(std::vector<BeatMatchSink*>::iterator it = mSinks.begin(); it != mSinks.end(); ++it){
        (*it)->Pass(mTrack, ms, gemID, mIsCurrentTrack);
    }
}

void TrackWatcherImpl::SendReleaseGem(float f1, int i2, float f3){
    for(std::vector<BeatMatchSink*>::iterator it = mSinks.begin(); it != mSinks.end(); ++it){
        (*it)->ReleaseGem(mTrack, f1, i2, f3);
    }
}

void TrackWatcherImpl::SendSeen(float f1, int gemID){
    if(mIsCurrentTrack && TheBeatMatchOutput.IsActive()){
        GameGem& gem = mGemList->GetGem(gemID);
        if(gem.IsRealGuitar()){
            float gemMs = gem.mMs;
            TheBeatMatchOutput.Print(
                MakeString("(%2d%10.1f GEM\t%d %d %d %d %d %d %d)\n", 0, gemMs, gemID, 
                    gem.GetFret(0), gem.GetFret(1), gem.GetFret(2), gem.GetFret(3), gem.GetFret(4), gem.GetFret(5))
            );
        }
        else {
            float gemMs = gem.mMs;
            TheBeatMatchOutput.Print(
                MakeString("(%2d%10.1f GEM\t%d %d)\n", 0, gemMs, gemID, gem.GetSlots())
            );
        }
    }
    for(std::vector<BeatMatchSink*>::iterator it = mSinks.begin(); it != mSinks.end(); ++it){
        (*it)->SeeGem(mTrack, f1, gemID);
    }
}

void TrackWatcherImpl::SendIgnore(float f, int i){
    for(std::vector<BeatMatchSink*>::iterator it = mSinks.begin(); it != mSinks.end(); ++it){
        (*it)->Ignore(mTrack, f, i, mUserGuid);
    }
}

void TrackWatcherImpl::SendImplicit(float f, int i){
    for(std::vector<BeatMatchSink*>::iterator it = mSinks.begin(); it != mSinks.end(); ++it){
        (*it)->ImplicitGem(mTrack, f, i, mUserGuid);
    }
}

void TrackWatcherImpl::SendWhammy(float f){
    if(mIsCurrentTrack){
        for(std::vector<BeatMatchSink*>::iterator it = mSinks.begin(); it != mSinks.end(); ++it){
            (*it)->FilteredWhammyBar(f);
        }
    }
}

void TrackWatcherImpl::SendSwingAtHopo(float f, int i){
    for(std::vector<BeatMatchSink*>::iterator it = mSinks.begin(); it != mSinks.end(); ++it){
        (*it)->SwingAtHopo(mTrack, f, i);
    }
}

void TrackWatcherImpl::SendHopo(float f, int i){
    for(std::vector<BeatMatchSink*>::iterator it = mSinks.begin(); it != mSinks.end(); ++it){
        (*it)->Hopo(mTrack, f, i);
    }
}