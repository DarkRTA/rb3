#ifndef RNDOBJ_PARTLAUNCHER_H
#define RNDOBJ_PARTLAUNCHER_H
#include "rndobj/Poll.h"
#include "rndobj/Part.h"
#include "rndobj/Mesh.h"

class RndPartLauncher : public RndPollable {
public:
    RndPartLauncher();
    OBJ_CLASSNAME(PartLauncher);
    OBJ_SET_TYPE(PartLauncher);
    virtual DataNode Handle(DataArray*, bool);
    virtual void Poll();
    virtual ~RndPartLauncher(){}
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    void LaunchParticles();
    void SetBit(unsigned int, bool);
    void CopyPropsFromPart();

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndPartLauncher)
    static void Init(){ REGISTER_OBJ_FACTORY(RndPartLauncher) }

    ObjPtr<RndParticleSys, ObjectDir> mPart; // 0x8
    ObjPtr<RndTransformable, ObjectDir> mTrans; // 0x14
    ObjPtr<RndMesh, ObjectDir> mMeshEmitter; // 0x20
    int mNumParts; // 0x2c
    Vector2 mEmitRate; // 0x30
    float mEmitCount; // 0x38
    PartOverride* mPartOverride; // 0x3c
};

#endif
