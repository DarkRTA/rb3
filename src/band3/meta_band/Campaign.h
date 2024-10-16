#ifndef METABAND_CAMPAIGN_H
#define METABAND_CAMPAIGN_H

#include "obj/Data.h"
#include "os/User.h"
#include "game/BandUser.h"

class Campaign {
public:
    LocalBandUser* GetUser() const;
    LocalBandUser* GetLaunchUser() const;
    bool HasCampaignLevel(Symbol) const;
    Symbol GetCurrentGoal() const;
    Symbol GetCampaignLevelForMetaScore(int) const;
};

extern Campaign* TheCampaign;

#endif // METABAND_CAMPAIGN_H
