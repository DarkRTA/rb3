#ifndef GAME_STATS_H
#define GAME_STATS_H

#include <vector>
#include "system/utl/BinStream.h"

class Stats {
    class StreakInfo {
        StreakInfo();

    };

    class MultiplierInfo {
        MultiplierInfo();
    };

    class SectionInfo {
        SectionInfo();
    };

public:
    Stats();
    Stats(const Stats&);
    void BuildHitStreak(int, float);
    void GetCurrentStreak() const;
    void SetCurrentStreak(int);
    void GetLongestStreak() const;
    void SetPersistentStreak(int);
    void EndHitStreak();
    void BuildMissStreak(int);
    void EndMissStreak();
    void BuildStreak(Stats::StreakInfo&, int);
    void EndStreak(Stats::StreakInfo&, std::vector<Stats::StreakInfo>&);
    void SetFinalized(bool);
    void UpdateBestSolo(int);
    void SetSoloButtonedSoloPercentage(int);
    void SetVocalSingerAndPartCounts(int, int);
    void SetSingerPartPercentage(int, int, float);
    void GetSingerRankedPercentage(int, int) const;
    void GetSingerRankedPart(int, int) const;
    void SetSingerPitchDeviationInfo(int, float, float);
    void UpdateBestTambourineSection(int);
    void SaveForEndGame(BinStream&) const;
    void LoadForEndGame(BinStream&);
    void SaveSingerStats(BinStream&) const;
    void LoadSingerStats(BinStream&);
    void AddAccuracy(int);
    void AddOverdrive(float);
    void AddSolo(int);
    void AddSustain(float);
    void AddScoreStreak(float);
    void AddBandContribution(float);
    void AddCodaPoints(int);
    void AddTambourine(float);
    void AddHarmony(int);
    int GetAccuracy() const;
    float GetOverdrive() const;
    int GetSolo() const;
    void GetSustain() const;
    void GetScoreStreak() const;
    void GetBandContribution() const;
    void GetCodaPoints() const;
    void GetTambourine() const;
    void GetHarmony() const;
    void SetNoScorePercent(float);
    void FailedNoScore() const;
    void AddFailurePoint(float);
    void AddToPlayersSaved(int, float);
    void AddToTimesSaved(float, float);
    void DeployOverdrive(float, int);
    void StopDeployingOverdrive(float, int);
    void BeginStreakMultiplier(float, int);
    void EndStreakMultiplier(float, int);
    void BeginMultiplier(Stats::MultiplierInfo&, float, int, float);
    void EndMultiplier(Stats::MultiplierInfo&, std::vector<Stats::MultiplierInfo>&, float, int, float, float&);
    void GetUnisonPhrasePercent() const;
    void SetHopoGemInfo(int, int, int);
    void IncrementHighFretGemsHit(bool);
    void IncrementSustainGemsHit(bool);
    void AddRoll(bool);
    void IncrementTrillsHit(bool);
    void SetCymbalGemInfo(int, int, int);
    void SetSectionInfo(int, Symbol, float, float);
    void GetSectionInfo(int) const;
    void GetAverageMsError() const;


    // These are implemented in Performer
    void GetDoubleHarmonyHit() const;
    void GetDoubleHarmonyPhraseCount() const;
    void GetTripleHarmonyHit() const;
    void GetTripleHarmonyPhraseCount() const;
    int GetHitCount() const;
    void GetNotesHitFraction() const;
    void GetNumberOfSingers() const;
    void GetVocalPartPercentage(int) const;
    void GetFailedDeploy() const;
    void GetPlayersSaved() const;
    void GetFillHitCount() const;
    void GetStrummedDown() const;
    void GetStrummedUp() const;
    void GetDeployCount() const;
    void GetSoloPercentage() const;
    void GetPerfectSoloWithSoloButtons() const;
    void GetFinalized() const;

