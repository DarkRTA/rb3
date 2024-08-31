#include "Stats.h"

Stats::Stats() {

}

void Stats::BuildHitStreak(int, float) {

}

void Stats::GetCurrentStreak() const {

}

void Stats::SetCurrentStreak(int) {

}

void Stats::GetLongestStreak() const {

}

void Stats::SetPersistentStreak(int) {
    
}

void Stats::EndHitStreak() {

}

void Stats::BuildMissStreak(int) {

}

void Stats::EndMissStreak() {

}

void Stats::BuildStreak(Stats::StreakInfo&, int) {

}

void Stats::EndStreak(Stats::StreakInfo&, std::vector<Stats::StreakInfo>&) {

}

void Stats::SetFinalized(bool) {}
void Stats::UpdateBestSolo(int) {}
void Stats::SetSoloButtonedSoloPercentage(int) {}
void Stats::SetVocalSingerAndPartCounts(int, int) {}
void Stats::SetSingerPartPercentage(int, int, float) {}
void Stats::GetSingerRankedPercentage(int, int) const {}
void Stats::GetSingerRankedPart(int, int) const {}
void Stats::SetSingerPitchDeviationInfo(int, float, float) {}
void Stats::UpdateBestTambourineSection(int) {}
void Stats::SaveForEndGame(BinStream&) const {}
void Stats::LoadForEndGame(BinStream&) {}
void Stats::SaveSingerStats(BinStream&) const {}
void Stats::LoadSingerStats(BinStream&) {}
void Stats::AddAccuracy(int) {}
void Stats::AddOverdrive(float) {}
void Stats::AddSolo(int) {}
void Stats::AddSustain(float) {}
void Stats::AddScoreStreak(float) {}
void Stats::AddBandContribution(float) {}
void Stats::AddCodaPoints(int) {}
void Stats::AddTambourine(float) {}
void Stats::AddHarmony(int) {}

int Stats::GetAccuracy() const {
    return mAccuracy;
}

float Stats::GetOverdrive() const {
    return mOverdrive;
}

int Stats::GetSolo() const {
    return mSolo;
}

void Stats::GetSustain() const {}
void Stats::GetScoreStreak() const {}
void Stats::GetBandContribution() const {}
void Stats::GetCodaPoints() const {}
void Stats::GetTambourine() const {}
void Stats::GetHarmony() const {}
void Stats::SetNoScorePercent(float) {}
void Stats::FailedNoScore() const {}
void Stats::AddFailurePoint(float) {}
void Stats::AddToPlayersSaved(int, float) {}
void Stats::AddToTimesSaved(float, float) {}
void Stats::DeployOverdrive(float, int) {}
void Stats::StopDeployingOverdrive(float, int) {}
void Stats::BeginStreakMultiplier(float, int) {}
void Stats::EndStreakMultiplier(float, int) {}
void Stats::BeginMultiplier(Stats::MultiplierInfo&, float, int, float) {}
void Stats::EndMultiplier(Stats::MultiplierInfo&, std::vector<Stats::MultiplierInfo>&, float, int, float, float&) {}
void Stats::GetUnisonPhrasePercent() const {}
void Stats::SetHopoGemInfo(int, int, int) {}
void Stats::IncrementHighFretGemsHit(bool) {}
void Stats::IncrementSustainGemsHit(bool) {}
void Stats::AddRoll(bool) {}
void Stats::IncrementTrillsHit(bool) {}
void Stats::SetCymbalGemInfo(int, int, int) {}
void Stats::SetSectionInfo(int, Symbol, float, float) {}
void Stats::GetSectionInfo(int) const {}
void Stats::GetAverageMsError() const {}




SingerStats::SingerStats(int) {}
void SingerStats::Finalize() {}
void SingerStats::SetPartPercentage(int, float) {}
void SingerStats::GetRankData(int) const {}

void SingerStats::SetPitchDeviationInfo(float param_1, float param_2) {
    mPitchDeviation1 = param_1;
    mPitchDeviation2 = param_2;
}

void SingerStats::GetPitchDeviationInfo(float&, float&) const {}


Stats::StreakInfo::StreakInfo() {}
Stats::MultiplierInfo::MultiplierInfo() {}
Stats::SectionInfo::SectionInfo() {}
