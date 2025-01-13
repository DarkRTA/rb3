#pragma once
#include "char/CharBones.h"
#include "obj/ObjVector.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"

/** "Holds state for a set of bones, allocates own space, and sets meshes accordingly" */
class CharBonesMeshes : public CharBonesAlloc {
public:
    CharBonesMeshes();
    virtual ~CharBonesMeshes();
    virtual void ReallocateInternal();
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Replace(Hmx::Object*, Hmx::Object*);

    void AcquirePose();
    void PoseMeshes();
    void StuffMeshes(std::list<Hmx::Object*>&);

    /** "Transes we will change" */
    ObjVector<ObjOwnerPtr<RndTransformable> > mMeshes; // 0x54
    RndTransformable* mDummyMesh; // 0x60
};
