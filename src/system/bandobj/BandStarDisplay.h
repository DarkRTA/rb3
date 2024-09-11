#pragma once
#include "rndobj/Dir.h"
#include "synth/Sequence.h"

class BandStarDisplay : public RndDir {
public:
    BandStarDisplay();
    OBJ_CLASSNAME(BandStarDisplay)
    OBJ_SET_TYPE(BandStarDisplay)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual ~BandStarDisplay();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SyncObjects();

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    float unk18c; // 0x18c
    ObjVector<int> unk190; // 0x190
    ObjVector<int> unk19c; // 0x19c
    ObjVector<int> unk1a8; // 0x1a8
    ObjVector<int> unk1b4; // 0x1b4
    ObjPtr<RndAnimatable, ObjectDir> unk1c0; // 0x1c0
    ObjPtr<Sequence, ObjectDir> unk1cc; // 0x1cc
    ObjPtr<Sequence, ObjectDir> unk1d8; // 0x1d8
    Symbol unk1e4; // 0x1e4
};