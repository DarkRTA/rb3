#ifndef RNDOBJ_PARTANIM_H
#define RNDOBJ_PARTANIM_H
#include "rndobj/Anim.h"

class RndParticleSysAnim : public RndAnimatable {
public:
    RndParticleSysAnim();
    OBJ_CLASSNAME(ParticleSysAnim);
    OBJ_SET_TYPE(ParticleSysAnim);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~RndParticleSysAnim();
    virtual void SetFrame(float, float);
    virtual float EndFrame();
    virtual Hmx::Object* AnimTarget();
    virtual void SetKey(float);
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Print();

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndParticleSysAnim)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndParticleSysAnim)
    }
};

#endif
