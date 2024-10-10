#ifndef METABAND_PROFILEMGR_H
#define METABAND_PROFILEMGR_H
#include "obj/MsgSource.h"
#include "meta/Profile.h"

class ProfileMgr : public MsgSource {
public:
    int GetSliderStepCount() const;
    Profile* GetProfileForUser(const LocalUser*);
    void SetCymbalConfiguration(unsigned int);

};

extern ProfileMgr TheProfileMgr;

#endif // METABAND_PROFILEMGR_H