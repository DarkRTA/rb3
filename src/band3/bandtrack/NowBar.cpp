#include "NowBar.h"

#include "game/FretHand.h"
#include "system/beatmatch/GameGem.h"

NowBar::NowBar(TrackDir *trackDir, const TrackConfig &trackConfig)
    : mSmashers(), unk_0x8(-1), unk_0xc(0), mTrackDir(trackDir),
      mTrackConfig(&trackConfig) {
    MILO_ASSERT(trackDir != 0, 0x1e);
    MILO_ASSERT(mSmashers[0] != 0, 0x21);

    Symbol type = mTrackConfig->Type();
    Symbol symbol1 = ("smashers");
    Symbol symbol2 = ("track_graphics");
}

void NowBar::Poll(float, bool) {}

void NowBar::Reset(bool reset) {
    for (int i = 0; i < mSmashers.size(); i++) {
        mSmashers[i]->Reset(reset);
    }

    unk_0xc = 0;
}

void NowBar::Hit(float fParam1, int iParam2, bool bParam3, int iParam4, bool bParam5) {
    int trackNum = mTrackConfig->TrackNum();

    GameGem *gameGem = 0;

    uint slots = gameGem->mSlots;

    int trackVar = mTrackConfig->IsDrumTrack();
    uint gameCymbalLanes;

    bool bVar = false;
    if (trackNum == 0 && !gameGem->mShowSlashes && gameGem->LeftHandSlide()) {
        bVar = true;
    }

    int trackNum2 = mTrackConfig->TrackNum();
    int totalGems = trackNum2;
    bool bVar2 = false;
    if (trackVar != 0) {
        if (gameGem->mShowChordNames
            && ((gameCymbalLanes = mTrackConfig->GetGameCymbalLanes()) & slots) != 0) {
            bVar2 = true;
        } else {
            bVar = true;
        }
    }

    trackVar = mTrackConfig->AllowsOverlappingGems();

    if (!trackVar != 0) {
        StopBurning(0xffffffff);
    }

    for (int i = 0; i < mTrackConfig->GetMaxSlots(); i++) {
        trackVar = mTrackConfig->GetMaxSlots();
        if (trackVar <= (int)i) {
            break;
        }
        if (((slots & 1 << i) != 0)
            && ((!bParam5 || (trackVar = gameGem->GetRGNoteType(i), trackVar != 1)))) {
            GemSmasher *gemSmasher = FindSmasher(i);
            MILO_ASSERT(gemSmasher != 0, 0x71);

            trackVar = gemSmasher->Null();
            if (trackVar == 0) {
                if (!bParam3) {
                    if ((int)(-(iParam4 & 2U) & ~(iParam4 & 2U)) < 0) {
                        if (!bParam5) {
                            if (bVar2) {
                                gemSmasher->HitDrumBonus();
                            } else if (bVar2) {
                                gemSmasher->HitCymbalBonus();
                            } else {
                                gemSmasher->HitBonus();
                            }
                        } else {
                            gemSmasher->HitChordBonus();
                        }
                        if (bVar) {
                            gemSmasher->BurnBonus();
                        }
                    } else if (!bParam5) {
                        if (bVar2) {
                            gemSmasher->HitDrum();
                        } else if (bVar2) {
                            gemSmasher->HitCymbal();
                        } else {
                            gemSmasher->Hit();
                        }
                        if (bVar) {
                            gemSmasher->Burn();
                        }
                    } else {
                        gemSmasher->HitChord();
                        if (bVar) {
                            gemSmasher->BurnChord();
                        }
                    }
                } else if (!bParam5) {
                    gemSmasher->CodaHit();
                    if (bVar) {
                        gemSmasher->CodaBurn();
                    }
                } else {
                    gemSmasher->CodaHitChord();
                    if (bVar) {
                        gemSmasher->CodaBurnChord();
                    }
                }
            }
        }
    }

    if (bVar) {
        unk_0xc |= slots;
    }
    unk_0x8 = iParam2;
    return;
}

void NowBar::Miss(float param1, int param2) {
    bool inRange = false;

    if (0 <= param2 && param2 < mTrackConfig->GetMaxSlots()) {
        inRange = true;
    }

    MILO_ASSERT(inRange, 0xba);

    GemSmasher *smasher = FindSmasher(param2);

    if (smasher != 0 && !HandleOutOfRangeKey(smasher, param2, false)) {
        smasher->Miss();

        bool isKeyboard = mTrackConfig->IsKeyboardTrack();

        if (!isKeyboard) {
            for (int i = 0; i < mSmashers.size(); i++) {
                GemSmasher *smasherVec = mSmashers[i];

                if (smasherVec != smasher && smasherVec->Glowing()) {
                    smasherVec->Miss();
                }
            }
        }
    }
    unk_0x8 = -1;
}

void NowBar::PopSmasher(int param1) {
    if (param1 == -1) {
        for (int i = 0; i < mSmashers.size(); i++) {
            mSmashers[i]->Miss();
        }
    } else {
        bool inRange = false;

        if (0 <= param1 && param1 < mTrackConfig->GetMaxSlots()) {
            inRange = true;
        }

        MILO_ASSERT(inRange, 0x126);

        GemSmasher *smasher = FindSmasher(param1);

        if (smasher != 0) {
            smasher->Miss();
        }
    }
}

void NowBar::FillHit(int param1, int param2) {
    GemSmasher *smasher = FindSmasher(param1);
    MILO_ASSERT(smasher != 0, 0x114);

    smasher->FillHit(param2);
}

void NowBar::SetSmasherGlowing(int param1, bool glowing) {
    if (param1 == -1) {
        for (int i = 0; i < mSmashers.size(); i++) {
            mSmashers[i]->SetGlowing(glowing);
        }
    } else {
        bool inRange = false;

        if (0 <= param1 && param1 < mTrackConfig->GetMaxSlots()) {
            inRange = true;
        }

        MILO_ASSERT(inRange, 0x13a);

        GemSmasher *smasher = FindSmasher(param1);

        if (smasher != 0 && !HandleOutOfRangeKey(smasher, param1, glowing)) {
            smasher->SetGlowing(glowing);
        }
    }
}

void NowBar::StopBurning(unsigned int index) {
    unk_0x8 = -1;

    if (unk_0xc != 0) {
        int i = 0;
        while (true) {
            int slots = mTrackConfig->GetMaxSlots();

            if (slots <= i) {
                break;
            }

            if ((1 << i) & index != 0) {
                GemSmasher *smasher = FindSmasher(i);
                if (smasher != 0) {
                    smasher->StopBurn();
                }
            }

            i++;
        }
        unk_0xc &= ~index;
    }
}

GemSmasher *NowBar::FindSmasher(int index) const {
    if (index < mSmashers.size()) {
        return mSmashers[index];
    }
    return 0;
}

bool NowBar::HandleOutOfRangeKey(GemSmasher *smasher, int index, bool range) {
    bool isKeyboard = mTrackConfig->IsKeyboardTrack();

    bool outOfRange;
    if (!isKeyboard || smasher->Showing()) {
        outOfRange = false;
    } else {
        if (range) {
            mTrackDir->KeyMissLeft();
        } else {
            mTrackDir->KeyMissRight();
        }
        outOfRange = true;
    }

    return outOfRange;
}