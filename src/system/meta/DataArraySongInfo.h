#ifndef META_DATAARRAYSONGINFO_H
#define META_DATAARRAYSONGINFO_H
#include "utl/SongInfoCopy.h"
#include "obj/Data.h"
#include "utl/BinStream.h"

class DataArraySongInfo : public SongInfoCopy {
public:
    DataArraySongInfo(DataArray*, DataArray*, Symbol);
    DataArraySongInfo(SongInfo*);
    DataArraySongInfo();
    virtual ~DataArraySongInfo();

    void* operator new(size_t ul){
        return _MemAlloc(ul, 0);
    }

    void operator delete(void* v){
        return _MemFree(v);
    }

};

BinStream& operator<<(BinStream&, const DataArraySongInfo&);
BinStream& operator>>(BinStream&, DataArraySongInfo&);

#endif
