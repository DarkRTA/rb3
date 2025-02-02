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
    : JoypadTrackWatcherImpl(track, u, slot, data, gemlist, parent, cfg, 5), unkd4(-1),
      mHeldSlots(0), unkdc(0), mMissWindowMs(0), unke4(0), mFatFingerWindowMs(50) {
    FatFingerData fingerData;
    fingerData.unk0 = -1;
    fingerData.unk8 = -1.0f;
    fingerData.unk10 = 0;
    fingerData.unk14 = kGemHitFlagNone;
    for (int i = 0; i < 10; i++) {
        mFatFingerDatas.push_back(fingerData);
    }
    if (cfg) {
        cfg->FindData("keyboard_miss_window_ms", mMissWindowMs, false);
        cfg->FindData("keyboard_fat_finger_window_ms", mFatFingerWindowMs, false);
    }
}

KeyboardTrackWatcherImpl::~KeyboardTrackWatcherImpl() {}

void KeyboardTrackWatcherImpl::Jump(float f) {
    TrackWatcherImpl::Jump(f);
    unkd4 = -1;
    mHeldSlots = 0;
    unke4 = 0;
}

void KeyboardTrackWatcherImpl::Poll(float f) {
    TrackWatcherImpl::Poll(f);
    for (int i = 0; i < mFatFingerDatas.size(); i++) {
        FatFingerData &curData = mFatFingerDatas[i];
        if (curData.unk0 != -1 && f - curData.unk8 > mFatFingerWindowMs) {
            TrackWatcherImpl::OnMiss(
                f, curData.unkc, curData.unk0, curData.unk10, curData.unk14
            );
            JoypadTrackWatcherImpl::FretButtonUp(curData.unkc);
            curData.unk0 = -1;
        }
    }
}

void KeyboardTrackWatcherImpl::FretButtonDown(int i) {
    unkdc |= 1 << i;
    SwingForTrill(i);
}

void KeyboardTrackWatcherImpl::FretButtonUp(int i) {
    int mask = 1 << i;
    unkdc &= ~mask;
    if (unkd4 != -1) {
        MILO_ASSERT(mHeldSlots != 0, 0x89);
        if (mHeldSlots & mask) {
            mHeldSlots &= ~mask;
            if (mHeldSlots == 0) {
                KillSustain(unkd4);
                unkd4 = -1;
            }
        }
    }
    FatFingerData *data = FindFatFingerDataForSlot(i);
    if (data) {
        if (data->unk4) {
            data->unk0 = -1;
        } else {
            TrackWatcherImpl::OnMiss(
                data->unk8, data->unkc, data->unk0, data->unk10, data->unk14
            );
            data->unk0 = -1;
        }
    }
}

void KeyboardTrackWatcherImpl::OutOfRangeSwing() {
    FOREACH(it, mSinks) { (*it)->OutOfRangeSwing(); }
}

int KeyboardTrackWatcherImpl::ClosestUnplayedGem(float f1, int i2) {
    int i1 = mGemList->ClosestMarkerIdx(f1 + mSyncOffset);
    float f4 = mGemList->TimeAt(i1);
    int i3;
    for (i3 = i1; i3 + 1 < mGemList->NumGems() && mGemList->TimeAt(i3) <= f4 + 20.0f;
         i3++)
        ;
    for (; i1 - 1 >= 0 && mGemList->TimeAt(i1) >= f4 - 20.0f; i1--)
        ;
    return RelevantGem(i1, i3, i2);
}

int KeyboardTrackWatcherImpl::RelevantGem(int, int, int) {
    MILO_WARN("closest_gem != -1");
}

void KeyboardTrackWatcherImpl::CheckForChordTimeout(float f) {
    if (mChordGemInProgress != -1 && mChordTimeout < f) {
        MILO_ASSERT(mChordSlotsInProgress != 0, 0x12E);
        unkd4 = mChordGemInProgress;
        mHeldSlots = mChordSlotsInProgress;
        OnHit(
            f, mChordLastSlot, mChordGemInProgress, mChordSlotsInProgress, kGemHitFlagNone
        );
        ResetChordInProgress();
    }
}

