#ifndef GAME_SCORING_H
#define GAME_SCORING_H
#include "beatmatch/TrackType.h"
#include "game/Defines.h"
#include "game/BandUser.h"
#include "obj/Data.h"
#include <vector>

class OverdriveConfig {
public:
    OverdriveConfig(DataArray*);

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
    PointInfo(int x = 0, int y = 0, int z = 0) : headPoints(x), tailPoints(y), chordPoints(z) {}
    int headPoints; // 0x0
    int tailPoints; // 0x4
    int chordPoints; // 0x8
};

class Scoring {
public:
    class StreakList {
    public:
    };

    Scoring();
    ~Scoring();

    PointInfo mPointInfo[10]; // 0xc
    std::vector<StreakList> unk78; // 0x78
    std::vector<StreakList> unk80; // 0x80
    int unk88;
    DataArray* unk8c;
    OverdriveConfig unk90; // 0x90
    float unkb0; // 0xb0
    float unkb4; // 0xb4
    mutable std::vector<int> mStarThresholds; // 0xb8
    int unkc0; // 0xc0

    int GetHeadPoints(TrackType) const;
    int GetTailPoints(TrackType, int) const;
    int GetChordPoints(TrackType) const;
    void InitializeStreakList(std::vector<StreakList>&, DataArray*);
    DataArray* GetCrowdConfig(Difficulty, BandUser*) const;
    float GetStreakData(int, Symbol, const std::vector<StreakList>&) const;
    int GetStreakMult(int, Symbol) const;
    int GetBandNumStars(int) const;
    float GetBandNumStarsFloat(int) const;
    float GetNumStarsFloat(int, std::vector<int>&) const;
    int GetBandScoreForStars(int) const;
    Symbol GetStarRating(int) const;
    DataArray* GetSoloBlock(Symbol) const;
    void GetSoloAward(int, Symbol, int&, Symbol&);
    float GetSoloGemReward(Symbol);
    float GetSoloGemPenalty(Symbol);
    void PrintStarThresholds() const;
};

extern Scoring* TheScoring;

#endif // GAME_SCORING_H