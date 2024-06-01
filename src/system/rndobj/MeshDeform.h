#ifndef RNDOBJ_MESHDEFORM_H
#define RNDOBJ_MESHDEFORM_H
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "obj/ObjVector.h"

class RndMesh;

class RndMeshDeform : public Hmx::Object {
public:
    class VertArray {
    public:
        VertArray(RndMeshDeform*);
        ~VertArray();
        void Clear();
        void SetSize(int);

        int mSize;
        void* mData;
        RndMeshDeform* mParent;
    };

    // size 0x6c
    class BoneDesc {
    public:
    };

    RndMeshDeform();
    virtual ~RndMeshDeform();
    OBJ_CLASSNAME(MeshDeform);
    OBJ_SET_TYPE(MeshDeform);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void PreSave(BinStream&);
    virtual void Print();

    void SetMesh(RndMesh*);

    NEW_OVERLOAD
    NEW_OBJ(RndMeshDeform)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndMeshDeform)
    }

    ObjPtr<RndMesh, ObjectDir> mMesh;
    Transform mMeshInverse;
    ObjVector<BoneDesc> mBones;
    VertArray mVerts;
    bool mSkipInverse;
    bool mDeformed;

};

#endif
