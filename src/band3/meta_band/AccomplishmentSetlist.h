#ifndef METABAND_ACCOMPLISHMENTSETLIST_H
#define METABAND_ACCOMPLISHMENTSETLIST_H

#include "system/obj/Data.h"
#include <set>
#include "Accomplishment.h"

enum Difficulty {};

class AccomplishmentSetlist {
    AccomplishmentSetlist(DataArray*, int);
    virtual ~AccomplishmentSetlist();
    void Configure(DataArray*);
    int GetType() const;
    bool CanBeLaunched() const;
    bool HasSpecificSongsToLaunch() const;
    int GetRequiredDifficulty() const;
    ScoreType InqRequiredScoreTypes(std::set<ScoreType>&) const;
    bool CheckRequirements(ScoreType, Difficulty, int);

    Accomplishment mAccomplishment;

    Symbol mSetlist;    // 0x74
    int mInstrument;    // 0x78
    int mDifficulty;    // 0x7c
    int mMinStars;      // 0x80
};

#endif // METABAND_ACCOMPLISHMENTSETLIST_H
