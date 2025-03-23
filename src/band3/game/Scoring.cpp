#include "Scoring.h"
#include "Defines.h"
#include "beatmatch/TrackType.h"
#include "decomp.h"
#include "game/MultiplayerAnalyzer.h"
#include "game/SongDB.h"
#include "obj/Data.h"
#include "os/System.h"
#include "os/Debug.h"

Scoring *TheScoring;

OverdriveConfig::OverdriveConfig(DataArray *cfg) {
    rechargeRate = cfg->FindFloat("recharge_rate");
    starPhrase = cfg->FindFloat("star_phrase");
    commonPhrase = cfg->FindFloat("common_phrase");
    fillBoost = cfg->FindFloat("fill_boost");
    whammyRate = cfg->FindFloat("whammy_rate");
    readyLevel = cfg->FindFloat("ready_level");
    multiplier = cfg->FindInt("multiplier");
    crowdBoost = cfg->FindFloat("crowd_boost");
    MILO_ASSERT_RANGE_EQ(rechargeRate, 0, 1, 0x22);
    MILO_ASSERT_RANGE_EQ(starPhrase, 0, 1, 0x23);
    MILO_ASSERT_RANGE_EQ(readyLevel, 0, 1, 0x24);
}

Scoring::Scoring()
    : mConfig(SystemConfig("scoring")), mOverdriveConfig(mConfig->FindArray("overdrive")),
      unkc0(0) {
    MILO_ASSERT(!TheScoring, 0x2C);
    TheScoring = this;

    mConfig->FindArray("points");
    DataArray *streakarr = mConfig->FindArray("streaks");
    DataArray *multarr = streakarr->FindArray("multipliers");
    DataArray *energyarr = streakarr->FindArray("energy");

    mCommonPhraseReward = mConfig->FindArray("unison_phrase")->FindFloat("reward");
    mCommonPhrasePenalty = mConfig->FindArray("unison_phrase")->FindFloat("penalty");
    InitializeStreakList(mStreakMultLists, multarr);
    InitializeStreakList(mStreakEnergyLists, energyarr);

    DataArray *pointarr = mConfig->FindArray("points");
    for (int i = 1; i < pointarr->Size(); i++) {
        int idx = SymToTrackType(pointarr->Array(i)->Sym(0));
        int head = pointarr->Array(i)->FindInt("head");
        int tail = pointarr->Array(i)->FindInt("tail");
        int chord = pointarr->Array(i)->FindInt("chord");
        mPointInfo[idx] = PointInfo(head, tail, chord);
    }
}

Scoring::~Scoring() {
    MILO_ASSERT(TheScoring, 0x48);
    TheScoring = nullptr;
}

// TODO: figure out what the DIM macro is actually supposed to do
#define DIM(x) 10U

#pragma push
#pragma pool_data off
void Scoring::ComputeStarThresholds(bool debug) const {
    std::vector<PlayerScoreInfo> &scoreinfos = TheSongDB->GetBaseScores();
    int i12 = 10;
    mStarThresholds.clear();
    DataArray *starRatings = mConfig->FindArray("star_ratings");

    DataArray *thresholds = starRatings->FindArray("new_instrument_thresholds");
    DataArray *newNumInstMults = starRatings->FindArray("new_num_instruments_multiplier");
    DataArray *newBonusThreshes = starRatings->FindArray("new_bonus_thresholds");

    float fb8[10];
    for (int i = 0; i < 10; i++)
        fb8[i] = 0;

    bool b1 = true;
    int i7 = 0;
    for (int i = 0; i < scoreinfos.size(); i++) {
        if (scoreinfos[i].mMaxStreakPts != 0) {
            i7++;
            if (scoreinfos[i].mDifficulty != kDifficultyExpert) {
                b1 = false;
            }
        }
    }

    float f16 = i7 == 0 ? 1 : newNumInstMults->Float(i7);

    if (debug) {
        MILO_LOG("                    base    bonus\n");
        for (int i = 0; i < scoreinfos.size(); i++) {
            Symbol trackSym = TrackTypeToSym(scoreinfos[i].mTrackType);
            MILO_LOG(
                "%15s%9d%9d\n",
                trackSym,
                scoreinfos[i].mMaxStreakPts,
                scoreinfos[i].mBonusPts
            );
        }
        MILO_LOG("\n");
    }

    for (int i = 0; i < scoreinfos.size(); i++) {
        Symbol trackSym = TrackTypeToSym(scoreinfos[i].mTrackType);
        DataArray *a = thresholds->FindArray(trackSym);
        MILO_ASSERT(a->Size() < DIM(thresholds), 0x8B);
        i12 = Min(i12, a->Size());
        scoreinfos[i].mSoloStarThresholds.clear();
        scoreinfos[i].mSoloStarThresholds.reserve(a->Size() + 1);
        scoreinfos[i].mSoloStarThresholds.push_back(0);
        if (debug)
            MILO_LOG("%15s", trackSym);
        for (int j = 1; j < a->Size(); j++) {
            float f15 = a->Float(j) * (float)scoreinfos[i].mMaxStreakPts;
            float f14 = newBonusThreshes->Float(j) * (float)scoreinfos[i].mBonusPts;
            int ic8 = f15 + f14;
            if (ic8 == 0)
                ic8 = 999999999;
            float add = f15 * f16 + f14;
            ;
            if (debug)
                MILO_LOG("%9d", (int)add);
            fb8[j] += add;
            scoreinfos[i].mSoloStarThresholds.push_back(ic8);
        }
        if (debug)
            MILO_LOG("\n");
    }
    if (debug)
        MILO_LOG("          TOTAL");

    mStarThresholds.push_back(0);
    for (int i = 1; i < i12; i++) {
        int icc = fb8[i];
        if (icc == 0)
            icc = 999999999;
        if (i >= 6 && !b1)
            icc = 999999999;
        if (debug)
            MILO_LOG("%9d", icc);
        mStarThresholds.push_back(icc);
    }
    if (debug)
        MILO_LOG("\n");
    PrintStarThresholds();
}
#pragma pop

