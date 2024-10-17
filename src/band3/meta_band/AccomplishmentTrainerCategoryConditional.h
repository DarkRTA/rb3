#ifndef METABAND_ACCOMPLISHMENTTRAINERCATEGORYCONDITIONAL_H
#define METABAND_ACCOMPLISHMENTTRAINERCATEGORYCONDITIONAL_H
#include "system/obj/Data.h"
#include "BandProfile.h"

#include "Accomplishment.h"
#include "AccomplishmentTrainerConditional.h"

class AccomplishmentTrainerCategoryConditional : public AccomplishmentTrainerConditional {
public:
    AccomplishmentTrainerCategoryConditional(DataArray*, int);
    virtual ~AccomplishmentTrainerCategoryConditional();
    virtual AccomplishmentType GetType() const;
    virtual bool IsFulfilled(BandProfile*) const;
    virtual bool InqIncrementalSymbols(BandProfile*, std::vector<Symbol>&) const;
    virtual Symbol GetFirstUnfinishedAccomplishmentEntry(BandProfile*) const;
    virtual int GetNumCompletedLessons(BandProfile*) const;
    virtual int GetTotalNumLessons() const;

    bool InqCompletedLessons(BandProfile*, std::vector<Symbol>&) const;
    void Configure(DataArray*);
    
    Symbol mCategory; // 0x7c
    int mNumLessons; // 0x80
};
#endif // METABAND_ACCOMPLISHMENTTRAINERCATEGORYCONDITIONAL_H