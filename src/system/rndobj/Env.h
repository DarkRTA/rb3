#ifndef RNDOBJ_ENV_H
#define RNDOBJ_ENV_H
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "math/Vec.h"

class _GXColor;
class RndLight;

class RndEnviron : public Hmx::Object {
public:
    RndEnviron();
    virtual ~RndEnviron();
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    OBJ_CLASSNAME(Environ);
    OBJ_SET_TYPE(Environ);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void Select(const Vector3*);
    virtual void ApplyApproxLighting(const _GXColor*);
    virtual bool HasPointCubeTex(void) const;
    virtual bool IsFake(RndLight*) const;
    virtual bool IsReal(RndLight*) const;
};

#endif
