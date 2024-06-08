#ifndef RNDOBJ_MULTIMESHPROXY_H
#define RNDOBJ_MULTIMESHPROXY_H
#include "rndobj/Trans.h"
#include "rndobj/Draw.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/MultiMesh.h"
#include <list>

class RndMultiMeshProxy : public RndTransformable, public RndDrawable {
public:
    RndMultiMeshProxy();
    OBJ_CLASSNAME(RndMultiMeshProxy);
    OBJ_SET_TYPE(RndMultiMeshProxy);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~RndMultiMeshProxy(){}
    virtual void Highlight(){ RndDrawable::Highlight(); }
    virtual void UpdatedWorldXfm();
    virtual void DrawShowing();

    void SetMultiMesh(RndMultiMesh*, const std::list<RndMultiMesh::Instance>::iterator&);

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndMultiMeshProxy)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndMultiMeshProxy)
    }

    ObjPtr<RndMultiMesh, ObjectDir> mMultiMesh; // 0xb0
    std::list<RndMultiMesh::Instance>::iterator mIndex; // 0xbc
};

#endif
