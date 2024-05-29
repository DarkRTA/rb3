#ifndef WORLD_CROWD_H
#define WORLD_CROWD_H
#include "rndobj/Draw.h"

class WorldCrowd : public RndDrawable {
public:
    WorldCrowd();
    OBJ_CLASSNAME(WorldCrowd);
    OBJ_SET_TYPE(WorldCrowd);
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
    virtual void ListDrawChildren(std::list<RndDrawable*>&);
    virtual void CollideList(const Segment&, std::list<Collision>&);
    virtual ~WorldCrowd();
    virtual void ListPollChildren(std::list<RndPollable*>&) const;
    virtual void Poll();
    virtual void Enter();
    virtual void Exit();
};

#endif
