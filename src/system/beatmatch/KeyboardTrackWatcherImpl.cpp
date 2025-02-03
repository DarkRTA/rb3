#include "beatmatch/BeatMatchSink.h"
#include "beatmatch/KeyboardTrackWatcherImpl.h"
#include "beatmatch/GameGem.h"
#include "beatmatch/GameGemList.h"
#include "beatmatch/JoypadTrackWatcherImpl.h"
#include "beatmatch/SongData.h"
#include "beatmatch/TrackType.h"
#include "beatmatch/TrackWatcherImpl.h"
#include "os/Debug.h"
#include "utl/Std.h"

KeyboardTrackWatcherImpl::KeyboardTrackWatcherImpl(
    int track,
    const UserGuid &u,
    int slot,
    SongData *data,
    GameGemList *gemlist,
    TrackWatcherParent *parent,
    DataArray *cfg
)
    : JoypadTrackWatcherImpl(track, u, slot, data, gemlist, parent, cfg, 5), mHeldGem(-1),
      mHeldSlots(0), mDownKeys(0), mMissWindowMs(0), mLastMissTimeMs(0),
      mFatFingerWindowMs(50) {
    FatFingerData fingerData;
    fingerData.gemID = -1;
    fingerData.unk8 = -1.0f;
    fingerData.slots = 0;
    fingerData.gemHitFlags = kGemHitFlagNone;
    for (int i = 0; i < 10; i++) {
        mFatFingerDatas.push_back(fingerData);
    }
    if (cfg) {
        cfg->FindData("keyboard_miss_window_ms", mMissWindowMs, false);
        cfg->FindData("keyboard_fat_finger_window_ms", mFatFingerWindowMs, false);
    }
}

KeyboardTrackWatcherImpl::~KeyboardTrackWatcherImpl() {}

void KeyboardTrackWatcherImpl::Jump(float ms) {
    TrackWatcherImpl::Jump(ms);
    mHeldGem = -1;
    mHeldSlots = 0;
    mLastMissTimeMs = 0;
}

void KeyboardTrackWatcherImpl::Poll(float ms) {
    TrackWatcherImpl::Poll(ms);
    for (int i = 0; i < mFatFingerDatas.size(); i++) {
        FatFingerData &curData = mFatFingerDatas[i];
        if (curData.gemID != -1 && ms - curData.unk8 > mFatFingerWindowMs) {
            TrackWatcherImpl::OnMiss(
                ms, curData.slot, curData.gemID, curData.slots, curData.gemHitFlags
            );
            JoypadTrackWatcherImpl::FretButtonUp(curData.slot);
            curData.gemID = -1;
        }
    }
}

void KeyboardTrackWatcherImpl::FretButtonDown(int slot) {
    mDownKeys |= 1 << slot;
    SwingForTrill(slot);
}

void KeyboardTrackWatcherImpl::FretButtonUp(int slot) {
    int mask = 1 << slot;
    mDownKeys &= ~mask;
    if (mHeldGem != -1) {
        MILO_ASSERT(mHeldSlots != 0, 0x89);
        if (mHeldSlots & mask) {
            mHeldSlots &= ~mask;
            if (mHeldSlots == 0) {
                KillSustain(mHeldGem);
                mHeldGem = -1;
            }
        }
    }
    FatFingerData *data = FindFatFingerDataForSlot(slot);
    if (data) {
        if (data->gemPlayed) {
            data->gemID = -1;
        } else {
            TrackWatcherImpl::OnMiss(
                data->unk8, data->slot, data->gemID, data->slots, data->gemHitFlags
            );
            data->gemID = -1;
        }
    }
}

void KeyboardTrackWatcherImpl::OutOfRangeSwing() {
    FOREACH(it, mSinks) { (*it)->OutOfRangeSwing(); }
}

int KeyboardTrackWatcherImpl::ClosestUnplayedGem(float ms, int slot) {
    int i1 = mGemList->ClosestMarkerIdx(ms + mSyncOffset);
    float f4 = mGemList->TimeAt(i1);
    int i3;
    for (i3 = i1; i3 + 1 < mGemList->NumGems() && mGemList->TimeAt(i3) <= f4 + 20.0f;
         i3++)
        ;
    for (; i1 - 1 >= 0 && mGemList->TimeAt(i1) >= f4 - 20.0f; i1--)
        ;
    return RelevantGem(i1, i3, slot);
}

int KeyboardTrackWatcherImpl::RelevantGem(int first_gem_id, int last_gem_id, int slot) {
    MILO_WARN("closest_gem != -1");
}

