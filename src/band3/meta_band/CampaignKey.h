#ifndef METABAND_CAMPAIGNKEY_H
#define METABAND_CAMPAIGNKEY_H

#include "obj/Data.h"

class CampaignKey {
    public:
    CampaignKey(DataArray*);
    virtual ~CampaignKey();
    virtual void Configure(DataArray*);

    Symbol mName; Symbol GetName() const;
};

#endif // METABAND_CAMPAIGNKEY_H