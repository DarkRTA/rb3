#ifndef RNDOBJ_LINE_H
#define RNDOBJ_LINE_H
#include "rndobj/Draw.h"
#include "rndobj/Trans.h"

class RndLine : public RndDrawable, public RndTransformable {
public:
    RndLine();
    OBJ_CLASSNAME(Line);
    OBJ_SET_TYPE(Line);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void UpdateSphere();
    virtual float GetDistanceToPlane(const Plane&, Vector3&);
    virtual bool MakeWorldSphere(Sphere&, bool);
    virtual void Mats(std::list<class RndMat*>&, bool);
    virtual void DrawShowing();
    virtual RndDrawable* CollideShowing(const Segment&, float&, Plane&);
    virtual int CollidePlane(const Plane&);
    virtual void Highlight();
    virtual ~RndLine();
    virtual int Mesh() const; // fix return type
    virtual void Print();

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndLine)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndLine)
    }
};

#endif
