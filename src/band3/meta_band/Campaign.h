#ifndef METABAND_CAMPAIGN_H
#define METABAND_CAMPAIGN_H

#include "BandProfile.h"
#include "beatmatch/TrackType.h"
#include "game/Defines.h"
#include "obj/Data.h"
#include "os/User.h"
#include "game/BandUser.h"

class BandProfile;

class Campaign {
public:
    LocalBandUser* GetUser() const;
    LocalBandUser* GetLaunchUser() const;
    bool HasCampaignLevel(Symbol) const;
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
};

extern Campaign* TheCampaign;

#endif // METABAND_CAMPAIGN_H
