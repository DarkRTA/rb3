#ifndef METABAND_ACCOMPLISHMENTCONDITIONAL_H
#define METABAND_ACCOMPLISHMENTCONDITIONAL_H

#include "Accomplishment.h"

struct AccomplishmentCondition {
    Symbol mCondition;   // 0x00
    int mValue;  // 0x04
    ScoreType mScoreType;  // 0x08
    Difficulty mDifficulty;  // 0x0c
};

class AccomplishmentConditional : public Accomplishment {
public:
    AccomplishmentConditional(DataArray*, int);
    virtual ~AccomplishmentConditional();
    void UpdateConditionOptionalData(AccomplishmentCondition&, DataArray*);
    void Configure(DataArray*);
    virtual bool CanBeLaunched() const;
    virtual bool InqRequiredScoreTypes(std::set<ScoreType>&) const;
    virtual Difficulty GetRequiredDifficulty() const;

    std::vector<AccomplishmentCondition> m_lConditions; // 0x74
};

#endif // METABAND_ACCOMPLISHMENTCONDITIONAL_H