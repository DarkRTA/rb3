#ifndef METABAND_ACCOMPLISHMENTTRAINERCONDITIONAL_H
#define METABAND_ACCOMPLISHMENTTRAINERCONDITIONAL_H

#include "Accomplishment.h"

struct TrainerCondition {
    TrainerCondition(){}
    Symbol mCondition;
    float mValue;
};

class AccomplishmentTrainerConditional : public Accomplishment {
public:
    AccomplishmentTrainerConditional(DataArray*, int);
    virtual ~AccomplishmentTrainerConditional();
    virtual bool ShowBestAfterEarn() const;
    virtual void UpdateIncrementalEntryName(UILabel*, Symbol);
    virtual bool InqProgressValues(BandProfile*, int&, int&);
    virtual bool IsSymbolEntryFulfilled(BandProfile*, Symbol) const;
    virtual bool CanBeLaunched() const;
    virtual int GetNumCompletedLessons(BandProfile*) const = 0;
    virtual int GetTotalNumLessons() const = 0;
    
    void Configure(DataArray*);
    bool CheckLessonCompleteCondition(BandProfile*, Symbol, float) const;
    bool CheckConditionsForLesson(BandProfile*, Symbol) const;

    std::list<TrainerCondition> mConditions;
};

#endif // METABAND_ACCOMPLISHMENTTRAINERCONDITIONAL_H