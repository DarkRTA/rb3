#ifndef WORLD_CROWD_H
#define WORLD_CROWD_H
#include "rndobj/Draw.h"
#include "rndobj/Poll.h"
#include "rndobj/Mesh.h"
#include "rndobj/Env.h"

class WorldCrowd : public RndDrawable, public RndPollable {
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

    void CleanUpCrowdFloor();
    int GetModifyStamp() const { return unk88; }

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(WorldCrowd)
    static void Init(){
        REGISTER_OBJ_FACTORY(WorldCrowd)
    }

    ObjPtr<RndMesh, ObjectDir> unk28;
    ObjList<int> unk34;
    int unk40;
    int unk44;
    int unk48;
    int unk4c;
    int unk50;
    bool unk54;
    bool unk55;
    float unk58;
    float unk5c;
    int unk60;
    ObjPtr<RndEnviron, ObjectDir> unk64;
    ObjPtr<RndEnviron, ObjectDir> unk70;
    ObjPtr<RndTransformable, ObjectDir> unk7c;
    int unk88;
};

#endif
