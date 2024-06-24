#ifndef METABAND_ACCOMPLISHMENTCONDITIONAL_H
#define METABAND_ACCOMPLISHMENTCONDITIONAL_H

#include "Accomplishment.h"

struct AccomplishmentCondition {
    Symbol s;   // 0x00
    int test2;  // 0x04
    ScoreType scoreType;  // 0x08
    Difficulty difficulty;  // 0x0c
};

class AccomplishmentConditional : public Accomplishment {
public:
    AccomplishmentConditional(DataArray*, int);
    virtual ~AccomplishmentConditional();
    void UpdateConditionOptionalData(AccomplishmentCondition&, DataArray*);
    virtual void Configure(DataArray*);
    virtual bool CanBeLaunched() const;
    virtual bool InqRequiredScoreTypes(std::set<ScoreType>&) const;
    virtual Difficulty GetRequiredDifficulty() const;

private:
    // starts at 0x74
    std::vector<AccomplishmentCondition> m_lConditions; 
};

#endif // METABAND_ACCOMPLISHMENTCONDITIONAL_H