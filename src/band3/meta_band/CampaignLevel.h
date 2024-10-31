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
    Symbol GetAdvertisement() const;
    Symbol GetEarnedText() const;
    Symbol GetRequirementToken() const;

    Symbol mName; // 0x4
    int unk8; // 0x8
    int mPointValue; // 0xc
    Symbol mAward; // 0x10
    Symbol mAdvertisement; // 0x14
    Symbol mRequirementToken; // 0x18
    bool mIsMajorLevel; // 0x1c
};