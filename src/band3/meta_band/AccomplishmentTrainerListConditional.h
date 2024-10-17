#pragma once
#include "AccomplishmentTrainerConditional.h"
#include "obj/Data.h"

class AccomplishmentTrainerListConditional : public AccomplishmentTrainerConditional {
public:
    AccomplishmentTrainerListConditional(DataArray*, int);
    virtual ~AccomplishmentTrainerListConditional();
    virtual AccomplishmentType GetType() const;
    virtual bool IsFulfilled(BandProfile*) const;
    virtual bool InqIncrementalSymbols(BandProfile*, std::vector<Symbol>&) const;
    virtual int GetNumCompletedLessons(BandProfile*) const;
    virtual int GetTotalNumLessons() const;

    void Configure(DataArray*);

    std::vector<Symbol> mLessons; // 0x7c
};