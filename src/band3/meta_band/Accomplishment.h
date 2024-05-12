#ifndef METABAND_ACCOMPLISHMENT_H
#define METABAND_ACCOMPLISHMENT_H

#include "system/obj/Data.h"

class Accomplishment {
public:
    Accomplishment(DataArray*, int);
    virtual ~Accomplishment();
    void Configure(DataArray*);
    void GetType() const;
    void GetName() const;
};
#endif // METABAND_ACCOMPLISHMENT_H