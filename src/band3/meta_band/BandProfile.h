#ifndef METABAND_BANDPROFILE_H
#define METABAND_BANDPROFILE_H

#include "system/meta/Profile.h"
#include "game/Defines.h"

class TourCharLocal;
class PatchDir;
class CharData;
class TourProgress;
class PerformerStatsInfo;
class PerformanceData;
class PatchDescriptor;
class LocalSavedSetlist;
class Stats;
class RockCentralOpCompleteMsg;
class LocalBandUser;

class BandProfile : public Profile, virtual Hmx::Object {
public:
    BandProfile(int);
    virtual ~BandProfile();
    void Poll();
    void GetAvailableStandins(int, std::vector<TourCharLocal*>&) const;
    void GetAllChars(std::vector<TourCharLocal*>&) const;
    void GetAvailableCharacters(std::vector<TourCharLocal*>&) const;
    void GetCharFromGuid(const HxGuid&);
    void GetMaxChars() const;
    void AddNewChar(TourCharLocal*);
    void DeleteChar(TourCharLocal*);
    void RenameCharacter(TourCharLocal*, const char*);
    void NumChars() const;
    void HasChar(const TourCharLocal*);
    void GetFirstEmptyPatch();
    void GetTexAtPatchIndex(int) const;
    void GetPatchIndex(const PatchDir*) const;
    void PotentiallyDeleteStandin(HxGuid);
    void GetCharacterStandinIndex(CharData*) const;
    void GetStandIn(int) const;
    void AccessStandIn(int);
    void GetNumStandins() const;
    void GetTourProgress();
    void OwnsTourProgress(const TourProgress*);
    void UpdateScore(int, const PerformerStatsInfo&, bool);
    void UploadPerformance(PerformanceData*);
    void GetNumDirtyPerformanceData();
    void UploadDirtyPerformanceData();
    void UploadDirtyAccomplishmentData();
    void UploadDirtyScoreData();
    void UploadDirtyData();
    void SetSongReview(int, int);
    void GetSongReview(int);
    void GetSongStatusMgr() const;
    void GetSongHighScore(int, ScoreType) const;
    void GetSavedSetlists() const;
    void AddSavedSetlist(const char*, const char*, bool, const PatchDescriptor&, const std::vector<int>&);
    void DeleteSavedSetlist(LocalSavedSetlist*);
    void SetlistChanged(LocalSavedSetlist*);
    void NumSavedSetlists() const;
    virtual bool HasCheated() const;
    void GetUploadFriendsToken() const;
    void SetUploadFriendsToken(int);
    virtual void SaveFixed(FixedSizeSaveableStream&) const;
    void SaveSize(int);
    virtual void PreLoad();
    virtual void LoadFixed(FixedSizeSaveableStream&, int);
    virtual bool IsUnsaved() const;
    virtual void SaveLoadComplete(ProfileSaveState);
    virtual bool HasSomethingToUpload();
    virtual void DeleteAll();
    void GetAssociatedLocalBandUser() const;
    void CheckForFinishedTrainerAccomplishments();
    void SetProGuitarSongLessonComplete(int, Difficulty);
    void SetProBassSongLessonComplete(int, Difficulty);
    void SetProKeyboardSongLessonComplete(int, Difficulty);
    void SetProGuitarSongLessonSectionComplete(int, Difficulty, int);
    void SetProBassSongLessonSectionComplete(int, Difficulty, int);
    void SetProKeyboardSongLessonSectionComplete(int, Difficulty, int);
    void IsProGuitarSongLessonSectionComplete(int, Difficulty, int) const;
    void IsProBassSongLessonSectionComplete(int, Difficulty, int) const;
    void IsProKeyboardSongLessonSectionComplete(int, Difficulty, int) const;
    void IsLessonComplete(const Symbol&, float) const;
    void GetLessonComplete(const Symbol&) const;
    void GetLessonCompleteSpeed(const Symbol&) const;
    void SetLessonComplete(const Symbol&, float);
    void EarnAccomplishment(Symbol);
    void GetAccomplishmentProgress() const;
    void AccessAccomplishmentProgress();
    void GetHardcoreIconLevel() const;
    void SetHardcoreIconLevel(int);
    void GetTourBand();
    void GetBandName() const;
    void HasBandNameBeenSet() const;
    void IsBandNameProfanityChecked() const;
    void GetBandLogoTex();
    void SendBandLogo();
    void GrantCampaignKey(Symbol);
    bool HasCampaignKey(Symbol);
    void UnlockModifier(Symbol);
    bool HasUnlockedModifier(Symbol);
    void HandlePerformanceDataUploadSuccess();
    void UpdatePerformanceData(const Stats&, int, ScoreType, Difficulty, Symbol, int, int, bool);
    void OnMsg(const RockCentralOpCompleteMsg&);
    void GetLocalBandUser() const;
    void GetAssociatedUsers(std::vector<LocalBandUser*>&) const;
    void CheckWebLinkStatus();
    void CheckWebSetlistStatus();
    void HasSeenHint(Symbol) const;
    void SetHasSeenHint(Symbol);
    void GetLastCharUsed() const;
    void SetLastCharUsed(CharData*);
    void SetLastPrefabCharUsed(Symbol);
    void FakeProfileFill();
    virtual DataNode Handle(DataArray*, bool);
    void GetPictureTex();
    void AutoFakeFill(int);
};

#endif // METABAND_BANDPROFILE_H