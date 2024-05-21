#ifndef WORLD_INSTANCE_H
#define WORLD_INSTANCE_H
#include "rndobj/Dir.h"
#include "obj/Dir.h"
#include <list>

class RndGroup;

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
    virtual FilePath* ProxyFile();
    virtual void PostSave(BinStream&);
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual float GetDistanceToPlane(const Plane&, Vector3&){ return 0.0f; }
    virtual int MakeWorldSphere(Sphere&, bool){ return 0; }
    virtual void DrawShowing();
    virtual int CollideShowing(const Segment&, float&, Plane&);
    virtual void Poll();
    virtual void Enter();
    virtual void PreSave(BinStream&);

    ObjDirPtr<WorldInstance> unk18c;
    int unk198;
    int unk19c;
};

class SharedGroup : public RndPollable {
public:
    SharedGroup(RndGroup*);
    virtual ~SharedGroup();

    void AddPolls(RndGroup*);

    RndGroup* unk8;
    ObjPtr<WorldInstance, ObjectDir> unkc;
    std::list<void*> unk18;
};

#endif