void KeyboardTrackWatcherImpl::CheckForChordTimeout(float ms) {
    if (mChordGemInProgress != -1 && mChordTimeout < ms) {
        MILO_ASSERT(mChordSlotsInProgress != 0, 0x12E);
        mHeldGem = mChordGemInProgress;
        mHeldSlots = mChordSlotsInProgress;
        OnHit(
            ms, mChordLastSlot, mChordGemInProgress, mChordSlotsInProgress, kGemHitFlagNone
        );
        ResetChordInProgress();
    }
}

void KeyboardTrackWatcherImpl::CodaSwing(int tick, int slot) {
    if (mSongData->TrackTypeAt(Track()) == 5) {
        TrackWatcherImpl::CodaSwing(tick, 0);
    } else
        TrackWatcherImpl::CodaSwing(tick, slot);
}

void KeyboardTrackWatcherImpl::OnHit(
    float ms, int slot, int gemID, unsigned int slots, GemHitFlags flags
) {
    TrackWatcherImpl::OnHit(ms, slot, gemID, slots, flags);
    mHeldGem = gemID;
    mHeldSlots = slots;
    FatFingerData *data = FindFatFingerData(gemID);
    if (data)
        data->gemPlayed = true;
}

void KeyboardTrackWatcherImpl::OnMiss(
    float ms, int slot, int gemID, unsigned int slots, GemHitFlags flags
) {
    float tick = mSongData->GetTempoMap()->TimeToTick(ms);
    if (!mParent->InCodaFreestyle(tick, true)) {
        if (ms - mLastMissTimeMs < mMissWindowMs) {
            SendSpuriousMiss(ms, slot, gemID);
            return;
        }
        if (CheckForFatFinger(ms, slot, slots, flags))
            return;
    }
    mLastMissTimeMs = ms;
    TrackWatcherImpl::OnMiss(ms, slot, gemID, slots, flags);
}

void KeyboardTrackWatcherImpl::OnPass(float ms, int gemID) {
    TrackWatcherImpl::OnPass(ms, gemID);
    FatFingerData *data = FindFatFingerData(gemID);
    if (data) {
        TrackWatcherImpl::OnMiss(
            ms, data->slot, data->gemID, data->slots, data->gemHitFlags
        );
        JoypadTrackWatcherImpl::FretButtonUp(data->slot);
        data->gemID = -1;
    }
}

void KeyboardTrackWatcherImpl::SwingForTrill(int slot) {
    float now = mParent->GetNow();
    int unplayed = ClosestUnplayedGem(now, slot);
    if (unplayed != -1) {
        CheckForTrills(now, mGemList->GetGem(unplayed).GetTick(), 1 << slot);
    }
}

bool KeyboardTrackWatcherImpl::CheckForFatFinger(
    float ms, int slot, unsigned int slots, GemHitFlags flags
) {
    if (!TrackForgivesFatFingering())
        return false;
    else {
        unsigned int neighborSlotMask = MakeNeighboringSlotMask(slot);
        MILO_ASSERT(neighborSlotMask != 0, 0x1BE);
        int gem = GetFatFingerGem(ms);
        if (gem == -1)
            return false;
        else if (!Playable(gem))
            return false;
        else {
            GameGem &fatGem = mGemList->GetGem(gem);
            unsigned int fatSlots = fatGem.GetSlots();
            if (!(fatSlots & neighborSlotMask))
                return false;
            else {
                FatFingerData *data = FindFatFingerData(gem);
                if (data) {
                    TrackWatcherImpl::OnMiss(
                        ms, data->slot, data->gemID, data->slots, data->gemHitFlags
                    );
                    JoypadTrackWatcherImpl::FretButtonUp(data->slot);
                    data->gemID = -1;
                }
                FatFingerData *unused = FindUnusedFatFingerData();
                unused->gemID = gem;
                unused->gemPlayed = fatGem.GetPlayed();
                unused->unk8 = ms;
                unused->slot = slot;
                unused->slots = slots;
                unused->gemHitFlags = flags;
                return true;
            }
        }
    }
}

KeyboardTrackWatcherImpl::FatFingerData *
KeyboardTrackWatcherImpl::FindFatFingerData(int gemID) {
    for (int i = 0; i < mFatFingerDatas.size(); i++) {
        FatFingerData *cur = &mFatFingerDatas[i];
        if (cur->gemID == gemID)
            return cur;
    }
    return nullptr;
}

