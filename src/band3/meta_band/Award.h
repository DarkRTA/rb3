#ifndef METABAND_AWARD_H
#define METABAND_AWARD_H
#include "system/obj/Data.h"
#include "BandProfile.h"

class AwardEntry {
};

class Award {
    Award(DataArray*, int);
    virtual ~Award();
    void Configure(DataArray*);
    Symbol GetName() const;
    Symbol GetDescription() const;
    Symbol GetDisplayName() const;
    bool HasIconArt() const;
    Symbol GetIconArt() const;
    bool IsBonus() const;
    void GrantAward(const AwardEntry&, BandProfile*);
    void InqAssets(std::vector<Symbol>&);
    bool HasAssets() const;
    void GrantAwards(BandProfile*);

    Symbol mName;
    Symbol mIconArt;
    Symbol mDescription;
    std::vector<AwardEntry> pAwardEntryArray;
    int mIndex;

    bool mIsSecret;
    bool mIsBonus;
    Symbol mIcon;
    Symbol mAwards;
};

#endif // METABAND_AWARD_H