#include "Scoring.h"
#include "beatmatch/TrackType.h"
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
    : mConfig(SystemConfig("scoring")),
      mOverdriveConfig(mConfig->FindArray("overdrive", true)), unkc0(0) {
    MILO_ASSERT(!TheScoring, 0x2C);
    TheScoring = this;

    mConfig->FindArray("points", true);
    DataArray *streakarr = mConfig->FindArray("streaks", true);
    DataArray *multarr = streakarr->FindArray("multipliers", true);
    DataArray *energyarr = streakarr->FindArray("energy", true);

    mCommonPhraseReward = mConfig->FindArray("unison_phrase", true)->FindFloat("reward");
    mCommonPhrasePenalty =
        mConfig->FindArray("unison_phrase", true)->FindFloat("penalty");
    InitializeStreakList(mStreakMultLists, multarr);
    InitializeStreakList(mStreakEnergyLists, energyarr);

    DataArray *pointarr = mConfig->FindArray("points", true);
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
    DataArray *starRatings = mConfig->FindArray("star_ratings", true);

    DataArray *thresholds = starRatings->FindArray("new_instrument_thresholds", true);
    DataArray *newNumInstMults =
        starRatings->FindArray("new_num_instruments_multiplier", true);
    DataArray *newBonusThreshes = starRatings->FindArray("new_bonus_thresholds", true);

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
        DataArray *a = thresholds->FindArray(trackSym, true);
        MILO_ASSERT(a->Size() < DIM(thresholds), 0x8B);
        i12 = Min(i12, a->Size());
        scoreinfos[i].unk14.clear();
        scoreinfos[i].unk14.reserve(a->Size() + 1);
        scoreinfos[i].unk14.push_back(0);
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
            scoreinfos[i].unk14.push_back(ic8);
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

int Scoring::GetStreakMult(int i, Symbol s) const {
    return GetStreakData(i, s, mStreakMultLists);
}

DataArray *Scoring::GetCrowdConfig(Difficulty diff, BandUser *user) const {
    DataArray *diffarr = mConfig->FindArray("crowd", true)->FindArray(diff, true);
    Symbol key = user ? user->GetTrackSym() : "default";
    DataArray *ret = diffarr->FindArray(key, false);
    if (ret)
        return ret;
    else
        return diffarr->FindArray("default", true);
}

int Scoring::GetBandNumStars(int i) const {
    int stars = GetNumStarsFloat(i, const_cast<Scoring *>(this)->mStarThresholds);
    if (stars < 0)
        return 0;
    else if (stars > 6)
        return 6;
    else
        return stars;
}

float Scoring::GetBandNumStarsFloat(int i) const {
    return GetNumStarsFloat(i, const_cast<Scoring *>(this)->mStarThresholds);
}

int Scoring::GetBandScoreForStars(int stars) const {
    MILO_ASSERT(stars < mStarThresholds.size(), 0x18A);
    return mStarThresholds[stars];
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

void Scoring::GetSoloAward(int i, Symbol s, int &iref, Symbol &sref) {
    DataArray *soloblock = GetSoloBlock(s);
    DataArray *awardarr = soloblock->FindArray("awards", true);
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
    DataArray *soloarr = mConfig->FindArray("solo", true);
    DataArray *blockarr = soloarr->FindArray(s, false);
    return blockarr ? blockarr : soloarr->FindArray("default", true);
}

float Scoring::GetSoloGemReward(Symbol s) { return GetSoloBlock(s)->FindFloat("reward"); }

float Scoring::GetSoloGemPenalty(Symbol s) {
    return GetSoloBlock(s)->FindFloat("penalty");
}

void Scoring::PrintStarThresholds() const {}
