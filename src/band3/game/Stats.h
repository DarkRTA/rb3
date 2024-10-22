#ifndef GAME_STATS_H
#define GAME_STATS_H
#include <vector>
#include "system/utl/BinStream.h"
#include "os/Debug.h"

class SingerStats {
public:
    SingerStats(int);
    void Finalize();
    void SetPartPercentage(int, float);
    void GetRankData(int) const;
    void SetPitchDeviationInfo(float, float);
    void GetPitchDeviationInfo(float&, float&) const;

    std::vector<std::pair<int, float> > unk0; // 0x0
    float mPitchDeviation1; // 0x08
    float mPitchDeviation2; // 0x0c

};

class Stats {
public:
    class StreakInfo {
    public:
        StreakInfo();

        bool operator>(const StreakInfo& s){
            return mDuration > s.mDuration;
        }

        int mStart; // 0x0
        int mDuration; // 0x4
    };

    class MultiplierInfo {
    public:
        MultiplierInfo();

        float mStartMs; // 0x0
        float mDurationMs; // 0x4
        int mStartingMultiplier; // 0x8
        int mEndingMultiplier; // 0xc
        float mPoints; // 0x10
    };

    class SectionInfo {
    public:
        SectionInfo();

        Symbol unk0; // 0x0
        float unk4; // 0x4
        float unk8; // 0x8
    };

    Stats();
    Stats(const Stats& s);


    // Stats::Stats(const Stats& s) : mHitCount(s.mHitCount), mMissCount(s.mMissCount), m0x08(s.m0x08), m0x0c(s.m0x0c), mPersistentStreak(s.mPersistentStreak), mLongestPersistentStreak(s.mLongestPersistentStreak),
    //     mNotesHitFraction(s.mNotesHitFraction), mFailedDeploy(s.mFailedDeploy), mDeployCount(s.mDeployCount), mFillHitCount(s.mFillHitCount), m0x28(s.m0x28), m0x2c(s.m0x2c), m0x30(s.m0x30), m0x34(s.m0x34),
    //     mFinalized(s.mFinalized), mSoloPercentage(s.mSoloPercentage), mSoloButtonedSoloPercentage(s.mSoloButtonedSoloPercentage), mPerfectSoloWithSoloButtons(s.mPerfectSoloWithSoloButtons), m0x41(s.m0x41),
    //     mNumberOfSingers(s.mNumberOfSingers), m0x48(s.m0x48), mDoubleHarmonyHit(s.mDoubleHarmonyHit), mDoubleHarmonyPhraseCount(s.mDoubleHarmonyPhraseCount), mTripleHarmonyHit(s.mTripleHarmonyHit),
    //     mTripleHarmonyPhraseCount(s.mTripleHarmonyPhraseCount), m0x5c(s.m0x5c), m0x60(s.m0x60), m0x64(s.m0x64), m0x68(s.m0x68), m0x6c(s.m0x6c), m0x70(s.m0x70), mSingerStats(s.mSingerStats), mAccessPerformanceAwards(s.mAccessPerformanceAwards),
    //     mAccuracy(s.mAccuracy), m0x8c(s.m0x8c), mSolo(s.mSolo), mOverdrive(s.mOverdrive), mSustain(s.mSustain), mScoreStreak(s.mScoreStreak), mBandContribution(s.mBandContribution),
    //     mCodaPoints(s.mCodaPoints), m0xa8(s.m0xa8), m0x09(s.m0x09), mTambourine(s.mTambourine), mHarmony(s.mHarmony), mFullCombo(s.mFullCombo), mNoScorePercent(s.mNoScorePercent), mCurrentHitStreak(s.mCurrentHitStreak) {

    // }

