#ifndef RNDOBJ_POLLANIM_H
#define RNDOBJ_POLLANIM_H
#include "rndobj/Anim.h"
#include "rndobj/Poll.h"
#include "obj/ObjPtr_p.h"

/**
* @brief: An object that polls animatables at a set time.
* Original _objects description:
* "Class that drives Anims with time based on their rate."
*/
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

    /** The list of animatables to poll. */
    ObjPtrList<RndAnimatable> mAnims; // 0x10
};

#endif
