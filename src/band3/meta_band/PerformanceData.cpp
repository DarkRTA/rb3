#include "PerformanceData.h"

PerformanceData::PerformanceData() {

}

PerformanceData::~PerformanceData() {

}

void PerformanceData::Initialize(const Stats&, int, ScoreType, Difficulty, Symbol, int, int, bool) {

}

void PerformanceData::SaveFixed(FixedSizeSaveableStream&) const {

}

void PerformanceData::SaveSize(int) {

}

void PerformanceData::LoadFixed(FixedSizeSaveableStream&, int) {

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
