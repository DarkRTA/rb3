#ifndef METABAND_CAMPAIGN_H
#define METABAND_CAMPAIGN_H

#include "obj/Data.h"
#include "os/User.h"

class Campaign {
public:
    LocalUser* GetUser() const;
    Symbol GetLaunchUser() const;
    bool HasCampaignLevel(Symbol) const;
    Symbol GetCurrentGoal() const;
};

extern Campaign* TheCampaign;

#endif // METABAND_CAMPAIGN_H
