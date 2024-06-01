#ifndef RNDOBJ_MESHDEFORM_H
#define RNDOBJ_MESHDEFORM_H
#include "obj/Object.h"

class RndMeshDeform : public Hmx::Object {
public:
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

    NEW_OBJ(RndMeshDeform)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndMeshDeform)
    }

};

#endif
