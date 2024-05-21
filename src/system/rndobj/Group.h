#ifndef RNDOBJ_GROUP_H
#define RNDOBJ_GROUP_H
#include "rndobj/Trans.h"
#include "rndobj/Draw.h"
#include "rndobj/Anim.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Env.h"
#include <vector>

class RndGroup : public RndAnimatable, public RndDrawable, public RndTransformable {
public:
    RndGroup();
    OBJ_CLASSNAME(Group)
    OBJ_SET_TYPE(Group)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual ~RndGroup();
    virtual void StartAnim();
    virtual void EndAnim();
    virtual void SetFrame(float, float);
    virtual float EndFrame();
    virtual void ListAnimChildren(std::list<RndAnimatable*>&) const;
    virtual void UpdateSphere();
    virtual float GetDistanceToPlane(const Plane&, Vector3&);
    virtual bool MakeWorldSphere(Sphere&, bool);
    virtual void DrawShowing();
    virtual void ListDrawChildren(std::list<RndDrawable*>&);
    virtual int CollideShowing(const Segment&, float&, Plane&);
    virtual void CollideList(const Segment&, std::list<Collision>&);
    virtual int CollidePlane(const Plane&);
    virtual bool DrawShowingBudget(float);
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Highlight();

    void Update();
    void UpdateLODState();
    void Merge(const RndGroup*);
    void RemoveObject(Hmx::Object*);

    ObjPtrList<Hmx::Object, ObjectDir> mObjects;
    ObjPtr<RndEnviron, ObjectDir> mEnv;
    ObjPtr<RndDrawable, ObjectDir> mDrawOnly;
    ObjPtr<RndDrawable, ObjectDir> mLod;
    float mLodScreenSize;
    bool unkf8;
    std::vector<int> mAnims;
    std::vector<int> mDraws;
    int asdf;
};

#endif
