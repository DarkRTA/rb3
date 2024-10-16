#ifndef METABAND_ACCOMPLISHMENTTRAINERCATEGORYCONDITIONAL_H
#define METABAND_ACCOMPLISHMENTTRAINERCATEGORYCONDITIONAL_H
#include "system/obj/Data.h"
#include "BandProfile.h"

#include "Accomplishment.h"
#include "AccomplishmentTrainerConditional.h"

class AccomplishmentTrainerCategoryConditional : public AccomplishmentTrainerConditional {
    AccomplishmentTrainerCategoryConditional(DataArray*, int);
    virtual ~AccomplishmentTrainerCategoryConditional();
    void Configure(DataArray*);
    virtual AccomplishmentType GetType() const;
    virtual bool IsFulfilled(BandProfile*) const;
    virtual int GetNumCompletedLessons(BandProfile*) const;
    virtual bool InqIncrementalSymbols(BandProfile*, std::vector<Symbol>&) const;
    virtual Symbol GetFirstUnfinishedAccomplishmentEntry(BandProfile*) const;
    virtual int GetTotalNumLessons() const;
    void InqCompletedLessons(BandProfile*, std::vector<Symbol>&) const;
private:
    Symbol m0x7c;
    int m0x80;
};
#endif // METABAND_ACCOMPLISHMENTTRAINERCATEGORYCONDITIONAL_H