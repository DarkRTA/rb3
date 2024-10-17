#ifndef METABAND_AWARD_H
#define METABAND_AWARD_H
#include "system/obj/Data.h"

class BandProfile;

class AwardEntry {
public:
    Symbol m_symAwardCategory;
    Symbol m_symAward;
};

class Award {
public:
    Award(DataArray *, int);
    virtual ~Award();
    void Configure(DataArray *);
    Symbol GetName() const;
    Symbol GetDescription() const;
    Symbol GetDisplayName() const;
    bool HasIconArt() const;
    Symbol GetIconArt() const;
    bool IsBonus() const;
    void GrantAward(const AwardEntry &, BandProfile *);
    bool InqAssets(std::vector<Symbol> &);
    bool HasAssets() const;
    void GrantAwards(BandProfile *);

    Symbol mName; // 0x04
    Symbol mIcon; // 0x08
    int mIndex; // 0x0c
    bool mIsSecret; // 0x10
    std::vector<AwardEntry> mAwardEntries; // 0x14
    bool mIsBonus; // 0x1c
};

#endif // METABAND_AWARD_H