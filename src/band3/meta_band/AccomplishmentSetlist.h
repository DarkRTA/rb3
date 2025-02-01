#pragma once
#include "system/obj/Data.h"
#include "utl/MemMgr.h"
#include <set>
#include "Accomplishment.h"

class AccomplishmentSetlist : public Accomplishment {
public:
    AccomplishmentSetlist(DataArray *, int);
    virtual ~AccomplishmentSetlist();
    virtual AccomplishmentType GetType() const;
    virtual Difficulty GetRequiredDifficulty() const;
    virtual bool InqRequiredScoreTypes(std::set<ScoreType> &) const;
    virtual bool CanBeLaunched() const;
    virtual bool HasSpecificSongsToLaunch() const;

    Symbol mSetlist; // 0x74
    ScoreType mInstrument; // 0x78
    Difficulty mDifficulty; // 0x7c
    int mMinStars; // 0x80

    void Configure(DataArray *);
    bool CheckRequirements(ScoreType, Difficulty, int);

    DELETE_OVERLOAD
};
