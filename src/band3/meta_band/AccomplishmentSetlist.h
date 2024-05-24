#ifndef METABAND_ACCOMPLISHMENTSETLIST_H
#define METABAND_ACCOMPLISHMENTSETLIST_H

#include "system/obj/Data.h"
#include <set>
#include "Accomplishment.h"

class AccomplishmentSetlist : private Accomplishment {
public:
    AccomplishmentSetlist(DataArray*, int);
    virtual ~AccomplishmentSetlist();

private:
    Symbol mSetlist;       // 0x74
    ScoreType mInstrument; // 0x78
    int mDifficulty;       // 0x7c
    int mMinStars;         // 0x80

    void Configure(DataArray*);
    int GetType() const;
    bool CanBeLaunched() const;
    bool HasSpecificSongsToLaunch() const;
    int GetRequiredDifficulty() const;
    bool InqRequiredScoreTypes(std::set<ScoreType>&) const;
    bool CheckRequirements(ScoreType, Difficulty, int);
};

#endif // METABAND_ACCOMPLISHMENTSETLIST_H
