#ifndef RNDOBJ_PROPANIM_H
#define RNDOBJ_PROPANIM_H
#include "rndobj/Anim.h"
#include "obj/Object.h"
#include <vector>
#include "rndobj/PropKeys.h"

class RndPropAnim : public RndAnimatable {
public:
    RndPropAnim();
    OBJ_CLASSNAME(PropAnim);
    OBJ_SET_TYPE(PropAnim);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~RndPropAnim();
    virtual bool Loop(){ return mLoop; }
    virtual void StartAnim(){}
    virtual void EndAnim(){}
    virtual void SetFrame(float, float);
    virtual float StartFrame();
    virtual float EndFrame();
    virtual void SetKey(float);
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Print();

    void RemoveKeys();
    
    std::vector<PropKeys> mPropKeys;
    float mLastFrame;
    bool mInSetFrame;
    bool mLoop;
};

// class RndPollable : public virtual Hmx::Object {
// public:
//     RndPollable(){}
//     OBJ_CLASSNAME(Poll);
//     OBJ_SET_TYPE(Poll);
//     virtual DataNode Handle(DataArray*, bool);
//     virtual void Poll(){}
//     virtual void Enter();
//     virtual void Exit();
//     virtual void ListPollChildren(std::list<RndPollable*>&) const {}
//     virtual ~RndPollable(){}
// };

#endif
