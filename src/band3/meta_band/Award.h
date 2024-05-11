#ifndef METABAND_AWARD_H
#define METABAND_AWARD_H
#include "system/obj/Data.h"

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
    // void GrantAward();
    void InqAssets(std::vector<Symbol>&);
    bool HasAssets() const;
    // void GrantAwards();

    Symbol mName;
    Symbol mIconArt;
    bool mIsBonus;
};

#endif // METABAND_AWARD_H