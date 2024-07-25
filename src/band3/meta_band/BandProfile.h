#ifndef METABAND_BANDPROFILE_H
#define METABAND_BANDPROFILE_H

#include "system/utl/Symbol.h"

class BandProfile {
public:
    BandProfile(int);
    virtual ~BandProfile();

    bool IsLessonComplete(const Symbol&, float) const;
};

#endif // METABAND_BANDPROFILE_H