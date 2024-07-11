#ifndef RNDOBJ_TEXBLENDCONTROLLER_H
#define RNDOBJ_TEXBLENDCONTROLLER_H
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"

// forward decs
class RndMesh;
class RndTex;
class RndTransformable;

class RndTexBlendController : public Hmx::Object {
public:
    RndTexBlendController();
    virtual ~RndTexBlendController();
    OBJ_CLASSNAME(TexBlendController);
    OBJ_SET_TYPE(TexBlendController);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    bool GetCurrentDistance(float&) const;
    void UpdateReferenceDistance();
    void UpdateMinDistance();
    void UpdateMaxDistance();
    void UpdateAllDistances();

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndTexBlendController)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndTexBlendController)
    }

    static unsigned short gRev;

    ObjPtr<RndMesh, ObjectDir> mMesh; // 0x1c
    ObjPtr<RndTransformable, ObjectDir> mObject1; // 0x28
    ObjPtr<RndTransformable, ObjectDir> mObject2; // 0x34
    float mReferenceDistance; // 0x40
    float mMinDistance; // 0x44
    float mMaxDistance; // 0x48
    ObjPtr<RndTex, ObjectDir> mTex; // 0x4c
};

#endif