    ~Stats(){}
    void BuildHitStreak(int, float);
    int GetCurrentStreak() const;
    void SetCurrentStreak(int);
    int GetLongestStreak() const;
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
    float GetSingerRankedPercentage(int, int) const;
    int GetSingerRankedPart(int, int) const;
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
    bool FailedNoScore() const;
    void AddFailurePoint(float);
    void AddToPlayersSaved(int, float);
    void AddToTimesSaved(float, float);
    void DeployOverdrive(float, int);
    void StopDeployingOverdrive(float, int);
    void BeginStreakMultiplier(float, int);
    void EndStreakMultiplier(float, int);
    void BeginMultiplier(Stats::MultiplierInfo&, float, int, float);
    void EndMultiplier(Stats::MultiplierInfo&, std::vector<Stats::MultiplierInfo>&, float, int, float, float&);
    int GetUnisonPhrasePercent() const;
    void SetHopoGemInfo(int, int, int);
    void IncrementHighFretGemsHit(bool);
    void IncrementSustainGemsHit(bool);
    void AddRoll(bool);
    void IncrementTrillsHit(bool);
    void SetCymbalGemInfo(int, int, int);
    void SetSectionInfo(int, Symbol, float, float);
    const SectionInfo& GetSectionInfo(int) const;
    void GetAverageMsError() const;

    int GetDoubleHarmonyHit() const { return mDoubleHarmonyHit; }
    int GetDoubleHarmonyPhraseCount() const { return mDoubleHarmonyPhraseCount; }
    int GetTripleHarmonyHit() const { return mTripleHarmonyHit; }
    int GetTripleHarmonyPhraseCount() const { return mTripleHarmonyPhraseCount; }
    int GetHitCount() const { return mHitCount; }
    float GetNotesHitFraction() const { return mNotesHitFraction; }
    int GetNumberOfSingers() const { return mNumberOfSingers; }
    float GetVocalPartPercentage(int i) const { return m0x70[i]; }
    bool GetFailedDeploy() const { return mFailedDeploy; }
    int GetPlayersSaved() const { return mPlayersSaved; }
    int GetFillHitCount() const { return mFillHitCount; }
    bool GetStrummedDown() const { return m0x2c > 0; }
    bool GetStrummedUp() const { return m0x28 > 0; }
    int GetDeployCount() const { return mDeployCount; }
    int GetSoloPercentage() const { return mSoloPercentage; }
    bool GetPerfectSoloWithSoloButtons() const { return mPerfectSoloWithSoloButtons; }
    bool GetFinalized() const { return mFinalized; }

