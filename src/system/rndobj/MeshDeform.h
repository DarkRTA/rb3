#ifndef RNDOBJ_MESHDEFORM_H
#define RNDOBJ_MESHDEFORM_H
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "obj/ObjVector.h"
#include "utl/MemMgr.h"

class RndMesh;
class SyncMeshCB;

class RndMeshDeform : public Hmx::Object {
public:
    class VertArray {
    public:
        VertArray(RndMeshDeform *);
        ~VertArray();
        void Clear();
        int NumVerts();
        void *FindVert(int);
        void CopyVert(int, int, VertArray &);
        void AppendWeights(int, int *, float *);
        void SetSize(int);
        void Copy(const VertArray &);
        void Load(BinStream &);

        int mSize;
        void *mData;
        RndMeshDeform *mParent;
    };

    // size 0x6c
    class BoneDesc {
    public:
        u8 pad[0x6c];
    };

    RndMeshDeform();
    virtual ~RndMeshDeform();
    OBJ_CLASSNAME(MeshDeform);
    OBJ_SET_TYPE(MeshDeform);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);
    virtual void PreSave(BinStream &);
    virtual void Print();

    void CopyWeights(int, int, RndMeshDeform *);
    void Reskin(SyncMeshCB *, bool);
    void SetNumBones(int);
    void SetMesh(RndMesh *);
    RndMesh *Mesh() const { return mMesh; }

    NEW_OVERLOAD
    DELETE_OVERLOAD
    NEW_OBJ(RndMeshDeform)
    DECLARE_REVS
    static void Init() { REGISTER_OBJ_FACTORY(RndMeshDeform) }
    static RndMeshDeform *FindDeform(RndMesh *);

    ObjPtr<RndMesh, ObjectDir> mMesh; // 0x1c
    Transform mMeshInverse; // 0x28
    ObjVector<BoneDesc> mBones; // 0x58
    VertArray mVerts; // 0x68
    bool mSkipInverse;
    bool mDeformed;
};

#endif