KeyboardTrackWatcherImpl::FatFingerData *
KeyboardTrackWatcherImpl::FindFatFingerDataForSlot(int slot) {
    for (int i = 0; i < mFatFingerDatas.size(); i++) {
        FatFingerData *cur = &mFatFingerDatas[i];
        if (cur->gemID != -1 && cur->slot == slot)
            return cur;
    }
    return nullptr;
}

KeyboardTrackWatcherImpl::FatFingerData *
KeyboardTrackWatcherImpl::FindUnusedFatFingerData() {
    for (int i = 0; i < mFatFingerDatas.size(); i++) {
        FatFingerData *cur = &mFatFingerDatas[i];
        if (cur->gemID == -1)
            return cur;
    }
    MILO_FAIL("Ran out of fat finger data!!!");
    return nullptr;
}

int KeyboardTrackWatcherImpl::GetFatFingerGem(float ms) {
    int idx = mGemList->ClosestMarkerIdxAtOrAfter(ms + mSyncOffset - mFatFingerWindowMs);
    if (idx == -1)
        return -1;
    else if (std::fabs(mGemList->GetGem(idx).mMs - ms) > mFatFingerWindowMs)
        return -1;
    return idx;
}

unsigned int KeyboardTrackWatcherImpl::MakeNeighboringSlotMask(int slot) const {
    TrackType ty = mSongData->TrackTypeAt(Track());
    unsigned int mask = 0;
    if (ty == kTrackRealKeys) {
        int neighboringSlot = GetNeighboringWhiteKeySlot(slot, 1);
        if (neighboringSlot != -1)
            mask = 1 << neighboringSlot;

        neighboringSlot = GetNeighboringWhiteKeySlot(slot, -1);
        if (neighboringSlot != -1)
            mask |= 1 << neighboringSlot;

        neighboringSlot = GetNeighboringBlackKeySlot(slot, 1);
        if (neighboringSlot != -1)
            mask |= 1 << neighboringSlot;

        neighboringSlot = GetNeighboringBlackKeySlot(slot, -1);
        if (neighboringSlot != -1)
            mask |= 1 << neighboringSlot;
    } else {
        int neighboringSlot = GetNeighboring5LaneSlot(slot, 1);
        if (neighboringSlot != -1)
            mask = 1 << neighboringSlot;

        neighboringSlot = GetNeighboring5LaneSlot(slot, -1);
        if (neighboringSlot != -1)
            mask |= 1 << neighboringSlot;
    }
    return mask;
}

int KeyboardTrackWatcherImpl::GetNeighboringWhiteKeySlot(int slot, int direction) const {
    MILO_ASSERT(direction == 1 || direction == -1, 0x278);
    if (slot == 0 && direction == -1)
        return -1;
    if (slot == 0x18 && direction == 1)
        return -1;
    if (direction == -1) {
        switch (slot % 12) {
        case 0:
        case 1:
        case 5:
        case 6:
        case 3:
        case 8:
        case 10:
            return slot - 1;
        default:
            return slot - 2;
        }
    } else {
        switch (slot % 12) {
        case 3:
        case 4:
        case 10:
        case 11:
        case 1:
        case 6:
        case 8:
            return slot + 1;
        default:
            return slot + 2;
        }
    }
}

int KeyboardTrackWatcherImpl::GetNeighboringBlackKeySlot(int slot, int direction) const {
    MILO_ASSERT(direction == 1 || direction == -1, 0x2A8);
    if (slot <= 1U && direction == -1)
        return -1;
    if ((slot == 0x18 || slot == 0x16) && direction == 1)
        return -1;
    if (direction == -1) {
        switch (slot % 12) {
        case 0:
        case 1:
        case 5:
        case 6:
            return -1;
        case 3:
        case 8:
        case 10:
            return slot - 2;
        default:
            return slot - 1;
        }
    } else {
        switch (slot % 12) {
        case 3:
        case 4:
        case 10:
        case 11:
            return -1;
        case 1:
        case 6:
        case 8:
            return slot + 2;
        default:
            return slot + 1;
        }
    }
}

int KeyboardTrackWatcherImpl::GetNeighboring5LaneSlot(int slot, int direction) const {
    MILO_ASSERT(direction == 1 || direction == -1, 0x2DD);
    if (slot == 0 && direction == -1)
        return -1;
    if (slot == 4 && direction == 1)
        return -1;
    return slot + direction;
}

bool KeyboardTrackWatcherImpl::TrackForgivesFatFingering() const {
    return mSongData->TrackTypeAt(Track()) == kTrackRealKeys;
}