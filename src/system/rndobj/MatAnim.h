#ifndef RNDOBJ_MATANIM_H
#define RNDOBJ_MATANIM_H
#include "rndobj/Anim.h"

class RndMatAnim : public RndAnimatable {
public:
    RndMatAnim();
    OBJ_CLASSNAME(MatAnim);
    OBJ_SET_TYPE(MatAnim);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~RndMatAnim();
    virtual void SetFrame(float, float);
    virtual float EndFrame();
    virtual Hmx::Object* AnimTarget();
    virtual void SetKey(float);
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Print();

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndMatAnim)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndMatAnim)
    }
};

#endif
