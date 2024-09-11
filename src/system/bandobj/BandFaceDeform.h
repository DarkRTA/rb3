#pragma once
#include "obj/Object.h"

class BandFaceDeform : public Hmx::Object {
public:
    class DeltaArray {
    public:
        DeltaArray();
        ~DeltaArray();
        int unk0;
        int unk4;
    };

    BandFaceDeform();
    virtual ~BandFaceDeform();
    OBJ_CLASSNAME(BandFaceDeform);
    OBJ_SET_TYPE(BandFaceDeform);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    std::vector<DeltaArray> unk1c; // 0x1c
};