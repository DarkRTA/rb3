#ifndef RNDOBJ_DIR_H
#define RNDOBJ_DIR_H
#include "obj/MsgSource.h" // MsgSource : public virtual Object
#include "rndobj/Poll.h" // RndPollable : public virtual Object
#include "rndobj/Trans.h" // RndTransformable : public virtual RndHighlightable
#include "rndobj/Anim.h" // RndAnimatable : public virtual Object
#include "rndobj/Draw.h" // RndDrawable : public virtual RndHighlightable
#include "obj/Dir.h" // ObjectDir : public virtual Object
#include "types.h"
#include <vector>
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Env.h"

class RndDir : public ObjectDir, public RndDrawable, public RndAnimatable, public RndTransformable, public RndPollable, public MsgSource {
public:
    RndDir();
    OBJ_CLASSNAME(RndDir)
    OBJ_SET_TYPE(RndDir)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual ~RndDir(){}
    virtual void SetSubDir(bool);
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SyncObjects();
    virtual void RemovingObject(Hmx::Object*);
    virtual void OldLoadProxies(BinStream&, int);
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void UpdateSphere();
    virtual float GetDistanceToPlane(const Plane&, Vector3&);
    virtual bool MakeWorldSphere(Sphere&, bool);
    virtual void DrawShowing();
    virtual RndDrawable* CollideShowing(const Segment&, float&, Plane&);
    virtual int CollidePlane(const Plane&);
    virtual void CollideList(const Segment&, std::list<Collision>&);
    virtual void ListDrawChildren(std::list<RndDrawable*>&);
    virtual void SetFrame(float, float);
    virtual float EndFrame();
    virtual void ListAnimChildren(std::list<RndAnimatable*>&) const;
    virtual void Poll();
    virtual void Enter();
    virtual void Exit();
    virtual void ListPollChildren(std::list<RndPollable*>&) const;
    virtual void Highlight();
    virtual void Export(DataArray*, bool);
    virtual void ChainSourceSubdir(MsgSource*, ObjectDir*);

    DataNode OnShowObjects(DataArray*);
    DataNode OnSupportedEvents(DataArray*);
    
    std::vector<RndDrawable*, u16> mDraws;
    std::vector<RndAnimatable*> mAnims;
    std::vector<RndPollable*, u16> mPolls;
    ObjPtr<RndEnviron, ObjectDir> mEnv;
    Symbol mTestEvent;

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndDir)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndDir)
    }
};

#endif
