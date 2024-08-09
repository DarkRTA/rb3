#ifndef METABAND_CAMPAIGN_H
#define METABAND_CAMPAIGN_H

#include "obj/Data.h"

class Campaign {
public:
    LocalUser* GetUser() const;
    Symbol GetLaunchUser() const;
};

static Campaign* TheCampaign;

#endif // METABAND_CAMPAIGN_H