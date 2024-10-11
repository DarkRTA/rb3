#ifndef METABAND_BANDPROFILE_H
#define METABAND_BANDPROFILE_H
#include "system/meta/Profile.h"
#include "game/Defines.h"
#include "meta_band/GameplayOptions.h"
#include <vector>
#include "StandIn.h"
#include "ProfileAssets.h"

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
class ProfilePicture;

class BandProfile : public Profile {
public:
    BandProfile(int);
    virtual ~BandProfile();
    virtual void SaveFixed(FixedSizeSaveableStream&) const;
    virtual void LoadFixed(FixedSizeSaveableStream&, int);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool HasCheated() const;
    virtual bool IsUnsaved() const;
    virtual void SaveLoadComplete(ProfileSaveState);
    virtual bool HasSomethingToUpload();
    virtual void DeleteAll();
    virtual void PreLoad();

    void Poll();
    void GetAvailableStandins(int, std::vector<TourCharLocal*>&) const;
    void GetAllChars(std::vector<TourCharLocal*>&) const;
    void GetAvailableCharacters(std::vector<TourCharLocal*>&) const;
    CharData* GetCharFromGuid(const HxGuid&);
    int GetMaxChars() const;
    void AddNewChar(TourCharLocal*);
    void DeleteChar(TourCharLocal*);
    void RenameCharacter(TourCharLocal*, const char*);
    int NumChars() const;
    bool HasChar(const TourCharLocal*);
    void GetFirstEmptyPatch();
    void GetTexAtPatchIndex(int) const;
    void GetPatchIndex(const PatchDir*) const;
    void PotentiallyDeleteStandin(HxGuid);
    void GetCharacterStandinIndex(CharData*) const;
    StandIn* GetStandIn(int) const;
    StandIn* AccessStandIn(int);
    int GetNumStandins() const;
    TourProgress* GetTourProgress();
    bool OwnsTourProgress(const TourProgress*);
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
    void GetUploadFriendsToken() const;
    void SetUploadFriendsToken(int);
    void SaveSize(int);
    LocalBandUser* GetAssociatedLocalBandUser() const;
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
    bool IsLessonComplete(const Symbol&, float) const;
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
    DataNode OnMsg(const RockCentralOpCompleteMsg&);
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
    void GetPictureTex();
    void AutoFakeFill(int);
    
    bool unk18;
    std::vector<int> unk1c; // 0x1c
    std::vector<CharData*> mChars; // 0x24 
    TourProgress* mTourProgress;   // 0x2c correct up to here
    std::map<Symbol, float> unk30; // 0x30
    int unk48; // 0x48 - SongStatusMgr
    std::vector<int> unk4c; // 0x4c
    // Gameplay options 0x2e
    // lessons 0x34
    // AccomplishmentProgress* 0x3d
    // song status mgr 0x48
    // saved song lists 0x4c
    std::vector<StandIn*> mStandIns; // 0x54
    HxGuid unk5c; // 0x5c
    Symbol unk6c; // 0x6c
    std::set<Symbol> unk70; // 0x70
    std::set<Symbol> unk88; // 0x88
    std::set<Symbol> unka0; // 0xa0
    GameplayOptions mGameplayOptions; // 0xb8
    // accomplishment progress 0xf4
    // something involving performance data 0x6f70
    // 0x6f74
    ProfileAssets* mProfileAssets; // 0x6f78
    ProfilePicture* mProfilePicture; // 0x6fbc

    // upload friends token 0x6fb4
    // hardcore icon level 0x6fb8
    // profile picture 0x6fbc
    // tour band 0x6fc0

};

#endif // METABAND_BANDPROFILE_H