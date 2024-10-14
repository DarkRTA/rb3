#ifndef METABAND_ACCOMPLISHMENTGROUP_H
#define METABAND_ACCOMPLISHMENTGROUP_H

#include "system/obj/Data.h"
#include "Accomplishment.h"

class AccomplishmentGroup {
public:
    AccomplishmentGroup(DataArray*, int);
    virtual ~AccomplishmentGroup();

    virtual void Configure(DataArray*);
    int GetIndex() const;
    Symbol GetName() const;
    char GetInstrumentIcon();
    Symbol GetAward() const;
    bool HasAward() const;

    Symbol mName; // 0x04
    int mIndex;   // 0x08
    char mInstrumentIcon; // 0x0c
    ScoreType mScoreType; // 0x10
    Symbol mAward; // 0x14
};

#endif // METABAND_ACCOMPLISHMENTGROUP_H