void KeyboardTrackWatcherImpl::CodaSwing(int i1, int i2) {
    if (mSongData->TrackTypeAt(Track()) == 5) {
        TrackWatcherImpl::CodaSwing(i1, 0);
    } else
        TrackWatcherImpl::CodaSwing(i1, i2);
}

void KeyboardTrackWatcherImpl::OnHit(
    float f1, int i2, int i3, unsigned int ui, GemHitFlags flags
) {
    TrackWatcherImpl::OnHit(f1, i2, i3, ui, flags);
    unkd4 = i3;
    mHeldSlots = ui;
    FatFingerData *data = FindFatFingerData(i3);
    if (data)
        data->unk4 = true;
}

void KeyboardTrackWatcherImpl::OnMiss(
    float f1, int i2, int i3, unsigned int ui, GemHitFlags flags
) {
    float tick = mSongData->GetTempoMap()->TimeToTick(f1);
    if (!mParent->InCodaFreestyle(tick, true)) {
        if (f1 - unke4 < mMissWindowMs) {
            SendSpuriousMiss(f1, i2, i3);
            return;
        }
        if (CheckForFatFinger(f1, i2, ui, flags))
            return;
    }
    unke4 = f1;
    TrackWatcherImpl::OnMiss(f1, i2, i3, ui, flags);
}

void KeyboardTrackWatcherImpl::OnPass(float f1, int i2) {
    TrackWatcherImpl::OnPass(f1, i2);
    FatFingerData *data = FindFatFingerData(i2);
    if (data) {
        TrackWatcherImpl::OnMiss(f1, data->unkc, data->unk0, data->unk10, data->unk14);
        JoypadTrackWatcherImpl::FretButtonUp(data->unkc);
        data->unk0 = -1;
    }
}

void KeyboardTrackWatcherImpl::SwingForTrill(int i1) {
    float now = mParent->GetNow();
    int unplayed = ClosestUnplayedGem(now, i1);
    if (unplayed != -1) {
        CheckForTrills(now, mGemList->GetGem(unplayed).GetTick(), 1 << i1);
    }
}

bool KeyboardTrackWatcherImpl::CheckForFatFinger(
    float f1, int i2, unsigned int ui, GemHitFlags flags
) {
    if (!TrackForgivesFatFingering())
        return false;
    else {
        unsigned int neighborSlotMask = MakeNeighboringSlotMask(i2);
        MILO_ASSERT(neighborSlotMask != 0, 0x1BE);
        int gem = GetFatFingerGem(f1);
        if (gem == -1)
            return false;
        else if (!Playable(gem))
            return false;
        else {
            GameGem &fatGem = mGemList->GetGem(gem);
            unsigned int slots = fatGem.GetSlots();
            if (!(slots & neighborSlotMask))
                return false;
            else {
                FatFingerData *data = FindFatFingerData(gem);
                if (data) {
                    TrackWatcherImpl::OnMiss(
                        f1, data->unkc, data->unk0, data->unk10, data->unk14
                    );
                    JoypadTrackWatcherImpl::FretButtonUp(data->unkc);
                    data->unk0 = -1;
                }
                FatFingerData *unused = FindUnusedFatFingerData();
                unused->unk0 = gem;
                unused->unk4 = fatGem.GetPlayed();
                unused->unk8 = f1;
                unused->unkc = i2;
                unused->unk10 = ui;
                unused->unk14 = flags;
                return true;
            }
        }
    }
}

KeyboardTrackWatcherImpl::FatFingerData *
KeyboardTrackWatcherImpl::FindFatFingerData(int gemID) {
    for (int i = 0; i < mFatFingerDatas.size(); i++) {
        FatFingerData *cur = &mFatFingerDatas[i];
        if (cur->unk0 == gemID)
            return cur;
    }
    return nullptr;
}

KeyboardTrackWatcherImpl::FatFingerData *
KeyboardTrackWatcherImpl::FindFatFingerDataForSlot(int slot) {
    for (int i = 0; i < mFatFingerDatas.size(); i++) {
        FatFingerData *cur = &mFatFingerDatas[i];
        if (cur->unk0 != -1 && cur->unkc == slot)
            return cur;
    }
    return nullptr;
}

