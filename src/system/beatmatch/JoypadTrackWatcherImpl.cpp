#include "beatmatch/JoypadTrackWatcherImpl.h"
#include "beatmatch/GameGem.h"
#include "beatmatch/GameGemList.h"
#include "beatmatch/TrackWatcherParent.h"
#include "beatmatch/SongData.h"
#include "os/Debug.h"
#include "utl/TempoMap.h"
#include "beatmatch/BeatMatchUtl.h"

JoypadTrackWatcherImpl::JoypadTrackWatcherImpl(
    int track,
    const UserGuid &u,
    int slot,
    SongData *data,
    GameGemList *gemlist,
    TrackWatcherParent *parent,
    DataArray *cfg,
    int size
)
    : TrackWatcherImpl(track, u, slot, data, gemlist, parent, cfg, size),
      mChordSlop(50.0f), mChordGemInProgress(-1), mChordSlotsInProgress(0),
      mChordLastSlot(0) {}

JoypadTrackWatcherImpl::~JoypadTrackWatcherImpl() {}

// fn_804672B8 - swing
bool JoypadTrackWatcherImpl::Swing(int i1, bool b1, bool b2, GemHitFlags flags) {
    KillSustainForSlot(i1);
    float now = mParent->GetNow();
    int unplayedGem = ClosestUnplayedGem(now, i1);
    float f15 = mGemList->TimeAt(unplayedGem);
    mGemList->TimeAtNext(unplayedGem);
    bool i4 = InSlopWindow(f15, now);
    GameGem &gem5 = mGemList->GetGem(unplayedGem);
    int i6 = mGemList->GetGem(unplayedGem).GetTick();
    unsigned int u13;
    if (gem5.NumSlots() == 1) {
        u13 = 1 << i1;
        NoteSwing(u13, i6);
    } else {
        u13 = 1 << i1;
        NoteSwing(mChordSlotsInProgress | u13, i6);
    }
    bool bvar2 = false;
    if (AllowAllInputInRolls()) {
        int f6 = mSongData->GetTempoMap()->TimeToTick(now + mSyncOffset);
        int i60 = 0;
        int i9 = mSongData->GetTempoMap()->GetLoopTick(f6, i60);
        if (mSongData->GetRollingSlotsAtTick(Track(), i9)) {
            unsigned int i68;
            int i64 = 0;
            mSongData->GetNextRoll(Track(), i9, i68, i64);
            bvar2 = true;
            float f16 = GetRollIntervalMs(
                mRollIntervalsConfig,
                mSongData->TrackTypeAt(Track()),
                mSongData->TrackDiffAt(Track()),
                false
            );
            for (int i = unplayedGem; i < mGemList->NumGems(); i++) {
                GameGem &curGem = mGemList->GetGem(i);
                if (curGem.mMs >= now + mSyncOffset + f16
                    || curGem.GetTick() >= i64 + i60)
                    break;
                mGemList->GetGem(i).SetUnk10B1(true);
            }
        }
    }
    if (mChordGemInProgress != -1) {
        if (mChordGemInProgress != unplayedGem) {
            OnMiss(now, mChordLastSlot, unplayedGem, 0, kGemHitFlagNone);
            ResetChordInProgress();
        } else {
            TryToCompleteChord(now, i1);
            return false;
        }
    }
    if (i4) {
        if (!gem5.GetPlayed() && Playable(unplayedGem)) {
            if (gem5.NumSlots() == 1) {
                if (i1 == gem5.GetSlot() || i1 == -1 || bvar2) {
                    OnHit(now, i1, unplayedGem, gem5.GetSlots(), flags);
                } else {
                    OnMiss(now, i1, unplayedGem, 0, flags);
                }
            }

            else {
                MILO_ASSERT(mChordGemInProgress == -1, 0x96);
                if (bvar2) {
                    OnHit(now, i1, unplayedGem, gem5.GetSlots(), flags);
                } else {
                    if (u13 & gem5.GetSlots()) {
                        mChordGemInProgress = unplayedGem;
                        mChordSlotsInProgress = u13;
                        mChordLastSlot = i1;
                        mChordTimeout = now + mChordSlop;
                    } else {
                        OnMiss(now, i1, unplayedGem, 0, kGemHitFlagNone);
                    }
                }
            }
        } else if (!bvar2)
            OnMiss(now, mChordLastSlot, unplayedGem, 0, kGemHitFlagNone);
    } else if (!bvar2)
        OnMiss(now, mChordLastSlot, unplayedGem, 0, kGemHitFlagNone);
    return true;
}

bool JoypadTrackWatcherImpl::AllowAllInputInRolls() const { return false; }

void JoypadTrackWatcherImpl::TryToCompleteChord(float f, int i) {
    GameGem &gem = mGemList->GetGem(mChordGemInProgress);
    int slots = gem.GetSlots();
    if (1 << i & slots) {
        mChordSlotsInProgress |= 1 << i;
        if (mChordSlotsInProgress == slots) {
            OnHit(f, i, mChordGemInProgress, mChordSlotsInProgress, kGemHitFlagNone);
        }
    } else {
        OnMiss(f, i, mChordGemInProgress, mChordSlotsInProgress, kGemHitFlagNone);
        ResetChordInProgress();
    }
}

void JoypadTrackWatcherImpl::FretButtonUp(int i) { KillSustainForSlot(i); }
float JoypadTrackWatcherImpl::HitGemHook(float, int, GemHitFlags) {
    ResetChordInProgress();
}
void JoypadTrackWatcherImpl::JumpHook(float f) { ResetChordInProgress(); }
void JoypadTrackWatcherImpl::PollHook(float f) { CheckForChordTimeout(f); }

void JoypadTrackWatcherImpl::CheckForChordTimeout(float f) {
    if (mChordGemInProgress != -1 && mChordTimeout < f) {
        OnMiss(
            f, mChordLastSlot, mChordGemInProgress, mChordSlotsInProgress, kGemHitFlagNone
        );
        ResetChordInProgress();
    }
}

void JoypadTrackWatcherImpl::ResetChordInProgress() {
    mChordGemInProgress = -1;
    mChordSlotsInProgress = 0;
    mChordLastSlot = -1;
    mChordTimeout = 0.0f;
}