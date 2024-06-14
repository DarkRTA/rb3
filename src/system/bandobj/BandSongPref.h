#pragma once

#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "utl/MemMgr.h"
class BandSongPref : public Hmx::Object {
    BandSongPref();
    virtual ~BandSongPref() {}
    OBJ_CLASSNAME(BandSongPref)
    OBJ_SET_TYPE(BandSongPref)
    virtual void Save(BinStream&);
    virtual void Load(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);

    DECLARE_REVS
    DELETE_OVERLOAD

    Symbol mPart2Instrument, mPart3Instrument, mPart4Instrument, mAnimGenre;
};