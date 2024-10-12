#pragma once
#include "obj/Data.h"

class TourDesc {
public:
    TourDesc(DataArray*, int);
    virtual ~TourDesc();
    virtual void Configure(DataArray*);

    Symbol GetFilterForGigNum(int) const;
    Symbol GetSetlistTypeForGigNum(int, int) const;
    int GetNumSongsForGigNum(int) const;
    Symbol GetVenueForGigNum(int) const;
    Symbol GetLeaderboardGoal() const;
    bool HasLeaderboardGoal() const;
    int GetNumGigs() const;
    int GetNumStarsPossibleForTour() const;
    Symbol GetCityForGigNum(int) const;
    Symbol GetName() const;
    Symbol GetWelcome() const;
};