#include "Stats.h"

Stats::Stats(const Stats& copy) {
    mHitCount = copy.mHitCount;
    mMissCount = copy.mMissCount;
}

void Stats::GetDoubleHarmonyHit() const {}
void Stats::GetDoubleHarmonyPhraseCount() const {}
void Stats::GetTripleHarmonyHit() const {}
void Stats::GetTripleHarmonyPhraseCount() const {}

int Stats::GetHitCount() const {
    return mHitCount;
}

void Stats::GetNotesHitFraction() const {}
void Stats::GetNumberOfSingers() const {}
void Stats::GetVocalPartPercentage(int) const {}    
void Stats::GetFailedDeploy() const {}
void Stats::GetPlayersSaved() const {}
void Stats::GetFillHitCount() const {}
void Stats::GetStrummedDown() const {}
void Stats::GetStrummedUp() const {}
void Stats::GetDeployCount() const {}
void Stats::GetSoloPercentage() const {}
void Stats::GetPerfectSoloWithSoloButtons() const {}
void Stats::GetFinalized() const {}