#pragma once
#include "rndobj/Dir.h"
#include "obj/Dir.h"
#include <list>

class RndGroup;
class SharedGroup;

/**
 * @brief A shared RndDir for everything to parent to.
 * Original _objects description:
 * "Shared instance of a RndDir"
 */
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
    void LoadPersistentObjects(BinStream*);
    void DeleteTransientObjects();

    /** "Which file we instance, only set in instances" */
    ObjDirPtr<WorldInstance> mDir; // 0x18c
    /** "Pointer to shared group, if any" */
    SharedGroup* mSharedGroup; // 0x198
    SharedGroup* mSharedGroup2; // 0x19c

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(WorldInstance)
    static void Init(){
        REGISTER_OBJ_FACTORY(WorldInstance)
    }
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
    RndGroup* Group() const { return mGroup; }
    WorldInstance* PollMaster() const { return mPollMaster; }

    RndGroup* mGroup; // 0x8
    ObjPtr<WorldInstance> mPollMaster; // 0xc
    std::list<RndPollable*> mPolls; // 0x18
};
