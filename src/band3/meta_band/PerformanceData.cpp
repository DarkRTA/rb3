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

void Stats::SetEndGameScore(int endGameScore) {
    mEndGameScore = endGameScore;
}

void Stats::SetNotesHitFraction(float notesHitFraction) {
    mNotesHitFraction = notesHitFraction;
}

void Stats::SetHitCount(int hitCount) {
    mHitCount = hitCount;
}

void Stats::SetMissCount(int missCount) {
    mMissCount = missCount;
}

void Stats::AccessFailurePoints() {}
void Stats::AccessSavedPoints() {}
void Stats::AccessClosestTimesSaved() {}
void Stats::AccessClosestPlayersSaved() {}
void Stats::SetTimesSaved(int) {}
void Stats::SetPlayersSaved(int) {}
void Stats::AccessCurrentStreakInfo() {}
void Stats::SetEndGameOverdrive(float) {}
void Stats::SetEndGameCrowdLevel(float) {}
void Stats::SetCodaPoints(int) {}
void Stats::SetOverdrivePhrasesCompleted(int) {}
void Stats::SetOverdrivePhraseCount(int) {}
void Stats::SetUnisonPhrasesCompleted(int) {}
void Stats::SetUnisonPhraseCount(int) {}
void Stats::AccessBestSolos() {}
void Stats::SetHitStreakCount(int) {}
void Stats::AccessHitStreak(int) {}
void Stats::SetMissStreakCount(int) {}
void Stats::AccessMissStreak(int) {}
void Stats::SetBestOverdriveDeploymentsCount(int) {}
void Stats::AccessBestOverdriveDeployment(int) {}
void Stats::SetBestStreakMultipliersCount(int) {}
void Stats::AccessBestStreakMultiplier(int) {}
void Stats::SetTotalOverdriveDuration(float) {}
void Stats::SetTotalMultiplierDuration(float) {}
void Stats::SetRollsHitCompletely(int) {}
void Stats::SetRollCount(int) {}
void Stats::SetHighGemsHitHigh(int) {}
void Stats::SetHighGemsHitLow(int) {}
void Stats::SetHighFretGemCount(int) {}
void Stats::SetSustainGemsHitCompletely(int) {}
void Stats::SetSustainGemsHitPartially(int) {}
void Stats::SetSustainGemCount(int) {}
void Stats::SetTrillsHitCompletely(int) {}
void Stats::SetTrillsHitPartially(int) {}
void Stats::SetTrillCount(int) {}

void Stats::SetDoubleHarmonyHit(int doubleHarmonyHit) {
    mDoubleHarmonyHit = doubleHarmonyHit;
}

void Stats::SetDoubleHarmonyPhraseCount(int doubleHarmonyPhraseCount) {
    mDoubleHarmonyPhraseCount = doubleHarmonyPhraseCount;
}

void Stats::SetTripleHarmonyHit(int tripleHarmonyHit) {
    mTripleHarmonyHit = tripleHarmonyHit;
}

void Stats::SetTripleHarmonyPhraseCount(int tripleHarmonyPhraseCount) {
    mTripleHarmonyPhraseCount = tripleHarmonyPhraseCount;
}

void Stats::AccessSingerStats(int) {}
