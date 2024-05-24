#ifndef METABAND_ACCOMPLISHMENTCATEGORY_H
#define METABAND_ACCOMPLISHMENTCATEGORY_H
#include "system/obj/Data.h"

class AccomplishmentCategory {
public:
    AccomplishmentCategory(const DataArray*, int);
    virtual ~AccomplishmentCategory();

private:
    void Configure(const DataArray*);
    Symbol GetName() const;
    int GetIndex() const;
    Symbol GetGroup() const;
    Symbol GetAward() const;
    bool HasAward() const;

    int mIndex;         // 0x04
    Symbol mName;       // 0x08
    Symbol mGroup;      // 0x0c
    Symbol mAward;      // 0x10
};
#endif // METABAND_ACCOMPLISHMENTCATEGORY_H