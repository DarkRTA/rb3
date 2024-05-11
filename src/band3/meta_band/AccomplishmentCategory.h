#ifndef METABAND_ACCOMPLISHMENTCATEGORY_H
#define METABAND_ACCOMPLISHMENTCATEGORY_H
#include "system/obj/Data.h"
#include "Award.h"

class AccomplishmentCategory {
    AccomplishmentCategory(const DataArray*, int);
    virtual ~AccomplishmentCategory();
    void Configure(const DataArray*);
    Symbol GetName() const;
    int GetIndex() const;
    Symbol GetGroup() const;
    Symbol GetAward() const;
    bool HasAward() const;

    int mIndex;
    Symbol mName;
    Symbol mGroup;
    Symbol mAward;

};
#endif // METABAND_ACCOMPLISHMENTCATEGORY_H