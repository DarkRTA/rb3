#ifndef META_DATAARRAYSONGINFO_H
#define META_DATAARRAYSONGINFO_H
#include "utl/SongInfoCopy.h"
#include "obj/Data.h"

class DataArraySongInfo : public SongInfoCopy {
public:
    DataArraySongInfo(DataArray*, DataArray*, Symbol);
    DataArraySongInfo();
    virtual ~DataArraySongInfo();

    char filler[0x50];
};

#endif
