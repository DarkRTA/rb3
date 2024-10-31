#ifndef METABAND_CAMPAIGN_H
#define METABAND_CAMPAIGN_H
#include "BandProfile.h"
#include "CampaignLevel.h"
#include "bandobj/MeterDisplay.h"
#include "beatmatch/TrackType.h"
#include "game/Defines.h"
#include "meta_band/AccomplishmentManager.h"
#include "meta_band/CampaignKey.h"
#include "meta_band/ProfileMessages.h"
#include "obj/Data.h"
#include "os/ProfileSwappedMsg.h"
#include "os/User.h"
#include "game/BandUser.h"
#include "ui/UIPicture.h"

class BandProfile;

class Campaign : public Hmx::Object {
public:
    Campaign(DataArray*);
    virtual ~Campaign();
    virtual DataNode Handle(DataArray*, bool);

    LocalBandUser* GetUser() const;
    LocalBandUser* GetLaunchUser() const;
    bool HasCampaignKey(Symbol) const;
    bool HasCampaignLevel(Symbol) const;
    CampaignKey* GetCampaignKey(Symbol) const;
    CampaignLevel* GetCampaignLevel(Symbol) const;
    Symbol GetCurrentGoal() const;
    Symbol GetCampaignLevelForMetaScore(int) const;
    int GetCampaignMetaScoreForProfile(BandProfile*) const;
    void SetupLaunchedAccomplishmentInfo(Symbol);
    BandProfile* GetProfile() const;
    bool HasReachedCampaignLevel(LocalBandUser*, Symbol) const;
    void SetWasLaunchedIntoMusicLibrary(bool);
    TrackType GetRequiredTrackTypeForGoal(Symbol) const;
    TrackType GetRequiredTrackTypeForCurrentAccomplishment() const;
    ScoreType GetRequiredScoreTypeForCurrentAccomplishment() const;
    void Init(DataArray*);
    void Cleanup();
    void ConfigureCampaignLevelData(DataArray*);
    void ConfigureCampaignKeyData(DataArray*);
    String GetCampaignLevelIconForUser(LocalBandUser*);
    Symbol GetCampaignLevelForUser(LocalBandUser*) const;
    bool HasScoreReachedCampaignLevel(int, Symbol) const;
    int GetCampaignMetaScoreForUser(LocalBandUser*) const;
    bool HasReachedCampaignLevel(Symbol) const;
    int GetCampaignFanCountForUser(LocalBandUser*) const;
    int GetPrimaryCampaignFanCount() const;
    Symbol GetPrimaryCampaignLevel() const;
    bool IsUserOnLastCampaignLevel(LocalBandUser*);
    bool IsPrimaryUserOnLastCampaignLevel();
    bool IsLastCampaignLevel(Symbol) const;
    Symbol GetNextCampaignLevel(Symbol) const;
    String GetCurrentMajorLevelIcon(LocalBandUser*);
    Symbol GetMajorLevelForMetaScore(int);
    Symbol GetNextMajorLevelForMetaScore(int);
    String GetIconArt() const;
    String GetNextMajorLevelIcon(LocalBandUser*);
    String GetPrimaryCurrentMajorLevelIcon();
    String GetPrimaryNextMajorLevelIcon();
    void UpdatePrimaryCurrentMajorLevelIcon(UIPicture*);
    void UpdatePrimaryNextMajorLevelIcon(UIPicture*);
    void UpdateCurrentMajorLevelIcon(LocalBandUser*, UIPicture*);
    void UpdateNextMajorLevelIcon(LocalBandUser*, UIPicture*);
    int GetTotalPointsForNextCampaignLevelForUser(LocalBandUser*);
    int GetCurrentPointsForNextCampaignLevelForUser(LocalBandUser*);
    int GetTotalPointsForNextMajorCampaignLevelForMetaScore(int);
    int GetTotalPointsForNextMajorCampaignLevelForPrimary();
    int GetTotalPointsForNextMajorCampaignLevelForUser(LocalBandUser*);
    int GetCurrentPointsForNextMajorCampaignLevelForMetaScore(int);
    int GetCurrentPointsForNextMajorCampaignLevelForPrimary();
    int GetCurrentPointsForNextMajorCampaignLevelForUser(LocalBandUser*);
    void ClearCurrentGoal();
    bool HasCurrentGoal() const;
    Symbol GetCurrentGoalDescription() const;
    String GetCurrentGoalIcon() const;
    Difficulty GetMinimumDifficultyForCurrentAccomplishment() const;
    ScoreType GetRequiredScoreTypeForGoal(Symbol) const;
    bool HasValidUser() const;
    LocalBandUser* HasUser() const;
    void UpdateProgressMeter(MeterDisplay*, LocalBandUser*);
    void UpdatePrimaryProgressMeter(MeterDisplay*);
    bool CanSkipSongs();
    bool CanResumeSongs();
    bool CanSaveSetlists();
    Symbol GetNextHintToShow() const;
    bool HasHintsToShow() const;
    Symbol GetCampaignLevelAdvertisement(Symbol) const;
    bool GetWasLaunchedIntoMusicLibrary() const;
    bool DidUserMakeProgressOnGoal(LocalBandUser*, Symbol);
    bool HasDisplayGoal();
    Symbol GetCategoryGroup(Symbol);
    Symbol GetGoalCategory(Symbol);
    Symbol GetDisplayGoal();
    bool ShouldReturnToCategoryScreen();
    void HandleLaunchedGoalComplete();
    RndTex* GetPrimaryBandLogoTex();
    void CheatNextMetaLevel();
    const char* GetCheatMetaLevel();
    void CheatReloadCampaignData();
    void UpdateEndGameInfoForCurrentCampaignGoal(UILabel*, UILabel*, UIPicture*);
    void UpdateEndGameInfo(UILabel*, UILabel*, UIPicture*);

    DataNode OnMsg(const ProfileSwappedMsg&);
    DataNode OnMsg(const PrimaryProfileChangedMsg&);

    AccomplishmentManager* m_pAccomplishmentMgr; // 0x1c
    Symbol m_symCurrentAccomplishment; // 0x20
    bool m_bWasLaunchedIntoMusicLibrary; // 0x24
    bool unk25; // 0x25
    Symbol unk28; // 0x28
    std::vector<Symbol> m_vCampaignLevels; // 0x2c
    std::map<Symbol, CampaignLevel*> m_mapCampaignLevels; // 0x34
    std::map<Symbol, Symbol> unk4c; // 0x4c
    std::vector<Symbol> unk64; // 0x64
    std::map<Symbol, CampaignKey*> m_mapCampaignKeys; // 0x6c
    BandProfile* unk84; // 0x84
    int unk88; // 0x88
};

extern Campaign* TheCampaign;

#endif // METABAND_CAMPAIGN_H
