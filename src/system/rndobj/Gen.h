#ifndef RNDOBJ_GENERATOR_H
#define RNDOBJ_GENERATOR_H
#include "rndobj/Anim.h"
#include "rndobj/Draw.h"
#include "rndobj/Trans.h"

class RndGenerator : public RndAnimatable, public RndTransformable, public RndDrawable {
public:
    RndGenerator();
    OBJ_CLASSNAME(Generator);
    OBJ_SET_TYPE(Generator);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~RndGenerator();
    virtual void SetFrame(float, float);
    virtual float StartFrame();
    virtual float EndFrame();
    virtual void ListAnimChildren(std::list<RndAnimatable*>&) const;
    virtual void DrawShowing();
    virtual void UpdateSphere();
    virtual bool MakeWorldSphere(Sphere&, bool);
    virtual void ListDrawChildren(std::list<RndDrawable*>&);
    virtual void Highlight();
    virtual void Print();

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndGenerator)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndGenerator)
    }
};

#endif
