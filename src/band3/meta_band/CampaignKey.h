#pragma once
#include "obj/Data.h"

class CampaignKey {
public:
    CampaignKey(DataArray *);
    virtual ~CampaignKey();
    virtual void Configure(DataArray *);

    Symbol mName;
    Symbol GetName() const;
};
