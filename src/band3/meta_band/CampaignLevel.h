#pragma once
#include "obj/Data.h"

class CampaignLevel {
public:
    CampaignLevel(DataArray*, int);
    virtual ~CampaignLevel();
    virtual void Configure(DataArray*);

    Symbol GetName() const;
    int GetValue() const;
    bool HasAward() const;
    Symbol GetAward() const;
    bool IsMajorLevel() const;
    String GetIconArt() const;
};