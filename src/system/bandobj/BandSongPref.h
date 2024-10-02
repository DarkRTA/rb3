#pragma once
#include "obj/Object.h"
#include "utl/MemMgr.h"

class BandSongPref : public Hmx::Object {
public:
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
    NEW_OVERLOAD
    DELETE_OVERLOAD

    Symbol Part2Inst() const { return mPart2Instrument; }
    Symbol Part3Inst() const { return mPart3Instrument; }
    Symbol Part4Inst() const { return mPart4Instrument; }
    Symbol GetAnimGenre() const { return mAnimGenre; }

    Symbol mPart2Instrument, mPart3Instrument, mPart4Instrument, mAnimGenre;
};