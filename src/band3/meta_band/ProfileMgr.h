#ifndef METABAND_PROFILEMGR_H
#define METABAND_PROFILEMGR_H
#include "obj/Object.h"
#include "meta/Profile.h"

class ProfileMgr : public virtual Hmx::Object {
public:
    int GetSliderStepCount() const;
    Profile* GetProfileForUser(const LocalUser*);
    void SetCymbalConfiguration(unsigned int);

};

extern ProfileMgr TheProfileMgr;

#endif // METABAND_PROFILEMGR_H