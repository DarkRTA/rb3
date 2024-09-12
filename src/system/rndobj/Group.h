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
    virtual ~RndGroup(){}
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
    virtual RndDrawable* CollideShowing(const Segment&, float&, Plane&);
    virtual void CollideList(const Segment&, std::list<Collision>&);
    virtual int CollidePlane(const Plane&);
    virtual bool DrawShowingBudget(float);
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Highlight(){ RndDrawable::Highlight(); }

    void Update();
    void UpdateLODState();
    void Merge(const RndGroup*);
    void RemoveObject(Hmx::Object*);
    void AddObject(Hmx::Object*, Hmx::Object*);
    void ClearObjects();
    void SortDraws();
    void AddObjectAtFront(Hmx::Object*);
    DataNode OnGetDraws(DataArray*);
    RndEnviron* GetEnv() const { return mEnv; }
    void SetEnv(RndEnviron* env){ mEnv = env; }

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndGroup)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndGroup)
    }

    ObjPtrList<Hmx::Object, ObjectDir> mObjects; // 0xc0
    ObjPtr<RndEnviron, ObjectDir> mEnv; // 0xd0
    ObjPtr<RndDrawable, ObjectDir> mDrawOnly; // 0xdc
    ObjPtr<RndDrawable, ObjectDir> mLod; // 0xe8
    float mLodScreenSize; // 0xf4
    bool unkf8; // 0xf8
    std::vector<RndAnimatable*> mAnims; // 0xfc
    std::vector<RndDrawable*> mDraws; // 0x104
    RndDrawable** mDrawItr; // 0x10c
};

#endif
