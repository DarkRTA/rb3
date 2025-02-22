#pragma once
#include "beatmatch/TrackType.h"
#include "game/Defines.h"
#include "game/BandUser.h"
#include "game/MultiplayerAnalyzer.h"
#include "obj/Data.h"
#include <vector>

class OverdriveConfig {
public:
    OverdriveConfig(DataArray *);

    float rechargeRate; // 0x0
    float starPhrase; // 0x4
    float commonPhrase; // 0x8
    float fillBoost; // 0xc
    float whammyRate; // 0x10
    float readyLevel; // 0x14
    int multiplier; // 0x18
    float crowdBoost; // 0x1c
};

// idk the name
class PointInfo {
public:
    PointInfo(int x = 0, int y = 0, int z = 0)
        : headPoints(x), tailPoints(y), chordPoints(z) {}
    int headPoints; // 0x0
    int tailPoints; // 0x4
    int chordPoints; // 0x8
};

class Scoring {
public:
    class StreakItem {
    public:
        StreakItem(int i, float f) : unk0(i), unk4(f) {}
        int unk0;
        float unk4;
    };

    class StreakList {
    public:
        StreakList(Symbol s) : unk0(s) {}

        Symbol unk0;
        std::vector<StreakItem> unk4;
    };

    Scoring();
    ~Scoring();

    int GetHeadPoints(TrackType) const;
    int GetTailPoints(TrackType, int) const;
    int GetChordPoints(TrackType) const;
    void InitializeStreakList(std::vector<StreakList> &, DataArray *);
    DataArray *GetCrowdConfig(Difficulty, BandUser *) const;
    float GetStreakData(int, Symbol, const std::vector<StreakList> &) const;
    int GetStreakMult(int, Symbol) const;
    int GetBandNumStars(int) const;
    float GetBandNumStarsFloat(int) const;
    float GetNumStarsFloat(int, std::vector<int> &) const;
    int GetBandScoreForStars(int) const;
    Symbol GetStarRating(int) const;
    DataArray *GetSoloBlock(Symbol) const;
    void GetSoloAward(int, Symbol, int &, Symbol &);
    float GetSoloGemReward(Symbol);
    float GetSoloGemPenalty(Symbol);
    void PrintStarThresholds() const;
    int GetSoloNumStars(int, TrackType) const;
    float GetSoloNumStarsFloat(int, TrackType) const;
    int GetSoloScoreForStars(int, TrackType) const;
    void ComputeStarThresholds(bool) const;
    float GetPartialStreakFraction(int, Symbol) const;
    const StreakList *GetStreakList(const std::vector<StreakList> &, Symbol) const;
    PlayerScoreInfo *GetPlayerScoreInfo(TrackType) const;
    int GetNotesPerMultiplier(Symbol) const;
    const StreakList *GetStreakList(Symbol s) const {
        return GetStreakList(mStreakMultLists, s);
    }

    PointInfo mPointInfo[10]; // 0xc
    std::vector<StreakList> mStreakMultLists; // 0x78
    std::vector<StreakList> mStreakEnergyLists; // 0x80
    int unk88;
    DataArray *mConfig; // 0x8c
    OverdriveConfig mOverdriveConfig; // 0x90
    float mCommonPhraseReward; // 0xb0
    float mCommonPhrasePenalty; // 0xb4
    mutable std::vector<int> mStarThresholds; // 0xb8
    int unkc0; // 0xc0
};

extern Scoring *TheScoring;