    // These are implemented in PerformanceData
    std::vector<Symbol>& AccessPerformanceAwards(){ return mAccessPerformanceAwards; }
    void SetEndGameScore(int endGameScore) { mEndGameScore = endGameScore; }
    void SetNotesHitFraction(float notesHitFraction) { mNotesHitFraction = notesHitFraction; }
    void SetHitCount(int hitCount) { mHitCount = hitCount; }
    void SetMissCount(int missCount) { mMissCount = missCount; }
    std::vector<float>& AccessFailurePoints(){ return mFailurePoints; }
    std::vector<float>& AccessSavedPoints(){ return mSavedPoints; }
    std::vector<float>& AccessClosestTimesSaved(){ return mClosestTimesSaved; }
    std::vector<float>& AccessClosestPlayersSaved(){ return mClosestPlayersSaved; }
    StreakInfo& AccessCurrentStreakInfo(){ return mCurrentHitStreak; }
    std::vector<int>& AccessBestSolos(){ return mBestSolos; }
    StreakInfo& AccessHitStreak(int index){
        MILO_ASSERT_RANGE(index, 0, mHitStreaks.size(), 0x1C5);
        return mHitStreaks[index];
    }
    StreakInfo& AccessMissStreak(int index){
        MILO_ASSERT_RANGE(index, 0, mMissStreaks.size(), 0x1D3);
        return mMissStreaks[index];
    }
    MultiplierInfo& AccessBestOverdriveDeployment(int index){
        MILO_ASSERT_RANGE(index, 0, mBestOverdriveDeployments.size(), 0x1E1);
        return mBestOverdriveDeployments[index];
    }
    MultiplierInfo& AccessBestStreakMultiplier(int index){
        MILO_ASSERT_RANGE(index, 0, mBestStreakMultipliers.size(), 0x1EF);
        return mBestStreakMultipliers[index];
    }
    SingerStats& AccessSingerStats(int index){
        MILO_ASSERT_RANGE(index, 0, mSingerStats.size(), 0xC6);
        return mSingerStats[index];
    }
    void SetTimesSaved(int timesSaved) { mTimesSaved = timesSaved; }
    void SetPlayersSaved(int playersSaved) { mPlayersSaved = playersSaved; }
    void SetEndGameOverdrive(float endGameOverdrive) { mEndGameOverdrive = endGameOverdrive; }
    void SetEndGameCrowdLevel(float endGameCrowdLevel) { mEndGameCrowdLevel = endGameCrowdLevel; }
    void SetCodaPoints(int codaPoints) { mCodaPoints = codaPoints; }
    void SetOverdrivePhrasesCompleted(int overdrivePhrasesCompleted) { mOverdrivePhrasesCompleted = overdrivePhrasesCompleted; }
    void SetOverdrivePhraseCount(int overdrivePhraseCount) { mOverdrivePhraseCount = overdrivePhraseCount; }
    void SetUnisonPhrasesCompleted(int unisonPhrasesCompleted) { mUnisonPhraseCompleted = unisonPhrasesCompleted; }
    void SetUnisonPhraseCount(int unisonPhraseCount) { mUnisonPhraseCount = unisonPhraseCount; }
    void SetHitStreakCount(int hitStreakCount) { mHitStreaks.resize(hitStreakCount); }
    void SetMissStreakCount(int missStreakCount) { mMissStreaks.resize(missStreakCount); }
    void SetBestOverdriveDeploymentsCount(int bestOverdriveDeploymentsCount) { mBestOverdriveDeployments.resize(bestOverdriveDeploymentsCount); }
    void SetBestStreakMultipliersCount(int bestStreakMultipliersCount) { mBestStreakMultipliers.resize(bestStreakMultipliersCount); }
    void SetTotalOverdriveDuration(float totalOverdriveDuration) { mTotalOverdriveDurationMs = totalOverdriveDuration; }
    void SetTotalMultiplierDuration(float totalMultiplierDuration) { mTotalMultiplierDuration = totalMultiplierDuration; }
    void SetRollsHitCompletely(int rollsHitCompletely) { mRollsHitCompletely = rollsHitCompletely; }
    void SetRollCount(int rollCount) { mRollCount = rollCount; }
    void SetHighGemsHitHigh(int highGemsHitHigh) { mHighGemsHitHigh = highGemsHitHigh; }
    void SetHighGemsHitLow(int highGemsHitLow) { mHighGemsHitLow = highGemsHitLow; }
    void SetHighFretGemCount(int highFretGemCount) { mHighFretGemCount = highFretGemCount; }
    void SetSustainGemsHitCompletely(int sustainGemsHitCompletely) { mSustainGemsHitCompletely = sustainGemsHitCompletely; }
    void SetSustainGemsHitPartially(int sustainGemsHitPartially) { mSustainGemsHitPartially = sustainGemsHitPartially; }
    void SetSustainGemCount(int sustainGemCount) { mSustainGemCount = sustainGemCount; }
    void SetTrillsHitCompletely(int trillsHitCompletely) { mTrillsHitCompletely = trillsHitCompletely; }
    void SetTrillsHitPartially(int trillsHitPartially) { mTrillsHitPartially = trillsHitPartially; }
    void SetTrillCount(int trillCount) { mTrillCount = trillCount; }
    void SetDoubleHarmonyHit(int doubleHarmonyHit) { mDoubleHarmonyHit = doubleHarmonyHit; }
    void SetDoubleHarmonyPhraseCount(int doubleHarmonyPhraseCount) { mDoubleHarmonyPhraseCount = doubleHarmonyPhraseCount; }
    void SetTripleHarmonyHit(int tripleHarmonyHit) { mTripleHarmonyHit = tripleHarmonyHit; }
    void SetTripleHarmonyPhraseCount(int tripleHarmonyPhraseCount) { mTripleHarmonyPhraseCount = tripleHarmonyPhraseCount; }

