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

    ObjVector<ObjOwnerPtr<RndTransformable, ObjectDir> > mMeshes;
    RndTransformable* mDummyMesh;
};

#endif
