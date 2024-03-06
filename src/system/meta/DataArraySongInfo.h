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
    virtual void Save(BinStream&) const;
    virtual void Load(BinStream&);
    virtual void SetBaseFileName(const char*);
    virtual void AddExtraMidiFile(const char*, const char*);

    static int sSaveVer;

    void* operator new(size_t ul){
        return _MemAlloc(ul, 0);
    }

    void operator delete(void* v){
        return _MemFree(v);
    }

};

BinStream& operator<<(BinStream& bs, const DataArraySongInfo& dinfo){
    dinfo.Save(bs);
    return bs;
}

BinStream& operator>>(BinStream& bs, DataArraySongInfo& dinfo){
    dinfo.Load(bs);
    return bs;
}

#endif
