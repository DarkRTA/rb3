#ifndef METABAND_CAMPAIGN_H
#define METABAND_CAMPAIGN_H
#include "BandProfile.h"
#include "CampaignLevel.h"
#include "beatmatch/TrackType.h"
#include "game/Defines.h"
#include "meta_band/AccomplishmentManager.h"
#include "meta_band/CampaignKey.h"
#include "obj/Data.h"
#include "os/User.h"
#include "game/BandUser.h"

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

    AccomplishmentManager* m_pAccomplishmentMgr; // 0x1c
    Symbol m_symCurrentAccomplishment; // 0x20
    bool unk24;
    bool unk25;
    Symbol unk28;
    std::vector<Symbol> unk2c;
    std::map<Symbol, CampaignLevel*> unk34;
    std::map<Symbol, Symbol> unk4c;
    std::vector<Symbol> unk64;
    std::map<Symbol, CampaignKey*> unk6c;
    int unk84;
    int unk88;
};

extern Campaign* TheCampaign;

#endif // METABAND_CAMPAIGN_H
