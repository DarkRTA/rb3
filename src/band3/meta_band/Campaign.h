#ifndef METABAND_CAMPAIGN_H
#define METABAND_CAMPAIGN_H

#include "BandProfile.h"
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
};

extern Campaign* TheCampaign;

#endif // METABAND_CAMPAIGN_H
