#pragma once
#include "obj/Object.h"
#include "rndobj/MeshAnim.h"

class BandFaceDeform : public Hmx::Object {
public:
    class DeltaArray {
    public:
        DeltaArray();
        DeltaArray(const DeltaArray&);
        ~DeltaArray();
        int NumVerts();

        DeltaArray& operator=(const DeltaArray&);

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

    int TotalSize();
    void SetFromMeshAnim(RndMeshAnim*, RndMeshAnim*, int, int);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    std::vector<DeltaArray> mFrames; // 0x1c
};