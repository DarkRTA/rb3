#pragma once
#include "system/obj/Data.h"
#include "system/ui/UILabel.h"
#include "AccomplishmentConditional.h"

class Performer;

class AccomplishmentOneShot : public AccomplishmentConditional {
public:
    AccomplishmentOneShot(DataArray *, int);
    virtual ~AccomplishmentOneShot();

    void Configure(DataArray *);
    AccomplishmentType GetType() const;
    bool AreOneShotConditionsMet(ScoreType, Difficulty, Performer *, Symbol, int);
    void InitializeTrackerDesc(TrackerDesc &) const;
    bool HasSpecificSongsToLaunch() const;

    Symbol mOneShotSong; // 0x7c
    int mOneShotPlayerMin; // 0x80
};
