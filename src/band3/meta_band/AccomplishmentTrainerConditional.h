#ifndef METABAND_ACCOMPLISHMENTTRAINERCONDITIONAL_H
#define METABAND_ACCOMPLISHMENTTRAINERCONDITIONAL_H

#include "Accomplishment.h"

struct TrainerCondition {
    Symbol c;
    float d;
};

class AccomplishmentTrainerConditional : public Accomplishment {
public:
    AccomplishmentTrainerConditional(DataArray*, int);
    virtual ~AccomplishmentTrainerConditional();
private:
    void Configure(DataArray*);
    bool CheckLessonCompleteCondition(BandProfile*, Symbol, float) const;
    bool CheckConditionsForLesson(BandProfile*, Symbol) const;
    virtual void UpdateIncrementalEntryName(UILabel*, Symbol);
    virtual bool InqProgressValues(BandProfile*, int&, int&);
    virtual bool IsSymbolEntryFulfilled(BandProfile*, Symbol) const;
    virtual bool ShowBestAfterEarn() const;
    virtual bool CanBeLaunched() const;
    std::list<TrainerCondition> mConditions;
};

#endif // METABAND_ACCOMPLISHMENTTRAINERCONDITIONAL_H