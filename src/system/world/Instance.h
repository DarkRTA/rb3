#ifndef WORLD_INSTANCE_H
#define WORLD_INSTANCE_H
#include "rndobj/Dir.h"
#include "obj/Dir.h"
#include <list>

class RndGroup;
class SharedGroup;

class WorldInstance : public RndDir {
public:
    WorldInstance();
    OBJ_CLASSNAME(WorldInstance)
    OBJ_SET_TYPE(WorldInstance)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual ~WorldInstance();
    virtual void SetProxyFile(const FilePath&, bool);
    virtual FilePath& ProxyFile(){ return mDir.GetFile(); }
    virtual void PostSave(BinStream&);
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual float GetDistanceToPlane(const Plane&, Vector3&);
    virtual bool MakeWorldSphere(Sphere&, bool);
    virtual void DrawShowing();
    virtual RndDrawable* CollideShowing(const Segment&, float&, Plane&);
    virtual void Poll();
    virtual void Enter();
    virtual void PreSave(BinStream&);

    void SyncDir();

    ObjDirPtr<WorldInstance> mDir; // 0x18c
    SharedGroup* mSharedGroup; // 0x198
    SharedGroup* mSharedGroup2; // 0x19c

    DECLARE_REVS;
    NEW_OVERLOAD
    NEW_OBJ(WorldInstance)
};

class SharedGroup : public RndPollable {
public:
    SharedGroup(RndGroup*);
    virtual ~SharedGroup();

    void TryPoll(WorldInstance*);
    void TryEnter(WorldInstance*);
    void Draw(const Transform&);
    bool Collide(const Transform&, const Segment&, float&, Plane&);
    float DistanceToPlane(const Transform&, const Plane&, Vector3&);
    bool MakeWorldSphere(const Transform&, Sphere&);
    void AddPolls(RndGroup*);
    void ClearPollMaster();

    RndGroup* mGroup; // 0x8
    ObjPtr<WorldInstance, ObjectDir> mPollMaster; // 0xc
    std::list<RndPollable*> mPolls; // 0x18
};

#endif
