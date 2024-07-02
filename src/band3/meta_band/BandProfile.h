#ifndef METABAND_BANDPROFILE_H
#define METABAND_BANDPROFILE_H

#include "system/meta/Profile.h"

class BandProfile : public Profile, virtual Hmx::Object {
public:
    BandProfile(int);
    virtual ~BandProfile();
    void SaveFixed(FixedSizeSaveableStream&) const;
    void LoadFixed(FixedSizeSaveableStream&, int);

    void SaveSize(int);
};

#endif // METABAND_BANDPROFILE_H
