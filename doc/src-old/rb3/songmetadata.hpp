#ifndef RB3_SONGMETADATA_HPP
#define RB3_SONGMETADATA_HPP
#include "obj/Data.h"
#include "obj/Object.h"
#include "utl/Symbol.h"

class SongMetadata : public Hmx::Object {
public:
    SongMetadata();
    SongMetadata(DataArray*, DataArray*, bool); // https://decomp.me/scratch/vjSkv
    virtual ~SongMetadata();
    virtual DataNode Handle(DataArray*, bool);
    virtual void Save(BinStream&);
    virtual void Load(BinStream&);

    void Initialize();

    short version;
    Symbol shortname; // song shortname?
    int songId;
    bool unk28;
    Symbol songSrc; // game_origin
    float previewStart;
    float previewEnd;
    int unk38; // actually a DataArraySongInfo*
    int unk3c;
};

#endif
