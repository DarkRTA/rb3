#ifndef RNDOBJ_MESHANIM_H
#define RNDOBJ_MESHANIM_H
#include "rndobj/Anim.h"
#include "rndobj/Mesh.h"
#include "utl/Key.h"

class RndMeshAnim : public RndAnimatable {
public:
    RndMeshAnim();
    OBJ_CLASSNAME(MeshAnim);
    OBJ_SET_TYPE(MeshAnim);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~RndMeshAnim();
    virtual void SetFrame(float, float);
    virtual float EndFrame();
    virtual Hmx::Object* AnimTarget();
    virtual void SetKey(float);
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Print();

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndMeshAnim)
    static void Init(){ REGISTER_OBJ_FACTORY(RndMeshAnim) }

    ObjPtr<RndMesh, ObjectDir> mMesh; // 0x10
    Keys<std::vector<Vector3>, std::vector<Vector3> > mVertPointsKeys; // 0x1c
    Keys<std::vector<Vector3>, std::vector<Vector3> > mVertNormalsKeys; // 0x24
    Keys<std::vector<Vector2>, std::vector<Vector2> > mVertTexsKeys; // 0x2c
    Keys<std::vector<Hmx::Color32>, std::vector<Hmx::Color32> > mVertColorsKeys; // 0x34
    ObjOwnerPtr<RndMeshAnim, ObjectDir> mKeysOwner; // 0x3c
};

#endif