void Scoring::InitializeStreakList(std::vector<StreakList> &streaks, DataArray *arr) {
    for (int i = 1; i < arr->Size(); i++) {
        DataArray *a = arr->Array(i);
        streaks.push_back(StreakList(a->Sym(0)));
        for (int j = 1; j < a->Size(); j++) {
            DataArray *a2 = a->Array(j);
            streaks.back().unk4.push_back(StreakItem(a2->Int(0), a2->Float(1)));
        }
    }
}

int Scoring::GetHeadPoints(TrackType instrument) const {
    MILO_ASSERT(instrument < kNumTrackTypes, 0xCA);
    return mPointInfo[instrument].headPoints;
}

int Scoring::GetTailPoints(TrackType instrument, int i) const {
    MILO_ASSERT(instrument < kNumTrackTypes, 0xD0);
    float f = ((float)i / 480.0f) * (float)mPointInfo[instrument].tailPoints;
    return Round(f);
}

int Scoring::GetChordPoints(TrackType instrument) const {
    MILO_ASSERT(instrument < kNumTrackTypes, 0xD7);
    return mPointInfo[instrument].chordPoints;
}

const Scoring::StreakList *
Scoring::GetStreakList(const std::vector<StreakList> &streaks, Symbol s) const {
    const StreakList *default_list = nullptr;
    for (int i = 0; i < streaks.size(); i++) {
        if (streaks[i].unk0 == s)
            return &streaks[i];
        else if (streaks[i].unk0 == "default") {
            default_list = &streaks[i];
        }
    }
    MILO_ASSERT(default_list, 0xEB);
    return default_list;
}

float Scoring::GetStreakData(int i1, Symbol s2, const std::vector<StreakList> &streaks)
    const {
    float f1 = 0;
    bool b2 = false;
    const std::vector<StreakItem> &items = GetStreakList(streaks, s2)->unk4;
    for (int i = 0; i < items.size(); i++) {
        if (i1 < items[i].unk0)
            break;
        f1 = items[i].unk4;
        b2 = true;
    }

    if (!b2) {
        MILO_FAIL("Scoring::GetStreakData failed %s %d\n", s2, i1);
    }
    return f1;
}

int Scoring::GetStreakMult(int i, Symbol s) const {
    return GetStreakData(i, s, mStreakMultLists);
}

float Scoring::GetPartialStreakFraction(int i1, Symbol s2) const {
    const std::vector<StreakItem> &items = GetStreakList(mStreakMultLists, s2)->unk4;
    int i5 = 0;
    for (int i = 0; i < items.size(); i++) {
        if (i1 < items[i].unk0) {
            return (float)(i1 - i5) / (float)(items[i].unk0 - i5);
        }
        i5 = items[i].unk0;
    }
    return 1;
}

DataArray *Scoring::GetCrowdConfig(Difficulty diff, BandUser *user) const {
    DataArray *diffarr = mConfig->FindArray("crowd")->FindArray(diff);
    Symbol key = user ? user->GetTrackSym() : "default";
    DataArray *ret = diffarr->FindArray(key, false);
    if (ret)
        return ret;
    else
        return diffarr->FindArray("default");
}

