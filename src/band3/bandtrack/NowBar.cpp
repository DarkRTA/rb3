#include "NowBar.h"

#include "GemSmasher.h"
#include "game/FretHand.h"
#include "game/SongDB.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "os/System.h"
#include "rndobj/Dir.h"
#include "system/beatmatch/GameGem.h"
#include "utl/Std.h"

NowBar::NowBar(TrackDir *trackDir, const TrackConfig &trackConfig)
    : mSmashers(), mCurrentGem(-1), unk_0xc(0), mTrackDir(trackDir),
      mTrackCfg(trackConfig) {
    MILO_ASSERT(mTrackDir, 0x1e);
    RndDir *smasherPlateDir = mTrackDir->SmasherPlate();
    MILO_ASSERT(smasherPlateDir, 0x21);

    DataArray *cfg = SystemConfig("track_graphics", "smashers", trackConfig.Type());
    for (int i = 0; i < trackConfig.GetMaxSlots(); i++) {
        RndDir *newDir = smasherPlateDir->Find<RndDir>(cfg->Str(i + 1), true);
        mSmashers.push_back(new GemSmasher(i, newDir, mTrackCfg.IsKeyboardTrack()));
    }
}

NowBar::~NowBar() { DeleteAll(mSmashers); }

void NowBar::Poll(float, bool) {}

void NowBar::Reset(bool reset) {
    FOREACH (it, mSmashers) {
        (*it)->Reset(reset);
    }
    unk_0xc = 0;
}

void NowBar::Hit(float f1, int gemID, bool coda, int i4, bool chord) {
    const GameGem &curGem = TheSongDB->GetGem(mTrackCfg.TrackNum(), gemID);
    unsigned int slots = curGem.GetSlots();
    bool isDrum = mTrackCfg.IsDrumTrack();
    bool burn = !isDrum && (!curGem.IgnoreDuration() || curGem.LeftHandSlide());
    bool bonus = (i4 & 2) > 0;
    TheSongDB->GetTotalGems(mTrackCfg.TrackNum());
    bool drum = false;
    bool cymbal = false;
    if (isDrum) {
        if (curGem.IsCymbal() && (slots & mTrackCfg.GetGameCymbalLanes()))
            cymbal = true;
        else
            drum = true;
    }
    if (!mTrackCfg.AllowsOverlappingGems()) {
        StopBurning(-1);
    }
    for (int i = 0; i < mTrackCfg.GetMaxSlots(); i++) {
        if ((slots & 1 << i) && (!chord || curGem.GetRGNoteType(i) != 1)) {
            GemSmasher *smasher = FindSmasher(i);
            MILO_ASSERT(smasher, 0x71);
            if (!smasher->Null()) {
                if (coda) {
                    if (chord) {
                        smasher->CodaHitChord();
                        if (burn)
                            smasher->CodaBurnChord();
                    } else {
                        smasher->CodaHit();
                        if (burn)
                            smasher->CodaBurn();
                    }
                } else if (bonus) {
                    if (chord)
                        smasher->HitChordBonus();
                    else if (drum)
                        smasher->HitDrumBonus();
                    else if (cymbal)
                        smasher->HitCymbalBonus();
                    else
                        smasher->HitBonus();
                    if (burn)
                        smasher->BurnBonus();
                } else if (chord) {
                    smasher->HitChord();
                    if (burn)
                        smasher->BurnChord();
                } else {
                    if (drum)
                        smasher->HitDrum();
                    else if (cymbal)
                        smasher->HitCymbal();
                    else
                        smasher->Hit();
                    if (burn)
                        smasher->Burn();
                }
            }
        }
    }
    if (burn)
        unk_0xc |= slots;
    mCurrentGem = gemID;
}

void NowBar::Miss(float param1, int slot) {
    MILO_ASSERT_RANGE(slot, 0, mTrackCfg.GetMaxSlots(), 0xBA);
    GemSmasher *smasher = FindSmasher(slot);
    if (smasher != 0 && !HandleOutOfRangeKey(smasher, slot, false)) {
        smasher->Miss();
        if (!mTrackCfg.IsKeyboardTrack()) {
            for (int i = 0; i < mSmashers.size(); i++) {
                GemSmasher *smasherVec = mSmashers[i];
                if (smasherVec != smasher && smasherVec->Glowing()) {
                    smasherVec->Miss();
                }
            }
        }
    }
    mCurrentGem = -1;
}

void NowBar::PartialHit(int gemID, unsigned int slots, bool b3, int i4) {
    const GameGem &curGem = TheSongDB->GetGem(mTrackCfg.TrackNum(), gemID);
    curGem.GetSlots();
    bool burn = !curGem.IgnoreDuration();
    bool bonus = (i4 & 2) > 0;
    StopBurning(-1);
    for (int i = 0; i < mTrackCfg.GetMaxSlots(); i++) {
        if (slots & 1 << i) {
            GemSmasher *smasher = FindSmasher(i);
            MILO_ASSERT(smasher, 0xEC);
            if (!smasher->Null()) {
                if (b3) {
                    smasher->CodaHit();
                    if (burn)
                        smasher->CodaBurn();
                } else if (bonus) {
                    smasher->HitBonus();
                    if (burn)
                        smasher->BurnBonus();
                } else {
                    smasher->Hit();
                    if (burn)
                        smasher->Burn();
                }
            }
        }
    }
    if (burn)
        unk_0xc |= slots;
    mCurrentGem = gemID;
}

void NowBar::FillHit(int param1, int param2) {
    GemSmasher *smasher = FindSmasher(param1);
    MILO_ASSERT(smasher, 0x114);
    smasher->FillHit(param2);
}

void NowBar::PopSmasher(int slot) {
    if (slot == -1) {
        FOREACH (it, mSmashers) {
            (*it)->Miss();
        }
    } else {
        MILO_ASSERT_RANGE(slot, 0, mTrackCfg.GetMaxSlots(), 0x126);
        GemSmasher *smasher = FindSmasher(slot);
        if (smasher) {
            smasher->Miss();
        }
    }
}

void NowBar::SetSmasherGlowing(int slot, bool glowing) {
    if (slot == -1) {
        FOREACH (it, mSmashers) {
            (*it)->SetGlowing(glowing);
        }
    } else {
        MILO_ASSERT_RANGE(slot, 0, mTrackCfg.GetMaxSlots(), 0x13A);
        GemSmasher *smasher = FindSmasher(slot);
        if (smasher && !HandleOutOfRangeKey(smasher, slot, glowing)) {
            smasher->SetGlowing(glowing);
        }
    }
}

void NowBar::StopBurning(unsigned int index) {
    mCurrentGem = -1;

    if (unk_0xc != 0) {
        for (int i = 0; i < mTrackCfg.GetMaxSlots(); i++) {
            if (1 << i & index) {
                GemSmasher *smasher = FindSmasher(i);
                if (smasher)
                    smasher->StopBurn();
            }
        }
        unk_0xc &= ~index;
    }
}

GemSmasher *NowBar::FindSmasher(int index) const {
    if (index < mSmashers.size()) {
        return mSmashers[index];
    }
    return nullptr;
}

bool NowBar::HandleOutOfRangeKey(GemSmasher *smasher, int index, bool range) {
    if (mTrackCfg.IsKeyboardTrack() && !smasher->Showing()) {
        if (range) {
            if (index < mTrackCfg.GetMaxSlots() / 2) {
                mTrackDir->KeyMissLeft();
            } else {
                mTrackDir->KeyMissRight();
            }
        }
        return true;
    } else
        return false;
}