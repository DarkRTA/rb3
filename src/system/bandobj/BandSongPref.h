#pragma once
#include "obj/Object.h"
#include "utl/MemMgr.h"

/** "Band Song Preferences, per song file settable properties" */
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
    NEW_OBJ(BandSongPref)
    static void Init() {
        Register();
    }
    REGISTER_OBJ_FACTORY_FUNC(BandSongPref)

    Symbol Part2Inst() const { return mPart2Instrument; }
    Symbol Part3Inst() const { return mPart3Instrument; }
    Symbol Part4Inst() const { return mPart4Instrument; }
    Symbol GetAnimGenre() const { return mAnimGenre; }

    /** "Who should sing the vocal part2?" Can choose from guitar, bass, drum */
    Symbol mPart2Instrument; // 0x1c
    /** "Who should sing the vocal part3?" Can choose from guitar, bass, drum */
    Symbol mPart3Instrument; // 0x20
    /** "Who should sing the vocal part4?" Can choose from guitar, bass, drum */
    Symbol mPart4Instrument; // 0x24
    /** "Animation genre for the song" Can choose from banger, dramatic, rocker, spazz */
    Symbol mAnimGenre; // 0x28
};