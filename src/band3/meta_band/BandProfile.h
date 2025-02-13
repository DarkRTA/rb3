#pragma once
#include "meta_band/SavedSetlist.h"
#include "obj/Msg.h"
#include "rndobj/Tex.h"
#include "system/meta/Profile.h"
#include "game/Defines.h"
#include "meta_band/GameplayOptions.h"
#include <vector>
#include "StandIn.h"
#include "ProfileAssets.h"
#include "meta_band/AccomplishmentProgress.h"
#include "net_band/DataResults.h"
#include "meta_band/PerformanceData.h"
#include "tour/TourCharLocal.h"

#define kMaxCharacters 10
#define kMaxPatchesPerProfile 8

class PatchDir;
class CharData;
class TourProgress;
class PerformerStatsInfo;
class PerformanceData;
class PatchDescriptor;
class SongStatusMgr;
class RockCentralOpCompleteMsg;
class LocalBandUser;
class ProfilePicture;
class TourBand;

class BandProfile : public Profile {
public:
    BandProfile(int);
    virtual ~BandProfile();
    virtual void SaveFixed(FixedSizeSaveableStream &) const;
    virtual void LoadFixed(FixedSizeSaveableStream &, int);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool HasCheated() const;
    virtual bool IsUnsaved() const;
    virtual void SaveLoadComplete(ProfileSaveState);
    virtual bool HasSomethingToUpload();
    virtual void DeleteAll();
    virtual void PreLoad();

    void Poll();
    void GetAvailableStandins(int, std::vector<TourCharLocal *> &) const;
    void GetAllChars(std::vector<TourCharLocal *> &) const;
    void GetAvailableCharacters(std::vector<TourCharLocal *> &) const;
    CharData *GetCharFromGuid(const HxGuid &);
    int GetMaxChars() const;
    void AddNewChar(TourCharLocal *);
    void DeleteChar(TourCharLocal *);
    void RenameCharacter(TourCharLocal *, const char *);
    bool HasChar(const TourCharLocal *);
    void GetFirstEmptyPatch();
    RndTex *GetTexAtPatchIndex(int) const;
    void GetPatchIndex(const PatchDir *) const;
    void PotentiallyDeleteStandin(HxGuid);
    int GetCharacterStandinIndex(CharData *) const;
    StandIn *GetStandIn(int) const;
    StandIn *AccessStandIn(int);
    int GetNumStandins() const;
    TourProgress *GetTourProgress();
    bool OwnsTourProgress(const TourProgress *);
    void UpdateScore(int, const PerformerStatsInfo &, bool);
    void UploadPerformance(PerformanceData *);
    void GetNumDirtyPerformanceData();
    void UploadDirtyPerformanceData();
    void UploadDirtyAccomplishmentData();
    void UploadDirtyScoreData();
    void UploadDirtyData();
    void SetSongReview(int, int);
    int GetSongReview(int);
    SongStatusMgr *GetSongStatusMgr() const;
    void GetSongHighScore(int, ScoreType) const;
    void GetSavedSetlists() const;
    void
    AddSavedSetlist(const char *, const char *, bool, const PatchDescriptor &, const std::vector<int> &);
    void DeleteSavedSetlist(LocalSavedSetlist *);
    void SetlistChanged(LocalSavedSetlist *);
    void NumSavedSetlists() const;
    void GetUploadFriendsToken() const;
    void SetUploadFriendsToken(int);
    LocalBandUser *GetAssociatedLocalBandUser() const;
    void CheckForFinishedTrainerAccomplishments();
    void SetProGuitarSongLessonComplete(int, Difficulty);
    void SetProBassSongLessonComplete(int, Difficulty);
    void SetProKeyboardSongLessonComplete(int, Difficulty);
    void SetProGuitarSongLessonSectionComplete(int, Difficulty, int);
    void SetProBassSongLessonSectionComplete(int, Difficulty, int);
    void SetProKeyboardSongLessonSectionComplete(int, Difficulty, int);
    bool IsProGuitarSongLessonSectionComplete(int, Difficulty, int) const;
    bool IsProBassSongLessonSectionComplete(int, Difficulty, int) const;
    bool IsProKeyboardSongLessonSectionComplete(int, Difficulty, int) const;
    bool IsLessonComplete(const Symbol &, float) const;
    void GetLessonComplete(const Symbol &) const;
    float GetLessonCompleteSpeed(const Symbol &) const;
    void SetLessonComplete(const Symbol &, float);
    void EarnAccomplishment(Symbol);
    AccomplishmentProgress *GetAccomplishmentProgress() const;
    AccomplishmentProgress *AccessAccomplishmentProgress();
    int GetHardcoreIconLevel() const;
    void SetHardcoreIconLevel(int);
    void GetTourBand();
    String GetBandName() const;
    void HasBandNameBeenSet() const;
    bool IsBandNameProfanityChecked() const;
    RndTex *GetBandLogoTex();
    void SendBandLogo();
    void GrantCampaignKey(Symbol);
    bool HasCampaignKey(Symbol);
    void UnlockModifier(Symbol);
    bool HasUnlockedModifier(Symbol);
    void HandlePerformanceDataUploadSuccess();
    void UpdatePerformanceData(
        const Stats &, int, ScoreType, Difficulty, Symbol, int, int, bool
    );
    DataNode OnMsg(const RockCentralOpCompleteMsg &);
    LocalBandUser *GetLocalBandUser() const;
    void GetAssociatedUsers(std::vector<LocalBandUser *> &) const;
    void CheckWebLinkStatus();
    void CheckWebSetlistStatus();
    bool HasSeenHint(Symbol) const;
    void SetHasSeenHint(Symbol);
    CharData *GetLastCharUsed() const;
    void SetLastCharUsed(CharData *);
    void SetLastPrefabCharUsed(Symbol);
    void FakeProfileFill();
    void GetPictureTex();
    void AutoFakeFill(int);
    int NumChars() const { return mCharacters.size(); }

    static int SaveSize(int);

    bool unk18;
    std::vector<PatchDir *> mPatches; // 0x1c
    std::vector<TourCharLocal *> mCharacters; // 0x24
    TourProgress *mTourProgress; // 0x2c
    std::map<Symbol, float> mLessonCompletions; // 0x30
    SongStatusMgr *mScores; // 0x48
    std::vector<LocalSavedSetlist *> mSavedSetlists; // 0x4c
    std::vector<StandIn> mStandIns; // 0x54
    HxGuid unk5c; // 0x5c
    Symbol unk6c; // 0x6c
    std::set<Symbol> unk70; // 0x70
    std::set<Symbol> unk88; // 0x88
    std::set<Symbol> unka0; // 0xa0
    GameplayOptions mGameplayOptions; // 0xb8
    AccomplishmentProgress mAccomplishmentProgress; // 0xf4
    int unk740;
    int unk744;
    int unk748;
    int unk74c;
    int unk750;
    DataResultList unk754;
    DataResultList unk76c;
    int unk784;
    PerformanceData unk788[50];
    int unk6f70;
    int unk6f74;
    ProfileAssets mProfileAssets; // 0x6f78
    int unk6fb4;
    int unk6fb8;
    ProfilePicture *mProfilePicture; // 0x6fbc
    TourBand *unk6fc0; // TourBand*
};

DECLARE_MESSAGE(ProfilePreDeleteMsg, "profile_pre_delete_msg");
BandProfile *GetProfile() const { return mData->Obj<BandProfile>(2); }
END_MESSAGE
;