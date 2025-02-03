#include "beatmatch/GuitarTrackWatcherImpl.h"
#include "BeatMatchControllerSink.h"
#include "beatmatch/BeatMatchControllerSink.h"
#include "os/Debug.h"
#include "beatmatch/GameGemList.h"

GuitarTrackWatcherImpl::GuitarTrackWatcherImpl(
    int track,
    const UserGuid &u,
    int slot,
    SongData *data,
    GameGemList *gemlist,
    TrackWatcherParent *parent,
    DataArray *cfg
)
    : BaseGuitarTrackWatcherImpl(track, u, slot, data, gemlist, parent, cfg),
      mFretButtonsDown(0) {}

GuitarTrackWatcherImpl::~GuitarTrackWatcherImpl() {}

bool GuitarTrackWatcherImpl::Swing(int i, bool b1, bool b2, GemHitFlags flags) {
    return BaseGuitarTrackWatcherImpl::Swing(i, b1, b2, flags);
}

bool GuitarTrackWatcherImpl::HandleHitsAndMisses(
    int i1, int i2, float ff, bool b1, bool b2, bool b3, GemHitFlags flags
) {
    GameGem &gem = mGemList->GetGem(i1);
    if (!gem.GetPlayed() && Playable(i1)) {
        bool bvar1 = false;
        if (!b1)
            flags = (GemHitFlags)(flags | kGemHitFlagSolo);
        if (gem.NumSlots() == 1) {
            if (i2 == gem.GetSlot()) {
                OnHit(ff, i2, i1, gem.GetSlots(), flags);
                bvar1 = true;
                if (!b1)
                    SetLastNoStrumGem(ff, i1);
            }
        } else if (mFretButtonsDown == gem.GetSlots()) {
            OnHit(ff, i2, i1, gem.GetSlots(), flags);
            if (!b1)
                SetLastNoStrumGem(ff, i1);
            bvar1 = true;
        }
        if (!bvar1) {
            if (b1 && mGemNotFretted != -1 && !b2) {
                OnMiss(ff, mFretWhenStrummed, mGemNotFretted, 0, kGemHitFlagNone);
                ResetGemNotFretted();
            }
            if (b1 || gem.NumSlots() > 1) {
                if (!b1 && !b3 && HarmlessFretDown(i2, i1))
                    return false;
                bool g5 = false;
                mGemNotFretted = i1;
                mFretWhenStrummed = i2;
                mFretWaitTimeout = ff + mFretSlop;
                if (mLastNoStrumGemHit == i1 - 1 || b2)
                    g5 = true;
                mHarmlessSwing = g5;
            } else
                OnMiss(ff, i2, i1, 0, kGemHitFlagNone);
        }
    } else {
        if (!b1 && !b3 && HarmlessFretDown(i2, i1))
            return false;
        if (!b2)
            OnMiss(ff, i2, i1, 0, kGemHitFlagNone);
        else
            return false;
    }
    return true;
}

void GuitarTrackWatcherImpl::RecordFretButtonDown(int i) { mFretButtonsDown |= 1 << i; }

void GuitarTrackWatcherImpl::RecordFretButtonUp(int i) { mFretButtonsDown &= ~(1 << i); }

unsigned int GuitarTrackWatcherImpl::GetFretButtonsDown() const {
    return mFretButtonsDown;
}

bool GuitarTrackWatcherImpl::HarmlessFretDown(int i1, int i2) const {
    int slot_bit = 1 << i1;
    MILO_ASSERT(mFretButtonsDown & slot_bit, 0xB7);
    if (slot_bit < int(mFretButtonsDown - slot_bit)) {
        return true;
    } else if (i2 == -1)
        return false;
    else {
        unsigned int slots = mGemList->GetGem(i2).GetSlots();
        if (slots & slot_bit)
            return true;
        else
            return false;
    }
}

bool GuitarTrackWatcherImpl::IsCoreGuitar() const { return true; }

bool GuitarTrackWatcherImpl::FretMatch(int i, bool b1, bool b2) const {
    GameGem &gem = mGemList->GetGem(i);
    if (gem.NumSlots() == 1) {
        return gem.GetSlot() == GameGem::GetHighestSlot(mFretButtonsDown);
    } else {
        return gem.GetSlots() == mFretButtonsDown;
    }
}

bool GuitarTrackWatcherImpl::IsChordSubset(int i) const {
    GameGem &gem = mGemList->GetGem(i);
    return (mFretButtonsDown & gem.GetSlots()) == mFretButtonsDown;
}

bool GuitarTrackWatcherImpl::IsHighestFret(int i) const {
    return mFretButtonsDown < (1 << (i + 1));
}

bool GuitarTrackWatcherImpl::InGem(int i, const GameGem &gem) const {
    return 1 << i & gem.GetSlots();
}