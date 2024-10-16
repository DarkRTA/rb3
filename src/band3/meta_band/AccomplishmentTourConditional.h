#pragma once
#include "meta_band/Accomplishment.h"
#include "obj/Data.h"
#include "tour/TourGameRules.h"

struct AccomplishmentTourCondition {
    AccomplishmentTourCondition(){}
    Symbol mCondition;
    int mValue;
    TourGameType mGameType;
    Symbol mTourDesc;
};

class AccomplishmentTourConditional : public Accomplishment {
public:
    AccomplishmentTourConditional(DataArray*, int);
    virtual ~AccomplishmentTourConditional();
    virtual AccomplishmentType GetType() const;
    virtual bool IsFulfilled(BandProfile*) const;
    virtual bool InqProgressValues(BandProfile*, int&, int&);
    virtual bool CanBeLaunched() const;

    void Configure(DataArray*);
    bool IsConditionMet(BandProfile*, const AccomplishmentTourCondition&) const;
    void UpdateConditionOptionalData(AccomplishmentTourCondition&, DataArray*);
    bool InqBestProgressValues(BandProfile*, int&, int&);
    bool InqConditionProgress(BandProfile*, const AccomplishmentTourCondition&, int&, int&) const;
    Symbol GetAssociatedTour() const;
    int GetTourValue() const;

    std::list<AccomplishmentTourCondition> m_vConditions; // 0x74
};