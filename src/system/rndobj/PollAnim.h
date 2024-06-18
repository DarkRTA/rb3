#ifndef RNDOBJ_POLLANIM_H
#define RNDOBJ_POLLANIM_H
#include "rndobj/Anim.h"
#include "rndobj/Poll.h"
#include "obj/ObjPtr_p.h"

class RndPollAnim : public virtual RndAnimatable, public virtual RndPollable, public virtual Hmx::Object {
public:
    RndPollAnim();
    OBJ_CLASSNAME(PollAnim);
    OBJ_SET_TYPE(PollAnim);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void StartAnim();
    virtual void EndAnim();
    virtual void SetFrame(float, float);
    virtual float EndFrame();
    virtual void ListAnimChildren(std::list<RndAnimatable*>&) const;
    virtual void Poll();
    virtual void Enter();
    virtual void Exit();
    virtual ~RndPollAnim(){}

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndPollAnim)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndPollAnim)
    }

    ObjPtrList<RndAnimatable, ObjectDir> mAnims;
};

#endif
