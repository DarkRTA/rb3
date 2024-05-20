#ifndef METABAND_PROFILEMGR_H
#define METABAND_PROFILEMGR_H

#include "obj/Object.h"
class ProfileMgr : public virtual Hmx::Object {
    public:
    int GetSliderStepCount() const;
};

extern ProfileMgr TheProfileMgr;

#endif // METABAND_PROFILEMGR_H