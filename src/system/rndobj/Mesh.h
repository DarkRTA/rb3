#ifndef RNDOBJ_MESH_H
#define RNDOBJ_MESH_H
#include "rndobj/Draw.h"
#include "rndobj/Trans.h"

class RndMesh : public RndDrawable {
public:
    RndMesh();
    OBJ_CLASSNAME(Mesh);
    OBJ_SET_TYPE(Mesh);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void UpdateSphere();
    virtual float GetDistanceToPlane(const Plane&, Vector3&);
    virtual int MakeWorldSphere(Sphere&, bool);
    virtual void Mats(std::list<class RndMat*>&, bool);
    virtual int CollideShowing(const Segment&, float&, Plane&);
    virtual int CollidePlane(const Plane&);
    virtual void Highlight();
    virtual ~RndMesh();

    // TODO: figure out what RndMesh's members are
    int filler;
};

#endif