    // These are implemented in PerformanceData
    void AccessPerformanceAwards();
    void SetEndGameScore(int);
    void SetNotesHitFraction(float);
    void SetHitCount(int);
    void SetMissCount(int);
    void AccessFailurePoints();
    void AccessSavedPoints();
    void AccessClosestTimesSaved();
    void AccessClosestPlayersSaved();
    void SetTimesSaved(int);
    void SetPlayersSaved(int);
    void AccessCurrentStreakInfo();
    void SetEndGameOverdrive(float);
    void SetEndGameCrowdLevel(float);
    void SetCodaPoints(int);
    void SetOverdrivePhrasesCompleted(int);
    void SetOverdrivePhraseCount(int);
    void SetUnisonPhrasesCompleted(int);
    void SetUnisonPhraseCount(int);
    void AccessBestSolos();
    void SetHitStreakCount(int);
    void AccessHitStreak(int);
    void SetMissStreakCount(int);
    void AccessMissStreak(int);
    void SetBestOverdriveDeploymentsCount(int);
    void AccessBestOverdriveDeployment(int);
    void SetBestStreakMultipliersCount(int);
    void AccessBestStreakMultiplier(int);
    void SetTotalOverdriveDuration(float);
    void SetTotalMultiplierDuration(float);
    void SetRollsHitCompletely(int);
    void SetRollCount(int);
    void SetHighGemsHitHigh(int);
    void SetHighGemsHitLow(int);
    void SetHighFretGemCount(int);
    void SetSustainGemsHitCompletely(int);
    void SetSustainGemsHitPartially(int);
    void SetSustainGemCount(int);
    void SetTrillsHitCompletely(int);
    void SetTrillsHitPartially(int);
    void SetTrillCount(int);
    void SetDoubleHarmonyHit(int);
    void SetDoubleHarmonyPhraseCount(int);
    void SetTripleHarmonyHit(int);
    void SetTripleHarmonyPhraseCount(int);
    void AccessSingerStats(int);


    int mHitCount;   // 0x00
    int mMissCount;  // 0x04
    int m0x08;
    int m0x0c;
    int m0x10;
    int m0x14;
    float mNotesHitFraction; // 0x18
    int m0x1c;
    int m0x20;
    int m0x24;
    int m0x28;
    int m0x2c;
    int m0x30;
    int m0x34;
    int m0x38;
    int m0x3c;
    int m0x40;
    int m0x44;
    int m0x48;
    int mDoubleHarmonyHit; // 0x4c
    int mDoubleHarmonyPhraseCount; // 0x50
    int mTripleHarmonyHit; // 0x54
    int mTripleHarmonyPhraseCount; // 0x58
    int m0x5c;
    int m0x60;
    int m0x64;
    int m0x68;
    int m0x6c;
    int m0x70;
    int m0x74;
    int m0x78;
    int m0x7c;
    int m0x80;
    int m0x84;
    int mAccuracy; // 0x88
    int m0x8c;
    int mSolo; // 0x90
    float mOverdrive; // 0x94
    int m0x98;
    // band contribution 0xa0

    int mCodaPoints; // 0xa4
    int mCurrentStreak; // 0xc0

    int mPlayersSaved; // 0xec
    int mTimesSaved; // 0xf8

    float mOverdriveDuration; // 0x128

    float mMultiplierDuration; // 0x148

    int mEndGameScore; // 0x154
    float mEndGameCrowdLevel; // 0x158
    float mEndGameOverdrive; // 0x15c
    int mOverdrivePhrasesCompleted; // 0x160
    int mOverdrivePhraseCount; // 0x164
    int mUnisonPhraseCompleted; // 0x168
    int mUnisonPhraseCount; // 0x16c
    int mHopoGemInfo1; // 0x170
    int mHopoGemInfo2; // 0x174
    int mHopoGemInfo3; // 0x178
    int mHighGemsHitHigh; // 0x17c
    int mHighGemsHitLow; // 0x180
    int mHighFretGemCount; // 0x184
    int mSustainGemsHitCompletely; // 0x188
    int mSustainGemsHitPartially; // 0x18c
    int mSustainGemCount; // 0x190

    int mRollCount; // 0x198
    int mRollsHitCompletely; // 0x19c

    int mTrillsHitCompletely; // 0x1a4
    int mTrillsHitPartially; // 0x1a8

    int mTrillCount; // 0x1a0

    int mSymbolGemInfo1; // 0x1ac
    int mSymbolGemInfo2; // 0x1b0
    int mSymbolGemInfo3; // 0x1b4

    bool mMultiplierActive; // 0x205
};

class SingerStats {
    SingerStats(int);
    void Finalize();
    void SetPartPercentage(int, float);
    void GetRankData(int) const;
    void SetPitchDeviationInfo(float, float);
    void GetPitchDeviationInfo(float&, float&) const;

    float mPitchDeviation1; // 0x08
    float mPitchDeviation2; // 0x0c

};

#endif // GAME_STATS_H