KeyboardTrackWatcherImpl::FatFingerData *
KeyboardTrackWatcherImpl::FindUnusedFatFingerData() {
    for (int i = 0; i < mFatFingerDatas.size(); i++) {
        FatFingerData *cur = &mFatFingerDatas[i];
        if (cur->unk0 == -1)
            return cur;
    }
    MILO_FAIL("Ran out of fat finger data!!!");
    return nullptr;
}

int KeyboardTrackWatcherImpl::GetFatFingerGem(float f) {
    int idx = mGemList->ClosestMarkerIdxAtOrAfter(f + mSyncOffset - mFatFingerWindowMs);
    if (idx == -1)
        return -1;
    else if (std::fabs(mGemList->GetGem(idx).mMs - f) > mFatFingerWindowMs)
        return -1;
    return idx;
}

unsigned int KeyboardTrackWatcherImpl::MakeNeighboringSlotMask(int i1) const {
    TrackType ty = mSongData->TrackTypeAt(Track());
    unsigned int mask = 0;
    if (ty == kTrackRealKeys) {
        int slot = GetNeighboringWhiteKeySlot(i1, 1);
        if (slot != -1)
            mask = 1 << slot;

        slot = GetNeighboringWhiteKeySlot(i1, -1);
        if (slot != -1)
            mask |= 1 << slot;

        slot = GetNeighboringBlackKeySlot(i1, 1);
        if (slot != -1)
            mask |= 1 << slot;

        slot = GetNeighboringBlackKeySlot(i1, -1);
        if (slot != -1)
            mask |= 1 << slot;
    } else {
        int slot = GetNeighboring5LaneSlot(i1, 1);
        if (slot != -1)
            mask = 1 << slot;

        slot = GetNeighboring5LaneSlot(i1, -1);
        if (slot != -1)
            mask |= 1 << slot;
    }
    return mask;
}

int KeyboardTrackWatcherImpl::GetNeighboringWhiteKeySlot(int i1, int direction) const {
    MILO_ASSERT(direction == 1 || direction == -1, 0x278);
    if (i1 == 0 && direction == -1)
        return -1;
    if (i1 == 0x18 && direction == 1)
        return -1;
    if (direction == -1) {
        switch (i1 % 12) {
        case 0:
        case 1:
        case 5:
        case 6:
        case 3:
        case 8:
        case 10:
            return i1 - 1;
        default:
            return i1 - 2;
        }
    } else {
        switch (i1 % 12) {
        case 3:
        case 4:
        case 10:
        case 11:
        case 1:
        case 6:
        case 8:
            return i1 + 1;
        default:
            return i1 + 2;
        }
    }
}

int KeyboardTrackWatcherImpl::GetNeighboringBlackKeySlot(int i1, int direction) const {
    MILO_ASSERT(direction == 1 || direction == -1, 0x2A8);
    if (i1 <= 1U && direction == -1)
        return -1;
    if ((i1 == 0x18 || i1 == 0x16) && direction == 1)
        return -1;
    if (direction == -1) {
        switch (i1 % 12) {
        case 0:
        case 1:
        case 5:
        case 6:
            return -1;
        case 3:
        case 8:
        case 10:
            return i1 - 2;
        default:
            return i1 - 1;
        }
    } else {
        switch (i1 % 12) {
        case 3:
        case 4:
        case 10:
        case 11:
            return -1;
        case 1:
        case 6:
        case 8:
            return i1 + 2;
        default:
            return i1 + 1;
        }
    }
}

int KeyboardTrackWatcherImpl::GetNeighboring5LaneSlot(int i1, int direction) const {
    MILO_ASSERT(direction == 1 || direction == -1, 0x2DD);
    if (i1 == 0 && direction == -1)
        return -1;
    if (i1 == 4 && direction == 1)
        return -1;
    return i1 + direction;
}

bool KeyboardTrackWatcherImpl::TrackForgivesFatFingering() const {
    return mSongData->TrackTypeAt(Track()) == kTrackRealKeys;
}