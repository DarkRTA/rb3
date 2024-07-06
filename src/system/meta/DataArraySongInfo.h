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

    NEW_OVERLOAD;
    DELETE_OVERLOAD;

};

BinStream& operator<<(BinStream& bs, const DataArraySongInfo& dinfo);
BinStream& operator>>(BinStream& bs, DataArraySongInfo& dinfo);

#define FIND_WITH_BACKUP(sym) \
    ((member_arr = main_arr->FindArray(sym, false), member_arr) || (backup_arr && (member_arr = backup_arr->FindArray(sym, false), member_arr)))

#endif
