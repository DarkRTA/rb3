#ifndef METABAND_ACCOMPLISHMENTCONDITIONAL_H
#define METABAND_ACCOMPLISHMENTCONDITIONAL_H

#include "Accomplishment.h"

class AccomplishmentCondition {

};

class AccomplishmentConditional : public Accomplishment {
public:
    AccomplishmentConditional(DataArray*, int);
    virtual ~AccomplishmentConditional();
    void UpdateConditionOptionalData(AccomplishmentCondition&, DataArray*);
    virtual void Configure(DataArray*);
    bool CanBeLaunched() const;
    void InqRequiredScoreTypes(std::set<ScoreType>&) const;
    virtual Difficulty GetRequiredDifficulty() const;

private:
    std::vector<AccomplishmentCondition> mConditions;
};

#endif // METABAND_ACCOMPLISHMENTCONDITIONAL_H