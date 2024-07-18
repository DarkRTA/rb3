#include "BandProfile.h"

BandProfile::BandProfile(int i) : Profile(i) {

}

BandProfile::~BandProfile() {

}

void BandProfile::Poll() {
}

void BandProfile::GetAvailableStandins(int, std::vector<TourCharLocal*>&) const {}
void BandProfile::GetAllChars(std::vector<TourCharLocal*>&) const {}
void BandProfile::GetAvailableCharacters(std::vector<TourCharLocal*>&) const {}
void BandProfile::GetCharFromGuid(const HxGuid&) {}
void BandProfile::GetMaxChars() const {}
void BandProfile::AddNewChar(TourCharLocal*) {}
void BandProfile::DeleteChar(TourCharLocal*) {}
void BandProfile::RenameCharacter(TourCharLocal*, const char*) {}
void BandProfile::NumChars() const {}
void BandProfile::HasChar(const TourCharLocal*) {}
void BandProfile::GetFirstEmptyPatch() {}
void BandProfile::GetTexAtPatchIndex(int) const {}
void BandProfile::GetPatchIndex(const PatchDir*) const {}
void BandProfile::PotentiallyDeleteStandin(HxGuid) {}
void BandProfile::GetCharacterStandinIndex(CharData*) const {}
void BandProfile::GetStandIn(int) const {}
void BandProfile::AccessStandIn(int) {}
void BandProfile::GetNumStandins() const {}
void BandProfile::GetTourProgress() {}
void BandProfile::OwnsTourProgress(const TourProgress*) {}
void BandProfile::UpdateScore(int, const PerformerStatsInfo&, bool) {}
void BandProfile::UploadPerformance(PerformanceData*) {}
void BandProfile::GetNumDirtyPerformanceData() {}
void BandProfile::UploadDirtyPerformanceData() {}
void BandProfile::UploadDirtyAccomplishmentData() {}
void BandProfile::UploadDirtyScoreData() {}
void BandProfile::UploadDirtyData() {}
void BandProfile::SetSongReview(int, int) {}
void BandProfile::GetSongReview(int) {}
void BandProfile::GetSongStatusMgr() const {}
void BandProfile::GetSongHighScore(int, ScoreType) const {}
void BandProfile::GetSavedSetlists() const {}
void BandProfile::AddSavedSetlist(const char*, const char*, bool, const PatchDescriptor&, const std::vector<int>&) {}
void BandProfile::DeleteSavedSetlist(LocalSavedSetlist*) {}
void BandProfile::SetlistChanged(LocalSavedSetlist*) {}
void BandProfile::NumSavedSetlists() const {}
bool BandProfile::HasCheated() const {}
void BandProfile::GetUploadFriendsToken() const {}
void BandProfile::SetUploadFriendsToken(int) {}
void BandProfile::SaveFixed(FixedSizeSaveableStream&) const {}
void BandProfile::SaveSize(int) {}
void BandProfile::PreLoad() {}
void BandProfile::LoadFixed(FixedSizeSaveableStream&, int) {}
bool BandProfile::IsUnsaved() const {}
void BandProfile::SaveLoadComplete(ProfileSaveState) {}
bool BandProfile::HasSomethingToUpload() {}
void BandProfile::DeleteAll() {}
void BandProfile::GetAssociatedLocalBandUser() const {}
void BandProfile::CheckForFinishedTrainerAccomplishments() {}
void BandProfile::SetProGuitarSongLessonComplete(int, Difficulty) {}
void BandProfile::SetProBassSongLessonComplete(int, Difficulty) {}
void BandProfile::SetProKeyboardSongLessonComplete(int, Difficulty) {}
void BandProfile::SetProGuitarSongLessonSectionComplete(int, Difficulty, int) {}
void BandProfile::SetProBassSongLessonSectionComplete(int, Difficulty, int) {}
void BandProfile::SetProKeyboardSongLessonSectionComplete(int, Difficulty, int) {}
void BandProfile::IsProGuitarSongLessonSectionComplete(int, Difficulty, int) const {}
void BandProfile::IsProBassSongLessonSectionComplete(int, Difficulty, int) const {}
void BandProfile::IsProKeyboardSongLessonSectionComplete(int, Difficulty, int) const {}
void BandProfile::IsLessonComplete(const Symbol&, float) const {}
void BandProfile::GetLessonComplete(const Symbol&) const {}
void BandProfile::GetLessonCompleteSpeed(const Symbol&) const {}
void BandProfile::SetLessonComplete(const Symbol&, float) {}
void BandProfile::EarnAccomplishment(Symbol) {}
void BandProfile::GetAccomplishmentProgress() const {}
void BandProfile::AccessAccomplishmentProgress() {}
void BandProfile::GetHardcoreIconLevel() const {}
void BandProfile::SetHardcoreIconLevel(int) {}
void BandProfile::GetTourBand() {}
void BandProfile::GetBandName() const {}
void BandProfile::HasBandNameBeenSet() const {}
void BandProfile::IsBandNameProfanityChecked() const {}
void BandProfile::GetBandLogoTex() {}
void BandProfile::SendBandLogo() {}
void BandProfile::GrantCampaignKey(Symbol) {}
bool BandProfile::HasCampaignKey(Symbol) {}
void BandProfile::UnlockModifier(Symbol) {}
bool BandProfile::HasUnlockedModifier(Symbol) {}
void BandProfile::HandlePerformanceDataUploadSuccess() {}
void BandProfile::UpdatePerformanceData(const Stats&, int, ScoreType, Difficulty, Symbol, int, int, bool) {}
void BandProfile::OnMsg(const RockCentralOpCompleteMsg&) {}
void BandProfile::GetLocalBandUser() const {}
void BandProfile::GetAssociatedUsers(std::vector<LocalBandUser*>&) const {}
void BandProfile::CheckWebLinkStatus() {}
void BandProfile::CheckWebSetlistStatus() {}
void BandProfile::HasSeenHint(Symbol) const {}
void BandProfile::SetHasSeenHint(Symbol) {}
void BandProfile::GetLastCharUsed() const {}
void BandProfile::SetLastCharUsed(CharData*) {}
void BandProfile::SetLastPrefabCharUsed(Symbol) {}
void BandProfile::FakeProfileFill() {}
DataNode BandProfile::Handle(DataArray*, bool) {}
void BandProfile::GetPictureTex() {}
void BandProfile::AutoFakeFill(int) {}