    template <class T> void SaveHighest(std::vector<T>&, const T&);

    int mHitCount;                             // 0x000
    int mMissCount;                            // 0x004
    int m0x08;                                 // 0x008
    int m0x0c;                                 // 0x00c
    int mPersistentStreak;                     // 0x010
    int mLongestPersistentStreak;              // 0x014
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
    int mSoloButtonedSoloPercentage;           // 0x03c
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
    std::vector<float> m0x70;                    // 0x070
    std::vector<SingerStats> mSingerStats;     // 0x078
    std::vector<Symbol> mAccessPerformanceAwards;                    // 0x080
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
    bool mFullCombo; // 0xb4
    float mNoScorePercent; // 0xb8
    StreakInfo mCurrentHitStreak; // 0xbc
    std::vector<StreakInfo> mHitStreaks; // 0xc4
    StreakInfo mCurrentMissStreak; // 0xcc
    std::vector<StreakInfo> mMissStreaks; // 0xd4
    std::vector<float> mFailurePoints; // 0xdc
    std::vector<float> mSavedPoints; // 0xe4
    int mPlayersSaved; // 0xec
    std::vector<float> mClosestPlayersSaved; // 0xf0
    int mTimesSaved; // 0xf8
    std::vector<float> mClosestTimesSaved; // 0xfc
    std::vector<int> mBestSolos; // 0x104
    MultiplierInfo mCurrentOverdriveDeployment; // 0x10c
    std::vector<MultiplierInfo> mBestOverdriveDeployments; // 0x120
    float mTotalOverdriveDurationMs; // 0x128
    MultiplierInfo mCurrentStreakMultiplier; // 0x12c
    std::vector<MultiplierInfo> mBestStreakMultipliers; // 0x140
    float mTotalMultiplierDuration; // 0x148
    int m0x14c; // 0x14c
    int m0x150;
    int mEndGameScore; // 0x154
    float mEndGameCrowdLevel; // 0x158
    float mEndGameOverdrive; // 0x15c
    int mOverdrivePhrasesCompleted; // 0x160
    int mOverdrivePhraseCount; // 0x164
    int mUnisonPhraseCompleted; // 0x168
    int mUnisonPhraseCount; // 0x16c
    int mHopoGemsHopoed; // 0x170
    int mHopoGemsStrummed; // 0x174
    int mHopoGemCount; // 0x178
    int mHighGemsHitHigh; // 0x17c
    int mHighGemsHitLow; // 0x180
    int mHighFretGemCount; // 0x184
    int mSustainGemsHitCompletely; // 0x188
    int mSustainGemsHitPartially; // 0x18c
    int mSustainGemCount; // 0x190
    float m0x194;
    int mRollCount; // 0x198
    int mRollsHitCompletely; // 0x19c
    int mTrillCount; // 0x1a0
    int mTrillsHitCompletely; // 0x1a4
    int mTrillsHitPartially; // 0x1a8
    int mCymbalGemInfo1; // 0x1ac
    int mCymbalGemInfo2; // 0x1b0
    int mCymbalGemInfo3; // 0x1b4
    std::vector<SectionInfo> mSections; // 0x1b8
    float unk1c0;
    float unk1c4;
    float unk1c8;

    // bool mMultiplierActive; // 0x205
};

BinStream& operator<<(BinStream&, const Stats::StreakInfo&);
BinStream& operator>>(BinStream&, Stats::StreakInfo&);
BinStream& operator<<(BinStream&, const Stats::SectionInfo&);
BinStream& operator>>(BinStream&, Stats::SectionInfo&);
bool operator>(const Stats::MultiplierInfo&, const Stats::MultiplierInfo&);

#endif // GAME_STATS_H
