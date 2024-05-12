#ifndef METABAND_ACCOMPLISHMENTSETLIST_H
#define METABAND_ACCOMPLISHMENTSETLIST_H

#include "system/obj/Data.h"
#include <set>
#include "Accomplishment.h"

// Don't know if these are classes or enums, using enums for now.
enum ScoreType {};
enum Difficulty {};

class AccomplishmentSetlist {
    Accomplishment mAccomplishment;
    
    AccomplishmentSetlist(DataArray*, int);
    ~AccomplishmentSetlist();
    void Configure(DataArray*);
    int GetType() const;
    bool CanBeLaunched() const;
    bool HasSpecificSongsToLaunch() const;
    int GetRequiredDifficulty() const;
    void InqRequiredScoreTypes(std::set<ScoreType>&) const;
    bool CheckRequirements(ScoreType, Difficulty, int);

    Symbol mSetlist;
    int mDifficulty;
    int mInstrument;
    int mMin_stars;
};

#endif // METABAND_ACCOMPLISHMENTSETLIST_H