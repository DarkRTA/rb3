#include "AccomplishmentSongConditional.h"

AccomplishmentSongConditional::AccomplishmentSongConditional(DataArray* i_pConfig, int index) : AccomplishmentConditional(i_pConfig, index) {

}

AccomplishmentSongConditional::~AccomplishmentSongConditional() {
    
}

void AccomplishmentSongConditional::CheckStarsCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const {

}

void AccomplishmentSongConditional::CheckScoreCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const {
    
}

void AccomplishmentSongConditional::CheckAccuracyCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const {}
void AccomplishmentSongConditional::CheckStreakCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const {}
void AccomplishmentSongConditional::CheckHoposPercentCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const {}
void AccomplishmentSongConditional::CheckSoloPercentCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const {}
void AccomplishmentSongConditional::CheckAwesomesCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const {}
void AccomplishmentSongConditional::CheckDoubleAwesomesCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const {}
void AccomplishmentSongConditional::CheckTripleAwesomesCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const {}
void AccomplishmentSongConditional::CheckHitBRECondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const {}
void AccomplishmentSongConditional::CheckAllDoubleAwesomesCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const {}
void AccomplishmentSongConditional::CheckAllTripleAwesomesCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const {}
void AccomplishmentSongConditional::CheckPerfectDrumRollsCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const {}
void AccomplishmentSongConditional::CheckFullComboCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const {}
void AccomplishmentSongConditional::CheckConditionsForSong(SongStatusMgr*, Symbol) const {}
void AccomplishmentSongConditional::UpdateIncrementalEntryName(UILabel*, Symbol) {}
void AccomplishmentSongConditional::InqProgressValues(BandProfile*, int&, int&) {}
void AccomplishmentSongConditional::IsSymbolEntryFulfilled(BandProfile*, Symbol) const {}
void AccomplishmentSongConditional::ShowBestAfterEarn() const {}
void AccomplishmentSongConditional::InitializeTrackerDesc(TrackerDesc&) const {}