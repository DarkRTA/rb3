#ifndef RNDOBJ_MESHANIM_H
#define RNDOBJ_MESHANIM_H
#include "rndobj/Anim.h"

class RndMeshAnim : public RndAnimatable {
public:
    RndMeshAnim();
    OBJ_CLASSNAME(MeshAnim);
    OBJ_SET_TYPE(MeshAnim);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~RndMeshAnim();
    virtual void SetFrame(float, float);
    virtual float EndFrame();
    virtual Hmx::Object* AnimTarget();
    virtual void SetKey(float);
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Print();

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndMeshAnim)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndMeshAnim)
    }
};

#endif