int Scoring::GetBandNumStars(int i) const {
    int stars = GetBandNumStarsFloat(i);
    if (stars < 0)
        return 0;
    else if (stars > 6)
        return 6;
    else
        return stars;
}

DECOMP_FORCEACTIVE(Scoring, "symbols")

float Scoring::GetNumStarsFloat(int i1, std::vector<int> &thresholds) const {
    MILO_ASSERT(!thresholds.empty(), 0x16C);
    if (i1 == 0)
        return 0;
    else {
        int i = thresholds.size();
        while (i >= 0) {
            int prev = i--;
            if (i1 >= thresholds[i]) {
                if (i < thresholds.size() - 1U) {
                    return i
                        + (float)(i1 - thresholds[i])
                        / (float)(thresholds[prev] / thresholds[i]);
                } else {
                    return i;
                }
            }
        }
        return 0;
    }
}

FORCE_LOCAL_INLINE
float Scoring::GetBandNumStarsFloat(int i) const {
    return GetNumStarsFloat(i, mStarThresholds);
}
END_FORCE_LOCAL_INLINE

int Scoring::GetBandScoreForStars(int stars) const {
    MILO_ASSERT(stars < mStarThresholds.size(), 0x18A);
    return mStarThresholds[stars];
}

int Scoring::GetSoloNumStars(int i1, TrackType ty) const {
    return GetSoloNumStarsFloat(i1, ty);
}

float Scoring::GetSoloNumStarsFloat(int i1, TrackType ty) const {
    PlayerScoreInfo *info = GetPlayerScoreInfo(ty);
    if (!info)
        return 0;
    else {
        float stars = GetNumStarsFloat(i1, info->mSoloStarThresholds);
        if (stars > 5.0f && info->mDifficulty != kDifficultyExpert) {
            stars = 5.0f;
        }
        return stars;
    }
}

int Scoring::GetSoloScoreForStars(int stars, TrackType ty) const {
    PlayerScoreInfo *info = GetPlayerScoreInfo(ty);
    if (!info)
        return 0;
    else {
        MILO_ASSERT(stars < info->mSoloStarThresholds.size(), 0x1A6);
        return info->mSoloStarThresholds[stars];
    }
}

PlayerScoreInfo *Scoring::GetPlayerScoreInfo(TrackType ty) const {
    std::vector<PlayerScoreInfo> &scores = TheSongDB->GetBaseScores();
    for (int i = 0; i < scores.size(); i++) {
        if (ty == scores[i].mTrackType) {
            return &scores[i];
        }
    }
    return nullptr;
}

Symbol Scoring::GetStarRating(int numStars) const {
    if (numStars == 0)
        return gNullStr;
    else {
        DataArray *ratings = mConfig->FindArray("star_ratings", "symbols")->Array(1);
        MILO_ASSERT_RANGE_EQ(numStars, 1,  ratings->Size(), 0x1BE);
        return ratings->Sym(numStars - 1);
    }
}

int Scoring::GetNotesPerMultiplier(Symbol s) const {
    const StreakList *streaks = GetStreakList(s);
    if (!streaks || streaks->unk4.size() <= 1)
        return 0;
    else
        return streaks->unk4[1].unk0;
}

void Scoring::GetSoloAward(int i, Symbol s, int &iref, Symbol &sref) {
    DataArray *soloblock = GetSoloBlock(s);
    DataArray *awardarr = soloblock->FindArray("awards");
    for (int idx = awardarr->Size() - 1; idx >= 1; idx--) {
        DataArray *arr = awardarr->Array(idx);
        if (i >= arr->Int(0)) {
            iref = arr->Int(1);
            sref = arr->Sym(2);
            return;
        }
    }
    MILO_FAIL("no solo award for %s: %i%%", s, i);
}

DataArray *Scoring::GetSoloBlock(Symbol s) const {
    DataArray *soloarr = mConfig->FindArray("solo");
    DataArray *blockarr = soloarr->FindArray(s, false);
    return blockarr ? blockarr : soloarr->FindArray("default");
}

float Scoring::GetSoloGemReward(Symbol s) {
    return GetSoloBlock(s)->FindArray("reward")->Float(1);
}

float Scoring::GetSoloGemPenalty(Symbol s) {
    return GetSoloBlock(s)->FindArray("penalty")->Float(1);
}

void Scoring::PrintStarThresholds() const {}
