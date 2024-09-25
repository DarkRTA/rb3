#ifndef METABAND_CAMPAIGN_H
#define METABAND_CAMPAIGN_H

#include "obj/Data.h"
#include "os/User.h"

class Campaign {
public:
    LocalUser* GetUser() const;
    Symbol GetLaunchUser() const;
};

extern Campaign* TheCampaign;

#endif // METABAND_CAMPAIGN_H
