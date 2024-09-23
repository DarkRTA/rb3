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
    int GetCurrentStreak() const;
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
    float GetSustain() const;
    float GetScoreStreak() const;
    float GetBandContribution() const;
    int GetCodaPoints() const;
    float GetTambourine() const;
    int GetHarmony() const;
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
    int GetDoubleHarmonyHit() const;
    int GetDoubleHarmonyPhraseCount() const;
    int GetTripleHarmonyHit() const;
    int GetTripleHarmonyPhraseCount() const;
    int GetHitCount() const;
    float GetNotesHitFraction() const;
    int GetNumberOfSingers() const;
    void GetVocalPartPercentage(int) const;
    bool GetFailedDeploy() const;
    int GetPlayersSaved() const;
    int GetFillHitCount() const;
    void GetStrummedDown() const;
    void GetStrummedUp() const;
    int GetDeployCount() const;
    int GetSoloPercentage() const;
    bool GetPerfectSoloWithSoloButtons() const;
    bool GetFinalized() const;

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

    int mHitCount;                             // 0x000
    int mMissCount;                            // 0x004
    int m0x08;                                 // 0x008
    int m0x0c;                                 // 0x00c
    int m0x10;                                 // 0x010
    int m0x14;                                 // 0x014
    float mNotesHitFraction;                   // 0x018
    bool mFailedDeploy;                        // 0x01c
    int mDeployCount;                          // 0x020
    int mFillHitCount;                         // 0x024
    int m0x28;                                 // 0x028
    int m0x2c;                                 // 0x02c
    int m0x30;                                 // 0x030
    bool m0x34;                                // 0x034
    bool mFinalized;                           // 0x035
    int mSoloPercentage;                       // 0x038
    int m0x3c;                                 // 0x03c
    bool mPerfectSoloWithSoloButtons;          // 0x040
    bool m0x41;                                // 0x041
    int mNumberOfSingers;                      // 0x044
    int m0x48;                                 // 0x048
    int mDoubleHarmonyHit;                     // 0x04c
    int mDoubleHarmonyPhraseCount;             // 0x050
    int mTripleHarmonyHit;                     // 0x054
    int mTripleHarmonyPhraseCount;             // 0x058
    int m0x5c;                                 // 0x05c
    int m0x60;                                 // 0x060
    int m0x64;                                 // 0x064
    int m0x68;                                 // 0x068
    int m0x6c;                                 // 0x06c
    std::vector<int> m0x70;                    // 0x070
    std::vector<int> m0x78;                    // 0x078
    std::vector<int> m0x80;                    // 0x080
    int mAccuracy; // 0x88
    int m0x8c;
    int mSolo; // 0x90
    float mOverdrive; // 0x94
    float mSustain;           // 0x98
    float mScoreStreak;       // 0x9c
    float mBandContribution;  // 0xa0
    int mCodaPoints; // 0xa4
    bool m0xa8;       // 0xa8
    bool m0x09;        // 0xa9
    float mTambourine; // 0xac
    int mHarmony; // 0xb0
    bool m0xb4;
    int m0xb8;
    int m0xbc;
    int mCurrentStreak; // 0xc0
    int m0xc4;
    int m0xc8;
    int m0xcc;
    int m0xd0;
    int m0xd4;
    int m0xd8;
    int m0xdc;
    int m0xe0;
    int m0xe4;
    int m0xe8;
    int mPlayersSaved; // 0xec
    int m0xf0;
    int m0xf4;
    int mTimesSaved; // 0xf8
    int m0xfc;
    int m0x100;
    int m0x104;
    int m0x108;
    int m0x10c;
    int m0x110;
    int m0x114;
    int m0x118;
    int m0x11c;
    int m0x120;
    int m0x124;
    float mTotalOverdriveDuration; // 0x128
    int m0x12c;
    int m0x130;
    int m0x134;
    int m0x138;
    int m0x13c;
    int m0x140;
    int m0x144;
    float mTotalMultiplierDuration; // 0x148
    int m0x14c;
    int m0x150;
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
    int m0x194;
    int mRollCount; // 0x198
    int mRollsHitCompletely; // 0x19c
    int mTrillCount; // 0x1a0
    int mTrillsHitCompletely; // 0x1a4
    int mTrillsHitPartially; // 0x1a8
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
