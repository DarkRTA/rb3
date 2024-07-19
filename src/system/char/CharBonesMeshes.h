#ifndef CHAR_CHARBONESMESHES_H
#define CHAR_CHARBONESMESHES_H
#include "char/CharBones.h"
#include "obj/ObjVector.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"

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

    ObjVector<ObjOwnerPtr<RndTransformable, ObjectDir> > mMeshes; // 0x54
    RndTransformable* mDummyMesh; // 0x60
};

#endif
