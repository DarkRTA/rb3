#ifndef META_DATAARRAYSONGINFO_H
#define META_DATAARRAYSONGINFO_H
#include "utl/SongInfoCopy.h"
#include "obj/Data.h"
#include "utl/BinStream.h"

class DataArraySongInfo : public SongInfoCopy {
public:
    DataArraySongInfo(DataArray*, DataArray*, Symbol);
    DataArraySongInfo();
    virtual ~DataArraySongInfo();

    void* operator new(size_t ul){
        return _MemAlloc(ul, 0);
    }

    char filler[0x50];
};

BinStream& operator<<(BinStream&, const DataArraySongInfo&);
BinStream& operator>>(BinStream&, DataArraySongInfo&);

#endif
