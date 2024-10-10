#include "PerformanceData.h"
#include "MetaPanel.h"

PerformanceData::PerformanceData() : m0x28(false), mIsOnline(false), mIsPlaytest(false), mIsCheating(false), 
mScoreType((ScoreType)0), mDifficulty(kDifficultyEasy), mStars(0), mBattleId(0), mTimestamp(0), mStats() {
    mSaveSizeMethod = SaveSize;
    InitializeStatsVectors();
}

PerformanceData::~PerformanceData() {

}

void PerformanceData::Initialize(const Stats& stats, int songId, ScoreType scoreType, Difficulty difficulty, Symbol mode, int stars, int battleId, bool) {
    if (MetaPanel::sIsPlaytest != '\0') {
        mIsPlaytest = true;
    }

    mMode = mode;
    mSongId = songId;
    mScoreType = scoreType;
    mDifficulty = difficulty;
    mStars = stars;
    mBattleId = battleId;
}

void PerformanceData::SaveFixed(FixedSizeSaveableStream& stream) const {
    stream << m0x24;
    stream << m0x28;
    stream << mIsOnline;
    stream << mIsPlaytest;
    stream << mIsCheating;
    stream << mSongId;
    stream << mScoreType;
    stream << mDifficulty;
    stream << mStars;
    stream << mBattleId;
    stream << mTimestamp;
    stream << mMode;

    // stream.WriteEndian();
}

int PerformanceData::SaveSize(int) {

}

void PerformanceData::LoadFixed(FixedSizeSaveableStream& stream, int) {
    stream >> m0x24;
    stream >> m0x28;
    stream >> mIsPlaytest;
}

void PerformanceData::Prune(Stats&) {}

void PerformanceData::InitializeStatsVectors() {}

BEGIN_HANDLERS(PerformanceData)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x2a8);
END_HANDLERS



void Stats::AccessPerformanceAwards() {

}

void Stats::SetEndGameScore(int endGameScore) { mEndGameScore = endGameScore; }
void Stats::SetNotesHitFraction(float notesHitFraction) { mNotesHitFraction = notesHitFraction; }
void Stats::SetHitCount(int hitCount) { mHitCount = hitCount; }
void Stats::SetMissCount(int missCount) { mMissCount = missCount; }
void Stats::AccessFailurePoints() {}
void Stats::AccessSavedPoints() {}
void Stats::AccessClosestTimesSaved() {}
void Stats::AccessClosestPlayersSaved() {}
void Stats::SetTimesSaved(int timesSaved) { mTimesSaved = timesSaved; }
void Stats::SetPlayersSaved(int playersSaved) { mPlayersSaved = playersSaved; }
void Stats::AccessCurrentStreakInfo() {}
void Stats::SetEndGameOverdrive(float endGameOverdrive) { mEndGameOverdrive = endGameOverdrive; }
void Stats::SetEndGameCrowdLevel(float endGameCrowdLevel) { mEndGameCrowdLevel = endGameCrowdLevel; }
void Stats::SetCodaPoints(int codaPoints) { mCodaPoints = codaPoints; }
void Stats::SetOverdrivePhrasesCompleted(int overdrivePhrasesCompleted) { mOverdrivePhrasesCompleted = overdrivePhrasesCompleted; }
void Stats::SetOverdrivePhraseCount(int overdrivePhraseCount) { mOverdrivePhraseCount = overdrivePhraseCount; }
void Stats::SetUnisonPhrasesCompleted(int unisonPhrasesCompleted) { mUnisonPhraseCompleted = unisonPhrasesCompleted; }
void Stats::SetUnisonPhraseCount(int unisonPhraseCount) { mUnisonPhraseCount = unisonPhraseCount; }
void Stats::AccessBestSolos() {}
void Stats::SetHitStreakCount(int hitStreakCount) { }
void Stats::AccessHitStreak(int) {}
void Stats::SetMissStreakCount(int missStreakCount) { }
void Stats::AccessMissStreak(int) {}
void Stats::SetBestOverdriveDeploymentsCount(int bestOverdriveDeploymentsCount) { }
void Stats::AccessBestOverdriveDeployment(int) {}
void Stats::SetBestStreakMultipliersCount(int bestStreakMultipliersCount) {}
void Stats::AccessBestStreakMultiplier(int) {}
void Stats::SetTotalOverdriveDuration(float totalOverdriveDuration) { mTotalOverdriveDurationMs = totalOverdriveDuration; }
void Stats::SetTotalMultiplierDuration(float totalMultiplierDuration) { mTotalMultiplierDuration = totalMultiplierDuration; }
void Stats::SetRollsHitCompletely(int rollsHitCompletely) { mRollsHitCompletely = rollsHitCompletely; }
void Stats::SetRollCount(int rollCount) { mRollCount = rollCount; }
void Stats::SetHighGemsHitHigh(int highGemsHitHigh) { mHighGemsHitHigh = highGemsHitHigh; }
void Stats::SetHighGemsHitLow(int highGemsHitLow) { mHighGemsHitLow = highGemsHitLow; }
void Stats::SetHighFretGemCount(int highFretGemCount) { mHighFretGemCount = highFretGemCount; }
void Stats::SetSustainGemsHitCompletely(int sustainGemsHitCompletely) { mSustainGemsHitCompletely = sustainGemsHitCompletely; }
void Stats::SetSustainGemsHitPartially(int sustainGemsHitPartially) { mSustainGemsHitPartially = sustainGemsHitPartially; }
void Stats::SetSustainGemCount(int sustainGemCount) { mSustainGemCount = sustainGemCount; }
void Stats::SetTrillsHitCompletely(int trillsHitCompletely) { mTrillsHitCompletely = trillsHitCompletely; }
void Stats::SetTrillsHitPartially(int trillsHitPartially) { mTrillsHitPartially = trillsHitPartially; }
void Stats::SetTrillCount(int trillCount) { mTrillCount = trillCount; }
void Stats::SetDoubleHarmonyHit(int doubleHarmonyHit) { mDoubleHarmonyHit = doubleHarmonyHit; }
void Stats::SetDoubleHarmonyPhraseCount(int doubleHarmonyPhraseCount) { mDoubleHarmonyPhraseCount = doubleHarmonyPhraseCount; }
void Stats::SetTripleHarmonyHit(int tripleHarmonyHit) { mTripleHarmonyHit = tripleHarmonyHit; }
void Stats::SetTripleHarmonyPhraseCount(int tripleHarmonyPhraseCount) { mTripleHarmonyPhraseCount = tripleHarmonyPhraseCount; }
void Stats::AccessSingerStats(int) {}
