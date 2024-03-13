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

    void operator delete(void* v){
        _MemFree(v);
    }

    ObjPtr<RndMesh, ObjectDir> mMesh;
    ObjPtr<RndTransformable, ObjectDir> mObject1;
    ObjPtr<RndTransformable, ObjectDir> mObject2;
    float mReferenceDistance;
    float mMinDistance;
    float mMaxDistance;
    ObjPtr<RndTex, ObjectDir> mTex;
};

#endif
